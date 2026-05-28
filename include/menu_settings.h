//
// Created by destin on 5/22/26.
//

#ifndef WEATHER_STATION_MENU_SETTINGS_H
#define WEATHER_STATION_MENU_SETTINGS_H
#include "menu.h"

class MenuSettings : public Menu
{
public:
    MenuSettings(Adafruit_SSD1306& device, AppState& state, EventDispatcher& dispatcher);
};

#endif //WEATHER_STATION_MENU_SETTINGS_H
