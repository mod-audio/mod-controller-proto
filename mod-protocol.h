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
//responese: `pi`
#define CMD_PING                      "pi"

// say <message>
//responese: `<message>`
#define CMD_SAY                       "say %s ..."

// led <led_id> <red> <green> <blue>
//responese: `r 0`
//HMI action: turn on LED
//HOST action: TODO, TURN ON PEAKMETER LEDS (if ever needed)
#define CMD_LED                       "l %i %i %i %i ..."

// glcd_text <glcd_id> <x_pos> <y_pos> <text>
//responese: `r 0`
//HMI action: display the line text <text> at x y
//HOST action: -
#define CMD_GLCD_TEXT                 "glcd_text %i %i %i %s"

// glcd_dialog <content>
//responese: `r 0`
//HMI action: display the text <text> in a popup
//HOST action: 0
#define CMD_GLCD_DIALOG               "glcd_dialog %s"

// glcd_draw <glcd_id> <x_pos> <y_pos> <data>
//responese: `r 0`
//HMI action: display the data <data> at x y
//HOST action: -
#define CMD_GLCD_DRAW                 "glcd_draw %i %i %i %s"

// ui_con
//responese: `r 0`
//HMI action: now aware the web-ui is connected
//HOST action: -
#define CMD_GUI_CONNECTED             "uc"

// ui_dis
//responese: `r 0`
//HMI action: now aware the web-ui is disconnected
//HOST action: -
#define CMD_GUI_DISCONNECTED          "ud"

// control_add <hw_id> <label> <control_prop> <unit> <value> <max> <min> <steps> 
//             [scale_point_count] [scale_point_flag] {[scale_point1_label] [scale_point1_value]}...
//responese: `r 0`
//HMI action: assign a new hw control
//HOST action: -
#define CMD_CONTROL_ADD               "a %i %s %i %s %f %f %f %i %i ..."

// control_rm <hw_id>
//responese: `r 0`
//HMI action: unassign a hw control
//HOST action: -
#define CMD_CONTROL_REMOVE            "d %i ..."

// control_get <hw_id> 
//responese: `s %i %f`
//HMI action: returns the assigned control value via control_set
//HOST action: returns the assigned control value via control_set
#define CMD_CONTROL_GET               "g %i"

// control_set <hw_id><value>
//responese: `r 0`
//HMI action: sends assigned control data
//HOST action: sends assigned control data
#define CMD_CONTROL_SET               "s %i %f"

// control_set <hw_id><value>
//responese: `a %i %s %i %s %f %f %f %i %i ...`
//HMI action: -
//HOST action: sends back a control_add command with new control page data
#define CMD_CONTROL_PAGE              "ncp %i %i"

// initial_state <amount of pb's> <page_min> <page_max> <bank_id> <pb_id> [current_pedalboards_list]
//responese: `r 0`
//HMI action: save initial pedalboard and bank data in static memory
//HOST action: -
#define CMD_INITIAL_STATE             "is %i %i %i %i %i %s %s ..."

// banks <direction> <current banks hover id>
//responese: `new banks list, with updated items`
//HMI action: -
//HOST action: returns a new page of banks 
#define CMD_BANKS                     "b %i %i"

// pedalboards <up/down page> <current page index> <bank_uid>
//responese: `new pedalboard list, with updated items`
//HMI action: -
//HOST action: returns a new page of pedalboards 
#define CMD_PEDALBOARDS               "p %i %i %s"

// pedalboard <bank_id> <pedalboard_uid>
//responese: `r 0`
//HMI action: -
//HOST action: loads the requested pedalboard 
#define CMD_LOAD_PEDALBOARD           "pb %i %s"

// pedalboard_reset
//responese: `r 0`
//HMI action: -
//HOST action: resets the pedalboard to the last saved state
#define CMD_PEDALBOARD_RESET          "pr"

// pedalboard_save
//responese: `r 0`
//HMI action: -
//HOST action: saves the pedalboard in the current state
#define CMD_PEDALBOARD_SAVE           "ps"

