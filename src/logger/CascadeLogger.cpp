/**
 * CascadeLogger.cpp
 *
 * Combine a persistent logger with a normal
 * logger in cascade for reliability (provides
 * data buffering/persistency)
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "CascadeLogger.h"

CascadeLogger::CascadeLogger(PersistentLogger &logger, Logger &cascade)
    : logger(logger), cascade(cascade) {}


bool CascadeLogger::ready(void) {
    return logger.ready() || cascade.ready();
}

bool CascadeLogger::log(const std::string &topic, const Message &message) {
    bool relayed = cascade.ready()
        && !logger.backlog(topic)
        && cascade.log(topic, message);
    return logger.log(topic, message, relayed) || relayed;
}

void CascadeLogger::poll(void) {
    logger.poll();
    cascade.poll();
    if (cascade.ready())
        logger.read(cascade);
}
