#include <buttons.h>

Buttons::Buttons() {
    setButtonPinModes();
}

void Buttons::setButtonPinModes() {
    // Set pinModes for button inputs
    for(int i = 0; i < 3; i++) {
        pinMode(attackerButtons[i], INPUT);
        pinMode(defenderButtons[i], INPUT);
    }
    pinMode(interruptPin, INPUT);
}

void Buttons::updateButtonStates() {
    for(int i = 0; i < 3; i++) {
        // digitalRead all buttons and update states if they are high
        if(digitalRead(attackerButtons[i])) {
            attackerButtonStates[i] = digitalRead(attackerButtons[i]);
        }
        if(digitalRead(defenderButtons[i])) {
            defenderButtonStates[i] = digitalRead(defenderButtons[i]);
        }
    }
}

int Buttons::getAttackerButton(int index) {
    return attackerButtons[index];
}

int Buttons::getDefenderButton(int index) {
    return defenderButtons[index];
}

void Buttons::resetButtonStates() {
    for(int i = 0; i < 3; i++) {
        attackerButtonStates[i] = 0;
        defenderButtonStates[i] = 0;
    }
}

volatile int* Buttons::getAttackerButtonStates() {
    return attackerButtonStates;
}

volatile int* Buttons::getDefenderButtonStates() {
    return defenderButtonStates;
}

