#include "smartsticker.h"

void setup() {
  Serial.begin(9600);
  
  while (!Serial) {
    delay(10); // hang out until serial port opens
  }
  
  buttonInit();

  esp_sleep_enable_timer_wakeup(TOTAL_SLEEP);
  
  light_setup();
  createLightTask();

  //tmp_hmd_setup();
  //createHmdTempTask();
  Serial.println(esp_reset_reason());
  Serial.println("End of setup...");
}

void loop() {
  buttonTriggered();
  vTaskDelay(pdMS_TO_TICKS(10));
}
