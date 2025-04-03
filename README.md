# Clock16
This project presents digital 24 hours clock.  While having only sixteen LEDs it shows time with 15 seconds precision.

![CLOCK](./images/IMKP5093_acr.jpg)

## How to Read the Time. WEB Model
Here is web model. It help understand this clock principle. There are four clock. They all synchronized and show the same time.
1. First dial at the left is regular analogous clock. Nothing to comment here.
2. Second dial works similarly to the first. But instead of clock hands here are arches. While in regular clock time is shown by  angle between hands  vertical axis this dial shows time by angle occupied by arches (outer arch for minutes, inner arch for hours ).
3. Third picture  is half-dial. For hours less than 6 and minutes less than 30  reading the time is not different of the second clock. But when hours are in the range 6..12 and minutes in the range 30..60 there is the change. Hours hand of the regular clock is positioned in the left side of dial. But there is no left side of the dial for this arch clock. So direction oof arch grows changes. Now it starts not at 12 mark but at 6 mark. That way you can show hours from 6 to 11 and minutes from 30 to 60.
4. Fourth  clock is similar to third but arches instead of solid become dotted. Meaning of each hour dot  (when white) is similar to the meaning of hours mark for a regular clock.   Meaning of each minute dot (when green) is similar to a meaning of five minute mark for a regular clock. One minute precision provided by a color of the last dot of minute arch. There is need to add color reading to reading provided by green dots (for cyan it is +1, for purple it is +2, for red it is +3, and for blue it is +4 ).  

![MODEL](./images/simulation.jpg) 
Model allows to play with clocks dynamically. Three modes exist:
1. Manual mode. Set the clock time by moving top slider.
2. Real time mode. CLock shows current local time on the machine where browser is running.
3. Simulated mode. Running of time is simulated. Simulation speed is controlled by bottom slider.

To activate the model after cloning the git repository go to directory p5model and open index.html file with browser of your choice. Alternative way would be to click on the link:

[web-model](https://filedn.com/lRLB6A8XqsC4voY39bLNwCj/Clock16/)

## Components and Circute
Here is list of project components.

1. Atmega328p Michrochip processor
2. Five 10mm tri-color  common cathod LEDs
3. Three 10mm tri0color common anod LEDs
4. Seven 10mm white LEDs
5. 5mm white LED
6. Sixteen 75 Ohm/0.125 W  resistors
9. Eleven silicon diods 1N4148
10. Shotkey diod 1N5817
11. Three  micro buttons
12. Super Capacitor 0.5 MF 5.5 V
13. Power down supply LM2596
14. Crystal 32768 KHZ
15. Optopair NTE3042
16. Resistor 220 Ohm/ 0.125 W

![CIRCUTE](./images/clock.jpg) 

## Program


