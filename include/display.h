//
// Created by destin on 5/20/26.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1306.h> // oled

#include "event_dispatcher.h"
#include "state.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET  -1

enum class View
{
    Loading = 0,
    Weather,
    Settings,
    Count_View_States
};

class Display
{
public:
    Display(AppState& state, EventDispatcher& dispatcher);
    ~Display();
    bool begin();
    void handleNextView();
    void handleWeatherInitialLoadComplete();
    void handleWeatherUpdate();

protected:
    Adafruit_SSD1306 m_oled;
    const AppState& m_state;
    const EventDispatcher& m_dispatcher;
    View m_current_view;
    void updateView();
    void viewLoading();
    void viewSettings();
    void viewWeather();

private:
};
#endif //DISPLAY_H
