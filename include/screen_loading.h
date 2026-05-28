//
// Created by destin on 5/28/26.
//

#ifndef WEATHER_STATION_SCREEN_LOADING_H
#define WEATHER_STATION_SCREEN_LOADING_H
#include "screen.h"

class ScreenLoading : public Screen
{
public:
    ScreenLoading(Adafruit_SSD1306& device, AppState& state);
    void render() override;
};
#endif //WEATHER_STATION_SCREEN_LOADING_H
