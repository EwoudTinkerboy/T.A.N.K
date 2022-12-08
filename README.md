<h1 align="center">the T.A.N.K.</h1>
<div align="center">
<br>
</div>

## Table of contents
* [General info](#general-info)
* [Video](#video)
* [Technologies](#technologies)
* [Characteristics](#characteristics)
* [Components](#components)
* [Wiring](#wiring)
* [Installation instructions](#installation-instructions)

## General info
The T.A.N.K. is a tracked multipurpose [Ripsaw](https://en.wikipedia.org/wiki/Ripsaw_(vehicle)) like carrier:
- on Lego Technic chassis,
- with light weight,
- and high ground clearance.

featuring:
- flexible and robust [torsion bar suspension](https://www.tanknology.co.uk/post/primer-torsion-bar-suspension) as used on German tanks,
- RC control,
- RC telemetry,
- FPV camera (work in progress),
- AI (work in progress).
	
## Video

[![Watch the video](https://github.com/EwoudTinkerboy/T.A.N.K/blob/main/the_tank.jpeg)](https://www.youtube.com/watch?v=WVPMDnqwUC0&t=7s)

## Technologies
Project is created with:
* Arduino IDE: version 1.8.15,
* Arduino library: S.Port sensor library for FrSky version 1.0.3,
* OpenTX COMPANION: version 2.3.15,

## Characteristics
- dimensions: ? mm x ? mm x ? mm,
- weight: ? g.

## Components
- [Arduino Uno Rev3](https://store.arduino.cc/products/arduino-uno-rev3),
- [Arduino Motorshield Rev3](https://store.arduino.cc/products/arduino-motor-shield-rev3),
- [6 VDC Dual axis gear motor](https://www.aliexpress.com/item/4000021146641.html?),
- [FrSky transmitter e.g. QX7](https://www.frsky-rc.com/product/taranis-q-x7-2/),
- [FrSky receiver e.g. XR8](https://www.frsky-rc.com/x8r/),
- [LiPo battery](https://www.frsky-rc.com/x8r/),
- [BUC converter](https://),
- [Raspberry Pi 4 Model B (work in progress)](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/),
	
## Wiring
[![the_tank.fzz](https://github.com/EwoudTinkerboy/T.A.N.K/blob/main/the_tank.jpeg)](https://github.com/PVanhevel/test/blob/main/the_tank.fzz)

## Installation instructions
1. Arduino: upload the_tank.ino sketch from GitHub onto the Arduino Uno,
2. OpenTX: import the the_tank.otx model & settings from GitHub into your up-to-date OpenTX Companion,
3. OpenTX: 'Write Model and Settings to Radio',
4. Test
5. Optional: convert the raw analogRead values into readable motor currents and e.g. battery voltages by applying ratios in the .ino sketch.
   (use voltage dividers!)
