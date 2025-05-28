#include "smartsticker.h"

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(10); // hang out until serial port opens
  }

  Serial.println("Basic test");
  tmp_hmd_setup();
  esp_sleep_enable_timer_wakeup(TOTAL_SLEEP);
}

void loop() {
  float temp, humidity;
  StaticJsonDocument<200> doc;
  readTmpHmdData(&temp, &humidity);
  Serial.print("Temp: "); Serial.println(temp);
  Serial.print("Hum: "); Serial.println(humidity);
  constructJsonPayload_TMP_HMD_SNSR(&doc, &temp, &humidity);
  loopedWifiDatabaseUpdate(&doc);
  delay(5000);
  Serial.println("About to deep sleep...");
  esp_deep_sleep_start();
  delay(2000);
}