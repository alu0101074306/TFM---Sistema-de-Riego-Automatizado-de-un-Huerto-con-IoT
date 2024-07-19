#include "Button.h"
#include "Globals.h"

void initializeButton() {
    pinMode(buttonPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING);
}

void buttonISR() {
    buttonPressed = true;
}
