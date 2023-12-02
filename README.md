# IMS_IoT-monitoring-system
Mini temperature, humidity and air quality monitoring system for IOT system, low cost.

**Download all files**
 * Open _360.ino in ARDUINO IDE

![](https://github.com/VictorIkeda/IMS_IoT-monitoring-system/blob/main/Images/screenshot.png?raw=true)

### **What you need**

* Sensor DHT11 for temperature and Humidity.
* Sensor MQ-135 To identify the air quality, it will be classified as good, average and bad.
* HC-05 Bluetooth module to be able to view the Arduino serial via the smartphone
* ESP8266 ESP-01 WiFi module to connect the system to the router and access via computer or smartphone

## **Instructions**
After assembling the system shown below, do not forget to enter the SSID and password in the code.

## Sensor DHT11
![](https://github.com/VictorIkeda/IMS_IoT-monitoring-system/blob/main/Images/dht11S.png?raw=true)

Connecting the sensor's analog pin to the Arduino's A5 analog pin and connecting the power pins on the board, as shown in the schematic. The adafruit/DHT-sensor-library library was used to program the sensor. The temperature and humidity values are displayed on the Arduino serial monitor in the IDE itself.

## Sensor MQ-135
![](https://github.com/VictorIkeda/IMS_IoT-monitoring-system/blob/main/Images/mqs.png?raw=true)

Sensor will capture CO2. To identify air quality, it will be classified as good, average and bad. The MQ-135 contains 4 pins and only 3 will be used in connection with the Arduino, which are the power pins and the analog pin, which will be connected to the Arduino input A0. Every time the sensor starts, the values are reset for accurate results. The values that the sensor returns for the CO2 calculation is the PPM. From a test carried out by placing the sensor near the car's exhaust, it was defined as ppm < 10 poor quality, ppm < 500 medium and ppm >= 500 as good.

```
  void setup(){
    Serial.begin(9600);
    delay(1000);
    dht.begin();
    float rzero = gasSensor.getRZero();// Returns the value that must be calibrated
    delay(3000);
    Serial.print("MQ135 calibration value : ");
    Serial.println(rzero);
  }
```

## HC-05 Bluetooth
![](https://github.com/VictorIkeda/IMS_IoT-monitoring-system/blob/main/Images/metade.png?raw=true)

The bluetooth module contains 6 pins but only 4 pins were used, namely: RXD, TXD, GND and VCC. The TXD pin is connected directly to the Arduino's TXD input, and RXD passes through the resistance of a 2.2k and a 1k resistor

## ESP8266 ESP-01
![](https://github.com/VictorIkeda/IMS_IoT-monitoring-system/blob/main/Images/FULL.png?raw=true)

The ESP8266 module is a WI-FI module with a microcontroller and can be programmed independently, without the need for an Arduino. ESP-01 ESP8266 is the first version of the module and brings several problems that were corrected through firmware, thus allowing new libraries to be used. The module comes from the factory with the oldest firmware version, allowing you to use only old libraries or libraries from the manufacturer itself. The module requires 2 supplies, 5v and 3.3v, being the module that consumes the most energy. For the module to receive data from Arduino and display it to the user, a Web Server was created directly from Arduino, executing HTML directly on Arduino. To open the web page, simply type the IP that appears on the serial monitor in the browser.
