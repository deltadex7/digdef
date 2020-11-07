#ifndef DIG_H_
#define DIG_H_

#define GROUND_WIDTH 10
#define GROUND_HEIGHT 40
#define GROUND_VISIBLE 20

#define SHIFT_DELAY_DEFAULT 12
#define SHIFT_REPEAT_DEFAULT 3
#define LOCK_DELAY_DEFAULT 30
#define LOCK_IDLE_DELAY_DEFAULT 600

const int CLEAR_DELAY[5] = {40, 32, 24, 16, 8};

#include <stdlib.h>
#include "piece.h"
#include "queue.h"

void InitializeGround(GroundColor **area, int width, int height)
{
  if (area == NULL)
  {
    area = (GroundColor **)malloc(sizeof(GroundColor *) * height);
    for(int i = 0; i < height; ++i)
      area[i] = (GroundColor *)malloc(sizeof(GroundColor) * width);
  }

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      area[i][j] = CNONE;
    }
  }
}

struct DigState
{
  int points = 0;
  int level = 0;
  bool isActive = false;
  bool isDead = true;
  PieceState queue[5];
  PieceState hold;
  GroundColor **GroundArea = NULL;
};

void InitializeDigger(DigState *state) {
  state->points = 0;
  state->level = 0;
  state->isActive = true;
  state->isDead = false;
  InitializeGround(state->GroundArea, GROUND_WIDTH, GROUND_HEIGHT);
  InitializePieceQueue(state->queue, 5);
}

#endif
