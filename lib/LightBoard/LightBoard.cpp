#include <LightBoard.h>

LightBoard::LightBoard() {
    for(int i = 0; i < 3; i++) {
        pinMode(lightRowControlPins[i], OUTPUT);
        pinMode(lightColumnControlPins[i], OUTPUT);
    }

    for(int i = 0; i < 3; i++) {
        for(int j = 0; i < 8; i++) {
            lightStates[i][j] = 0;
        }
    }
    
}

// Flash LED with no delay
void LightBoard::powerLED(int row, int column) {
    for(int i = 0; i < 3; i++) {
        if(lightRowControlPins[i] == lightRowControlPins[row]) {
            digitalWrite(lightRowControlPins[i], HIGH);
        }
        else {
            digitalWrite(lightRowControlPins[i], LOW);
        }
    }
    
    digitalWrite(lightColumnControlPins[2], (column & 4));
    digitalWrite(lightColumnControlPins[1], (column & 2));
    digitalWrite(lightColumnControlPins[0], (column & 1));
}


// Iteratively turns on the lights that have state set to high 
void LightBoard::displayLights() {
    for(int row = 0; row < 3; row++) {
        for(int column = 0; column < 8; column++) {
            powerLED(row, column);
            delay(0.5);
        }
    }
}

void LightBoard::updateLightStates(int buttonStates[3]) {
    for(int i = 0; i < 3; i++) {
        if(buttonStates[i]) {
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

// Light sequence when attacker wins
void LightBoard::attackerWinSequence() {
    int currentTime = millis();
    while(millis() - currentTime < 3000) {
        powerLED(2, 7);
        delay(25);
        powerLED(1, 7);
        delay(25);
        powerLED(0, 7);
        delay(25);
    }
}

// Light sequence when defender wins
void LightBoard::defenderWinSequence() {
    int currentTime = millis();
    while(millis() - currentTime < 3000) {
        powerLED(2, 0);
        delay(25);
        powerLED(1, 0);
        delay(25);
        powerLED(0, 0);
        delay(25);
    }
}

int LightBoard::checkLightColumnState(int* arrayToCheck, int column) {
    int numberOfMatches = 0;
    for(int i = 0; i < 3; i++) {
        if(arrayToCheck[i] == lightStates[i][column]) {
            numberOfMatches++;
        }
    }
    return numberOfMatches;
}

void LightBoard::setLightState(int row, int column, int state) {
    lightStates[row][column] = state;
}
