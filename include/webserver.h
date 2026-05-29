//
// Created by destin on 5/29/26.
//

#ifndef WEATHER_STATION_WEBSERVER_H
#define WEATHER_STATION_WEBSERVER_H

#include <WiFi.h>
//#include <WiFiServer.h>
#include "appstate.h"
#include "event_dispatcher.h"

#define WEBSERVER_PORT 8080

class WebServer
{
public:
    WebServer(AppState& state, EventDispatcher& dispatcher);
    void begin();
    void loop();

private:
    AppState& m_state;
    EventDispatcher& m_dispatcher;
    WiFiServer m_wifi_server;
    String m_header;
    void client_connected(WiFiClient& client);
};
#endif //WEATHER_STATION_WEBSERVER_H
