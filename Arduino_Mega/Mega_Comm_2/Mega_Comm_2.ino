// Arduino Mega Side of the Communication System || Serial1
// RX1 --> D19, TX1 --> D18

//___________LIBRARIES_________________
//#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


//____________Define JSON object size____________
#define JSON_BUFFER_SIZE 256
//--------------------------------

/*
  LDR -->A01234
  gas & flame --> A5 A6

  RC522 Module SCK to Mega pin 52 -->31
  RC522 Module MOSI to Mega pin 51 -->30
  RC522 Module MISO to Mega pin 50 -->29
  RC522 Module IRQ to unconnected 
  RC522 Module GND to GND
  servo control pin -->2
  servo control pin -->3
  servo control pin -->4
  LEDs 22-->32
  int Ap = 5;
  int Bp = 6;
  int Cp = 7;
  int Dp = 8;
  int EmLight = 13;
*/

#define SS_PIN_1 7  // Slave Select pin for RC522 Module 1
#define RST_PIN_1 6  // Reset pin for RC522 Module 1

#define SS_PIN_2 10   // Slave Select pin for RC522 Module 2
#define RST_PIN_2 9  // Reset pin for RC522 Module 2


//----------PINS--------------------------------------------------------//
//-------digital pins -->> breadboard-----------
#define dpin_1 22
#define dpin_2 23
#define dpin_3 24
#define dpin_4 25
#define dpin_5 26
#define dpin_6 27
#define dpin_7 28
#define dpin_8 29
#define dpin_9 30
#define dpin_10 31
#define dpin_11 32
#define dpin_12 33
#define dpin_13 34
#define dpin_14 35
#define dpin_15 36
#define dpin_16 37
#define dpin_17 38
#define dpin_18 39
#define dpin_19 40
#define dpin_20 41
#define dpin_21 42
#define dpin_22 43
#define dpin_23 44
#define dpin_24 45
#define dpin_25 46
#define dpin_26 47
#define dpin_27 48
#define dpin_28 49
#define dpin_29 50
#define dpin_30 51
#define dpin_31 52
#define dpin_32 53

//************************************  #Defines  **************************************************

//--------------LDRs-----------------------
const int LDR_Pin[5] = {A0,A1,A2,A3,A4};

#define LightThreshold 100

#define CarSlot_1 0
#define CarSlot_2 1
#define CarSlot_3 2
#define CarSlot_4 3
#define CarSlot_5 4

int Slots[5] = {CarSlot_1,CarSlot_2,CarSlot_3,CarSlot_4,CarSlot_5}; // holds 0 or 1 , 0 >> not available, 1 >> available
int Temp[5];
#define SlotAvailable 1
#define SlotNOTAvailable 0

  int i ;//iterator



//----------------RFID----------------------
  MFRC522 mfrc522_1(SS_PIN_1, RST_PIN_1); // Create MFRC522 instance for Module 1
  MFRC522 mfrc522_2(SS_PIN_2, RST_PIN_2); // Create MFRC522 instance for Module 2

  Servo Entrance_Servo;  // create servo object to control a servo
  Servo Exit_Servo;  // create servo object to control a servo
  Servo Emergency_Servo;


  // Define named NFC cards (UID -> Card Name)
  typedef struct {
    byte uid[7];      // UID bytes of the NFC card (4-byte array)
    const char* name; // Name associated with the NFC card
  } NFCCard;

  // List of named NFC cards (change UID bytes and names accordingly)
  NFCCard nfcCards[] = {
    {{0x04, 0x50, 0x10, 0x5C, 0x39, 0x61, 0x80}, "Card 1"},
    {{0x04, 0x06, 0x85, 0x5B, 0x39, 0x61, 0x80}, "Card 2"},
    {{0x04, 0x53, 0x28, 0x5B, 0x39, 0x61, 0x81}, "Card 3"},
    {{0x04, 0xBA, 0x4A, 0x5B, 0x39, 0x61, 0x80}, "Card 4"},
    {{0x04, 0xAC, 0xE1, 0x5B, 0x39, 0x61, 0x80}, "Card 5"}
  };


//------(RFID 1/2) -->> (entrance / exit)------------
int ModFlag;
int CardNumber;
int TimeVar;
#define EntranceMod 1
#define ExitMod 2

