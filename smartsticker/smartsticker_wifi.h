#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "sensor_info.h"

#define ssid              "Ecole Maison Rocher"
// #define ssid              "Mason’s iPhone"
// #define ssid              "Thorin, Son of Thrain"
#define password          "laboratory"

#define FIREBASE_API_KEY  "AIzaSyCPv_k2k0sj_5s8RTfHVqA7vRbAvJviE5o"
#define PROJECT_ID        "haven-data"
#define COLLECTION        "stickers" // Firestore collection

extern String url;

void loopedWifiDatabaseUpdate(StaticJsonDocument<200> *doc);

/* void getNTPTime(struct tm *timeinfo); */

void listNetworks();

bool doesGroupIDExist();

