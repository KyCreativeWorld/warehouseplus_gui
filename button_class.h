#pragma once

#include "raylib.h"
#include <string>
#include <fstream>
// #include <nlohmann/json.hpp>
// using json = nlohmann::json;

class Button {
    private:
        std::string type;
        Rectangle bounds;
        bool active;
    public:
        Button(std::string t, Rectangle b) { this->type = t; this->bounds = b; }

        void update();
        void draw();

        bool isActive() { return this->active; }
        void setActive(bool a) { this->active = a; }

    protected:
        virtual void onClick();
};

class SimulatorButton : public Button {  
    public:
        void setSliderValues(int inboundMin, int inboundMax, int outboundMin, int outboundMax, int timerMin, int timerMax) {
            this->IBmin = inboundMin;
            this->IBmax = inboundMax;

            this->OBmin = outboundMin;
            this->OBmax = outboundMax;

            this->timerMin = timerMin;
            this->timerMax = timerMax;
        }
    protected:
        void onClick() override;
    private:
        int IBmin;
        int IBmax;

        int OBmin;
        int OBmax;

        int timerMin;
        int timerMax;
};