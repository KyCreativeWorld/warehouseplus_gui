#include "raylib.h"
#include "slider_struct.cpp"
#include "button_class.h"
#include "config.h"
#include "nlohmann/json.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>

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
    try {
        // std::filesystem::remove returns true if the file was deleted, false if it didn't exist
        if (std::filesystem::remove("../warehouseplus/backend/simulator_info.json")) {
            std::cout << "Cleanup successful: simulator_info.json file deleted.\n";
        } else {
            std::cout << "Cleanup note: File did not exist.\n";
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Cleanup Error: Could not delete file. " << e.what() << '\n';
    }

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1710;
    const int screenHeight = 1107;

    InitWindow(screenWidth, screenHeight, "📦 WarehousePLUS 📦");

    MonitorInfo monitors[MAX_MONITORS] = { 0 };
    int currentMonitorIndex = GetCurrentMonitor();
    int monitorCount = 0;

    SetTargetFPS(60);

    std::ofstream programIsRunningFile("../warehouseplus/backend/is_running.txt");



    Slider simIBminSlider = {"Inbound Shipment Minimum: %i", { 1000, 450, 210, 20 }, 0.5f, 0, 300};
    Slider simIBmaxSlider = {"Inbound Shipment Maximum: %i", { 1000, 550, 210, 20 }, 0.5f, 0, 300};

    Slider simOBminSlider = {"Outbound Shipment Minimum: %i", { 1360, 450, 210, 20 }, 0.5f, 0, 300};
    Slider simOBmaxSlider = {"Outbound Shipment Maximum: %i", { 1360, 550, 210, 20 }, 0.5f, 0, 300};

    Slider simTimerminSlider = {"Minimum Time Inteval: %i", { 1360, 200, 210, 20 }, 0.5f, 1, 30};
    Slider simTimermaxSlider = {"Maximum Time Inteval: %i", { 1360, 300, 210, 20 }, 0.5f, 1, 30};

    SimulatorButton simButton("Off", "On", {1000, 160, 210, 80});
    SimUpdateButton simUpdater("Update", "Update", {1000, 260, 210, 80}, simButton);

    Button delButton("Delete 10 Items", "Delete 10 Items", {640, 160, 210, 80}, "delete_items.txt");
    Button saleButton("SALE", "SALE", {640, 260, 210, 80}, "put_items_on_sale.txt");
    
    

    unsigned int warehouseSize = 0;
    unsigned int firstItemPrice = 0;
    
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

        simUpdater.Update();

        delButton.Update();
        saleButton.Update();

        
        // Drawing
        BeginDrawing();

        ClearBackground(SECONDARY_BG);

        DrawRectangle(20, 20, 1670, 927, PRIMARY_BG);

        DrawText("WarehousePLUS", 40, 40, 32, TEXT_COLOR);



        if (std::filesystem::remove("new_data_available.txt")) {
            std::ifstream warehouseInfoFile("warehouse_info.json");

            json warehouseInfo;
            try {
                warehouseInfoFile >> warehouseInfo;
                warehouseSize = warehouseInfo["warehouse_size"];
                firstItemPrice = warehouseInfo["first_item_price"];
            } catch (const json::parse_error& e) {
                std::cout << "JSON Parsing Error on update: " << e.what() << std::endl;
            }

            warehouseInfoFile.close();
        }

        DrawText(TextFormat("Warehouse Size: %u", warehouseSize), 40, 740, 52, TEXT_COLOR);
        DrawText(TextFormat("First Item's Price: %u", firstItemPrice), 40, 840, 52, TEXT_COLOR);
        


        // Draw sliders
        DrawText("Inbound Shipment Count", 1000, 100, 20, TEXT_COLOR);
        simIBminSlider.Draw();
        simIBmaxSlider.Draw();

        simOBminSlider.Draw();
        simOBmaxSlider.Draw();

        simTimerminSlider.Draw();
        simTimermaxSlider.Draw();


        simButton.Draw();
        simUpdater.Draw();

        delButton.Draw();
        saleButton.Draw();

        EndDrawing(); // End the drawing
    }

    // Closing
    //--------------------------------------------------------------------------------------
    try {
        if (std::filesystem::remove("../warehouseplus/backend/simulator_info.json")) {
            std::cout << "Cleanup successful: simulator_info.json file deleted.\n";
        } else {
            std::cout << "Cleanup note: File did not exist.\n";
        }
        
        if (std::filesystem::remove("../warehouseplus/backend/new_data_available.txt")) {
            std::cout << "Cleanup successful: new_data_available.txt file deleted.\n";
        } else {
            std::cout << "Cleanup note: new_data_available.txt already deleted.\n";
        }

        if (std::filesystem::remove("../warehouseplus/backend/delete_items.txt")) {
            std::cout << "Cleanup successful: delete_items.txt file deleted.\n";
        } else {
            std::cout << "Cleanup note: delete_items.txt already deleted.\n";
        }

        if (std::filesystem::remove("../warehouseplus/backend/is_running.txt")) {
            std::cout << "Cleanup successful: is_running.txt file deleted.\n";
        } else {
            std::cout << "Cleanup note: is_running.txt already deleted.\n";
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Cleanup Error: Could not delete file. " << e.what() << '\n';
    }

    CloseWindow();

    return 0;
}