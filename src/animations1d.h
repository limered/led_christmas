#include "Arduino.h"
#include "renderer.h"
#include "my_colors.h"

#pragma once

uint8 waist_offset = 0;
uint8 waist_length = 36;

uint8 buttons_offset = 36;
uint8 buttons_length = 8;

uint8 l_arm_offset = 44;
uint8 l_arm_length = 11;

uint8 l_leg_offset = 55;
uint8 l_leg_length = 16;

uint8 r_leg_offset = 71;
uint8 r_leg_length = 16;

uint8 r_arm_offset = 87;
uint8 r_arm_length = 11;

void one_color(Renderer *renderer)
{
  for (size_t i = 0; i < waist_length; i++)
  {
    renderer->setPixel(waist_offset + i, 0, green);
  }

    for (size_t i = 0; i < buttons_length; i++)
  {
    renderer->setPixel(buttons_offset + i, 0, red);
  }

    for (size_t i = 0; i < l_arm_length; i++)
  {
    renderer->setPixel(l_arm_offset + i, 0, blue);
  }

    for (size_t i = 0; i < l_leg_length; i++)
  {
    renderer->setPixel(l_leg_offset + i, 0, magenta);
  }

    for (size_t i = 0; i < r_leg_length; i++)
  {
    renderer->setPixel(r_leg_offset + i, 0, yellow);
  }

  for (size_t i = 0; i < r_arm_length; i++)
  {
    renderer->setPixel(r_arm_offset + i, 0, cyan);
  }
}

void random_color(Renderer *renderer)
{
  for (size_t i = 0; i < renderer->frameWidth; i++)
  {
    renderer->setPixel(i, 0, white);
  }
}