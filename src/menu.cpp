//
// Created by destin on 5/21/26.
//

#include "menu.h"

Menu::Menu(Adafruit_SSD1306& device, AppState& state, EventDispatcher& dispatcher)
    : Screen(device, state, dispatcher)
{
    m_activeItemIndex = 0;
    m_left_button_event = Event::JumpToWeatherScreen;
}

void Menu::render()
{
    m_device.clearDisplay();
    m_device.setTextSize(1);
    m_device.setCursor(0, 0);
    m_device.println(m_title);
    m_device.println(" ");

    for (int i = 0; i < m_items.size(); i++)
    {
        if (m_activeItemIndex == i)
        {
            m_device.print("> ");
        }
        else
        {
            // Print a space in liu of >
            m_device.print("  ");
        }
        m_device.print(m_items[i].title);
        m_device.print("\n");
    }
    m_device.display();
}

void Menu::onUp()
{
    if (m_activeItemIndex == 0)
    {
        m_activeItemIndex = m_items.size() - 1;
    }
    else
    {
        m_activeItemIndex--;
    }
    render();
}

void Menu::onDown()
{
    if (m_activeItemIndex == m_items.size() - 1)
    {
        m_activeItemIndex = 0;
    }
    else
    {
        m_activeItemIndex++;
    }
    render();
}

void Menu::onLeft()
{
    m_dispatcher.dispatch(m_left_button_event);
}

void Menu::onRight()
{
    m_dispatcher.dispatch(m_items[m_activeItemIndex].event);
}
