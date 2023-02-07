#include "UNIT_EXT_ENCODER.h"

void UNIT_EXT_ENCODER::writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                              uint8_t length) {
    _wire->beginTransmission(addr);
    _wire->write(reg);
    for (int i = 0; i < length; i++) {
        _wire->write(*(buffer + i));
    }
    _wire->endTransmission();
}

void UNIT_EXT_ENCODER::readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                             uint8_t length) {
    uint8_t index = 0;
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->endTransmission(false);
    _wire->requestFrom(addr, length);
    for (int i = 0; i < length; i++) {
        buffer[index++] = _wire->read();
    }
}

bool UNIT_EXT_ENCODER::begin(TwoWire *wire, uint8_t addr, uint8_t sda, uint8_t scl,
                         uint32_t speed) {
    _wire  = wire;
    _addr  = addr;
    _sda   = sda;
    _scl   = scl;
    _speed = speed;
    _wire->begin(_sda, _scl, _speed);
    delay(10);
    _wire->beginTransmission(_addr);
    uint8_t error = _wire->endTransmission();
    if (error == 0) {
        return true;
    } else {
        return false;
    }     
}

uint32_t UNIT_EXT_ENCODER::getEncoderValue(void) {
    uint8_t data[4];

    uint8_t reg = UNIT_EXT_ENCODER_ENCODER_REG;
    readBytes(_addr, reg, data, 4);
    uint32_t value = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
    return value;
}

uint32_t UNIT_EXT_ENCODER::getZeroPulseValue(void) {
    uint8_t data[4];

    uint8_t reg = UNIT_EXT_ENCODER_ZERO_PULSE_VALUE_REG;
    readBytes(_addr, reg, data, 4);
    uint32_t value = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
    return value;
}

uint32_t UNIT_EXT_ENCODER::getMeterValue(void) {
    uint8_t data[4];

    uint8_t reg = UNIT_EXT_ENCODER_METER_REG;
    readBytes(_addr, reg, data, 4);
    uint32_t value = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
    return value;
}

void UNIT_EXT_ENCODER::getMeterString(char* str) {
    char read_buf[9] = {0};

    uint8_t reg = UNIT_EXT_ENCODER_METER_STRING_REG;
    readBytes(_addr, reg, (uint8_t*)read_buf, 9);
    memcpy(str, read_buf, sizeof(read_buf));
}

void UNIT_EXT_ENCODER::resetEncoder(void) {
    uint8_t data[8] = {0};

    uint8_t reg = UNIT_EXT_ENCODER_RESET_REG;
    data[0] = 1;
    writeBytes(_addr, reg, data, 1);
}

void UNIT_EXT_ENCODER::setPerimeter(uint32_t perimeter) {
    uint8_t data[8] = {0};

    uint8_t reg = UNIT_EXT_ENCODER_PERIMETER_REG;
    data[0] = (perimeter & 0xff);
    data[1] = ((perimeter >> 8)& 0xff);
    data[2] = ((perimeter >> 16)& 0xff);
    data[3] = ((perimeter >> 24)& 0xff);
    writeBytes(_addr, reg, data, 4);
}

uint32_t UNIT_EXT_ENCODER::getPerimeter(void) {
    uint8_t data[8] = {0};

    uint8_t reg = UNIT_EXT_ENCODER_PERIMETER_REG;
    readBytes(_addr, reg, data, 4);
    uint32_t value = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
    return value;
}

void UNIT_EXT_ENCODER::setPulse(uint32_t pulse) {
    uint8_t data[8] = {0};

    uint8_t reg = UNIT_EXT_ENCODER_PULSE_REG;
    data[0] = (pulse & 0xff);
    data[1] = ((pulse >> 8)& 0xff);
    data[2] = ((pulse >> 16)& 0xff);
    data[3] = ((pulse >> 24)& 0xff);
    writeBytes(_addr, reg, data, 4);
}

uint32_t UNIT_EXT_ENCODER::getPulse(void) {
    uint8_t data[8] = {0};

    uint8_t reg = UNIT_EXT_ENCODER_PULSE_REG;
    readBytes(_addr, reg, data, 4);
    uint32_t value = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
    return value;
}

uint8_t UNIT_EXT_ENCODER::setI2CAddress(uint8_t addr) {
    _wire->beginTransmission(_addr);
    _wire->write(I2C_ADDRESS_REG);
    _wire->write(addr);
    _wire->endTransmission();    
    _addr = addr;
    return _addr;
}

uint8_t UNIT_EXT_ENCODER::getI2CAddress(void) {
    _wire->beginTransmission(_addr);
    _wire->write(I2C_ADDRESS_REG);
    _wire->endTransmission();  

    uint8_t RegValue;

    _wire->requestFrom(_addr, 1); 
    RegValue = Wire.read();
    return RegValue;
}

uint8_t UNIT_EXT_ENCODER::getFirmwareVersion(void) {
    _wire->beginTransmission(_addr);
    _wire->write(FIRMWARE_VERSION_REG);
    _wire->endTransmission();  

    uint8_t RegValue;

    _wire->requestFrom(_addr, 1); 
    RegValue = Wire.read();
    return RegValue;
}
