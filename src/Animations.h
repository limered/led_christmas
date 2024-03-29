#include "Arduino.h"
#include "renderer.h"

// Shared
uint8_t posX = 0;
uint8_t posY = 0;

Coord vLine[8] = {
    Coord(0, 0),
    Coord(0, 1),
    Coord(0, 2),
    Coord(0, 3),
    Coord(0, 4),
    Coord(0, 5),
    Coord(0, 6),
    Coord(0, 7)};

Coord hLine[25] = {
    Coord(0, 0),
    Coord(1, 0),
    Coord(2, 0),
    Coord(3, 0),
    Coord(4, 0),
    Coord(5, 0),
    Coord(6, 0),
    Coord(7, 0),
    Coord(8, 0),
    Coord(9, 0),
    Coord(10, 0),
    Coord(11, 0),
    Coord(12, 0),
    Coord(13, 0),
    Coord(14, 0),
    Coord(15, 0),
    Coord(16, 0),
    Coord(17, 0),
    Coord(18, 0),
    Coord(19, 0),
    Coord(20, 0),
    Coord(21, 0),
    Coord(22, 0),
    Coord(23, 0),
    Coord(24, 0)};

///////////
// Color
//////////
uint8_t maxC = 80;
float maxL = 0.3f;

RgbColor green(0, maxC, 0);
RgbColor red(maxC, 0, 0);
RgbColor blue(0, 0, maxC);
RgbColor magenta(maxC, 0, maxC);
RgbColor yellow(maxC, maxC, 0);
RgbColor cyan(0, maxC, maxC);
RgbColor white(maxC, maxC, maxC);

RgbColor darkGreen(0, maxC / 2, 0);

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

/////////////////////////////////
// PartyLine
////////////////////////////////
uint8_t lineMode = 0;
void nextLineMode()
{
  lineMode = (lineMode + 1) % 4;
}
void PartyLine(Renderer *renderer)
{
  HslColor col = useHsl ? hueShiftColor : HslColor(colors[pColors]);
  if (lineMode == 0)
  {
    renderer->draw(hLine, renderer->frameWidth, Coord(0, posY), col);
    if (posY >= renderer->frameHeight - 1)
    {
      nextLineMode();
      nextColor();
    }else{
      posY++;
    }
  }
  else if (lineMode == 1)
  {
    renderer->draw(vLine, renderer->frameHeight, Coord(posX, 0), col);
    if (posX >= renderer->frameWidth - 1)
    {
      nextLineMode();
      nextColor();
    }else{
      posX++;
    }
  }
  else if (lineMode == 2)
  {
    renderer->draw(hLine, renderer->frameWidth, Coord(0, posY), col);
    if (posY <= 0)
    {
      nextLineMode();
      nextColor();
    }else{
      posY--;
    }
  }
  else if (lineMode == 3)
  {
    renderer->draw(vLine, renderer->frameHeight, Coord(posX, 0), col);
    if (posX <= 0)
    {
      nextLineMode();
      nextColor();
    }else{
      posX--;
    }
  }
};

////////////////////////////////
// Sparkle
///////////////////////////////

void Sparkle(Renderer *renderer)
{
  uint8_t x = random(renderer->frameWidth);
  uint8_t y = random(renderer->frameHeight);
  auto color = useHsl ? hueShiftColor : HslColor(0, 0, maxL);
  renderer->setPixel(x, y, color);
}

//////////////////////////
// Runner
/////////////////////////

uint8_t runnerX1 = 0;
uint8_t runnerX2 = 0;
uint8_t runnerX3 = 0;
uint8_t runnerY = 0;

void Runner(Renderer *renderer)
{
  auto col = useHsl ? hueShiftColor : colors[pColors];
  renderer->setPixel(runnerX1, runnerY, col);
  renderer->setPixel(runnerX2, runnerY, col);
  renderer->setPixel(runnerX3, runnerY, col);

  runnerY++;
  if (runnerY >= renderer->frameHeight)
  {
    runnerY = 0;
    runnerX1++;
    runnerX1 = runnerX1 % renderer->frameWidth;
    runnerX2 = (runnerX1 + 8) % renderer->frameWidth;
    runnerX3 = (runnerX1 + 17) % renderer->frameWidth;
    nextColor();
  }
}

