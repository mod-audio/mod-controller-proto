/*
************************************************************************************************************************
*           MOD Devices Controller Protocol Definitions
************************************************************************************************************************
*/

/*
********************************
    SHARED DEVICE COMMANDS
********************************
*/

// ping
//response: `r 0`
//HMI action: nothing, just respond back
//HOST action: -
#define CMD_PING                      "pi"

// say <message>
//response: `<message>`
#define CMD_SAY                       "say %s ..."

// led <led_id> <red> <green> <blue>
//response: `r 0`
//HMI action: turn on LED
//HOST action: TODO, TURN ON PEAKMETER LEDS (if ever needed)
#define CMD_LED                       "l %i %i %i %i ..."

// glcd_text <glcd_id> <x_pos> <y_pos> <text>
//response: `r 0`
//HMI action: display the line text <text> at x y
//HOST action: -
#define CMD_GLCD_TEXT                 "glcd_text %i %i %i %s"

// glcd_dialog <content>
//response: `r 0`
//HMI action: display the text <text> in a popup
//HOST action: 0
#define CMD_GLCD_DIALOG               "glcd_dialog %s"

// glcd_draw <glcd_id> <x_pos> <y_pos> <data>
//response: `r 0`
//HMI action: display the data <data> at x y
//HOST action: -
#define CMD_GLCD_DRAW                 "glcd_draw %i %i %i %s"

// ui_con
//response: `r 0`
//HMI action: now aware the web-ui is connected
//HOST action: -
#define CMD_GUI_CONNECTED             "uc"

// ui_dis
//response: `r 0`
//HMI action: now aware the web-ui is disconnected
//HOST action: -
#define CMD_GUI_DISCONNECTED          "ud"

// control_add <hw_id> <label> <control_prop> <unit> <value> <max> <min> <steps>
//             [scale_point_count] [scale_point_flag] [scale_point_index] {[scale_point1_label] [scale_point1_value]}...
//response: `r 0`
//HMI action: assign a new hw control
//HOST action: -
#define CMD_CONTROL_ADD               "a %i %s %i %s %f %f %f %i %i ..."

// control_rm <hw_id>
//response: `r 0`
//HMI action: unassign a hw control
//HOST action: -
#define CMD_CONTROL_REMOVE            "d %i ..."

// control_get <hw_id>
//response: `s %i %f`
//HMI action: -
//HOST action: returns the assigned control value via control_set
#define CMD_CONTROL_GET               "g %i"

// control_set <hw_id><value>
//response: `r 0`
//HMI action: sends assigned control data
//HOST action: sends assigned control data
#define CMD_CONTROL_SET               "s %i %f"

// control_set <hw_id><value>
//response: `a %i %s %i %s %f %f %f %i %i ...`
//HMI action: -
//HOST action: sends back a control_add command with new control page data
#define CMD_CONTROL_PAGE              "ncp %i %i"

// initial_state <amount of pb's> <page_min> <page_max> <bank_id> <pb_id> [current_pedalboards_list]
//response: `r 0`
//HMI action: save initial pedalboard and bank data in static memory
//HOST action: -
#define CMD_INITIAL_STATE             "is %i %i %i %i %i %s %s ..."

// banks <direction> <current banks hover id>
//response: `new banks list, with updated items`
//HMI action: -
//HOST action: returns a new page of banks
#define CMD_BANKS                     "b %i %i"

// pedalboards <up/down page> <current page index> <bank_uid>
//response: `new pedalboard list, with updated items`
//HMI action: -
//HOST action: returns a new page of pedalboards
#define CMD_PEDALBOARDS               "p %i %i %i"

// pedalboard <bank_id> <pedalboard_uid>
//response: `r 0`
//HMI action: -
//HOST action: loads the requested pedalboard
#define CMD_PEDALBOARD_LOAD           "pb %i %s"

// snapshots <up/down page> <current page index>
//response: `new snapshot list, with updated items`
//HMI action: -
//HOST action: returns a new page of pedalboards
#define CMD_SNAPSHOTS                 "ssg %i %i"

