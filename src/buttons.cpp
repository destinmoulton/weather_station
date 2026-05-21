//
// Created by destin on 5/20/26.
//

#include <Wire.h>
#include "buttons.h"

#include <Arduino.h>

#include "event_dispatcher.h"

// Stati definitions
Buttons* Buttons::m_instance = nullptr;
QueueHandle_t Buttons::m_eventQueue = nullptr;

Buttons::Buttons(EventDispatcher& dispatcher) : m_dispatcher(dispatcher)
{
    m_instance = this;

    // Create an event queue
    // This uses freeRTOS function call to allocate
    // the queue - it is non-locking - only running when
    // there are events in the queue
    m_eventQueue = xQueueCreate(10, sizeof(ButtonEvent));
    // The stack depth matters: too small and it might cause a crash!
    xTaskCreate(task, "ButtonTask", 8192, this, 1, nullptr);

    // Initialize the debounce variable
    for (int i = 0; i < ButtonEvent::STATE_COUNT_EVENTS; i++)
    {
        m_lastPressTimes[i] = 0;
    }
}

Buttons::~Buttons()
{
}

void Buttons::begin()
{
    // Set the button pin modes
    pinMode(PIN_BUTTON_UP, INPUT);
    pinMode(PIN_BUTTON_DOWN, INPUT);
    pinMode(PIN_BUTTON_LEFT, INPUT);
    pinMode(PIN_BUTTON_RIGHT, INPUT);

    attachInterruptArg(PIN_BUTTON_UP, onInterruptPressButton, (void*)(uintptr_t)BUTTON_UP, RISING);
    attachInterruptArg(PIN_BUTTON_DOWN, onInterruptPressButton, (void*)(uintptr_t)BUTTON_DOWN, RISING);
    attachInterruptArg(PIN_BUTTON_LEFT, onInterruptPressButton, (void*)(uintptr_t)BUTTON_LEFT, RISING);
    attachInterruptArg(PIN_BUTTON_RIGHT, onInterruptPressButton, (void*)(uintptr_t)BUTON_RIGHT, RISING);
}


// NOTE: DO NOT DO ANY Serial printing in the interrupt methods - it will crash!
void IRAM_ATTR Buttons::onInterruptPressButton(void* evt_arg)
{
    if (m_instance && m_instance->m_eventQueue)
    {
        const uint32_t now = millis();

        ButtonEvent evt = (ButtonEvent)(uintptr_t)evt_arg;
        if (now - m_instance->m_lastPressTimes[evt] > BUTTON_DEBOUNCE_TIME)
        {
            m_instance->m_lastPressTimes[evt] = now;
            // xQueueSendFromISR is ISR-safe
            BaseType_t higherPriorityTaskWoken = pdFALSE;
            xQueueSendFromISR(m_instance->m_eventQueue, &evt, &higherPriorityTaskWoken);
            // Yield to higher priority task if one was woken
            portYIELD_FROM_ISR(higherPriorityTaskWoken);
        }
    }
}

/**
 * task will be run by the freeRTOS
 * task/queue manager
 *
 * @param pvParameters
 */
void Buttons::task(void* pvParameters)
{
    const Buttons* self = static_cast<Buttons*>(pvParameters);
    ButtonEvent evt;

    // This looks locking - but it isn't
    // freeRTOS schedules it
    while (true)
    {
        // Block until an event arrives in the queue
        if (xQueueReceive(self->m_eventQueue, &evt, portMAX_DELAY))
        {
            switch (evt)
            {
            case ButtonEvent::BUTON_RIGHT:
                self->m_dispatcher.dispatch(Event::NextView);
                break;
            }
        }
    }
}