//-------Timer Arrays-------------------
unsigned long Cars[5];
unsigned long EndTime[5];
unsigned long StartTime[5];

//--------LEDs---------------
// Define the pins to be used for the LEDs
const int ledPins[] = {dpin_1,dpin_2,dpin_3,dpin_4,dpin_5,dpin_6,dpin_7,dpin_8,dpin_9,dpin_10,dpin_11};
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]); // Calculate the number of LEDs
const int EmLight = 45;

#define ThereIsEmergency 99 
#define NoEmergency 0

#define MQ_5_A A5
#define Flame_D A6

//-----------------SevenSeg-----------------------

  //seven-segment-anode-7448-decoder

//Declaring variabiles
int Ap = 33;
int Bp = 34;
int Cp = 35;
int Dp = 36;

//---------------------Lcd----------------------

// Prototypes
int ExitLcd(int x);

//initialize the liquid crystal library
//the first parameter is  the I2C address
//the second parameter is how many rows are on your screen
//the  third parameter is how many columns are on your screen

LiquidCrystal_I2C lcd(0x27, 16, 2);

//----------------------------------------

//---servo related variables
  int ServoFlag = 0;
  int pos = 0;     // variable to store the servo position


//-------------------------------------------

//---------------------------------Application Variables---------------------------
int APP_AvailableSlots;       //DONE
int APP_Total_Profit;        //DONE
int APP_Emergency;          //DONE
int APP_TotalNumberOfCars; //DONE
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>__________<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
//unsigned long startTime; // Variable to store the start time


//---------FunctionPrototypes--------------
int CheckAvailableSlot(int LDR_Pin);
int NumberOfAvailableSlots();
void TimerFunc(int ThisModule,int ThisCar);
int Time(int ThisCar);
void LEDPath_init();
void LEDPath(int Slot);
//void LCD_Initialize();
void RFID_Init();
void Read_Card_Open_Gate();
int fees(int timeSec);
void ServoFunc(int);
void MainPathFunc();
void segWrite(int n);
int WhichCar();


void setup(){


  Serial.begin(9600);  //-----SerialMonitor---------
  LEDPath_init(); // Initialize the LED---------
  //LCD_Initialize(); // Initialize the lcd----
  RFID_Init();

  Serial.print("Sensor Value: ");
  int MQ_Value = analogRead(MQ_5_A);
  int Flame_Value = digitalRead(Flame_D);


  //--SevSeg--
  //Declaring pin as output
  pinMode(Ap, OUTPUT);
  pinMode(Bp, OUTPUT);
  pinMode(Cp, OUTPUT);
  pinMode(Dp, OUTPUT);

  pinMode(EmLight, OUTPUT);

   //initialize lcd screen
  lcd.begin();
  int money = 14;//example value
  //ExitLcd(money);
  //Calling LCD function to print "Your fees are ___$"
  
  

}



