#pragma once
#include "resource/Enmon.h"
#include "Config.h"


/**
 * Energy monitoring plant informations
 */
static EnmonInfo enmonInfo = {
    .name = "plant0",
    .latitude = 46.0804,
    .longitude = 13.2118,
    .capacity_generation = 5000,
    .capacity_battery = 3000,
};
 

#if defined(CONFIG_ENMON_SOFAR_ME3000SP)

#include "resource/EnmonME3000SP.h"
#include "sensor/SofarME3000SP/SofarME3000SP.h"


/**
 * Sample ME3000SP configuration
 */
static RS485 rs845(
    Serial2,                    /* hw serial */
    8,                          /* tx pin */
    9,                          /* rx pin */
    1                           /* dir pin */
);
static ModbusRTUMaster modbus(rs845);
static SofarME3000SP sofar(
    modbus,                     /* modbus interface */
    0x01                        /* modbus slave id */
);
static EnmonME3000SP enmon(enmonInfo,
    Timer(Timer::Minutes(10)),  /* reporting interval */
    sofar                       /* monitored inverter */
);


#elif defined(CONFIG_ENMON_MOCK)

#include "resource/EnmonMock.h"
#include "sensor/MeterCT.h"
#include "sensor/Thermistor.h"
#define CONFIG_REQUIRES_NTP


/**
 * Sample mock monitoring configuration
 */
static MeterCT ct0(
    A0,                         /* thermistor analog pin */
    29                          /* calibration value */
);
static Thermistor therm0(A1,
    10000,                      /* fixedR */
    1.002267361e-3,             /* coeffA */
    2.314268510e-4,             /* coeffB */
    2.721887503e-7              /* coeffC */
);
static EnmonMock enmon(enmonInfo,
    Timer(Timer::Minutes(10)),  /* reporting interval */
    ct0,                        /* attached current sensor */
    therm0                      /* attached temperature sensor */
);


#else
#error "Unknown hardware configuration!"
#endif
