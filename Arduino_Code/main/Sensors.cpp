#include "Sensors.h"
#include <Wire.h>
#include "DHT.h"
#include <Adafruit_BMP085.h>
#include "Globals.h"

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;

const int humedadAire = 550;
const int humedadAgua = 250;

void initializeSensors() {
    dht.begin();
    if (!bmp.begin()) {
        Serial.println("Could not find a valid BMP085 sensor, check wiring!");
        while (1) {}
    }

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void updateSensors() {
    humedad = dht.readHumidity();
    temperatura = dht.readTemperature();

    if (isnan(humedad) || isnan(temperatura)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }

    indicetemperatura = dht.computeHeatIndex(temperatura, humedad, false);

    float presionCruda = bmp.readPressure() / 100.0;
    presionatm = presionCruda / pow(1 - (0.0065 * altitud) / (temperatura + 0.0065 * altitud + 273.15), 5.257);

    sensorValue = 0;
    sum = 0;
    for (int i = 0; i < 1024; i++) {
        sensorValue = analogRead(A2);
        sum = sensorValue + sum;
        delay(2);
    }
    vout = sum >> 10;
    vout = vout * 4980.0 / 1024;

    if (vout < 50) {
        radiacion = 0;
    } else if (vout < 227) {
        radiacion = 1;
    } else if (vout < 318) {
        radiacion = 2;
    } else if (vout < 408) {
        radiacion = 3;
    } else if (vout < 503) {
        radiacion = 4;
    } else if (vout < 606) {
        radiacion = 5;
    } else if (vout < 696) {
        radiacion = 6;
    } else if (vout < 795) {
        radiacion = 7;
    } else if (vout < 881) {
        radiacion = 8;
    } else if (vout < 976) {
        radiacion = 9;
    } else if (vout < 1079) {
        radiacion = 10;
    } else {
        radiacion = 11;
    }

    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - startTime;

    if (elapsedTime >= 1000) {
        detachInterrupt(digitalPinToInterrupt(windsensorPin));

        float frequency = pulseCount / (elapsedTime / 1000.0);
        velviento = (2.6994 * frequency) + 0.7;

        int directionValue = analogRead(winddirectionPin);
        dirviento = map(directionValue, 0, 1023, 0, 360);

        pulseCount = 0;
        startTime = currentTime;

        attachInterrupt(digitalPinToInterrupt(windsensorPin), countPulse, RISING);
    }

    int humedadtierra = analogRead(sensorPin);
    humsustrato = map(humedadtierra, humedadAire, humedadAgua, 0, 100);
    if (humsustrato > 100) humsustrato = 100;

    Serial.print("Humedad del sustrato: ");
    Serial.print(humsustrato);
    Serial.println("%");

    // Enviar un pulso de 10us al pin Trigger
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Leer la duración del pulso en el pin Echo
    long duration = pulseIn(echoPin, HIGH);
    
    // Calcular la distancia en cm (velocidad del sonido = 34300 cm/s)
    long distance = duration * 0.034 / 2;

    // Calcular el nivel de llenado en porcentaje
    if (distance <= 25) {
        niveldeposito = 100;
    } else if (distance >= 75) {
        niveldeposito = 0;
    } else {
        // Mapeo lineal entre 25cm y 75cm
        niveldeposito = map(distance, 25, 75, 100, 0);
    }

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm, niveldeposito: ");
    Serial.print(niveldeposito);
    Serial.println("%");
}
