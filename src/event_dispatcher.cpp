#include "event_dispatcher.h"

void EventDispatcher::registerHandler(Event event, EventHandler handler)
{
    handlers[event] = std::move(handler);
}

void EventDispatcher::dispatch(Event event) const
{
    const auto it = handlers.find(event);
    if (it != handlers.end())
    {
        it->second(); // invoke the handler
    }
}
