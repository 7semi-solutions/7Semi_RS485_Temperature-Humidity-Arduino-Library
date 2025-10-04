#include <7Semi_RS485_Tem_Hum.h>

RS485TH_7Semi::RS485TH_7Semi() {}

void RS485TH_7Semi::begin(uint8_t rxPin, uint8_t txPin, uint8_t rtsPin, uint32_t baud) {
  _rs485 = new SoftwareSerial(rxPin, txPin);
  _rs485->begin(baud);
  _rts = rtsPin;
  pinMode(_rts, OUTPUT);
  digitalWrite(_rts, LOW);
  _turnaround = 800;
}

void RS485TH_7Semi::setSlaveId(uint8_t id) { _slaveId = id; }
void RS485TH_7Semi::setStartAddress(uint16_t addr) { _startAddr = addr; }
void RS485TH_7Semi::setNumRegs(uint16_t regs) { _numRegs = regs; }
void RS485TH_7Semi::setTurnaroundUs(uint16_t us) { _turnaround = us; }

void RS485TH_7Semi::rs485_tx(bool on) {
  digitalWrite(_rts, on ? HIGH : LOW);
  delayMicroseconds(120);
}

uint16_t RS485TH_7Semi::crc16(const uint8_t* d, uint8_t n) {
  uint16_t c = 0xFFFF;
  for (uint8_t i = 0; i < n; i++) {
    c ^= d[i];
    for (uint8_t b = 0; b < 8; b++) c = (c & 1) ? (c >> 1) ^ 0xA001 : (c >> 1);
  }
  return c;
}

bool RS485TH_7Semi::readData(float &temperature, float &humidity) {
  uint8_t req[8];
  req[0] = _slaveId;
  req[1] = 0x03;
  req[2] = (_startAddr >> 8);
  req[3] = (_startAddr & 0xFF);
  req[4] = (_numRegs >> 8);
  req[5] = (_numRegs & 0xFF);
  uint16_t c = crc16(req, 6);
  req[6] = (uint8_t)(c & 0xFF);
  req[7] = (uint8_t)(c >> 8);

  rs485_tx(true);
  _rs485->write(req, 8);
  _rs485->flush();
  delayMicroseconds(_turnaround);
  rs485_tx(false);

  uint8_t rx[16]; int n = 0;
  unsigned long t0 = millis();
  while (millis() - t0 < 1000) {
    while (_rs485->available()) {
      if (n < sizeof(rx)) rx[n++] = _rs485->read();
    }
  }

  if (n >= 9 && rx[0] == _slaveId && rx[1] == 0x03) {
    uint16_t crc_calc = crc16(rx, n - 2);
    uint16_t crc_recv = rx[n-2] | (rx[n-1] << 8);
    if (crc_calc == crc_recv) {
      int16_t t_x100 = (int16_t)((rx[3] << 8) | rx[4]);
      uint16_t rh_x100 = (uint16_t)((rx[5] << 8) | rx[6]);
      temperature = t_x100 / 100.0f;
      humidity = rh_x100 / 100.0f;
      return true;
    }
  }
  return false;
}
