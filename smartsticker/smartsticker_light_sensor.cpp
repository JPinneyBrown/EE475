#include "smartsticker_light_sensor.h"

void readLightData(int *lightLevel) {
  int sensorValue = analogRead(PHOTODIODE_PIN);
  *lightLevel = map(sensorValue, 0, 4095, 0, 4095);
}

void constructJsonPayload_LGHT_SNSR(StaticJsonDocument<200> *doc, int *lightLevel/*, tm *timeinfo*/) {
  JsonObject fields = (*doc)["fields"];
  if (fields.isNull()) {
    fields = doc->createNestedObject("fields");
  }
  
  /*
  char timestamp[25];
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
  */

  // JSON payload using ArduinoJson
  Serial.println("Get here!");
  fields["peripheral"]["stringValue"] = "Light";
  fields["value"]["doubleValue"] = *lightLevel;
  // fields["timestamp"]["stringValue"] = timestamp;
  if (inGroup || doesGroupIDExist()) {
    fields["groupID"]["stringValue"] = "group_1";
  }
}

void vLightTask(void *pvParameters) {
  int lightLevel;
  StaticJsonDocument<200> doc;
  while(1) {
    vTaskDelay(pdMS_TO_TICKS(2000));
    readLightData(&lightLevel);
    Serial.print("Light Level: "); Serial.println(lightLevel);

    constructJsonPayload_LGHT_SNSR(&doc, &lightLevel);
    loopedWifiDatabaseUpdate(&doc);

    vTaskDelay(pdMS_TO_TICKS(5000));
    // esp_deep_sleep_start();
    deepSleep();
  }

}