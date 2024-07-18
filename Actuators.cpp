#include "Actuators.h"
#include "Globals.h"

void initializeActuators() {
    pinMode(riegoPin, OUTPUT);
    pinMode(purgadoPin, OUTPUT);
    pinMode(llenadoPin, OUTPUT);
    pinMode(focoPin, OUTPUT);

    digitalWrite(riegoPin, HIGH);
    digitalWrite(purgadoPin, HIGH);
    digitalWrite(llenadoPin, HIGH);
    digitalWrite(focoPin, HIGH);
}
