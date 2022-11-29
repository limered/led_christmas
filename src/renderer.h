#include "Arduino.h"
#include <NeoPixelBus.h>

class Renderer
{
  static const uint16_t pixelCount = 30;
  static const uint8_t pixelPin = 2;
  float clearDegradation = 0.8;
  NeoPixelBus<NeoGrbwFeature, Neo800KbpsMethod> strip;
  RgbColor frameBuffer[pixelCount];

public:
  Renderer(uint8_t w, uint8_t h)
      : strip(pixelCount, pixelPin)
  {
    frameWidth = w;
    frameHeight = h;
  }

  uint8_t frameWidth;
  uint8_t frameHeight;

  void init()
  {
    strip.Begin();
    strip.Show();
  }

  void clear(RgbColor col)
  {
    for (size_t i = 0; i < pixelCount; i++)
    {
      strip.SetPixelColor(i, col);
      int r = frameBuffer[i].R * clearDegradation;
      int g = frameBuffer[i].G * clearDegradation;
      int b = frameBuffer[i].B * clearDegradation;
      frameBuffer[i] = RgbColor(r, g, b);
    }
    strip.Show();
  }

  void render()
  {
    for (size_t i = 0; i < pixelCount; i++)
    {
      strip.SetPixelColor(i, frameBuffer[i]);
    }
    strip.Show();
  }

  void setPixel(int x, int y, RgbColor col)
  {
    if (y % 2 == 1)
    {
      x = frameWidth - x - 1;
    }

    int index = y * frameWidth + x;
    frameBuffer[index] = col;
  }

  static RgbColor randomColor()
  {
    return RgbColor(random(255), random(255), random(255));
  }
};

// three element pixels, in different order and speeds
// NeoPixelBus<NeoGrbwFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);
// NeoPixelBus<NeoRgbFeature, Neo400KbpsMethod> strip(PixelCount, PixelPin);

// For Esp8266, the Pin is omitted and it uses GPIO3 due to DMA hardware use.
// There are other Esp8266 alternative methods that provide more pin options, but also have
// other side effects.
// For details see wiki linked here https://github.com/Makuna/NeoPixelBus/wiki/ESP8266-NeoMethods.

// You can also use one of these for Esp8266,
// each having their own restrictions.
//
// These two are the same as above as the DMA method is the default.
// NOTE: These will ignore the PIN and use GPI03 pin.
// NeoPixelBus<NeoGrbFeature, NeoEsp8266Dma800KbpsMethod> strip(PixelCount, PixelPin);
// NeoPixelBus<NeoRgbFeature, NeoEsp8266Dma400KbpsMethod> strip(PixelCount, PixelPin);

// Uart method is good for the Esp-01 or other pin restricted modules.
// for details see wiki linked here https://github.com/Makuna/NeoPixelBus/wiki/ESP8266-NeoMethods.
// NOTE: These will ignore the PIN and use GPI02 pin.
// NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart1800KbpsMethod> strip(PixelCount, PixelPin);
// NeoPixelBus<NeoRgbFeature, NeoEsp8266Uart1400KbpsMethod> strip(PixelCount, PixelPin);

// The bitbang method is really only good if you are not using WiFi features of the ESP.
// It works with all but pin 16.
// NeoPixelBus<NeoGrbFeature, NeoEsp8266BitBang800KbpsMethod> strip(PixelCount, PixelPin);
// NeoPixelBus<NeoRgbFeature, NeoEsp8266BitBang400KbpsMethod> strip(PixelCount, PixelPin);

// four element pixels, RGBW
// NeoPixelBus<NeoRgbwFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);