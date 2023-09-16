/**
 * Regs.h
 *
 * ME3000SP register and functions information
 * from Sofar MTU protocol datasheet
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once

/* inverter registers of interest */
#define ME3000SP_INVERTER_ADDRESS       0x0200
    #define HREG_RUNNING_STATE              0x00
    #define HREG_FAULT_STATE_1              0x01
    #define HREG_FAULT_STATE_2              0x02
    #define HREG_FAULT_STATE_3              0x03
    #define HREG_FAULT_STATE_4              0x04
    #define HREG_FAULT_STATE_5              0x05
    #define HREG_BATTERY_PERCENTAGE         0x10
    #define HREG_BATTERY_TEMPERATURE        0x11
    #define HREG_METER_GRID                 0x12
    #define HREG_METER_BATTERY              0x14
    #define HREG_METER_GENERATION           0x15


/* custom modbus time reading function code */
#define ME3000SP_FUNCTION_READ_TIME     0x10
