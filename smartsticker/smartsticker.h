// #define _DEBUG_

#define SLEEP_HRS     0
#define SLEEP_MIN     (0 + (SLEEP_HRS*60))
#define SLEEP_SECONDS (10 + (SLEEP_MIN*60))
#define TOTAL_SLEEP   (SLEEP_SECONDS * 1000000ULL)

#include "sensor_info.h"

#include "smartsticker_light_sensor.h"
#include "smartsticker_tmp_hmd_sensor.h"
#include "smartsticker_wifi.h"


