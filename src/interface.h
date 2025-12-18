#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body style="font-family: Arial; font-size: 25px;">

<h1>Rainbow Controller<h1>

<form action="/action_page" style="width: 100vw; display: flex; flex-direction: column; justify-content: center; padding: 20px;">
  <div>
    <input type="text" id="latenight" name="latenight" value="" style="margin: 20px;">
    <label for="latenight"> More? </label>
  </div>
  Speed<br/>
  <input type="range" name="speed" value="50" min="10" max="120" oninput="this.nextElementSibling.value = this.value" />
  <output>50</output>
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
  <h3>Full Animations:</h3>
  <select name="animation" style="font-size: 50px;">
    <option value="runner">Runner</option>
    <option value="runner_front_to_back">Runner Bounce</option>
    <option value="sparkler">Sparkles</option>
    <option value="breather">Breathe</option>
    <option value="loading">Loading</option>
    <option value="moving_dot">Mouse</option>
    <option value="conway">Conway</option>
    <option value="runner_multi">Multirunner</option>
    <option value="icing">Traditional Ginger</option>
    <option value="waves">Waves</option>
  </select>
  <br />

  <input type="submit" value="Submit" style="font-size: 50px;"/>
</form>

</body>
</html>
)=====";

String animation_names[] = {
  "runner", 
  "runner_front_to_back", 
  "sparkler", 
  "breather", 
  "loading", 
  "moving_dot", 
  "conway", 
  "runner_multi",
  "icing",
  "waves"
};

const char *ssid = "GINGERBEAR"; // Enter SSID here
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

String lastResult[]{"60", "0.7", "0.01", "usehsl_", "waves", "demo", "latenight_"};

void handle_next()
{
  lastResult[0] = server.arg("speed");
  lastResult[1] = server.arg("fade");
  lastResult[2] = server.arg("hue");
  lastResult[3] = server.arg("usehsl");
  lastResult[4] = server.arg("animation");
  lastResult[5] = server.arg("demo");
  lastResult[6] = server.arg("latenight");
  

  String s = "Success";             // Read HTML contents
  server.send(200, "text/html", s); // Send web page
}

uint8_t animation_index(){
  for(uint8_t i = 0; i < 10; i++){
    if(animation_names[i] == lastResult[4]){
      return i;
    }
  }
  return -1;
}

uint8_t speed(){
  return lastResult[0].toInt();
}

float fade(){
  return lastResult[1].toFloat();
}

float hue_shift_speed(){
  return lastResult[2].toFloat();
}

bool use_hsl(){
  return lastResult[3] == "usehsl";
}

bool is_demo(){
  return lastResult[5] == "demo";
}

int pDemoAnimations = 10;
float switchTimer = 0;
float switchTime = 15;

void progress_demo_switcher(){
  if (switchTimer > switchTime){
      switchTimer = 0;
      lastResult[0] = String(random(10, 30), 2);
      lastResult[1] = String(random(40, 90) / 100.0, 2);
      lastResult[2] = "0.01";
      lastResult[3] = random(4) < 1 ? "usehsl" : "";
      lastResult[4] = animation_names[pDemoAnimations];
      pDemoAnimations = (pDemoAnimations + random(1, 4)) % 10;
    }
    else{
      switchTimer += 1.0 / speed();
    }
}

bool is_late(){
  return lastResult[6] == "latenight";
}