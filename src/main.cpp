#include "Animations.h"
#include "website.h"

uint8_t fps = 30;
RgbColor black(0);
Renderer renderer(25, 8);

float timeSinceStart = 0;
float switchTime = 4*60; // 4 minutes

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ; // wait for serial attach

  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid);
  delay(100);

  server.on("/", handle_OnConnect);
  server.on("/action_page", handle_next);
  server.onNotFound(handle_NotFound);
  server.begin();

  renderer.init();

  renderer.clear(black);
}

void loop()
{
  server.handleClient();
  renderer.clearDegradation = lastResult[1].toFloat();
  renderer.clear();

  if (lastResult[4] == "partyline")
  {
    PartyLine(&renderer);
  }
  if (lastResult[4] == "circle")
  {
    Circle(&renderer);
  }
  if (lastResult[4] == "tunnel")
  {
    Tunnel(&renderer);
  }
  if (lastResult[4] == "sparkle")
  {
    Sparkle(&renderer);
  }
  if (lastResult[4] == "tannenbaum")
  {
    Tannenbaum(&renderer);
  }
  if (lastResult[4] == "litbaum")
  {
    TannenbaumLights(&renderer);
  }
  if (lastResult[4] == "screensaver")
  {
    HslBlock(&renderer);
  }
  if (lastResult[4] == "runner")
  {
    Runner(&renderer);
  }
  if (lastResult[4] == "star")
  {
    Star(&renderer);
  }
  if (lastResult[4] == "bmlogo")
  {
    BmLogo(&renderer);
  }
  if (lastResult[4] == "bigheart")
  {
    BigHeart(&renderer);
  }
  if (lastResult[4] == "ants")
  {
    Ants(&renderer);
  }
  if (lastResult[4] == "rain")
  {
    RainOnMe(&renderer);
  }
  if (lastResult[4] == "firework")
  {
    Firework(&renderer);
  }

  fps = lastResult[0].toInt();
  renderer.render();
  delay(1000 / fps);
  renderer.framesSinceStart++;
  timeSinceStart += 1.0 / fps;

  useHsl = lastResult[3] == "usehsl";
  hueShiftSpeed = lastResult[2].toFloat();
  ShiftHue();
}
