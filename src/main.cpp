#include <Arduino.h>
#include <Buttons.h>
#include <LightBoard.h>

int gameClockCyclePeriod = 150; // Time for each clock cycle in milliseconds

// Create an instance of buttons and lightboard classes to interface with hardware
Buttons buttons = Buttons();
LightBoard lightBoard = LightBoard();

volatile int rowSetFlags[3] = {0, 0, 0}; // Keep track of whether the row has been set to HIGH
int rowSetCycleCount[3] = {0, 0, 0}; // Keep track of how many cycles the row has been set to HIGH 
volatile int defenderScore = 0; // Number of times the defender has won

void buttonPress() {
    // Read button states and store updated state
    buttons.updateButtonStates();

    // Update light states based on button states
    lightBoard.updateLightStates(buttons.getAttackerButtonStates(), buttons.getDefenderButtonStates());

    // Check if last column light and defender light states match
    for(int i = 0; i < 3; i++) {
        if(buttons.getDefenderButtonStates()[i] && lightBoard.getLightState(i, 6) && !rowSetFlags[i]) {
            lightBoard.setLightRowStates(i);
            rowSetFlags[i] = 1;
            defenderScore++;
        }
    }
    
    // Reset button states to LOW
    buttons.resetButtonStates();
}

void setup() {
    // Attach interrupt on pin 2
    attachInterrupt(digitalPinToInterrupt(2), buttonPress, RISING);
}

void loop() {
    if(defenderScore < 10) {
        // Loop through displaying lights for gameClockCyclePeriod length of time
        // Interrupts to update button states are fired throughout this time
        unsigned long previousTime = millis();
        while(millis() - previousTime < gameClockCyclePeriod) {
            lightBoard.displayLights();
        }
            
        // Check if any of the rows has been written to high by testing rowSetFlags for each row
        for(int i = 0; i < 3; i++) {
            if(rowSetFlags[i]) {
                if(rowSetCycleCount[i] == 2) {
                    // If rowSetCycleCount is high enough reset states of light row and reset flags
                    // to allow the row to function normally again
                    lightBoard.resetLightRowStates(i);
                    rowSetFlags[i] = 0;
                    rowSetCycleCount[i] = 0;
                }
                else {
                    // If rowSetCycleCount is not high enough, increment rowSetCycleCount
                    rowSetCycleCount[i]++;
                }
            }
        }
        // Shift light states, excluding any rows that have been set to high 
        lightBoard.shiftLightStates(rowSetFlags);
    }
    else {
        // If the defender reaches a score of 10, run winSequence and reset the game
        lightBoard.runWinSequence();
        lightBoard.resetAllLightStates();
        defenderScore = 0;
    }

}

