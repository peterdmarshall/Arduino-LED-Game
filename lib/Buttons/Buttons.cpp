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
    // Initialize pin change interrupts on pins 0:5
    for(byte i = 0; i < 6; i++) {
        *digitalPinToPCMSK(i) |= bit(digitalPinToPCMSKbit(i));
        PCIFR |= bit(digitalPinToPCICRbit(i));
        PCICR |= bit(digitalPinToPCICRbit(i));
    }
}

int Buttons::getAttackerButton(int index) {
    return attackerButtons[index];
}

int Buttons::getDefenderButton(int index) {
    return defenderButtons[index];
}

volatile int* Buttons::getAttackerButtonStates() {
    return attackerButtonStates;
}

volatile int* Buttons::getDefenderButtonStates() {
    return defenderButtonStates;
}

