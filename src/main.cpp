/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
*********/
#include "main.h"
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> // oled
#include <DHT.h>

#include "display.h"

const int OLED_NUMBER_PAGES = 2;
int oled_current_page = 1;

// Configuration values for the temp/humidity sensor
#define DHTPIN 19
#define DHTTYPE DHT11
#define NUM_TO_AVERAGE 30
const long DHT_DELAY_MS = 4000;
int dht_previous_ms = 0;
float temperatures[NUM_TO_AVERAGE];
float humidities[NUM_TO_AVERAGE];
float average_temperature = 0;
float average_humidity = 0;
DHT dht(DHTPIN, DHTTYPE);

// Button Pin
const int BUTTONPIN = 34;

// Setup web server (port 80)
WiFiServer server(80);
// Variable to store the HTTP request
String header;

// Wifi details
const char* SSID = "Bigger Brother";
const char* WIFI_PASSWORD = "TheOutpost575";

// Set your Static IP address
IPAddress local_IP(192, 168, 100, 125);
// Set your Gateway IP address
IPAddress gateway(192, 168, 100, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(1, 1, 1, 1); //optional
IPAddress secondaryDNS(8, 8, 4, 4);

AppState app_state{0.0, 0.0, String("0.0,0.0")};
Display display(app_state);

// The handler fired when the button is pressed
// NOTE: DO NOT DO ANY Serial printing in the interrupt methods - it will crash!
void IRAM_ATTR buttonPressHandler()
{
  // Change the "page" visible on the oled
  oled_current_page++;
  if (oled_current_page > OLED_NUMBER_PAGES)
  {
    // Reset back to the first page
    oled_current_page = 1;
  }
}

void setup()
{
  Serial.begin(115200);

  while (!Serial)
  {
    delay(10); // Wait for Serial to be ready
  }

  // Delay another 1 sec for the serial connection (buggy)
  delay(1000);

  // Initialize the temperature and humidity arrays for averaging
  for (int i = 0; i < NUM_TO_AVERAGE; i++)
  {
    temperatures[i] = 0.0;
    humidities[i] = 0.0;
  }

  Serial.println("\nConfiguring static ip...");
  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
  {
    Serial.println("Static IP Failed to configure");
  }

  // Connect to wifi
  //WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, WIFI_PASSWORD);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
  Serial.print("Connected to WiFi! Local ESP32 IP: ");
  Serial.println(WiFi.localIP());

  // Start the web server
  server.begin();


  // Setup the button pin
  pinMode(BUTTONPIN, INPUT);
  // Attach the interrupt function
  attachInterrupt(BUTTONPIN, buttonPressHandler, RISING);

  display.begin();

  // Start DHT
  dht.begin();
}


void loop()
{
  // Don't use delay() so we can have a functional loop
  unsigned long currentMillis = millis();


  if (currentMillis - dht_previous_ms >= DHT_DELAY_MS)
  {
    dht_previous_ms = currentMillis;

    // Read the sensor
    readDHTSensor();
  }

  WiFiClient client = server.available(); // Listen for incoming clients

  if (client)
  {
    clientConnectedToServer(client);
  }
}

void readDHTSensor()
{
  float h = dht.readHumidity();
  // Read temperature as Farenheit
  float t = dht.readTemperature(true);

  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Failed to read DHT sensor!"));
    return;
  }

  int count_nonzero_temperatures = 0;
  int count_nonzero_humidities = 0;
  float total_temperature = 0.0;
  float total_humidity = 0.0;
  for (int i = NUM_TO_AVERAGE - 1; i >= 0; i--)
  {
    if (i > 0)
    {
      // Shift the values for the averaging
      temperatures[i] = temperatures[i - 1];
      humidities[i] = humidities[i - 1];
    }
    else
    {
      // Zeroth element becomes the newest reading
      temperatures[0] = t;
      humidities[0] = h;
    }


    if (temperatures[i] != 0.0)
    {
      count_nonzero_temperatures++;
      total_temperature += temperatures[i];
    }
    if (humidities[i] != 0.0)
    {
      count_nonzero_humidities++;
      total_humidity += humidities[i];
    }
  }

  if (count_nonzero_temperatures > 0)
  {
    app_state.temperature = total_temperature / count_nonzero_temperatures;
  }

  if (count_nonzero_humidities > 0)
  {
    app_state.humidity = total_humidity / count_nonzero_humidities;
  }


  Serial.printf(
    "Measured Temp: %4.2f F | Count Temperature Measurements: %d | Average Temp: %4.2f F | Measured Humidity: %4.2f %% | Count Humidity Measurements: %d | Average Humidity: %4.2f %%",
    t, count_nonzero_temperatures, app_state.temperature, h, count_nonzero_humidities, app_state.humidity);
  Serial.println("");
}


void clientConnectedToServer(WiFiClient client)
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
      header += c;
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
          if (header.indexOf("GET /26/on") >= 0)
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
          client.printf("<p>Temperature: %4.2f &deg;F</p>", average_temperature);
          client.printf("<p>Humidity: %4.2f %%</p>", average_humidity);

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
  // Clear the header variable
  header = "";
  // Close the connection
  client.stop();
  Serial.println("Client disconnected.");
  Serial.println("");
}
