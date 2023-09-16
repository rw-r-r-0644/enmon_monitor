/**
 * NetworkClass.cpp
 *
 * This class mantains a stable internet connection,
 * automatically reconnecting after connection losses.
 * In the future it may also handle automatic
 * Ethernet/WiFi/Cellular handover.
 *
 * The ESP32 provides a more convenient way to
 * archieve this result, WiFi.setAutoReconnect(true),
 * but it's not part of the standard Arduino WiFi
 * API, so it may not be present on other targets.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "Network.h"
#include "Arduino.h"
#include <WiFi.h>
#include "../Config.h"

NetworkClass Network;

NetworkClass::NetworkClass()
    : Connection(
        Timer(Timer::Seconds(5)),
        Timer(Timer::Seconds(30), Timer::Minutes(15))
    ) {}

void NetworkClass::restoreConnection(void) {
    WiFi.setTimeout(1000);
    WiFi.disconnect();
    WiFi.begin(CONFIG_WIFI_SSID, CONFIG_WIFI_PASS);
}

bool NetworkClass::checkConnection(void) {
    return WiFi.status() == WL_CONNECTED;
}
