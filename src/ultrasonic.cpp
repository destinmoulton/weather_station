//
// Created by destin on 6/3/26.
//

#include "ultrasonic.h"

#include <Arduino.h>
#include <esp32-hal-gpio.h>

#include "pins.h"

// ── Static member init ────────────────────────────────────────────────────────
Ultrasonic* Ultrasonic::s_instance = nullptr;

// ── Constructor ───────────────────────────────────────────────────────────────
Ultrasonic::Ultrasonic(AppState& state, EventDispatcher& dispatcher)
    : m_app_state(state)
      , m_dispatcher(dispatcher)
      , m_sensor_state(SensorState::IDLE)
      , m_us_last_measured(0)
      , m_us_state_entered(0)
      , m_us_echo_start(0)
      , m_us_echo_end(0)
      , m_echo_ready(false)
      , m_distanceCm(0.0f)
      , m_distanceInch(0.0f)
{
}

// ── begin ─────────────────────────────────────────────────────────────────────
void Ultrasonic::begin()
{
    Serial.println("Ultrasonic::begin() - Configuring ultrasonic sensor...");

    s_instance = this;

    pinMode(PIN_US_TRIG, OUTPUT);
    digitalWrite(PIN_US_TRIG, LOW);
    pinMode(PIN_US_ECHO, INPUT);

    attachInterrupt(digitalPinToInterrupt(PIN_US_ECHO), echo_isr, CHANGE);
}

// ── ISR — catches both edges of the ECHO pulse ────────────────────────────────
void IRAM_ATTR Ultrasonic::echo_isr()
{
    if (digitalRead(PIN_US_ECHO) == HIGH)
    {
        s_instance->m_us_echo_start = micros();
    }
    else
    {
        s_instance->m_us_echo_end = micros();
        s_instance->m_echo_ready = true;
    }
}

// ── loop ──────────────────────────────────────────────────────────────────────
void Ultrasonic::loop()
{
    update_state();
}

// ── update_state ──────────────────────────────────────────────────────────────
void Ultrasonic::update_state()
{
    const unsigned long now_us = micros();

    switch (m_sensor_state)
    {
    // ── IDLE: wait for the 2000 ms measurement interval ──────────────────────
    case SensorState::IDLE:
        if ((now_us - m_us_last_measured) >= US_MEASURE_INTERVAL_US)
        {
            digitalWrite(PIN_US_TRIG, HIGH);
            m_us_state_entered = now_us;
            m_sensor_state = SensorState::TRIG_HIGH;
        }
        break;

    // ── TRIG_HIGH: hold TRIG HIGH for 2 ms ───────────────────────────────────
    case SensorState::TRIG_HIGH:
        if ((now_us - m_us_state_entered) >= US_TRIG_PULSE_US)
        {
            digitalWrite(PIN_US_TRIG, LOW);
            m_us_state_entered = now_us;
            m_echo_ready = false;
            m_sensor_state = SensorState::WAIT_ECHO;
        }
        break;

    // ── WAIT_ECHO: ISR captures both edges; we just wait for the result ───────
    case SensorState::WAIT_ECHO:
        if (m_echo_ready)
        {
            unsigned long pulse_us = m_us_echo_end - m_us_echo_start;
            m_distanceCm = pulse_us / 58.0f;
            m_distanceInch = pulse_us / 148.0f;

            Serial.printf("[Ultrasonic] Distance: %.1f cm  /  %.1f in\n",
                          m_distanceCm, m_distanceInch);

            m_us_last_measured = now_us;
            m_sensor_state = SensorState::IDLE;
        }
        else if ((now_us - m_us_state_entered) >= US_ECHO_TIMEOUT_US)
        {
            Serial.println("[Ultrasonic] Timeout — no echo received");
            m_distanceCm = -1.0f;
            m_distanceInch = -1.0f;
            m_us_last_measured = now_us;
            m_sensor_state = SensorState::IDLE;
        }
        break;
    }
}
