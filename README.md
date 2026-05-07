# 🤖 RoboPet — ESP32 Obstacle-Avoiding Robot

An autonomous obstacle-avoiding robot built on the **ESP32** microcontroller. RoboPet uses a sweeping ultrasonic sensor mounted on a servo to continuously scan its environment and react in real time — moving forward when the path is clear, stopping when something is close, and reversing when an obstacle is detected nearby.

---

## 📸 Overview

RoboPet mimics the curiosity of a small pet — always scanning ahead, cautiously navigating its surroundings without any human input.

---

## ⚙️ Hardware Requirements

| Component | Details |
|---|---|
| Microcontroller | ESP32 (any standard dev board) |
| Ultrasonic Sensor | HC-SR04 (Trig: GPIO 4, Echo: GPIO 18) |
| Servo Motor | Standard 5V servo (Signal: GPIO 19) |
| Motor Driver | TB6612FNG or similar dual H-bridge |
| DC Motors | 2× TT gear motors |
| Power Supply | 7.4V LiPo or 2×18650 battery pack |

### Motor Driver Wiring

| Motor Driver Pin | ESP32 GPIO |
|---|---|
| AIN1 | 14 |
| AIN2 | 27 |
| PWMA | 26 |
| BIN1 | 33 |
| BIN2 | 25 |
| PWMB | 32 |
| STBY | 13 |

---

## 📦 Dependencies

Install the following library via the **Arduino Library Manager** or PlatformIO:

- [`ESP32Servo`](https://github.com/madhephaestus/ESP32Servo) — Servo control for ESP32

---

## 🚀 Getting Started

1. **Clone this repository**
   ```bash
   git clone https://github.com/Vaibhav-pachori/Robo-Pet-ESP32.git
   cd Robo-Pet-ESP32
   ```

2. **Open in Arduino IDE** (or PlatformIO)
   - Select your ESP32 board from *Tools → Board*
   - Select the correct COM port

3. **Install dependencies**
   - Search for `ESP32Servo` in the Library Manager and install it

4. **Upload the sketch**
   - Click *Upload* and open the Serial Monitor at `115200` baud

---

## 🧠 How It Works

The servo sweeps left and right continuously, taking an ultrasonic distance reading at each step.

| Distance | Behavior |
|---|---|
| < 15 cm | Move **backward** (obstacle too close) |
| 15 – 25 cm | **Stop** (cautious zone) |
| > 25 cm | Move **forward** (path is clear) |

The servo sweeps between **20° and 160°** (±70° from center) in 1° increments for smooth, continuous scanning.

---

## 🔧 Tunable Parameters

You can adjust these constants at the top of the sketch to fine-tune behaviour for your build:

```cpp
const int SERVO_CENTER = 90;   // Servo neutral position
const int SWEEP_RANGE  = 70;   // Half-sweep angle (degrees)
const int SERVO_STEP   = 1;    // Step size per loop iteration
const int MOTOR_SPEED  = 120;  // Base PWM speed (0–255)
int LEFT_SPEED         = 160;  // Left motor trim
int RIGHT_SPEED        = 200;  // Right motor trim
```

> **Tip:** If your robot drifts left or right, adjust `LEFT_SPEED` and `RIGHT_SPEED` until it tracks straight.

---

## 📁 Project Structure

```
Robo-Pet-ESP32/
├── RoboPet.ino       # Main Arduino sketch
└── README.md
```

---

## 🛠️ Troubleshooting

**Robot not moving?**
- Check that `STBY` pin is wired and `digitalWrite(STBY, HIGH)` is present in `setup()`.
- Verify your motor driver power supply is connected separately from the ESP32's 3.3V rail.

**Servo jittering?**
- Ensure the servo has a stable 5V supply. Powering it from the ESP32's onboard 3.3V pin will cause instability.

**Distance readings erratic?**
- Add a small capacitor (10–100µF) across the HC-SR04's VCC and GND pins.
- Ensure no obstacles are within 2 cm of the sensor at startup.

---

## 📄 License

This project is open source under the [MIT License](LICENSE).

---

## 🙌 Contributing

Pull requests are welcome! If you improve the movement logic, add turning behaviour, or integrate additional sensors, feel free to open a PR.
