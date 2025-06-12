#include "smartsticker_wifi.h"

String url = String("https://firestore.googleapis.com/v1/projects/") + PROJECT_ID +
             "/databases/(default)/documents/" + COLLECTION +
             "/sticker_" + DEVICE_TYPE + UNID +
             "?key=" + FIREBASE_API_KEY;

void connectToWifi() {
  
  Serial.print("Connecting to WiFi: "); Serial.println(ssid);
  
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
    
    vTaskDelay(pdMS_TO_TICKS(10));
    String jsonPayload;
    serializeJson(*doc, jsonPayload);

    
    Serial.print("Free heap memory: ");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" bytes");
    
    vTaskDelay(pdMS_TO_TICKS(30));
    // Send HTTP PATCH request
    HTTPClient http;
    Serial.println(url);
    vTaskDelay(pdMS_TO_TICKS(10));
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
    
    vTaskDelay(pdMS_TO_TICKS(80));
    http.end();
    Serial.println("Disconnecting WiFi to save power...");
    vTaskDelay(pdMS_TO_TICKS(10));
    WiFi.disconnect(true); // Save power
    WiFi.mode(WIFI_OFF);
  } else {
    vTaskDelay(pdMS_TO_TICKS(10));
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

bool doesGroupIDExist() {
  connectToWifi();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected.");
    return false;
  }

  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    String response = http.getString();
    Serial.println("GET Response:");
    Serial.println(response);

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, response);
    if (error) {
      Serial.print("JSON error: ");
      Serial.println(error.c_str());
      return false;
    }

    // Check if groupID exists
    if (doc["fields"]["groupID"]["stringValue"]) {
      Serial.print("groupID exists: ");
      Serial.println(doc["fields"]["groupID"]["stringValue"].as<String>());
      return true;
    } else {
      Serial.println("groupID does NOT exist.");
      return false;
    }

  } else {
    Serial.print("GET failed, code: ");
    Serial.println(httpCode);
    return false;
  }

  http.end();
  WiFi.disconnect(true); // Save power
  WiFi.mode(WIFI_OFF);
}

/*
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
*/

