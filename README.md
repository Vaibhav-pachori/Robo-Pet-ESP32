# Robo-Pet-ESP32

An autonomous robot pet project based on the ESP32 microcontroller. The robot uses an ultrasonic sensor to detect obstacles, a servo motor to scan the environment, and a motor driver to control movement.

## Features
- **Obstacle Avoidance**: Utilizes an ultrasonic sensor to detect objects.
  - Moves forward if the path is clear (> 25 cm).
  - Stops if an object is within 15 cm to 25 cm.
  - Reverses if an object is too close (< 15 cm).
- **Environment Scanning**: The ultrasonic sensor is mounted on a servo motor that sweeps back and forth (between 20° and 160°) to give the robot a wider field of view.
- **ESP32 Powered**: Takes advantage of the ESP32's processing power and precise PWM capabilities.

## Hardware Components
- ESP32 Development Board
- Ultrasonic Sensor (HC-SR04)
- Servo Motor (e.g., SG90)
- Motor Driver (e.g., TB6612FNG or L298N)
- 2x DC Motors & Wheels

## Pin Mapping

### Ultrasonic Sensor
- **TRIG_PIN**: 4
- **ECHO_PIN**: 18

### Servo Motor
- **SERVO_PIN**: 19

### Motor Driver
- **Motor A**
  - AIN1: 14
  - AIN2: 27
  - PWMA: 26
- **Motor B**
  - BIN1: 33
  - BIN2: 25
  - PWMB: 32
- **Standby (STBY)**: 13

## Software Dependencies
- [ESP32Servo Library](https://github.com/madhephaestus/ESP32Servo) - Required for stable PWM control of the servo motor on the ESP32.

## Installation
1. Install the [Arduino IDE](https://www.arduino.cc/en/software) and set up the [ESP32 board manager](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).
2. Open the Library Manager in the Arduino IDE and install the **ESP32Servo** library by Kevin Harrington.
3. Open the `RoboPet.ino` file in the Arduino IDE.
4. Select your specific ESP32 board and the correct COM port.
5. Compile and upload the code to your ESP32.
