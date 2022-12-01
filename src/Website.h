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
  Fade Strength<br />
  <input type="range" name="fade" step="0.1" value="0.7" min="0.0" max="0.9" oninput="this.nextElementSibling.value = this.value"/>
  <output>0.7</output>
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

String lastResult[4]{"45", "0.7"};

void handle_next()
{
  lastResult[0] = server.arg("speed");
  lastResult[1] = server.arg("fade");

  String s = "<a href='/' style=\"fontSize:50px\"> Go Back </a>";
  server.send(200, "text/html", s); // Send web page
}
