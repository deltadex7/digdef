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

// #include <cstdlib>
#include <queue>
#include "piece.hpp"
#include "queue.hpp"

struct DigState
{
  int points = 0;
  int level = 0;
  bool isActive = false;
  bool isDead = true;
  PieceQueue queue;
  // GroundColor **GroundArea = NULL;

  DigState();

  // void InitializeGround(GroundColor **area, int width, int height);
};

#endif
