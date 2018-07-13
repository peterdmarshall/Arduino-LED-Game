#include <arduino.h>

#ifndef BUTTONS_H
#define BUTTONS_H
#define RISING 3

class Buttons {
    public:
        Buttons();

        // Read all button states and update them
        void updateButtonStates();

        // Interrupt triggered whenever a button is pressed
        void buttonInterrupt();

        // Initialize interrupts on attacker and defender buttons
        void initializeInterrupts();

        int getAttackerButton(int index);

        int getDefenderButton(int index);


    private:
        // Attacker buttons are digital pins 0:2
        int attackerButtons[3] = {0, 1, 2};

        // Defender buttons are digital pins 3:5
        int defenderButtons[3] = {3, 4, 5};

        int attackerButtonStates[3];
        int defenderButtonStates[3];


};



#endif