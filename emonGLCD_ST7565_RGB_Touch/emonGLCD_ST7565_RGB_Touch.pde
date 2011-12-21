//------------------------------------------------------------------------------------------------------------------------
// Touchscreen GLCD Energy Monitor Display using Adafruit RGB ST7565 128x64 GLCD and Nintendo DS touchscreen
// By Nathan Chantrell. http://zorg.org/
// Builds on emonGLCD example by Trystan Lea and Glyn Hudson at OpenEnergyMonitor.org
//
// Features:
//  Touch control using Nintendo DS touchscreen
//  3 Different display views selectable via touchscreen
//  Receive power reading from emonTX via RF
//  Receive remote temperature reading via RF
//  Read room temperature from DS18B20 sensor
//  Transmit room temperature reading via RF
//  Backlight colour changes depending on power reading
//  Supports MCP79410 RTC for time & date display
//------------------------------------------------------------------------------------------------------------------------

#include <OneWire.h> // http://www.pjrc.com/teensy/arduino_libraries/OneWire.zip
#include <DallasTemperature.h> // http://download.milesburton.com/Arduino/MaximTemperature/DallasTemperature_371Beta.zip
#include <Ports.h> // https://github.com/jcw/jeelib
#include <RF12.h> // https://github.com/jcw/jeelib
#include <Wire.h> // Wire library required for I2C for MCP79410 http://www.arduino.cc/en/Reference/Wire
#include <GLCD_ST7565.h> // https://github.com/jcw/glcdlib
#include "utility/font_clR4x6.h" // tiny font
#include "utility/font_clR6x6.h" // small font
#include "utility/font_clR6x8.h" // large font
#include "utility/font_helvB14.h" // huge font

// Fixed RF12 settings
#define MYNODE 27            //node ID, 30 is reserved for base station
#define freq RF12_433MHZ     //frequency
#define group 210            //network group 
#define emonTxNode 10        //node ID of the emonTX
#define tempTxNode 11        //node ID of the tempTX

// DS18B20 Temperature sensor on pin D4
#define ONE_WIRE_BUS 4      

// Backlight auto colour mode
#define greenLevel 700 // Watts below which backlight is green, above this it moves towards blue
#define blueLevel 1200 // Watts at which backlight starts to move from blue towards red
#define redLevel 1800 // Watts above which backlight is red

// RGB Backlight pins - Need to be on 3,5,6 or 9 for PWM control
#define redPin   5   // Red cathode
#define greenPin 6  // Green cathode
#define bluePin  9  // Blue cathode

// Backlight variables for PWM
int redLEDValue = 255;
int greenLEDValue = 1;
int blueLEDValue = 1;

// Backlight state
int backLightMode = 1; // 1=auto, 2=default,fixed at above values
int backLightOn = 1; // backlight always on at startup

// Touchscreen
int x,y = 0;
int TouchState = 0;
int TouchStateLast;
#define xLow  14 // X1 connected to analogue 0
#define xHigh 16 // X2 connected to analogue 2
#define yLow  17 // Y1 connected to analogue 3
#define yHigh 15 // Y2 connected to analogue 1

//GLCD
GLCD_ST7565 glcd; 

//########################################################################################################################
//Data Structure to be received 
//########################################################################################################################

typedef struct {
  	  int ct;		// current transformer
	  int supplyV;		// emontx voltage
	} Payload;
	Payload emontx;

int emontx_nodeID;    //node ID of emon tx, extracted from RF datapacket. Not transmitted as part of structure

//########################################################################################################################
//Data Structure to be sent
//########################################################################################################################

typedef struct {
  	  int temp;		// internal temp sensor
	  int supplyV;		// emonGLCD voltage
	} PayloadOut;
	PayloadOut temptx;

//########################################################################################################################

//variables
unsigned long last; // last update from rf
unsigned long lastTemp; // last local temp reading
unsigned long lastTx; // last local temp transmission

double temp; // local temp
double temp1; // remote temp
double cval; // ct reading from emonTX
double cval2; // scrolling value for power display

char str[50]; // general char array

