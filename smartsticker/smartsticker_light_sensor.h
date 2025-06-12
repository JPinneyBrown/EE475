#ifndef _SS_LGHT_SNSR_H_
#define _SS_LGHT_SNSR_H_

#include <Arduino.h>

#include "ArduinoJson.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "sensor_info.h"
#include "smartsticker_wifi.h"


#define     PHOTODIODE_PIN      2

void readLightData(int *lightLevel);

void constructJsonPayload_LGHT_SNSR(StaticJsonDocument<200> *doc, int *lightLevel, tm *timeinfo);

void vLightTask(void *pvParameters);

#define light_setup()         pinMode(PHOTODIODE_PIN, INPUT);

#define createLightTask()     xTaskCreate(vLightTask, "LightTask", 4096, NULL, 1, NULL)
#endif