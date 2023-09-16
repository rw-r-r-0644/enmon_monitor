#include "Enmon.h"
#include <ArduinoJson.h>

Enmon::Enmon(EnmonInfo info, Timer reportTimer)
    : basePath("enmon/" + info.name + "/"), reportTimer(reportTimer), info(info)
{
    reportTimer.disable();
}

bool Enmon::read(DataLogger &logger) {
    EnmonStatus status;
    std::string error;

    reportTimer.enable();
    if (!reportTimer.alarm())
        return true;

    /* every once in a while, re-report plant informations 
     * (the MQTT broker might have rebooted or crashed) */
    if (!infoInterval--) {
        logger.report(basePath + "info", info, false);
        infoInterval = 20;
    }

    if (!readEnmon(status, error))
        logger.report(basePath + "error", error);

    logger.report(basePath + "status", status);
    return true;
}


bool convertToJson(const struct EnmonInfo &info, JsonVariant dst) {
    dst["longitude"] = info.longitude;
    dst["latitude"] = info.latitude;
    dst["capacity_generation"] = info.capacity_generation;
    dst["capacity_battery"] = info.capacity_battery;
    return true;
} 

bool convertToJson(const struct EnmonStatus &status, JsonVariant dst) {
    dst["timestamp"] = status.timestamp;
    dst["meter_battery"] = status.meter_battery;
    dst["meter_generation"] = status.meter_generation;
    dst["meter_grid"] = status.meter_grid;
    dst["percentage_battery"] = status.percentage_battery;
    dst["temperature_battery"] = status.temperature_battery;
    return true;
}
