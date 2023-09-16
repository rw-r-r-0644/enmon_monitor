/**
 * StreamStore.h
 *
 * Stores arbitrary streams of data on SD files and
 * keeps track of the next read/write position in an
 * index file across reboots.
 * Multiple redundant copies of the index are stored
 * on the SD to improve reliability.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include "FileRW.h"

class StreamStore : public FileRW {
    static constexpr size_t indexFileCount = 2;
    File indexFile[indexFileCount];

    /* the index stores the next data
     * file read and write position */
    struct Index {
        uint32_t generation;
        uint32_t writePos;
        uint32_t readPos;
    } index;

    void loadIndex();
    void updateIndex();

public:
    bool open(const std::string &basePath);
    void close();

    /* flush pending writes to file and update write index */
    void commitWrites();

    /* update read index */
    void commitReads();
};
