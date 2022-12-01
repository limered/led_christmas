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

RgbColor darkGreen(0, maxC / 2, 0);

uint8_t pColors = 0;
RgbColor colors[] = {
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