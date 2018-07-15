#include <Arduino.h>
#include <Buttons.h>
#include <LightBoard.h>

volatile int defenderMissCounter = 0;
volatile int attackerButtonPresses = 0;
int gameClockCyclePeriod = 150; // In milliseconds

Buttons buttons = Buttons();
LightBoard lightBoard = LightBoard();

void setup() {
    // Initialize the buttons and lights, as well as the interrupts on the buttons
    Serial.begin(9600);
}

void loop() {

    if(defenderMissCounter < 5 || attackerButtonPresses < 10) {
        int previousTime = millis();
        while(millis() - previousTime < gameClockCyclePeriod) {
            lightBoard.displayLights();
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 8; j++) {
                    Serial.print(lightBoard.getLightState(i, j));
                    Serial.println();
                }
            }
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
    defenderMissCounter += lightBoard.checkLightColumnState(buttons.getDefenderButtonStates(), 6);
    buttons.resetButtonStates();
}



