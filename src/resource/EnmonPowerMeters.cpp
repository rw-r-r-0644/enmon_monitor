/**
 * EnmonPowerMeters.h
 *
 * Energy monitor using the provided power meters
 * to measure power generation and consumption.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "EnmonPowerMeters.h"
#include <ctime>

EnmonPowerMeters::EnmonPowerMeters(EnmonInfo info, Timer reportTimer,
    PowerMeter &generation, PowerMeter &consumption)
    : Enmon(info, reportTimer)
    , generation(generation), consumption(consumption)
{}

void EnmonPowerMeters::begin(void) {
    generation.begin();
    consumption.begin();
}

bool EnmonPowerMeters::readEnmon(EnmonStatus &status, std::string &error) {
    status.timestamp = time(NULL);
    status.meter_generation = generation.readPower();
    status.meter_grid = consumption.readPower() - status.meter_generation;
    return true;
}
