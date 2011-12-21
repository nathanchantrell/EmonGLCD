//------------------------------------------------------------------------------------------------------------------------
// Touchscreen GLCD Energy Monitor Display using Sparkfun LCD-09351 serial GLCD 128x64 and Nintendo DS touchscreen
// By Nathan Chantrell. http://zorg.org/
// Builds on emonGLCD example by Trystan Lea and Glyn Hudson at OpenEnergyMonitor.org
//
// Serial backpack is loaded with summoningdark's alternative firmware: https://sourceforge.net/projects/serialglcd/
// GLCD library is http://sourceforge.net/projects/serialglcdlib/
//
// Features:
//  Touch control using Nintendo DS touchscreen
//  3 Different display views selectable via touchscreen
//  Receive power reading from emonTX via RF
//  Receive remote temperature reading via RF
//  Read room temperature from DS18B20 sensor
//  Transmit room temperature reading via RF
//------------------------------------------------------------------------------------------------------------------------

#include <OneWire.h> // http://www.pjrc.com/teensy/arduino_libraries/OneWire.zip
#include <DallasTemperature.h> // http://download.milesburton.com/Arduino/MaximTemperature/DallasTemperature_371Beta.zip
#include <Ports.h> // https://github.com/jcw/jeelib
#include <RF12.h> // https://github.com/jcw/jeelib
#include <serialGLCD.h> // Include the serialGLCD library http://sourceforge.net/projects/serialglcdlib/

// Fixed RF12 settings
#define MYNODE 26            //node ID, 30 is reserved for base station
#define freq RF12_433MHZ     //frequency
#define group 210            //network group 
#define emonTxNode 10        //node ID of the emonTX
#define tempTxNode 11        //node ID of the tempTX

// DS18B20 Temperature sensor on pin D5
#define ONE_WIRE_BUS 5   

// Display
serialGLCD lcd; // initialise the display
int d = 200; // used for display delay
int backLight;

// Touchscreen
int x,y = 0;
int TouchState = 0;
int TouchStateLast;
#define xLow  14 // X1 connected to analogue 0
#define xHigh 16 // X2 connected to analogue 2
#define yLow  17 // Y1 connected to analogue 3
#define yHigh 15 // Y2 connected to analogue 1

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

void setup()
{
  
 rf12_initialize(MYNODE, freq,group); // Initialise the RFM12B

 last = millis();
    
 sensors.begin(); //start up temp sensor
 
 //get inital temperature reading
 sensors.requestTemperatures();
 temp=(sensors.getTempCByIndex(0));
 
 Serial.begin(115200); //default baudrate of the display, can be changed, consult summoningdark's README that comes with the firmware to change it
 delay(5000);

 lcd.backLight(100); // Backlight on full
 lcd.clearLCD(); // Clear screen
 delay(10); // Allow for a short delay after clearLCD since it takes some time for the backpack to clear the entire screen
  
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

void loop()
{
  
  if (TouchState != TouchStateLast) { // screen was touched
   delay(500);  // delay to prevent bouncing on touch
  }
    
  // get values from touch screen
  x=readX();
  y=readY();
 
  TouchStateLast = TouchState; //reset touch state

// now determine where the touch was located on the screen

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
    lcd.backLight(100); // turn backlight on full
   } else
   if (y>510 && x>490) {
    lcd.backLight(50); // set backlight to 50%
   } else
   if (y<500 && x<490) {
    lcd.backLight(0); // turn backlight off
    backLight=0;
   } else
   if (y<500 && x>490) {
    TouchState = 0; // return to main menu
   }

 } else // we're on a display screen, detect touch anywhere and go to main menu
  if (x<900 || y<900) {
    TouchState = 0;
 }
}

clearOnChange(); // clear screen if mode changed, turn backlight on if off

TouchStateLast = TouchState;

// What to do when touched
  if (TouchState == 0) {
     menuOne();
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

} // end loop

//########################################################################################################################
// Menu screens
//########################################################################################################################

  void menuOne(){ // draw the main menu

  lcd.drawBox(0,0,62,30,1);
  lcd.gotoPosition(10,12);
  Serial.print("View 1");
 
  lcd.drawBox(66,0,127,30,1);
  lcd.gotoPosition(78,12);
  Serial.print("View 2");
  
  lcd.drawBox(0,34,62,63,1);
  lcd.gotoPosition(10,46);
  Serial.print("View 3");
  
  lcd.drawBox(66,34,127,63,1);
  lcd.gotoPosition(70,39);
  Serial.print("Backlight");
  lcd.gotoPosition(77,52);
  Serial.print("Control");
  delay(d*2);
  }
  
  void menuTwo(){ // draw the settings menu
  lcd.drawBox(0,0,62,30,1);
  lcd.gotoPosition(5,5);
  Serial.print("Backlight");
  lcd.gotoPosition(18,18);
  Serial.print("100%");
 
  lcd.drawBox(66,0,127,30,1);
  lcd.gotoPosition(70,5);
  Serial.print("Backlight");
  lcd.gotoPosition(88,18);
  Serial.print("50%");
  
  lcd.drawBox(0,34,62,63,1);
  lcd.gotoPosition(5,39);
  Serial.print("Backlight");
  lcd.gotoPosition(21,52);
  Serial.print("Off"); 
  
  lcd.drawBox(66,34,127,63,1);
  lcd.gotoPosition(85,39);
  Serial.print("Main");
  lcd.gotoPosition(85,52);
  Serial.print("Menu");
  delay(d*2);
  }

