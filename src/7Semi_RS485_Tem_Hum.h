#ifndef _7SEMI_RS485_TEM_HUM_H_
#define _7SEMI_RS485_TEM_HUM_H_

#include <Arduino.h>
#include <SoftwareSerial.h>

class RS485TH_7Semi {
public:
  RS485TH_7Semi();
  void begin(uint8_t rxPin, uint8_t txPin, uint8_t rtsPin, uint32_t baud);
  void setSlaveId(uint8_t id);
  void setStartAddress(uint16_t addr);
  void setNumRegs(uint16_t regs);
  void setTurnaroundUs(uint16_t us);
  bool readData(float &temperature, float &humidity);
private:
  uint8_t _slaveId, _rts;
  uint16_t _startAddr, _numRegs;
  uint16_t _turnaround;
  SoftwareSerial* _rs485;
  void rs485_tx(bool on);
  uint16_t crc16(const uint8_t* d, uint8_t n);
};

// Alias for backwards compatibility with sketches expecting a 7Semi-style name
using RS485TH_7Semi = RS485TH_7Semi;
#endif