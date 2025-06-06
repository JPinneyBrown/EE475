#include "smartsticker_wifi.h"

extern String url = String("https://firestore.googleapis.com/v1/projects/") + PROJECT_ID +
             "/databases/(default)/documents/" + COLLECTION +
             "/" + DOCUMENT +
             "?key=" + FIREBASE_API_KEY;

void connectToWifi() {
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 80) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  Serial.print("WiFi status code: ");
  Serial.println(WiFi.status());
}

void loopedWifiDatabaseUpdate(StaticJsonDocument<200> *doc) {
  // Connect to Wi-Fi
  connectToWifi();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi!");

    String jsonPayload;
    serializeJson(*doc, jsonPayload);

    Serial.print("Free heap memory: ");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" bytes");

    // Send HTTP PATCH request
    HTTPClient http;
    Serial.println(url);
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.PATCH(jsonPayload);
    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response:");
      Serial.println(response);
    } else {
      Serial.println("Error sending request");
    }

    http.end();
    Serial.println("Disconnecting WiFi to save power...");
    WiFi.disconnect(true); // Save power
    WiFi.mode(WIFI_OFF);
  } else {
    Serial.println("WiFi connection failed.");
  }
  return;
}


void listNetworks() {
  Serial.println("Scanning WiFi networks...");
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; i++) {
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(WiFi.SSID(i));
    Serial.print(" (");
    Serial.print(WiFi.RSSI(i));
    Serial.println(" dBm)");
  }
}

void getNTPTime(struct tm *timeinfo) {
  connectToWifi();
  if (WiFi.status() == WL_CONNECTED) {
    configTime(-8 * 3600, 0, "pool.ntp.org", "time.nist.gov");
    if (getLocalTime(timeinfo)) {
      Serial.println(timeinfo, "Initial time: %Y-%m-%d %H:%M:%S");
    } else {
      Serial.println("Failed to get time");
    }
  } else {
    Serial.println("WiFi connection failed.");
  }
}