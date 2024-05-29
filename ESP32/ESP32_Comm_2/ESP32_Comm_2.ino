// ESP32 Side of the Communication System || Serial2
// RX2 --> GPIO16(GREEN), TX2--> GPIO17(BLUE)

//// Libraries
#include <ArduinoJson.h>
#include <WiFi.h>
#include "ThingSpeak.h"

//// Wifi_Credentials
const char* ssid = "MegzEsp";   // your network SSID (name) 
const char* password = "14559000";   // your network password

//// ThingSpeak Settings
unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "Secret";

//// Global Objects and Variables
WiFiClient  client;
int Data[8] = {0};

// Define JSON object size
#define JSON_BUFFER_SIZE 256

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
        delay(500);
        Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
    
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  StaticJsonDocument<JSON_BUFFER_SIZE> doc;
  
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
    Data[7] = doc["TotalNumberofCars"];

    /* 
    Serial.println("---------------------------");
    Serial.print("Slot1: ");
    Serial.println(Data[0]);
    Serial.print("Slot2: ");
    Serial.println(Data[1]);
    Serial.print("Slot3: ");
    Serial.println(Data[2]);
    Serial.print("Slot4: ");
    Serial.println(Data[3]);
    Serial.print("Slot5: ");
    Serial.println(Data[4]);
    Serial.print("Emergency: ");
    Serial.println(Data[5]);
    Serial.print("TotalProfit: ");
    Serial.println(Data[6]);
    Serial.print("TotalNumberOfCars: ");
    Serial.println(Data[7]);
    Serial.println("---------------------------");
    */
   
  SendData();
  delay(10*60*1000);
 }
}

 void SendData(){
  for(int DataField = 1; DataField <= 8; DataField++)
    {
      ThingSpeak.setField(DataField, Data[DataField - 1]);
    }

    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
 }