void loop(){



  //Serial.print("SmokedetectorValue :");
  //Serial.println(analogRead(sensorPin));

  if((digitalRead(Flame_D) == 0)||(analogRead(MQ_5_A) > 600)){

  
    APP_Emergency = ThereIsEmergency; 
      //
    for (pos = 90; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      Emergency_Servo.write(pos);              // tell servo to go to position in variable 'pos'
      Entrance_Servo.write(pos);              // tell servo to go to position in variable 'pos'
      Exit_Servo.write(pos);              // tell servo to go to position in variable 'pos'
      
      delay(10); 
    }
    
    ServoFlag = 1;

    while((digitalRead(Flame_D) == 0)||(analogRead(MQ_5_A) > 600)){

      Serial.print("GASdetectorValue :");
      Serial.println(analogRead(MQ_5_A));
      Serial.print("FlamedetectorValue :");
      Serial.println(analogRead(Flame_D));
      
      //emergency code {}
      digitalWrite(EmLight,HIGH);
      delay(200);
      digitalWrite(EmLight,LOW);
      delay(200);

                            // waits 15ms for the servo to reach the position
    }
      

    

  }else{

    if (ServoFlag==1){

      for (pos = 0; pos <= 90; pos += 1) { // goes from 180 degrees to 0 degrees
      Emergency_Servo.write(pos);              // tell servo to go to position in variable 'pos'
      Entrance_Servo.write(pos);              // tell servo to go to position in variable 'pos'
      Exit_Servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15ms for the servo to reach the position
    }
    }

    
    APP_Emergency = NoEmergency;



    APP_AvailableSlots = NumberOfAvailableSlots();
    segWrite(APP_AvailableSlots);
    for(i=0;i<5;i++){

      Temp[i] = Slots[i];

    }

            
    Read_Card_Open_Gate(); // our big func##############____MAINCODE_____________#################################

    
    
    delay(50);





    
    if(APP_AvailableSlots < NumberOfAvailableSlots()){//$$$$$$$$$$$$$$UltraSonic$$$$$$$$$$$$$$$$$$$$$$

        ModFlag = ExitMod;

        CardNumber = WhichCar();
        
        TimerFunc(ModFlag,CardNumber);
        
        TimeVar = Time(CardNumber/*CardNumber*/);
        
        APP_TotalNumberOfCars ++;
        
        Serial.print("time for this car = ");
        Serial.println(TimeVar);

        ServoFunc(ExitMod);

        delay(1000);

   
    }





    ServoFlag = 0;
  
    
    
  
  /*
  //Serial.println("  ");
  //Serial.println(APP_AvailableSlots);
  //Serial.println("  ");

  Serial.print("the time of car number__ ");
  Serial.print(CardNumber);
  Serial.print("is ___");
  Serial.println(TimeVar);
  delay(1000);
  */



  }

  //*******Sending data to ESP32************
  // Create JSON object
  
  
  
  StaticJsonDocument<JSON_BUFFER_SIZE> doc;

  // Assign data fields to the JSON object that will be sent over UART to ESP32
  doc["Slot1"] = Slots[0];
  doc["Slot2"] = Slots[1];
  doc["Slot3"] = Slots[2];
  doc["Slot4"] = Slots[3];
  doc["Slot5"] = Slots[4];

  doc["Emergency"] = APP_Emergency;
  doc["TotalProfit"] = APP_Total_Profit;
  doc["TotalNumberofCars"] = APP_TotalNumberOfCars;

  // Serialize JSON object to string
  char jsonBuffer[JSON_BUFFER_SIZE];
  serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));

  // Send JSON string over serial
  Serial1.println(jsonBuffer);

  //delay(100); // Send data every 0.1 seconds

}








int CheckAvailableSlot(int LDR_Pin) {


  if(analogRead(LDR_Pin) > LightThreshold){

    return SlotAvailable;

  }else{
    return SlotNOTAvailable;
  }



}

int NumberOfAvailableSlots() {
  int i = 0;
  int NumberOfSlots = 0 ;
  for(i=0;i<5;i++){
    Slots[i] = 0;
  }

  for(i = 0 ; i<5 ; i++){
    if(CheckAvailableSlot(LDR_Pin[i]) == SlotAvailable){
      Slots[i] = 1;
      NumberOfSlots++;
    }
  }


  //______________SERIALPRINT________________
  
  for(i=0;i<5;i++){
    Serial.print("LDR_");
    Serial.print(i+1);
    Serial.print("  value = ");
    Serial.println(analogRead(LDR_Pin[i]));
    
  }

  //___________________________________________
  
  
  return NumberOfSlots;
}

void TimerFunc(int ThisModule,int ThisCar) {
  unsigned long Duration;
  if(ThisModule==EntranceMod){

    StartTime[ThisCar] = millis();
    Serial.print("start_time");
    Serial.println(StartTime[ThisCar]);
  ModFlag = 0;

  }else if(ThisModule==ExitMod){

    EndTime[ThisCar] = millis();
    Serial.print("End_time");
    Serial.println(StartTime[ThisCar]);


     Duration = (EndTime[ThisCar] - StartTime[ThisCar])/1000;
    Cars[ThisCar] = Duration;

    
  

  ModFlag = 0;
  }

 
}

int Time(int ThisCar) {

  return Cars[ThisCar];

}

void LEDPath_init() {
 // Initialize the digital pins as output
 for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
 }
}

