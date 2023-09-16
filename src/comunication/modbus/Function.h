#pragma once
#include "DataBuffer.h"

/* standard ModBus function codes */
#define MODBUS_READ_HOLDING_REGISTERS   0x03

/* generic ModBus function */
class ModbusFunction {
public:
    const uint8_t code;
    const size_t requestSize, responseSize;

    ModbusFunction(uint8_t code, size_t requestSize, size_t responseSize)
        : code(code), requestSize(requestSize), responseSize(responseSize) {}

    virtual bool writeRequest(const ModbusRequestData &request) const = 0;
    virtual bool readResponse(const ModbusResponseData &response) const = 0;
}; 
