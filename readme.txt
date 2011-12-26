emonGLCD open-source wireless graphical display using alternative displays
***************************************************************************

Now converted for Arduino 1.0

This builds on the OpenEnergyMonitor.org emonGLCD design using alternative graphical displays and adds receive of a remote
temperature sensor and transmit of a locally connected DS18B20 one wire temperature sensor.

Four versions are available including two with touchscreen support.

All the required libraries are linked to in code comments.

Details of a simple remote temperature sensor node can be found here: http://zorg.org/j58

emonGLCD_KS0108
----------------------
This version uses the KS0108 parallel display. Details of my build using this screen can be found on my blog at
http://zorg.org/yeg
The additional fonts used are available in this repository as Impact.h and Switzerland.h

emonGLCD_LCD_09351
------------------
This version uses the SparkFun LCD-09351 which is a KS0108 type display with an ATmega 168 based serial backpack attached.
NB: This will not work with the default firmware that the LCD-09351 ships with. The default firmware is poor so I have flashed
the backpack with the alternative firmware made by summoningdark which can be found here:
https://sourceforge.net/projects/serialglcd/
More info on this screen can be found on by blog at http://zorg.org/u9f
Read serialGLCD_Library_Notes.txt for converting the serialGLCD library for Arduino 1.0

emonGLCD_LCD_09351_Touch
------------------------
This version uses the same SparkFun LCD-09351 as above and a Nintendo DS touchscreen has been added to provide a way to 
change the display. A couple of alternative layouts of the power and temperatures and a menu to control the backlight 
have been created as a demonstration.
More info on this screen and the use of the Nintendo DS touchscreen can be found on by blog at http://zorg.org/u9f
Read serialGLCD_Library_Notes.txt for converting the serialGLCD library for Arduino 1.0

emonGLCD_ST7565_RGB_Touch
-------------------------
This version uses the ST7565 based LCD with RGB backlight from Adafruit and the Nintendo DS touchscreen. Inludes 3 different
views and changing backlight colour depending on power usage. Details of my build using this screen can be found on my
blog at http://zorg.org/60x
