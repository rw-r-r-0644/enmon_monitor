/**
 * MeterCT.cpp
 *
 * Grid current measurement and power estimation
 * using current transformer sensors (such
 * as the SCT-013 split core transformer).
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "MeterCT.h"
#include "../Config.h"
#include <Arduino.h>


MeterCT::MeterCT(int analogPin, double calibration)
    : pin(analogPin)
    , calibration(calibration)
{
    /**
     * Account for voltage divider DC bias that
     * ensures the signal remains positive
     */
    sampleCenter = double(CONFIG_ADC_VALUES) / 2.0;
}

void MeterCT::begin(void) {
    pinMode(pin, INPUT);
}

double MeterCT::readCurrent(void) {
    double sampleSquareSum = 0;

    long start = millis();
    long sampleCount = 0;

    while ((millis() - start) < minReadMs) {
        double sample = analogRead(pin);
        Serial.println(sample);

        /**
         * The center of the signal (0V) might not match exactly
         * the center of ADC values, due to imperfections in the bias
         * and the ADC. Keep a moving average of the current voltage
         * to approximate the center of the signal.
         */
        sampleCenter = (1023 * sampleCenter + sample) / 1024;

        /* center sample around 0V */
        double sampleCentered = sample - sampleCenter;
        sampleSquareSum += sampleCentered * sampleCentered;
        sampleCount++;
        delayMicroseconds(50);
    }

    /* compute RMS */
    double sampleRMS = sqrt(sampleSquareSum / sampleCount);
    double voltageRMS = (sampleRMS * double(CONFIG_VCC_VOLTAGE)) /
        (double(CONFIG_ADC_VALUES) * 1000.0 /* mV -> V */);
    return calibration * voltageRMS;
}
