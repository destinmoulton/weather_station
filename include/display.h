//
// Created by destin on 5/20/26.
//

#pragma once

#include <Adafruit_SSD1306.h> // oled
#include <memory>

#include "event_dispatcher.h"
#include "menu_settings.h"
#include "screen_loading.h"
#include "screen_weather.h"
#include "screen_wifi_info.h"
#include "appstate.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_SLEEP_MS 10000 // Amount of ms before sleeping the display
#define OLED_RESET  -1

enum class View
{
    Loading = 0,
    Weather,
    Settings,
    WifiInfo,
    Count_View_States
};

class Display
{
public:
    Display(AppState& state, EventDispatcher& dispatcher);
    ~Display();
    bool begin();
    void loop();
    void handleNextView();
    void handleWeatherInitialLoadComplete();
    void handleWeatherUpdate();
    void handlePressAnyButton();
    void handlePressButtonUp();
    void handlePressButtonDown();
    void handlePressButtonLeft();
    void handlePressButtonRight();
    void handleShowWifiInfo();

protected:
    Adafruit_SSD1306 m_oled;
    const AppState& m_state;
    const EventDispatcher& m_dispatcher;
    View m_current_view;
    Screen* m_active_screen;
    ScreenLoading m_screen_loading;
    ScreenWeather m_screen_weather;
    MenuSettings m_screen_settings;
    ScreenWifiInfo m_screen_wifi_info;
    bool m_is_screen_awake;
    unsigned int m_sleep_timer_ms;

    void turnDisplayOn();
    void turnDisplayOff();

    void changeScreen(const View view);
    void render();

private:
};
