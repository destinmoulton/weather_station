//
// Created by destin on 5/28/26.
//

#pragma once
#include "screen.h"

class ScreenLoading : public Screen
{
public:
    ScreenLoading(Adafruit_SSD1306& device, AppState& state, EventDispatcher& dispatcher);
    void render() override;
};
