/**
 * CompositeLogger.cpp
 *
 * Combine two loggers
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "CompositeLogger.h"

CompositeLogger::CompositeLogger(Logger &log0, Logger &log1)
    : log0(log0), log1(log1) {}

bool CompositeLogger::ready(void) {
    return log0.ready() || log1.ready();
}

void CompositeLogger::poll(void) {
    log0.poll();
    log1.poll();
}

bool CompositeLogger::log(const std::string &topic, const Message &message) {
    bool res0 = log0.log(topic, message);
    bool res1 = log1.log(topic, message);
    return res0 || res1;
}
 
