#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body style="font-family: Arial; font-size: 25px;">

<h1>Rainbow Controller<h1>

<form action="/action_page" style="width: 100vw; display: flex; flex-direction: column; justify-content: center; padding: 20px;">
  Speed<br/>
  <input type="range" name="speed" value="30" min="10" max="120" oninput="this.nextElementSibling.value = this.value" />
  <output>30</output>
  <br/>
  Fade Strength<br />
  <input type="range" name="fade" step="0.1" value="0.7" min="0.0" max="0.9" oninput="this.nextElementSibling.value = this.value"/>
  <output>0.7</output>
  <br />
  Hue Speed<br />
  <input type="range" name="hue" step="0.01" value="0.01" min="0.0" max="0.6" oninput="this.nextElementSibling.value = this.value"/>
  <output>0.01</output>
  <br />
  <div>
    <input type="checkbox" id="usehsl" name="usehsl" value="usehsl" style="transform: scale(4); margin: 20px;">
    <label for="usehsl"> Special Mode</label>
  </div>
  <div>
    <input type="checkbox" id="demo" name="demo" value="demo" style="transform: scale(4); margin: 20px;">
    <label for="demo"> Demo Mode </label>
  </div>
  <br/>
  <h3>Animations:</h3>
  <select name="animation" style="font-size: 50px;">
    <option value="partyline">Partyline</option>
    <!-- <option value="circle">Spinner</option> -->
    <!-- <option value="tunnel">Tunnel</option> -->
    <option value="sparkle">Sparkle</option>
    <!-- <option value="tannenbaum">Tannenbaum</option> -->
    <!-- <option value="litbaum">+ Lichter</option> -->
    <!-- <option value="screensaver">Screensaver</option> -->
    <option value="runner">Runner</option>
    <!-- <option value="star">Star</option> -->
    <!-- <option value="bmlogo">BM Logo</option> -->
    <!-- <option value="bigheart">Heart</option> -->
    <option value="ants">Ants</option>
    <option value="rain">Rain ON Meee</option>
    <option value="firework">Firework</option>
    <option value="colorwheel">Colorwheel</option>
    <option value="stacker">Stacker</option>
    <option value="waves">Waves</option>
  </select>
  <br />
  <input type="submit" value="Submit" style="font-size: 50px;"/>
</form>

</body>
</html>
)=====";



const char *ssid = "PARTYETI"; // Enter SSID here
const char *password = "4321";     // Enter Password here
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

String lastResult[]{"30", "0.7", "0.01", "usehsl_", "waves", "demo_"};

void handle_next()
{
  lastResult[0] = server.arg("speed");
  lastResult[1] = server.arg("fade");
  lastResult[2] = server.arg("hue");
  lastResult[3] = server.arg("usehsl");
  lastResult[4] = server.arg("animation");
  lastResult[5] = server.arg("demo");

  String s = MAIN_page;             // Read HTML contents
  server.send(200, "text/html", s); // Send web page
}
