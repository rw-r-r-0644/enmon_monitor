#include "StreamStore.h"
#include <string>

bool StreamStore::open(const std::string &basePath) {
    /* attempt to open data and index files */
    SD.mkdir(basePath.c_str());

    bool okay = FileRW::open((basePath + std::string("/data")).c_str(), FILE_WRITE);
    for (size_t i = 0; okay && i < indexFileCount; i++) {
        indexFile[i] = SD.open((basePath + std::string("/index") + std::to_string(i)).c_str(), FILE_WRITE);
        okay = okay && indexFile[i];
    }
    if (okay) {
        /* load latest index */
        loadIndex();
        seekp(index.writePos);
        seekg(index.readPos);
        return true;
    }

    FileRW::close();
    for (size_t i = 0; i < indexFileCount; i++) {
        if (!indexFile[i]) continue;
        indexFile[i].close();
    }
    return false;
}

void StreamStore::close() {
    if (!good())
        return;

    close();
    for (size_t i = 0; i < indexFileCount; i++)
        indexFile[i].close();
}

void StreamStore::loadIndex() {
    if (!good()) return;

    /* find and load the latest index */
    size_t latest = 0;
    for (size_t i = 0; i < indexFileCount; i++) {
        struct Index i_index;
        indexFile[i].seek(0);

        if (indexFile[i].available() < sizeof(i_index))
            continue; /* new or bad index */

        indexFile[i].read((uint8_t *)&i_index, sizeof(i_index));
        if (i_index.generation < latest)
            continue; /* not the latest index */

        latest = i_index.generation;
        memcpy(&index, &i_index, sizeof(index));
    }

    /* new store */
    if (latest == 0)
        index.readPos = index.writePos = 0;
}

void StreamStore::updateIndex() {
    if (!good())
        return;

    /* update i-th index */
    size_t i = ++index.generation % indexFileCount;
    indexFile[i].seek(0);
    indexFile[i].write((uint8_t *)&index, sizeof(index));
    indexFile[i].flush(); /* write to fs */
}

void StreamStore::commitWrites() {
    if (!good())
        return;
    flush();
    index.writePos = tellp();
    updateIndex();
}

void StreamStore::commitReads() {
    if (!good())
        return;
    index.readPos = tellg();
    updateIndex();
}
