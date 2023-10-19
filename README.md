Note: This repository is still in progress.

The Open Saddle Vibrator is a sit-on vibrator that can be made at home with a 3D printer and some basic hand tools. The project is primarily made from timber, 3D printed parts and some metal angle iron.

Dome has an 7 ply ply-wood arch frames to keep its shape and is covered in 2 lays of 3 ply ply-wood with layers of thin rubber, foam and leather. It is also covered internally with a sound dampening material.

Base is 12mm ply wood to which the internal framework is bolted.

Sides are also 12mm plywood, covered in leather for aesthetics and have eyebolts mounted in the lower corners, handles and the IO and power connectors mounted.

The 3D framework is a strong square frame design connected parallel bars. On top of of the parallel bars is mounted 2 x M8 pillow block bearings holding a M8 steel shaft, which is pushed through an offset 3D printed shaft, this shaft is mounted to a pare of M12 pillow block bearings mounted to one end of the vibration plate. The other end of the of the vibration plate is connected to the parallel bars, via a 3D printed bride and a 20mm rubber dampener.

The electronics are relatively simple. An Arduino Uno acts as the mainboard, and an Arduino Nano acts as the controller.

The Uno as the mainboard controls the 2 ESCs controlling the rotation motor (55RPM 12V geared) and the vibration motor (100W 2750RPM straight motor).

The Nano in the controller has 2 pots to control the speed of the motor controllers and 2 buttons for the instant 100% pulse mode and the other for a slow ramping mode. The Arduinos communicate via serial using Serial.print() Arduino fuction with a very straight forward protocol (hoping to get it to use the buttplug.io system in the future).
