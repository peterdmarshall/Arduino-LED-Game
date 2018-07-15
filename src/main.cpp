#include <Arduino.h>
#include <Buttons.h>
#include <LightBoard.h>

int defenderMissCounter = 0;
int attackerButtonPresses = 0;
int gameClockCyclePeriod = 20; // In milliseconds

Buttons buttons = Buttons();
LightBoard lightBoard = LightBoard();

void setup() {
    // Initialize the buttons and lights, as well as the interrupts on the buttons
}

void loop() {

    if(defenderMissCounter < 5 || attackerButtonPresses < 50) {
        int startTime = millis();

        // Display lights for the time specified by gameClockCyclePeriod
        while(millis() - startTime < gameClockCyclePeriod) {
            lightBoard.displayLights();
        }

        // Update game state once per clock cycle
        lightBoard.shiftLightStates();
    }

    else if(defenderMissCounter < 5) {
        // Defender wins!
        lightBoard.defenderWinSequence();
    }

    else if(attackerButtonPresses < 50) {
        // Attacker wins!
        lightBoard.attackerWinSequence();
    }


}

ISR(PCINT2_vect) {
    buttons.updateButtonStates();
    lightBoard.updateLightStates(buttons.getAttackerButtonStates());
    defenderMissCounter += lightBoard.checkLightColumnState(buttons.getDefenderButtonStates(), 7);
}



