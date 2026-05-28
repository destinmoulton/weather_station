//
// Created by destin on 5/20/26.
//

#ifndef WEATHER_STATION_EVENT_DISPATCHER_H
#define WEATHER_STATION_EVENT_DISPATCHER_H
#include <functional>
#include <unordered_map>
#include <vector>

// scoped enum
enum class Event
{
    WeatherUpdate,
    WeatherInitialLoadComplete,
    NextView,
    JumpToWifiInfoScreen,
    JumpToWeatherScreen,
    JumpToSettingsScreen,
    WifiRestart,
    Reboot,
    PressButtonUp,
    PressButtonDown,
    PressButtonLeft,
    PressButtonRight,
};

// function event handler
using EventHandler = std::function<void()>;

class EventDispatcher
{
public:
    void registerHandler(Event event, EventHandler handler);
    void dispatch(Event event) const;

private:
    std::unordered_map<Event, std::vector<EventHandler>> handlers;
};
#endif //WEATHER_STATION_EVENT_DISPATCHER_H