void LEDPath(int Slot) {

 switch (Slot)
 {
    case CarSlot_1 :

    digitalWrite(ledPins[0], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[0], LOW); // Turn off the LED
    
    digitalWrite(ledPins[1], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[1], LOW); // Turn off the LED
    
    digitalWrite(ledPins[2], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[2], LOW); // Turn off the LED

    

    break;

    case CarSlot_2 :

    digitalWrite(ledPins[0], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[0], LOW); // Turn off the LED
    
    digitalWrite(ledPins[1], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[1], LOW); // Turn off the LED
    
    digitalWrite(ledPins[3], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[3], LOW); // Turn off the LED

    digitalWrite(ledPins[4], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[4], LOW); // Turn off the LED

    

    break;

    case CarSlot_3 :

    digitalWrite(ledPins[0], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[0], LOW); // Turn off the LED
    
    digitalWrite(ledPins[1], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[1], LOW); // Turn off the LED
    
    digitalWrite(ledPins[3], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[3], LOW); // Turn off the LED

    digitalWrite(ledPins[5], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[5], LOW); // Turn off the LED

    digitalWrite(ledPins[6], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[6], LOW); // Turn off the LED

    


    break;

    case CarSlot_4 :

    digitalWrite(ledPins[0], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[0], LOW); // Turn off the LED
    
    digitalWrite(ledPins[1], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[1], LOW); // Turn off the LED
    
    digitalWrite(ledPins[3], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[3], LOW); // Turn off the LED

    digitalWrite(ledPins[5], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[5], LOW); // Turn off the LED

    digitalWrite(ledPins[7], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[7], LOW); // Turn off the LED

    digitalWrite(ledPins[8], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[8], LOW); // Turn off the LED

    break;

    case CarSlot_5 :

    digitalWrite(ledPins[0], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[0], LOW); // Turn off the LED
    
    digitalWrite(ledPins[1], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[1], LOW); // Turn off the LED
    
    digitalWrite(ledPins[3], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[3], LOW); // Turn off the LED

    digitalWrite(ledPins[5], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[5], LOW); // Turn off the LED

    digitalWrite(ledPins[7], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[7], LOW); // Turn off the LED

    digitalWrite(ledPins[9], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[9], LOW); // Turn off the LED

    digitalWrite(ledPins[10], HIGH); // Turn on the LED
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[10], LOW); // Turn off the LED


    break;

    case ThereIsEmergency :

    //mesh delwa2ty-----

    break;
 } 
}

void RFID_Init(){
  

  //-------setup-------------
  SPI.begin();          // Init SPI bus
  mfrc522_1.PCD_Init(); // Init MFRC522 Module 1
  mfrc522_2.PCD_Init(); // Init MFRC522 Module 2

  Serial.println("Scan an NFC card...");

  Emergency_Servo.attach(2);
  Entrance_Servo.attach(3);  // attaches the servo on pin 2 to the servo object
  Exit_Servo.attach(4);  // attaches the servo on pin 3 to the servo object

}

void handleCard(byte* uid) {
  // Compare UID of the detected card with known NFC cards
  for (size_t i = 0; i < sizeof(nfcCards) / sizeof(nfcCards[0]); i++) {
    if (compareUID(uid, nfcCards[i].uid)) {
      Serial.print("Card detected: ");
      Serial.println(nfcCards[i].name);
      CardNumber = i;
      // Add logic or actions based on the card name here
      break; // Exit loop after finding a matching card
    }
  }
}

bool compareUID(byte* uid1, byte* uid2) {
  // Compare two UID arrays byte by byte
  for (int i = 0; i < 7; i++) {
    if (uid1[i] != uid2[i]) {
      return false; // UIDs don't match
    }
  }
  return true; // UIDs match
}

