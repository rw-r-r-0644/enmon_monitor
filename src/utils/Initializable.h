/**
 * Initializable.h
 *
 * Oftentimes Arduino classes should be initialized
 * before use. This stems from the fact that in the
 * specific circumstance of embedded Arduino boards
 * with limited compute power and available heap
 * capacity, it is often considered reasonable to
 * utilise statically allocated global objects.
 *
 * This interface serves as an informal indication
 * of the need to initialize a class after instantiation.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once

class Initializable {
public:
    inline virtual void begin(void) {};
    inline virtual void end(void) {};
};
