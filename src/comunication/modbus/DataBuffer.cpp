/**
 * DataBuffer.cpp
 *
 * Modbus request/response data buffer accessor.
 * Performs endianess conversions and bound checks.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "DataBuffer.h"

/* istantiate templates for a fixed set of safe types */

bool ModbusRequestData::write8(size_t offset, uint8_t value) const {
    return write<uint8_t>(offset, value);
}
bool ModbusRequestData::write16(size_t offset, uint16_t value) const {
    return write<uint16_t>(offset, value);
}
bool ModbusRequestData::write32(size_t offset, uint32_t value) const {
    return write<uint32_t>(offset, value);
}

uint8_t ModbusResponseData::read8(size_t offset) const {
    return read<uint8_t>(offset);
}
uint16_t ModbusResponseData::read16(size_t offset) const {
    return read<uint16_t>(offset);
}
uint32_t ModbusResponseData::read32(size_t offset) const {
    return read<uint32_t>(offset);
}
