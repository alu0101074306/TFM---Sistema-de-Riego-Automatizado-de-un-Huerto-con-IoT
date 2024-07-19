#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <Adafruit_BMP085.h>
#include "Sensors.h"
#include "Actuators.h"
#include "Display.h"
#include "Communication.h"
#include "Button.h"
#include "Globals.h"

void setup() {
    Serial.begin(9600);
    Serial2.begin(9600);

    initializeSensors();
    initializeDisplay();
    initializeActuators();
    initializeCommunication();
    initializeButton();

    displayMenu();
    startTime = millis();
}

void loop() {
    updateSensors();

    if (buttonPressed) {
        buttonPressed = false;
        menu = (menu + 1) % 3;
        displayMenu();
    }

    handleCommunication();

    unsigned long currentTime = millis();
    if (currentTime - lastUpdateTime >= updateInterval) {
        lastUpdateTime = currentTime;
        displayMenu();
    }
}
