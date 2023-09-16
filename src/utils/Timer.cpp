/**
 * Timer.cpp
 *
 * Provides timers with fixed waiting periods
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */

#include "Timer.h"

Timer::Timer(uint32_t baseInterval, uint32_t maxInterval, bool enabled)
    : baseInterval(baseInterval)
    , maxInterval(maxInterval)
    , interval(baseInterval)
    , enabled(enabled)
{
    lastAlarm = enabled ? millis() : 0;
}

Timer::Timer(uint32_t interval, bool enabled)
    : Timer(interval, interval, enabled) {}

void Timer::enable(bool immediate) {
    if (enabled)
        return;

    lastAlarm = millis() - (immediate ? interval : 0);
    enabled = true;
}

void Timer::disable() {
    interval = baseInterval;
    enabled = false;
}

bool Timer::alarm() {
    if (!enabled)
        return false;

    uint32_t now = millis();
    if ((now - lastAlarm) < interval)
        return false;
    lastAlarm = now;

    interval += interval;
    if (interval > maxInterval)
        interval = maxInterval;

    return true;
}
