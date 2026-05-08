#include "raylib.h"

#define MAX_MONITORS 10

// Monitor info
typedef struct MonitorInfo {
    Vector2 position;
    const char *name;
    int width;
    int height;
    int physicalWidth;
    int physicalHeight;
    int refreshRate;
} MonitorInfo;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1710;
    const int screenHeight = 1107;

    InitWindow(screenWidth, screenHeight, "📦 WarehousePLUS 📦");

    MonitorInfo monitors[MAX_MONITORS] = { 0 };
    int currentMonitorIndex = GetCurrentMonitor();
    int monitorCount = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_BACKSLASH)) {
            ToggleFullscreen();
        }

        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        DrawRectangle(20, 20, 1670, 927, GRAY);

        DrawText("WarehousePLUS", 40, 40, 32, BLACK);

        


        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}