////////////////////////////////////
// Ants
////////////////////////////////////
struct Ant
{
  float x;
  float y;
  float dx;
  float dy;
  float ax;
  float ay;
  float speed;
  Ant(Coord p, Coord d, float s)
  {
    x = p.x;
    y = p.y;
    dx = d.x;
    dy = d.y;
    speed = s;
  };
};

Ant antA(Coord(2, 2), Coord(1, 0), 0.01f);
Ant antB(Coord(7, 2), Coord(0, 1), 0.05f);
Ant antC(Coord(7, 7), Coord(-1, 0), 0.04f);
Ant antD(Coord(2, 7), Coord(0, -1), 0.076f);

float Len(float x, float y)
{
  return sqrtf(x * x + y * y);
};
const float maxAntSpeed = 2.0f;
void UpdateAnt(Ant *ant, Renderer *renderer)
{
  ant->x += ant->dx;
  ant->y += ant->dy;

  ant->dx += ant->ax * ant->speed;
  ant->dy += ant->ay * ant->speed;

  ant->dx = min(ant->dx, maxAntSpeed) * 0.8f;
  ant->dy = min(ant->dy, maxAntSpeed) * 0.8f;

  ant->ax = random(4.0f) - 2.0f;
  ant->ay = random(4.0f) - 2.0f;

  if (ant->x < 0)
  {
    ant->x = renderer->frameWidth - 1;
  }
  if (ant->y < 0)
  {
    ant->y = renderer->frameHeight - 1;
  }
  if (ant->x > renderer->frameWidth)
  {
    ant->x = 0 + 1;
  }
  if (ant->y > renderer->frameHeight)
  {
    ant->y = 0 + 1;
  }
}

void Ants(Renderer *renderer)
{

  UpdateAnt(&antA, renderer);
  UpdateAnt(&antB, renderer);
  UpdateAnt(&antC, renderer);
  UpdateAnt(&antD, renderer);

  renderer->setPixel(antA.x, antA.y, (useHsl) ? RgbColor(hueShiftColor) : red);
  renderer->setPixel(antB.x, antB.y, (useHsl) ? RgbColor(hueShiftColor) : green);
  renderer->setPixel(antC.x, antC.y, (useHsl) ? RgbColor(hueShiftColor) : blue);
  renderer->setPixel(antD.x, antD.y, (useHsl) ? RgbColor(hueShiftColor) : yellow);
  renderer->setPixel(antA.x, antD.y, (useHsl) ? RgbColor(hueShiftColor) : cyan);
  renderer->setPixel(antB.x, antC.y, (useHsl) ? RgbColor(hueShiftColor) : magenta);
}

//////////////////////////
// Rain
//////////////////////////
uint8_t rainXs[] = {25, 25, 25, 25, 25, 25, 25, 25};

void RainOnMe(Renderer *renderer)
{
  uint8_t p = random(8);
  rainXs[p] = rainXs[p] - 1 < 0 ? 25 : rainXs[p] - 1;
  HslColor col(white);
  for (size_t i = 0; i < 8; i++)
  {
    if (rainXs[i] < 25 && rainXs[i] > -1)
    {
      if (useHsl)
      {
        col = HslColor(hueShiftColor);
        col.H += i / 50.0f;
      }
      renderer->setPixel(rainXs[i], i, col);
    }
  }
}


////////////////////////
// Feuerwerk
////////////////////////

Coord firework_circle[] = {
  Coord(-1, 2), 
  Coord(0, 2), 
  Coord(1, 2), 
  Coord(-2, 1), 
  Coord(-2, 0), 
  Coord(-2, -1), 
  Coord(2, 1), 
  Coord(2, 0), 
  Coord(2, -1), 
  Coord(-1, -2), 
  Coord(0, -2), 
  Coord(1, -2)
  };


Coord firework_coord(5,0);
uint8_t mode = 0;
uint8_t trail_duration = 5;
float fire_animation_delta;

