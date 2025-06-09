// #define _DEBUG_

#define DEVICE_TYPE   "Humidity"

#define SLEEP_HRS     0
#define SLEEP_MIN     (0 + (SLEEP_HRS*60))
#define SLEEP_SECONDS (10 + (SLEEP_MIN*60))
#define TOTAL_SLEEP   (SLEEP_SECONDS * 1000000ULL)

#include "smartsticker_tmp_hmd_sensor.h"
#include "smartsticker_wifi.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <time.h>
