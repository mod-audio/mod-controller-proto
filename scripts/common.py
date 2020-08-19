#!/usr/bin/env python3

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
resp_errs = []

def read_protocol_file(protofile: str):
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
                    return False

                try:
                    intvalue = int(value)
                except:
                    print("ERROR: invalid value in line", line)
                    return False

                cmdcount[model] = intvalue

            elif line.startswith("BANK_FUNC_"):
                bankfuncs.append(line)

            elif line.startswith("MENU_ID_"):
                menus.append(line)

            elif line.startswith("FLAG_"):
                flagdata = line.replace('FLAG_','',1).split('_',1)
                if len(flagdata) != 2:
                    print("ERROR: incorrect flag syntax (1) in line", line)
                    return False
                flagtype, flagdata = flagdata
                flagdata = flagdata.split(None,1)
                if len(flagdata) != 2:
                    print("ERROR: incorrect flag syntax (2) in line", line)
                    return False
                if flagtype not in flags:
                    flags[flagtype] = []
                flags[flagtype].append(flagdata)
                flags['ALL'].append((flagtype+'_'+flagdata[0], flagdata[1]))

            elif line.startswith("RESP_ERR_"):
                resp_errs.append(line)

            else:
                print("ERROR: unhandled define in line", line)
                return False

    return True
