//
// Created by destin on 5/20/26.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1306.h> // oled
#include <memory>

#include "event_dispatcher.h"
#include "menu_settings.h"
#include "screen_loading.h"
#include "screen_weather.h"
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
    void handlePressButtonUp();
    void handlePressButtonDown();

protected:
    Adafruit_SSD1306 m_oled;
    const AppState& m_state;
    const EventDispatcher& m_dispatcher;
    View m_current_view;
    Screen* m_active_screen;
    ScreenLoading m_screen_loading;
    ScreenWeather m_screen_weather;
    MenuSettings m_screen_settings;
    void changeScreen(const View view);
    void render();

private:
};
#endif //DISPLAY_H
