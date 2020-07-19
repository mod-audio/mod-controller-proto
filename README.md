# mod-controller-proto 

This repository contains the shared protocol between MOD's devices controller and mod-ui.

The protocol and its header file must follow these strict rules:

 1. all different types of command, menu id, flags etc must each have a unique prefix  
    (commands are "CMD_", menu ids are "MENU_ID_", etc)

 2. All shared commands must be unique

 3. Each device can have its own specific set of commands, but they also be unique for a device usage.  
    They do not need to be unique across devices though.

 4. Menu IDs must be unique

 5. Bank function IDs must be unique

 6. Control properties are bitmask flags, so they must be unique and a power of 2

Running `make` will run a script and build the protocol in C to ensure these rules are being followed.
