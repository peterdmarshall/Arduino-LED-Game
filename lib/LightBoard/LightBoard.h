#include <arduino.h>

#ifndef LIGHTBOARD_H
#define LIGHTBOARD_H

class LightBoard {
    public:
        LightBoard();
        
        // Flash LED with no delay
        void powerLED(int row, int column);

        // Displays next light in array
        void displayLights();

        // Update the lightStates array based on button states
        void updateLightStates(int attackerButtonStates[3], int defenderButtonStates[3]);

        // Shift light states one (done every game clock cycle)
        void shiftLightStates();

        // Light sequence when attacker wins
        void attackerWinSequence();

        // Light sequence when defender wins
        void defenderWinSequence();

        // Getter and setter for lightStates array
        int getLightState(int row, int column);

        int compareLightColumnState(int statesToCompare[3], int column);

        void setLightState(int row, int column, int state); 

        // Reset light states
        void resetLightStates();

    private:
        int lightColumnControlPins[3] = {10, 9, 8}; // 3:8 Decoder
        int lightRowControlPins[3] = {13, 12, 11};
        // Defender on side by column 7
        // Attacker on side by column 0
        int lightStates[3][8];

};

#endif