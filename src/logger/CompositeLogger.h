/**
 * CompositeLogger.h
 *
 * Combine two loggers
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include "Logger.h"

class CompositeLogger : public Logger {
    Logger &log0, &log1;
public:
    CompositeLogger(Logger &log0, Logger &log1);

    /**
     * Logger interface implementation
     */
    bool ready(void) override;
    void poll(void) override;
    bool log(const std::string &topic, const Message &message) override;
};
 
