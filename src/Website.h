#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>

<h2>Circuits4you<h2>
<h3> HTML Form ESP8266</h3>

<form action="/action_page">
  Red<br>
  <input type="range" name="red" value="0" min="0" max="255">
  <br>
  Green<br>
  <input type="range" name="green" value="0" min="0" max="255">
  <br>
  Blue<br>
  <input type="range" name="blue" value="0" min="0" max="255">
  <br>
  <br>
  <input type="submit" value="Submit">
</form>

</body>
</html>
)=====";

const char *ssid = "NodeMCU";      // Enter SSID here
const char *password = "12345678"; // Enter Password here
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
ESP8266WebServer server(80);

void handle_OnConnect()
{
  String s = MAIN_page;             // Read HTML contents
  server.send(200, "text/html", s); // Send web page
}

void handle_NotFound()
{
  server.send(404, "text/plain", "Not found");
}

String lastResult[3];

void handle_next()
{
  lastResult[0] = server.arg("red");
  lastResult[1] = server.arg("green");
  lastResult[2] = server.arg("blue");

  String s = "<a href='/' style=\"fontSize:50px\"> Go Back </a>";
  server.send(200, "text/html", s); // Send web page
}
