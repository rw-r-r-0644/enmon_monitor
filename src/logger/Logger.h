/**
 * Logger.h
 *
 * Sensor data logger interface
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include <ArduinoJson.h>
#include <string>

/**
 * Ideally we should probably use a flexible,
 * format agnostic interface to represent
 * serializable messages.
 * However this adds a significant amount of
 * overhead, and complicates the process of
 * storing and retrieving messages, as type
 * information has to be preserved for formats
 * such as JSON to work.
 * Realistically JSON offers a sufficient amount
 * of flexibility for our purposes, so as the
 * resources of the embedded systems targeted by
 * this projects are fairly limited, we trade a bit
 * of flexibility for reduced overhead.
 */
using Message = JsonDocument;

class Logger {
public:
    /**
     * Determine if the logger is available for writing
     * (connected/with enough space/...)
     */
    virtual bool ready(void) {
        return true;
    }

    /**
     * (Try to) log the provided message
     */
    virtual bool log(const std::string &topic, const Message &message) = 0;

    /**
     * Execute internal logger operations (message
     * relaying, keep alives, ...).
     * Call this function periodically
     */
    virtual void poll(void) {};
};
