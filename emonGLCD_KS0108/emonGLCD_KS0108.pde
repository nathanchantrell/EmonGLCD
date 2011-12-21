//------------------------------------------------------------------------------------------------------------------------
// GLCD Energy Monitor Display using KS0108 display with temperature transmit and receive
// By Nathan Chantrell. http://zorg.org/
// Builds on emonGLCD example by Trystan Lea and Glyn Hudson at OpenEnergyMonitor.org
//
// Features:
//  Receive power reading from emonTX via RF
//  Receive remote temperature reading via RF
//  Read room temperature from DS18B20 sensor
//  Transmit room temperature reading via RF
//------------------------------------------------------------------------------------------------------------------------

#include <OneWire.h> // http://www.pjrc.com/teensy/arduino_libraries/OneWire.zip
#include <DallasTemperature.h> // http://download.milesburton.com/Arduino/MaximTemperature/DallasTemperature_371Beta.zip
#include <Ports.h> // https://github.com/jcw/jeelib
#include <RF12.h> // https://github.com/jcw/jeelib
#include <glcd.h>  // GLCD-Arduino library http://code.google.com/p/glcd-arduino
#include "fonts/SystemFont5x7.h"   // system font
#include "fonts/Digital.h" // Digital font

// Fixed RF12 settings
#define MYNODE 28            //node ID, 30 is reserved for base station
#define freq RF12_433MHZ     //frequency
#define group 210            //network group 
#define emonTxNode 10        //node ID of the emonTX
#define tempTxNode 11        //node ID of the tempTX

// DS18B20 Temperature sensor on pin D1
#define ONE_WIRE_BUS 1  

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
    
 GLCD.Init(NON_INVERTED);   // Initialise the glcd library
 GLCD.ClearScreen(); // Clear Screen

 last = millis();
    
 sensors.begin(); //start up temp sensor

 //get inital temperature reading
 sensors.requestTemperatures();
 temp=(sensors.getTempCByIndex(0));

}

void loop () 
{
  
 getReadings(); // get data from RFM12 and temp sensor

 showDisplay(); // display data
  
} // end loop


  void showDisplay(){
  
   GLCD.SelectFont(System5x7);
   GLCD.GotoXY(0, 0);
   GLCD.Puts("OpenEnergyMonitor");
   GLCD.GotoXY(0, 19);
   GLCD.Puts("Power:");
   
   //print power value on GLCD
    cval2 = cval2 + (cval - cval2)*0.20; //smooth scroll of power reading
    itoa((int)cval2,str,10);
    strcat(str,"  W");
    GLCD.SelectFont(Digital);
    GLCD.GotoXY(40, 8);
    GLCD.EraseTextLine();
    GLCD.Puts(str);

   //Room Temp
    GLCD.SelectFont(System5x7);
    GLCD.GotoXY(0, 47);
    GLCD.Puts("Room Temp: ");
    dtostrf(temp,0,1,str); 
    strcat(str,"C");
    GLCD.GotoXY(62, 47);
    GLCD.EraseTextLine();
    GLCD.Puts(str);

   //Outside Temp
    GLCD.GotoXY(0, 57);
    GLCD.Puts("Outside Temp:");
    dtostrf(temp1/100,0,1,str);
    strcat(str,"C ");
    GLCD.GotoXY(80, 57);
    GLCD.EraseTextLine();
    GLCD.Puts(str);
  
   //last updated
    int seconds = (int)((millis()-last)/1000.0);
    itoa(seconds,str,10);
    GLCD.GotoXY(115, 0);
    GLCD.EraseTextLine();
    GLCD.Puts(str);
   
   //draw power bar
    GLCD.FillRect(0, 36, 127, 7, WHITE); //clear bar
    GLCD.DrawRect(0, 36, 127, 7, BLACK);
    GLCD.FillRect(0, 36, (cval*0.042), 7, BLACK); //bar fully black at 3Kw
   
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

