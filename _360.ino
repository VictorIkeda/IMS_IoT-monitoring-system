#include <SoftwareSerial.h>
 
//RX pin 2, TX pin 3
SoftwareSerial esp8266(2, 3);

#define DEBUG true
#include "MQ135.h"
#include "DHT.h"
#define ANALOGPIN A0  
#undef RZERO
#define RZERO 206.85 
#undef RZERO
#define RZERO 76.63
#define dht_pin A5 //DATA pin of the Sensor connected to the Analog A5 port
#define DHTTYPE DHT11
MQ135 gasSensor = MQ135(ANALOGPIN);
DHT dht(dht_pin, DHTTYPE);
void setup()
{
  Serial.begin(9600);
  esp8266.begin(115200);
  sendData("AT+RST\r\n", 2000, DEBUG); // rst
  // Conecta a rede wireless
  sendData("AT+CWJAP=\"SSID\",\"PASSWORD\"\r\n", 2000, DEBUG); // Please fill in the SSID and PASSPORT fields
  
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG);
  while(millis() < 10000){}
  // Mostra o endereco IP
  sendData("AT+CIFSR\r\n", 1000, DEBUG);
  // Configures for multiple connections
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG);
  // Start the web server on port 80
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG);
  while(millis() < 1000){}
  dht.begin();
  float rzero = gasSensor.getRZero();
  while(millis() < 3000){}
}
 
void loop()
{
  //float h = dht.readHumidity();
  //float t = dht.readTemperature();

  if (esp8266.available())
  {
    char target[] = "+IPD,";
    if (esp8266.find(target))
    {
      float ppm = gasSensor.getPPM();
      delay(300);
      int connectionId = esp8266.read() - 48;
      
      String webpage = "<head><meta http-equiv=""refresh"" content=""3"">";
      webpage += "<font size=""6""><center></head><h1><u>IoT Monitoring System</u></h1><h2>";
      webpage += "Temperature: ";
      int a = (int) dht.readTemperature();
      webpage += a;
      webpage += " degrees Celsius";
      Serial.print("Temperature . = ");
      Serial.print(dht.readTemperature());
      webpage += "<h2>Air humidity: ";
      int b = (int) dht.readHumidity();
      Serial.print("Air humidity. = ");
      Serial.print(dht.readHumidity());
      webpage += b;
      webpage += "%";
      webpage += "<h2>Air Quality: ";
      Serial.print("CO2 ppm value : ");
      Serial.println(ppm);
      if(ppm < 10){
      webpage += "Bad";
      }else if(ppm < 500){
      webpage += "Medium";
      }else{
      webpage += "Good";
      }
      //webpage += "<h2><iframe width=""475"" height=""250"" src=""https://relogioonline.com.br/embed/horario/#theme=0&ampm=0&showdate=1"" frameborder=""0"" allowfullscreen></iframe>";
      webpage += "</h2>";
      String cipSend = "AT+CIPSEND=";
      cipSend += connectionId;
      cipSend += ",";
      cipSend += webpage.length();
      cipSend += "\r\n";
 
      sendData(cipSend, 1000, DEBUG);
      sendData(webpage, 1000, DEBUG);
      
      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId; // append connection id
      closeCommand += "\r\n";
      
      //sendData(closeCommand, 3000, DEBUG);
      
    }
  }
}
 
String sendData(String command, const int timeout, boolean debug)
{
  // Sending AT commands to the module
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
