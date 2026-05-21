#include "event_dispatcher.h"

#include <HardwareSerial.h>

void EventDispatcher::registerHandler(Event event, EventHandler handler)
{
    handlers[event].push_back(std::move(handler));
}

void EventDispatcher::dispatch(Event event) const
{
    Serial.println("EventDispatcher::dispatch()");
    auto it = handlers.find(event);
    if (it != handlers.end())
    {
        for (const auto& handler : it->second)
        {
            handler();
        }
    }
}
