#include "Animations.h"
#include "website.h"

uint8_t fps = 30;
RgbColor black(0);
Renderer renderer(10, 10);

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

  if (lastResult[3] == "partyline")
  {
    PartyLine(&renderer);
  }
  if (lastResult[12] == "circle")
  {
    Circle(&renderer);
  }
  if (lastResult[14] == "tunnel")
  {
    Tunnel(&renderer);
  }
  if (lastResult[4] == "sparkle")
  {
    Sparkle(&renderer);
  }
  if (lastResult[5] == "tannenbaum")
  {
    Tannenbaum(&renderer);
  }
  if (lastResult[6] == "litbaum")
  {
    TannenbaumLights(&renderer);
  }
  if (lastResult[7] == "screensaver")
  {
    HslBlock(&renderer);
  }
  if (lastResult[13] == "runner")
  {
    Runner(&renderer);
  }
  if (lastResult[10] == "star")
  {
    Star(&renderer);
  }
  if (lastResult[9] == "bmlogo")
  {
    BmLogo(&renderer);
  }
  if (lastResult[11] == "bigheart")
  {
    BigHeart(&renderer);
  }
  if (lastResult[15] == "ants")
  {
    Ants(&renderer);
  }
  if (lastResult[16] == "rain")
  {
    RainOnMe(&renderer);
  }
  if (lastResult[17] == "starfield")
  {
    Starfield(&renderer);
  }

  fps = lastResult[0].toInt();
  renderer.render();
  delay(1000 / fps);
  renderer.framesSinceStart++;

  useHsl = lastResult[8] == "usehsl";
  hueShiftSpeed = lastResult[2].toFloat();
  ShiftHue();
}
