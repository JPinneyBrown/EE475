#include "smartsticker_tmp_hmd_sensor.h"

Adafruit_AM2320 am2320 = Adafruit_AM2320();

void readTmpHmdData(float *temp, float *humidity) {
  *temp = am2320.readTemperature();
  *humidity = am2320.readHumidity();
}

void constructJsonPayload_TMP_HMD_SNSR(StaticJsonDocument<200> *doc, float *temp, float *humidity) {
  JsonObject fields = doc->createNestedObject("fields");
  
  // JSON payload using ArduinoJson
  fields["type"]["stringValue"] = "Temp And Humidity Sensor";
  fields["fields"]["unique ID"]["integerValue"] = UNID;
  fields["fields"]["temperature"]["doubleValue"] = *temp;
  fields["fields"]["humidity"]["doubleValue"] = *humidity;
  return;
}