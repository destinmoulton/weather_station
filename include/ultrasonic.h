//
// Created by destin on 6/3/26.
//

#pragma once

#include "appstate.h"
#include "event_dispatcher.h"
#include <esp32-hal.h>

constexpr unsigned long US_MEASURE_INTERVAL_US = 2000000UL; // 2000 ms
constexpr unsigned long US_TRIG_PULSE_US = 2000UL; //    2 ms
constexpr unsigned long US_ECHO_TIMEOUT_US = 25000UL; //   25 ms (~4.3 m)

class Ultrasonic
{
public:
    Ultrasonic(AppState& state, EventDispatcher& dispatcher);

    void begin();
    void loop();

    float getDistanceCm() const { return m_distanceCm; }
    float getDistanceInch() const { return m_distanceInch; }

private:
    // ── State machine ─────────────────────────────────────────────────────────
    enum class SensorState : uint8_t
    {
        IDLE,
        TRIG_HIGH,
        WAIT_ECHO,
    };

    void update_state();

    // ── ISR ───────────────────────────────────────────────────────────────────
    static Ultrasonic* s_instance;
    static void IRAM_ATTR echo_isr();

    // ── Timing ────────────────────────────────────────────────────────────────
    unsigned long m_us_last_measured;
    unsigned long m_us_state_entered;
    volatile unsigned long m_us_echo_start;
    volatile unsigned long m_us_echo_end;
    volatile bool m_echo_ready;

    // ── Results ───────────────────────────────────────────────────────────────
    float m_distanceCm;
    float m_distanceInch;

    // ── State ─────────────────────────────────────────────────────────────────
    SensorState m_sensor_state;
    AppState& m_app_state;
    EventDispatcher& m_dispatcher;
};
