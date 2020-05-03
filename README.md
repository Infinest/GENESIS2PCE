# Genesis2PCE

This adapter PCB allows connecting Genesis 3 or 6 button controllers to your PC Engine.
It consists of all the components a real PC Engine 6 button controller has inside of it + an Atmega328p for interfacing with Genesis controllers.

When connecting a Genesis 6 button controller without holding the Mode button, the adapter will go into 6 button mode. This means you can use it as an actual 6 button PC Engine adapter for the handful of games that support it (Street Fighter 2, Art of Fighting, Fatal Fury 2 etc.).
To ensure compatiblity with other games and the Sega Genesis 6 button controller, one should hold the Mode button while powering on the adapter to put the controller into 3 button mode and the adapter into 2 button mode.
Sega Genesis 3 button controllers will always put the adapter into 2 button mode.

## Please note:

**The PCB for the adapter is not yet final. Gerbers will be added to the repository at a later point in time**

# Mapping
| PC Engine | Sega Genesis 3 button | Sega Genesis 6 button|
|--|--|--|
| Up | Up | Up |
| Down| Down | Down |
| Left| Left | Left |
| Right| Right | Right |
| Select | Start | Start|
| Run | A | Mode |
| I | C | C |
| II | B | B |
| III |--| A |
| IV |--| X |
| V |--| Y |
| VI |--| Z |

# References
Very helpful information on how to read Genesis Pads was gathered from these sources:
* https://github.com/jonthysell/SegaController
* https://segaretro.org/Six_Button_Control_Pad_(Mega_Drive)#Technical_information 