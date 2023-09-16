/**
 * TemperatureSensor.h
 *
 * Generic temperature sensor interface
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include "../utils/Initializable.h"

class TemperatureSensor : public Initializable {
public:
    /*
     * Read the temperature (in °C)
     * measured by the sensor
     */
    virtual double readTemperature(void) = 0;
};
