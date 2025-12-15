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

/**
 * 
 * Singleline animations
 * 
 */

// Runner
uint8_t runner_position = 0;

void runner_with_offset(Renderer *renderer, uint8_t offset, uint8_t length, RgbColor color = cyan){

  renderer->setPixel(runner_position + offset, 0, current_color());

  runner_position++;
  if(runner_position >= offset + length){
    runner_position = offset;
    nextColor();
  }
}

void runner(Renderer *renderer)
{
 runner_with_offset(renderer, 0, 98);
}

uint8_t runner_direction = 1;
void runner_front_to_back(Renderer *renderer){

  renderer->setPixel(runner_position, 0, current_color());

  runner_position += runner_direction;
  if(runner_position >= renderer->frameWidth || runner_position <= 0){
    runner_direction *= -1;
    nextColor();
  }
}

// Sparkler
void sparkler(Renderer *renderer)
{
  if(useHsl)
    renderer->setPixel(random(98), 0, hueShiftColor);
  else
    renderer->setPixel(random(98), 0, white);
}


// Breather
float breather_strength = 0.0;
bool breather_color_switched = false;
void breather(Renderer *renderer)
{
  float sinVal = sin(renderer->timeSinceStart);
  breather_strength = sinVal * 0.5 + 0.5;

  HslColor color = current_color();
  color.L = breather_strength;
  renderer->clear(color);

  if(breather_strength < 0.005 && !breather_color_switched){
    nextColor();
    breather_color_switched = true;
  }
  if(breather_strength > 0.45){
    breather_color_switched = false;
  }
}


// Loading
uint8_t loading_percents[6] = {0, 0, 0, 0, 0, 0};
float loading_speed = 2.0;
void loading(Renderer *renderer)
{
  // load legs
  loading_percents[3] = (loading_percents[3] + loading_speed >= 100) ? 100 : loading_percents[3] + loading_speed;
  loading_percents[4] = (loading_percents[4] + loading_speed >= 100) ? 100 : loading_percents[4] + loading_speed;

  uint8_t leg_length = l_leg_length * (loading_percents[3] / 100.0);
  for(uint8_t i = 0; i < leg_length; i++){
    renderer->setPixel(l_leg_offset + i, 0, current_color());
    renderer->setPixel(r_arm_offset - i - 1, 0, current_color());
  }
  // load buttons
  if(loading_percents[3] >= 100){
    loading_percents[1] = (loading_percents[1] + loading_speed >= 100) ? 100 : loading_percents[1] + loading_speed;
    uint8_t b_length = buttons_length * (loading_percents[1] / 100.0);
    for(uint8_t i = 0; i < b_length; i++){
      renderer->setPixel(buttons_offset + i, 0, current_color());
    }
  }
  // load waist
  if(loading_percents[1] >= 100){
    loading_percents[0] = (loading_percents[0] + loading_speed >= 100) ? 100 : loading_percents[0] + loading_speed;
    uint8_t w_length = waist_length * (loading_percents[0] / 100.0);
    for(uint8_t i = 0; i < w_length; i++){
      renderer->setPixel(waist_offset + i, 0, current_color());
    }
  }
  // load arms
  if(loading_percents[0] >= 100){
    loading_percents[2] = (loading_percents[2] + loading_speed >= 100) ? 100 : loading_percents[2] + loading_speed;
    loading_percents[3] = (loading_percents[2] + loading_speed >= 100) ? 100 : loading_percents[3] + loading_speed;
    uint8_t arm_length = l_arm_length * (loading_percents[2] / 100.0);
    for(uint8_t i = 0; i < arm_length; i++){
      renderer->setPixel(l_arm_offset + i, 0, current_color());
      renderer->setPixel(r_arm_offset + i, 0, current_color());
    }
  }
  // blink
  if(loading_percents[2] >= 100){
    if(random(5) == 1){
      renderer->clear(black);
    }
    if(random(30) == 1){
      loading_percents[0] = 0;
      loading_percents[1] = 0;
      loading_percents[2] = 0;
      loading_percents[3] = 0;
      loading_percents[4] = 0;
      nextColor();
    }
  }
}

// moving dot
uint8_t dot_position = 0;
void moving_dot(Renderer *renderer)
{
  uint8_t move_command = random(3);
  uint8_t direction = move_command == 0 ? -1 : move_command == 2 ? 1 : 0;

  uint8_t turbo = random(5);
  if(random(40) == 1){
    nextColor();
  }

  dot_position = dot_position + direction * (turbo == 1 ? 3 : 1);
  if(dot_position > 97){
    dot_position = 0;
  }
  if(dot_position < 0){
    dot_position = 97;
  }
  renderer->setPixel(dot_position, 0, current_color());
}


