#ifndef _SNSR_INFO_
#define _SNSR_INFO_

#ifndef _DEVICE_TYPE_INIT_
#define DEVICE_TYPE   "light"
#define UNID          String(0x0001)
#endif

#include "ArduinoJson.h"

#define BUTTON_PIN 3  // D1 = GPIO3

extern volatile bool buttonPressed;

extern StaticJsonDocument<200> *doc;

extern RTC_DATA_ATTR volatile bool inGroup;

void IRAM_ATTR handleButtonInterrupt();

void addInGroupToJsonPayload();

#define buttonInit()  pinMode(BUTTON_PIN, INPUT_PULLDOWN); \
                      attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonInterrupt, FALLING); \
                      inGroup = false

#define deepSleep()     esp_deep_sleep_enable_gpio_wakeup(1ULL << BUTTON_PIN, ESP_GPIO_WAKEUP_GPIO_HIGH); \
                        esp_deep_sleep_start(); \
                        Serial.println(inGroup); \
                        pinMode(BUTTON_PIN, INPUT_PULLDOWN)

#define buttonTriggered() if (buttonPressed) {buttonPressed = false; /*addInGroupToJsonPayload();*/ /*Serial.println("Add group_1 field...");*/} 

#endif