//DS18B20
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup () {
  
 Wire.begin(); // Initiate the Wire library so we can communicate with I2C devices (eg. MCP79410 RTC)

// Temporary method to manually set the time on the MCP79410
// need to find better way to do this
/*
  WriteRTCByte(0,0);       //STOP RTC
  WriteRTCByte(1,0x58);    //MINUTE
  WriteRTCByte(2,0x12);    //HOUR
  WriteRTCByte(3,0x03);    //DAY=1(MONDAY) AND VBAT=1
  WriteRTCByte(4,0x21);    //DATE
  WriteRTCByte(5,0x12);    //MONTH
  WriteRTCByte(6,0x11);    //YEAR
  WriteRTCByte(0,0x80);    //START RTC, SECOND=00
  delay(100);
*/

 rf12_initialize(MYNODE, freq,group); // Initialise the RFM12B

 last = millis();
    
 sensors.begin(); //start up temp sensor
 
 //get inital temperature reading
 sensors.requestTemperatures();
 temp=(sensors.getTempCByIndex(0));

 // Set the backlight pins as outputs
 pinMode(redPin, OUTPUT);   
 pinMode(greenPin, OUTPUT);
 pinMode(bluePin, OUTPUT);
       
 // Set backlight at default values
 analogWrite(redPin,   redLEDValue); 
 analogWrite(greenPin, greenLEDValue);
 analogWrite(bluePin,  blueLEDValue);

 glcd.begin(); // initialise the display
 
 menuOne(); // Show main menu on initial power up

}

// Nintendo DS Touchscreen stuff
 int readX() // returns the value of the touch screen's X-axis
{
  pinMode(xLow,OUTPUT);
  pinMode(xHigh,OUTPUT);
  digitalWrite(xLow,LOW);
  digitalWrite(xHigh,HIGH);
  digitalWrite(yLow,LOW);
  digitalWrite(yHigh,LOW);
  pinMode(yLow,INPUT);
  pinMode(yHigh,INPUT);
  delay(10);
  x=analogRead(yLow);
}

 int readY() // returns the value of the touch screen's Y-axis
{
  pinMode(yLow,OUTPUT);
  pinMode(yHigh,OUTPUT);
  digitalWrite(yLow,LOW);
  digitalWrite(yHigh,HIGH);
  digitalWrite(xLow,LOW);
  digitalWrite(xHigh,LOW);
  pinMode(xLow,INPUT);
  pinMode(xHigh,INPUT);
  delay(10);
  int y=analogRead(xLow);
}

void loop() {

 if (TouchState != TouchStateLast) { // screen was touched
  if (backLightOn == 0) { // if screen is touched and backlight is off turn it back on
   backLightOn = 1; 
  } 
  delay(500);  // delay to prevent bouncing on touch
 }

 // get values from touch screen
 x=readX();
 y=readY();
 
 TouchStateLast = TouchState; //reset touch state
 
// now determine where the touch was located on the screen
// values are based on touchscreen aligned with bottom of ST7565 screen
 if (x>100 && y>100) { 
  if (TouchState == 0) { // we're in the main menu
    if (y>510 && x<490) {
     TouchState = 1; // top left
    } else
    if (y>510 && x>490) {
     TouchState = 2; // top right
    } else
    if (y<500 && x<490) {
     TouchState = 3; // bottom left
    } else
    if (y<500 && x>490) {
     TouchState = 4; // bottom right
    } 
  } else  
   if (TouchState == 4) { // we're in the backlight menu
    if (y>510 && x<490) {
     backLightMode = 1; // turn auto backlight colour changing on
    } else
    if (y>510 && x>490) { 
     backLightOn = 0; // turn backlight off completely
    } else
    if (y<500 && x<490) {
     backLightMode = 2; // turn auto backlight colour changing off, switch to default
    } else
    if (y<500 && x>490) {
     TouchState = 0; // return to main menu
   }

  } else // we're on a display screen, detect touch anywhere and go to main menu
   if (x<900 || y<900) {
     TouchState = 0;
  }
 }
 

// What to do when touched
  if (TouchState == 0) {
     menuOne(); // go to main menu
  } else 
  if (TouchState == 1) {
     viewOne();
  } else 
  if (TouchState == 2) {
     viewTwo();
  } else 
  if (TouchState == 3) {
     viewThree();
  } else
  if (TouchState == 4) {
     menuTwo(); // go to other menu
  }

 getReadings(); // get data from RFM12 and temp sensor
 
 glcd.refresh(); // update display
 glcd.clear();
 
 //Backlight mode
  if (backLightMode == 1 && cval != NULL && TouchState != 0 && TouchState != 4) { 
    autoBacklight(); // Change backlight colour automatically
  } else 
  if (backLightOn == 0) {  // turn backlight off
    analogWrite(redPin, 255);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 255);
  } else {
    menuBacklight(); // otherwise use menu backlight setting
  }

} // end loop


