# IMS_IoT-monitoring-system
Mini temperature, humidity and air quality monitoring system for IOT system, low cost.

**Download all files**
 * Open _360.ino in ARDUINO IDE

### **What you need**

* Sensor DHT11 for temperature and Humidity.
* Sensor MQ-135 To identify the air quality, it will be classified as good, average and bad.
* ESP8266 ESP-01 WiFi module to connect the system to the router and access via computer or smartphone
* HC-05 Bluetooth module to be able to view the Arduino serial via the smartphone

## Sensor DHT11
![](https://github.com/VictorIkeda/IMS_IoT-monitoring-system/blob/main/Images/dht11S.png?raw=true)

Connecting the sensor's analog pin to the Arduino's A5 analog pin and connecting the power pins on the board, as shown in the schematic. The adafruit/DHT-sensor-library library was used to program the sensor. The temperature and humidity values are displayed on the Arduino serial monitor in the IDE itself.
