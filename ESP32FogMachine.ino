// Thermistor Example #3 from the Adafruit Learning System guide on Thermistors
// https://learn.adafruit.com/thermistor/overview by Limor Fried, Adafruit Industries
// MIT License - please keep attribution and consider buying parts from Adafruit

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ArduinoNvs.h>
#include <Artnet.h>
#include "index.h"  //Web page header file
#include "setup.h" //Web page for configuring Fog Machine Setup paramaters
#include "Functions.h"
#include "MillisTimer.h"
bool allowed = 1;
int duration = 0;
int del = 0;
ArtnetReceiver artnet;
uint32_t universe1 = 1;
uint32_t universe2;
int timemultiplier = 118; // This times delay or duration == time on or off
WebServer server(80);
void fogOff() {
  Serial.println("Fog Machine No longer Blows");
  digitalWrite(blowPin, LOW);

}
void fogOn() {
  Serial.println("Fog Machine Blows");
  digitalWrite(blowPin, HIGH);
}
void callback(uint8_t* data, uint16_t size)
{
  // you can also use pre-defined callbacks
}
void handleADC() {
  int a = GetTemp(analogRead(A0));
  String adcValue = String(a);

  server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}
void handleSSID() {

  String adcValue = NVS.getString ("ss");
  Serial.println("Got SSID: " + adcValue);

  server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}
void handlePw() {
  String adcValue = NVS.getString ("pw");
  server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}
void handleDur() {

  int val = NVS.getInt ("dur");
  String adcValue = String(val);
  duration = val;
  server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}
void handleDel() {

  int val = NVS.getInt ("del");
  String adcValue = String(val);
  del = val;
  server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}
void handleUni() {
  String adcValue = NVS.getString ("uni");

  server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}
void handleAdr() {
  int val = NVS.getInt("adr");
  String adcValue = String(val);
  server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}
void handleRoot() {

  String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}
void setupPage() {

  String s = SETUP_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}


void handleSave() {
  bool ok;
  Serial.println("Saving");
  if (server.arg("adr") != "") {
    Serial.println("address: " + server.arg("adr"));
    String ad = server.arg("adr");
    int ad2 = ad.toInt();
    ok = NVS.setInt ("adr", ad2);
    Serial.println("okay: " + ok);

  }

  if (server.arg("ss") != "") {
    Serial.println("SSID: " + server.arg("ss"));
    ok = NVS.setString ("ss", server.arg("ss"));
    Serial.println("okay: " + ok);


  }

  if (server.arg("pw") != "") {

    Serial.println("PW: " + server.arg("pw"));
    ok = NVS.setString ("pw", server.arg("pw"));
    Serial.println("okay: " + ok);
  }
  if (server.arg("uni") != "") {

    Serial.println("uni: " + server.arg("uni"));
    ok = NVS.setString ("uni", server.arg("uni"));
    Serial.println("okay: " + ok);
  }
  if (server.arg("dur") != "") {
    String ad = server.arg("dur");
    int ad2 = ad.toInt();
    Serial.println("dur: " + server.arg("dur"));
    ok = NVS.setInt ("dur", ad2);
    Serial.println("okay: " + ok);
  }
  if (server.arg("del") != "") {
    String ad = server.arg("del");
    int ad2 = ad.toInt();
    Serial.println("del: " + server.arg("del"));
    ok = NVS.setInt ("del", ad2);
    Serial.println("okay: " + ok);
  }


}

void savedur(int dur) {
  NVS.setInt ("dur", dur);
}

void setup(void) {
  NVS.begin();
  pinMode(heatPin, OUTPUT);
  pinMode(blowPin, OUTPUT);

  Serial.begin(115200);
  //analogReference(EXTERNAL);


  Serial.println("Booting");



  const char* password = "paulnathan";
  int address = 1;
  //  if (NVS.getString ("ss") != "") {
  String x = NVS.getString ("ss");
  const char*   ssid = x.c_str();
  Serial.println(ssid);
  //  };
  //  if (NVS.getString ("pw") != "") {
  //    password = NVS.getString ("pw").c_str();
  //  };
  //  if (NVS.getInt ("adr") != NULL) {
  //    address = NVS.getInt ("adr");
  //  };
  Serial.println(address);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  Serial.println("Connecting to ");
  Serial.print(ssid);

  //Wait for WiFi to connect
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  //----------------------------------------------------------------
  // -- Initializing the configuration.

  artnet.begin();


  // if Artnet packet comes to this universe, this function (lambda) is called
  artnet.subscribe(universe1, [&](uint8_t* data, uint16_t size)
  {
    //Serial.print("lambda : artnet data (universe : ");
    //Serial.print(universe1);
    //Serial.println(") = ");
    for (size_t i = 0; i < size; ++i)
    {
      if (i == address) {
        //Serial.print(data[i]); Serial.print(",");
        NVS.setInt ("dur", data[i]);
      }
      if (i == address + 1) {
        //Serial.print(data[i]); Serial.print(",");
        NVS.setInt ("del", data[i]);
      }
    }
    //Serial.println();
  });

  // you can also use pre-defined callbacks
  artnet.subscribe(universe2, callback);

  // -- Set up required URL handlers on the web server.


  Serial.println("Ready.");
  server.on("/", handleRoot);      //This is display page
  server.on("/readADC", handleADC);//To get update of ADC Value only
  server.on("/setup", setupPage);//To get update of ADC Value only
  server.on("/readUNI", handleUni);//To get update of Universe Value only
  server.on("/readADR", handleAdr);//To get update of Starting Address only
  server.on("/readSS", handleSSID);//To get update of SSID only
  server.on("/readPW", handlePw);//To get update of WiFi PW only
  server.on("/readDUR", handleDur);//To get update of Duration only
  server.on("/readDEL", handleDel);//To get update of Duration only

  server.on ("/save", handleSave);
  server.begin();                  //Start server
  Serial.println("HTTP server started");


  setupOta();
  int c = (1000 * NVS.getInt ("dur")) / 2;
  Serial.print(" x=: ");
  Serial.println(c);


}
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long previousMillis2 = 0;        // will store last time LED was updated

void runFog() {
  unsigned long currentMillis = millis();
  unsigned long currentMillis2 = millis();


  if (allowed == 1) {
    if (currentMillis - previousMillis >= 100 * NVS.getInt ("del")) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      Serial.println("test");
      fogOn();
      allowed = 0;
    }



  }
  if (currentMillis2 - previousMillis2 >= 100 * NVS.getInt ("dur")) {
    // save the last time you blinked the LED
    previousMillis2 = currentMillis2;
    fogOff();
    allowed = 1;
  };
}
void loop(void) {
  int t = avg();
  //Serial.println(t);
  if (t <= 300 && t > 0 ) {
    digitalWrite(heatPin, HIGH);
    //Serial.println("nominal Temp");

    runFog();
  } else if (t < 0) {
    digitalWrite(heatPin, LOW);
    digitalWrite(blowPin, LOW);
    Serial.println("Under Temp Error");

  } else {

    digitalWrite(heatPin, LOW);
    digitalWrite(blowPin, LOW);
    Serial.println("Over Temp Error");
  }



  ArduinoOTA.handle();

  server.handleClient();
  //BlinkLights();
  artnet.parse(); // check if artnet packet has come and execute callback

  delay(1);

}
