#include "sensor_info.h"

StaticJsonDocument<200> internalDoc;
extern StaticJsonDocument<200>* doc = &internalDoc;

volatile bool buttonPressed = false;

RTC_DATA_ATTR volatile bool inGroup = false;

/*
void addInGroupToJsonPayload() {
  JsonObject fields = (*doc)["fields"];
  if (fields.isNull()) {
    doc->createNestedObject("fields");
  }
  
  fields["groupID"]["stringValue"] = "group_1";

  return;
}
*/
void IRAM_ATTR handleButtonInterrupt() {
  buttonPressed = true;
  inGroup = true;
}