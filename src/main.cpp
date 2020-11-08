/*******************************************************************************************
*
*   DigDef: Dig and Defend
*
*   Dig the lunar grounds and defend your miner from enemies!
*
*   A submission for GitHub [Game Off 2020](https://itch.io/jam/game-off-2020)
*   under the theme "Moonshot".
*
*   This project is created using raylib 3.0 (www.raylib.com).
*   raylib is licensed under an unmodified zlib/libpng license
*   (View raylib.h for details)
*
*   Copyright (c) 2020 Delta Dextra (@deltadex7)
*
********************************************************************************************/

#include "raylib.h"
#include <ctime>
#include <cstdlib>
#include "piece.hpp"
#include "queue.hpp"
#include <cstdio>

int main()
{
  // Initialization
  //--------------------------------------------------------------------------------------
  srand((unsigned)time(NULL));
  int screenWidth = 1280;
  int screenHeight = 720;
  bool firstPiece = true;
  bool hasHeld = false;
  PieceState currentpiece(true);
  PieceQueue queue(5);

  InitWindow(screenWidth, screenHeight, "game");

  int blockSize = 32;
  int centerWidth = screenWidth / 2;
  int centerHeight = screenHeight / 2;

  SetTargetFPS(60);
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    if (firstPiece)
    {
      currentpiece = queue.ShiftPieceQueue();
      firstPiece = false;
    }
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    if (IsKeyPressed(' '))
    {
      currentpiece = queue.ShiftPieceQueue();
      hasHeld = false;
    }
    if (IsKeyPressed('F'))
      currentpiece.Rotate(RIGHT);
    if (IsKeyPressed('D'))
      currentpiece.Rotate(LEFT);
    if (IsKeyPressed('S'))
      currentpiece.Rotate(DOUBLE);
    if (IsKeyPressed('A'))
      if (!hasHeld)
      {
        currentpiece = queue.HoldPiece(currentpiece);
        hasHeld = true;
      }
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    {
      ClearBackground(DARKGRAY);

      // Draw current
      currentpiece.Draw(centerWidth, centerHeight, blockSize);

      // Draw queue
      int pos = 0;
      for (auto i = queue.queue.begin(); i < queue.queue.end(); i++, pos++)
      {
        i->Draw(
            centerWidth + 8 * blockSize,
            centerHeight + (pos - 2) * 5 * blockSize,
            blockSize);
      }

      // Draw hold
      queue.hold.Draw(centerWidth - 8 * blockSize, centerHeight, blockSize);

      // DrawText("Congrats! You created your first window!", 190, 200, 20, WHITE);
    }
    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
