# Eva's neck engine control app

App for the Arbotix-M Robocontroller to control the servo engines of Eva's neck.

## Dynamixel IDs
In order to Arbotix-M properly recognize the Dynamixel Servos, it is necessary to add an ID to them. You can find a step-by-step guide [here](https://learn.trossenrobotics.com/arbotix/1-using-the-tr-dynamixel-servo-tool#&panel1-1)

**Note:** The ID has to be `1` and `2`, being the `1` the one screwed to the engine support. 

## Uploading software to the Arbotix-M Robocontroller

To upload the NeckApp solution to the Arbotix-M PCB and follow the general steps:
- Download and Install the Arduino IDE 1.0.6 from [here](https://www.arduino.cc/en/Main/OldSoftwareReleases)
- Install the FTDI drivers, you can find them [here](http://www.ftdichip.com/Drivers/VCP.htm), and a guide to installing them [here](http://www.ftdichip.com/Support/Documents/InstallGuides.htm)
- Download the ArbotiX-M Hardware and Library Files from [here](https://github.com/trossenrobotics/arbotix/archive/master.zip), and add them into the Arduino user folder.
- Connect the Arbotix-M Robocontroller to your Computer
- Load the NeckApp proyect into the Arduino IDE and upload it.

You can find a step by step guide [here](https://learn.trossenrobotics.com/arbotix/7-arbotix-quick-start-guide)

## Head movements
Commands:
- n: nod
- s: shake
- c: center
- r: right
- l: left
- u: up
- d: down
- e: up and right
- q: up and left
- x: down and right
- z: down and left
- h: list of commands

**Note:** all commands except `c` can be used in `uppercase`, with the use of this format the movements become wider.
