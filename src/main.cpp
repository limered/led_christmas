#include "Animations.h"
#include "website.h"

uint8_t fps = 30;
RgbColor black(0);
RgbColor bmBlue(0, 159, 223);
RgbColor currentColor(bmBlue);
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

uint8_t ycoord = 0;
uint8_t xcoord = 0;
int direction = 1;

void loop()
{
  server.handleClient();
  renderer.clearDegradation = lastResult[1].toFloat();
  renderer.clear(black);

  Tannenbaum(&renderer);

  fps = lastResult[0].toInt();
  renderer.render();
  delay(1000 / fps);
  renderer.framesSinceStart++;
}
