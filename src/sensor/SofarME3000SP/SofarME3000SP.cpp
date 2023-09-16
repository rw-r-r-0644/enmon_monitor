/**
 * SofarME3000SP.cpp
 *
 * Read data from Sofar ME3000SP inverters
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "SofarME3000SP.h"
#include "../../comunication/modbus/ReadHoldingRegisters.h"
#include "SofarReadTimeRequest.h"
#include "Regs.h"

SofarME3000SP::SofarME3000SP(ModbusRTUMaster &modbus, int slaveId)
    : modbus(modbus), slaveId(slaveId) {}

void SofarME3000SP::begin() {
    modbus.begin(9600);
}

bool SofarME3000SP::readStatus(StatusME3000SP &status) {
    Serial.println("calling readHoldingRegisters");
    std::array<uint16_t, 0x1B> registers;

    ModbusRTUMaster::Result result = modbus.execute(slaveId, ModbusReadHoldingRegisters(ME3000SP_INVERTER_ADDRESS, registers));
    Serial.print("done: ");
    Serial.println(result, HEX);
    if (result != ModbusRTUMaster::Success)
        return false;

    /* copy registers of monitoring use */
    status.runningState = registers[HREG_RUNNING_STATE];
    for (int i = 0; i < 5; i++)
        status.faultState[i] = registers[HREG_FAULT_STATE_1 + i];
    status.meterGrid = (int16_t)registers[HREG_METER_GRID];
    status.meterGeneration = registers[HREG_METER_GENERATION];
    status.meterBattery = (int16_t)registers[HREG_METER_BATTERY];
    status.batteryPercentage = registers[HREG_BATTERY_PERCENTAGE];
    status.batteryTemperature = registers[HREG_BATTERY_TEMPERATURE];
    return true;
}

bool SofarME3000SP::readTimestamp(time_t &timestamp) {
    struct tm timeinfo;
    if (!modbus.execute(slaveId, SofarReadTimeRequest(timeinfo)))
        return false;

    timestamp = mktime(&timeinfo);
    return true;
}
