# GENESIS2PCE

This adapter PCB allows connecting Genesis 3 or 6 button controllers to a PC Engine console.
It consists of all the components a real PC Engine 6 button controller has + an Atmega328p for interfacing with Genesis controllers.
When connecting a Genesis 6 button controller without holding the Mode button, the adapter will go into 6 button mode.
This means you can use it as an actual 6 button PC Engine adapter for the handful of games that support it (Street Fighter 2, Art of Fighting, Fatal Fury 2 etc.).
To ensure compatiblity with other games and the Sega Genesis 6 button controller, one should hold the Mode button while powering on the adapter to put the controller into 3 button mode and the adapter into 2 button mode. Sega Genesis 3 button controllers will always put the adapter into 2 button mode.

Which mode the adapter is currently in, is represented by the onboard LED.

| LED on | LED off |
|--|--|
| 6-button mode | 2-button mode |

# File structure
- Gerber files can be found in the Gerber directory
- BOMs can be found in the BOM directory
- Hex files for flashing the Atmega328p can be found in the Hex directory
- Project source can be found in the GENESIS2PCE directory

# Images
![PCB](https://github.com/Infinest/GENESIS2PCE/blob/master/Images/boardv3.jpg)

![PHOTO](https://github.com/Infinest/GENESIS2PCE/blob/master/Images/boardv3_real.jpg)

# Mapping
| PC Engine | Sega Genesis 3 button | Sega Genesis 6 button|
|--|--|--|
| Up | Up | Up |
| Down| Down | Down |
| Left| Left | Left |
| Right| Right | Right |
| Select | Start / A | Start / Mode|
| Run | A / Start | Mode / Start |
| I | C | C |
| II | B | B |
| III |--| A |
| IV |--| X |
| V |--| Y |
| VI |--| Z |

The button assignments for Select and Run can be swapped. To do this, simply hold A, B, C & Start on your  connected Genesis controller for 8 seconds. This configuration will be retained through power cycles.

# Flashing the Atmega328p

The hex files for flashing the Atmega328p are available inside the Hex directory.
The Atmega328p's fuse bytes should be set to the following values:
| Fuse Byte | Value |
|--|--|
|Fuse Low Byte| 0xDF |
|Fuse High Byte| 0xFE |
|Extended Fuse Byte| 0xFC |

# References
Very helpful information on how to read Genesis controllers was gathered from these sources:
* https://github.com/jonthysell/SegaController
* https://segaretro.org/Six_Button_Control_Pad_(Mega_Drive)#Technical_information 
