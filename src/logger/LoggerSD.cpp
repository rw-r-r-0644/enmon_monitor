/**
 * LoggerSD.cpp
 *
 * Logger implementation for writing SDCard CSV files.
 *
 * Received messages are dispatched to a CSV file
 * based on message type. Messages with the same
 * subject but different MessageType will be dropped.
 *
 * A cascade Logger can optionally be attached. Received
 * messages will be relayed to the cascade logger. If
 * some messages fail to be logged by the cascade logger,
 * they will be sent again during poll() when the cascade
 * logger becomes available again.
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "LoggerSD.h"
#include "../Config.h"

MessagePackStore &LoggerSD::getTopic(const std::string &topic) {
    /* new message topic */
    auto it = topicStore.find(topic);
    if (it != topicStore.end())
        return it->second;

    /* new message topic */
    topicStore[topic].open(topic,
        CONFIG_LOGGER_SD_FLUSH_FREQ, CONFIG_LOGGER_SD_FLUSH_FREQ);
    return topicStore[topic];
}

bool LoggerSD::read(Logger &cascade) {
    /* relay messages */
    for (auto &entry : topicStore) {
        const std::string &topic = entry.first;
        MessagePackStore &store = entry.second;

        while (store.available()) {
            if (!store.read(doc)) {
                /* Read failed, for some reason?
                * This shouldn't happen, give up relaying
                * old messages from this file */
                Serial.println("LoggerSD::read() file read failure!");
                store.skip();
                break;
            }

            if (!cascade.log(topic, doc)) {
                /* attached logger stopped delivering
                 * messages, stop relaying messages */
                store.unread();
                return false;
            }
        }
    }

    return true;
}

bool LoggerSD::backlog(const std::string &topic) {
    return getTopic(topic).available();
}

bool LoggerSD::log(const std::string &topic, const JsonDocument &message, bool syncRead) {
    /* (try to) log message to file */
    MessagePackStore &store = getTopic(topic);
    bool result = store.write(message);
    if (syncRead)
        store.skip();

    return result;
}
