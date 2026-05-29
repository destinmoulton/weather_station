//
// Created by destin on 5/28/26.
//

#include <WiFi.h>
#include <WiFiUdp.h>
#include "wifi_interface.h"

#include "event_dispatcher.h"
#include "appstate.h"

#define SSID "Bigger Brother"
#define PASSWORD "TheOutpost575"
#define IP 192,168,100,125
#define GATEWAY 192,168,100,1
#define SUBNET 255,255,255,0
#define PRIMARY_DNS 1,1,1,1
#define SECONDARY_DNS 8,8,8,8
#define NTP_SERVER "pool.ntp.org"
#define NTP_GMT_OFFSET -21600 // GMT-7 (IMPORTANT: negative for -7)

WifiInterface::WifiInterface(AppState& state, EventDispatcher& dispatcher)
    : m_wifi_ssid(SSID),
      m_wifi_password(PASSWORD),
      m_ntp_client(m_udp,NTP_SERVER,NTP_GMT_OFFSET),
      m_config_IP(IP),
      m_config_gateway(GATEWAY),
      m_config_subnet(SUBNET),
      m_config_primary_DNS(PRIMARY_DNS),
      m_config_secondary_DNS(SECONDARY_DNS)
{
}

bool WifiInterface::connect()
{
    WiFi.begin(SSID, PASSWORD);

    Serial.println("\nConfiguring static ip...");
    // Configures static IP address
    if (!WiFi.config(m_config_IP, m_config_gateway, m_config_subnet, m_config_primary_DNS, m_config_secondary_DNS))
    {
        Serial.println("Static IP Failed to configure...");
        return false;
    }

    Serial.println("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }

    // Synchronize the time
    m_udp.begin(123);

    // Show the time
    Serial.println(m_ntp_client.getUnixTime());

    Serial.print("Connected to WiFi! Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
    return true;
}
