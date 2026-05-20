//
// Created by destin on 5/20/26.
//

#ifndef WEATHER_STATION_EVENT_DISPATCHER_H
#define WEATHER_STATION_EVENT_DISPATCHER_H
#include <functional>
#include <unordered_map>
#include <iostream>

// scoped enum
enum class Event
{
    OnClick,
    OnHover,
    OnKeyPress,
    OnResize
};

// function event handler
using EventHandler = std::function<void()>;

class EventDispatcher
{
public:
    void registerHandler(Event event, EventHandler handler);
    void dispatch(Event event) const;

private:
    std::unordered_map<Event, EventHandler> handlers;
};
#endif //WEATHER_STATION_EVENT_DISPATCHER_H
