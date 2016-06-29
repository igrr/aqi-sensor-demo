#include "SSD1306.h"
#include <Wire.h>
#include "Sds011.h"
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <time.h>
#include "font.h"
#include "secret.h"
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>

SSD1306  display(0x3c, 14, 12); // D5, D6
SoftwareSerial mySerial(4, 5); // D1, D2
sds011::Sds011 sensor(mySerial);
ESP8266WebServer webServer;
String lastStatus;
int pm25;
int pm10;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  display.init();
  mySerial.begin(9600);
  delay(100);
  sensor.set_sleep(false);
  sensor.set_mode(sds011::QUERY);

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STA_SSID, STA_PASS);
  Serial.println("Connecting to WiFi");
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    displaySpinner(i++);
    delay(30);
  }
  Serial.println();
  displayConnected(WiFi.localIP());
  configTime(8 * 3600, 0, "pool.ntp.org");
  setupOTA();
  webServer.on("/", [](){
    webServer.send(200, "text/html", getLastStatus());
  });
  webServer.begin();
  delay(2000);
  displayWaitingForSensor();
}

void loop() {
  static int lastUpdateMillis = 0;
  if (millis() - lastUpdateMillis > 10000) {
    updateSensorData();
    lastUpdateMillis = millis();
  }
  ArduinoOTA.handle();
  webServer.handleClient();
}

void updateSensorData() {
  sensor.set_sleep(false);
  displayTime();
  
  bool ok = sensor.query_data_auto(&pm25, &pm10, 10);
  displayValues(ok, pm25, pm10);
  
  if (ok) {
    postToThingspeak(pm25, pm10);
  }
  
  sensor.set_sleep(true);
}

String getLastStatus() {
  String result;
  result += "<html><body>";
  result += "<h1>PM2.5: ";
  result += pm25;
  result += "</h1><h1>PM10: ";
  result += pm10;
  result += "</h1></body></html>";
  return result;
}

