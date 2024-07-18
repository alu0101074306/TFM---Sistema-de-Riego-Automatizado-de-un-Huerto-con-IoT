#include "Communication.h"
#include "Globals.h"

void initializeCommunication() {
    Serial2.begin(9600);
}

void handleCommunication() {
    if (Serial2.available()) {
        String command = Serial2.readStringUntil('\n');
        Serial.print("Received command: ");
        Serial.println(command);
        if (command == "REQUEST_DATA") {
            sendDataToPi();
        } else if (command.startsWith("SET_TIME:")) {
            hora = command.substring(9);
        } else if (command.startsWith("SET_RIEGO:")) {
            EVriego = command.substring(10) == "ON";
            digitalWrite(riegoPin, EVriego ? LOW : HIGH);
            Serial.print("Riego set to: ");
            Serial.println(EVriego ? "ON" : "OFF");
        } else if (command.startsWith("SET_PURGADO:")) {
            EVpurgado = command.substring(12) == "ON";
            digitalWrite(purgadoPin, EVpurgado ? LOW : HIGH);
            Serial.print("Purgado set to: ");
            Serial.println(EVpurgado ? "ON" : "OFF");
        } else if (command.startsWith("SET_LLENADO:")) {
            EVllenado = command.substring(11) == "ON";
            digitalWrite(llenadoPin, EVllenado ? LOW : HIGH);
            Serial.print("Llenado set to: ");
            Serial.println(EVllenado ? "ON" : "OFF");
        } else if (command.startsWith("SET_FOCO:")) {
            foco = command.substring(9) == "ON";
            digitalWrite(focoPin, foco ? LOW : HIGH);
            Serial.print("Foco set to: ");
            Serial.println(foco ? "ON" : "OFF");
        }
    }
}

void sendDataToPi() {
    Serial2.print("Temperature: ");
    Serial2.print(temperatura);
    Serial2.print("°C, Humidity: ");
    Serial2.print(humedad);
    Serial2.print("%, Pressure: ");
    Serial2.print(presionatm);
    Serial2.print(" mb, Index Temp: ");
    Serial2.print(indicetemperatura);
    Serial2.print("°C, Wind Speed: ");
    Serial2.print(velviento);
    Serial2.print(" km/h, Wind Direction: ");
    Serial2.print(dirviento);
    Serial2.print(" deg, UV Index: ");
    Serial2.print(radiacion);
    Serial2.print(", Water Present: ");
    Serial2.print(waterpresent ? "Yes" : "No");
    Serial2.print(", Riego: ");
    Serial2.print(digitalRead(riegoPin) == LOW ? "ON" : "OFF");
    Serial2.print(", Purgado: ");
    Serial2.print(digitalRead(purgadoPin) == LOW ? "ON" : "OFF");
    Serial2.print(", Llenado: ");
    Serial2.print(digitalRead(llenadoPin) == LOW ? "ON" : "OFF");
    Serial2.print(", Foco: ");
    Serial2.print(digitalRead(focoPin) == LOW ? "ON" : "OFF");
    Serial2.print(", Tank Level: ");
    Serial2.print(niveldeposito);
    Serial2.print(", Caudal: ");
    Serial2.print(caudal);
    Serial2.print(", Humedad del Sustrato: ");
    Serial2.print(humsustrato);
    Serial2.print(", Hora: ");
    Serial2.println(hora);
}
