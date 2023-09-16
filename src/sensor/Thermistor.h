/**
 * Thermistor.h
 *
 * Generic thermistor temperature sensors support.
 * The thermistor should be wired up to the Arduino
 * as part of a voltage divider with a known fixed-value
 * resistor:
 *
 *  VCC -------------+
 *                   |
 *              [fixedR resistor]
 *                   |
 *  analogPin -------+
 *                   |
 *              [thermistor here]
 *                   |
 *                  --- GND
 *                   -
 * 
 * 
 * The resistence value is computed from the analog reading
 * and the known fixed-value resistor.
 * The correspoinding temperature is estimated from the
 * resistence value using the Steinhart–Hart equation
 * with the provided sensor calibration coefficients.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include "TemperatureSensor.h"

class Thermistor : public TemperatureSensor {
    const int pin;
    const double fixedR, coeffA, coeffB, coeffC;

public:
    /**
     * Temperature sensor constructor, where
     * analogPin
     *   is the analog pin to which the sensor is wired up to
     * fixedR
     *   is the value of the fixed resistor in the voltage divider
     * coeffA, coeffB, coeffC
     *   are the sensor calibration coefficient, which can be
     *   obtained from the sensor datasheet or by fitting the
     *   Steinhart–Hart equation to 3 known resistence/temperature
     *   measurements
     */
    Thermistor(int analogPin, double fixedR,
        double coeffA, double coeffB, double coeffC);

    void begin(void) override;
    double readTemperature(void) override;
};
