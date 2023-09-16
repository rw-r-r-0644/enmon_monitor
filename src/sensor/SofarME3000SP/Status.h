/**
 * Status.h
 *
 * ME3000SP inverter generation and
 * fault status data
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */

#pragma once
#include <string>

struct StatusME3000SP {
    enum State {
        STATE_WAIT,
        STATE_CHECK,
        STATE_NORMAL,
        STATE_EPS,
        STATE_FAULT,
        STATE_PERMANENT_FAULT,
    };

    uint16_t runningState;
    uint16_t faultState[5];

    int16_t meterGrid;
    uint16_t meterGeneration;
    int16_t meterBattery;

    uint16_t batteryPercentage;
    uint16_t batteryTemperature;

    inline bool faulty(void) {
        return runningState == STATE_FAULT
            || runningState == STATE_PERMANENT_FAULT;
    }
    bool fault(std::string &message);

private:
    static char const *const faultMessages[];
};

