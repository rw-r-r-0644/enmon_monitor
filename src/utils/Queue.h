/**
 * Queue.h
 *
 * Sngle producer, single consumer
 * circular buffer queue interface.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include <array>
#include <atomic>
#include "QueueInterface.h"
#include "QueueRP2040.h"

#ifdef ARDUINO_ARCH_RP2040
template <typename T, size_t N>
using Queue = QueueRP2040<T,N>;
#else
#error TODO
#endif
