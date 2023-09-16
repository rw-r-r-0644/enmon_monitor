/**
 * SofarReadTimeRequest.cpp
 *
 * Non-standard Sofar Modbus function to query
 * inverter current time
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "SofarReadTimeRequest.h"
#include "Regs.h"

SofarReadTimeRequest::SofarReadTimeRequest(struct tm &timeinfo)
    : ModbusFunction(ME3000SP_FUNCTION_READ_TIME, 4, 7)
    , timeinfo(timeinfo)
{}


bool SofarReadTimeRequest::writeRequest(const ModbusRequestData &request) const {
    return request.write16(0x00, 0x8000)
        && request.write16(0x02, 0x0000);
}

bool SofarReadTimeRequest::readResponse(const ModbusResponseData &response) const {
    if (response.read8(0x00) != 0x06)
        return false;

    timeinfo.tm_sec = response.read8(0x01);
    timeinfo.tm_min = response.read8(0x02);
    timeinfo.tm_hour = response.read8(0x03);
    timeinfo.tm_mday = response.read8(0x04);
    timeinfo.tm_mon = response.read8(0x05);
    timeinfo.tm_year = 2000 + response.read8(0x06);
    /*
    * The year returned by the inverter is only made up of 2 digits.
    * This probably won't be used in 2100 either way..
    * (Oh no, not again. - probably a bowl of petunias)
    */
    return true;
}

