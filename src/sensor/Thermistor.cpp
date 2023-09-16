/**
 * Thermistor.cpp
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
#include "Thermistor.h"
#include "../Config.h"
#include <Arduino.h>
#include <math.h>

Thermistor::Thermistor(int analogPin, double fixedR,
    double coeffA, double coeffB, double coeffC)
    : pin(analogPin), fixedR(fixedR)
    , coeffA(coeffA), coeffB(coeffB), coeffC(coeffC)
{}

void Thermistor::begin(void) {
    pinMode(pin, INPUT);
}

double Thermistor::readTemperature(void) {
    int sample = analogRead(pin);    
    double R = fixedR * (double(sample) / double(CONFIG_ADC_VALUES - sample));
    double lnR = log(R);
    double invT = coeffA + lnR * (coeffB + coeffC * (lnR * lnR));
    double degK = 1.0 / invT;
    return degK - 273.15;
}

