#include <arduino.h>

#ifndef BUTTONS_H
#define BUTTONS_H

class Buttons {
    public:
        Buttons();

        // Set button and interrupt pin modes to input
        void setButtonPinModes();

        // Read all button states and update them
        void updateButtonStates();

        // Return state of a single attacker button
        int getAttackerButton(int index);

        // Return state of a single defender button
        int getDefenderButton(int index);

        // Set all button states to LOW
        void resetButtonStates();

        // Return array of attackerButtonStates
        volatile int* getAttackerButtonStates();

        // Return array of defenderButtonStates
        volatile int* getDefenderButtonStates();


    private:
        // Attacker buttons are digital pins 0:2
        int attackerButtons[3] = {7, 6, 5};

        // Defender buttons are digital pins 3:5
        int defenderButtons[3] = {4, 3, 1};

        int interruptPin = 2;

        volatile int attackerButtonStates[3] = {0, 0, 0};
        volatile int defenderButtonStates[3] = {0, 0, 0};

};


#endif