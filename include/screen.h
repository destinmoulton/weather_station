//
// Created by destin on 5/21/26.
//

#ifndef WEATHER_STATION_SCREEN_H
#define WEATHER_STATION_SCREEN_H
#include "Adafruit_SSD1306.h"
#include "event_dispatcher.h"
#include "appstate.h"

class Screen
{
public:
    Screen(Adafruit_SSD1306& device, AppState& state, EventDispatcher& dispatcher);
    virtual void render();
    virtual void onUp();
    virtual void onDown();
    virtual void onRight();
    virtual void onLeft();

protected:
    Adafruit_SSD1306& m_device;
    const AppState& m_state;
    EventDispatcher& m_dispatcher;
};
#endif //WEATHER_STATION_SCREEN_H
