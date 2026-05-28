//
// Created by destin on 5/28/26.
//

#include "screen_loading.h"

#include "Adafruit_SSD1306.h"
#include "state.h"

ScreenLoading::ScreenLoading(Adafruit_SSD1306& device, AppState& state)
    : Screen(device, state)
{
}

void ScreenLoading::render()
{
    m_device.clearDisplay();

    m_device.setTextSize(2);
    m_device.setCursor(0, 30);
    // Display static text
    m_device.println("Loading...");
    m_device.display();
}
