#include "smartsticker.h"

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(10); // hang out until serial port opens
  }

  Serial.println("Basic test");
  tmp_hmd_setup();
  esp_sleep_enable_timer_wakeup(TOTAL_SLEEP);

  createHmdTempTask();
}

void loop() {
}

void vTempHumidityTask(void *pvParameters) {
  float temp, humidity;
  struct tm timeinfo;
  StaticJsonDocument<200> doc;
  while (1) {
    readTmpHmdData(&temp, &humidity);
    Serial.print("Temp: "); Serial.println(temp);
    Serial.print("Hum: "); Serial.println(humidity);

    getNTPTime(&timeinfo);
    constructJsonPayload_TMP_HMD_SNSR(&doc, &temp, &humidity, &timeinfo);
    loopedWifiDatabaseUpdate(&doc);

    vTaskDelay(pdMS_TO_TICKS(5000));  // Delay 5 seconds between iterations

    Serial.println("Entering deep sleep....");
    // esp_deep_sleep_start();
  }

  vTaskDelete(NULL); // Not necessary here, but good habit for tasks that could exit
}