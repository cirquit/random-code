/**
 * Uses WeeESP8266 Library: https://github.com/itead/ITEADLIB_Arduino_WeeESP8266
 * For Sketching with Hardware 2015b by Patrick Proppe
 */

#include "ESP8266.h"
#define esp8266 Serial1
// orange = Pin18
// yellow = Pin19


#define SSID        "swh"
#define PASSWORD    "swhswhswh"
ESP8266 wifi(Serial1);
String comdata = "";

void setup()
{

  Serial.begin(9600);
  Serial.println("Setup begin");
  Serial.print("FW Version: ");
  Serial.println(wifi.getVersion().c_str());


  if (wifi.setOprToStation()) {
    Serial.println("Setting ESP up as a client: Ok");
  } else {
    Serial.println("Setting ESP up as a client: Error");
  }

  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.println("Join AP success");
    Serial.print("IP: ");
    Serial.println(wifi.getLocalIP().c_str());
    wifi.enableMUX(); // multiple connection mode
    esp8266.println("AT+CIPMUX=1");
  } else {
    Serial.println("Join AP failure");
  }

  Serial.println("setup end");

}
void closeServer() {
  esp8266.println("AT+CIPCLOSE");//close TCP
}
void getComdata()
{
  while (esp8266.available() > 0) {
    comdata += char(esp8266.read());
    delay(1);
  }
}

int f = 0;
void loop() {
  getComdata();
  if (comdata.length() > 0) {
    Serial.print(comdata);
    comdata = "";
  }
  if (f == 0) {

    delay(1000);
    getHTTP("141.84.8.119", "/picCount", 8000);

    f = 1;

  }

  if (Serial.available()) {
    esp8266.write(Serial.read());
  }
}

boolean getHTTP(String server, String subdirs, int port )
{

  if (wifi.createTCP(1, server, port)) {

    String getReq = "GET " + subdirs + " HTTP/1.0\r\n\r\n";

    char data[getReq.length() + 1];
    getReq.toCharArray(data, getReq.length() + 1); // Converted String to char.


    if (wifi.send(1, (uint8_t *)data, sizeof(data))) {
      Serial.println("DEBUG: send was successful");
    }
  }

}
