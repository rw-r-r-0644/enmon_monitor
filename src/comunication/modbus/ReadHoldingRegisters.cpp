/**
 * ReadHoldingRegisters.cpp
 *
 * Standard ModBus read holding registers function
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "ReadHoldingRegisters.h"

ModbusReadHoldingRegisters::ModbusReadHoldingRegisters(
    uint16_t address, uint16_t *registers, uint16_t count)
    : ModbusFunction(MODBUS_READ_HOLDING_REGISTERS,
        sizeof(uint16_t) * 2, sizeof(uint8_t) + sizeof(uint16_t) * count)
    , address(address), registers(registers), count(count)
{}

bool ModbusReadHoldingRegisters::writeRequest(const ModbusRequestData &request) const {
    return request.write16(0x00, address)
        && request.write16(0x02, count);
}

bool ModbusReadHoldingRegisters::readResponse(const ModbusResponseData &response) const {
    if (response.read8(0x00) != count * sizeof(uint16_t))
        return false;

    for (int i = 0; i < count; i++)
        registers[i] = response.read16(i * sizeof(uint16_t));
    return true;
}
