#include <arduino.h>

#ifndef LIGHTBOARD_H
#define LIGHTBOARD_H

class LightBoard {
    public:
        LightBoard();
        
        // Set pins to output
        void setControlPinModes();

        // Power LED by writing to control pins
        void powerLED(int row, int column);

        // Iterates over lightStateArray, using powerLED on lights with state=HIGH
        void displayLights();

        // Update the lightStates array based on button states
        void updateLightStates(int attackerButtonStates[3], int defenderButtonStates[3]);

        // Shift light states one space (done every game clock cycle)
        void shiftLightStates();

        // Shift light states one space, excluding the specified rows
        void shiftLightStates(int rowsToExclude[3]);

        // Get state of single entry in lightStates array
        int getLightState(int row, int column);

        // Set state of single entry in lightStates array
        void setLightState(int row, int column, int state); 

        // Reset all light states in lightStates array to LOW
        void resetAllLightStates();

        // Reset all light states in specified row of lightStates array to LOW
        void resetLightRowStates(int row);

        // Light sequence when defender wins
        void runWinSequence();

        // Set all light states in lightStates array to HIGH
        void setAllLightStates();

        // Set all light states in specified row of lightStates array to HIGH
        void setLightRowStates(int row);

    private:
        int lightColumnControlPins[3] = {10, 9, 8}; // 3:8 Decoder
        int lightRowControlPins[3] = {13, 12, 11}; 

        // Array to hold state of each light (HIGH/LOW)
        int lightStates[3][8];

};

#endif