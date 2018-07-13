#include <Arduino.h>
#include <Buttons.h>
#include <LightBoard.h>

Buttons buttons = Buttons();
LightBoard lightBoard = LightBoard();

void setup() {
    // Initialize the buttons and lights, as well as the interrupts on the buttons
}

void loop() {
    // Main loop holds game logic
    lightBoard.displayLights(40); // 40ms game clock cycle
    lightBoard.shiftLightStates();
}



