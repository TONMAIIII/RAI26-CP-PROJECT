# 🤖 2. Autonomous Robot

<details>
<summary><b>View Autonomous Robot Details</b></summary>

## Overview

The **RAI26 Autonomous Robot** is an Arduino-based robotics project designed to navigate its environment using distance sensors and motor control algorithms.

The robot uses multiple analog distance sensors to detect surrounding walls and obstacles. Based on sensor readings, the control system adjusts the speed of its left and right motors to maintain a target distance from the wall.

The firmware implements a PD-style control algorithm to improve movement accuracy and responsiveness.

## 🎯 Project Objectives

- Develop an autonomous robotic navigation system.
- Implement wall-following algorithms.
- Improve movement accuracy using PD control.
- Integrate distance sensors with motor control.
- Develop reliable real-time hardware and software interaction.

## ✨ Key Features

| Feature | Description |
|:---|:---|
| Autonomous Wall Tracking | Follows either the left or right wall |
| Distance Detection | Measures distance using analog sensor readings |
| PD Motor Control | Adjusts motor speed based on tracking error |
| Obstacle Detection | Responds to front sensor readings |
| Dual Motor Control | Independently controls left and right motors |
| Buzzer System | Provides startup sounds and warning signals |
| Sensor Monitoring | Displays sensor information through Serial Monitor |

## 🧰 Hardware & Components

The following components are identified from the current firmware. Exact hardware models should be added when confirmed.

| Component | Function |
|:---|:---|
| Arduino-compatible board | Main controller |
| DC Motors | Robot movement |
| Motor Driver | Controls motor direction and speed |
| Left Distance Sensor | Left-side distance measurement |
| Right Distance Sensor | Right-side distance measurement |
| Front Distance Sensor | Front obstacle detection |
| Middle Sensor | Additional analog sensor input |
| Buzzer | Audio feedback |
| Battery | Power supply |

## 🔌 Pin Configuration

The following pin assignments are defined in the source code.

### Motor Driver

| Pin | Arduino Pin | Function |
|:---|:---|:---|
| ENA | D11 | Left motor PWM |
| IN1 | D10 | Left motor direction |
| IN2 | D8 | Left motor direction |
| ENB | D6 | Right motor PWM |
| IN3 | D9 | Right motor direction |
| IN4 | D5 | Right motor direction |

### Sensors

| Sensor | Arduino Pin | Function |
|:---|:---|:---|
| LSensor | A0 | Left distance sensor |
| RSensor | A1 | Right distance sensor |
| FSensor | A2 | Front distance sensor |
| MSensor | A5 | Middle sensor |

### Buzzer

| Pin | Arduino Pin | Function |
|:---|:---|:---|
| BZ_A | D7 | Buzzer control |
| BZ_B | D12 | Buzzer control |

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

| Parameter | Value | Description |
|:---|---:|:---|
| Base Speed | 200 | Default motor speed |
| Kp | 30 | Proportional gain |
| Kd | 25 | Derivative gain |
| Target Distance | 9 | Target sensor distance |
| Front Threshold | 8 cm | Front obstacle threshold |
| Correction Limit | -80 to BaseSpeed | Motor correction range |

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

| Function | Description |
|:---|:---|
| `startSound()` | Plays the startup sound sequence |
| `beep()` | Generates warning beeps |
| `sound()` | Generates a sound at a specified frequency |
| `sweep()` | Creates a frequency sweep |
| `vibrato()` | Generates alternating frequencies |

## 💻 Software & Programming

The Autonomous Robot firmware is developed using **Arduino IDE** with C++.

The program handles sensor readings, motor control, wall tracking, obstacle detection, and buzzer operations.

**Project file:** `RAI_COMPRO_AUTO.ino`

</details>
