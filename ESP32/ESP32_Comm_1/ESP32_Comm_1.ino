// ESP32 Side of the Communication System || Serial2
// RX2 --> GPIO16, TX2--> GPIO16

//// Libraries
#include <ArduinoJson.h>

// Define JSON object size
#define JSON_BUFFER_SIZE 256

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
}

void loop() {
  // Check for incoming data
  if (Serial2.available() > 0) {
    char jsonBuffer[JSON_BUFFER_SIZE];
    int bytesRead = Serial2.readBytesUntil('\n', jsonBuffer, sizeof(jsonBuffer));
    jsonBuffer[bytesRead - 1] = '\0'; // Replace newline with null terminator

    // Deserialize JSON string to object
    DeserializationError error = deserializeJson(doc, jsonBuffer);
    if (error) {
      Serial.print("Error parsing JSON: ");
      Serial.println(error.f_str());
      return;
    }

    // Access data from JSON object
    int sensor1Value = doc["Sensor1"];
    unsigned long timestamp = doc["Time"];

    Serial.print("Sensor 1: ");
    Serial.println(sensor1Value);
    Serial.print("Timestamp: ");
    Serial.println(timestamp);
  }
  
  delay(100); // Check for data more frequently
}
