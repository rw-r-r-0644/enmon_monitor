/**
 * LoggerStream.h
 *
 * Logger implementation for Arduino Stream
 * (Serial ports, etc.)
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "LoggerStream.h"

LoggerStream::LoggerStream(Stream &stream)
    : stream(stream) {}

bool LoggerStream::log(const std::string &topic, const Message &message) {
    stream.print('[');
    stream.print(topic.c_str());
    stream.print(']');
    serializeJson(message, stream);
    stream.println();
    return true;
}
