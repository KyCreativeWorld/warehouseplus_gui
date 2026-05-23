#include "raylib.h"
#include "slider_struct.cpp"
#include "button_class.h"
#include "config.h"
#include "nlohmann/json.hpp"

#include <iostream>
#include <fstream>
#include <stdio.h>

#define MAX_MONITORS 10

using json = nlohmann::json;

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

    Slider simIBminSlider = {"Inbound Shipment Minimum: %i", { 1000, 450, 210, 20 }, 0.5f, 0, 300};
    Slider simIBmaxSlider = {"Inbound Shipment Maximum: %i", { 1000, 550, 210, 20 }, 0.5f, 0, 300};

    Slider simOBminSlider = {"Outbound Shipment Minimum: %i", { 1360, 450, 210, 20 }, 0.5f, 0, 300};
    Slider simOBmaxSlider = {"Outbound Shipment Maximum: %i", { 1360, 550, 210, 20 }, 0.5f, 0, 300};

    Slider simTimerminSlider = {"Minimum Time Inteval: %i", { 1360, 200, 210, 20 }, 0.5f, 0, 300};
    Slider simTimermaxSlider = {"Maximum Time Inteval: %i", { 1360, 300, 210, 20 }, 0.5f, 0, 300};

    SimulatorButton simButton("Off", "On", {1000, 200, 210, 100});
    
    // std::cout << "Created file" << std::endl;
    // std::fstream statsFile("../warehouseplus/info.json");
    
    // Update
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_BACKSLASH)) {
            ToggleFullscreen();
        }

        // Update the sliders
        simTimerminSlider.Update();
        simTimermaxSlider.Update();
        
        simIBminSlider.Update();
        simIBmaxSlider.Update();

        simOBminSlider.Update();
        simOBmaxSlider.Update();

        simButton.Update(simTimerminSlider.GetValue(),
                         simTimermaxSlider.GetValue(),
                         simIBminSlider.GetValue(),
                         simIBmaxSlider.GetValue(),
                         simOBminSlider.GetValue(),
                         simOBmaxSlider.GetValue());

        
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


        simButton.Draw();

        EndDrawing(); // End the drawing

        // Update info.json
        // std::cout << "Removed file" << std::endl;
        // int delStatus = remove("../warehouseplus/info.json");

        // if (delStatus == 0) {
            // std::cout << "Wrote to file" << std::endl;
            // std::fstream statsFile("../warehouseplus/info.json");

            // statsFile << "{\"sim_timer_min\": " << simTimerminSlider.GetValue()
            //           << ", \"sim_timer_max\": " << simTimermaxSlider.GetValue()
            //           << ", \"sim_inbound_min\": " << simIBminSlider.GetValue()
            //           << ", \"sim_inbound_max\": " << simIBmaxSlider.GetValue()
            //           << ", \"sim_outbound_min\": " << simOBminSlider.GetValue()
            //           << ", \"sim_outbound_max\": " << simOBmaxSlider.GetValue() << "}";

            // statsFile.close();
        // }
    }

    // Closing
    //--------------------------------------------------------------------------------------
    if (IsPathFile("../warehouseplus/simulator_info.json")) remove("../warehouseplus/simulator_info.json");
    
    CloseWindow();

    return 0;
}