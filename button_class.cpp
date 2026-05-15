#include "button_class.h"



void Button::update() {
    Vector2 mousePos = GetMousePosition();

    if (CheckCollisionPointRec(mousePos, bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        this->onClick();
    }
}
void Button::draw() {

}

void Button::onClick() {
    this->setActive(!this->isActive());
}



void SimulatorButton::onClick() {
    this->setActive(!this->isActive());

    std::ofstream simulatorInfo("simulator_info.json");

    simulatorInfo << "{\"inboundMin\": }"
}
