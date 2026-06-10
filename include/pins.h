//
// Created by destin on 6/3/26.
//

#pragma once

#if defined(BOARD_ESP32_S3)
// Buttons
#define PIN_BUTTON_UP 2
#define PIN_BUTTON_DOWN 42
#define PIN_BUTTON_LEFT 41
#define PIN_BUTTON_RIGHT 40

// Weather Pins
#define PIN_DHT_SENSOR 1
#define PIN_SOIL_SENSOR 4

#define OLED_PIN_SDA 8
#define OLED_PIN_SCL 9

#elif defined(BOARD_ESP32D)

// Buttons
#define PIN_BUTTON_UP 23
#define PIN_BUTTON_DOWN 22
#define PIN_BUTTON_LEFT 19
#define PIN_BUTTON_RIGHT 21

// Weather Pins
#define PIN_DHT_SENSOR 4
#define PIN_SOIL_A_SENSOR 34
#define PIN_SOIL_B_SENSOR 35

#define OLED_PIN_SDA 32
#define OLED_PIN_SCL 33
#else
#endif
