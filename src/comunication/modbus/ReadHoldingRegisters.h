/**
 * ReadHoldingRegisters.h
 *
 * Standard Modbus read holding registers function
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include <cstdint>
#include <cstddef>
#include <array>
#include "Function.h"

class ModbusReadHoldingRegisters : public ModbusFunction {
    const uint16_t address, count;
    uint16_t *const registers;

    ModbusReadHoldingRegisters(uint16_t address, uint16_t *registers, uint16_t count);

public:
    /**
     * Read registers from the given address
     */
    template<size_t count>
    ModbusReadHoldingRegisters(uint16_t address, std::array<uint16_t, count> &registers)
        : ModbusReadHoldingRegisters(address, registers.data(), count) {}

    /**
     * ModbusFunction interface implementation
     */
    bool writeRequest(const ModbusRequestData &request) const override;
    bool readResponse(const ModbusResponseData &response) const override;
};