//########################################################################################################################
// Display Screens
//########################################################################################################################

  void viewOne(){
      
    lcd.gotoPosition(0,1);
    Serial.print("OpenEnergyMonitor");
    
   //print power value on GLCD   
    lcd.gotoPosition(0,19);  
    Serial.print("Power:");
    cval2 = cval2 + (cval - cval2)*0.20; //smooth scroll of power reading
    itoa((int)cval2,str,10);
    strcat(str,"W");
    lcd.eraseBlock(40,15,127,30);
    lcd.toggleFont();  
    lcd.gotoPosition(40,15);
    Serial.print(str);
    lcd.toggleFont();
    
   //print room temperature on GLCD 
    lcd.gotoPosition(0,44);  
    Serial.print("Room Temp:");
    dtostrf(temp,0,1,str); 
    strcat(str,"C");
    lcd.eraseBlock(62,44,127,54);
    lcd.gotoPosition(62,44);  
    Serial.print(str);

   //print outside temperature on GLCD     
    lcd.gotoPosition(0,55);  
    Serial.print("Outside Temp:");
    dtostrf(temp1/100,0,1,str);
    strcat(str,"C");
    lcd.eraseBlock(80,55,127,64);
    lcd.gotoPosition(80,55);  
    Serial.print(str);

    
   //last updated
    int seconds = (int)((millis()-last)/1000.0);
    itoa(seconds,str,10);
    lcd.eraseBlock(115,1,127,10);
    lcd.gotoPosition(115,1);
    Serial.print(str);
    
   //draw power bar   
    lcd.eraseBlock(((cval*0.042+1)),33,126,38); //clear bar to end
    lcd.drawBox(0,32,127,39,1);
    lcd.drawFilledBox(1,32,(cval*0.042),39,0xFF); //bar fully black at 3Kw 

  delay(d);
  }

  void viewTwo(){
        
    lcd.gotoPosition(0,1);
    Serial.print("OpenEnergyMonitor");
    lcd.gotoPosition(1,15);  

   //print power value on GLCD  
    lcd.toggleFont();  
    Serial.print("Power:");
    cval2 = cval2 + (cval - cval2)*0.20; //smooth scroll of power reading
    itoa((int)cval2,str,10);
    strcat(str,"W");
    lcd.eraseBlock(71,15,127,30);
    lcd.gotoPosition(71,15);
    Serial.print(str);

    lcd.toggleFont();
    
   //print room temperature on GLCD 
    lcd.drawBox(0,34,62,63,1); 
    lcd.drawLine(0,46,62,46,1);
    lcd.gotoPosition(20,37);  
    Serial.print("Room");
    dtostrf(temp,0,1,str); 
    strcat(str," C");
    lcd.eraseBlock(16,52,60,62);
    lcd.gotoPosition(16,52); 
    Serial.print(str);
    
   //print outside temperature on GLCD 
    lcd.drawBox(66,34,127,63,1);
    lcd.drawLine(66,46,127,46,1);
    lcd.gotoPosition(78,37);  
    Serial.print("Outside");
    dtostrf(temp1/100,0,1,str);
    strcat(str,"C");
    lcd.eraseBlock(82,52,125,62);
    lcd.gotoPosition(82,52); 
    Serial.print(str);
    
   //last updated
    int seconds = (int)((millis()-last)/1000.0);
    itoa(seconds,str,10);
    lcd.eraseBlock(115,1,127,10);
    lcd.gotoPosition(115,1);
    Serial.print(str);
    
  delay(d);
  }
  
  void viewThree(){

   //print power value on GLCD          
    lcd.gotoPosition(1,1);
    lcd.toggleFont();  
    Serial.print("Power:");
    cval2 = cval2 + (cval - cval2)*0.20; //smooth scroll of power reading
    itoa((int)cval2,str,10);
    strcat(str,"W");
    lcd.eraseBlock(71,1,127,16);
    lcd.gotoPosition(71,1);
    Serial.print(str);
    
   //print room temperature on GLCD 
    lcd.gotoPosition(20,30); 
    lcd.toggleFont();   
    Serial.print("Room");
    lcd.toggleFont();
    lcd.gotoPosition(5,40);  
    dtostrf(temp,0,1,str); 
    strcat(str,"C");
    lcd.eraseBlock(5,40,70,55); 
    Serial.print(str);
        
   //print outside temperature on GLCD 
    lcd.gotoPosition(75,30);
    lcd.toggleFont();    
    Serial.print("Outside");
    lcd.toggleFont();  
    lcd.gotoPosition(72,40);  
    dtostrf(temp1/100,0,1,str);
    strcat(str,"C");
    lcd.eraseBlock(72,40,127,55);
    Serial.print(str);

   //last updated
    lcd.toggleFont();
    lcd.gotoPosition(0,55);  
    Serial.print("Last updated:");
    int seconds = (int)((millis()-last)/1000.0);
    itoa(seconds,str,10);
    strcat(str,"s ago");
    lcd.eraseBlock(83,55,127,64);
    lcd.gotoPosition(83,55);
    Serial.print(str); 
   
   //draw power bar   
    lcd.eraseBlock(((cval*0.042+1)),19,126,25); //clear bar to end
    lcd.drawBox(0,18,127,25,1);
    lcd.drawFilledBox(1,18,(cval*0.042),25,0xFF); //bar fully black at 3Kw 

  delay(d);
  }
  
  void clearOnChange(){
   if (TouchState !=  TouchStateLast) { // clear display if changed
   lcd.clearLCD();
   if (backLight == 0) {lcd.backLight(100);} // if backlight is off turn it on
   delay(d);
   }
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
    // 3) Send data via RF every 30s
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

