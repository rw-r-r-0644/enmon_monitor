/**
 * EnmonME3000SP.h
 *
 * Sofar ME3000SP energy monitor
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "EnmonME3000SP.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

EnmonME3000SP::EnmonME3000SP(EnmonInfo info, Timer reportingTimer, SofarME3000SP &inverter)
    : Enmon(info, reportingTimer), inverter(inverter)
{}

void EnmonME3000SP::begin(void) {
    inverter.begin();
}

bool EnmonME3000SP::readEnmon(EnmonStatus &status, std::string &error) {
    StatusME3000SP inverterStatus;

    if (!inverter.readTimestamp(status.timestamp) ||
        !inverter.readStatus(inverterStatus)) {
        error = "failed to read from inverter";
        return false;
    }

    /* convert meter readings */
    status.meter_grid = inverterStatus.meterGrid * 10;
    status.meter_battery = inverterStatus.meterBattery * 10;
    status.meter_generation = inverterStatus.meterGeneration * 10;

    status.percentage_battery = inverterStatus.batteryPercentage;
    status.temperature_battery = inverterStatus.batteryTemperature;

    /* return operational state */
    return !inverterStatus.faulty()
        || inverterStatus.fault(error);
}

