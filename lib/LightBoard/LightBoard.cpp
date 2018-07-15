#include <LightBoard.h>

LightBoard::LightBoard() {

}

// Flash LED with no delay
void LightBoard::flashLED(int row, int column) {
    digitalWrite(lightRowControlPins[row], HIGH);
    for(int i = 2; i >= 0; i--) {
        digitalWrite(lightColumnControlPins[i], (column >> i));
    }
}


// Iteratively turns on the lights that have state set to high 
void LightBoard::displayLights(int cycleTime) {
    int startTime = millis();
    int lightCount = 0;
    while((millis() - startTime < cycleTime) || lightCount < 24) {
        for(int row = 0; row < 3; row++) {
            for(int col = 0; col < 8; col++) {
                flashLED(row, col);
                lightCount++;
            }
        }
    }
}

void LightBoard::updateLightStates(int attackerButtonStates[3]) {
    for(int i = 0; i < 3; i++) {
        if(attackerButtonStates[i]) {
            // Set first light to HIGH
            setLightState(i, 1, HIGH);
        }
    }
}

// Shift light states one (done every game clock cycle)
void LightBoard::shiftLightStates() {
    // Make a copy of lightStates array
    int previousLightStates[3][8];
    for(int row = 0; row < 3; row++) {
        for(int col = 0; col < 8; col++) {
            previousLightStates[row][col] = lightStates[row][col];
        }
    }

    // Update lightStates array based on previous lightStates
    for(int row = 0; row < 3; row++) {
        for(int col = 0; col < 8; col++) {
            if(col == 0){
                lightStates[row][0] = 0;
            }
            else {
                lightStates[row][col] = previousLightStates[row][col - 1];
            }
        }
    }
}

int LightBoard::getLightState(int row, int column) {
    return lightStates[row][column];
}

void LightBoard::setLightState(int row, int column, int state) {
    lightStates[row][column] = state;
}
