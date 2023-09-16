#pragma once
#include "utils/Queue.h"
#include "utils/Initializable.h"
#include "logger/LoggerMQTT.h"
#include "logger/LoggerSD.h"
#include "logger/LoggerStream.h"
#include "logger/CascadeLogger.h"
#include "logger/CompositeLogger.h"

class DataLogger : public Initializable {
    struct LogEntry {
        std::string topic;
        bool persistent;
        StaticJsonDocument<256> doc;
    };
    Queue<LogEntry, 8> queue;

    /* logging interfaces */
    LoggerSD sd;
    LoggerMQTT mqtt;
    LoggerStream serial;

    /* distribution */
    CascadeLogger mqttPersist;
    CompositeLogger persistentLogger;
    CompositeLogger volatileLogger;

public:
    DataLogger();
    void begin(void) override;
    
    /**
     * Foward messages to their destination,
     * and execute internal upkeeping operations
     * (keepalives, ...)
     */
    void poll(void);

    /**
     * Report sensor data
     * If persistent is set, information will be stored on
     * permanent storage (when available).
     */
    template<typename T>
    void report(const std::string &topic, const T& data, bool persistent = true) {
        queue.send([&](LogEntry &entry){
            entry.topic = topic;
            entry.persistent = persistent;
            entry.doc.set(data);
        });
    }
};