// pedalboard <pedalboard_uid>
//response: `r 0`
//HMI action: -
//HOST action: loads the requested snapshot
#define CMD_SNAPSHOTS_LOAD            "ssl %s"

// pedalboard_reset
//response: `r 0`
//HMI action: -
//HOST action: resets the pedalboard to the last saved state
#define CMD_PEDALBOARD_RESET          "pr"

// pedalboard_save
//response: `r 0`
//HMI action: -
//HOST action: saves the pedalboard in the current state
#define CMD_PEDALBOARD_SAVE           "ps"

//set the name of the current pedalboard
//response: `r 0`
//HMI action: save and possibly display the new pedalboard name
//HOST action: -
#define CMD_PEDALBOARD_NAME_SET       "pn %s ..."

//clear both snapshots and controls
//response: `r 0`
//HMI action: clear all pedalboard related items
//HOST action: -
#define CMD_PEDALBOARD_CLEAR          "pcl"

//set the name of the current snapshot
//response: `r 0`
//HMI action: save and possibly display the new snapshot name
//HOST action: -
#define CMD_SNAPSHOT_NAME_SET         "sn %s ..."

// tuner <frequency> <note> <cents>
//response: `r 0`
//HMI action: adjust the tuner screen to new data
//HOST action: -
#define CMD_TUNER                     "ts %f %s %i"

// tuner on
//response: `r 0`
//HMI action: -
//HOST action: turn on the tuner
#define CMD_TUNER_ON                  "tn"

// tuner off
//response: `r 0`
//HMI action: -
//HOST action: turn off the tuner
#define CMD_TUNER_OFF                 "tf"

// tuner_input <input>
//response: `r 0`
//HMI action: -
//HOST action: changes the tuner input source
#define CMD_TUNER_INPUT               "ti %i"

// reboot in restore mode
//response: `r 0`
//HMI action: boot into restore mode
//HOST action: -
#define CMD_RESTORE                   "restore"

// resp <status> ...
//response: -
//HMI action: -
//HOST action: -
#define CMD_RESPONSE                  "r %i ..."

/*
********************************
    SHARED MENU COMMANDS
********************************
Almost all menu items are also setable via the MENU_ITEM_CHANGE command, but some have their dedicated
*/

//change a menu setting [uint8_t]<menu_item_id> [uint16_t]<menu_item_value>
//response: `r 0`
//HMI action: change the setting in the menu acourding to the settings ID
//HOST action: change the setting in the system acourding to the settings ID
//if there is only 1 argument given, the value of that argument will be returned
#define CMD_MENU_ITEM_CHANGE          "c %i %i ..."

//get profile data command <int profile>
//response: `r 0`
//HMI action: -
//HOST action: loads the selected user profile
#define CMD_PROFILE_LOAD              "upr %i"

//store the current profile in mod-ui
//response: `r 0`
//HMI action: -
//HOST action: store the selected user profile with current settings
#define CMD_PROFILE_STORE             "ups %i"

//request the next page <page_to_load>
//response: `r 0`
//HMI action: -
//HOST action: reassigns all controls to the next control page when available
#define CMD_NEXT_PAGE                 "lp %i"

//clear all HMI EEPROM settings
//response: `r 0`
//HMI action: clear internal EEPROM settings and reset default value's
//HOST action: -
#define CMD_RESET_EEPROM              "reset_eeprom"

/*
********************************
    Duo Specific commands
********************************
*/

//the HMI is ready to boot
#define CMD_DUO_BOOT                  "boot %i %i %s ..."

//enable footswitch bank navigation [uint8_t]<foot>
//response: `r 0`
//HMI action: -
//HOST action: turns on bank navigation on footswitch <foot>
#define CMD_DUO_FOOT_NAVIG            "fn %i"

