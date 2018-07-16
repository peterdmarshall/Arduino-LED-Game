#include <arduino.h>

#ifndef BUTTONS_H
#define BUTTONS_H

class Buttons {
    public:
        Buttons();

        // Read all button states and update them
        void updateButtonStates();

        // Initialize interrupts on attacker and defender buttons
        void initializeInterrupts();

        int getAttackerButton(int index);

        int getDefenderButton(int index);

        void resetButtonStates();

        volatile int* getAttackerButtonStates();

        volatile int* getDefenderButtonStates();


    private:
        // Attacker buttons are digital pins 0:2
        int attackerButtons[3] = {7, 6, 5};

        // Defender buttons are digital pins 3:5
        int defenderButtons[3] = {4, 3, 2};

        volatile int attackerButtonStates[3] = {0, 0, 0};
        volatile int defenderButtonStates[3] = {0, 0, 0};


};


#endif