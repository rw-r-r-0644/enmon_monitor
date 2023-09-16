/**
 * PersistentLogger.h
 *
 * Logger capable of archiving and retrieving messages
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include "Logger.h"

class PersistentLogger : public Logger {
public:
    inline bool log(const std::string &topic, const Message &message) override {
        return log(topic, message, false);
    }

    /**
     * Determines if there are unread archived messages for the given topic
     */
    virtual bool backlog(const std::string &topic) = 0;

    /**
     * (Try to) log the provided message
     * If syncRead is set, update the read
     * pointer after writing the message
     */
    virtual bool log(const std::string &topic, const Message &message, bool syncRead) = 0;

    /**
     * Report unread archived messages to
     * the provided logger
     */
    virtual bool read(Logger &logger) = 0;
};
 
