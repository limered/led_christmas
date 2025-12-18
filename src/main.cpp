// #include "Animations.h"
#include "animations1d.h"
#include "my_colors.h"
#include "interface.h"

uint8_t fps = 30;
Renderer renderer(45, 1);

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
  renderer.clearDegradation = fade();
  renderer.clear();

  if (is_demo()){
    progress_demo_switcher();
  }

  switch (animation_index())
  {
  case 0:
    runner(&renderer);
    break;
  case 1:
    runner_front_to_back(&renderer);
    break;
  case 2:
    sparkler(&renderer);
    break;
  case 3:
    breather(&renderer);
    break;
  case 4:
    loading(&renderer);
    break;
  case 5:
    moving_dot(&renderer);
    break;
  case 6:
    conway(&renderer);
    break;
  case 7:
    runner_multi(&renderer);
    break;
  case 8:
    icing(&renderer);
    break;
  case 9:
    waves(&renderer);
    break;
  default:
    // renderer.clear(red);
    strobo(&renderer);
    break;
  }


  fps = speed();
  renderer.render();
  delay(1000 / fps);
  renderer.framesSinceStart++;
  renderer.timeSinceStart += 1.0 / fps;

  useHsl = use_hsl();
  hueShiftSpeed = hue_shift_speed();
  ShiftHue();

  if(is_late()){
    renderer.saveMode = true;
  }
}
