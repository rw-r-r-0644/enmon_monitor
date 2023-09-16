/**
 * RTUMaster.cpp
 *
 * Simple Modbus RTU master
 * link-layer implementation
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "RTUMaster.h"
#include "../../utils/Timer.h"
#include <Arduino.h>

static uint16_t crc16Update(uint16_t crc, uint8_t data) {
    crc ^= data;
    for (int i = 0; i < 8; i++)
        crc = (crc >> 1) ^ (0xA001 & -(crc & 1));
    return crc;
}

static uint16_t crc16Calc(const uint8_t *data, size_t size) {
    uint16_t crc = 0xFFFF;
    for (int i = 0; i < size; i++)
        crc = crc16Update(crc, data[i]);
    return crc;
}

ModbusRTUMaster::ModbusRTUMaster(RS485 &rs485)
    : rs485(rs485) {}

void ModbusRTUMaster::begin(uint32_t baudRate) {
    rs485.begin(baudRate);
}

ModbusRTUMaster::Result ModbusRTUMaster::writeRequest(uint8_t slaveId, const ModbusFunction &function) {
    size_t aduSize = 0;
    memset(aduBuffer, 0, sizeof(aduBuffer));

    /* write request */
    aduBuffer[aduSize++] = slaveId;
    aduBuffer[aduSize++] = function.code;

    if (function.requestSize > pduMaxDataSize)
        return RequestSizeExcessive;

    if (function.writeRequest(ModbusRequestData(&aduBuffer[aduSize], function.requestSize)))
        aduSize += function.requestSize;
    else
        return RequestWriteFailed;

    uint16_t checksum = crc16Calc(aduBuffer, aduSize);
    aduBuffer[aduSize++] = checksum >> 8;
    aduBuffer[aduSize++] = checksum & 0xFF;

    /* flush old outgoing/incoming data */
    rs485.flush();
    while (rs485.read() != -1);

    /* transmit request */
    rs485.beginTransmission();
    size_t written = rs485.write(aduBuffer, aduSize);
    rs485.flush();
    rs485.endTransmission();

    return written == aduSize
        ? Success : RequestTransmissionFailed;
}

ModbusRTUMaster::Result ModbusRTUMaster::readResponse(uint8_t slaveId, const ModbusFunction &function) {
    if (function.responseSize > pduMaxDataSize)
        return ResponseSizeExcessive;

    /* receive response */
    const size_t aduSize = 4 + function.responseSize;
    rs485.setTimeout(2000);
    if (rs485.readBytes(aduBuffer, aduSize) < aduSize)
        return ResponseTimeout;

    /* validate response */
    if (aduBuffer[0] != slaveId)
        return ResponseInvalidSlaveId;
    if (aduBuffer[1] != function.code)
        return ResponseInvalidFunctionCode;

    uint16_t checksum = crc16Calc(aduBuffer, aduSize - 2);
    if ((checksum >> 8) != aduBuffer[aduSize - 2] ||
        (checksum & 0xFF) != aduBuffer[aduSize - 1])
        return ResponseInvalidChecksum;

    return function.readResponse(ModbusResponseData(&aduBuffer[2], function.responseSize))
        ? Success : ResponseReadFailed;
}

ModbusRTUMaster::Result ModbusRTUMaster::execute(uint8_t slaveId, const ModbusFunction &function) {
    Result res = writeRequest(slaveId, function);
    if (res != Success)
        return res;
    return readResponse(slaveId, function);
}
