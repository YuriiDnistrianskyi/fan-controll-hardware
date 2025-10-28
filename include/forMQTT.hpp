#ifndef FOR_MQTT_HPP
#define FOR_MQTT_HPP

void reconnect();
void sendDataMQTT(float motorTemperature);
void callback(char* topic, byte* payload, unsigned int length);
void initMQTT();

#endif
