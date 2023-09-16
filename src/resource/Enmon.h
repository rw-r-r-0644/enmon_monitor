#pragma once
#include "Resource.h"

struct EnmonInfo {
    std::string name;
    double latitude;
    double longitude;
    int capacity_generation;
    int capacity_battery = -1;
}; 

struct EnmonStatus {
    long long timestamp;
    int meter_battery = 0;
    int meter_generation = 0;
    int meter_grid = 0;
    int percentage_battery = -1;
    int temperature_battery = 0;
};

class Enmon : public Resource {
    const std::string basePath;

    int infoInterval = 0;
    Timer reportTimer;

protected:
    const EnmonInfo info;
    Enmon(EnmonInfo info, Timer reportTimer);
    virtual bool readEnmon(EnmonStatus &status, std::string &error) = 0;

public:
    bool read(DataLogger &datalogger) override final;
};
