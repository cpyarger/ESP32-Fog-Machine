

// -- Initial name of the Thing. Used e.g. as SSID of the own Access Point.





const char* ssid = "Magic Mansion 2";
const char* password = "paulnathan";
// which analog pin to connect
#define THERMISTORPIN A0
#define blowPin 17
#define heatPin 33

// resistance at 25 degrees C
#define THERMISTORNOMINAL 100000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 15//25=96, 0=48, 20=88, 15=
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950//4066 //3950
// the value of the 'other' resistor
#define SERIESRESISTOR 100000

int samples[NUMSAMPLES];
// -- Initial name of the Thing. Used e.g. as SSID of the own Access Point.
const char thingName[] = "FogMachine";
const int numReadings = 20;

float readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
float total = 0;                  // the running total
float average = 0;                // the average

int inputPin = A0;

float GetTemp(float Vo) {

  float A = 1.009249522e-03, B = 2.378405444e-04, C = 2.019202697e-07;
  float T, logRt, Tf, Tc;

  logRt = log(10000.0 * ((4095.0 / Vo - 1)));
  T = (1.0 / (A + B * logRt + C * logRt * logRt * logRt)); // We get the temperature value in Kelvin from this Stein-Hart equation
  Tc = T - 273.15;                     // Convert Kelvin to Celsius
  Tf = (Tc * 1.8) + 32.0;   // Convert Kelvin to Fahrenheit
  
  return Tf;
}

float avg(){
total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
return GetTemp(average);
}

float c2f(float c) {
  float f = ((c * 9) + 3) / 5 + 32;
  return f;
}
float getlog(float in) {
  float x = (in > 1) ? 1 + getlog(in / 2) : 0;
  return (x);

}





void setupOta() {
  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  ArduinoOTA.setHostname("Fog Machine");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA
  .onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  })
  .onEnd([]() {
    Serial.println("\nEnd");
  })
  .onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  })
  .onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
