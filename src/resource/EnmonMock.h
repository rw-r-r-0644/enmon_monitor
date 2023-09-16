/**
 * EnmonMock.h
 *
 * Simulate reasonable Enmon readings, with
 * a single PowerMeter and battery temperature
 * sensor.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "Resource.h"
#include "Enmon.h"
#include "../sensor/PowerMeter.h"
#include "../sensor/TemperatureSensor.h"
#include "../utils/Timer.h"

class EnmonMock : public Enmon {
    PowerMeter &consumption;
    TemperatureSensor &batteryTemp;
    int power_generation;
    bool readEnmon(EnmonStatus &status, std::string &error) override;

public:
    EnmonMock(EnmonInfo info, Timer reportTimer,
        PowerMeter &consumption, TemperatureSensor &batteryTemp);

    void begin(void) override;
};
