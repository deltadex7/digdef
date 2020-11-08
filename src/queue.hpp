#ifndef QUEUE_H
#define QUEUE_H
// #include <cstdlib>
#include "piece.hpp"
#include <queue>
#include <algorithm>

class PieceQueue
{
  size_t maxLength;
  void fillQueue();

public:
  std::deque<PieceState> queue;
  PieceState hold;

  PieceQueue(int length);

  void Initialize();

  PieceState ShiftPieceQueue();

  PieceState HoldPiece(PieceState current);
};

#endif
