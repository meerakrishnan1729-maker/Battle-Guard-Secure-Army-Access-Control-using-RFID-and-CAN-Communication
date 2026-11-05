# 🔐 BattleGuard – Secure Army Access Control Using RFID and CAN Communication

## 📌 Project Overview

**BattleGuard** is a multi-ECU embedded security system designed to provide secure access control for restricted areas such as army bases and military facilities. The system uses RFID-based authentication to identify authorized personnel and controls gate access through CAN communication between multiple Electronic Control Units (ECUs).

The system is developed using the **ARM7 LPC2129 microcontroller** and Embedded C. It integrates an EM-18 RFID reader, CAN communication, an LCD display, an SG90 servo motor, a GSM module, an LED, and a buzzer.

The system grants access to authorized RFID cards and activates security alerts when an unauthorized card is detected.

---

## 🎯 Project Objectives

- Implement RFID-based authentication for secure access control.
- Establish communication between multiple ECUs using the CAN protocol.
- Automate gate operation using an SG90 servo motor.
- Display authentication status on an LCD.
- Detect unauthorized access attempts.
- Generate visual and audible alerts using an LED and buzzer.
- Send SMS notifications through a GSM module when unauthorized access is detected.

---

## ⚙️ Hardware Components

| Component | Purpose |
|---|---|
| ARM7 LPC2129 Microcontroller | Main controller for authentication and system operation |
| EM-18 RFID Reader | Reads RFID card/tag identification numbers |
| SG90 Servo Motor | Controls the access gate |
| GSM Module | Sends SMS alerts for unauthorized access |
| 20×4 LCD Display | Displays RFID and access status |
| LED | Provides visual security alerts |
| Buzzer | Provides audible security alerts |
| CAN Interface | Enables communication between the three ECUs |

---

## 💻 Software and Technologies

- Embedded C
- ARM7 LPC2129
- UART Communication
- CAN Communication
- PWM-based Servo Control
- GPIO Interfacing
- LCD Interfacing
- Keil µVision
- Flash Magic

---

## 🏗️ System Architecture

The project is designed using three independent ECUs connected through the CAN communication network.

### ECU 1 – Main Controller / Transmitter

The first ECU acts as the main authentication unit.

Responsibilities:

- Receives RFID data from the EM-18 reader through UART0.
- Compares the received RFID ID with the authorized RFID ID.
- Displays authentication results on the LCD.
- Sends CAN messages to the other ECUs based on the authentication result.
- Uses the GSM module through UART1 to send SMS alerts for unauthorized access.

### ECU 2 – Gate Control / CAN Receiver

The second ECU is responsible for controlling the access gate.

Responsibilities:

- Receives authentication messages through CAN communication.
- Activates the SG90 servo motor when valid access is granted.
- Opens and closes the gate based on the received command.

### ECU 3 – Security Alert / CAN Receiver

The third ECU handles unauthorized access alerts.

Responsibilities:

- Receives alert messages through CAN communication.
- Activates the LED when unauthorized access is detected.
- Activates the buzzer to generate an audible alert.

### Architecture Diagram

```text
                 RFID CARD / TAG
                       |
                       v
                EM-18 RFID Reader
                       |
                     UART0
                       |
                       v
             +---------------------+
             |      ECU 1          |
             |  LPC2129 Controller |
             |                     |
             | RFID Authentication |
             |    LCD Display      |
             |    GSM Module       |
             +---------------------+
                       |
                 CAN Communication
                  /            \
                 /              \
                v                v
       +----------------+  +----------------+
       |     ECU 2      |  |     ECU 3      |
       |  CAN Receiver  |  |  CAN Receiver  |
       |                |  |                |
       | LPC2129        |  | LPC2129        |
       | Servo Motor    |  | LED & Buzzer   |
       +----------------+  +----------------+
                |                 |
                v                 v
           Gate Control       Security Alert
```

---

## 🔄 Working Principle

### 1. RFID Detection

When an RFID card or tag is brought near the EM-18 RFID reader, the reader detects its identification number and transmits the data to the main LPC2129 controller through UART communication.

### 2. Authentication

The main controller receives the RFID data and compares it with the stored authorized RFID identification number.

The system supports authorized RFID identification, while any unregistered RFID card is treated as unauthorized.

### 3. Authorized Access

When a valid RFID card is detected:

