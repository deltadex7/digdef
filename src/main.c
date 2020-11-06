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
#include "piece.h"

int main()
{
  // Initialization
  //--------------------------------------------------------------------------------------
  int screenWidth = 1280;
  int screenHeight = 720;
  bool firstPiece = true;
  PieceState currentpiece;

  time_t time;

  InitWindow(screenWidth, screenHeight, "game");
  srand(&time);

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
      currentpiece = NewPiece();
      firstPiece = false;
    }
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    if (IsKeyPressed('R'))
      currentpiece = NewPiece();
    if (IsKeyPressed('F'))
      PieceRotate(&currentpiece, RIGHT);
    if (IsKeyPressed('D'))
      PieceRotate(&currentpiece, LEFT);
    if (IsKeyPressed('S'))
      PieceRotate(&currentpiece, DOUBLE);
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    {
      ClearBackground(DARKGRAY);

      for (int i = 0; i < 4; ++i)
      {
        DrawRectangle(
            centerWidth + (currentpiece.piece[i] % 5 - 2) * blockSize,
            centerHeight + (currentpiece.piece[i] / 5 - 2) * blockSize,
            blockSize, blockSize, RaylibGroundColor(currentpiece.color[i]));
      }

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