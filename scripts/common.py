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

_CMD_SYS_PREFIX = None
_CMD_SYS_LENGTH = None
_CMD_SYS_DATA_LENGTH = None

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

            if not line:
                print("ERROR: empty define in line", line)
                return False

            if line.startswith("CMD_"):
                if line.startswith("CMD_RESPONSE_"):
                    continue

                for model in validmodels:
                    if line.startswith("CMD_{}_".format(model)):
                        cmds[model].append(line)
                        break
                else:
                    cmds['ALL'].append(line)

                # extra checks for system commands
                if line.startswith("CMD_SYS_"):
                    if _CMD_SYS_PREFIX is None:
                        print("ERROR: _CMD_SYS_PREFIX is not defined")
                        return False
                    if _CMD_SYS_LENGTH is None:
                        print("ERROR: _CMD_SYS_PREFIX is not defined")
                        return False
                    macro, string = line.replace("CMD_SYS_","",1).split(None,1)
                    if " " in string:
                        syscmd,sysargs = string[1:-1].split(None,1)
                    else:
                        syscmd = string[1:-1]
                        sysargs = ""
                    if len(syscmd) != _CMD_SYS_LENGTH:
                        print("ERROR: system command has invalid length:", syscmd)
                        return False
                    if not syscmd.startswith(_CMD_SYS_PREFIX):
                        print("ERROR: system command has invalid prefix:", syscmd, "vs", _CMD_SYS_PREFIX)
                        return False
                    if sysargs:
                        sysargs = sysargs.split(" ")
                        if len(sysargs) == 1:
                            print("ERROR: system command has single argument:", syscmd, "(should be size + real args)")
                            return False
                        if sysargs[0] != "%02x":
                            print("ERROR: first argument of system command must be %02x:", syscmd)
                            return False

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

            elif line.startswith("_CMD_SYS_PREFIX"):
                _CMD_SYS_PREFIX = line.split()[1][1:-1]

            elif line.startswith("_CMD_SYS_LENGTH"):
                _CMD_SYS_LENGTH = int(line.split()[1])

            elif line.startswith("_CMD_SYS_DATA_LENGTH"):
                _CMD_SYS_DATA_LENGTH = int(line.split()[1])

            else:
                print("ERROR: unhandled define in line", line)
                return False

    return True
