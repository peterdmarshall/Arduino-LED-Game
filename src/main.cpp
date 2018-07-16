#include <Arduino.h>
#include <Buttons.h>
#include <LightBoard.h>

int gameClockCyclePeriod = 120; // In milliseconds

Buttons buttons = Buttons();
LightBoard lightBoard = LightBoard();

volatile int rowSetFlags[3] = {0, 0, 0};
int rowFlashCount[3] = {0, 0, 0};


void setup() {

}

void loop() {
    // Loop through displaying lights for gameClockCyclePeriod length of time
    // Interrupts to update button states are fired throughout this time
    unsigned long previousTime = millis();
    while(millis() - previousTime < gameClockCyclePeriod) {
        lightBoard.displayLights();
    }
        
    // Check if any of the rows has been written to high
    for(int i = 0; i < 3; i++) {
        if(rowSetFlags[i]) {
            if(rowFlashCount[i] == 2) {
                lightBoard.resetLightRowStates(i);
                rowSetFlags[i] = 0;
                rowFlashCount[i] = 0;
            }
            else {
                rowFlashCount[i]++;
            }
        }
    }
    // Update game state once per clock cycle
    lightBoard.shiftLightStates(rowSetFlags);

}


ISR(PCINT2_vect) {
    // Read button states and store updated state
    buttons.updateButtonStates();

    // Update light states based on button states
    lightBoard.updateLightStates(buttons.getAttackerButtonStates(), buttons.getDefenderButtonStates());

    // Check if last column light and defender light states match
    for(int i = 0; i < 3; i++) {
        if(buttons.getDefenderButtonStates()[i] && lightBoard.getLightState(i, 6)) {
            lightBoard.setLightRowStates(i);
            rowSetFlags[i] = 1;
        }
    }
    
    // Reset button states
    buttons.resetButtonStates();
}
