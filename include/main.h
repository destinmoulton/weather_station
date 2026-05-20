//
// Created by destin on 5/19/26.
//

#ifndef TEMP_AND_LCD_WITH_BUTTON_MAIN_H
#define TEMP_AND_LCD_WITH_BUTTON_MAIN_H

#include <WiFi.h>
void readDHTSensor();
void displayTempAndHumidity();
void displayWiFiInformation();
void clientConnectedToServer(WiFiClient client);
#endif //TEMP_AND_LCD_WITH_BUTTON_MAIN_H
