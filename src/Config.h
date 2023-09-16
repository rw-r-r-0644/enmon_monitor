/**
 * Config.h
 *
 * Main enmon configuration file
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once


/**
 * WiFi configuration
 */
//#define CONFIG_WIFI_SSID                "WIFI_SSID_HERE"
//#define CONFIG_WIFI_PASS                "WIFI_PASSWORD_HERE"


/**
 * MQTT broker configuration
 */
//#define CONFIG_MQTT_BROKER              "192.168.2.1"
//#define CONFIG_MQTT_BROKER_PORT         1883


/**
 * Select one of the preconfigured hardware setups
 * (see Hardware.h)
 */
//#define CONFIG_ENMON_SOFAR_ME3000SP
//#define CONFIG_ENMON_MOCK


/**
 * SDCard SPI gpio pins
 */
//#define CONFIG_PIN_SD_MISO              4
//#define CONFIG_PIN_SD_MOSI              7
//#define CONFIG_PIN_SD_SCK               6
//#define CONFIG_PIN_SD_CS                5


/**
 * Set available board ADC resolution
 */
//#define CONFIG_ADC_BITS                 12
//#define CONFIG_ADC_VALUES               (1 << (CONFIG_ADC_BITS))


/**
 * Set board VCC voltage (in mV)
 */
//#define CONFIG_VCC_VOLTAGE              3300


/**
 * Set country grid voltage (in V) and frequency (in Hz)
 */
//#define CONFIG_GRID_VOLTAGE             230
//#define CONFIG_GRID_FREQ                50


/**
 * How often the logged messages should be
 * flushed to disk. Files will be flushed
 * every CONFIG_LOGGER_SD_FLUSH_FREQ messages.
 *
 * Higher flushing frequencies will result in
 * less lata being lost in the event of an
 * unexpected shutdown or crash, at the cost
 * of potentially reducing the SD lifespan.
 */
//#define CONFIG_LOGGER_SD_FLUSH_FREQ     20

