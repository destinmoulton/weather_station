//
// Created by destin on 5/28/26.
//

#ifndef WEATHER_STATION_WIFI_H
#define WEATHER_STATION_WIFI_H

#include <WiFi.h>
#include "appstate.h"
#include "event_dispatcher.h"


class WifiInterface
{
public:
    WifiInterface(AppState& state, EventDispatcher& dispatcher);
    bool connect();

private:
    const char* m_wifi_ssid;
    const char* m_wifi_password;
    const IPAddress m_config_IP;
    const IPAddress m_config_gateway;
    const IPAddress m_config_subnet;
    const IPAddress m_config_primary_DNS;
    const IPAddress m_config_secondary_DNS;
};
#endif //WEATHER_STATION_WIFI_H
