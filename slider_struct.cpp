#include "raylib.h"

struct Slider {
    Rectangle bounds;
    float value;
    bool isDragging;

    void Update() {
        Vector2 mousePos = GetMousePosition();

        if (CheckCollisionPointRec(mousePos, bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isDragging = true;
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            isDragging = false;
        }

        if (isDragging) {
            value = (mousePos.x - bounds.x) / bounds.width;
            if (value > 1.0f) value = 1.0f;
            if (value < 0.0f) value = 0.0f;
        }

    }

    void Draw() {
        DrawRectangleRec(bounds, BLACK);

        
    }
};