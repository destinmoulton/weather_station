//
// Created by destin on 5/20/26.
//

#include <Adafruit_SSD1306.h> // oled
#include "display.h"

#include <Wire.h>

Display::Display(AppState& state, EventDispatcher& dispatcher)
    : m_state(state),
      m_dispatcher(dispatcher),
      m_active_screen(nullptr),
      m_screen_loading(m_oled, state, dispatcher),
      m_screen_weather(m_oled, state, dispatcher),
      m_screen_settings(m_oled, state, dispatcher),
      m_screen_wifi_info(m_oled, state, dispatcher)
{
    m_oled = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


    dispatcher.registerHandler(Event::PressButtonUp, [this]() { handlePressButtonUp(); });
    dispatcher.registerHandler(Event::PressButtonDown, [this]() { handlePressButtonDown(); });
    dispatcher.registerHandler(Event::PressButtonLeft, [this]() { handlePressButtonLeft(); });
    dispatcher.registerHandler(Event::PressButtonRight, [this]() { handlePressButtonRight(); });
    dispatcher.registerHandler(Event::NextView, [this]() { handleNextView(); });
    dispatcher.registerHandler(Event::WeatherInitialLoadComplete, [this]() { handleWeatherInitialLoadComplete(); });
    dispatcher.registerHandler(Event::WeatherUpdate, [this]() { handleWeatherUpdate(); });
    dispatcher.registerHandler(Event::JumpToWeatherScreen, [this]() { changeScreen(View::Weather); });
    dispatcher.registerHandler(Event::JumpToSettingsScreen, [this]() { changeScreen(View::Settings); });
    dispatcher.registerHandler(Event::JumpToWifiInfoScreen, [this]() { changeScreen(View::WifiInfo); });
}

Display::~Display()
{
    //Deconstructor
}

bool Display::begin()
{
    if (!m_oled.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        return false;
    }

    // Enable advanced character set (for things like degree symbol)
    m_oled.cp437(true);
    m_oled.setTextColor(WHITE);

    changeScreen(View::Loading);

    return true;
}

void Display::handleWeatherInitialLoadComplete()
{
    changeScreen(View::Weather);
}

void Display::handleWeatherUpdate()
{
    render();
}

void Display::handleShowWifiInfo()
{
}


void Display::handleNextView()
{
    switch (m_current_view)
    {
    case View::Loading:
        // Loading should lead directly to weather
        changeScreen(View::Weather);
        break;
    case View::Weather:
        changeScreen(View::Settings);
        break;
    case View::Settings:
        changeScreen(View::Weather);
        break;
    case View::WifiInfo:
        changeScreen(View::WifiInfo);
        break;
    }
}

void Display::handlePressButtonUp()
{
    m_active_screen->onUp();
}

void Display::handlePressButtonDown()
{
    m_active_screen->onDown();
}

void Display::handlePressButtonLeft()
{
    m_active_screen->onLeft();
}

void Display::handlePressButtonRight()
{
    m_active_screen->onRight();
}

void Display::changeScreen(const View view)
{
    m_current_view = view;

    switch (m_current_view)
    {
    case View::Loading:
        m_active_screen = &m_screen_loading;
        break;
    case View::Weather:
        m_active_screen = &m_screen_weather;
        break;
    case View::Settings:
        m_active_screen = &m_screen_settings;
        break;
    case View::WifiInfo:
        m_active_screen = &m_screen_wifi_info;
        break;
    }
    render();
}

void Display::render()
{
    m_active_screen->render();
}

