#include "Arduino.h"
#include "renderer.h"

// Shared
uint8_t posX = 0;
uint8_t posY = 0;

Coord vLine[10] = {
    Coord(0, 0),
    Coord(0, 1),
    Coord(0, 2),
    Coord(0, 3),
    Coord(0, 4),
    Coord(0, 5),
    Coord(0, 6),
    Coord(0, 7),
    Coord(0, 8),
    Coord(0, 9)};

Coord hLine[10] = {
    Coord(0, 0),
    Coord(1, 0),
    Coord(2, 0),
    Coord(3, 0),
    Coord(4, 0),
    Coord(5, 0),
    Coord(6, 0),
    Coord(7, 0),
    Coord(8, 0),
    Coord(9, 0)};

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

HslColor hueShiftColor(0, 1.0, 0.3);
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
    renderer->draw(hLine, 10, Coord(0, posY), col);
    posY++;
    if (posY >= renderer->frameHeight - 1)
    {
      nextLineMode();
      nextColor();
    }
  }
  else if (lineMode == 1)
  {
    renderer->draw(vLine, 10, Coord(posX, 0), col);
    posX++;
    if (posX >= renderer->frameWidth - 1)
    {
      nextLineMode();
      nextColor();
    }
  }
  else if (lineMode == 2)
  {
    renderer->draw(hLine, 10, Coord(0, posY), col);
    posY--;
    if (posY <= 0)
    {
      nextLineMode();
      nextColor();
    }
  }
  else if (lineMode == 3)
  {
    renderer->draw(vLine, 10, Coord(posX, 0), col);
    posX--;
    if (posX <= 0)
    {
      nextLineMode();
      nextColor();
    }
  }
};

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
  if (blockX + blockSize >= renderer->frameWidth)
  {
    dirX *= -1;
  }
  if (blockY + blockSize >= renderer->frameHeight)
  {
    dirY *= -1;
  }
  if (blockX <= 0)
  {
    dirX *= -1;
  }
  if (blockY <= 0)
  {
    dirY *= -1;
  }
  blockX += dirX;
  blockY += dirY;
}

////////////////////////////////
// Sparcle
///////////////////////////////

void Sparkle(Renderer *renderer)
{
  uint8_t x = random(renderer->frameWidth);
  uint8_t y = random(renderer->frameHeight);
  auto color = useHsl ? hueShiftColor : HslColor(0, 0, maxL);
  renderer->setPixel(x, y, color);
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

float halfPi = PI * 0.5f;
float quaterPi = PI * 0.25f;
float sinHalfPi = sinf(halfPi);
float cosHalfPi = cosf(halfPi);

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
    auto rotX = candy[i].x * cosf(theta + quaterPi) - candy[i].y * sinf(theta + quaterPi);
    auto rotY = candy[i].x * sinf(theta + quaterPi) + candy[i].y * cosf(theta + quaterPi);
    renderer->setPixel(rotX + c.x, rotY + c.y, colA);

    auto rotX2 = rotX * cosHalfPi - rotY * sinHalfPi;
    auto rotY2 = rotX * sinHalfPi + rotY * cosHalfPi;
    renderer->setPixel(rotX2 + c.x, rotY2 + c.y, colA);

    rotX = rotX2 * cosHalfPi - rotY2 * sinHalfPi;
    rotY = rotX2 * sinHalfPi + rotY2 * cosHalfPi;
    renderer->setPixel(rotX + c.x, rotY + c.y, colA);

    rotX2 = rotX * cosHalfPi - rotY * sinHalfPi;
    rotY2 = rotX * sinHalfPi + rotY * cosHalfPi;
    renderer->setPixel(rotX2 + c.x, rotY2 + c.y, colA);
  }
  for (size_t i = 0; i < 7; i++)
  {
    auto rotX = candy[i].x * cosf(theta) - candy[i].y * sinf(theta);
    auto rotY = candy[i].x * sinf(theta) + candy[i].y * cosf(theta);
    renderer->setPixel(rotX + c.x, rotY + c.y, colB);

    auto rotX2 = rotX * cosHalfPi - rotY * sinHalfPi;
    auto rotY2 = rotX * sinHalfPi + rotY * cosHalfPi;
    renderer->setPixel(rotX2 + c.x, rotY2 + c.y, colB);

    rotX = rotX2 * cosHalfPi - rotY2 * sinHalfPi;
    rotY = rotX2 * sinHalfPi + rotY2 * cosHalfPi;
    renderer->setPixel(rotX + c.x, rotY + c.y, colB);

    rotX2 = rotX * cosHalfPi - rotY * sinHalfPi;
    rotY2 = rotX * sinHalfPi + rotY * cosHalfPi;
    renderer->setPixel(rotX2 + c.x, rotY2 + c.y, colB);
  }
}

//////////////////////////
// Runner
/////////////////////////

uint8_t runnerX = 0;
uint8_t runnerY = 0;

void Runner(Renderer *renderer)
{
  auto col = useHsl ? hueShiftColor : colors[pColors];
  renderer->setPixel(runnerX, runnerY, col);

  runnerX++;
  if (runnerX >= renderer->frameWidth)
  {
    runnerX = 0;
    runnerY++;
    runnerY = runnerY % renderer->frameHeight;
    nextColor();
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
      float rotX = x * cosf(theta * 6.29f) - y * sinf(theta * 6.29f);
      float rotY = x * sinf(theta * 6.29f) + y * cosf(theta * 6.29f);
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
      float rotX = x * cosf(theta * 6.29f) - y * sinf(theta * 6.29f);
      float rotY = x * sinf(theta * 6.29f) + y * cosf(theta * 6.29f);
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