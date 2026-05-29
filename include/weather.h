//
// Created by destin on 5/29/26.
//

#ifndef WEATHER_STATION_WEATHER_H
#define WEATHER_STATION_WEATHER_H
#include "appstate.h"
#include "event_dispatcher.h"
#include <DHT.h>

#define DHT_PIN 19
#define DHT_TYPE DHT11
#define DHT_NUM_TO_AVERAGE 30
#define DHT_DELAY_MS 4000

class Weather
{
public:
    Weather(AppState& state, EventDispatcher& dispatcher);
    void begin();
    void loop();

private:
    unsigned long m_previous_time_checked;
    AppState& m_state;
    EventDispatcher& m_dispatcher;
    float m_temperatures[DHT_NUM_TO_AVERAGE];
    float m_humidities[DHT_NUM_TO_AVERAGE];
    float m_avg_temperature;
    float m_avg_humidity;
    DHT m_dht;
    void read_sensor();
};
#endif //WEATHER_STATION_WEATHER_H
