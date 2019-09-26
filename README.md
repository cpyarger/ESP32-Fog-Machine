# ESP32 Fog Machine

##Web interface controlable Fog Machine controller
Can be connected to either in SoftAP mode or after being connected to a WiFi Network
Has built in ArtNet Support. Defaults to Artnet Universe 1, address 1
Device uses 2 channels, the first being duration, The second being delay
Device automatically shuts down fog machine heater, and pump if Temperatures go above 300 degrees F or below 0 Degrees F

##Important Pins

- Thermistor is connected to pin A0
- Pump is connected to pin 17
- Heater is connected to pin 33


## WIP

- Telnet Support
- MQTT Support
- Web Control of Duration, Delay Variables 
