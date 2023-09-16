/**
 * MeterCT.h
 *
 * Grid current measurement and power estimation
 * using current transformer sensors (such as the
 * SCT-013 split core transformer).
 *
 * WARNING: without measuing voltage we cannot know the
 * current direction. This simple implementation does
 * NOT take current direction into account, current is
 * always considered positive.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include "PowerMeter.h"

class MeterCT : public PowerMeter {
    const int pin;
    const double calibration;
    double sampleCenter;

    static constexpr int gridPeriodMs = 1000 / double(CONFIG_GRID_FREQ);
    static constexpr int minReadMs = 5 * gridPeriodMs;

public:
    MeterCT(int analogPin, double calibration);

    void begin(void) override;
    double readCurrent(void) override;
};
