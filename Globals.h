#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

// Pines de los actuadores
extern const int riegoPin;
extern const int purgadoPin;
extern const int llenadoPin;
extern const int focoPin;

// Pines de los sensores
extern const int sensorPin;
extern const int trigPin;
extern const int echoPin;

// Variables globales
extern volatile bool buttonPressed;
extern unsigned long startTime;
extern unsigned long lastUpdateTime;
extern const unsigned long updateInterval;
extern int menu;

// Variables del sistema
extern bool EVriego;
extern bool EVllenado;
extern bool EVpurgado;
extern bool waterpresent;
extern bool foco;
extern float temperatura;
extern float indicetemperatura;
extern int humedad;
extern int dirviento;
extern float velviento;
extern long presionatm;
extern int niveldeposito;
extern int radiacion;
extern int caudal;
extern int humsustrato;
extern String hora;
extern const float altitud;
extern int sensorValue;
extern long sum;
extern int vout;
extern const int windsensorPin;
extern const int winddirectionPin;
extern const int DHTPIN;
extern const int DHTTYPE;
extern volatile unsigned long pulseCount;
extern const int buttonPin;

// Funciones
void countPulse();

#endif
