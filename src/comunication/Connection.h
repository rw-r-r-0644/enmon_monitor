/**
 * Connection.h
 *
 * This class handles automatic connection /
 * reconnection to a given service which may
 * become unavailable.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include "Arduino.h"
#include "../utils/Timer.h"

class Connection {
    Timer timerCheck;
    Timer timerRestore;
    bool connectionAvailable;

protected:
    virtual void pollConnection(void);
    virtual void restoreConnection(void) = 0;
    virtual bool checkConnection(void) = 0;
    void updateConnectionStatus(void);

public:
    Connection(const Timer &timerCheck, const Timer &timerReconnect);

    /**
     * Setup timers and establish an initial connection
     */
    void begin(void);

    /**
     * Call this periodically to mantain
     * the connection active
     */
    void poll(void);

    /**
     * Returns current connection status
     */
    bool available(void) const;
};
