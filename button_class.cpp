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
    this->setActive(!this->isActive());
}


void SimulatorButton::Update(int sTimerMin, int sTimerMax, int sIBmin, int sIBmax, int sOBmin, int sOBmax) {
    Vector2 mousePos = GetMousePosition();

    if (CheckCollisionPointRec(mousePos, bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        this->timerMin = sTimerMin;
        this->timerMax = sTimerMax;

        this->IBmin = sIBmin;
        this->IBmax = sIBmax;

        this->OBmin = sOBmin;
        this->OBmax = sOBmax;

        this->onClick();
        this->clickFade = 5;
    }
}

void SimulatorButton::onClick() {
    this->setActive(!this->isActive());

    // std::cout << "Wrote to file" << std::endl;
    std::ofstream simInfoFile("../warehouseplus/simulator_info.json");

    simInfoFile << "{\"sim_active\": " << this->isActive()
                << ", \"sim_timer_min\": " << timerMin
                << ", \"sim_timer_max\": " << timerMax
                << ", \"sim_inbound_min\": " << IBmin
                << ", \"sim_inbound_max\": " << IBmax
                << ", \"sim_outbound_min\": " << OBmin
                << ", \"sim_outbound_max\": " << OBmax << "}";

    simInfoFile.close();
}
