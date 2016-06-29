#include <ESP8266HTTPClient.h>
#include "secret.h"

void postToThingspeak(int pm25, int pm10)
{
  Serial.println("Sending data to thingspeak");
  HTTPClient client;
  client.begin("http://api.thingspeak.com/update");

  String postStr = APIKEY;
  postStr += "&field1=";
  postStr += pm25;
  postStr += "&field2=";
  postStr += pm10;
  postStr += "\r\n\r\n";

  client.addHeader("X-THINGSPEAKAPIKEY", APIKEY);
  int result = client.POST(postStr);
  Serial.print("POST result: ");
  Serial.println(result);
}

