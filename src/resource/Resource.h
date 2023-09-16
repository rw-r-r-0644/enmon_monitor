/**
 * Resource.h
 *
 * High-level abstraction for classes periodically
 * reporting processed information from one or more
 * hardware sensors.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include "../DataLogger.h"
#include "../utils/Initializable.h"

class Resource : public Initializable {
public:
    /**
     * Report available sensor information to
     * the provided message logger.
     * Returns true if all available information
     * was successfully read, false otherwise.
     */
    virtual bool read(DataLogger &logger) = 0;
};
