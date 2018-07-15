#include <buttons.h>

Buttons::Buttons() {
    // Setup buttons
    for(int i = 0; i < 3; i++) {
        pinMode(attackerButtons[i], INPUT);
        pinMode(defenderButtons[i], INPUT);
    }
    // Initialize interrupts
    initializeInterrupts();
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
    // Initialize pin change interrupts on pins 0:7
    PCICR |= 0b00000001;
    PCMSK2 |= 0b0011111;
}

int Buttons::getAttackerButton(int index) {
    return attackerButtons[index];
}

int Buttons::getDefenderButton(int index) {
    return defenderButtons[index];
}
