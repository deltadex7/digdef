#ifndef PIECE_H
#define PIECE_H

#include <stdlib.h>
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

Color RaylibGroundColor(GroundColor color)
{
  switch (color)
  {
  case CNONE:
    return BLANK;
  case CRED:
    return RED;
  case CORANGE:
    return ORANGE;
  case CYELLOW:
    return YELLOW;
  case CGREEN:
    return GREEN;
  case CCYAN:
    return SKYBLUE;
  case CBLUE:
    return BLUE;
  case CPURPLE:
    return PURPLE;
  case CBROWN:
    return BROWN;
  case CGRAY:
    return GRAY;
  case CLIGHTGRAY:
    return LIGHTGRAY;
  case CDARKGRAY:
    return DARKGRAY;
  case CBLACK:
    return BLACK;
  }
  return BLANK;
}
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

const int PieceIData[4] = {
    11, 12, 13, 14};

const int PieceJData[4] = {
    6, 11, 12, 13};

const int PieceLData[4] = {
    8, 11, 12, 13};

const int PieceOData[4] = {
    7, 8, 12, 13};

const int PieceSData[4] = {
    7, 8, 11, 12};

const int PieceTData[4] = {
    7, 11, 12, 13};

const int PieceZData[4] = {
    6, 7, 12, 13};

/**
 * @brief Set the PieceData object
 * 
 * @param n Enum name of piece
 * @param pdata Piece data to be set
 */
void SetPieceData(PieceName n, int pdata[4])
{
  switch (n)
  {
  case PieceI:
    for (int i = 0; i < 4; i++)
      pdata[i] = PieceIData[i];
    break;
  case PieceJ:
    for (int i = 0; i < 4; i++)
      pdata[i] = PieceJData[i];
    break;
  case PieceL:
    for (int i = 0; i < 4; i++)
      pdata[i] = PieceLData[i];
    break;
  case PieceO:
    for (int i = 0; i < 4; i++)
      pdata[i] = PieceOData[i];
    break;
  case PieceS:
    for (int i = 0; i < 4; i++)
      pdata[i] = PieceSData[i];
    break;
  case PieceT:
    for (int i = 0; i < 4; i++)
      pdata[i] = PieceTData[i];
    break;
  case PieceZ:
    for (int i = 0; i < 4; i++)
      pdata[i] = PieceZData[i];
    break;
  default:
    for (int i = 0; i < 4; i++)
      pdata[i] = 0;
  }
}

/**
 * @brief Get the piece color from name
 * 
 * @param name Name of piece
 * @return Piece color with respect to piece name
 */
GroundColor GetPieceColor(PieceName name)
{
  switch (name)
  {
  case PieceI:
    return CCYAN;
  case PieceJ:
    return CBLUE;
  case PieceL:
    return CORANGE;
  case PieceO:
    return CYELLOW;
  case PieceS:
    return CGREEN;
  case PieceT:
    return CPURPLE;
  case PieceZ:
    return CRED;
  }
  return CNONE;
}

/**
 * @brief Get a random piece
 * 
 * @return Random piece name 
 */
PieceName GetRandomPiece()
{
  static int generated = 0;
  ++generated;
  int val = rand() % 7;
  return (PieceName)(val);
}

typedef enum PieceRotation
{
  ZERO,
  RIGHT,
  DOUBLE,
  LEFT
} PieceRotation;

typedef struct PieceState
{
  PieceName name;
  int piece[4];
  GroundColor color[4];
  PieceRotation rotation;
  int posX;
  int posY;
} PieceState;

PieceState NewPiece()
{
  PieceState state;
  state.name = GetRandomPiece();
  SetPieceData(state.name, state.piece);
  GroundColor color = GetPieceColor(state.name);
  state.color[0] = color;
  state.color[1] = color;
  state.color[2] = color;
  state.color[3] = color;
  state.posX = 0;
  state.posY = 0;
  return state;
}

void PieceRotate(PieceState *rot, PieceRotation delta)
{
  rot->rotation = (PieceRotation)((rot->rotation + delta) % 4);

  switch (delta)
  {
  case RIGHT:
    for (int i = 0; i < 4; ++i)
    {
      int oldP = rot->piece[i];
      int newP = (oldP % 5 + 1) * 5 - (oldP / 5 + 1);
      rot->piece[i] = newP;
    }
    break;
  case LEFT:
    for (int i = 0; i < 4; ++i)
    {
      int oldP = rot->piece[i];
      int newP = (oldP / 5) + (4 - oldP % 5) * 5;
      rot->piece[i] = newP;
    }
    break;
  case DOUBLE:
    for (int i = 0; i < 4; ++i)
    {
      int oldP = rot->piece[i];
      int newP = 24 - oldP;
      rot->piece[i] = newP;
    }
    break;
  case ZERO:
  default:
    break;
  }
}

#pragma endregion Piece

#endif