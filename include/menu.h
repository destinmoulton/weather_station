//
// Created by destin on 5/21/26.
//

#ifndef WEATHER_STATION_MENU_H
#define WEATHER_STATION_MENU_H
#include <vector>

#include "screen.h"


class Menu : public Screen
{
public:
    Menu(Adafruit_SSD1306& device, AppState& state);
    void render() override;
    void onUp() override;
    void onDown() override;

protected:
    uint16_t m_activeItemIndex;
    std::vector<String> m_items;
    String m_title;
};


#endif //WEATHER_STATION_MENU_H
