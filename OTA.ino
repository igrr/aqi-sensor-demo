void setupOTA() {
  ArduinoOTA.begin();
  ArduinoOTA.onStart([](){
    displayOTAStart();
  });
  ArduinoOTA.onProgress([](unsigned progress, unsigned size) {
    displayOTAProgress(progress, size);
  });
  ArduinoOTA.onEnd([]() {
    displayOTAEnd();
  });
  ArduinoOTA.onError([](ota_error_t) {
    displayOTAError();
  });
}
