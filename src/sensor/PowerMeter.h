/**
 * PowerMeter.h
 *
 * Generic power meter interface
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include "../Config.h"
#include "../utils/Initializable.h"

class PowerMeter : public Initializable {
public:
    /*
     * Read RMS current (in A)
     */
    virtual double readCurrent(void) = 0;

    /*
     * Read utilized power (in W)
     */
    virtual double readPower(void) {
        return readCurrent() * double(CONFIG_GRID_VOLTAGE);
    }
};
 