1. The controller identifies the card as authorized.
2. The LCD displays an access-granted message.
3. A CAN message is transmitted to ECU 2.
4. ECU 2 receives the message and controls the SG90 servo motor.
5. The gate opens to allow access and subsequently returns to its closed position.

### 4. Unauthorized Access

When an invalid RFID card is detected:

1. The controller identifies the card as unauthorized.
2. The LCD displays an access-denied message.
3. A CAN alert message is transmitted to ECU 3.
4. ECU 3 activates the LED and buzzer.
5. The GSM module sends an SMS notification to the concerned authority.
6. The gate remains closed.

---

## 📡 Communication Protocols

### UART Communication

UART is used for serial communication between the main controller and external modules.

- **UART0:** Communication with the EM-18 RFID reader.
- **UART1:** Communication with the GSM module.

### CAN Communication

The Controller Area Network (CAN) protocol is used for communication between the three LPC2129-based ECUs.

The main controller transmits authentication-related messages, and the receiving ECUs perform their respective operations based on the received commands.

### PWM Control

PWM is used to control the SG90 servo motor connected to the gate-control ECU. By varying the PWM pulse width, the servo motor position is controlled to open and close the gate.

---

## 🚀 Key Features

- RFID-based access authentication.
- Three-ECU distributed control architecture.
- CAN-based communication between controllers.
- Automatic gate operation using a servo motor.
- Real-time authentication status on LCD.
- Unauthorized access detection.
- LED and buzzer-based security alerts.
- GSM-based SMS notification.
- Independent gate-control and alert-control ECUs.

---

## 📂 Project Structure

The firmware is organized into separate source and header files for modular development.

```text
BattleGuard/
│
├── Transmitter/
│   ├── mainTX.c
│   ├── can2.c
│   ├── can2.h
│   ├── uart.c
│   ├── uart.h
│   ├── lcd.c
│   ├── lcd.h
│   ├── gsm.c
│   ├── gsm.h
│   └── delay.h
│
├── Receiver_Servo/
│   ├── mainRX.c
│   ├── can2.c
│   ├── can2.h
│   └── delay.h
│
├── Receiver_Alert/
│   ├── mainRX.c
│   ├── can2.c
│   ├── can2.h
│   └── delay.h
│
└── README.md
```

*Note: The folder and file names above are an illustrative organization. Adjust them to match the actual files in the repository.*

---

## 🛠️ Development and Setup

1. Install Keil µVision.
2. Create or open the LPC2129 project.
3. Add the required `.c` and `.h` files to the respective ECU projects.
4. Configure the microcontroller peripherals for UART, CAN, GPIO, LCD, and PWM as required.
5. Compile each ECU firmware separately.
6. Flash the generated HEX files into the respective LPC2129 controllers using Flash Magic.
7. Connect the three ECUs through the CAN network.
8. Connect the RFID reader, GSM module, LCD, servo motor, LED, and buzzer to their respective controllers.
9. Power up the system and test it using authorized and unauthorized RFID cards.

---

## 📈 Applications

- Military base access control.
- Restricted-area security systems.
- Secure entry management.
- Industrial access control.
- Multi-controller embedded security applications.

---

## 🔮 Future Improvements

- Maintain access logs with timestamps.
- Support multiple authorized RFID cards.
- Add EEPROM-based storage for authorized RFID IDs.
- Integrate additional security sensors.
- Implement a centralized monitoring system.
- Improve authentication using additional security mechanisms.

---

## 📚 Learning Outcomes

This project provided practical experience in:

- ARM7 LPC2129 microcontroller programming.
- Embedded C development.
- UART and CAN protocol implementation.
- RFID and GSM module interfacing.
- PWM-based servo motor control.
- LCD and GPIO interfacing.
- Multi-ECU communication and coordination.
- Embedded hardware debugging and integration.

---

## 👩‍💻 Project Information

**Project Name:** BattleGuard – Secure Army Access Control Using RFID and CAN Communication

**Controller:** ARM7 LPC2129

**Programming Language:** Embedded C

**Architecture:** Three-ECU Distributed Embedded System

**Communication:** UART and CAN

**Development Environment:** Keil µVision

---

*BattleGuard demonstrates the integration of RFID authentication, CAN-based multi-ECU communication, automatic gate control, and GSM-based security alerts in an embedded access-control application.*
