/**
 * FileRW.cpp
 *
 * Wraps Arduino File to provide independent
 * read and write pointers.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "FileRW.h"

bool FileRW::open(const char *path, int mode) {
    close();

    file = SD.open(path, FILE_WRITE);
    if (file)
        fileOpen = true;

    return fileOpen;
}

void FileRW::close() {
    if (!fileOpen)
        return;
    file.close();
    fileOpen = false;
}

size_t FileRW::write(uint8_t data) {
    if (!fileOpen)
        return 0;
    file.seek(writePos);
    size_t bytesWritten = file.write(data);
    writePos += bytesWritten;
    return bytesWritten;
}

size_t FileRW::write(const uint8_t *buffer, size_t size) {
    if (!fileOpen)
        return 0;
    file.seek(writePos);
    size_t bytesWritten = file.write(buffer, size);
    writePos += bytesWritten;
    return bytesWritten;
}

int FileRW::available() {
    return (fileOpen && writePos > readPos)
        ? (writePos - readPos) : 0;
}

int FileRW::read() {
    if (!fileOpen || !available())
        return -1;
    file.seek(readPos);
    int data = file.read();
    if (data >= 0) readPos++;
    return data;
}

int FileRW::peek() {
    if (!fileOpen || !available())
        return -1;
    file.seek(readPos);
    return file.read();
}

int FileRW::tellg() {
    return fileOpen ? readPos : -1;
}

int FileRW::tellp() {
    return fileOpen ? writePos : -1;
}

int FileRW::seekg(int pos) {
    if (!fileOpen || pos < 0 || readPos > writePos || !file.seek(pos))
        return -1;
    readPos = pos;
    return readPos;
}

int FileRW::seekp(int pos) {
    if (!fileOpen || !file.seek(pos))
        return -1;
    writePos = pos;
    if (readPos > writePos)
        readPos = writePos;
    return writePos;
}

void FileRW::flush(void) {
    if (!fileOpen)
        return;
    file.flush();
}
