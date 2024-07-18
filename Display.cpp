#include "Display.h"
#include <LiquidCrystal_I2C.h>
#include "Globals.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);

void initializeDisplay() {
    lcd.begin(20, 4);
    lcd.backlight();
}

void displayMenu() {
    lcd.clear();
    switch (menu) {
        case 0:
            lcd.setCursor(0, 0);
            lcd.print("ACTUADORES: ");
            lcd.print(hora);
            lcd.setCursor(0, 1);
            lcd.print("RIEG:");
            lcd.print(digitalRead(riegoPin) == LOW ? "ON " : "OFF ");
            lcd.setCursor(10, 1);
            lcd.print("PURG:");
            lcd.print(digitalRead(purgadoPin) == LOW ? "ON " : "OFF ");
            lcd.setCursor(0, 2);
            lcd.print("LLEN:");
            lcd.print(digitalRead(llenadoPin) == LOW ? "ON " : "OFF ");
            lcd.setCursor(10, 2);
            lcd.print("FOCO:");
            lcd.print(digitalRead(focoPin) == LOW ? "ON " : "OFF ");
            lcd.setCursor(0, 3);
            lcd.print("Water Pres:");
            lcd.print(waterpresent ? "ON " : "OFF ");
            break;
        case 1:
            lcd.setCursor(0, 0);
            lcd.print("ESTACION: ");
            lcd.print("Pres:");
            lcd.print(presionatm);
            lcd.setCursor(0, 1);
            lcd.print("Temp:");
            lcd.print(temperatura);
            lcd.setCursor(10, 1);
            lcd.print(" IndT:");
            lcd.print(indicetemperatura);
            lcd.setCursor(0, 2);
            lcd.print("Humd:");
            lcd.print(humedad);
            lcd.print(" RUV:");
            lcd.print(radiacion);
            lcd.setCursor(0, 3);
            lcd.print("WVel:");
            lcd.print(velviento);
            lcd.print(" WDir:");
            lcd.print(dirviento);
            break;
        case 2:
            lcd.setCursor(0, 0);
            lcd.print("RIEGO: ");
            lcd.print("WaterP: ");
            lcd.print(waterpresent ? "ON " : "OFF ");
            lcd.setCursor(0, 1);
            lcd.print("Tank Level: ");
            lcd.print(niveldeposito);
            lcd.setCursor(0, 2);
            lcd.print("Substrato: ");
            lcd.print(humsustrato);
            lcd.setCursor(0, 3);
            lcd.print("Flow: ");
            lcd.print(caudal);
            break;
    }
}
