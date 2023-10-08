/*
* Project: 
*    HomeWeather
* 
* Target: 
*    Measure temperature near my potplants and show me the temp + Humidity
* 
* Working: 
*   Visualisation per 4Digit 7Sev Display and Transmission via Bluetooth with a few settings --> everythings possible
* 
* HickHacks with Bluetooth: 
*   To change SensorPullrate: Stop the Sending-Service (if running) and then set the Pullrate. Do not go below 15 ms, better yet not below 30ms. The communication will crash, if you do it...
* 
* Settings:
*   #define TEMP 0  --> Show Temp on Display
*   #define HUM 1   --> Show Hum on Display
*   #define OFF 2   --> Show nothing on Display
*   #define SENSOR_PULL_RATE 4 --> change sensor pulling rate
*   #define SEND 5  --> send temp and hum per bluetooth ( Service: 0xFFE0 | 0000ffe0-0000-1000-8000-00805f9b34fb    Charac: 0xFFE1 | 0000ffe1-0000-1000-8000-00805f9b34fb )
*   #define UwU 6//66   --> find out yourself!
*/

#include <Arduino.h>

//------------------------------DHT11
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN A0
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

//------------------------------ 4digit 7seg
#include "SevSeg.h" 
SevSeg sevseg;

//------------------------------ HM-18 (Bluetooth Module)
#include <SoftwareSerial.h>

#define softRX A1
#define softTX A2

SoftwareSerial softSerial(softRX, softTX);
char c;

//------------------------------ Programm Params
#define TEMP 0
#define HUM 1
#define OFF 2
#define SENSOR_PULL_RATE 4
#define SEND 5
#define UwU 6//66

//------------------------------ Programm Variables
boolean sending = false;
unsigned long clock_sensors = millis();
unsigned long pullSensors = 1000*60*5;
float temp;
float hum;

//--------------------------------------------------------------------------- SETUP
void setup() {
    byte numDigits = 4;
    byte digitPins[] = { 2, 3, 4, 5 };
    byte segmentPins[] = { 6, 7, 8, 9, 10, 11, 12, 13 };
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
    sevseg.setBrightness(50);

    dht.begin();

    softSerial.begin(9600); // Verbindung zu HM-18
}

//--------------------------------------------------------------------------- LOOP
void loop() {
//------------------------------------- read the Sensor
    if (millis() - clock_sensors > pullSensors) {
        clock_sensors = millis();

        sensors_event_t event;
        dht.temperature().getEvent(&event);

        // Get temp event and store its value.
        if (isnan(event.temperature)) {
            temp = 9999;
        } else {
            temp = event.temperature * 100;
        }

        // Get humidity event and store its value.
        dht.humidity().getEvent(&event);
        if (isnan(event.relative_humidity)) {
            hum = 9999;
        } else {
            hum = event.relative_humidity * 100;
        }
   
        if (sending && c != SENSOR_PULL_RATE) {
            String readings = String(temp / 100) + "," + String(hum / 100);
            softSerial.print(readings);
        }
    }

//-------------------------------------- get the programm params to run
    while (softSerial.available()) {
        c = softSerial.read();
    }

    switch (c)
    {
    case TEMP:
        sevseg.setNumber(temp, 2);
        break;

    case HUM:
        sevseg.setNumber(hum, 2);
        break;

    case SENSOR_PULL_RATE: // send singel digit call, then the wished time as String
        sending = false;

        while (softSerial.available()) {
            pullSensors = softSerial.readString().toInt();

            c = TEMP;
            softSerial.clearWriteError();
        }
        break;

    case SEND:
        if (sending) {
            sending = false;
            c = UwU;
        } else {
            sending = true;
            c = TEMP;
        }
        break;

    case UwU:
        sevseg.setChars("UnnU");
        break;

    case OFF:
        // fallthrough on purpose
    default:
        sevseg.blank();
        sevseg.setBrightness(0);
        break;
    }
//-------------------------------------- refresh display (is always needed...)
    sevseg.refreshDisplay(); // Must run repeatedly
}