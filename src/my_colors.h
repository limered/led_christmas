#pragma once

#include "Arduino.h"
#include "renderer.h"

uint8_t maxC = 255;

RgbColor black(0);
RgbColor green(0, maxC, 0);
RgbColor red(maxC, 0, 0);
RgbColor blue(0, 0, maxC);
RgbColor magenta(maxC, 0, maxC);
RgbColor yellow(maxC, maxC, 0);
RgbColor cyan(0, maxC, maxC);
RgbColor white(maxC * 0.5, maxC * 0.5, maxC * 0.5);


uint8_t pColors = 0;
HslColor colors[] = {
    red,
    green,
    blue,
    yellow,
    magenta,
    cyan,
};
void nextColor()
{
  pColors = (pColors + 1) % 6;
}

HslColor hueShiftColor(0, 1.0, 0.5);
float hueShiftSpeed = 0.1;
bool useHsl = false;
void ShiftHue()
{
  hueShiftColor.H += hueShiftSpeed;
  if (hueShiftColor.H >= 1.0)
  {
    hueShiftColor.H = 0;
  }
}

HslColor current_color(){
  return useHsl ? hueShiftColor : HslColor(colors[pColors]);
}