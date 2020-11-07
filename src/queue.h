#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>
#include "piece.h"

void InitializePieceQueue(PieceState *queue, int length)
{
  for (int i = 0; i < length; ++i)
    queue[i] = NewPiece();
}

PieceState ShiftPieceQueue(PieceState *queue, int length)
{
  PieceState temp = queue[0];
  for (int i = 0; i < length; ++i)
  {
    if (i < length - 1)
      queue[i] = queue[i + 1];
    else
      queue[i] = NewPiece();
  }
  return temp;
}

void HoldPiece(PieceState *queue, PieceState *hold, PieceState *current, int length)
{
  if (hold->name == NoPiece)
  {
    *hold = *current;
    *current = ShiftPieceQueue(queue, length);
  }
  else
  {
    PieceState *temp = hold;
    hold = current;
    current = temp;
  }
}

#endif