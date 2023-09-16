/**
 * EnmonME3000SP.h
 *
 * Sofar ME3000SP energy monitor
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "Resource.h"
#include "Enmon.h"
#include "../sensor/SofarME3000SP/SofarME3000SP.h"

class EnmonME3000SP : public Enmon {
    SofarME3000SP &inverter;
    bool readEnmon(EnmonStatus &status, std::string &error) override;

public:
    EnmonME3000SP(EnmonInfo info, Timer reportTimer, SofarME3000SP &inverter);
    void begin(void) override;
};
