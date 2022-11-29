// #include "Arduino.h"
#include "renderer.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// const char MAIN_page[] PROGMEM = R"=====(
// <!DOCTYPE html>
// <html>
// <body>

// <h2>Circuits4you<h2>
// <h3> HTML Form ESP8266</h3>

// <form action="/action_page">
//   Red<br>
//   <input type="range" name="red" value="0" min="0" max="255">
//   <br>
//   Green<br>
//   <input type="range" name="green" value="0" min="0" max="255">
//   <br>
//   Blue<br>
//   <input type="range" name="blue" value="0" min="0" max="255">
//   <br>
//   <br>
//   <input type="submit" value="Submit">
// </form>

// </body>
// </html>
// )=====";

const int fps = 60;
RgbColor black(0);
RgbColor bmBlue(0, 159, 223);
RgbColor currentColor(bmBlue);

Renderer renderer(10, 3);
// const char *ssid = "NodeMCU";      // Enter SSID here
// const char *password = "12345678"; // Enter Password here
// IPAddress local_ip(192, 168, 1, 1);
// IPAddress gateway(192, 168, 1, 1);
// IPAddress subnet(255, 255, 255, 0);
// ESP8266WebServer server(80);

// void handle_OnConnect()
// {
//   String s = MAIN_page;             // Read HTML contents
//   server.send(200, "text/html", s); // Send web page
// }

// void handle_NotFound()
// {
//   server.send(404, "text/plain", "Not found");
// }

// void handle_next()
// {
//   String red = server.arg("red");
//   String green = server.arg("green");
//   String blue = server.arg("blue");

//   currentColor = RgbColor(red.toInt(), green.toInt(), blue.toInt());

//   String s = "<a href='/' style=\"fontSize:50px\"> Go Back </a>";
//   server.send(200, "text/html", s); // Send web page
// }

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ; // wait for serial attach

  // WiFi.softAPConfig(local_ip, gateway, subnet);
  // WiFi.softAP(ssid);
  // delay(100);

  // server.on("/", handle_OnConnect);
  // server.on("/action_page", handle_next);
  // server.onNotFound(handle_NotFound);
  // server.begin();

  renderer.init();
}

uint8_t ycoord = 0;
uint8_t xcoord = 0;
u_int framesSinceStart = 0;
int direction = 1;

void loop()
{
  // server.handleClient();

  renderer.clear(black);

  renderer.setPixel(xcoord, 0, currentColor);
  renderer.setPixel(xcoord, 1, currentColor);
  renderer.setPixel(xcoord, 2, currentColor);

  xcoord = (xcoord + 1) % renderer.frameWidth;

  // if (xcoord >= renderer.frameWidth)
  // {
  //   direction = -1;
  // }
  // else if (xcoord <= 0)
  // {
  //   direction = 1;
  // }

  renderer.render();
  delay(1000 / fps);
  framesSinceStart++;
}
