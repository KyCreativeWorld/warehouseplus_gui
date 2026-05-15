#include "raylib.h"
#include <cmath>
#include <string>
#include <format>

#include "color_scheme.h"

struct Slider {
    std::string sliderText;
    Rectangle bounds;
    float sliderPos;
    int minVal;
    int maxVal;
    int valsInterval = maxVal - minVal;
    bool isDragging = false;
    Rectangle sliderBounds = {bounds.x + (bounds.width / 2), (bounds.y + (bounds.height / 2)) - bounds.height, (bounds.height + 2) * 2, (bounds.height + 2) * 2};

    int GetValue() {
        return minVal + static_cast<int>(std::round(sliderPos * valsInterval));
    }
    
    void Update() {
        Vector2 mousePos = GetMousePosition();

        if ((CheckCollisionPointRec(mousePos, bounds) || CheckCollisionPointRec(mousePos, sliderBounds)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isDragging = true;
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            isDragging = false;
        }

        if (isDragging) {
            sliderPos = (mousePos.x - bounds.x) / bounds.width;
            if (sliderPos > 1.0f) sliderPos = 1.0f;
            if (sliderPos < 0.0f) sliderPos = 0.0f;

            if (valsInterval > 0) {
                sliderPos = std::round(sliderPos * valsInterval) / valsInterval;
            }
        }

    }

    void Draw() {
        DrawRectangle(bounds.x + 5, bounds.y + 5, bounds.width - 10, bounds.height - 10, BLACK);

        float sliderX = bounds.x + (sliderPos * bounds.width);
        sliderBounds.x = sliderX - bounds.height;
        DrawCircle(sliderX, bounds.y + (bounds.height / 2), bounds.height, ACCENT_COLOR);

        if (isDragging) DrawCircleLines(sliderX, bounds.y + (bounds.height / 2), bounds.height + 2, SECONDARY_BG);

        DrawText(TextFormat(sliderText.c_str(), GetValue()), bounds.x - 40, bounds.y - 40, 20, TEXT_COLOR);
    }
};