//TODO, IS THIS COMMAND STILL USED?!?
// bank_config <hw_id> <function>
//response: `r 0`
//HMI action: turns on bank navigation on footswitch <hw_id> with <function>
//HOST action: -
#define CMD_DUO_BANK_CONFIG           "bc %i %i"

// control_next <hw_id>
//response: `r 0`
//HMI action: -
//HOST action: reassigns control <hw_id> with a new actuator
#define CMD_DUO_CONTROL_NEXT          "n %i"

// control_index_set <hw_id> <current_index> <total_index>
//response: `r 0`
//HMI action: saves and possibly displays the control indexes for control <hw_id>
//HOST action: -
#define CMD_DUO_CONTROL_INDEX_SET     "si %i %i %i"

/*
********************************
    DuoX Specific commands
********************************
*/

//the HMI is ready to boot
#define CMD_DUOX_BOOT                 "boot %i %i %s ..."

//save a snapshot <snapshot_id>
//response: `r 0`
//HMI action: -
//HOST action: save all controls as a snapshot with index <snapshot_id>
#define CMD_DUOX_SNAPSHOT_SAVE        "ss %i"

//load a snapshot <snapshot_id>
//response: `r 0`
//HMI action: -
//HOST action: set all controls to a snapshot with index <snapshot_id>
#define CMD_DUOX_SNAPSHOT_LOAD        "sl %i"

// TODO is this really used??
//clear a snapshot <snapshot_id>
//response: `r 0`
//HMI action: -
//HOST action: clear a snapshot with index <snapshot_id>
#define CMD_DUOX_SNAPSHOT_CLEAR       "sc"

//let the HMI know how many pages there are
//response: `r 0`
//HMI action: turn on scrolling through a selection of pages
//HOST action: -
#define CMD_DUOX_PAGES_AVAILABLE      "pa %i %i %i %i %i %i"

/*
********************************
    Dwarf Specific commands
********************************
*/

//report to UI that a subpage changed for control <hw_id> <subpage>
//response: `r 0`
//HMI action: -
//HOST action: reassigns control <hw_id> with the actuator from the requested page
#define CMD_DWARF_CONTROL_SUBPAGE     "cs %i %i"

//let the HMI know how many pages there are
//response: `r 0`
//HMI action: turn on scrolling through a selection of pages
//HOST action: -
#define CMD_DWARF_PAGES_AVAILABLE     "pa %i %i %i %i %i %i %i %i"

/*
********************************
    Selftest Specific commands
********************************
*/

//send if an encoder is clicked (used in selftest) <encoder_id>
//response: -
//HMI action: -
//HOST action: -
#define CMD_SELFTEST_ENCODER_CLICKED      "enc_clicked %i"

//send if an encoder is turned left (used in selftest) <encoder_id>
//response: -
//HMI action: -
//HOST action: -
#define CMD_SELFTEST_ENCODER_LEFT         "enc_left %i"

//send if an encoder is turned right (used in selftest) <encoder_id>
//response: -
//HMI action: -
//HOST action: -
#define CMD_SELFTEST_ENCODER_RIGHT        "enc_right %i"

//send if an button is clicked (used in selftest) <button_id>
//response: -
//HMI action: -
//HOST action: -
#define CMD_SELFTEST_BUTTON_CLICKED       "button_clicked %i"

//send so HMI can check calibration (used in selftest) <pot_id>
//response: -
//HMI action: check call and return id when ok
//HOST action: -
#define CMD_SELFTEST_CHECK_CALIBRATION    "pot_call_check %i"

//send if an button is clicked (used in selftest) <pot_id>
//response: -
//HMI action: -
//HOST action: -
#define CMD_SELFTEST_CALLIBRATION_OK      "pot_call_ok %i"

//send if the selftest hangs on a control to continue
//response: -
//HMI action: -
//HOST action: -
#define CMD_SELFTEST_SKIP_CONTROL_ENABLE  "control_skip_enable"

//send if the selftest hangs on a control to continue
//response: -
//HMI action: -
//HOST action: -
#define CMD_SELFTEST_SKIP_CONTROL         "control_bad_skip"

