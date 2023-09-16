#pragma once

class Pollable {
    /**
     * Execute periodic internal operations
     * (keep alives, reconnections, ...).
     */
    virtual void poll() = 0;
};
