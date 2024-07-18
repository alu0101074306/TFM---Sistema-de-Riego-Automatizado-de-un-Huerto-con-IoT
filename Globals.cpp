#include "Globals.h"
#include "DHT.h"

// Pines de los actuadores
const int riegoPin = 44;
const int purgadoPin = 45;
const int llenadoPin = 46;
const int focoPin = 47;

// Pines de los sensores
const int sensorPin = A1;
const int trigPin = 7;
const int echoPin = 6;

// Variables globales
volatile bool buttonPressed = false;
unsigned long startTime;
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 1000;
int menu = 0;

// Variables del sistema
bool EVriego = false;
bool EVllenado = false;
bool EVpurgado = false;
bool waterpresent = true;
bool foco = false;
float temperatura = 0;
float indicetemperatura = 0;
int humedad = 0;
int dirviento = 0;
float velviento = 0;
long presionatm = 0;
int niveldeposito = 0;
int radiacion = 0;
int caudal = 0;
int humsustrato = 0;
String hora = "00:00";

const float altitud = 0.0;

int sensorValue;
long sum = 0;
int vout = 0;

const int windsensorPin = 2;
const int winddirectionPin = A0;
const int DHTPIN = 4;
const int DHTTYPE = DHT22;
volatile unsigned long pulseCount = 0;
const int buttonPin = 3;

void countPulse() {
    pulseCount++;
}
