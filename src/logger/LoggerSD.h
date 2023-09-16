/**
 * LoggerSD.h
 *
 * PersistentLogger implementation for SDCard
 * JSON-like MessagePack archives.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include "PersistentLogger.h"
#include "../utils/MessagePackStore.h"
#include <ArduinoJson.h>
#include <unordered_map>

class LoggerSD : public PersistentLogger {
    std::unordered_map<std::string, MessagePackStore> topicStore;
    StaticJsonDocument<256> doc;

    /* get the message file corresponding to a given topic file */
    MessagePackStore &getTopic(const std::string &topic);

public:
    /**
     * PersistentLogger interface implementation
     */
    bool read(Logger &cascade) override;
    bool backlog(const std::string &topic) override;
    bool log(const std::string &topic, const JsonDocument &message, bool syncRead) override;
};
