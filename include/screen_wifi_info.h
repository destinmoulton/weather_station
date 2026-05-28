//
// Created by destin on 5/28/26.
//

#ifndef WEATHER_STATION_SCREEN_WIFI_INFO_H
#define WEATHER_STATION_SCREEN_WIFI_INFO_H

class ScreenWifiInfo : public Screen
{
public:
    ScreenWifiInfo(Adafruit_SSD1306& device, AppState& state, EventDispatcher& dispatcher);
    void render() override;
    void onLeft() override;
};
#endif //WEATHER_STATION_SCREEN_WIFI_INFO_H
