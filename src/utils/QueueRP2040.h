/**
 * QueueRP2040.h
 *
 * Normally a generic queue implementation using atomics
 * or locks would suffice. Unfortunately, pico-sdk
 * and the Arduino Pico core do not provide an implementation
 * of atomic variables, and the Pico FreeRTOS port is not
 * currently compatible with WiFi (so we also can't rely
 * on generic FreeRTOS synchronization primitives).
 * We thus have to rely directly on pico-sdk synchronization
 * primitives (which are however incompatible with other
 * potential target platforms).
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include <atomic>
#include <Arduino.h>
#include "QueueInterface.h"

#ifdef ARDUINO_ARCH_RP2040

template <typename T, size_t N>
class QueueRP2040 : public QueueInterface<T> {
    semaphore_t freeSlots, dataSlots;
    unsigned int freeIndex, dataIndex;
    T buffer[N];

public:
    void begin(void) override {
        sem_init(&freeSlots, N, N);
        sem_init(&dataSlots, 0, N);
        freeIndex = dataIndex = 0;
    }

    bool full(void) override {
        return sem_available(&freeSlots) == 0;
    }

    void send(const std::function<void(T&)> producer) override {
        sem_acquire_blocking(&freeSlots);

        /* send message to queue */
        producer(buffer[freeIndex]);
        freeIndex = (freeIndex + 1) % N;

        sem_release(&dataSlots);
    }

    bool empty(void) override {
        return sem_available(&dataSlots) == 0;
    }

    void recv(const std::function<void(const T&)> consumer) override {
        sem_acquire_blocking(&dataSlots);

        /* read message from queue */
        consumer(buffer[dataIndex]);
        dataIndex = (dataIndex + 1) % N;

        sem_release(&freeSlots);
    }
};

#endif /* ARDUINO_ARCH_RP2040 */
