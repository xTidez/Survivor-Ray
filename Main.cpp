#include "raylib.h"
#include "GameManager.h"

int main()
{
    // Initialize window
    const int screenWidth = 1000;
    const int screenHeight = 1000;
    const Vector2 screenCenter = { screenWidth * 0.5, screenHeight * 0.5 };
   

    InitWindow(screenWidth, screenHeight, "Survive!");
    SetTargetFPS(60);

    GameManager gameManager;
    gameManager.Initialize(screenWidth, screenHeight, screenCenter);

    // Game loop
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        // Update
        gameManager.Update(deltaTime);

        BeginDrawing();

        ClearBackground(RAYWHITE);
        
        gameManager.Draw();
   

        EndDrawing();
    }

    // Cleanup
    CloseWindow();

    return 0;
}