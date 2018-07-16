#include <Arduino.h>
#include <Buttons.h>
#include <LightBoard.h>


volatile int defenderMissCounter = 0;
volatile int attackerButtonPresses = 0;
int gameClockCyclePeriod = 250; // In milliseconds
int attackerWins = 0;           // Attacker win flag
int defenderWins = 0;           // Defender win flag

Buttons buttons = Buttons();
LightBoard lightBoard = LightBoard();

void setup() {
    // Initialize the buttons and lights, as well as the interrupts on the buttons
}

void loop() {

    if(defenderMissCounter < 5 && attackerButtonPresses < 30) {

        unsigned long previousTime = millis();
        while(millis() - previousTime < gameClockCyclePeriod) {
            lightBoard.displayLights();
        }
        
        // Update game state once per clock cycle
        lightBoard.shiftLightStates();

    }

    else if(defenderMissCounter >= 5) {
        // Attacker wins!
        defenderWins = 1;
        lightBoard.defenderWinSequence();
        lightBoard.resetLightStates();
        defenderMissCounter = 0;
        attackerButtonPresses = 0;
        defenderWins = 0;
    }

    else if(attackerButtonPresses >= 30) {
        // Defender wins!
        attackerWins = 1;
        lightBoard.attackerWinSequence();
        lightBoard.resetLightStates();
        defenderMissCounter = 0;
        attackerButtonPresses = 0;
        attackerWins = 0;
    }

}

ISR(PCINT2_vect) {
    if(!(attackerWins || defenderWins)) {
        buttons.updateButtonStates();
        lightBoard.updateLightStates(buttons.getAttackerButtonStates(), buttons.getDefenderButtonStates());
        defenderMissCounter += lightBoard.compareLightColumnState(buttons.getDefenderButtonStates(), 6);
        buttons.resetButtonStates();
    }
}


