#include "smartsticker_light_sensor.h"

void readLightData(int *lightLevel) {
  int sensorValue = analogRead(PHOTODIODE_PIN);
  *lightLevel = map(sensorValue, 0, 4095, 0, 3);
  Serial.print("Photodiode Reading: ");
  Serial.println(*lightLevel);
}

void constructJsonPayload_LGHT_SNSR(StaticJsonDocument<200> *doc, int *lightLevel, tm *timeinfo) {
  JsonObject fields = doc->createNestedObject("fields");
  
  char timestamp[25];
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

  // JSON payload using ArduinoJson
  fields["peripheral"]["doubleValue"] = "Light";
  fields["Light Level"]["doubleValue"] = *lightLevel;
  fields["timestamp"]["stringValue"] = timestamp;
}