//########################################################################################################################
// Menu screens
//########################################################################################################################

  void menuOne(){ // draw the main menu
  glcd.setFont(font_clR6x8); //use large font
  
  glcd.drawRect(0,0,62,30,BLACK);
  glcd.drawString(10,12,"View 1");
 
  glcd.drawRect(66,0,62,30,BLACK);
  glcd.drawString(78,12,"View 2");
  
  glcd.drawRect(0,34,62,30,BLACK);
  glcd.drawString(10,46,"View 3");
  
  glcd.drawRect(66,34,62,30,BLACK);
  glcd.drawString(72,42,"Settings");
  glcd.drawString(83,50,"Menu");

  }
  
  void menuTwo(){ // draw the settings menu
  glcd.setFont(font_clR6x8); //use large font
  
  glcd.drawRect(0,0,62,30,BLACK);
  glcd.drawString(17,8,"Auto");
  glcd.drawString(12,16,"Colour");
 
  glcd.drawRect(66,0,62,30,BLACK);
  glcd.drawString(70,8,"Backlight");
  glcd.drawString(88,16,"Off");
  
  glcd.drawRect(0,34,62,30,BLACK);
  glcd.drawString(14,42,"Fixed");
  glcd.drawString(12,50,"Colour");
  
  glcd.drawRect(66,34,62,30,BLACK);
  glcd.drawString(83,42,"Main");
  glcd.drawString(83,50,"Menu");

  }

