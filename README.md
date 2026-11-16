# 🤖 RAI26 – Autonomous Robot

<p align="center">
  <img src="https://img.shields.io/badge/RAI-2026-blue?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white" />
  <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" />
</p>

<p align="center">   An autonomous robotics project developed for the RAI 2026 Computer Programming Competition.   <br>   Designed to perform wall tracking, distance detection, and autonomous movement using Arduino-based control systems. </p>

---

## 📖 About The Project

**RAI26 Autonomous Robot** is an Arduino-based robotics project developed for the RAI 2026 Computer Programming Competition.

The robot uses multiple analog distance sensors to detect surrounding walls and obstacles. Based on sensor readings, the control system adjusts the speed of its left and right motors to maintain a target distance from the wall.

The firmware implements a PD-style control algorithm to improve movement accuracy and responsiveness.

### 🎯 Project Objectives

- Develop an autonomous robotic navigation system.
- Implement wall-following algorithms.
- Improve movement accuracy using PD control.
- Integrate distance sensors with motor control.
- Develop reliable real-time hardware and software interaction.

## ✨ Key Features

| Feature                  | Description                                        |
| :----------------------- | :------------------------------------------------- |
| Autonomous Wall Tracking | Follows either the left or right wall              |
| Distance Detection       | Measures distance using analog sensor readings     |
| PD Motor Control         | Adjusts motor speed based on tracking error        |
| Obstacle Detection       | Responds to front sensor readings                  |
| Dual Motor Control       | Independently controls left and right motors       |
| Buzzer System            | Provides startup sounds and warning signals        |
| Sensor Monitoring        | Displays sensor information through Serial Monitor |

## 🧰 Hardware & Components

The following components are identified from the current firmware. Exact hardware models should be added when confirmed.

| Component                | Function                           |
| :----------------------- | :--------------------------------- |
| Arduino-compatible board | Main controller                    |
| DC Motors                | Robot movement                     |
| Motor Driver             | Controls motor direction and speed |
| Left Distance Sensor     | Left-side distance measurement     |
| Right Distance Sensor    | Right-side distance measurement    |
| Front Distance Sensor    | Front obstacle detection           |
| Middle Sensor            | Additional analog sensor input     |
| Buzzer                   | Audio feedback                     |
| Battery                  | Power supply                       |

## 🔌 Pin Configuration

The following pin assignments are defined in the source code.

### Motor Driver

| Pin | Arduino Pin | Function              |
| :-- | :---------- | :-------------------- |
| ENA | D11         | Left motor PWM        |
| IN1 | D10         | Left motor direction  |
| IN2 | D8          | Left motor direction  |
| ENB | D6          | Right motor PWM       |
| IN3 | D9          | Right motor direction |
| IN4 | D5          | Right motor direction |

### Sensors

| Sensor  | Arduino Pin | Function              |
| :------ | :---------- | :-------------------- |
| LSensor | A0          | Left distance sensor  |
| RSensor | A1          | Right distance sensor |
| FSensor | A2          | Front distance sensor |
| MSensor | A5          | Middle sensor         |

### Buzzer

| Pin  | Arduino Pin |
| :--- | :---------- |
| BZ_A | D7          |
| BZ_B | D12         |

## 🧠 Control System

The robot uses sensor feedback to determine its movement and adjust motor speeds.

### 1. Wall Following

The firmware supports two wall-tracking functions:

- `Track_wall_L()` – Left wall tracking.
- `Track_wall_R()` – Right wall tracking.

The selected tracking function reads the corresponding distance sensor and calculates the motor correction.

### 2. PD Control Algorithm

The robot uses proportional and derivative correction to adjust its movement.

The control calculation is based on:

```cpp
error = Position - Target;

PowerMotor = (Kp * error) +
             (Kd * (error - lastError));
```

The motor speeds are adjusted depending on the calculated correction.

**Current control parameters:**

