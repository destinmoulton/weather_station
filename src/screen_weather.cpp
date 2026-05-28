//
// Created by destin on 5/28/26.
//

#include "screen.h"
#include "screen_weather.h"

ScreenWeather::ScreenWeather(Adafruit_SSD1306& device, AppState& state, EventDispatcher& dispatcher)
    : Screen(device, state, dispatcher)
{
}

void ScreenWeather::render()
{
    m_device.clearDisplay();
    m_device.setTextSize(2);
    m_device.setCursor(0, 0);
    m_device.printf("%4.2f%c F\n", m_state.temperature, 0xF8);
    m_device.printf("%4.2f%% Hum\n", m_state.humidity);
    m_device.display();
}
