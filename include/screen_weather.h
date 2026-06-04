//
// Created by destin on 5/28/26.
//

#pragma once

class ScreenWeather : public Screen
{
public:
    ScreenWeather(Adafruit_SSD1306& device, AppState& state, EventDispatcher& dispatcher);
    void render() override;
    void onLeft() override;
    void onRight() override;
};
