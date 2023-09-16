#include "DataLogger.h"
#include "Config.h"

DataLogger::DataLogger()
    : mqtt(CONFIG_MQTT_BROKER, CONFIG_MQTT_BROKER_PORT)
    , serial(Serial)
    , mqttPersist(sd, mqtt)
    , persistentLogger(serial, mqttPersist)
    , volatileLogger(serial, mqtt)
{}

void DataLogger::begin(void) {
    queue.begin();
    mqtt.begin();

    SPI.setRX(CONFIG_PIN_SD_MISO);
    SPI.setTX(CONFIG_PIN_SD_MOSI);
    SPI.setSCK(CONFIG_PIN_SD_SCK);
    SD.begin(CONFIG_PIN_SD_CS);
}
 
void DataLogger::poll(void) {
    persistentLogger.poll();

    while (!queue.empty()) {
        queue.recv([&](const LogEntry &entry) {
            Logger &logger = entry.persistent ? persistentLogger : volatileLogger;
            logger.log(entry.topic, entry.doc);
        });
    }
}
