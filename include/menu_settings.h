//
// Created by destin on 5/22/26.
//

#pragma once

#include "menu.h"

class MenuSettings : public Menu
{
public:
    MenuSettings(Adafruit_SSD1306& device, AppState& state, EventDispatcher& dispatcher);
};
