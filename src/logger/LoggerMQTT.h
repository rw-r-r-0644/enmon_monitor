/**
 * LoggerMQTT.h
 *
 * Logger implementation for MQTT
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include <Arduino.h>
#include "Logger.h"
#include <WiFi.h>
#include <ArduinoMqttClient.h>
#include "../comunication/Connection.h"
#include "../utils/Timer.h"

class LoggerMQTT : public Logger, Connection {
    WiFiClient wifiClient;
    MqttClient mqttClient;

    const std::string broker;
    const uint16_t port;

    void pollConnection(void) override;
    void restoreConnection(void) override;
    bool checkConnection(void) override;

public:
    LoggerMQTT(const std::string &broker,
        uint16_t port = 1883);

    /**
     * Establish a connection with the MQTT broker
     */
    void begin(void);

    /**
     * Logger interface implementation
     */
    bool ready(void) override;
    void poll(void) override;
    bool log(const std::string &topic, const Message &message) override;
};
