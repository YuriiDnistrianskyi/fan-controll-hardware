#ifndef FOR_MQTT_HPP
#define FOR_MQTT_HPP

#include "PowerFanEnum.hpp"

void reconnect();
void sendDataMQTT(float temperature, float pressure, bool fanState, PowerFanEnum powerFan);
void callback(char* topic, byte* payload, unsigned int length);
void initMQTT();

#endif
