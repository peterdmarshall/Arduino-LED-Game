#include <Arduino.h>
#include <Buttons.h>
#include <LightBoard.h>

int gameClockCyclePeriod = 100; // In milliseconds

Buttons buttons = Buttons();
LightBoard lightBoard = LightBoard();

void setup() {

}

void loop() {
    // 
    unsigned long previousTime = millis();
    while(millis() - previousTime < gameClockCyclePeriod) {
        lightBoard.displayLights();
    }
        
    for(int row = 0; row < 3; row++) {
        int rowCount = 0;
        for(int col = 0; col < 8; col++) {
            if(lightBoard.getLightState(row, col) == 1){
                rowCount++;
            }
        }
        if(rowCount == 7) {
            delay(3000);
            lightBoard.resetLightRowStates(row);
        }
    }
    // Update game state once per clock cycle
    lightBoard.shiftLightStates();

}


ISR(PCINT2_vect) {
    // Read button states and store updated state
    buttons.updateButtonStates();

    // Update light states based on button states
    lightBoard.updateLightStates(buttons.getAttackerButtonStates(), buttons.getDefenderButtonStates());

    // Check if last column light and defender light states match
    if((lightBoard.compareLightColumnState(buttons.getDefenderButtonStates(), 6))) {
        for(int i = 0; i < 3; i++) {
            if(buttons.getDefenderButtonStates()[i] == 1) {
                lightBoard.setLightRowStates(i);
            }
        }
    }
    
    // Reset button states
    buttons.resetButtonStates();
}
