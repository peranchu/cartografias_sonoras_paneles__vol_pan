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
"pantalla.h"
Gestión Pantalla Inicio - Principal VOLUMEN - PANORAMIC
*/

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x26, 16, 2); // Dirección i2c y tamaño 16x2

// Set Pantalla Inicio
char text[] = "Cartografias Sonoras"; // Texto Pantalla inicio
const unsigned int scrollDelay = 200;
const unsigned int demoDelay = 2000;
byte textLen;

// define custom characters - every character is 5x8 "pixels"
byte gauge_left[8] = {B11111, B10000, B10000, B10000, B10000, B10000, B10000, B11111};   // left part of empty gauge    [
byte gauge_center[8] = {B11111, B00000, B00000, B00000, B00000, B00000, B00000, B11111}; // center part of empty gauge  _
byte gauge_right[8] = {B11111, B00001, B00001, B00001, B00001, B00001, B00001, B11111};  // right part of empty gauge   ]
byte gauge_fill[8] = {B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111};   // filled gauge                █

int cpu_gauge;   // value for the CPU gauge
int gpu_gauge;   // value for the GPU gauge
char buffer[10]; // helper buffer to store C-style strings (generated with sprintf function)

const int gauge_size_chars = 16;         // width of the gauge in number of characters
char gauge_string[gauge_size_chars + 1]; // string that will include all the gauge character to be printed

// Dibuja la pantalla Principal
void dibujoPantalla(int valVol, int valPan)
{
    // VOLUME Gauge
    lcd.setCursor(0, 0);                  // move cursor to top left
    sprintf(buffer, "VOL:%3d%%", valVol); // set a string as CPU: XX%, with the number always taking at least 3 character
    lcd.print(buffer);                    // print the string on the display

    // 8 characters to draw the gauge --- ████___]
    float cpu_gauge_step = 100.0 / 8.0; // 100% is the maximum number, gauge is 8 characters wide, calculate one step
    for (int i = 0; i < 8; i++)
    {
        if (valVol <= cpu_gauge_step * i)
        { // value is smaller than step*i, draw "empty" character
            if (i == 0)
            {
                lcd.write(0);
            } // [     first cell, opening bracket
            else if (i == 7)
            {
                lcd.write(2);
            } // ]     last cell, closing bracket
            else
            {
                lcd.write(1);
            } // _     any other cell, lines top and bottom
        }
        else
        { // value is bigger than step*i, draw filled character - █
            lcd.write(3);
        }
    }

    // PANORAMIC Gauge
    lcd.setCursor(0, 1);                  // move cursor to second line
    sprintf(buffer, "PAN:%3d%%", valPan); // set a string as GPU: XX%, with the number always taking at least 3 character
    lcd.print(buffer);                    // print the string on the display

    // 8 characters to draw the gauge --- [______]
    float gpu_gauge_step = 100.0 / 8.0; // 100% is the maximum number, gauge is 8 characters wide, calculate one step
    for (int i = 0; i < 8; i++)
    {
        if (valPan <= gpu_gauge_step * i)
        { // value is smaller than step*i, draw "empty" character
            if (i == 0)
            {
                lcd.write(0);
            } // [     first cell, opening bracket
            else if (i == 7)
            {
                lcd.write(2);
            } // ]     last cell, closing bracket
            else
            {
                lcd.write(1);
            } // _     any other cell, lines top and bottom
        }
        else
        { // value is bigger than step*i, draw filled character - █
            lcd.write(3);
        }
    }

    delay(100); // wait for a while - 100ms = update the screen 10x in a second
}
////// FIN DIBUJO PANTALLA PRINCPAL ///////

// Dibujo Pantalla inicio
void Pantalla_inicio()
{
    textLen = sizeof(text) - 1;

    lcd.setCursor(0, 0);
    lcd.print(text);
    delay(5);

    // Scroll entire text in a row to the left outside the screen
    for (byte positionCounter = 0; positionCounter < textLen; positionCounter++)
    {
        lcd.scrollDisplayLeft();
        delay(scrollDelay);
    }

    // Scroll entire text in a row to the right outside the screen
    for (byte posticionCounter = 0; posticionCounter < textLen + 16; posticionCounter++)
    {
        lcd.scrollDisplayRight();
        delay(scrollDelay);
    }

    lcd.clear();

    lcd.setCursor(0, 1);
    lcd.print("ArtTec (c)2025");
    delay(demoDelay);
}
////// FIN DIBUJO PANTALLA INICIO //////