//send to the HMI to save the current value of a pot as the calibration value (used in selftest) <min/max> <pot_id>
//response: -
//HMI action: save current pot value as min/max calibration value
//HOST action: -
#define CMD_SELFTEST_SAVE_POT_CALIBRATION "save_pot_cal %i %i"

/*
********************************
    Command count per device
********************************
*/

#define COMMAND_COUNT_DUO   49
#define COMMAND_COUNT_DUOX  49
#define COMMAND_COUNT_DWARF 46

/*
********************************
    Banks functions definitions
********************************
*/

#define BANK_FUNC_NONE                  0
#define BANK_FUNC_TRUE_BYPASS           1
#define BANK_FUNC_PEDALBOARD_NEXT       2
#define BANK_FUNC_PEDALBOARD_PREV       3
#define BANK_FUNC_COUNT                 4

/*
********************************
    Flags/bitmasks definitions
********************************
*/

//command bitmask definitions
#define FLAG_CONTROL_BYPASS             0x001
#define FLAG_CONTROL_TAP_TEMPO          0x002
#define FLAG_CONTROL_ENUMERATION        0x004
#define FLAG_CONTROL_SCALE_POINTS       0x008
#define FLAG_CONTROL_TRIGGER            0x010
#define FLAG_CONTROL_TOGGLED            0x020
#define FLAG_CONTROL_LOGARITHMIC        0x040
#define FLAG_CONTROL_INTEGER            0x080
#define FLAG_CONTROL_REVERSE            0x100
#define FLAG_CONTROL_MOMENTARY          0x200

//list pagination bitmasks
#define FLAG_PAGINATION_PAGE_UP         0x1
#define FLAG_PAGINATION_WRAP_AROUND     0x2
#define FLAG_PAGINATION_INITIAL_REQ     0x4
#define FLAG_PAGINATION_ALT_LED_COLOR   0x8

//scalepoints bitmasks
#define FLAG_SCALEPOINT_PAGINATED       0x1
#define FLAG_SCALEPOINT_WRAP_AROUND     0x2
#define FLAG_SCALEPOINT_END_PAGE        0x4
#define FLAG_SCALEPOINT_ALT_LED_COLOR   0x8

/*
********************************
    Menu Item ID's
********************************
Each menu item in the MOD OS has its own ID, this allows for it to be easily changed and parsed to both sides of the system
*/

//shared
#define MENU_ID_SL_IN                   0
#define MENU_ID_SL_OUT                  1
#define MENU_ID_TUNER_MUTE              2
#define MENU_ID_QUICK_BYPASS            3
#define MENU_ID_PLAY_STATUS             4
#define MENU_ID_MIDI_CLK_SOURCE         5
#define MENU_ID_MIDI_CLK_SEND           6
#define MENU_ID_SNAPSHOT_PRGCHGE        7
#define MENU_ID_PB_PRGCHNGE             8
#define MENU_ID_TEMPO                   9
#define MENU_ID_BEATS_PER_BAR           10
#define MENU_ID_BYPASS1                 11
#define MENU_ID_BYPASS2                 12
#define MENU_ID_BRIGHTNESS              13
#define MENU_ID_CURRENT_PROFILE         14
//duo
#define MENU_ID_FOOTSWITCH_NAV          30
//duox
#define MENU_ID_EXP_CV_INPUT            40
#define MENU_ID_HP_CV_OUTPUT            41
#define MENU_ID_MASTER_VOL_PORT         42
#define MENU_ID_EXP_MODE                43
//dwarf

#define MENU_ID_TOP                     44

/*
********************************
    Response error messages
********************************
*/

// error messages configuration
#define RESP_ERR_COMMAND_NOT_FOUND      "not found"
#define RESP_ERR_MANY_ARGUMENTS         "many arguments"
#define RESP_ERR_FEW_ARGUMENTS          "few arguments"
#define RESP_ERR_INVALID_ARGUMENT       "invalid argument"
