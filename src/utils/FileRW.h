/**
 * FileRW.h
 *
 * Wraps Arduino File to provide independent
 * read and write pointers.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include <SD.h>

class FileRW : public Stream {
    File file;
    bool fileOpen = false;
    int writePos = 0, readPos = 0;

public:
    bool open(const char *path, int mode);
    void close();
    inline bool good() {
        return fileOpen;
    }

    /**
     * Arduino Print interface implementation
     */
    size_t write(uint8_t data) override;
    size_t write(const uint8_t *buffer, size_t size) override;

    /**
     * Arduino Stream interface implementation
     */
    int available() override;
    int read() override;
    int peek() override;

    /* set read pointer */
    int seekg(int pos);
    int tellg();

    /* set write pointer */
    int seekp(int pos);
    int tellp();

    /* flush pending writes to SD */
    void flush(void);
};
