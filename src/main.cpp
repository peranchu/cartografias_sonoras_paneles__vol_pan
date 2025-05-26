#include <Arduino.h>
#include "potes.h"
#include "pantalla.h"

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

  lcd.createChar(0, gauge_left);    // create special character on position 0, gauge left    [ 
  lcd.createChar(1, gauge_center);  // create special character on position 1, gauge center  _
  lcd.createChar(2, gauge_right);   // create special character on position 2, gauge right   ]
  lcd.createChar(3, gauge_fill);    // create special character on position 3, gauge fill    █
  lcd.backlight();                 // enable backlight for the LCD module
  delay(100);

 
  resposivePot_vol = ResponsiveAnalogRead(PotVolumen, true, snapMultipler);
  resposivePot_pan = ResponsiveAnalogRead(PotPano, true, snapMultipler);
}

void loop()
{
  //Lectura Potenciometros
  Lectura_poteVol();

  Lectura_potePan();

  dibujoPantalla(valPotes_scale_vol, valPotes_scale_pan);
}
