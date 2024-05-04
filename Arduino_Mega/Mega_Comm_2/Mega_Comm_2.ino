// Arduino Mega Side of the Communication System || Serial1
// RX1 --> D19, TX1 --> D18

//// Libraries
#include <ArduinoJson.h>

// Define JSON object size
#define JSON_BUFFER_SIZE 256

// Some Global Variables For Logic Functions
int Total_Profit = 0; // This should count the total profit, increase with each function call

int Total_Number_Of_Cars = 0; // This should count how many distinct cars entered today 
                              // {increment with each function call}

int Slots[5] = {0}; //Each element should either be 1 or 0 
                    //depending on the LDR sensor under the slot
int Emergency_State;

// Setup Code

void setup() 
{
  Serial.begin(115200);
  Serial1.begin(9600);
}

void loop() 
{
  // Create JSON object
  StaticJsonDocument<JSON_BUFFER_SIZE> doc;

  // Assign data fields to the JSON object that will be sent over UART to ESP32
  doc["Slot1"] = Slot[0];
  doc["Slot2"] = Slot[1];
  doc["Slot3"] = Slot[2];
  doc["Slot4"] = Slot[3];
  doc["Slot5"] = Slot[4];

  doc["Emergency"] = Emergency_State;
  doc["TotalProfit"] = Total_Profit;
  doc["TotalNumberofCars"] = Total_Number_Of_Cars;

  // Serialize JSON object to string
  char jsonBuffer[JSON_BUFFER_SIZE];
  serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));

  // Send JSON string over serial
  Serial1.println(jsonBuffer);

  delay(100); // Send data every 0.1 seconds
}


// Functions that will edit the global variables defined above the setup

void Check_Slot(int slot_num)
{
  int state;

  // bla bla bla --> Logic for LDR check,
  //                 this function should do the job for the 5 slots

  slot[slot_num - 1] = state;
}

void IsEmergency()
{
  int FunctionState;

  // bla bla bla --> Logic for Emergency check,
  //                 this function should only edit the global variable (Emergency_State)

  Emergency_State = FunctionState;

}

// You can use the last two increment variables in your functions brought from other code
