/**
 * DataBuffer.h
 *
 * Modbus request/response data buffer accessor.
 * Performs endianess conversions and bound checks.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include <cstdint>
#include <cstddef>

class ModbusRequestData {
    uint8_t *const buf;
    const size_t size;

    template<typename T>
    bool write(size_t offset, T value) const {
        if (offset >= size || offset + sizeof(value) > size)
            return false;

        /* store data as big endian */
        for (int i = sizeof(value) - 1; i >= 0; i--) {
            buf[offset + i] = value & 0xFF;
            value >>= 8;
        }
        return true;
    }

public:
    ModbusRequestData(uint8_t *const buf, size_t size)
        : buf(buf), size(size) {}

    bool write8(size_t offset, uint8_t value) const;
    bool write16(size_t offset, uint16_t value) const;
    bool write32(size_t offset, uint32_t value) const;
};

class ModbusResponseData {
    uint8_t *const buf;
    const size_t size;

    template<typename T>
    T read(size_t offset) const {
        T value = 0;

        if (offset >= size || offset + sizeof(value) > size)
            return value; /* not quite ideal */

        /* read big endian data */
        for (int i = 0; i < sizeof(value); i++) {
            value <<= 8;
            value |= buf[offset + i];
        }

        return value;
    }

public:
    ModbusResponseData(uint8_t *const buf, size_t size)
        : buf(buf), size(size) {}

    uint8_t read8(size_t offset) const;
    uint16_t read16(size_t offset) const;
    uint32_t read32(size_t offset) const;
};