void GoToMode0()
{
  mode = 0;
  firework_coord.x = 0;
  firework_coord.y = random(8);
  trail_duration = random(16) + long(4);
  nextColor();
}

float firework_scale_t = 0.0;
float firework_scale_delta = 0.1;
float firework_rotation = 0.0;
float firework_scale_size = 1.1;
float firework_scale_mod_x = 1.0;
float firework_scale_mod_y = 1.0;

void GoToMode1()
{
  mode = 1;
  firework_scale_t = 0;
  firework_scale_delta = random(10) + 20;
  firework_scale_delta = float(1.0) / firework_scale_delta;
  firework_rotation = (random(360) / 180.0) * PI;
  firework_scale_size = (random(6) + 9) * 0.1;
  firework_scale_mod_x = (6 + random(8)) * 0.1;
  firework_scale_mod_y = (6 + random(8)) * 0.1;
}

void Firework(Renderer *renderer)
{
  if(mode == 0){
    int newX = (firework_coord.x + 1) > 24 ? 0 : firework_coord.x + 1;
    firework_coord.x = newX;

    renderer->setPixel(firework_coord.x, firework_coord.y, white);
    if(newX >= trail_duration){
      GoToMode1();
    }
  }else if (mode == 1)
  {
    firework_scale_t += firework_scale_delta;
    float t = firework_scale_size - powf(1.0 - firework_scale_t, 5);

    RgbColor col = (useHsl) ? RgbColor(hueShiftColor) : RgbColor(colors[pColors]);
    col = col.Dim(255 * (firework_scale_size - t));

    renderer->draw(firework_circle, 12, firework_coord, col, t * firework_scale_mod_x, t * firework_scale_mod_y, firework_rotation);

    if(firework_scale_t > 1.0){
      GoToMode0();
    }
  }
}

////////////////////////////////
// Color Wheel
////////////////////////////////

Coord wheelLine[] = {
  Coord(0, 0), Coord(1, 0), Coord(2, 0), Coord(3, 0), Coord(4, 0), Coord(5, 0), 
  Coord(6, 0), Coord(7, 0), Coord(8, 0), Coord(9, 0), Coord(10, 0), Coord(11, 0)
  };

float numRays = 5.0;
float rotationSpeed = 0.1;
float angleStep = 2 * PI / numRays;
Coord center = Coord(12, 3);

void ColorWheel(Renderer *renderer)
{
  float animationStart = fmodf(renderer->framesSinceStart * rotationSpeed, 2 * PI);

  for (int i = 0; i < numRays; i++)
  {
    float angle = i * angleStep;
    float animationAngle = fmodf(animationStart + angle, 2 * PI);

    HslColor color = HslColor(colors[i]);
    if(useHsl){
      color.H += hueShiftColor.H;
    }

    renderer->draw(wheelLine, 13, center, color, 1, 1, animationAngle);
  }
}

////////////////////////////////
// Stacker
////////////////////////////////

Coord horizontalLine[] = {
  Coord(0, 0), Coord(0, 1), Coord(0, 2), Coord(0, 3), Coord(0, 4), Coord(0, 5), Coord(0, 6), Coord(0, 7),  
};

HslColor stackColors[25];

size_t stackHeight = 0;
size_t stackAnimationPos = 24;
size_t stackColorPointer = 0;

void Stacker(Renderer *renderer)
{
  for (size_t i = 0; i < stackHeight; i++)
  {
    if(useHsl){
      renderer->draw(horizontalLine, 8, Coord(i, 0), stackColors[i]);
    }else{
      renderer->draw(horizontalLine, 8, Coord(i, 0), colors[stackColorPointer]);
    }
  }
  
  if(useHsl){
    renderer->draw(horizontalLine, 8, Coord(stackAnimationPos--, 0), stackColors[stackHeight]);
  }else{
    renderer->draw(horizontalLine, 8, Coord(stackAnimationPos--, 0), colors[stackColorPointer]);
  }

  if(stackAnimationPos <= stackHeight){
    stackAnimationPos = 24;
    stackHeight++;
    if(stackHeight > 24){
      stackHeight = 0;
      stackColorPointer = (stackColorPointer + 1) % 6;
    }else{
      stackColors[stackHeight] = hueShiftColor;
    }
  }
}

