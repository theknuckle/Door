// #include <Blynk.h>
 #include <BlynkApiArduino.h>
// #include <BlynkApiMbed.h>
// #include <BlynkApiParticle.h>
// #include <BlynkParticle.h>
// #include <BlynkSimpleCC3000.h>
// #include <BlynkSimpleCurieBLE.h>
// #include <BlynkSimpleEnergiaEthernet.h>
// #include <BlynkSimpleEnergiaWiFi.h>
// #include <BlynkSimpleEsp32.h>
// #include <BlynkSimpleEsp8266.h>
// #include <BlynkSimpleEsp8266_SSL.h>
// #include <BlynkSimpleEthernet.h>
// #include <BlynkSimpleEthernet2.h>
// #include <BlynkSimpleEthernetV2_0.h>
// #include <BlynkSimpleFishino.h>
// #include <BlynkSimpleIntelEdisonWiFi.h>
// #include <BlynkSimpleLinkItONE.h>
// #include <BlynkSimpleMKR1000.h>
// #include <BlynkSimpleParticle.h>
// #include <BlynkSimpleRedBearLab_BLE_Nano.h>
// #include <BlynkSimpleRedBear_Duo.h>
// #include <BlynkSimpleRedBear_Duo_BLE.h>
// #include <BlynkSimpleRFduinoBLE.h>
// #include <BlynkSimpleSerialBLE.h>
// #include <BlynkSimpleShieldEsp8266.h>
// #include <BlynkSimpleSIM800.h>
// #include <BlynkSimpleSimbleeBLE.h>

// #include <BlynkSimpleTinyDuino.h>
// #include <BlynkSimpleUIPEthernet.h>
// #include <BlynkSimpleUserDefined.h>
// #include <BlynkSimpleWifi.h>
// #include <BlynkSimpleWiFiShield101.h>
// #include <BlynkSimpleWiFiShield101_SSL.h>
// #include <BlynkSimpleWiFly.h>
// #include <BlynkSimpleWildFire.h>
// #include <BlynkSimpleYun.h>
// #include <BlynkWidgets.h>
// #include <WidgetBridge.h>
// #include <WidgetGPS.h>
// #include <WidgetLCD.h>
// #include <WidgetLED.h>
// #include <WidgetMap.h>
// #include <WidgetRTC.h>
// #include <WidgetSD.h>
// #include <WidgetTable.h>
// #include <WidgetTerminal.h>
// #include <WidgetTimeInput.h>

/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  =>
  =>          USB HOWTO: http://tiny.cc/BlynkUSB
  =>

  You’ll need:
   - Blynk App (download from AppStore or Google Play)
   - Arduino Uno board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT SwSerial

#include <SoftwareSerial.h>
SoftwareSerial SwSerial(10, 11); // RX, TX

int OpenPin = 6;
int ClosePin = 7;
int Redlight = 8;
int GreenLight = 9;

String key = String("12345"); //key code
String entered = String("00000"); //variable for entered code by user

bool keyStatus = false;

int keylength = 5;

bool status = false; //if key is corret, also acts as a check

double time1 = 0; //time key is entered
double time2 = 0; //time elapsed since key has been entered

int index = 0; //length of key code
    

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "c3b3e3cf3f20401aa24b381a273bc87f";

#include <BlynkSimpleStream.h>

void setup()
{
  // Debug console
  SwSerial.begin(9600);
  Serial.begin(9600);

  pinMode(OpenPin, OUTPUT);
  pinMode(ClosePin, OUTPUT);
  pinMode(Redlight, OUTPUT);
  pinMode(GreenLight, OUTPUT);

  digitalWrite(OpenPin, LOW);
  digitalWrite(ClosePin, HIGH);
  digitalWrite(Redlight, LOW);
  digitalWrite(GreenLight, LOW);

  Blynk.virtualWrite(V1, LOW);

  time2 = millis();

  Serial.print("Waiting for keypress \n");

  Blynk.begin(Serial, auth);
}

void loop()
{
 Blynk.run();


  if (keyStatus == true && status == false) 
  {
    status = true;
    time1 = millis();
    Serial.print("unlocked");

  }


  if (status == true)
  {
    digitalWrite(OpenPin, HIGH);
    digitalWrite(ClosePin, LOW);
    digitalWrite(Redlight, LOW);
    digitalWrite(GreenLight, HIGH);  
    time2 = millis();
  }

  if (time2 - time1 > 10000 && status == true)
  {
    status = false;
    digitalWrite(OpenPin, LOW);
    digitalWrite(ClosePin, HIGH);
    digitalWrite(Redlight, HIGH);
    digitalWrite(GreenLight, LOW);
    //entered = "00000";  
    keyStatus = false;
    Serial.print("timeout");
    delay(100);
  }



}


/*void serialEvent()
{
	while(Serial.available())
	{
	    
	    	while (index < keylength)
	    	{
	    		entered [index] = Serial.read();
	    		index++
			;}
		

	}
	
	index = 0;
}
*/

BLYNK_WRITE(V2) 
{

  if(key == param.asStr())
  {
	  keyStatus == true;
  }
  else if (key != param.asStr())
  {
	 
    digitalWrite(Redlight, HIGH);
    status = false;

  }
  terminal.flush();
}


