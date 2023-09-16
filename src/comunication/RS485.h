#pragma once
#include <Arduino.h>

class RS485 : public Stream {
    SerialUART &serial;
    const int txPin, rxPin, dePin;

public:
    RS485(SerialUART &serial, int txPin, int rxPin, int dePin)
        : serial(serial), txPin(txPin), rxPin(rxPin), dePin(dePin) {}

    inline void begin(uint32_t baudrate)  {
        pinMode(dePin, OUTPUT);
        digitalWrite(dePin, LOW);

        serial.end();
        serial.setPinout(txPin, rxPin);
        serial.begin(baudrate);
    }
    inline void beginTransmission() {
        digitalWrite(dePin, HIGH);
    }
    inline void endTransmission() {
        serial.flush();
        digitalWrite(dePin, LOW);
    }

    /**
     * Stream interface implementation
     
     * (most of these passthrough functions
     *  should be inlined by the compiler)
     */
    inline int available() override {
        return serial.available();
    }
    inline int read() override {
        return serial.read();
    }
    inline int peek() override {
        return serial.peek();
    }
    inline size_t write(uint8_t ch) override {
        return serial.write(ch);
    }
    inline size_t write(const uint8_t *buffer, size_t size) override {
        return serial.write(buffer, size);
    }
    inline int availableForWrite() override {
        return serial.availableForWrite();
    }
    inline void flush() override {
        return serial.flush();
    }
};