////////////////////////////////
// Linear Waves
////////////////////////////////

float waveCoord = 0;
size_t waveColorCounter = 0;
HslColor currentWaveColor = blue;

void LinearWaves(Renderer *renderer){
  for (size_t i = 0; i < 25; i++)
  {
    auto color = useHsl ? hueShiftColor : currentWaveColor;
    int absolute = int(waveCoord - i);
    if(absolute <= 4 && absolute >= 0){
      continue;
    }
    
    renderer->draw(horizontalLine, 8, Coord(i, 0), color);
  }

  waveCoord += 0.5;
  if(waveCoord > 29){
    waveCoord = 0;

    if(waveColorCounter++ > 2){
      waveColorCounter = 0;
      currentWaveColor = hueShiftColor;
    }
  }
}

////////////////////////////////
// Fire
////////////////////////////////

size_t firePositions[] = {0, 0, 0, 0, 0, 0, 0, 0};
size_t sparkPositions[] = {0, 0, 0, 0, 0, 0, 0, 0};

void Fire(Renderer *renderer){
  float baseHue = useHsl ? hueShiftColor.H : 0.0;
  float hueDelta = useHsl ? 90.0 : 15.0;
  // randomize fire positions
  for (size_t i = 0; i < 8; i++)
  {
    firePositions[i] = random(7) + 3;

    for (size_t j = 0; j <= firePositions[i]; j++){
      HslColor color = HslColor(red);
      color.H = baseHue + ((hueDelta * (j / 10.0)) / 360.0);

      renderer->setPixel(j, i, color);
    }
  }

  // add sparks
  if(random(20) == 1){
    size_t max = 0;
    size_t coord = 0;
    for (size_t i = 0; i < 8; i++){
      if(firePositions[i] > max){
        max = firePositions[i];
        coord = i;
      }
    }
    sparkPositions[coord] = max+1;
  }

  // render sparks
  for (size_t i = 0; i < 8; i++)
  {
    if(sparkPositions[i] <= 0){
      continue;
    }

    auto color = HslColor(red);
    color.H = baseHue + (((hueDelta - 5) * (1.0 - ((sparkPositions[i] - 10) / 14.0))) / 360.0);
    renderer->setPixel(sparkPositions[i], i, color);

    if(random(5) == 1){
      sparkPositions[i]++;
      if(random(15) == 1 || sparkPositions[i] > 24){
        sparkPositions[i] = 0;
      }
    }
  }
}

////////////////////////////////
// Line Race
////////////////////////////////

size_t lineRaceLines[25];

void LineRace(Renderer *renderer){
  for(size_t i = 0; i < 25; i++){
    HslColor col = useHsl ? hueShiftColor : HslColor(colors[i % 6]);
    renderer->draw(horizontalLine, 4, Coord(i, lineRaceLines[i]), col);

    if(random(4) < 1)
      lineRaceLines[i] = (lineRaceLines[i] + 1) % 8;
  }
}














////////////////////////////////
// Tree
////////////////////////////////
Coord tree[52] = {
    Coord(4, 0),
    Coord(5, 0),

    Coord(0, 1),
    Coord(1, 1),
    Coord(2, 1),
    Coord(3, 1),
    Coord(4, 1),
    Coord(5, 1),
    Coord(6, 1),
    Coord(7, 1),
    Coord(8, 1),
    Coord(9, 1),

    Coord(1, 2),
    Coord(2, 2),
    Coord(3, 2),
    Coord(4, 2),
    Coord(5, 2),
    Coord(6, 2),
    Coord(7, 2),
    Coord(8, 2),

    Coord(3, 3),
    Coord(4, 3),
    Coord(5, 3),
    Coord(6, 3),

    Coord(1, 4),
    Coord(2, 4),
    Coord(3, 4),
    Coord(4, 4),
    Coord(5, 4),
    Coord(6, 4),
    Coord(7, 4),
    Coord(8, 4),

    Coord(2, 5),
    Coord(3, 5),
    Coord(4, 5),
    Coord(5, 5),
    Coord(6, 5),
    Coord(7, 5),

    Coord(4, 6),
    Coord(5, 6),

    Coord(2, 7),
    Coord(3, 7),
    Coord(4, 7),
    Coord(5, 7),
    Coord(6, 7),
    Coord(7, 7),

    Coord(3, 8),
    Coord(4, 8),
    Coord(5, 8),
    Coord(6, 8),

    Coord(4, 9),
    Coord(5, 9),
};

