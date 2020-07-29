#!/usr/bin/env python3

import os
import sys

if len(sys.argv) < 3:
    sys.exit(1)

protofile = sys.argv[1]
usagefile = sys.argv[2]

from common import *

if not read_protocol_file(protofile):
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
