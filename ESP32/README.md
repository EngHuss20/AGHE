# ESP32 Communication System

This folder contains the code for an ESP32-based communication system that reads data from a secondary microcontroller via Serial2, parses JSON data, and uploads the parsed data to ThingSpeak. The device used is an ESP32 DevKit V4.

## Overview

The ESP32 reads JSON-formatted data from a secondary device through the Serial2 interface. The JSON data is parsed and the extracted values are stored in an array. These values are then uploaded to ThingSpeak for remote monitoring.

## Hardware Setup

1. **ESP32 DevKit V4**:
   - RX2 (GPIO 16, Green wire)
   - TX2 (GPIO 17, Blue wire)

2. **Connections**:
   - Connect RX2 (GPIO 16) of the ESP32 to the TX pin of the secondary device.
   - Connect TX2 (GPIO 17) of the ESP32 to the RX pin of the secondary device.
   - Ensure both devices share a common ground.

## Software Setup

### Libraries Required

- `ArduinoJson`
- `WiFi`
- `ThingSpeak`

You can install these libraries via the Arduino Library Manager.

### Wifi Credentials

Ensure to update your WiFi SSID and password in the code:

```cpp
const char* ssid = "YourNetworkSSID";
const char* password = "YourNetworkPassword";
```

### ThingSpeak Credentials

Update your ThingSpeak channel number and Write API Key:

```cpp
unsigned long myChannelNumber = YourChannelNumber;
const char* myWriteAPIKey = "YourWriteAPIKey";
```

### Code Explanation

- **Initialization**:
  - Initializes Serial communication at 115200 baud for debugging.
  - Initializes Serial2 communication at 9600 baud for receiving data.
  - Connects to WiFi and initializes the ThingSpeak client.

- **Main Loop**:
  - Waits for incoming data on Serial2.
  - Reads the JSON data and parses it into a `StaticJsonDocument`.
  - Extracts values from the JSON document and stores them in the `Data` array.
  - Sends these values to ThingSpeak.

### Sample Data

The following keys are expected in the incoming JSON data:

- `Slot1`
- `Slot2`
- `Slot3`
- `Slot4`
- `Slot5`
- `Emergency`
- `TotalProfit`
- `TotalNumberofCars`

### Example JSON Input

```json
{
  "Slot1": 1,
  "Slot2": 1,
  "Slot3": 1,
  "Slot4": 1,
  "Slot5": 1,
  "Emergency": 1,
  "TotalProfit": 69,
  "TotalNumberofCars": 500
}
```

### Sample Output on Serial Monitor

```plaintext
Connecting to YourNetworkSSID
...
WiFi connected
IP address: 192.168.1.100
Channel update successful.
```

### Error Handling

If there's an error parsing the JSON or updating the ThingSpeak channel, an error message will be printed on the Serial Monitor.

## Usage

1. **Upload the Code**: Upload the provided code to the ESP32 using the Arduino IDE.
2. **Monitor Serial Output**: Open the Serial Monitor at a baud rate of 115200 to view the debug messages.
3. **Send Data**: Send JSON-formatted data from the secondary device to the ESP32 via Serial2.
4. **ThingSpeak**: Check the ThingSpeak channel to see the uploaded data.

## License

This project is licensed under the MIT License.

---

This README file provides a comprehensive guide to set up and run the ESP32-based communication system for reading JSON data via Serial2 and uploading it to ThingSpeak. Make sure to update the placeholders with your actual credentials and test the system thoroughly.
