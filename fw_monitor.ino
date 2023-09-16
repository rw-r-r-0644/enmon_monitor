#include "src/Config.h"
#include "src/DataLogger.h"
#include "src/comunication/Network.h"
#include "src/Hardware.h"

static DataLogger logger;
static void initBarrier(int coreId);
static void waitNTP(void);

/**
 * Data reporting core
 */
void setup() {
    Serial.begin(115200);
    Serial.println("Initializing WiFi");
    Network.begin();
#ifdef CONFIG_REQUIRES_NTP
    waitNTP();
#endif
    Serial.println("Initializing data logger");
    logger.begin();
    Serial.println("Waiting for core 1 initialization");
    initBarrier(0);
    Serial.println("Ready");
}

void loop() {
    Network.poll();
    logger.poll();
    delay(100);
}


/**
 * Data collection core
 */
void setup1() {
    analogReadResolution(CONFIG_ADC_BITS);
    enmon.begin();
    initBarrier(1);
}

void loop1() {
    enmon.read(logger);
    delay(100);
}


/**
 * Wait for other core's initialization
 */
static void initBarrier(int coreId) {
    static volatile uint8_t coreReady[2] = {0, 0};
    std::atomic_thread_fence(std::memory_order_release);
    coreReady[coreId] = 1;
    while (!coreReady[!coreId]);
}


/**
 * Required for build configurations without external time sources
 */
static void waitNTP(void) {
    Serial.print("Waiting for a network connnection...");
    while (!Network.available()) {
        Serial.print(".");
        Network.poll();
        delay(500);
    }
    Serial.println("OK");

    NTP.begin("pool.ntp.org", "time.nist.gov");
    Serial.print("Waiting for NTP time sync");
    NTP.waitSet([]() { Serial.print("."); });
    Serial.println("OK");
}
