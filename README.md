# DHT11-Blynk
DHT11-Blynk project

// Author - Peter W. Chan , July 2017

Project:
	1.	Connect DHT-11 temperature and humidity sensor to ESP8266 device. 
	2.	Collect data from DHT-11 sensor data (i.e. temperature and humidity) and update Blynk Cloud every 10 seconds
	3.	Connect LED and 220Ω/330Ω resistor to demonstrate remote control through Internet (i.e. IoT)
	4.	Setup Blynk free service account using Blynk mobile application.
	5.	Setup Blynk dashboard with widgets to display the DHT-11 sensor data. Use “History Graph” widget to display the temperature data. 
			Use “ Labeled Value” widget to display the humidity data.
	6.	Setup LED button (i.e. “Button” widget) to turn on/off LED. Use “LED” widget to display the physical status of the LED.
	7.	Display the location of the IoT device with a Blynk's map widget in mobile  

Hardware:
	1.  1 x Nodemcu/WEMOS ESP8266 development boards (e.g. NodeMCU 1.0 (ESP-12E module))
	2.  1 x DHT-11 sensor (temperature and humidity)
	3.  1 x LED
	4.  1 x 220ohms/330ohms resistor
	5.  jumpers and wires
	6.  breadboard

Arduino library required (Use Arduino Library Manager / Zip files installation):
	1.  ESP8266 WiFi 
	2.  Blynk
	3.  Time/TimeLib
	4.  DHT sensor library
	5.  Adafruit Unified Sensor

ESP8266 Board Installation:
  1.	Installing the Addon With the “Arduino Boards Manage”
    	Go to the Preferences (File > Preferences)
    	Scroll towards the bottom of the window, copy this URL into the “Additional Board Manager URLs” text box:
      		http://arduino.esp8266.com/stable/package_esp8266com_index.json
	2.	Navigate to the Board Manager by going to Tools > Boards > Boards Manager. Install esp8266 platform 
			(and don't forget to select your ESP8266 board from Tools > Board menu after installation).
			Alternatively, you could install the ESP8266/ESP32 Arduino libraries by clone the Github repository 
			into “hardware/esp8266com/esp8266” directory at your computer: 
      		https://github.com/esp8266/Arduino/tree/master/
	3.	With the Board addon installed, all that’s left to do is select “ESP8266 Thing” from the Tools > Boards menu.

Blynk (http://www.blynk.cc/)
	Blynk was designed for the Internet of Things. It can control hardware remotely, it can display sensor data, 
	it can store data, visualize it and do many other cool things.
	There are three major components in the platform:
			Blynk App - 		allows to you create amazing interfaces for your projects using various widgets we provide.
			Blynk Server - 	responsible for all the communications between the smartphone and hardware. 
											You can use our Blynk Cloud or run your private Blynk server locally. It’s open-source, could easily handle thousands of devices and can even be launched on a Raspberry Pi.
			Blynk Library - for all the popular hardware platforms - enable communication with the server and process 
											all the incoming and outcoming commands.
	Blynk has an export function (My Apps) to create your own mobile apps to Apple Store or Google Play for further distribution

	Blynk - Getting Started
		1.	Download Blynk’s mobile apps for Android or iOS phone.
		2.	Get the Authorised Token (Auth Token)
		3.	Install Blynk Arduino library through Arduino IDE’s Library Manager
		4.	Create your first example sketch code
					https://examples.blynk.cc/?board=ESP8266&shield=ESP8266%20WiFi&example=GettingStarted%2FBlynkBlink
		5.	Paste the Auth Token in the sketch code
		6.	Flash the code to your hardware – Finish connected to Blynk Cloud!

	Blynk Documentation:   http://docs.blynk.cc/
	Blynk Widgets Documentation:  https://github.com/blynkkk/blynkkk.github.io/blob/master/Widgets.md
	
	


	
	

