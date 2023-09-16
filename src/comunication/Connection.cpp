/**
 * Connection.cpp
 *
 * This class handles automatic connection /
 * reconnection to a given service which may
 * become unavailable.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "Connection.h"

Connection::Connection(const Timer &timerCheck, const Timer &timerRestore)
    : timerCheck(timerCheck)
    , timerRestore(timerRestore)
    , connectionAvailable(false)
{
    this->timerCheck.disable();
    this->timerRestore.disable();
}

void Connection::begin(void) {
    timerCheck.enable(true);
    poll();
}

void Connection::updateConnectionStatus(void) {
    if (checkConnection()) {
        connectionAvailable = true;
        timerRestore.disable();
    } else {
        connectionAvailable = false;
        timerRestore.enable(true);
    }
}

void Connection::pollConnection(void) {}

void Connection::poll(void) {
    if (timerCheck.alarm())
        updateConnectionStatus();

    if (timerRestore.alarm())
        restoreConnection();

    if (connectionAvailable)
        pollConnection();
}

bool Connection::available(void) const {
    return connectionAvailable;
}