//########################################################################################################################
// Display Screens
//########################################################################################################################

  void viewOne(){ // large power & temp readings

   //print power value on GLCD          
    glcd.setFont(font_helvB14); //use huge font
    glcd.drawString(0,0,"Power:");
    cval2 = cval2 + (cval - cval2)*0.20; //smooth scroll of power reading
    itoa((int)cval2,str,10);
    strcat(str,"W");
    glcd.drawString(67,00,str);
    
   //print room temperature on GLCD 
    glcd.setFont(font_clR6x6); //use small font
    glcd.drawString(15,30, "Room");
    dtostrf(temp,0,1,str); 
    strcat(str,"C");
    glcd.setFont(font_helvB14); //use huge font
    glcd.drawString(5,37,str);
        
   //print outside temperature on GLCD 
    glcd.setFont(font_clR6x6); //use small font
    glcd.drawString(72,30, "Outside");
    dtostrf(temp1/100,0,1,str);
    strcat(str,"C");
    glcd.setFont(font_helvB14); //use huge font
    glcd.drawString(72,37,str);

   // display time
    glcd.setFont(font_clR6x6); //use small font
    (rtcTime()).toCharArray(str, 50);
    glcd.drawString(2,57,str);

   //last updated
    glcd.setFont(font_clR4x6); //select tiny font   
    glcd.drawString(64,57, "Updated: ");
    int seconds = (int)((millis()-last)/1000.0);
    itoa(seconds,str,10);
    strcat(str,"s ago");
    glcd.drawString(98,57,str);
   
   //draw power bar   
    glcd.drawRect(0, 20, 127, 7, BLACK);
    glcd.fillRect(0, 20, (cval*0.042), 7, BLACK); //bar fully black at 3Kw
      
  }

  void viewTwo(){ // large time and power readings
          
   // display time & date
   glcd.setFont(font_helvB14); //use huge font
   (rtcTime()).toCharArray(str, 50);
   glcd.drawString(2,0,str);
   glcd.setFont(font_clR6x8); //use large font
   (rtcDate()).toCharArray(str, 50);
   glcd.drawString(74,6,str);

   //print power value on GLCD  
    glcd.setFont(font_helvB14); //use huge font
    glcd.drawString(2,18,"Power:");
    cval2 = cval2 + (cval - cval2)*0.20; //smooth scroll of power reading
    itoa((int)cval2,str,10);
    strcat(str,"W");
    glcd.drawString(67,18,str);
    
   //print room temperature on GLCD 
    glcd.drawRect(0,36,62,28,BLACK); 
    glcd.drawLine(0,48,61,48,BLACK);
    glcd.setFont(font_clR6x8); //use large font
    glcd.drawString(18,39, "Room");
    dtostrf(temp,0,1,str); 
    strcat(str," C");
    glcd.drawString(16,52,str);
    
   //print outside temperature on GLCD 
    glcd.drawRect(66,36,62,28,BLACK);//29
    glcd.drawLine(66,48,127,48,BLACK);
    glcd.setFont(font_clR6x8); //use large font
    glcd.drawString(76,39, "Outside");
    dtostrf(temp1/100,0,1,str);
    strcat(str,"C");
    glcd.drawString(82,52,str);
   
  }

  void viewThree(){ // based on original OEM view
    
   glcd.setFont(font_clR6x8); //use large font
   glcd.drawString(0,0,"OpenEnergyMonitor");
    
   //print power value on GLCD   
    glcd.drawString(0,18,"Power:");
    cval2 = cval2 + (cval - cval2)*0.20; //smooth scroll of power reading
    itoa((int)cval2,str,10);
    strcat(str,"W");
    glcd.setFont(font_helvB14); //use huge font
    glcd.drawString(40,11,str);
    
   //print room temperature on GLCD 
    glcd.setFont(font_clR6x6); //use small font
    glcd.drawString(0,40, "Room Temp: ");
    dtostrf(temp,0,1,str); 
    strcat(str,"C");
    glcd.drawString(60,40,str);

   //print outside temperature on GLCD     
    glcd.setFont(font_clR6x6); //use small font
    glcd.drawString(0,48, "Outside Temp: ");
    dtostrf(temp1/100,0,1,str);
    strcat(str,"C");
    glcd.drawString(78,48,str);
    
   // display time
    glcd.setFont(font_clR6x6); //use small font
    (rtcTime()).toCharArray(str, 50);
    glcd.drawString(0,57,str);

   //last updated
    glcd.setFont(font_clR4x6); //select tiny font   
    glcd.drawString(64,57, "Updated: ");
    int seconds = (int)((millis()-last)/1000.0);
    itoa(seconds,str,10);
    strcat(str,"s ago");
    glcd.drawString(98,57,str);
    
   //draw power bar
    glcd.drawRect(0, 29, 127, 7, BLACK);
    glcd.fillRect(0, 29, (cval*0.042), 7, BLACK); //bar fully black at 3Kw
 
  }

 void getReadings(){
 //--------------------------------------------------------------------
 // 1) Receive data from RFM12
 //--------------------------------------------------------------------
    if (rf12_recvDone() && rf12_crc == 0 && (rf12_hdr & RF12_HDR_CTL) == 0) {
        emontx=*(Payload*) rf12_data;   
        emontx_nodeID = rf12_hdr & 0x1F;  // get node ID
        last = millis();
    }

 //--------------------------------------------------------------------------------------------------
 // 2) Which node did it come from?
 //--------------------------------------------------------------------------------------------------   
      if (emontx_nodeID == emonTxNode){ // if node is emonTX
        cval = emontx.ct;
      } else     
      if (emontx_nodeID == tempTxNode){   // If node is TempTx
        temp1 = emontx.ct;
      }   
  
 //--------------------------------------------------------------------
 // 3) get data from temp sensor every 10s
 //--------------------------------------------------------------------
    if (millis()>lastTemp+10000){
     sensors.requestTemperatures();
     temp=(sensors.getTempCByIndex(0));
     lastTemp=millis();
    }
    
 //--------------------------------------------------------------------------------------------------
 // 4) Send data via RF every 30s
 //--------------------------------------------------------------------------------------------------
     if (millis()>lastTx+30000) { 
      temptx.supplyV = readVcc(); 
      temptx.temp = temp * 100;
      rfwrite() ;
      lastTx=millis();
     }     
 }
  
 //--------------------------------------------------------------------------------------------------
 // Send payload data via RF
 //--------------------------------------------------------------------------------------------------
    static void rfwrite(){
     while (!rf12_canSend())
     rf12_recvDone();
     rf12_sendStart(0, &temptx, sizeof temptx); 
     rf12_sendWait(2);    //wait for RF to finish sending while in standby mode
    }

 //--------------------------------------------------------------------------------------------------
 // Read current supply voltage
 //--------------------------------------------------------------------------------------------------
    long readVcc() {
    long result;
     // Read 1.1V reference against AVcc
     ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
     delay(2); // Wait for Vref to settle
     ADCSRA |= _BV(ADSC); // Convert
     while (bit_is_set(ADCSRA,ADSC));
     result = ADCL;
     result |= ADCH<<8;
     result = 1126400L / result; // Back-calculate AVcc in mV
     return result;
    }

 //--------------------------------------------------------------------------------------------------
 // Change backlight according to power reading
 //--------------------------------------------------------------------------------------------------
    void autoBacklight() {
     if (cval2 <= greenLevel) { // Less than green level stay green
      redLEDValue = 255;
      greenLEDValue = 1;
      blueLEDValue = 255;
     } else
     if (cval2 <= blueLevel) { // Less than blue level move from green towards blue
      redLEDValue = 255;
      greenLEDValue = ((cval2-greenLevel)*(255/(blueLevel-greenLevel))); 
      blueLEDValue = (256-(cval2-greenLevel)*(255/(blueLevel-greenLevel))); 
     } else 
     if (cval2 <= redLevel) { // Less than red move from blue towards red
      redLEDValue = (256-(cval2-blueLevel)*(255/(redLevel-blueLevel)));
      greenLEDValue = 255;
      blueLEDValue = ((cval2-blueLevel)*(255/(redLevel-blueLevel)));
     } else {
      redLEDValue = 1; // Otherwise red
      greenLEDValue = 255;
      blueLEDValue = 255;
     } 
     analogWrite(redPin,   redLEDValue);   // Write current values to backlight
     analogWrite(greenPin, greenLEDValue);
     analogWrite(bluePin,  blueLEDValue);
    }

 //--------------------------------------------------------------------------------------------------
 // Backlight setting for menus
 //--------------------------------------------------------------------------------------------------
    void menuBacklight() {
     analogWrite(redPin, 255);
     analogWrite(greenPin, 1);
     analogWrite(bluePin, 1);
    }

 //--------------------------------------------------------------------------------------------------
 // MCP79410 RTC
 //--------------------------------------------------------------------------------------------------
   
 // Called to read bytes from RTC
  unsigned char ReadRTCByte(const unsigned char adr){
   unsigned char data;
   Wire.beginTransmission(0x6f);
   Wire.send(adr);
   Wire.endTransmission();
   Wire.requestFrom(0x6f,1);
   while (Wire.available()) data=Wire.receive();
   return data;
  }

 // Called to write bytes to RTC
  void WriteRTCByte(const unsigned char adr, const unsigned char data){
   Wire.beginTransmission(0x6f);
   Wire.send(adr);
   Wire.send(data);
   Wire.endTransmission();
  } 

 // Return the time from RTC as a string in format hh:mm:ss
  String rtcTime() { 
   unsigned char data;
   data=ReadRTCByte(2); // get hours from rtc
   int hour=data & 0xff>>(2);
   data=ReadRTCByte(1); // get minutes from rtc
   int minute=data & 0xff>>(1);
   data=ReadRTCByte(0); // get seconds from rtc
   int second=data & 0xff>>(1);
  //build time string
   String rtcTime;
   if (hour < 10){rtcTime += "0";} // fudge to add leading zero
   rtcTime += String(hour,HEX);
   rtcTime += ":";  
   if (minute < 10){rtcTime += "0";} // fudge to add leading zero
   rtcTime += String(minute,HEX);  
   rtcTime += ":";  
   if (second < 10){rtcTime += "0";} // fudge to add leading zero
   rtcTime += String(second,HEX);
   return rtcTime;  
  }

 // Return the date from RTC as a string in format dd:mm:yy
  String rtcDate() { 
   unsigned char data;
   data=ReadRTCByte(4); // get day from rtc
   int day=data & 0xff>>(2);
   data=ReadRTCByte(5); // get month from rtc
   int month=data & 0xff>>(3);
   data=ReadRTCByte(6); // get year from rtc
   int year=data & 0xff>>(0);
  //build date string
   String rtcDate;
   rtcDate += String(day,HEX);
   rtcDate += "/";  
   rtcDate += String(month,HEX);  
   rtcDate += "/";  
   rtcDate += String(year,HEX);
   return rtcDate;  
  }
