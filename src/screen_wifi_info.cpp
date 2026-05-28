//
// Created by destin on 5/28/26.
//

#include "screen.h"
#include "screen_wifi_info.h"
#include <WiFi.h>

ScreenWifiInfo::ScreenWifiInfo(Adafruit_SSD1306& device, AppState& state, EventDispatcher& dispatcher)
    : Screen(device, state, dispatcher)
{
}

void ScreenWifiInfo::render()
{
    m_device.clearDisplay();
    m_device.setTextSize(1);
    m_device.setCursor(0, 0);
    m_device.println("---   Wifi Info   ---");
    m_device.println(" ");
    m_device.print("IP: ");
    m_device.print(WiFi.localIP().toString());
    m_device.print("\n");
    m_device.print("Gate: ");
    m_device.print(WiFi.gatewayIP().toString());
    m_device.print("\n");
    m_device.print("Sub: ");
    m_device.print(WiFi.subnetMask().toString());
    m_device.print("\n");
    m_device.print("DNS: ");
    m_device.print(WiFi.dnsIP().toString());
    m_device.print("\n");

    m_device.print("\n");
    m_device.display();
}

void ScreenWifiInfo::onLeft()
{
    m_dispatcher.dispatch(Event::JumpToSettingsScreen);
}

