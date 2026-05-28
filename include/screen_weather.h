//
// Created by destin on 5/28/26.
//

#ifndef WEATHER_STATION_SCREEN_WEATHER_H
#define WEATHER_STATION_SCREEN_WEATHER_H

class ScreenWeather : public Screen
{
public:
    ScreenWeather(Adafruit_SSD1306& device, AppState& state, EventDispatcher& dispatcher);
    void render() override;
    void onLeft() override;
    void onRight() override;
};
#endif //WEATHER_STATION_SCREEN_WEATHER_H
