#include "dig.hpp"

// void DigState::InitializeGround(GroundColor **area, int width, int height)
// {
//   if (area == NULL)
//   {
//     area = new GroundColor *[height];
//     for (int i = 0; i < height; ++i)
//       area[i] = new GroundColor[width];
//   }

//   for (int i = 0; i < height; i++)
//   {
//     for (int j = 0; j < width; j++)
//     {
//       area[i][j] = CNONE;
//     }
//   }
// }

DigState::DigState() : queue(5)
{
  this->points = 0;
  this->level = 0;
  this->isActive = true;
  this->isDead = false;
  // InitializeGround(this->GroundArea, GROUND_WIDTH, GROUND_HEIGHT);
  queue.Initialize();
}

void PieceQueue::fillQueue()
{
  while (queue.size() < maxLength)
  {
    PieceState state;
    queue.push_back(state);
  }
}

PieceQueue::PieceQueue(int length) : maxLength(length), hold(true)
{
  this->Initialize();
}

void PieceQueue::Initialize()
{
  while (!queue.empty())
  {
    queue.clear();
  }

  this->fillQueue();
}

PieceState PieceQueue::ShiftPieceQueue()
{
  PieceState temp = queue.front();
  queue.pop_front();
  this->fillQueue();
  return temp;
}

PieceState PieceQueue::HoldPiece(PieceState current)
{
  if (hold.name == NoPiece)
  {
    hold = current;
    current = ShiftPieceQueue();
  }
  else
  {
    std::swap(hold, current);
  }
  return current;
}

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

void PieceData::Set(PieceName n, int pdata[4])
{
  static int IData[4] = {
      11, 12, 13, 14};

  static int JData[4] = {
      6, 11, 12, 13};

  static int LData[4] = {
      8, 11, 12, 13};

  static int OData[4] = {
      7, 8, 12, 13};

  static int SData[4] = {
      7, 8, 11, 12};

  static int TData[4] = {
      7, 11, 12, 13};

  static int ZData[4] = {
      6, 7, 12, 13};
  switch (n)
  {
  case PieceI:
    for (int i = 0; i < 4; i++)
      pdata[i] = IData[i];
    break;
  case PieceJ:
    for (int i = 0; i < 4; i++)
      pdata[i] = JData[i];
    break;
  case PieceL:
    for (int i = 0; i < 4; i++)
      pdata[i] = LData[i];
    break;
  case PieceO:
    for (int i = 0; i < 4; i++)
      pdata[i] = OData[i];
    break;
  case PieceS:
    for (int i = 0; i < 4; i++)
      pdata[i] = SData[i];
    break;
  case PieceT:
    for (int i = 0; i < 4; i++)
      pdata[i] = TData[i];
    break;
  case PieceZ:
    for (int i = 0; i < 4; i++)
      pdata[i] = ZData[i];
    break;
  default:
    for (int i = 0; i < 4; i++)
      pdata[i] = 0;
  }
}

GroundColor PieceData::GetColor(PieceName name)
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
  default:
    return CNONE;
  }
  return CNONE;
}

PieceName GetRandomPiece()
{
  static int generated = 0;
  ++generated;
  int val = rand() % 7 + 1;
  return (PieceName)(val);
}

PieceState::PieceState(bool empty)
{

  this->name = empty ? NoPiece : GetRandomPiece();
  PieceData::Set(this->name, this->piece);
  GroundColor color = PieceData::GetColor(this->name);
  this->color[0] = color;
  this->color[1] = color;
  this->color[2] = color;
  this->color[3] = color;
  this->posX = 0;
  this->posY = 0;
}

void PieceState::Rotate(PieceRotation delta)
{

  this->rotation = (PieceRotation)((this->rotation + delta) % 4);

  switch (delta)
  {
  case RIGHT:
    for (int i = 0; i < 4; ++i)
    {
      int oldP = this->piece[i];
      int newP = (oldP % 5 + 1) * 5 - (oldP / 5 + 1);
      this->piece[i] = newP;
    }
    break;
  case LEFT:
    for (int i = 0; i < 4; ++i)
    {
      int oldP = this->piece[i];
      int newP = (oldP / 5) + (4 - oldP % 5) * 5;
      this->piece[i] = newP;
    }
    break;
  case DOUBLE:
    for (int i = 0; i < 4; ++i)
    {
      int oldP = this->piece[i];
      int newP = 24 - oldP;
      this->piece[i] = newP;
    }
    break;
  case ZERO:
  default:
    break;
  }
}

void PieceState::Draw(int x, int y, int blockSize)
{
  for (int i = 0; i < 4; ++i)
  {
    DrawRectangle(
        x + ((piece[i] % 5) * blockSize),
        y + ((piece[i] / 5) * blockSize),
        blockSize, blockSize, RaylibGroundColor(color[i]));
  }
}