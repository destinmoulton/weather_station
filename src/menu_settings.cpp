//
// Created by destin on 5/22/26.
//

#include "menu_settings.h"

#include "Adafruit_SSD1306.h"

MenuSettings::MenuSettings(Adafruit_SSD1306& device, AppState& state)
    : Menu(device, state)
{
    m_title = "---   Settings   ---";
    m_items.push_back("Wifi Info");
    m_items.push_back("Restart Wifi");
    m_items.push_back("Restart Device");
}


