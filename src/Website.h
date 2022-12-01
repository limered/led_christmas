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
  <output>30</output>
  <br/>
  Fade Strength<br />
  <input type="range" name="fade" step="0.1" value="0.7" min="0.0" max="0.9" oninput="this.nextElementSibling.value = this.value"/>
  <output>0.7</output>
  <br />
  <input type="checkbox" id="usehsl" name="usehsl" value="usehsl">
  <label for="usehsl">Use Hue Shift</label><br/>
  Hue Speed<br />
  <input type="range" name="hue" step="0.01" value="0.01" min="0.0" max="0.6" oninput="this.nextElementSibling.value = this.value"/>
  <output>0.01</output>
  <br />
  <h3>Animations:</h3>
  <input type="checkbox" id="partyline" name="partyline" value="partyline">
  <label for="partyline">Partyline</label><br>
  <input type="checkbox" id="sparkle" name="sparkle" value="sparkle">
  <label for="sparkle">Sparkle</label><br>
  <input type="checkbox" id="tannenbaum" name="tannenbaum" value="tannenbaum">
  <label for="tannenbaum">Tannenbaum</label><br>
  <input type="checkbox" id="litbaum" name="litbaum" value="litbaum">
  <label for="litbaum">+ Lichter</label><br>
  <input type="checkbox" id="screensaver" name="screensaver" value="screensaver">
  <label for="screensaver">Screensaver</label><br>
  <br />
  <input type="submit" value="Submit" />
</form>

</body>
</html>
)=====";

const char *ssid = "EmilsZaubershirt"; // Enter SSID here
const char *password = "12345678";     // Enter Password here
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

String lastResult[9]{"45", "0.0", "0.01",
                     "partyline_off", "sparkle_off", "tannenbaum_off", "litbaum_off",
                     "screensaver", "usehsl_off"};

void handle_next()
{
  lastResult[0] = server.arg("speed");
  lastResult[1] = server.arg("fade");
  lastResult[8] = server.arg("usehsl");
  lastResult[2] = server.arg("hue");
  lastResult[3] = server.arg("partyline");
  lastResult[4] = server.arg("sparkle");
  lastResult[5] = server.arg("tannenbaum");
  lastResult[6] = server.arg("litbaum");
  lastResult[7] = server.arg("screensaver");

  String s = "<a href='/' style=\"fontSize:50px\"> Go Back </a>";
  server.send(200, "text/html", s); // Send web page
}
