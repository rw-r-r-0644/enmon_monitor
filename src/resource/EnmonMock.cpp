/**
 * EnmonMock.cpp
 *
 * Simulate reasonable Enmon readings, with
 * a single PowerMeter and battery temperature
 * sensor.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "EnmonMock.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

static void permutate(int &base, int min, int max) {
    int gen = rand() % 100;
    double rel = gen < 5 ? 0.20 : (gen < 25 ? 0.10 : 0.05);
    int delta = base * rel * (1 - 2 * (gen & 1));
    base = std::max(min, std::min(max, base + delta));
}

EnmonMock::EnmonMock(EnmonInfo info, Timer reportingTimer,
    PowerMeter &consumption, TemperatureSensor &batteryTemp)
    : Enmon(info, reportingTimer)
    , consumption(consumption), batteryTemp(batteryTemp)
{
    power_generation = info.capacity_generation / 2;
}

void EnmonMock::begin(void) {
    consumption.begin();
    batteryTemp.begin();
}

bool EnmonMock::readEnmon(EnmonStatus &status, std::string &error) {
    status.timestamp = time(NULL);
    status.percentage_battery = 50;

    /* read real power consumption and temperature  */
    int meter_consumption = consumption.readPower();
    status.temperature_battery = batteryTemp.readTemperature();

    /* randomly permutate power generation and deduce remaining variables */
    permutate(power_generation, 0, info.capacity_generation);
    status.meter_generation = power_generation;
    status.meter_battery = (meter_consumption > status.meter_generation)
        ? std::min(meter_consumption - status.meter_generation, 1000)
        : -std::min(status.meter_generation - meter_consumption, 300);
    status.meter_grid = meter_consumption
        - status.meter_generation - status.meter_battery;

    return true;
}

