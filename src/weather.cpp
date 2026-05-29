//
// Created by destin on 5/29/26.
//

#include "weather.h"
#include <DHT.h>

Weather::Weather(AppState& state, EventDispatcher& dispatcher)
    : m_state(state),
      m_dispatcher(dispatcher),
      m_dht(DHT_PIN, DHT_TYPE)
{
    // Initialize the temperature and humidity arrays for averaging
    for (int i = 0; i < DHT_NUM_TO_AVERAGE; i++)
    {
        m_temperatures[i] = 0.0;
        m_humidities[i] = 0.0;
    }
}

void Weather::begin()
{
    // Start DHT
    m_dht.begin();
}

void Weather::loop()
{
    // Don't use delay() so we can have a functional loop
    unsigned long current_millis = millis();

    if (current_millis - m_previous_time_checked >= DHT_DELAY_MS)
    {
        m_previous_time_checked = current_millis;

        // Read the sensor
        read_sensor();
    }
}

void Weather::read_sensor()
{
    float h = m_dht.readHumidity();
    // Read temperature as Farenheit
    float t = m_dht.readTemperature(true);

    if (isnan(h) || isnan(t))
    {
        Serial.println(F("Failed to read DHT sensor!"));
        return;
    }

    int count_nonzero_temperatures = 0;
    int count_nonzero_humidities = 0;
    float total_temperature = 0.0;
    float total_humidity = 0.0;
    for (int i = DHT_NUM_TO_AVERAGE - 1; i >= 0; i--)
    {
        if (i > 0)
        {
            // Shift the values for the averaging
            m_temperatures[i] = m_temperatures[i - 1];
            m_humidities[i] = m_humidities[i - 1];
        }
        else
        {
            // Zeroth element becomes the newest reading
            m_temperatures[0] = t;
            m_humidities[0] = h;
        }


        if (m_temperatures[i] != 0.0)
        {
            count_nonzero_temperatures++;
            total_temperature += m_temperatures[i];
        }
        if (m_humidities[i] != 0.0)
        {
            count_nonzero_humidities++;
            total_humidity += m_humidities[i];
        }
    }

    if (count_nonzero_temperatures > 0)
    {
        m_state.temperature = total_temperature / count_nonzero_temperatures;
    }

    if (count_nonzero_humidities > 0)
    {
        m_state.humidity = total_humidity / count_nonzero_humidities;
    }

    if (count_nonzero_temperatures == 1)
    {
        // Just one reading so initial load is complete
        m_dispatcher.dispatch(Event::WeatherInitialLoadComplete);
    }
    else if (count_nonzero_temperatures > 1)
    {
        // Regular weather updated
        m_dispatcher.dispatch(Event::WeatherUpdate);
    }

    //Serial.printf(
    //  "Measured Temp: %4.2f F | Count Temperature Measurements: %d | Average Temp: %4.2f F | Measured Humidity: %4.2f %% | Count Humidity Measurements: %d | Average Humidity: %4.2f %%",
    //  t, count_nonzero_temperatures, m_state.temperature, h, count_nonzero_humidities, m_state.humidity);
    //Serial.println("");
}
