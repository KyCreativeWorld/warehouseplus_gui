#include "raylib.h"
#include "slider_struct.cpp"
#include "color_scheme.h"

#include <iostream>
#include <fstream>
#include <stdio.h>

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

    SetTargetFPS(60);

    Slider simIBminSlider = {"Inbound Shipment Minimum: %i", { 1000, 200, 210, 20 }, 0.5f, 0, 300};
    Slider simIBmaxSlider = {"Inbound Shipment Maximum: %i", { 1000, 300, 210, 20 }, 0.5f, 0, 300};

    Slider simOBminSlider = {"Outbound Shipment Minimum: %i", { 1000, 450, 210, 20 }, 0.5f, 0, 300};
    Slider simOBmaxSlider = {"Outbound Shipment Maximum: %i", { 1000, 550, 210, 20 }, 0.5f, 0, 300};

    Slider simTimerminSlider = {"Min: %i", { 1000, 700, 210, 20 }, 0.5f, 0, 300};
    Slider simTimermaxSlider = {"Max: %i", { 1000, 800, 210, 20 }, 0.5f, 0, 300};
    
    // Update
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_BACKSLASH)) {
            ToggleFullscreen();
        }

        // Update the sliders
        simIBminSlider.Update();
        simIBmaxSlider.Update();

        simOBminSlider.Update();
        simOBmaxSlider.Update();

        simTimerminSlider.Update();
        simTimermaxSlider.Update();

        
        // Drawing
        BeginDrawing();

        ClearBackground(SECONDARY_BG);

        DrawRectangle(20, 20, 1670, 927, PRIMARY_BG);

        DrawText("WarehousePLUS", 40, 40, 32, TEXT_COLOR);


        // Draw sliders
        DrawText("Inbound Shipment Count", 1000, 100, 20, TEXT_COLOR);
        simIBminSlider.Draw();
        simIBmaxSlider.Draw();

        simOBminSlider.Draw();
        simOBmaxSlider.Draw();

        simTimerminSlider.Draw();
        simTimermaxSlider.Draw();

        EndDrawing(); // End the drawing

        // Update stats.csv
        int delStatus = remove("stats.csv");

        if (delStatus == 0) {
            std::fstream statsFile("stats.csv");

            statsFile << simTimerminSlider.GetValue() << std::endl << simTimermaxSlider.GetValue()
                      << std::endl << simIBminSlider.GetValue() << std::endl << simIBmaxSlider.GetValue()
                      << std::endl << simOBminSlider.GetValue() << std::endl << simOBmaxSlider.GetValue();

            statsFile.close();
        }
    }

    // Closing
    //--------------------------------------------------------------------------------------
    CloseWindow();

    return 0;
}