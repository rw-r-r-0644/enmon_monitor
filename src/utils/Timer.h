/**
 * Timer.h
 *
 * Provides timers with fixed waiting periods
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */

#pragma once
#include "Arduino.h"

class Timer {
protected:
    const uint32_t baseInterval, maxInterval;
    uint32_t interval, lastAlarm;
    bool enabled;

public:
    static inline constexpr uint32_t Seconds(int secs) {
        return secs * 1000;
    }
    static inline constexpr uint32_t Minutes(int mins) {
        return Seconds(mins * 60);
    }

    Timer(uint32_t baseInterval, uint32_t maxInterval, bool enabled = false);
    Timer(uint32_t interval, bool enabled = false);

    /**
     * If the timer is disabled, enables the timer,
     * alarm will sound after each fixed interval.
     * Otherwise does nothing
     *
     * If immediate is set, the first alarm will
     * sound immediatly
     */
    void enable(bool immediate = false);

    /**
     * Disable the timer, alarm will never sound
     */
    void disable();

    /**
     * Returns true each time the alarm sounds
     */
    bool alarm();
};
