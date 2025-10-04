# 7Semi-RS485-Temperature-Humidity-Probe-Arduino-Library

This Arduino library provides an easy-to-use interface to communicate with **7Semi RS485 Temperature and Humidity Sensors** using the Modbus RTU protocol over RS485 (via a MAX485 or compatible module).

![Platform](https://img.shields.io/badge/platform-arduino-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Status](https://img.shields.io/badge/status-active-brightgreen.svg)

---

## 📦 Features

- Communicates with 7Semi RS485 Temp/Hum sensors over Modbus RTU
- Supports both temperature and humidity readings
- Allows sensor address configuration
- Works with hardware or software serial
- Plug-and-play integration with 7Semi industrial-grade RS485 sensor modules

---

## 🔧 Hardware Required

- 7Semi RS485 Temperature & Humidity Probe  
- RS485-to-TTL Converter (e.g., MAX485 module)  
- Arduino-compatible board (Uno, Mega, ESP32, STM32, etc.)  
- Jumper wires

---

## 🧪 Example Wiring

| RS485 Probe | MAX485 Module /  compatible module | Arduino Uno |
|-------------|----------------------------------- |-------------|
| A           | A                                  |             |
| B           | B                                  |             |
| VCC         | VCC                                | 5V          |
| GND         | GND                                | GND         |

| MAX485 Pin  | Arduino Pin |
|-------------|-------------|
| TX          | D10 (RX)    |
| RX          | D11 (TX)    |
| RST         | D2          |



---

## 🚀 Getting Started

### 1. Installation via Arduino Library Manager

1. Open the **Arduino IDE**
2. Go to:
   - `Sketch > Include Library > Manage Libraries…` (IDE 1.x), or  
   - Click the **Library Manager** icon 📚 in the sidebar (IDE 2.x)
3. Search:
   7Semi RS485 Temperature Humidity

