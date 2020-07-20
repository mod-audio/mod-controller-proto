#!/usr/bin/env python3

import os
import sys

if len(sys.argv) < 3:
    sys.exit(1)

protofile = sys.argv[1]
usagefile = sys.argv[2]

validmodels = (
    'DUO',
    'DUOX',
    'DWARF',
)

cmds = dict((model,[]) for model in validmodels)
cmds.update({'ALL':[]})

cmdcount = dict((model,0) for model in validmodels)

bankfuncs = []
menus = []

flags = {'ALL':[]}

with open(protofile, 'r') as fh:
    stopcounter = 0

    while True:
        line = fh.readline()

        if not line:
            stopcounter += 1
            if stopcounter == 10:
                break
        else:
            stopcounter = 0

        line = line.strip()

        if not line.startswith('#define'):
            continue

        line = line.replace('#define','',1).strip()

        if line.startswith("CMD_"):
            for model in validmodels:
                if line.startswith("CMD_{}_".format(model)):
                    cmds[model].append(line)
                    break
            else:
                cmds['ALL'].append(line)

        elif line.startswith("COMMAND_COUNT_"):
            model, value = line.replace("COMMAND_COUNT_","",1).split()

            if model not in validmodels:
                print("ERROR: invalid model in line", line)
                sys.exit(2)

            try:
                intvalue = int(value)
            except:
                print("ERROR: invalid value in line", line)
                sys.exit(2)

            cmdcount[model] = intvalue

        elif line.startswith("BANK_FUNC_"):
            bankfuncs.append(line)

        elif line.startswith("MENU_ID_"):
            menus.append(line)

        elif line.startswith("FLAG_"):
            flagdata = line.replace('FLAG_','',1).split('_',1)
            if len(flagdata) != 2:
                print("ERROR: incorrect flag syntax (1) in line", line)
                sys.exit(2)
            flagtype, flagdata = flagdata
            flagdata = flagdata.split(None,1)
            if len(flagdata) != 2:
                print("ERROR: incorrect flag syntax (2) in line", line)
                sys.exit(2)
            if flagtype not in flags:
                flags[flagtype] = []
            flags[flagtype].append(flagdata)
            flags['ALL'].append((flagtype+'_'+flagdata[0], flagdata[1]))

        else:
            print("ERROR: unhandled define in line", line)
            sys.exit(2)

# tests follow, flag is set if we should exit with error
error = False

# test 1: check if count matches
for model in validmodels:
    realcount = len(cmds['ALL']) + len(cmds[model])
    if cmdcount[model] != realcount:
        error = True
        print("ERROR: command count for", model, "does not match value in protocol file")
        print(" file has {}, but real value is {}".format(cmdcount[model], realcount))

# test 2: cmds must be unique
cmds_ids = []

for cmd in cmds['ALL']:
    cmd_id = cmd.split(None,1)[1].strip()[1:].split(None,1)[0].replace('"','')

    if cmd_id not in cmds_ids:
        cmds_ids.append(cmd_id)
    else:
        error = True
        print("ERROR: command", cmd_id, "is duplicated")

for model in validmodels:
    model_cmds_ids = cmds_ids.copy()

    for cmd in cmds[model]:
        cmd_id = cmd.split(None,1)[1].strip()[1:].split(None,1)[0].replace('"','')

        if cmd_id not in model_cmds_ids:
            model_cmds_ids.append(cmd_id)
        else:
            error = True
            print("ERROR: command", cmd_id, "is duplicated in the device-specific", model)

# test 3: menu ids must be unique
menus_ids = []

for menu in menus:
    menu_id = menu.split(None,1)[1].strip()

    try:
        int_menu_id = int(menu_id)
    except:
        error = True
        print("ERROR: menu define", menu, "cannot be converted to integer")
        continue

    if int_menu_id not in menus_ids:
        menus_ids.append(int_menu_id)
    else:
        error = True
        print("ERROR: menu", menu_id, "is duplicated")

# test 4: bank functions must be unique
bankfuncs_ids = []

for bankfunc in bankfuncs:
    bankfunc_id = bankfunc.split(None,1)[1].strip()

    try:
        int_bankfunc_id = int(bankfunc_id)
    except:
        error = True
        print("ERROR: bank function define", bankfunc, "cannot be converted to integer")
        continue

    if int_bankfunc_id not in bankfuncs_ids:
        bankfuncs_ids.append(int_bankfunc_id)
    else:
        error = True
        print("ERROR: bank function", bankfunc_id, "is duplicated")

# test 5: check flags, must be unique and a real flag
flags_all = flags.pop('ALL')
flags_ids = {'ALL':[]}
valid_flags = (0,) + tuple(1 << v for v in range(16))

for flagname, flagvalue in flags_all:
    if flagname not in flags_ids['ALL']:
        flags_ids['ALL'].append(flagname)
    else:
        error = True
        print("ERROR: flag value {} for {} is duplicated".format(flagvalue, flagname))

for flagtype, flagdata in flags.items():
    flags_ids[flagtype] = []

    for flagname, flagvalue in flagdata:
        try:
            flagvalue = int(flagvalue, 16)
        except:
            error = True
            print("ERROR: flag value {} for {} cannot be converted to integer".format(flagvalue, flagname))
            continue

        if flagvalue not in flags_ids[flagtype]:
            flags_ids[flagtype].append(flagvalue)
        else:
            error = True
            print("ERROR: flag value {} for {} is duplicated".format(flagvalue, flagname))

        if flagvalue not in valid_flags:
            error = True
            print("ERROR: flag value {} for {} is not a valid flag (must be a power of 2)".format(flagvalue, flagname))

# exit now in case of error
if error:
    sys.exit(2)

# now we can write to the usage file, which will test building of the protocol in C code
with open(usagefile, 'w') as fh:
    fh.write('#include "../mod-protocol.h"\n')
    fh.write('#include <stdio.h>\n')
    fh.write('int main()\n{\n')
    fh.write('\tconst char* tmp;\n')
    for cmd in cmds['ALL']:
        fh.write('\ttmp = {};\n'.format(cmd.split(None,1)[0]))
        fh.write('\tputs(tmp);\n');
    for model in validmodels:
        for cmd in cmds[model]:
            fh.write('\ttmp = {};\n'.format(cmd.split(None,1)[0]))
            fh.write('\tputs(tmp);\n');
    fh.write('\treturn 0;\n}\n')
