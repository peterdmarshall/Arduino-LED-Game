#include <arduino.h>
#include <buttons.h>

Buttons::Buttons() {
    // Setup buttons
    for(int i = 0; i < 3; i++) {
        pinMode(attackerButtons[i], INPUT);
        pinMode(defenderButtons[i], INPUT);
    }
}

void Buttons::updateButtonStates() {
    for(int i = 0; i < 3; i++) {
        // digitalRead all buttons and update states if they are high
        if(digitalRead(attackerButtons[i])) {
            attackerButtonStates[i] = attackerButtons[i];
        }
        if(digitalRead(defenderButtons[i])) {
            defenderButtonStates[i] = defenderButtons[i];
        }
    }
}

void Buttons::initializeInterrupts() {
    // Initialize interrupts on attacker and defender buttons
    for(int i = 0; i < 3; i++) {
        attachInterrupt(digitalPinToInterrupt(attackerButtons[i]), buttonInterrupt, RISING);
        attachInterrupt(digitalPinToInterrupt(defenderButtons[i]), buttonInterrupt, RISING);
    }
}

void Buttons::buttonInterrupt() {
    // Update button states in button interrupt
    updateButtonStates();
}

int Buttons::getAttackerButton(int index) {
    return attackerButtons[index];
}

int Buttons::getDefenderButton(int index) {
    return defenderButtons[index];
}