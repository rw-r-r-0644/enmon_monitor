/**
 * Network.h
 *
 * This class mantains a stable internet connection,
 * automatically reconnecting after connection losses.
 * In the future it may also handle automatic
 * Ethernet/WiFi/Cellular handover.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include "Arduino.h"
#include "Connection.h"

class NetworkClass : public Connection {
    void restoreConnection(void) override;
    bool checkConnection(void) override;

public:
    NetworkClass();
};

/* This.. doesn't feel very safe, but as the
 * class interacts with the global WiFi class
 * defined by Arduino, even without globals
 * it would't be significantly safer...
 * This also allows for static allocation */
extern NetworkClass Network;
