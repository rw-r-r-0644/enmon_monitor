/**
 * EnmonPowerMeters.h
 *
 * Energy monitor using the provided power meters
 * to measure power generation and consumption.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "Resource.h"
#include "Enmon.h"
#include "../sensor/PowerMeter.h"
#include "../sensor/TemperatureSensor.h"
#include "../utils/Timer.h"


class EnmonPowerMeters : public Enmon {
    PowerMeter &generation, &consumption;
    bool readEnmon(EnmonStatus &status, std::string &error) override;

public:
    EnmonPowerMeters(EnmonInfo info, Timer reportTimer,
        PowerMeter &generation, PowerMeter &consumption);
    void begin(void) override;
};
