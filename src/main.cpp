#include "renderer.h"
#include "website.h"

int fps = 10;
RgbColor black(0);
RgbColor bmBlue(0, 159, 223);
RgbColor currentColor(bmBlue);

Renderer renderer(10, 3);

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
}

uint8_t ycoord = 0;
uint8_t xcoord = 0;
u_int framesSinceStart = 0;
int direction = 1;

void loop()
{
  server.handleClient();
  renderer.clear(black);

  currentColor = RgbColor(lastResult[0].toInt(), lastResult[1].toInt(), lastResult[2].toInt());

  renderer.setPixel(xcoord, 0, currentColor);
  renderer.setPixel(xcoord, 1, currentColor);
  renderer.setPixel(xcoord, 2, currentColor);

  xcoord += direction;

  if (xcoord >= renderer.frameWidth - 1 || xcoord <= 0)
  {
    direction *= -1;
  }

  fps = lastResult[3].toInt();
  renderer.render();
  delay(1000 / fps);
  framesSinceStart++;
}
