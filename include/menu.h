//
// Created by destin on 5/21/26.
//

#ifndef WEATHER_STATION_MENU_H
#define WEATHER_STATION_MENU_H
#include <vector>

#include "screen.h"
#include "event_dispatcher.h"

struct MenuItem
{
    String title;
    Event event;
};

class Menu : public Screen
{
public:
    Menu(Adafruit_SSD1306& device, AppState& state, EventDispatcher& dispatcher);
    void render() override;
    void onUp() override;
    void onDown() override;
    void onRight() override;
    void onLeft() override;

protected:
    uint16_t m_activeItemIndex;
    std::vector<MenuItem> m_items;
    String m_title;
    Event m_left_button_event;
};


#endif //WEATHER_STATION_MENU_H
