//
// Created by destin on 5/20/26.
//

#ifndef WEATHER_STATION_BUTTONS_H
#define WEATHER_STATION_BUTTONS_H
#include "event_dispatcher.h"

#define PIN_BUTTON_UP 34
#define PIN_BUTTON_DOWN 35
#define PIN_BUTTON_LEFT 32
#define PIN_BUTTON_RIGHT 33
#define BUTTON_DEBOUNCE_TIME 200


enum ButtonEvent
{
    BUTTON_UP = 0,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT,
    PIR_MOTION,
    STATE_COUNT_EVENTS // event count
};

class Buttons
{
public:
    Buttons(EventDispatcher& dispatcher);
    ~Buttons();
    void begin();

protected:
    static Buttons* m_instance;
    const EventDispatcher& m_dispatcher;
    uint32_t m_lastPressTimes[ButtonEvent::STATE_COUNT_EVENTS];
    static QueueHandle_t m_eventQueue;
    static void IRAM_ATTR onInterruptPressButton(void* arg);
    static void task(void* pvParameters);
};
#endif //WEATHER_STATION_BUTTONS_H
