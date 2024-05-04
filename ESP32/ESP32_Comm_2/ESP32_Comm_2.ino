// ESP32 Side of the Communication System || Serial2
// RX2 --> GPIO16, TX2--> GPIO16

//// Libraries
#include <ArduinoJson.h>
#include <WiFi.h>
#include "ThingSpeak.h"

//// Wifi_Credentials
const char* ssid = "MegzESP";   // your network SSID (name) 
const char* password = "1";   // your network password

//// Global Objects and Variables
WiFiClient  client;
int Data[8] = {0};

//// ThingSpeak Settings
unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "Key";

// Define JSON object size
#define JSON_BUFFER_SIZE 256

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
}

void loop() {

    // Connect or reconnect to WiFi
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect");
    while(WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, password);
      Serial.print(".");
      delay(500);     
    } 
   Serial.println("\nConnected.");
  }

  // Check for incoming data
  if (Serial2.available() > 0) 
  {
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

    // Writing the JSON Data Elements into one Data Array
    // You can edit the Data Array to use Test dummy data
    Data[0] = doc["Slot1"];
    Data[1] = doc["Slot2"];
    Data[2] = doc["Slot3"];
    Data[3] = doc["Slot4"];
    Data[4] = doc["Slot5"];
    Data[5] = doc["Emergency"];
    Data[6] = doc["TotalProfit"];
    Data[7] = doc["TotalNumberOfCars"];


    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    for(int DataField = 1; DataField <= 8; DataField++)
    {
        int Upload_State = ThingSpeak.writeField(myChannelNumber, DataField, Data[DataField-1], myWriteAPIKey);

        if(Upload_State == 200)
        {
            Serial.print("Channel update successful, DataField: ");
            Serial.println(counter);
        }
        else
        {
            Serial.println("Problem updating channel. HTTP error code " + String(x));
            counter--; // To repeat the last upload
        }
    }
    
    
  }
  
  delay(100); // Check for data more frequently
}

