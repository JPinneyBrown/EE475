#ifndef _SS_TMP_HMD_SNSR_H_
#define _SS_TMP_HMD_SNSR_H_

#include <Arduino.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"
#include "ArduinoJson.h"

#ifdef _DEVICE_TYPE_INIT_
#undef DEVICE_TYPE
#undef UNID
#define DEVICE_TYPE   "Temperature"
#define UNID          itoa(0x0001);
#endif

extern Adafruit_AM2320 am2320;

void readTmpHmdData(float *temp, float *humidity);

void constructJsonPayload_TMP_HMD_SNSR(StaticJsonDocument<200> *doc, float *temp, float *humidity, tm *timeinfo);

void constructJsonPayload_TMP_HMD_PR(StaticJsonDocument<200> *doc);

void vTempHumidityTask(void *pvParameters);

#ifdef _DEBUG_
  #define   tmp_hmd_setup()   am2320.begin();
#else
  #define   tmp_hmd_setup()   esp_log_level_set("i2c.master", ESP_LOG_NONE); am2320.begin();
#endif

#define     createHmdTempTask() xTaskCreate(vTempHumidityTask, "TempHumidityTask", 4096, NULL, 1, NULL);

#endif