//
// Created by destin on 5/21/26.
//

#include "screen.h"

#include "event_dispatcher.h"

Screen::Screen(Adafruit_SSD1306& device, AppState& state, EventDispatcher& dispatcher)
    : m_device(device), m_state(state), m_dispatcher(dispatcher)
{
}

void Screen::render()
{
}

void Screen::onUp()
{
}

void Screen::onDown()
{
}

void Screen::onRight()
{
}

void Screen::onLeft()
{
}
