#include "Arduino.h"
#include <NeoPixelBus.h>

struct Coord
{
  int8_t x;
  int8_t y;
  Coord()
  {
    x = 0;
    y = 0;
  }
  Coord(uint8_t _x, uint8_t _y)
  {
    x = _x;
    y = _y;
  };
  void Normalize()
  {
    float len = sqrtf(x * x + y * y);
    x /= len;
    y /= len;
  };
  void Scale(float s)
  {
    x *= s;
    y *= s;
  };
};

class Renderer
{
  static const uint16_t pixelCount = 100;
  static const uint8_t pixelPin = 2;
  uint8_t saveLightValue = 7;
  float savePercent = 0.03;
  bool saveMode = false;
  NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip;
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
  float clearDegradation = 0.7;
  u_int framesSinceStart = 0;

  void init()
  {
    strip.Begin();
    strip.Show();
  }

  void clear()
  {
    for (size_t i = 0; i < pixelCount; i++)
    {
      int r = frameBuffer[i].R * clearDegradation;
      int g = frameBuffer[i].G * clearDegradation;
      int b = frameBuffer[i].B * clearDegradation;
      frameBuffer[i] = RgbColor(r, g, b);
    }
  }

  void clear(RgbColor col)
  {
    for (size_t i = 0; i < pixelCount; i++)
    {
      frameBuffer[i] = col;
    }
  }

  void render()
  {
    for (size_t i = 0; i < pixelCount; i++)
    {
      if (saveMode)
      {
        auto r = frameBuffer[i].R * savePercent;
        auto g = frameBuffer[i].G * savePercent;
        auto b = frameBuffer[i].B * savePercent;
        strip.SetPixelColor(i, RgbColor(r, g, b));
      }
      else
        strip.SetPixelColor(i, frameBuffer[i]);
    }
    strip.Show();
  }

  void setPixel(int x, int y, RgbColor col)
  {
    if (x < 0 || x > frameWidth - 1 || y < 0 || y > frameHeight - 1)
    {
      return;
    }

    if (y % 2 == 1)
    {
      x = frameWidth - x - 1;
    }

    uint8_t index = y * frameWidth + x;
    frameBuffer[index] = col;
  }

  void draw(Coord *coord, uint8_t size, Coord position, RgbColor color)
  {
    for (size_t i = 0; i < size; i++)
    {
      uint8_t x = coord[i].x + position.x;
      uint8_t y = coord[i].y + position.y;
      setPixel(x, y, color);
    }
  }

  void draw(Coord *coord, uint8_t size, Coord position, RgbColor color, float scaleX, float scaleY)
  {
    for (size_t i = 0; i < size; i++)
    {
      uint8_t x = coord[i].x * scaleX + position.x;
      uint8_t y = coord[i].y * scaleY + position.y;
      setPixel(x, y, color);
    }
  }

    void draw(Coord *coord, uint8_t size, Coord position, RgbColor color, float scaleX, float scaleY, float rot)
  {
    for (size_t i = 0; i < size; i++)
    {
      float rot_x = coord[i].x * cos( rot) - coord[i].y * sin(rot);
      float rot_y = coord[i].y * cos( rot) + coord[i].x * sin(rot);
      uint8_t x = rot_x * scaleX + position.x;
      uint8_t y = rot_y * scaleY + position.y;
      setPixel(x, y, color);
    }
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