#include <arduino.h>

#ifndef LIGHTBOARD_H
#define LIGHTBOARD_H

class LightBoard {
    public:
        LightBoard();
        
        // Flash LED with no delay
        void flashLED(int row, int column);

        // Iteratively turns on the lights that have state set to high 
        void displayLights(int cycleTime);

        // Update the lightStates array based on button states
        void updateLightStates(int attackerButtonStates[3]);

        // Shift light states one (done every game clock cycle)
        void shiftLightStates();

        // Getter and setter for lightStates array
        int getLightState(int row, int column);

        void setLightState(int row, int column, int state);

    private:
        int lightColumnControlPins[3] = {6, 7, 8}; // 3:8 Decoder
        int lightRowControlPins[3] = {9, 10, 11};
        int lightStates[3][8];


};

#endif