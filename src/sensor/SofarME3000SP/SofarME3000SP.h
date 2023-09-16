/**
 * SofarME3000SP.h
 *
 * Read data from Sofar ME3000SP inverters
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include "../../comunication/modbus/RTUMaster.h"
#include "../../utils/Initializable.h"
#include "Status.h"
#include <ctime>

class SofarME3000SP : public Initializable {
    ModbusRTUMaster &modbus;
    const int slaveId;

public:
    SofarME3000SP(ModbusRTUMaster &modbus, int slaveId);

    void begin(void);
    bool readStatus(StatusME3000SP &status);
    bool readTimestamp(time_t &timestamp);
};
