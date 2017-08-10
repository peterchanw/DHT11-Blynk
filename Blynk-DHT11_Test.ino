// Developer - Peter W. Chan - July 2017

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

  You’ll need:
   - Blynk App (download from AppStore or Google Play)
   - ESP8266 board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

#include <DHT.h>     //include DHT11 sensor library

// DHT Settings
#define DHTPIN D6         // what digital pin we're connected to. If you are not using NodeMCU change D6 to real pin
#define DHTTYPE DHT11     // DHT 11
const boolean IS_METRIC = true;

int tempThresholds = 20;  // threshold temperature to trigger an email notification
boolean notification = true;
int counter =0;

#define ledPin 2       // LED pin (GPIO2 - D4)

// Initialize the temperat/ure/ humidity sensor
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

WidgetLED led0(V0);   //virtual pin 0 to control led display
WidgetRTC rtc;
WidgetMap myMap(V6);  //virtual pin 6 for the device location

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "******************************";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "******";
char pass[] = "************";

// Digital clock display of the time
void clockDisplay()
{
  // You can call hour(), minute(), ... at any time
  // Please see Time library examples for details

  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + " " + month() + " " + year();
  Serial.print("Current time: ");
  Serial.print(currentTime);
  Serial.print(" ");
  Serial.print(currentDate);
  Serial.println();

  // Send time to the App
  Blynk.virtualWrite(V4, currentTime);
  // Send date to the App
  Blynk.virtualWrite(V5, currentDate);
  //Device location - Sydney CBD coordinate
  //Get the latitude and longitude reading from Google Map)
  int index = 1;
  float lat = -33.8618;
  float lon = 151.2109;
  // Enter your IoT device name "**********"
  myMap.location(index, lat, lon, "**********");
}

// This function sends Arduino's up time every second to Virtual Pin (2) and Virtual Pin (3).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, h);
  Blynk.virtualWrite(V3, t);
  Serial.print("Current Temperature: " + String(t) + " °C, ");
  Serial.print("  Current Humidity: " + String(h) + " %");
  Serial.println("");
  if ((t > tempThresholds)&&(notification)) {
    // Blynk.email("your_email@mail.com", "Subject: Button Logger", "You just pushed the button..."); //
    // If you want to use the email specified in the App (like for App Export):
    Blynk.email("Subject: Warm to Hot weather - Alert", "Current temperature is "+String(t)+" °C");
    Blynk.tweet("Temperature is "+String(t)+" °C, "+"Humidity is "+String(h)+" %");
    notification = false;
    counter += 1;
  }
  else if (t <= tempThresholds) {
    notification = true;
    counter = 0;
  }
  else {
    if (counter > 99) {
      notification = true;
      counter = 0;
    }
    else
      counter += 1;  
  }
}

// This function will be called every time Button Widget at V1
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V1)
{
  int virtualPin1 = param.asInt(); // assigning incoming value from pin V0 to a variable
  // process received value
  if (virtualPin1 == 1){
    digitalWrite(ledPin, HIGH);
    led0.on();
  }
  else {
    digitalWrite(ledPin, LOW);
    led0.off();
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  // Begin synchronizing time
  rtc.begin();

  // Remove all points:
  myMap.clear();

  //Device location - Sydney coordinate
  int index = 1;
  float lat = -33.772156;
  float lon = 151.053815;
  myMap.location(index, lat, lon, "IoT-DHT11");
  
  // Setup a function to check the sensor every 10 seconds
  timer.setInterval(10000L, sendSensor);
  // Display digital clock every 10 seconds
  timer.setInterval(10000L, clockDisplay);
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
  timer.run();      // Initiates BlynkTimer
}

