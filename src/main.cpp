/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <time.h>
#include <stdlib.h>
#include "piece.hpp"
#include "queue.hpp"

int main()
{
  // Initialization
  //--------------------------------------------------------------------------------------
  srand((unsigned)time(NULL));
  int screenWidth = 1280;
  int screenHeight = 720;
  bool firstPiece = true;
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
      currentpiece = queue.ShiftPieceQueue();
    if (IsKeyPressed('F'))
      currentpiece.Rotate(RIGHT);
    if (IsKeyPressed('D'))
      currentpiece.Rotate(LEFT);
    if (IsKeyPressed('S'))
      currentpiece.Rotate(DOUBLE);
    if (IsKeyPressed('A'))
      currentpiece = queue.HoldPiece(currentpiece);
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
