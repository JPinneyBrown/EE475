#ifndef _SS_LGHT_SNSR_H_
#define _SS_LGHT_SNSR_H_

#include <Arduino.h>
#include "ArduinoJson.h"

#define PHOTODIODE_PIN A0

#ifdef _DEVICE_TYPE_INIT_
#undef DEVICE_TYPE
#undef UNID
#define DEVICE_TYPE   "Light"
#define UNID          itoa(0x0001);
#endif

void readLightData(int *lightLevel);

void constructJsonPayload_LGHT_SNSR(StaticJsonDocument<200> *doc, int *lightLevel, tm *timeinfo);

#define light_setup() pinMode(PHOTODIODE_PIN, input);

#endif