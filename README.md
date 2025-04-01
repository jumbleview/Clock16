# Clock16
This project presents digital 24 hours clock.  While having only sixteen LEDs it shows time with 15 seconds precision.

![CLOCK](./images/IMKP5093_acr.jpg)

## How to Read the Time. WEB Model
Here is web model. It help understand this clock principle. There are four clock. They all synchronized and show the same time.
1. First dial at the left is regular analogous clock. Nothing to comment here.
2. Second dial works similarly to the first. But instead of clock hands here are arches. While in regular clock time is shown by  angle between hands  vertical axis this dial shows time by angle occupied by arches (outer arch for minutes, inner arch for hours ).
3. Third picture  is half-dial. For hours less than 6 and minutes less than 30  reading the time is not different of the second clock. But when hours are in the range 6..12 and minutes in the range 30..60 there is the change. Hours hand of the regular clock is positioned in the left side of dial. But there is no left side of the dial for this arch clock. So direction oof arch grows changes. Now it starts not at 12 mark but at 6 mark. That way you can show hours from 6 to 11 and minutes from 30 to 60.
4. Fourth  clock is similar to third but arches instead of solid become dotted. Meaning of each hour dot  (when white) is similar to meaning of hours mark for regular clock.   Meaning of each minute dot (when green) is similar to meaning of five minute mark for regular clock. To show time with one minute precision there is take into consideration color of the last dot of minute arch it shows how many minutes there is need to add to reading provided bu green dots (for cyan is +1, for purple is +2, for red is +3, and for blue is +4 ).  
Model allows to play with clocks dynamically. 
![MODEL](./images/simulation.jpg) 
[web-model](https://filedn.com/lRLB6A8XqsC4voY39bLNwCj/Clock16/)

## Components and Circute
Here is list of project components.

1. Atmega328p Michrochip processor
2. Five 10mm tri-color  common cathod LEDs
3. Three 10mm tri0color common anod LEDs
4. Seven 10mm white LEDs
5. 5mm white LED
6. Sixteen 75 Ohm/0.125 W  resistors
9. Eleven silicon diods 
10. Shotkey diod
11. Three  micro buttons
12. Super Capacitor 0.5 MF 5.5 V
13. Power down supply



![CIRCUTE](./images/clock.jpg) 

## Program


