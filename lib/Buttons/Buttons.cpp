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
            attackerButtonStates[i] = digitalRead(attackerButtons[i]);
        }
        if(digitalRead(defenderButtons[i])) {
            defenderButtonStates[i] = digitalRead(defenderButtons[i]);
        }
    }
}

void Buttons::initializeInterrupts() {
    // Initialize pin change interrupts on pins 0:5
    for(byte i = 2; i < 8; i++) {
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