//set the name of the current pedalboard
//responese: `r 0`
//HMI action: save and possibly display the new pedalboard name
//HOST action: -
#define CMD_PB_NAME_SET               "pn %s ..."

//clear both snapshots and controls 
//responese: `r 0`
//HMI action: clear all pedalboard related items
//HOST action: -
#define CMD_CLEAR_PEDALBOARD           "pcl"

// tuner <frequency> <note> <cents>
//responese: `r 0`
//HMI action: adjust the tuner screen to new data
//HOST action: -
#define CMD_TUNER                     "ts %f %s %i"

// tuner on
//responese: `r 0`
//HMI action: TODO: turn on the tuner from the system
//HOST action: turn on the tuner
#define CMD_TUNER_ON                  "tn"
// tuner off
//responese: `r 0`
//HMI action: TODO: turn off the tuner from the system
//HOST action: turn off the tuner
#define CMD_TUNER_OFF                 "tf"
// tuner_input <input>
//responese: `r 0`
//HMI action: -
//HOST action: changes the tuner input source 
#define CMD_TUNER_INPUT               "ti %i"

// resp <status> ...
//responese: -
//HMI action: -
//HOST action: -
#define CMD_RESPONSE                  "r %i ..."


// reboot in restore mode
//responese: `r 0`
//HMI action: -
//HOST action: boot into restore mode
#define CMD_RESTORE                   "restore"

/*
********************************
    SHARED MENU COMMANDS
********************************
Almost all menu items are also setable via the MENU_ITEM_CHANGE command, but some have their dedicated
*/    
//change a menu setting [uint8_t]<menu_item_id> [uint16_t]<menu_item_value>
//responese: `r 0`
//HMI action: change the setting in the menu acourding to the settings ID
//HOST action: change the setting in the system acourding to the settings ID
//if there is only 1 argument given, the value of that argument will be returned
#define CMD_MENU_ITEM_CHANGE          "c %i %i ..."

//get profile data command <int profile>
//responese: `r 0`
//HMI action: -
//HOST action: loads the selected user profile
#define CMD_LOAD_PROFILE              "upr %i"

//store the current profile in mod-ui
//responese: `r 0`
//HMI action: -
//HOST action: store the selected user profile with current settings
#define CMD_STORE_PROFILE             "ups %i"

/*
********************************
    Menu Item ID's
********************************

Each menu item in the MOD OS has its own ID, this allows for it to be easily changed and parsed to both sides of the system
*/  
//shared
#define MENU_ID_SL_IN 				0
#define MENU_ID_SL_OUT 				1
#define MENU_ID_TUNER_MUTE 			2
#define MENU_ID_QUICK_BYPASS 		3
#define MENU_ID_PLAY_STATUS			4
#define MENU_ID_MIDI_CLK_SOURCE		5
#define MENU_ID_MIDI_CLK_SEND		6
#define MENU_ID_SNAPSHOT_PRGCHGE   	7
#define MENU_ID_PB_PRGCHNGE        	8
#define MENU_ID_TEMPO				9
#define MENU_ID_BEATS_PER_BAR		10
#define MENU_ID_BYPASS1				11
#define MENU_ID_BYPASS2				12
#define MENU_ID_BRIGHTNESS   		13
#define MENU_ID_CURRENT_PROFILE		14
//duo
#define MENU_ID_FOOTSWITCH_NAV    	30
//duox
#define MENU_ID_EXP_CV_INPUT		40
#define MENU_ID_HP_CV_OUTPUT		41
#define MENU_ID_MASTER_VOL_PORT		42
#define MENU_ID_EXP_MODE			43
//dwarf     


#define MENU_ID_TOP					44
/*
********************************
    Control Property definitions
********************************
*/

