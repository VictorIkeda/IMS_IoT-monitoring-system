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

## Sensor MQ-135
![](https://github.com/VictorIkeda/IMS_IoT-monitoring-system/blob/main/Images/mqs.png?raw=true)

Sensor will capture CO2. To identify air quality, it will be classified as good, average and bad. The MQ-135 contains 4 pins and only 3 will be used in connection with the Arduino, which are the power pins and the analog pin, which will be connected to the Arduino input A0. Every time the sensor starts, the values are reset for accurate results.
  The values that the sensor returns for the CO2 calculation is the PPM. From a test carried out by placing the sensor near the car's exhaust, it was defined as ppm < 10 poor quality, ppm < 500 medium and ppm >= 500 as good.

`void setup(){
  Serial.begin(9600);
delay(1000);
  dht.begin();
  float rzero = gasSensor.getRZero();// Returns the value that must be calibrated
  delay(3000);
  Serial.print("MQ135 calibration value : ");
  Serial.println(rzero);}`