Coord lights[8] = {
    Coord(0, 1),
    Coord(2, 2),
    Coord(4, 3),
    Coord(6, 4),
    Coord(7, 5),
    Coord(2, 5),
    Coord(4, 6),
    Coord(6, 7),

};
Coord lights2[8] = {
    Coord(8, 1),
    Coord(6, 2),
    Coord(5, 3),
    Coord(4, 4),
    Coord(3, 5),
    Coord(6, 5),
    Coord(5, 6),
    Coord(4, 8),
};

float lightsColors = 0;

void Tannenbaum(Renderer *renderer)
{
  renderer->draw(tree, 52, Coord(0, 0), darkGreen);
}

void TannenbaumLights(Renderer *renderer)
{
  HslColor lineCol = useHsl ? hueShiftColor : HslColor(red);
  HslColor line2Col = useHsl ? hueShiftColor : HslColor(red);

  line2Col.H += 0.5;
  renderer->draw(lights, 8, Coord(0, 0), lineCol);
  renderer->draw(lights2, 8, Coord(0, 0), line2Col);
}

///////////////////////////
// Heart
///////////////////////////
Coord heart[] = {Coord(2, 0),
                 Coord(1, 1), Coord(2, 1), Coord(3, 1),
                 Coord(0, 2), Coord(1, 2), Coord(2, 2), Coord(3, 2), Coord(4, 2),
                 Coord(0, 3), Coord(1, 3), Coord(2, 3), Coord(3, 3), Coord(4, 3),
                 Coord(1, 4), Coord(3, 4)};

///////////////////////////
// HslBlock
//////////////////////////

float blockX = 1.0f;
float blockY = 3.0f;
float dirX = 0.3f;
float dirY = 0.12f;
uint8_t blockSize = 2;

void HslBlock(Renderer *renderer)
{
  if (useHsl)
  {
    blockSize = 2;
    for (size_t x = 0; x < blockSize; x++)
    {
      for (size_t y = 0; y < blockSize; y++)
      {
        renderer->setPixel(x + blockX, y + blockY, hueShiftColor);
      }
    }
  }
  else
  {
    blockSize = 5;
    renderer->draw(heart, 16, Coord(blockX, blockY), red);
  }
  // animate
  if (blockX + blockSize > renderer->frameWidth)
  {
    dirX *= -1;
    blockX = renderer->frameWidth - blockSize - 1;
  }
  if (blockY + blockSize > renderer->frameHeight)
  {
    dirY *= -1;
    blockY = renderer->frameHeight - blockSize - 1;
  }
  if (blockX <= 0)
  {
    dirX *= -1;
    blockX = 0;
  }
  if (blockY <= 0)
  {
    dirY *= -1;
    blockY = 0;
  }
  blockX += dirX;
  blockY += dirY;
}



///////////////////////////////
// BM Logo
///////////////////////////////

HslColor bmBlue(0.77f, 1.0f, 0.44f);
RgbColor lightBlue(0, 159, 223);

Coord bmLogo[] = {Coord(1, 1), Coord(2, 1), Coord(3, 1), Coord(4, 1), Coord(5, 1),
                  Coord(1, 2), Coord(2, 2), Coord(3, 2), Coord(4, 2), Coord(5, 2),
                  Coord(3, 4), Coord(4, 4), Coord(5, 4), Coord(6, 4), Coord(7, 4),
                  Coord(3, 5), Coord(4, 5), Coord(5, 5), Coord(6, 5), Coord(7, 5),
                  Coord(1, 7), Coord(2, 7), Coord(3, 7), Coord(4, 7), Coord(5, 7),
                  Coord(1, 8), Coord(2, 8), Coord(3, 8), Coord(4, 8), Coord(5, 8)};

