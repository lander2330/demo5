// Sketch: demo5.ino
// Version: Version 2026.05.20
// Author: Larry Anderson
//
// This ESP32 microcontroller project describes how to
// add over-the-air (ota) firmware updating capability
// to your ESP32 sketch.
// 
// This technique for replacing your compiled sketch stored
// in your ESP32 uses wireless wifi opposed to requiring a
// usb wired connection to your ESP32.
//
// Imagine wirelessly replacing the compiled sketch that runs in your ESP32
// with just the use of your mobile device being a cell phone, tablet, laptop, or pc. 
// 
// If your sketch starts your ESP32 wifi as an access point, your wifi device
// can join that access point wifi network and then initiate the over-the-air update
// to your ESP32.
// 
// If your sketch starts your ESP32 wifi as a station on an existing wifi network,
// your wifi device can join that existing wifi network and then initiate the 
// over-the-air update to your ESP32.
//  
// Add the statements shown in this sketch to your existing sketch
// so that your updated, compiled, and uploaded sketch running in your ESP32
// will support the ESP32 over-the-air update requests from your web browser
// running on a mobile device.
// 
// Use Sketch->Export Compiled Binary located on the Arduino IDE Action Bar
// to compile your sketch and create its firmware file named something like
// yoursketchname\build\esp32.esp32.esp32c6\yoursketchname.ino.bin
// Copy yoursketchname.ino.bin file to a file directory
// on your mobile device that you can access later when
// you are ready to initiate the over-the-air update using 
// its web browser app.
// 
// When you are ready to initiate the over-the-air update,
// make sure your mobile device and your ESP32 are logged on to the same wifi network.
// Start your mobile device's web browser and navigate to http://yourESP32WebServer.local/update
//
// The over-the-air update web server running as part of your ESP32 sketch sends your web browser
// the following display:
//
// Firmware:
// [Choose File]   No file chosen  [Update Firmware]
//
// FileSystem
// [Choose File]   No file chosen  [Update FileSystem]
//
// At this point, select the Firmware [Choose File] button.
// Navigate to yoursketchname.ino.bin file and select it.
// Then select the Firmware [Update Firmware] button
// After about 15 seconds, the following message displays
// Update Success! Rebooting...
//
// At this point, your ESP32 is running your newly uploaded sketch firmware.
//
// It is important to note you can look into acquiring a static ip address for your networks modem/router
// and optionally a domain name associated with that static ip address and setup
// port forwarding in your wifi router so that it routes an incoming ota update request 
// to your esp32 from a cell phone, tablet, laptop, or pc located anywhere in the
// world with internet access.
//
// Add all the remaining statements below to your sketch 
// to add support for over-the-air updating capability to your sketch.
#include <WiFi.h>
#include <HTTPClient.h>

char ssid[32] = "yourwifissid";
char password[32] = "yourwifipassword";

#include <ESPAsyncWebServer.h>
AsyncWebServer server(80);

#include <ESPAsyncHTTPUpdateServer.h>
ESPAsyncHTTPUpdateServer updateServer;
#include <ESPmDNS.h>

void setup()
  {
  //Serial.begin(9600);
  //delay(2000);

  // demonstrating station mode, joins an existing wifi network
  WiFi.mode(WIFI_STA);      
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
    {
    delay(1000);
    }

  delay(100);

  // add over-the-air update capability to your ESP32 web server
  updateServer.setup(&server);
  updateServer.onUpdateBegin = [](const UpdateType type, int &result)
    {
    //abort the update like this if you need to:
    //result = UpdateResult::UPDATE_ABORT;        
    //Serial.println("Update started : " + String(type));
    };
  updateServer.onUpdateEnd = [](const UpdateType type, int &result)
    {
    //Serial.println("Update finished : " + String(type) + " result: " + String(result));
    };   

  // start your ESP32 web server
  server.begin();

  // creates a local domain name so the mobile web browser user can enter http://yourESP32WebServer.local/update
  // to connect to your ESP32 web server and initiate the over-the-air update process.
  if (!MDNS.begin("yourESP32WebServer"))
    {
    //Serial.println("domain name service begin failed"); 
    }
  // Advertises your web server on the standard http protocol html TCP port 80     
  else
    {    
    MDNS.addService("http","tcp",80);    
    }

  // Serial.println("yourESP32WebServer is ready to accept an over-the-air update request from a mobile devices web browser");
  }

// this demo sketch doesn't really do anything other than
// show the minimal statements required to support the over-the-air updating capability
void loop ()
  {    
  }

// these statements show my software development environment
// Microsoft Windows 11 
// Arduino IDE 2.3.6
// Board: ESP32C6 Dev Module (specifically Espressif Systems ESP32-C6-DEVKITC-1-N8 Microcontroller)
// Flash Size: 8MB(64Mb)
// Partition Scheme: 8M with spiffs (3MB APP/1.5MB SPIFFS)
// Using library WiFi at version 3.3.0 in folder: C:\Users\larry\AppData\Local\Arduino15\packages\esp32\hardware\esp32\3.3.0-alpha1\libraries\WiFi 
// Using library Networking at version 3.3.0 in folder: C:\Users\larry\AppData\Local\Arduino15\packages\esp32\hardware\esp32\3.3.0-alpha1\libraries\Network 
// Using library HTTPClient at version 3.3.0 in folder: C:\Users\larry\AppData\Local\Arduino15\packages\esp32\hardware\esp32\3.3.0-alpha1\libraries\HTTPClient 
// Using library NetworkClientSecure at version 3.3.0 in folder: C:\Users\larry\AppData\Local\Arduino15\packages\esp32\hardware\esp32\3.3.0-alpha1\libraries\NetworkClientSecure 
// Using library ESP Async WebServer at version 3.7.7 in folder: C:\Users\larry\OneDrive\Documents\Arduino\libraries\ESP_Async_WebServer 
// Using library FS at version 3.3.0 in folder: C:\Users\larry\AppData\Local\Arduino15\packages\esp32\hardware\esp32\3.3.0-alpha1\libraries\FS 
// Using library Async TCP at version 3.4.0 in folder: C:\Users\larry\OneDrive\Documents\Arduino\libraries\Async_TCP 
// Using library ESPAsyncHTTPUpdateServer at version 3.0.0 in folder: C:\Users\larry\OneDrive\Documents\Arduino\libraries\ESPAsyncHTTPUpdateServer 
// Using library ESPmDNS at version 3.3.0 in folder: C:\Users\larry\AppData\Local\Arduino15\packages\esp32\hardware\esp32\3.3.0-alpha1\libraries\ESPmDNS 
// Using library Ticker at version 3.3.0 in folder: C:\Users\larry\AppData\Local\Arduino15\packages\esp32\hardware\esp32\3.3.0-alpha1\libraries\Ticker 
// Using library SPIFFS at version 3.3.0 in folder: C:\Users\larry\AppData\Local\Arduino15\packages\esp32\hardware\esp32\3.3.0-alpha1\libraries\SPIFFS 
// Using library Update at version 3.3.0 in folder: C:\Users\larry\AppData\Local\Arduino15\packages\esp32\hardware\esp32\3.3.0-alpha1\libraries\Update 
