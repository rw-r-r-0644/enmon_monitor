#pragma once
#include <ArduinoJson.h>
#include "StreamStore.h"

class MessagePackStore {
    StreamStore streamFile;
    int writeCommitFreq = -1, readCommitFreq = -1;
    int uncommittedWrites = 0, uncommittedReads = 0;
    int prevReadPos = -1;

public:
    bool open(const std::string &basePath,
        int readCommitFreq = -1, int writeCommitFreq = -1);
    bool available();

    /* write next MessagePack document */
    bool write(const JsonDocument &doc);

    /* read next MessagePack document */
    bool read(JsonDocument &doc);

    /* undo the very last read */
    bool unread(void);

    /* skip to the end of the file */
    void skip(void);
};
