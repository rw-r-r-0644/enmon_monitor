#include "MessagePackStore.h"

bool MessagePackStore::open(const std::string &basePath, int readCommitFreq, int writeCommitFreq) {
    this->readCommitFreq = readCommitFreq;
    this->writeCommitFreq = writeCommitFreq;
    return this->streamFile.open(basePath);
}

bool MessagePackStore::available() {
    return streamFile.available() > 0;
}

bool MessagePackStore::read(JsonDocument &doc) {
    /**
     * For reads we commit an entry immediatly before
     * reading the next one, as otherwise we have no
     * way of knowing if the rest of the program properly
     * processed/utilised the data in the event of a sudden
     * shutdown.
     */
    if (uncommittedReads == readCommitFreq) {
        streamFile.commitReads();
        uncommittedReads = 0;
    }

    prevReadPos = streamFile.tellg();
    if (deserializeMsgPack(doc, streamFile))
        return false;

    uncommittedReads++;
    return true;
}

bool MessagePackStore::write(const JsonDocument &doc) {
    if (!serializeMsgPack(doc, streamFile))
        return false;

    if (uncommittedWrites++ == writeCommitFreq) {
        streamFile.commitWrites();
        uncommittedWrites = 0;
        Serial.println("commited writes to SD");
    }
    return true;
}

bool MessagePackStore::unread(void) {
    if (!uncommittedReads || prevReadPos < 0 || streamFile.tellg() <= prevReadPos)
        return false;

    uncommittedReads--;
    streamFile.seekg(prevReadPos);
    prevReadPos = -1;
    return true;
}

void MessagePackStore::skip(void) {
    streamFile.seekg(streamFile.tellp());
}
