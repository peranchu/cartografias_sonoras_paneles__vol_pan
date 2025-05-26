/*
              _ _______
    /\        | |__   __|
   /  \   _ __| |_ | | ___  ___
  / /\ \ | '__| __|| |/ _ \/ __|
 / ____ \| |  | |_ | |  __/ (__
/_/    \_\_|   \__||_|\___|\___|

CARTOGRAFÍAS SONORAS
Honorino García Mayo 2025

Panel Principal de control: VOLUMEN - PANORAMIC
"potes.h"
Lectura GAMETRAK VOLUME: Pull - PANORAMIC: Izquierda, Derecha
*/

#include <Arduino.h>
#include <ResponsiveAnalogRead.h>
#include "clip.h"

// Param Potes
#define PotVolumen 34
#define PotPano 33

// POTE VOLUMEN
int valPotes_vol = 0;
int valPotes_scale_vol = 0; // escalado para pintar en Pantalla

int readingPot_vol = 0;
int PotCState_vol = 0;
int PotPState_vol = 0;
const char *envioPot_vol[] = {"/PotVolume"};

int potVar_vol = 0;
const int TIMEOUT_POT_vol = 300;
const byte varthresholdPot_vol = 1;
bool potMoving_vol = true;
unsigned long PTimePot_vol = 0;
unsigned long timerPot_vol = 0;

int pot_min_vol = 26;
int pot_max_vol = 360;
///////////////////////////////////////////////

// POTE PAN
int valPotes_pan = 0;
int valPotes_scale_pan = 0; // escalado para pintar en Pantalla

int readingPot_pan = 0;
int PotCState_pan = 0;
int PotPState_pan = 0;
const char *envioPot_pan[] = {"/PotPan"};

int potVar_pan = 0;
const int TIMEOUT_POT_pan = 300;
const byte varthresholdPot_pan = 1;
bool potMoving_pan = true;
unsigned long PTimePot_pan = 0;
unsigned long timerPot_pan = 0;

int pot_min_pan = 0;
int pot_max_pan = 1023;
///////////////////////////////////////////////

// Resposive analog Read
float snapMultipler = 0.01;
ResponsiveAnalogRead resposivePot_vol;
ResponsiveAnalogRead resposivePot_pan;
///////////////////////////

///////////////////////////

// Lectura Potenciómetros
int Lectura_poteVol()
{
    readingPot_vol = analogRead(PotVolumen);
    resposivePot_vol.update(readingPot_vol);
    PotCState_vol = resposivePot_vol.getValue();

    PotCState_vol = clipValue(PotCState_vol, pot_min_vol, pot_max_vol);

    potVar_vol = abs(PotCState_vol - PotPState_vol);

    if (potVar_vol > varthresholdPot_vol)
    {
        PTimePot_vol = millis();
    }
    timerPot_vol = millis() - PTimePot_vol;

    if (timerPot_vol < TIMEOUT_POT_vol)
    {
        potMoving_vol = true;
    }
    else
    {
        potMoving_vol = false;
    }
    if (potMoving_vol == true)
    {
        valPotes_scale_vol = map(PotCState_vol, 26, 360, 0, 100);
        valPotes_vol = PotCState_vol;

        //Serial.print(" Potenciometro: ");
        //Serial.println(PotCState_vol);

        // Serial.println();

        PotPState_vol = PotCState_vol;
    }

    return valPotes_scale_vol;
}
////// FIN LECTURA POTENCIOMETRO VOLUMEN /////////

// Lectura Potenciometro PANORAMA
int Lectura_potePan()
{
    readingPot_pan = analogRead(PotPano);
    resposivePot_pan.update(readingPot_pan);
    PotCState_pan = resposivePot_pan.getValue();

    PotCState_pan = clipValue(PotCState_pan, pot_min_pan, pot_max_pan);

    potVar_pan = abs(PotCState_pan - PotPState_pan);

    if (potVar_pan > varthresholdPot_pan)
    {
        PTimePot_pan = millis();
    }
    timerPot_pan = millis() - PTimePot_pan;

    if (timerPot_pan < TIMEOUT_POT_pan)
    {
        potMoving_pan = true;
    }
    else
    {
        potMoving_pan = false;
    }
    if (potMoving_pan == true)
    {
        valPotes_scale_pan = map(PotCState_pan, 0, 1023, 0, 100);
        valPotes_pan = PotCState_pan;

        //Serial.print(" PotenciometroPan: ");
        //Serial.println(PotCState_pan);

        // Serial.println();

        PotPState_pan = PotCState_pan;
    }

    return valPotes_scale_pan;
}
////// FIN LECTURA POTENCIOMETRO PANORAMA /////////