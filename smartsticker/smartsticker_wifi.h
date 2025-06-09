#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <time.h>

#define ssid              "Mason’s iPhone"
#define password          "geometry"

#define FIREBASE_API_KEY  "AIzaSyCPv_k2k0sj_5s8RTfHVqA7vRbAvJviE5o"
#define PROJECT_ID        "haven-data"
#define COLLECTION        "stickers" // Firestore collection

#ifndef _DEVICE_TYPE_INIT_
#define DEVICE_TYPE   "default"
#define UNID          String(0)
#endif
// #define DOCUMENT          "counts_data"   // we set document in smartsticker_wifi.cpp

extern String url;

void loopedWifiDatabaseUpdate(StaticJsonDocument<200> *doc);
void getNTPTime(struct tm *timeinfo);
void listNetworks();


void listNetworks();