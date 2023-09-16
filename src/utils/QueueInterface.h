/**
 * QueueInterface.h
 *
 * Single producer, single consumer
 * circular buffer queue interface.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include <array>
#include <atomic>
#include <functional>

template <typename T>
class QueueInterface {
public:
    /**
     * Initializes the queue. Must be
     * called before using any other
     * QueueInterface function.
     */
    virtual void begin(void) = 0;

    /**
     * Determines whether the queue is
     * full and the next send operation
     * would block.
     */
    virtual bool full(void) = 0;

    /**
     * Produces and sends a message to the queue.
     */
    virtual void send(const std::function<void(T&)> producer) = 0;

    /**
     * Determines whether the queue is
     * empty and the next recv operation
     * would block.
     */
    virtual bool empty(void) = 0;

    /**
     * Receives and consumes a message from the queue.
     * If no message is available, blocks until a
     * message becomes available.
     */
    virtual void recv(const std::function<void(const T&)> consumer) = 0;
};
