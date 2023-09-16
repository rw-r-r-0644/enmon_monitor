# enmon_monitor
This repository contains the code for an energy monitoring device (for photovoltaics or other power generation plants) built using a Raspberry Pico W. The device can interface with Sofar ME3000SP inverters through the available Modbus RTU interface, or monitor generic plants using two CT sensors.  
Data is stored on an SD card and transmitted over MQTT when a connection to the MQTT broker is available.

## Required Arduino Libraries
- ArduinoMqttClient
- ArduinoJson

## Supported Monitoring Configuration
- Sofar ME3000SP Inverter (via RS485)
- Generic power plants using 2 CT sensors (battery monitoring unavailable)
- Mock/testing configuration with a single CT sensor and a thermistor used for monitoring the battery temperature (simulates the presence of a battery)

## Required Config Files
The necessary firmware configuration can be provided through `src/Config.h`.