void Read_Card_Open_Gate() {

  ModFlag = 0;

  if (mfrc522_1.PICC_IsNewCardPresent() && mfrc522_1.PICC_ReadCardSerial() && (0 != APP_AvailableSlots))
  {
    MFRC522::Uid uid_1 = mfrc522_1.uid; // Get UID struct
    handleCard(uid_1.uidByte); // Pass UID bytes to handleCard()
    Serial.println("Card detected on Module 1");
    ModFlag = EntranceMod;////////////////////////////////////////////////////////////////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<,,
    delay(10); // Delay to avoid multiple reads
    mfrc522_1.PICC_HaltA(); // Halt PICC


    TimerFunc(ModFlag,CardNumber);
    //TimeVar = Time(CardNumber);
    ServoFunc(EntranceMod);
    MainPathFunc();

    
    
    



  }
  /*else if (mfrc522_2.PICC_IsNewCardPresent() && mfrc522_2.PICC_ReadCardSerial())
  {
    MFRC522::Uid uid_2 = mfrc522_2.uid; // Get UID struct
    handleCard(uid_2.uidByte); // Pass UID bytes to handleCard()
    Serial.println("Card detected on Module 2");
    ModFlag = ExitMod;//////////////////////////////////////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    delay(10); // Delay to avoid multiple reads
    mfrc522_2.PICC_HaltA(); // Halt PICC
    
    APP_TotalNumberOfCars ++;//increase total number of cars by 1
    

    TimerFunc(ModFlag,CardNumber);
    TimeVar = Time(CardNumber);
    ServoFunc(ExitMod);


    //Serial.println("  ");
    //Serial.println(APP_TotalNumberOfCars);
    //Serial.println("  ");

    
   



  }*/

  //
  Serial.println("MAINN function run successfully");
  //

}

void ServoFunc(int ThisMod){
  
  if(ThisMod == EntranceMod){

    for (pos = 90; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      Entrance_Servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15ms for the servo to reach the position
    }
    
    delay(3000);//---------------time between openning the gate and closing it------------------------
    
    for (pos = 0; pos <= 90; pos += 1) { // goes from 180 degrees to 0 degrees
      Entrance_Servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15ms for the servo to reach the position
    
    }

    }else if(ThisMod == ExitMod){

      for (pos = 90; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      Exit_Servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15ms for the servo to reach the position
    }

    
    ExitLcd(fees(TimeVar));
    
    //delay(3000);//---------------time between openning the gate and closing it------------------------
    
    for (pos = 0; pos <= 90; pos += 1) { // goes from 180 degrees to 0 degrees
      Exit_Servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15ms for the servo to reach the position
    }

    }

}

// The function responsible for calculating fees
int fees(int timeSec){
  
  int fees = timeSec*2;

  APP_Total_Profit += fees;
  
  return fees; 
  
}
//____________________________
void MainPathFunc(){

  int FuncVar = NumberOfAvailableSlots();
  //
 
  Serial.print("num of available slots :");
  Serial.println(FuncVar);
  //
  
  int i;
  for(i=4;i>=0;i--){
    if(Slots[i]==SlotAvailable){
      
      while( FuncVar <= NumberOfAvailableSlots() ){

        LEDPath(i);

      }
      
      break;

    }
  
  }

  //
  Serial.println("Main path function run successfully");
  //

} 
//____________________________
void segWrite(int n){
  ///Decimal-Binary Conversion Function

  //Turns off all LEDs
  digitalWrite(Dp, LOW);
  digitalWrite(Cp, LOW);
  digitalWrite(Bp, LOW);
  digitalWrite(Ap, LOW);

  ///Decimal Conversion
  if(n >= 8){
    digitalWrite(Dp, HIGH);
    n = n - 8 ;
  }
  if(n >= 4){
    digitalWrite(Cp, HIGH);
    n = n - 4;
  }
  if(n>=2){
    digitalWrite(Bp, HIGH);
    n = n - 2;
  }
  if(n>=1){
    digitalWrite(Ap, HIGH);
    n = n - 1;
  }
}
//function to print fees on the lcd 
int ExitLcd(int x){
  // turn on the backlight
  lcd.backlight();
  // tell the screen to write on the top row
  lcd.setCursor(0,0);
  lcd.print("Your fees are ");
  // tell the screen to write on the bottom row
  lcd.setCursor(12,1);
  // print the variable money amount 
  lcd.print(x); 
  lcd.print("$");
  delay(5500);
  lcd.clear();
}
int WhichCar(){

  int i;
  

  for(i=0;i<5;i++){

    if(Slots[i]!=Temp[i]){


     return i;


    }
  
  }

}