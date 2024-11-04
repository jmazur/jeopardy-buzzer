# Jeopardy Buzzer
This project is a Jeopardy! inspired buzzer for home use. You can connect up to
10 contestants and 1 host to play trivia game. The first contestant to buzz in
locks all the other contestants out. 

The buzzers communicate over a local WIFI which can be configured in the
firmware.

## Hardware
This project uses an ESP 32 S2 SOLO. All schematics and PCB design was completed
using KiCAD. The full project can be found in the `pcb` folder.

There is a known issue with the spacing of the button contacts at the bottom of
the pcb, they need a little more space between them. They can still be used
as-is (which is why it didn't fixed earlier) but any new boards can use this
design change.

This project also uses a non-standard battery. I ran out of time to work on a
battery circuit to use a standard AA battery so I opted for a 
`3.2 Volt 600 mAh LiFePO4 14500 Battery` instead. It would be really nice to
change this to a single or a pair of AA or AAA batteries in a future version.

## Software
All firmware is compiled and sent to the ESP using the Arduino IDE. All files
are located in the `firmware` folder.

There is a flag called `IS_HOST` which differentiates buzzers between hosts and
contestants. There can only ever be 1 host per WIFI network. There can be up to
10 contestants before the network stops allowing new connections.
