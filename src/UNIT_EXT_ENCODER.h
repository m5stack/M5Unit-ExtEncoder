#ifndef __UNIT_EXT_ENCODER_H
#define __UNIT_EXT_ENCODER_H

#include "Arduino.h"
#include "Wire.h"

#define UNIT_EXT_ENCODER_ADDR                 0x59
#define UNIT_EXT_ENCODER_ENCODER_REG          0x00
#define UNIT_EXT_ENCODER_METER_REG            0x10
#define UNIT_EXT_ENCODER_METER_STRING_REG     0x20
#define UNIT_EXT_ENCODER_RESET_REG            0x30
#define UNIT_EXT_ENCODER_PERIMETER_REG        0x40
#define UNIT_EXT_ENCODER_PULSE_REG            0x50
#define UNIT_EXT_ENCODER_ZERO_PULSE_VALUE_REG 0x60
#define FIRMWARE_VERSION_REG                  0xFE
#define I2C_ADDRESS_REG                       0xFF

class UNIT_EXT_ENCODER {
   private:
    uint8_t _addr;
    TwoWire* _wire;
    uint8_t _scl;
    uint8_t _sda;
    uint8_t _speed;
    void writeBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);
    void readBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);

   public:
    bool begin(TwoWire* wire = &Wire, uint8_t addr = UNIT_EXT_ENCODER_ADDR,
               uint8_t sda = 21, uint8_t scl = 22, uint32_t speed = 100000L);
    uint32_t getEncoderValue(void);
    uint32_t getZeroPulseValue(void);
    uint32_t getMeterValue(void);
    void getMeterString(char* str);
    void resetEncoder(void);
    void setPerimeter(uint32_t perimeter);
    uint32_t getPerimeter(void);
    void setPulse(uint32_t pulse);
    uint32_t getPulse(void);
    uint8_t getFirmwareVersion(void);
    uint8_t setI2CAddress(uint8_t addr);
    uint8_t getI2CAddress(void);
};

#endif
