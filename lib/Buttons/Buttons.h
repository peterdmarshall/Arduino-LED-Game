#include <arduino.h>
#include <vector.h>

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


    private:
        // Attacker buttons are digital pins 0:2
        std::vector<int> attackerButtons[3] = {0, 1, 2};

        // Defender buttons are digital pins 3:5
        std::vector<int> defenderButtons[3] = {3, 4, 5};

        volatile std::vector<int> attackerButtonStates[3];
        volatile std::vector<int> defenderButtonStates[3];


};


#endif