void BmLogo(Renderer *renderer)
{
  float s = (sinf(renderer->framesSinceStart / 10.0f) + 1.0f) * 0.5f;
  HslColor bmBlue(lightBlue);
  bmBlue.L *= s * 0.44;
  renderer->draw(bmLogo, 30, Coord(0, 0), bmBlue);
}

//////////////////////////////
// Star
//////////////////////////////

Coord bigStar[39] = {Coord(-4, 5),
                     Coord(-3, 0), Coord(-3, 1), Coord(-3, 4), Coord(-3, 5),
                     Coord(-2, 1), Coord(-2, 2), Coord(-2, 3), Coord(-2, 4), Coord(-2, 5),
                     Coord(-1, 2), Coord(-1, 3), Coord(-1, 4), Coord(-1, 5), Coord(-1, 6), Coord(-1, 7),
                     Coord(0, 2), Coord(0, 3), Coord(0, 4), Coord(0, 5), Coord(0, 6), Coord(0, 7), Coord(0, 8),
                     Coord(1, 2), Coord(1, 3), Coord(1, 4), Coord(1, 5), Coord(1, 6), Coord(1, 7),
                     Coord(2, 1), Coord(2, 2), Coord(2, 3), Coord(2, 4), Coord(2, 5),
                     Coord(3, 0), Coord(3, 1), Coord(3, 4), Coord(3, 5),
                     Coord(4, 5)};

void Star(Renderer *renderer)
{
  float s = useHsl ? 1 : sinf(renderer->framesSinceStart / 10.0f);
  for (size_t i = 0; i < 39; i++)
  {
    auto x = bigStar[i].x * s;
    auto y = bigStar[i].y;
    renderer->setPixel(x + 4.5f, y, yellow);
  }
}

//////////////////////////////
// Big Heart
//////////////////////////////

Coord bigHeart[22] = {Coord(-4, 1), Coord(-4, 2), Coord(-4, 3),
                      Coord(-3, -1), Coord(-3, 0), Coord(-3, 4),
                      Coord(-2, -2), Coord(-2, 4),
                      Coord(-1, -2), Coord(-1, 3),
                      Coord(0, -3), Coord(0, 2),
                      Coord(1, -2), Coord(1, 3),
                      Coord(2, -2), Coord(2, 4),
                      Coord(3, -1), Coord(3, 0), Coord(3, 4),
                      Coord(4, 1), Coord(4, 2), Coord(4, 3)};
void BigHeart(Renderer *renderer)
{
  float s = sinf(renderer->framesSinceStart / 13.0f);
  float scale = abs(s);
  for (size_t i = 0; i < 22; i++)
  {
    auto x = bigHeart[i].x * scale;
    auto y = bigHeart[i].y * scale;
    if (useHsl)
    {
      auto rotX = x * cosf(s) - y * sinf(s);
      auto rotY = x * sinf(s) + y * cosf(s);
      renderer->setPixel(rotX + 4.5f, rotY + 4.5, red);
    }
    else
    {
      renderer->setPixel(x + 4.5f, y + 4.5, red);
    }
  }
}

////////////////////////////
// Circle
////////////////////////////

Coord candy[] = {Coord(0, 0), Coord(0, 1), Coord(-1, 1), Coord(-1, 2), Coord(0, 3), Coord(0, 4),
                 Coord(1, 4)};

const float TAU = 2 * PI;
const float thirdTau = TAU * 0.33f;
const float sixthTau = thirdTau * 0.5f;
float sinThirdTau = sinf(thirdTau);
float cosThirdTau = cosf(thirdTau);

