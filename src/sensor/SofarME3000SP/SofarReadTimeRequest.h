/**
 * SofarReadTimeRequest.h
 *
 * Non-standard Sofar Modbus function to query
 * inverter current time
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */

#pragma once
#include "../../comunication/modbus/Function.h"
#include <ctime>

class SofarReadTimeRequest : public ModbusFunction {
    struct tm &timeinfo;
    bool writeRequest(const ModbusRequestData &request) const override;
    bool readResponse(const ModbusResponseData &response) const override;

public:
    SofarReadTimeRequest(struct tm &timeinfo);
};
 
