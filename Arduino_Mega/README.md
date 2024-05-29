# Parking Management System

This repository contains the code for an Arduino Mega-based Parking Management System. The system uses multiple sensors, including RFID readers, LDRs, and gas and flame detectors, to manage and monitor the parking lot. The system also includes features for emergency situations.

## Table of Contents

- [Parking Management System](#parking-management-system)
  - [Table of Contents](#table-of-contents)
  - [Hardware Components](#hardware-components)
  - [Wiring](#wiring)
  - [Libraries Used](#libraries-used)
  - [Code Structure](#code-structure)
  - [Setup](#setup)
  - [Usage](#usage)
  - [Contributing](#contributing)
  - [License](#license)

## Hardware Components

- Arduino Mega
- RC522 RFID Module (2 units)
- LDR Sensors (5 units)
- Gas Sensor (MQ-5)
- Flame Sensor
- Servo Motors (3 units)
- LEDs
- 7-Segment Display
- LCD Display (I2C)
- Various resistors, jumper wires, and breadboard

## Wiring

- **RFID Module 1**
  - SCK to Mega pin 52
  - MOSI to Mega pin 51
  - MISO to Mega pin 50
  - SS to Mega pin 7
  - RST to Mega pin 6

- **RFID Module 2**
  - SCK to Mega pin 52
  - MOSI to Mega pin 51
  - MISO to Mega pin 50
  - SS to Mega pin 10
  - RST to Mega pin 9

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

## Libraries Used

- [SPI](https://www.arduino.cc/en/reference/SPI)
- [MFRC522](https://github.com/miguelbalboa/rfid)
- [Servo](https://www.arduino.cc/en/Reference/Servo)
- [ArduinoJson](https://arduinojson.org/)
- [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)

## Code Structure

The main functionalities of the code include:
- Reading RFID cards for entrance and exit.
- Managing servo motors for gates.
- Monitoring available parking slots using LDR sensors.
- Handling emergency situations with gas and flame sensors.
- Displaying information on LCD and 7-segment displays.
- Communicating with an ESP32 module via Serial1 for data transmission.

## Setup

1. **Install Libraries**: Ensure you have all the required libraries installed in your Arduino IDE.
2. **Upload Code**: Upload the provided code to your Arduino Mega.
3. **Wire Components**: Connect all the hardware components as per the wiring instructions.
4. **Power Up**: Power up your Arduino Mega and connected components.

## Usage

- **Normal Operation**: The system will monitor the parking slots and manage the entrance and exit gates based on the RFID card readings.
- **Emergency Handling**: If the gas or flame sensor detects an emergency, all gates will open automatically, and an emergency light will flash.
- **Data Transmission**: The system will send parking data to an ESP32 module via Serial1.

## Contributing

Feel free to fork this repository and contribute by submitting a pull request. For major changes, please open an issue to discuss what you would like to change.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.