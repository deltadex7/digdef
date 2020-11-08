#ifndef PIECE_H
#define PIECE_H

// #include <cstdlib>
#include "raylib.h"

#pragma region Ground
/**
 * @brief Color for individual ground/block unit
 * 
 */
typedef enum GroundColor
{
  CNONE,
  CRED,
  CORANGE,
  CYELLOW,
  CGREEN,
  CCYAN,
  CBLUE,
  CPURPLE,
  CBROWN,
  CGRAY,
  CLIGHTGRAY,
  CDARKGRAY,
  CBLACK
} GroundColor;

Color RaylibGroundColor(GroundColor color);
#pragma endregion Ground

#pragma region Piece
/**
 * Name of pieces, based on tetromino
 * */
typedef enum PieceName
{
  NoPiece,
  PieceI,
  PieceJ,
  PieceL,
  PieceO,
  PieceS,
  PieceT,
  PieceZ
} PieceName;

class PieceData
{
public:
  static void Set(PieceName n, int pdata[4]);

  static GroundColor GetColor(PieceName name);
};

/**
 * @brief Get a random piece
 * 
 * @return Random piece name 
 */
PieceName GetRandomPiece();

typedef enum PieceRotation
{
  ZERO,
  RIGHT,
  DOUBLE,
  LEFT
} PieceRotation;

struct PieceState
{
  PieceName name;
  int piece[4];
  GroundColor color[4];
  PieceRotation rotation;
  int posX;
  int posY;

  PieceState(bool empty);
  PieceState() : PieceState(false) {}

  void Rotate(PieceRotation delta);

  void Draw(int x, int y, int blockSize);
};

#pragma endregion Piece

#endif
