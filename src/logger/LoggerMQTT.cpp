/**
 * LoggerMQTT.cpp
 *
 * Logger implementation for MQTT
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "LoggerMQTT.h"
#include "../comunication/Network.h"

LoggerMQTT::LoggerMQTT(const std::string &broker, uint16_t port)
    : mqttClient(wifiClient)
    , broker(broker)
    , port(port)
    , Connection(
        Timer(Timer::Seconds(5)),
        Timer(Timer::Seconds(30), Timer::Minutes(15))
    )
{
}

void LoggerMQTT::begin(void) {
    mqttClient.setConnectionTimeout(15 * 1000);
    Connection::begin();
}

void LoggerMQTT::pollConnection(void) {
    mqttClient.poll();
}

void LoggerMQTT::restoreConnection(void) {
    if (Network.available()) {
        Serial.println("LoggerMQTT: attempting broker connection");
        mqttClient.connect(broker.c_str(), port);
        Serial.println("LoggerMQTT: done");
    }
}

bool LoggerMQTT::checkConnection(void) {
    return Network.available()
        && mqttClient.connected();
}


bool LoggerMQTT::ready(void) {
    return Connection::available();
}

void LoggerMQTT::poll(void) {
    Connection::poll();
}

bool LoggerMQTT::log(const std::string &topic, const Message &message) {
    if (!ready())
        return false;

    bool sent = mqttClient.beginMessage(topic.c_str(), /* retain */ true, /* qos */ 1)
        && serializeJson(message, mqttClient) > 0
        && mqttClient.endMessage();

    if (!sent) {
        mqttClient.stop();
        updateConnectionStatus();
        return false;
    }
    return true;
}
