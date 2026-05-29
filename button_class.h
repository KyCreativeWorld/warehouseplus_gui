#pragma once

#include "raylib.h"
#include "config.h"
#include <string>
#include <fstream>
// #include <nlohmann/json.hpp>
// using json = nlohmann::json;

class Button {
    protected:
        std::string offText;
        std::string onText;
        Rectangle bounds;
        bool active;

        short clickFade = 0;    
        virtual void onClick();

    public:
        Button(std::string offText, std::string onText, Rectangle buttonShape) {
            this->offText = offText;
            this->onText = onText;
            this->bounds = buttonShape;
        }

        void Update();
        void Draw();

        bool isActive() { return this->active; }
        void setActive(bool a) { this->active = a; }
};

class SimulatorButton : public Button {  
    public:
        SimulatorButton(std::string offText, std::string onText, Rectangle buttonShape) : Button(offText, onText, buttonShape) {
            this->IBmin = 0;
            this->IBmax = 0;
            this->OBmin = 0;
            this->OBmax = 0;
            this->timerMin = 0;
            this->timerMax = 0;
        }

        void setSliderValues(int inboundMin, int inboundMax, int outboundMin, int outboundMax, int timerMin, int timerMax) {
            this->IBmin = inboundMin;
            this->IBmax = inboundMax;

            this->OBmin = outboundMin;
            this->OBmax = outboundMax;

            this->timerMin = timerMin;
            this->timerMax = timerMax;
        }

        void Update(int sTimerMin, int sTimerMax, int sIBmin, int sIBmax, int sOBmin, int sOBmax);

        void UpdateJSON();
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

class SimUpdateButton : public Button {
    public:
        SimUpdateButton(std::string offText, std::string onText, Rectangle buttonShape, SimulatorButton& sim)
                       : Button(offText, onText, buttonShape),
                         simButton(sim) {}
    protected:
        SimulatorButton& simButton;
        void onClick() override { simButton.UpdateJSON(); }
    
};