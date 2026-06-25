//
// Created by destin on 5/20/26.
//

#pragma once

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
    PressAnyButton,
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
