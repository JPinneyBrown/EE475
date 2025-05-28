#ifndef _SS_TMP_HMD_SNSR_H_
#define _SS_TMP_HMD_SNSR_H_

#include <Arduino.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"
#include "ArduinoJson.h"

#define UNID 0x0001

extern Adafruit_AM2320 am2320;

void readTmpHmdData(float *temp, float *humidity);

void constructJsonPayload_TMP_HMD_SNSR(StaticJsonDocument<200> *doc, float *temp, float *humidity);

#ifdef _DEBUG_
  #define   tmp_hmd_setup()   am2320.begin();
#else
  #define   tmp_hmd_setup()   esp_log_level_set("i2c.master", ESP_LOG_NONE); am2320.begin();
#endif

#endif