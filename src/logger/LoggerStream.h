/**
 * LoggerStream.h
 *
 * Logger implementation for Arduino Stream
 * (Serial ports, etc.)
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include <Arduino.h>
#include "Logger.h"

class LoggerStream : public Logger {
    Stream &stream;

public:
    LoggerStream(Stream &stream);

    /**
     * Logger interface implementation
     */
    bool log(const std::string &topic, const Message &message) override;
};

using LoggerSerial = LoggerStream;
