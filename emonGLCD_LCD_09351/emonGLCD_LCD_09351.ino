//------------------------------------------------------------------------------------------------------------------------
// GLCD Energy Monitor Display using Sparkfun LCD-09351 serial GLCD 128x64
// By Nathan Chantrell. http://zorg.org/
// Builds on emonGLCD example by Trystan Lea and Glyn Hudson at OpenEnergyMonitor.org
//
// Serial backpack is loaded with summoningdark's alternative firmware: https://sourceforge.net/projects/serialglcd/
// GLCD library is http://sourceforge.net/projects/serialglcdlib/
//
// Features:
//  Receive power reading from emonTX via RF
//  Receive remote temperature reading via RF
//  Read room temperature from DS18B20 sensor
//  Transmit room temperature reading via RF
//------------------------------------------------------------------------------------------------------------------------

#include <OneWire.h> // http://www.pjrc.com/teensy/arduino_libraries/OneWire.zip
#include <DallasTemperature.h> // http://download.milesburton.com/Arduino/MaximTemperature/DallasTemperature_371Beta.zip
#include <JeeLib.h> // https://github.com/jcw/jeelib
#include <serialGLCD.h> // Include the serialGLCD library http://sourceforge.net/projects/serialglcdlib/
                        // See serialGLCD_Library_Notes.txt for running under Arduino 1.0

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

}

void loop()
{
  
 getReadings(); // get data from RFM12 and temp sensor

 showDisplay(); // display data

 delay(d);
  
} // end loop
  
   
  void showDisplay(){
      
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

