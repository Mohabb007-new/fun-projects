# Arduino Home Automation Robot

This project is an Arduino-based home automation robot that integrates multiple sensors and modules to perform tasks such as timekeeping, temperature sensing, flame detection, automation, and basic calculations using an IR remote.

## Description

The robot is designed to demonstrate a small-scale home automation system. It interacts with its environment using various sensors and modules, allowing it to display time, measure temperature and humidity, detect flames, and perform automated actions based on IR remote commands. The project showcases the integration of hardware components and software to create a multifunctional system.

## Features

- Timekeeping using the DS1302 RTC module.
- Temperature and humidity sensing with the DHT11 sensor.
- Flame detection with a flame sensor.
- IR remote control for automation and calculations.
- LCD display for real-time data visualization and interaction prompts.

## Hardware

- **Microcontroller**: Arduino (compatible board)
- **Modules**:
    - DS1302 RTC module
    - DHT11 temperature and humidity sensor
    - Flame sensor
    - IR receiver module
    - 16x2 LCD with I2C interface
- **Other Components**:
    - Relay module
    - Buzzer
    - Potentiometer
- **Power**: Recommended battery voltage/current based on Arduino board specifications.

## Wiring

- **Pin Assignments**:
    - IR Receiver: D11
    - Relay: D8
    - Buzzer: D4
    - DHT11 Sensor: D2
    - Flame Sensor: A3
    - DS1302 RTC:
        - CE: D5
        - IO: D6
        - SCLK: D7
    - LCD: I2C interface (address 0x27)
- Ensure a common ground and appropriate voltage levels for all components.

## Software / Dependencies

- **Arduino IDE**: Version 1.8.x or later
- **Libraries**:
    - `DS1302` — For interfacing with the RTC module.
    - `Wire` — For I2C communication.
    - `LiquidCrystal_I2C` — For controlling the LCD.
    - `SimpleDHT` — For reading data from the DHT11 sensor.
    - `IRremote` — For decoding IR remote signals.

## Installation / Upload

1. Install the required libraries in the Arduino IDE.
2. Open the `robot.ino` file in the Arduino IDE.
3. Select the appropriate board and COM port.
4. Upload the code to the Arduino board.

## Configuration

- **Adjustable Constants**:
    - `RECV_PIN = 11` (IR receiver pin)
    - `relay = 8` (Relay control pin)
    - `pinDHT11 = 2` (DHT11 data pin)
    - `potpin = A3` (Potentiometer pin)
    - `Beep = 4` (Buzzer pin)

## Usage

1. Power on the robot.
2. The LCD will display the current time and temperature.
3. Use the IR remote to interact with the robot (e.g., turn on/off the relay, perform calculations).
4. The robot will alert you if the temperature exceeds a threshold or if a flame is detected.

## Troubleshooting

- **Library problems**: I faced a lot of problems whn impoting the libraries. You need to test and  debug the code while changing functions in the main sensor libraries. Dm me to send you the modified functions.
- **No LCD Display**: Check I2C connections and address (default: 0x27).
- **IR Remote Not Responding**: Verify the IR receiver wiring and ensure the remote is functional.
- **Sensor Readings Incorrect**: Check sensor connections and ensure they are powered correctly.
