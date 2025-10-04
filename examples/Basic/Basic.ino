/***************************************************************
 * @file       BasicRead.ino
 * @brief      Demonstrates reading temperature and humidity 
 *             using the 7Semi RS485 Temperature-Humidity Sensor
 *
 * This example initializes communication with the RS485-based
 * 7Semi temperature and humidity probe using Modbus RTU protocol.
 *
 * Key features demonstrated:
 * - Serial communication over RS485
 * - Configuring Modbus parameters (slave ID, registers, delay)
 * - Reading temperature (°C) and relative humidity (%RH)
 * - Formatted fixed-width printing for clarity
 *
 * Sensor Configuration:
 * - Interface     : RS485 (Modbus RTU)
 * - Baud Rate     : 9600 bps
 * - Registers     : Temp & RH (2 registers)
 * - Address       : Default Modbus address = 1
 * - Protocol Gap  : 800 μs (can be adjusted)
 *
 * Connections:
 * - TX (MAX485) → Arduino RX (e.g., D10)
 * - RX (MAX485) → Arduino TX (e.g., D11)
 * - RST       → Digital pin (e.g., D2)
 * - VCC / GND   → 5V / GND
 *
 * Library     : 7Semi-RS485-Temperature-Humidity-Probe-Arduino-Library
 * Author      : 7Semi
 * Version     : 1.0
 * Date        : 04 October 2025
 * License     : MIT
 ***************************************************************/


#include <7Semi_RS485_Tem_Hum.h>

// Use alias that mirrors 7Semi naming while staying C++-legal
_7SemiTH TH;

static void printFixed(float v, uint8_t width, uint8_t prec) {
  char s[16];
  dtostrf(v, width, prec, s);
  Serial.print(s);
}

void setup() {
  Serial.begin(115200);

  /** 
   - begin(rxPin, txPin, rtsPin, baud)
   - Default pins below are examples; change to match your hardware
  */
  TH.begin(10, 11, 2, 9600);

  /**
   - Modbus settings
   - setSlaveId: address of the RS485 sensor
   - setStartAddress: first register (0x0000 or 0x0001 depending on your map)
   - setNumRegs: number of registers to read (2 for T+RH)
   - setTurnaroundUs: inter-frame gap (us) to match device timing
  */
  TH.setSlaveId(1);
  TH.setStartAddress(0x0000); // set 0x0001 if your map is 1-based
  TH.setNumRegs(2);
  TH.setTurnaroundUs(800);
}

void loop() {
  float t, rh;
  if (TH.readData(t, rh)) {
    Serial.print(F("Temperature: ")); printFixed(t, 6, 2); Serial.print(F(" °C    "));
    Serial.print(F("Humidity: "));    printFixed(rh, 6, 2); Serial.println(F(" %RH"));
  } else {
    Serial.println(F("No response"));
  }
  delay(1000);
}
