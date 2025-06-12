#ifndef _SS_TMP_HMD_SNSR_H_
#define _SS_TMP_HMD_SNSR_H_

#include <Arduino.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"

#include "ArduinoJson.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "sensor_info.h"
#include "smartsticker_wifi.h"

// #define _TMP_
// #define _HUM_

extern Adafruit_AM2320 am2320;

void readTmpHmdData(float *temp, float *humidity);

void constructJsonPayload_TMP_HMD_SNSR(StaticJsonDocument<200> *doc, float *temp, float *humidity/*, tm *timeinfo*/);

void vTempHumidityTask(void *pvParameters);

#ifdef _DEBUG_
  #define   tmp_hmd_setup()             am2320.begin();
#else
  #define   tmp_hmd_setup()             esp_log_level_set("i2c.master", ESP_LOG_NONE); am2320.begin();
#endif

#define     createHmdTempTask()         xTaskCreate(vTempHumidityTask, "TempHumidityTask", 4096, NULL, 1, NULL);

#endif