| Parameter        |            Value | Description              |
| :--------------- | ---------------: | :----------------------- |
| Base Speed       |              200 | Default motor speed      |
| Kp               |               30 | Proportional gain        |
| Kd               |               25 | Derivative gain          |
| Target Distance  |                9 | Target sensor distance   |
| Front Threshold  |             8 cm | Front obstacle threshold |
| Correction Limit | -80 to BaseSpeed | Motor correction range   |

### 3. Obstacle Detection

The front distance sensor is checked during wall tracking.

When the front distance is 8 cm or less and the selected side distance is below 20 cm, the robot performs a corrective motor movement to avoid the detected obstacle.

### 4. Sensor-Based Operation

The main loop checks the left and right distance sensors.

When either side sensor detects a distance of 5 cm or less, the firmware waits one second and checks again.

If the condition remains true, the robot activates the corresponding wall-tracking routine until the middle sensor reading is no longer above 450.

The motors then stop.

## 🔊 Buzzer System

The robot includes an audio feedback system.

| Function       | Description                                |
| :------------- | :----------------------------------------- |
| `startSound()` | Plays the startup sound sequence           |
| `beep()`       | Generates warning beeps                    |
| `sound()`      | Generates a sound at a specified frequency |
| `sweep()`      | Creates a frequency sweep                  |
| `vibrato()`    | Generates alternating frequencies          |

## 📂 Repository Structure

```text
RAI26-CP-PROJECT-AUTO/
│
├── RAI_COMPRO_AUTO.ino
│
├── README.md
│
└── LICENSE
```

## ⚙️ Getting Started

### Requirements

- Arduino IDE
- Arduino-compatible microcontroller
- USB programming cable
- Required sensors and motor driver
- DC motors and power supply

### Installation

**1. Clone the repository**

```bash
git clone https://github.com/TONMAIIII/RAI26-CP-PROJECT-AUTO.git
```

**2. Open the project**

Navigate to the project folder and open:

```text
RAI_COMPRO_AUTO.ino
```

**3. Configure Arduino IDE**

- Select the correct Arduino board.
- Select the appropriate COM port.
- Verify the pin connections.

**4. Upload the firmware**

Click Upload in Arduino IDE and wait for compilation and uploading to finish.

**5. Test the robot**

Check sensor readings, motor directions, wall tracking, and buzzer functionality.

## 🧪 Development Progress

- [x] Arduino firmware development
- [x] Motor direction and speed control
- [x] Analog sensor reading
- [x] Left wall tracking algorithm
- [x] Right wall tracking algorithm
- [x] PD-style motor correction
- [x] Buzzer sound system
- [ ] Hardware integration testing
- [ ] Sensor calibration
- [ ] Full autonomous navigation testing
- [ ] Competition testing

## 📸 Project Gallery

<p align="center">
&#x20; <i>Project photos, circuit diagrams, and testing videos will be added here.</i>
</p>

<h3 align="center">Auto Robot Design</h3>

<p align="center">
  <img src="assets/robot.jpg" width="100%" alt="Robot Design">
</p>

## 🚀 Future Improvements

- Improve sensor calibration and distance accuracy.
- Optimize PD control parameters.
- Improve obstacle avoidance.
- Reduce unnecessary motor delays.
- Improve navigation stability.
- Perform extensive real-world testing.

## 👨‍💻 Contributors

<p align="center">   Developed for the <b>RAI 2026 Computer Programming Competition</b>. </p>

| Contributor | Role                               |
| :---------- | :--------------------------------- |
| Mr. Yossarun Junkhiew    | Robotics Programming & Development |
| Mr. Nopasin Plailaharn   | Robotics Programming & Development |
| Mr. Kittipat Srilekart   | Robotics Programming & Development |

## 📄 License

This project is distributed under the license included in this repository. See the [LICENSE](LICENSE) file for details.

---

<p align="center">
&#x20; <b>RAI 2026 — Autonomous Robotics Project</b>
&#x20; <br>
&#x20; Built with Arduino, Engineering & Innovation. ⚡
</p>
