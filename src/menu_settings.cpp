//
// Created by destin on 5/22/26.
//

#include "menu_settings.h"

#include "Adafruit_SSD1306.h"

MenuSettings::MenuSettings(Adafruit_SSD1306& device, AppState& state, EventDispatcher& dispatcher)
    : Menu(device, state, dispatcher)
{
    m_title = "---   Settings   ---";
    m_items.push_back(MenuItem{
        "Wifi Info", Event::JumpToWifiInfoScreen
    });
    m_items.push_back(MenuItem{
        "Restart Wifi", Event::WifiRestart
    });
    m_items.push_back(MenuItem{"Reboot", Event::Reboot});
}


