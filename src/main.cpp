/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
*********/
#include "main.h"
#include <Wire.h>

#include "buttons.h"
#include "display.h"
#include "event_dispatcher.h"
#include "weather.h"
#include "webserver.h"
#include "wifi_interface.h"


// Create the local instances
AppState app_state{0.0, 0.0};

// Event Handler/Dispatcher
EventDispatcher dispatcher;
Buttons buttons(dispatcher);
Display display(app_state, dispatcher);
WifiInterface wifi_interface(app_state, dispatcher);
Weather weather(app_state, dispatcher);
WebServer webserver(app_state, dispatcher);

void setup()
{
  Serial.begin(115200);

  while (!Serial)
  {
    delay(10); // Wait for Serial to be ready
  }

  // Delay another 1 sec for the serial connection (buggy)
  delay(1000);


  // configure the dispatcher to run a reboot if requested
  dispatcher.registerHandler(Event::Reboot, []
  {
    ESP.restart();
  });


  wifi_interface.connect();

  // Start the web server
  webserver.begin();

  // Start the buttons
  buttons.begin();

  // Start the display
  display.begin();

  // Start the weather monitoring
  weather.begin();
}


void loop()
{
  // Run the weather loop
  weather.loop();

  // Run the webserver loop
  webserver.loop();
}
