// Arduino Mega Side of the Communication System || Serial1
// RX1 --> D19, TX1 --> D18

//// Libraries
#include <ArduinoJson.h>

// Define JSON object size
#define JSON_BUFFER_SIZE 256

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
}

void loop() {
  // Create JSON object
  StaticJsonDocument<JSON_BUFFER_SIZE> doc;
  doc["Sensor1"] = 10.0;  // Example sensor data
  doc["Time"] = millis();        // Example timestamp

  // Serialize JSON object to string
  char jsonBuffer[JSON_BUFFER_SIZE];
  serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));

  // Send JSON string over serial
  Serial1.println(jsonBuffer);

  delay(1000); // Send data every second
}
