/**
 * Status.cpp
 *
 * ME3000SP inverter generation and
 * fault status data
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "Status.h"


/* convert fault bitset in a set of fault messages */
bool StatusME3000SP::fault(std::string &message) {
    bool hasHault = false;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 16; j++) {
            if (!(faultState[i] & (1 << j)))
                continue;

            int offset = i * 16 + j;
            int id = offset + 1;

            if (!hasHault) {
                hasHault = true;
                message = "";
            } else
                message += ", ";

            message += std::string(faultMessages[offset]);
            message += " (ID" + std::to_string(id) + ")";
        }
    }

    return hasHault;
}


/* fault error messages from Sofar Modbus RTU protocol datasheet */
char const *const StatusME3000SP::faultMessages[] = {
    "grid overvoltage protection",
    "grid undervoltage protection",
    "grid overfrequency protection",
    "grid underfrequency protection",
    "battery overvoltage protection",
    NULL, 
    "lvrt function is faulty",
    "input overvoltage protection",


    "llcbus overvoltage hardware protection",
    "bus overvoltage hardware protection",
    "buckboost overcurrent hardware protection",
    "battery overcurrent hardware protection",
    "gfci overcurrent hardware protection",
    "pv overcurrent hardware protection",
    "output current hardware protection",
    "input current unbalanced",


    "grid current sampling error",
    "dci sampling error",
    "grid voltage sampling error",
    "gfci sampling error",
    "main chip fault",
    "hardware auxiliary power fault",
    NULL, NULL,


    "llcbus overcurrent protection",
    "bus overvoltage software protection",
    "battery overcurrent protection",
    "dci overcurrent protection",
    "output overcurrent software protection",
    "buck overcurrent protection",
    "output overcurrent protection",
    "input overcurrent software protection",


    "detected input mode missconfiguration",
    "overload protection",
    "ct error",
    NULL, NULL, NULL, NULL, NULL,


    NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    "inconsistent gfci measure between master and slave dsp",


    "high grid voltage sampling variance between master and slave dsp",
    "high grid frequency sampling variance between master and slave dsp",
    "high dci sampling variance between master and slave dsp",
    "battery communication fault",
    "spi communication fault",
    "sci communication fault",
    "relay fault",
    "insulation resistance is too low",


    "excessive battery temperature",
    "excessive heatsink temperature",
    "excessive environment temp",
    "grounding not correct",
    NULL, NULL, NULL, NULL,


    "unrecoverable fault provoked by grid overcurrent",
    "unrecoverable fault provoked by bus overvoltage",
    "unrecoverable fault provoked by eps mode battery overcurrent",
    "unrecoverable fault provoked by input unbalance",
    NULL,
    "unrecoverable fault provoked by output overcurrent",
    NULL, NULL,


    "unrecoverable fault provoked by input mode missconfiguration",
    "unrecoverable fault provoked by input overcurrent",
    "unrecoverable fault during eeprom write",
    "unrecoverable fault during eeprom read",
    "unrecoverable relay fault",
    NULL, NULL, NULL,
};
