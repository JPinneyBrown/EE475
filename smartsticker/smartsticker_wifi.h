#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define ssid              "Thorin, Son of Thrain"
#define password          "johnsons"

#define FIREBASE_API_KEY  "AIzaSyCPv_k2k0sj_5s8RTfHVqA7vRbAvJviE5o"
#define PROJECT_ID        "haven-data"
#define COLLECTION        "test_3" // Firestore collection
#define DOCUMENT          "counts_data"   // Firestore document name

extern String url;

void loopedWifiDatabaseUpdate(StaticJsonDocument<200> *doc);
void listNetworks();



void listNetworks();