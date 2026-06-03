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
    m_device.setTextSize(1);
    m_device.setCursor(0, 0);
    m_device.println("       Weather  ");
    m_device.println(" ");
    m_device.setTextSize(2);
    m_device.printf("%4.2f%c F\n", m_state.temperature, 0xF8);
    m_device.printf("%4.2f%% Hum\n", m_state.humidity);

    if (m_state.soil > 2700)
    {
        m_device.printf("%c%c%c%c", 0xB0, 0xB0, 0xB0, 0xB0);
    }
    else if (m_state.soil <= 2700 && m_state.soil > 2300)
    {
        m_device.printf("%c%c%c%c", 0xB2, 0xB0, 0xB0, 0xB0);
    }
    else if (m_state.soil <= 2300 && m_state.soil > 1900)
    {
        m_device.printf("%c%c%c%c", 0xB2, 0xB2, 0xB0, 0xB0);
    }
    else if (m_state.soil <= 1900 && m_state.soil > 1500)
    {
        m_device.printf("%c%c%c%c", 0xB2, 0xB2, 0xB2, 0xB0);
    }
    else if (m_state.soil <= 1500)
    {
        m_device.printf("%c%c%c%c", 0xB2, 0xB2, 0xB2, 0xB2);
    }
    //m_device.printf("%d Soil\n", m_state.soil);
    m_device.display();
}

void ScreenWeather::onLeft()
{
    m_dispatcher.dispatch(Event::JumpToSettingsScreen);
}

void ScreenWeather::onRight()
{
    m_dispatcher.dispatch(Event::JumpToSettingsScreen);
}
