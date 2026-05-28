//
// Created by destin on 5/28/26.
//

#include "screen.h"
#include "screen_wifi_info.h"

ScreenWifiInfo::ScreenWifiInfo(Adafruit_SSD1306& device, AppState& state, EventDispatcher& dispatcher)
    : Screen(device, state, dispatcher)
{
}

void ScreenWifiInfo::render()
{
    m_device.clearDisplay();
    m_device.setTextSize(1);
    m_device.setCursor(0, 0);
    m_device.println("----   Wifi Info   ----");
    m_device.print("IP: ");
    m_device.print(m_state.ip);
    m_device.print("\n");
    m_device.display();
}

void ScreenWifiInfo::onLeft()
{
    m_dispatcher.dispatch(Event::JumpToSettingsScreen);
}

