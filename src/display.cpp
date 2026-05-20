//
// Created by destin on 5/20/26.
//

#include <Adafruit_SSD1306.h> // oled
#include "display.h"

#include <Wire.h>

Display::Display(AppState& state) : m_state(state)
{
    m_current_view = View::Loading;

    // Constructor
    m_oled = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
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

    viewLoading();

    return true;
}

void Display::viewLoading()
{
    if (m_current_view != View::Loading) return;

    m_oled.clearDisplay();

    m_oled.setTextSize(1);
    m_oled.setTextColor(WHITE);
    m_oled.setCursor(0, 10);
    // Display static text
    m_oled.println("Loading...");
    m_oled.display();
}

// NOTE: DO NOT DO ANY Serial printing in this function
void Display::viewWeather()
{
    if (m_current_view != View::Weather) return;

    m_oled.clearDisplay();

    m_oled.setTextSize(2);
    m_oled.setTextColor(WHITE);
    m_oled.setCursor(0, 10);

    m_oled.printf("%4.2f%c F\n", m_state.temperature, 0xF8);
    m_oled.printf("%4.2f%% Hum\n", m_state.humidity);

    m_oled.display();
}

// NOTE: DO NOT DO ANY Serial printing in this function
void Display::viewSettings()
{
    if (m_current_view != View::Settings) return;

    m_oled.clearDisplay();
    m_oled.setTextSize(1);
    m_oled.setTextColor(WHITE);
    m_oled.setCursor(0, 10);
    m_oled.print("IP: ");
    m_oled.print(m_state.ip);
    m_oled.display();
}
