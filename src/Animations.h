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
  if (lineMode == 0)
  {
    renderer->draw(hLine, 10, Coord(0, posY), colors[pColors]);
    posY++;
    if (posY >= renderer->frameHeight - 1)
    {
      nextLineMode();
      nextColor();
    }
  }
  else if (lineMode == 1)
  {
    renderer->draw(vLine, 10, Coord(posX, 0), colors[pColors]);
    posX++;
    if (posX >= renderer->frameWidth - 1)
    {
      nextLineMode();
      nextColor();
    }
  }
  else if (lineMode == 2)
  {
    renderer->draw(hLine, 10, Coord(0, posY), colors[pColors]);
    posY--;
    if (posY <= 0)
    {
      nextLineMode();
      nextColor();
    }
  }
  else if (lineMode == 3)
  {
    renderer->draw(vLine, 10, Coord(posX, 0), colors[pColors]);
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
  lightsColors = sinf(renderer->framesSinceStart / 15.0);
  if (lightsColors < -0.5)
  {
    renderer->draw(lights, 8, Coord(0, 0), yellow);
    renderer->draw(lights2, 8, Coord(0, 0), blue);
  }
  else if (lightsColors < 0)
  {
    renderer->draw(lights, 8, Coord(0, 0), red);
    renderer->draw(lights2, 8, Coord(0, 0), cyan);
  }
  else if (lightsColors < 0.5)
  {
    renderer->draw(lights, 8, Coord(0, 0), red);
    renderer->draw(lights2, 8, Coord(0, 0), blue);
  }
  else
  {
    renderer->draw(lights, 8, Coord(0, 0), yellow);
    renderer->draw(lights2, 8, Coord(0, 0), cyan);
  }
}