//// Control propertires definitions
#define CONTROL_PROP_LINEAR         0
#define CONTROL_PROP_BYPASS         1
#define CONTROL_PROP_TAP_TEMPO      2
#define CONTROL_PROP_ENUMERATION    4
#define CONTROL_PROP_SCALE_POINTS   8
#define CONTROL_PROP_TRIGGER        16
#define CONTROL_PROP_TOGGLED        32
#define CONTROL_PROP_LOGARITHMIC    64
#define CONTROL_PROP_INTEGER        128
#define CONTROL_PROP_REVERSE_ENUM   256
#define CONTROL_PROP_MOMENTARY      512

//// Banks functions definition
#define BANK_FUNC_NONE              0
#define BANK_FUNC_TRUE_BYPASS       1
#define BANK_FUNC_PEDALBOARD_NEXT   2
#define BANK_FUNC_PEDALBOARD_PREV   3
#define BANK_FUNC_AMOUNT            4

//command bitmask definitions
//list pagination bitmasks
#define BM_NP_PAGE_UP         (1 << 1)
#define BM_NP_WRAP_AROUND     (1 << 2)
#define BM_NP_INITIAL_REQ     (1 << 3)

//scalepoints bitmasks
#define BM_SCALPOINT_PAGINATED   		(1 << 0)
#define BM_SCALPOINT_WRAP_AROUND 		(1 << 1)
#define BM_SCALPOINT_END_PAGE    		(1 << 2)
#define BM_SCALPOINT_ALT_LED_COLOR		(1 << 3)

/*
********************************
    Duo Specific commands
********************************
*/

//the HMI is ready to boot
#define CMD_DUO_BOOT              "boot %i %i %s ..."

//set display brightness  <brightness>
//responese: `r 0`
//HMI action: sets display brightness <brightness>
//HOST action: -
#define CMD_DUO_BRIGHTNESS_SET            "bs %i"

//enable footswitch bank navigation [uint8_t]<foot>
//responese: `r 0`
//HMI action: turns on bank navigation on footswitch <foot>
//HOST action: -
#define CMD_DUO_FOOT_NAVIG                "fn %i"

//TODO, IS THIS COMMAND STILL USED?!?
// bank_config <hw_id> <function>
//responese: `r 0`
//HMI action: turns on bank navigation on footswitch <hw_id> with <function>
//HOST action: -
#define CMD_DUO_BANK_CONFIG               "bc %i %i"

// control_next <hw_id>
//responese: `r 0`
//HMI action: -
//HOST action: reassigns control <hw_id> with a new actuator
#define CMD_DUO_CONTROL_NEXT              "n %i"

// control_index_set <hw_id> <current_index> <total_index>
//responese: `r 0`
//HMI action: saves and possibly displays the control indexes for control <hw_id>
//HOST action: -
#define CMD_DUO_CONTROL_INDEX_SET          "si %i %i %i"
/*
********************************
    DuoX Specific commands
********************************
*/

//the HMI is ready to boot
#define CMD_DUOX_BOOT             "boot %i %i %s ..."

//request the next page <page_to_load>
//responese: `r 0`
//HMI action: -
//HOST action: reassigns all controls to the next control page when available
#define CMD_DUOX_NEXT_PAGE             "lp %i"

//save a snapshot <snapshot_id>
//responese: `r 0`
//HMI action: -
//HOST action: save all controls as a snapshot with index <snapshot_id> 
#define CMD_DUOX_SAVE_SNAPSHOT         "ss %i"

//load a snapshot <snapshot_id>
//responese: `r 0`
//HMI action: -
//HOST action: set all controls to a snapshot with index <snapshot_id> 
#define CMD_DUOX_LOAD_SNAPSHOT         "sl %i"

//clear a snapshot <snapshot_id>
//responese: `r 0`
//HMI action: -
//HOST action: clear a snapshot with index <snapshot_id> 
#define CMD_DUOX_CLEAR_SNAPSHOT        "sc"

/*
********************************
    Dwarf Specific commands
********************************
*/

//TODO AS DEVELOPMENT HAS NOT STARTED

#define COMMAND_COUNT_DUO   36
#define COMMAND_COUNT_DUOX  35
#define COMMAND_COUNT_DWARF 30
