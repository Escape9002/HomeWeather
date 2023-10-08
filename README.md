# HomeWeather
Measure temperature near my potplants and show me the temp + Humidity
 
## Working: 
Visualisation per 4Digit 7Sev Display and Transmission via Bluetooth with a few settings --> everythings possible
 
## HickHacks with Bluetooth: 
To change SensorPullrate: Stop the Sending-Service (if running) and then set the Pullrate. Do not go below 15 ms, better yet not below 30ms. The communication will crash, if you do it...
 
## Settings:
   * define TEMP 0  --> Show Temp on Display
   *  HUM 1   --> Show Hum on Display
   *  OFF 2   --> Show nothing on Display
   *  SENSOR_PULL_RATE 4 --> change sensor pulling rate
   *  SEND 5  --> send temp and hum per bluetooth 
   * * Service: 0xFFE0 | 0000ffe0-0000-1000-8000-00805f9b34fb
   * * Charac: 0xFFE1 | 0000ffe1-0000-1000-8000-00805f9b34fb
   *  UwU 6//66   --> find out yourself!

## The potplant
Rubbertree: 
* Temps: 20-25°C (not below 15°C)
* Sun but not directly
* ~30cm high

        Lets hope he survives!
# TischArduino
This was an older project of mine, I still enjoy the code and it might be helpful for further extension of this main project, so you can find it here (on another branch) as well. It's not best practice, so please dont do PullRequest from TischArduino into this project, as it would overwrite everything...they are not the same and shall not see each other!