// conway
uint8_t conway_positions[98] = {0};
uint8_t conway_buffer[98] = {0};
uint8_t conway_iterations = 0;

void conway_init(Renderer *renderer){
  for(uint8_t i = 0; i < 98; i++){
    conway_positions[i] = random(2);
  }
}

uint8_t get_cell(uint8_t index){
  auto real_index = index < 0 ? 98 + index : index;
  real_index = index > 97 ? index % 98 : index;
  return conway_positions[real_index];
}

uint8_t calculate_alive(uint8_t index){
  auto c = get_cell(index - 1) + get_cell(index + 1) + get_cell(index - 2) + get_cell(index + 2);
  if(get_cell(index) == 1){
    return c == 4 || c == 2 ? 1 : 0;
  }else{
    return c == 2 || c == 3 ? 1 : 0;
  }
}

void conway(Renderer *renderer){
  if(renderer->framesSinceStart % 5 != 0){
    for(uint8_t i = 0; i < 98; i++){
      if(conway_positions[i] == 1){
        renderer->setPixel(i, 0, current_color());
      }
    }
    return;
  }
  conway_iterations++;
  bool still_alive = false;
  for(uint8_t i = 0; i < 98; i++){
    conway_buffer[i] = calculate_alive(i);
    still_alive = still_alive || conway_buffer[i] == 1;
  }
  bool changes = false;
  for(uint8_t i = 0; i < 98; i++){
    changes = changes || conway_positions[i] != conway_buffer[i];
    conway_positions[i] = conway_buffer[i];
    if(conway_positions[i] == 1){
      renderer->setPixel(i, 0, current_color());
    }
    conway_buffer[i] = 0;
  }
  if(!still_alive || !changes || conway_iterations > 60){
    conway_iterations = 0;
    conway_init(renderer);
    nextColor();
  }
}

// runner multi
uint8_t runner_positions[6] = 
{
  waist_offset, 
  buttons_offset,
  l_arm_offset,
  l_leg_offset,
  r_leg_offset,
  r_arm_offset
};

void runner_multi(Renderer *renderer)
{
  for (size_t i = 0; i < 6; i++)
  {
    auto color_id = (pColors + i) % 6;
    renderer->setPixel(runner_positions[i], 0, colors[color_id]);
  }

  runner_positions[0] = (runner_positions[0] + 1 >= waist_offset + waist_length) 
    ? waist_offset : runner_positions[0] + 1;
  runner_positions[1] = (runner_positions[1] + 1 >= buttons_offset + buttons_length) 
  ? buttons_offset : runner_positions[1] + 1;
  runner_positions[2] = (runner_positions[2] + 1 >= l_arm_offset + l_arm_length) 
  ? l_arm_offset : runner_positions[2] + 1;
  runner_positions[3] = (runner_positions[3] + 1 >= l_leg_offset + l_leg_length) 
  ? l_leg_offset : runner_positions[3] + 1;
  runner_positions[4] = (runner_positions[4] + 1 >= r_leg_offset + r_leg_length) 
  ? r_leg_offset : runner_positions[4] + 1;
  runner_positions[5] = (runner_positions[5] + 1 >= r_arm_offset + r_arm_length) 
  ? r_arm_offset : runner_positions[5] + 1;

  if(random(30) == 1){
    nextColor();
  }
}

// rudolph
void rudolph(Renderer *renderer)
{
  renderer->setPixel(36, 0, red);
  renderer->setPixel(37, 0, red);
}

// icing
void icing(Renderer *renderer)
{
  renderer->clear(white);

  for(uint8_t i = buttons_offset; i < buttons_offset + buttons_length; i++){
    renderer->setPixel(i, 0, hueShiftColor);
  }
}

// waves
float wave_coord = 0;
void waves(Renderer *renderer)
{
  wave_coord += 0.1;
  for(uint8_t i = 0; i < 98; i++){
    float y = sin(i * 0.1 + wave_coord) * 0.5 + 0.5;
    renderer->setPixel(i, 0, HslColor(y, 1.0, 0.5));
  }
}

// strobo
void strobo(Renderer *renderer)
{
  if(renderer->framesSinceStart % 5 == 0){
    renderer->clear(current_color());
  }else{
    renderer->clear(black);
  }

  if(random(60) == 1){
    nextColor();
  }
}