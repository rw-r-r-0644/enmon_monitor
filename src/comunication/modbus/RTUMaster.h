/**
 * RTUMaster.h
 *
 * Simple Modbus RTU master
 * link-layer implementation
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include <cstdint>
#include <cstddef>
#include "../RS485.h"
#include "Function.h"

class ModbusRTUMaster {
    static constexpr size_t aduBufferSize = 300;
    static constexpr size_t pduMaxDataSize = aduBufferSize - 4;
    RS485 &rs485;
    uint8_t aduBuffer[aduBufferSize];

public:
    enum Result {
        Success                     = 0,
        RequestSizeExcessive        = 0x10,
        RequestWriteFailed,
        RequestTransmissionFailed,
        ResponseTimeout             = 0x20,
        ResponseSizeExcessive,
        ResponseInvalidSize,
        ResponseInvalidSlaveId,
        ResponseInvalidFunctionCode,
        ResponseInvalidChecksum,
        ResponseReadFailed,
    };

    ModbusRTUMaster(RS485 &rs485);
    void begin(uint32_t baudRate);
    Result execute(uint8_t slaveId, const ModbusFunction &function);

private:
    Result writeRequest(uint8_t slaveId, const ModbusFunction &function);
    Result readResponse(uint8_t slaveId, const ModbusFunction &function);
};
