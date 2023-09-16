/**
 * CascadeLogger.h
 *
 * Combine a persistent logger with a normal
 * logger in cascade for reliability (provides
 * data buffering/persistency)
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include "Logger.h"
#include "PersistentLogger.h"

class CascadeLogger : public Logger {
    PersistentLogger &logger;
    Logger &cascade;
public:
    CascadeLogger(PersistentLogger &logger, Logger &cascade);

    /**
     * Logger interface implementation
     */
    bool ready(void) override;
    bool log(const std::string &topic, const JsonDocument &message) override;
    void poll(void) override;
};
