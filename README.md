# Parking Management System

This project consists of two main components: an ESP32-based communication system and an Arduino Mega-based parking management system. The ESP32 module handles data transmission to ThingSpeak for remote monitoring, while the Arduino Mega manages the physical aspects of the parking lot, such as vehicle entry and exit, slot monitoring, and emergency handling.

## Project Structure

- **ESP32 Communication System**: Reads data from the Arduino Mega, parses JSON data, and uploads it to ThingSpeak.
- **Arduino Mega Parking Management System**: Manages RFID entry/exit, slot monitoring, and emergency detection.

## Overview

The Parking Management System uses sensors and communication modules to provide real-time data on parking slot availability, emergency situations, and overall parking lot statistics. The data is collected by the Arduino Mega and sent to the ESP32, which then uploads the data to ThingSpeak for remote monitoring.

## Components

1. **ESP32 DevKit V4**
2. **Arduino Mega**
3. **RC522 RFID Modules** (2 units)
4. **LDR Sensors** (5 units)
5. **Gas Sensor (MQ-5)**
6. **Flame Sensor**
7. **Servo Motors** (3 units)
8. **LEDs**
9. **7-Segment Display**
10. **LCD Display (I2C)**
11. **Various resistors, jumper wires, and breadboard**

## Hardware Setup

### ESP32 Communication System

1. **ESP32 DevKit V4**:
   - RX2 (GPIO 16, Green wire)
   - TX2 (GPIO 17, Blue wire)

2. **Connections**:
   - Connect RX2 (GPIO 16) of the ESP32 to the TX pin of the Arduino Mega.
   - Connect TX2 (GPIO 17) of the ESP32 to the RX pin of the Arduino Mega.
   - Ensure both devices share a common ground.

### Arduino Mega Parking Management System

#### RFID Module 1
- **SCK** to Mega pin 52
- **MOSI** to Mega pin 51
- **MISO** to Mega pin 50
- **SS** to Mega pin 7
- **RST** to Mega pin 6

#### RFID Module 2
- **SCK** to Mega pin 52
- **MOSI** to Mega pin 51
- **MISO** to Mega pin 50
- **SS** to Mega pin 10
- **RST** to Mega pin 9

#### Other Connections
- **LDR Sensors**: Connected to analog pins A0 to A4
- **Gas Sensor (MQ-5)**: Connected to analog pin A5
- **Flame Sensor**: Connected to digital pin A6
- **Servo Motors**:
  - Entrance Servo to pin 3
  - Exit Servo to pin 4
  - Emergency Servo to pin 2
- **LEDs**: Connected to digital pins 22 to 32
- **7-Segment Display**: Connected to digital pins 33 to 36
- **Emergency Light**: Connected to digital pin 45
- **LCD Display**: Connected via I2C

## Software Setup

### Libraries Required

For the ESP32:
- `ArduinoJson`
- `WiFi`
- `ThingSpeak`

For the Arduino Mega:
- `SPI`
- `MFRC522`
- `Servo`
- `ArduinoJson`
- `LiquidCrystal_I2C`

These libraries can be installed via the Arduino Library Manager.

### WiFi and ThingSpeak Credentials for ESP32

Update your WiFi SSID and password in the ESP32 code:

```cpp
const char* ssid = "YourNetworkSSID";
const char* password = "YourNetworkPassword";
```

Update your ThingSpeak channel number and Write API Key:

```cpp
unsigned long myChannelNumber = YourChannelNumber;
const char* myWriteAPIKey = "YourWriteAPIKey";
```

## Code Explanation

### ESP32 Communication System

- **Initialization**:
  - Initializes Serial communication at 115200 baud for debugging.
  - Initializes Serial2 communication at 9600 baud for receiving data from Arduino Mega.
  - Connects to WiFi and initializes the ThingSpeak client.

- **Main Loop**:
  - Waits for incoming data on Serial2.
  - Reads the JSON data and parses it into a `StaticJsonDocument`.
  - Extracts values from the JSON document and stores them in the `Data` array.
  - Sends these values to ThingSpeak.

### Arduino Mega Parking Management System

- **Initialization**:
  - Initializes Serial communication for debugging.
  - Sets up the RFID modules, sensors, servos, and display.
  - Connects to the ESP32 module via Serial1 for data transmission.

- **Main Loop**:
  - Reads RFID cards for vehicle entry and exit.
  - Monitors parking slots using LDR sensors.
  - Checks for emergency situations using gas and flame sensors.
  - Controls gate servos and updates displays.
  - Transmits data to the ESP32 module.

## Usage

1. **Upload the Code**:
   - Upload the provided code to the Arduino Mega and ESP32 using the Arduino IDE.
2. **Wire Components**:
   - Connect all the hardware components as per the wiring instructions.
3. **Power Up**:
   - Power up your Arduino Mega, ESP32, and connected components.
4. **Monitor Serial Output**:
   - Open the Serial Monitor at a baud rate of 115200 to view the debug messages.
5. **Send Data**:
   - Send JSON-formatted data from the Arduino Mega to the ESP32 via Serial2.
6. **ThingSpeak**:
   - Check the ThingSpeak channel to see the uploaded data.

## License

This project is licensed under the MIT License.

---

This README file provides a comprehensive guide to set up and run the Parking Management System. Ensure to connect all components correctly, update the necessary credentials, and test the system thoroughly.