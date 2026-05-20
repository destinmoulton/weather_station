//
// Created by destin on 5/20/26.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1306.h> // oled

#include "state.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET  -1

enum class View
{
    Loading,
    Weather,
    Settings
};

class Display
{
public:
    Display(AppState& state);
    ~Display();
    bool begin();

protected:
    Adafruit_SSD1306 m_oled;
    const AppState& m_state;
    View m_current_view;
    void viewLoading();
    void viewSettings();
    void viewWeather();

private:
};
#endif //DISPLAY_H
