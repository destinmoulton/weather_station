//
// Created by destin on 5/29/26.
//

#include "webserver.h"


WebServer::WebServer(AppState& state, EventDispatcher& dispatcher)
  : m_state(state),
    m_dispatcher(dispatcher),
    m_wifi_server(WEBSERVER_PORT)
{
}

void WebServer::begin()
{
  m_wifi_server.begin();
}

void WebServer::loop()
{
  WiFiClient client = m_wifi_server.available(); // Listen for incoming clients

  if (client)
  {
    client_connected(client);
  }
}

void WebServer::client_connected(WiFiClient& client)
{
  // If a new client connects,
  Serial.println("New Client."); // print a message out in the serial port
  String currentLine = ""; // make a String to hold incoming data from the client
  while (client.connected())
  {
    // loop while the client's connected
    if (client.available())
    {
      // if there's bytes to read from the client,
      char c = client.read(); // read a byte, then
      Serial.write(c); // print it out the serial monitor
      m_header += c;
      if (c == '\n')
      {
        // if the byte is a newline character
        // if the current line is blank, you got two newline characters in a row.
        // that's the end of the client HTTP request, so send a response:
        if (currentLine.length() == 0)
        {
          // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
          // and a content-type so the client knows what's coming, then a blank line:
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();

          // perform GET operations
          if (m_header.indexOf("GET /26/on") >= 0)
          {
          }

          // Display the HTML web page
          client.println("<!DOCTYPE html><html>");
          client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<link rel=\"icon\" href=\"data:,\">");
          // CSS to style the on/off buttons
          // Feel free to change the background-color and font-size attributes to fit your preferences
          client.println("<style>");
          client.println(
            "html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
          client.println("</style></head>");

          // Web Page Heading
          client.println("<body><h1>Greenhouse Web Server</h1>");

          // Display current temperature
          client.printf("<p>Temperature: %4.2f &deg;F</p>", m_state.temperature);
          client.printf("<p>Humidity: %4.2f %%</p>", m_state.humidity);

          client.println("</body></html>");

          // The HTTP response ends with another blank line
          client.println();
          // Break out of the while loop
          break;
        }
        else
        {
          // if you got a newline, then clear currentLine
          currentLine = "";
        }
      }
      else if (c != '\r')
      {
        // if you got anything else but a carriage return character,
        currentLine += c; // add it to the end of the currentLine
      }
    }
  }
  // Clear the m_header variable
  m_header = "";
  // Close the connection
  client.stop();
  Serial.println("Client disconnected.");
  Serial.println("");
}
