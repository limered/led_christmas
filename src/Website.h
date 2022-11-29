#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>

<h2>Rainbow Controller<h2>

<form action="/action_page" style="fontSize: 50px">
  Speed<br/>
  <input type="range" name="speed" value="30" min="10" max="120" oninput="this.nextElementSibling.value = this.value" />
  <output>10</output>
  <br/>
  Red<br />
  <input type="range" name="red" value="0" min="0" max="255" oninput="this.nextElementSibling.value = this.value"/>
  <output>10</output>
  <br />
  Green<br />
  <input type="range" name="green" value="0" min="0" max="255" oninput="this.nextElementSibling.value = this.value"/>
  <output>10</output>
  <br />
  Blue<br />
  <input type="range" name="blue" value="0" min="0" max="255" oninput="this.nextElementSibling.value = this.value"/>
  <output>10</output>
  <br />
  <br />
  <input type="submit" value="Submit" />
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

String lastResult[4]{"22", "0", "0", "30"};

void handle_next()
{
  lastResult[0] = server.arg("red");
  lastResult[1] = server.arg("green");
  lastResult[2] = server.arg("blue");
  lastResult[3] = server.arg("speed");

  String s = "<a href='/' style=\"fontSize:50px\"> Go Back </a>";
  server.send(200, "text/html", s); // Send web page
}
