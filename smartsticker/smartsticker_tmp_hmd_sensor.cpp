#include "smartsticker_tmp_hmd_sensor.h"

Adafruit_AM2320 am2320 = Adafruit_AM2320();

void readTmpHmdData(float *temp, float *humidity) {
  *temp = am2320.readTemperature();
  vTaskDelay(pdMS_TO_TICKS(2000));
  *humidity = am2320.readHumidity();
  if (isnan(*temp)) {
    *temp = 20.0;
  }
  if (isnan(*humidity)) {
    *humidity = 20.0;
  }
}

void constructJsonPayload_TMP_HMD_SNSR(StaticJsonDocument<200> *doc, float *temp, float *humidity/*, struct tm *timeinfo*/) {
  JsonObject fields = (*doc)["fields"];
  if (fields.isNull()) {
    fields = doc->createNestedObject("fields");
  }
  
  /*
  char timestamp[25];
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
  */

  // JSON payload using ArduinoJson
  #ifdef _TMP_  // Temperature Sensor
  fields["peripheral"]["stringValue"] = "Temperature";
  fields["value"]["doubleValue"] = *temp;
  #endif

  #ifdef _HUM_  // Humidity Sensor
  fields["peripheral"]["stringValue"] = "Humidity";
  fields["value"]["doubleValue"] = *humidity;
  #endif
  if (inGroup || doesGroupIDExist()) {
    fields["groupID"]["stringValue"] = "group_1";
  }
  // fields["timestamp"]["stringValue"] = timestamp;
  return;
}

void vTempHumidityTask(void *pvParameters) {
  float temp, humidity;
  while (1) {
    vTaskDelay(pdMS_TO_TICKS(2000));
    readTmpHmdData(&temp, &humidity);

    
    Serial.print("Temp: "); Serial.println(temp);
    Serial.print("Hum: "); Serial.println(humidity);
    
    constructJsonPayload_TMP_HMD_SNSR(doc, &temp, &humidity);
    
    loopedWifiDatabaseUpdate(doc);

    vTaskDelay(pdMS_TO_TICKS(5000)); 

    // Deep sleep;
    deepSleep();
  }

  vTaskDelete(NULL); // Not necessary here, but good habit for tasks that could exit
}

