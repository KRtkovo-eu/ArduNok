# ArduNok
Open source firmware for Arduino that mimics Nokia DCT-3 phones UI (such as 5110, 3310 etc.). Enjoy the taste of the age when mobile phones were amazing devices!

![proof-of-concept](https://raw.githubusercontent.com/KRtkovo-eu/ArduNok/master/Pictures/misc/proof-of-concept.jpg)            
Youtube presentation: https://www.youtube.com/watch?v=msxXc8mSOrg

## Current development
- FW model: PSB-1
- FW version: v00.02
- Development phase: proof-of-concept
- Author: KRtek.tm (Ondřej Kotas)
- License: GNU GPL v3

## What is this project?
I have passion for retro things which I know from my childhood. Nokia phones with snake game, its iconic ringtones, menu and usability were legendary.       
Those which I used I still have in my drawer. To buy such a device nowaday is more expensive with every day.        
And even if you have one, it's still a phone - so you need to insert a SIM card (can be disused) and then you can play games, melodies, use picture editor and ringtone composer, use calendar, notes and that's probably all. Yes, you still can play multiplayer snake over IrDA port with friend having the same phone, but WAP over GSM calls doesn't work anymore, maybe GSM is already turned off in your country, so the connectivity options and other features of those devices are now (2022) fairly limited.        
So that's why this project was created. I want to create open source firmware for Arduino which mimics iconic Nokia UI, can be modified, features of your own choice can be selected or which you can simply rebuild and use for your own purposes.

## HW requirements
- Arduino MEGA 2560 (This version of firmware is optimized only for MEGA 2560 due to the memory and flash memory requirements. If you need smaller board, there is MEGA 2560 embedded version.)
- Nokia display (84*48 pixels, monochrome)
- 4 buttons (4x4 keyboard in future)
- piezo buzzer (or speaker however it will act as buzzer)
- optionally SPACE 2560 shield (IN FUTURE, not available now)

## Features
After the proof-of-concept phase, which is more or less hardcoded, uses a lot of memory and has very hard procedure to add any feature, I want to prepare core architecture of the firmware (as was the firmware of Nokia).     
It should be simple to add/remove/edit menu entries, applications and features so you can grab the firmware and make your own custom version for your devices.      
In this repository, the master version is called PSB-1 and will include all features available for future SPACE 2560 device:
- Serial line monitor
- Clock (without RTC)
- Multimeter (internal voltage and measurements over analog pins)
- RTTTL sounds, composer (known from Nokia, IN PROGRESS), sound settings, buzzer volume (IN PROGRESS, maybe available only as HW feature), vibrations (IN PROGRESS)
- 1-bit pictures, image editor (IN PROGRESS)
- Games: throw dice, (maybe some others as legendary snake etc, but games are not priority at the moment)
- Connectivity as IrDA, WiFi etc. (IN PROGRESS, not priority)
- NOT IMPLEMENTED NOW: Date, Calendar (recreation of the handy Nokia calendar, without tasks - just for days etc.), Alarm (1 for time), Units conversion, Calculator (priority for binary/decimal/hexadecimal conversion) and other features which can be useful in hobby workshop and other places I visits.