void Circle(Renderer *renderer)
{
  Coord c(4.5, 5.5);
  float theta = ((renderer->framesSinceStart % 120) / 120.0f) * 6.29f;

  HslColor colA = useHsl ? hueShiftColor : HslColor(white);
  HslColor colB = useHsl ? hueShiftColor : HslColor(red);
  if (useHsl)
  {
    colB.H += 0.5f;
  }

  for (size_t i = 0; i < 7; i++)
  {
    auto rotX = candy[i].x * cosf(theta + sixthTau) - candy[i].y * sinf(theta + sixthTau);
    auto rotY = candy[i].x * sinf(theta + sixthTau) + candy[i].y * cosf(theta + sixthTau);
    renderer->setPixel(rotX + c.x, rotY + c.y, colA);

    auto rotX2 = rotX * cosThirdTau - rotY * sinThirdTau;
    auto rotY2 = rotX * sinThirdTau + rotY * cosThirdTau;
    renderer->setPixel(rotX2 + c.x, rotY2 + c.y, colA);

    rotX = rotX2 * cosThirdTau - rotY2 * sinThirdTau;
    rotY = rotX2 * sinThirdTau + rotY2 * cosThirdTau;
    renderer->setPixel(rotX + c.x, rotY + c.y, colA);
  }
  for (size_t i = 0; i < 7; i++)
  {
    auto rotX = candy[i].x * cosf(theta) - candy[i].y * sinf(theta);
    auto rotY = candy[i].x * sinf(theta) + candy[i].y * cosf(theta);
    renderer->setPixel(rotX + c.x, rotY + c.y, colB);

    auto rotX2 = rotX * cosThirdTau - rotY * sinThirdTau;
    auto rotY2 = rotX * sinThirdTau + rotY * cosThirdTau;
    renderer->setPixel(rotX2 + c.x, rotY2 + c.y, colB);

    rotX = rotX2 * cosThirdTau - rotY2 * sinThirdTau;
    rotY = rotX2 * sinThirdTau + rotY2 * cosThirdTau;
    renderer->setPixel(rotX + c.x, rotY + c.y, colB);
  }
}



///////////////////////
// Tunnel
///////////////////////

Coord tunnel[] = {Coord(-5, 4), Coord(-4, 4), Coord(-3, 4), Coord(-2, 4), Coord(-1, 4), Coord(0, 4),
                  Coord(5, 4), Coord(4, 4), Coord(3, 4), Coord(2, 4), Coord(1, 4),
                  Coord(-5, -4), Coord(-4, -4), Coord(-3, -4), Coord(-2, -4), Coord(-1, -4), Coord(0, -4),
                  Coord(5, -4), Coord(4, -4), Coord(3, -4), Coord(2, -4), Coord(1, -4)};

void Tunnel(Renderer *renderer)
{
  float cx = 5.0f;
  float cy = 5.0f;
  float theta = ((renderer->framesSinceStart % 30) / 30.0f);
  float s = theta * theta;
  for (size_t i = 0; i < 20; i++)
  {
    auto x = tunnel[i].x * s;
    auto y = tunnel[i].y * s;
    if (useHsl)
    {
      float rotX = x * cosf(theta * TAU) - y * sinf(theta * TAU);
      float rotY = x * sinf(theta * TAU) + y * cosf(theta * TAU);
      renderer->setPixel(rotX + cx, rotY + cy, hueShiftColor);
    }
    else
    {
      renderer->setPixel(x + cx, y + cy, colors[pColors]);
    }
  }

  theta = (((renderer->framesSinceStart + 15) % 30) / 30.0f);
  s = theta * theta;
  for (size_t i = 0; i < 20; i++)
  {
    auto x = tunnel[i].y * s;
    auto y = -tunnel[i].x * s;
    if (useHsl)
    {
      float rotX = x * cosf(theta * TAU) - y * sinf(theta * TAU);
      float rotY = x * sinf(theta * TAU) + y * cosf(theta * TAU);
      renderer->setPixel(rotX + cx, rotY + cy, hueShiftColor);
    }
    else
    {
      renderer->setPixel(x + cx, y + cy, colors[pColors]);
    }
  }
  if (renderer->framesSinceStart % 30 == 0)
  {
    nextColor();
  }
}




