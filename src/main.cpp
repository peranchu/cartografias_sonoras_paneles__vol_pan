/*
              _ _______
    /\        | |__   __|
   /  \   _ __| |_ | | ___  ___
  / /\ \ | '__| __|| |/ _ \/ __|
 / ____ \| |  | |_ | |  __/ (__
/_/    \_\_|   \__||_|\___|\___|

CARTOGRAFÍAS SONORAS
Honorino García Mayo 2025

Panel Control VOLUME - PANORAMIC
*/

#include <Arduino.h>
#include "pantalla.h"
#include "potes.h"

void setup()
{
  Serial.begin(115200);
  delay(100);

  analogReadResolution(10);
  delay(100);

  lcd.init(); // initialize the 16x2 lcd module
  lcd.backlight();

  Pantalla_inicio();

  lcd.clear();
  delay(100);

  ConexionWiFi(); // Inicia La comunicación WiFi

  lcd.clear();
  delay(100);

  // Caracteres fijos pantalla
  lcd.createChar(0, gauge_left);   // create special character on position 0, gauge left    [
  lcd.createChar(1, gauge_center); // create special character on position 1, gauge center  _
  lcd.createChar(2, gauge_right);  // create special character on position 2, gauge right   ]
  lcd.createChar(3, gauge_fill);   // create special character on position 3, gauge fill    █
  lcd.backlight();                 // enable backlight for the LCD module
  delay(100);

  // suabizado Lecturas
  resposivePot_vol = ResponsiveAnalogRead(PotVolumen, true, snapMultipler);
  resposivePot_pan = ResponsiveAnalogRead(PotPano, true, snapMultipler);
}

void loop()
{
  //Si existe conexión
  if (conexion)
  {
    // Lectura Potenciometros
    Lectura_poteVol();

    Lectura_potePan();

    dibujoPantalla(valPotes_scale_vol, valPotes_scale_pan);
  }
}

/*
  _____           _                         __ _              _____
 / ____|         | |                       / _(_)            / ____|
| |     __ _ _ __| |_ ___   __ _ _ __ __ _| |_ _  __ _ ___  | (___   ___  _ __   ___  _ __ __ _ ___
| |    / _` | '__| __/ _ \ / _` | '__/ _` |  _| |/ _` / __|  \___ \ / _ \| '_ \ / _ \| '__/ _` / __|
| |___| (_| | |  | || (_) | (_| | | | (_| | | | | (_| \__ \  ____) | (_) | | | | (_) | | | (_| \__ \
 \_____\__,_|_|   \__\___/ \__, |_|  \__,_|_| |_|\__,_|___/ |_____/ \___/|_| |_|\___/|_|  \__,_|___/
                            __/ |
                           |___/

 Honorino García Mayo 2025
*/
