#include "smartsticker_tmp_hmd_sensor.h"

Adafruit_AM2320 am2320 = Adafruit_AM2320();

void readTmpHmdData(float *temp, float *humidity) {
  *temp = am2320.readTemperature();
  *humidity = am2320.readHumidity();
}

void constructJsonPayload_TMP_HMD_SNSR(StaticJsonDocument<200> *doc, float *temp, float *humidity, struct tm *timeinfo) {
  JsonObject fields = doc->createNestedObject("fields");
  
  char timestamp[25];
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

  // JSON payload using ArduinoJson
  fields["type"]["stringValue"] = "Temp And Humidity Sensor";
  fields["unique ID"]["integerValue"] = UNID;
  fields["temperature"]["doubleValue"] = *temp;
  fields["humidity"]["doubleValue"] = *humidity;
  fields["timestamp"]["stringValue"] = timestamp;
  return;
}

