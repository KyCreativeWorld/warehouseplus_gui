#include "button_class.h"
#include <iostream>



void Button::Update() {
    Vector2 mousePos = GetMousePosition();

    if (CheckCollisionPointRec(mousePos, bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        this->onClick();
        this->clickFade = 5;
    }
}
void Button::Draw() {
    Color colorA = SECONDARY_BG;
    Color colorB = ACCENT_COLOR;
    if (clickFade-- > 0) { colorA = TEXT_COLOR; colorB = SECONDARY_BG; }

    
    DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height, colorA);
    DrawRectangle(bounds.x + 5, bounds.y + 5, bounds.width - 10, bounds.height - 10, colorB);

    if (this->isActive()) {
        DrawText(onText.c_str(), bounds.x + 15, bounds.y + 15, 20, TEXT_COLOR);
    } else {
        DrawText(offText.c_str(), bounds.x + 15, bounds.y + 15, 20, TEXT_COLOR);
    }
}

void Button::onClick() {
    std::ofstream fileCall("../warehouseplus/backend/" + this->file);

    fileCall.close();
}


void SimulatorButton::Update(int sTimerMin, int sTimerMax, int sIBmin, int sIBmax, int sOBmin, int sOBmax) {
    Vector2 mousePos = GetMousePosition();

    this->timerMin = sTimerMin;
    this->timerMax = sTimerMax;

    this->IBmin = sIBmin;
    this->IBmax = sIBmax;

    this->OBmin = sOBmin;
    this->OBmax = sOBmax;

    if (CheckCollisionPointRec(mousePos, bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        this->onClick();
        this->clickFade = 5;
    }
}

void SimulatorButton::onClick() {
    this->setActive(!this->isActive());

    UpdateJSON();
};

void SimulatorButton::UpdateJSON() {
    // std::cout << "[DEBUG] UpdateJSON() called inside SimulatorButton!" << std::endl;
    // std::cout << "[DEBUG] Current IBmin state: " << IBmin << std::endl;

    std::ofstream simInfoFile("../warehouseplus/backend/simulator_info.json");

    if (!simInfoFile.is_open()) {
        std::cerr << "[ERROR] Could not write to file! Path mismatch or missing 'backend' folder." << std::endl;
        return;
    }

    simInfoFile << "{\"sim_active\": " << (this->isActive() ? "true" : "false")
                << ", \"sim_timer_min\": " << timerMin
                << ", \"sim_timer_max\": " << timerMax
                << ", \"sim_inbound_min\": " << IBmin
                << ", \"sim_inbound_max\": " << IBmax
                << ", \"sim_outbound_min\": " << OBmin
                << ", \"sim_outbound_max\": " << OBmax << "}";

    
    std::ofstream newDataAvailableNotificationFile("../warehouseplus/backend/new_data_available.txt");

    newDataAvailableNotificationFile.close();
    simInfoFile.close();
    // std::cout << "[SUCCESS] simulator_info.json successfully written!" << std::endl;
}