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
"esp32Utils.h"
Configuración Conexión WiFi
*/
#include <Arduino.h>
#include "config.h"

WiFiUDP Udp;

// Prototipo Función
void PantallaConexion(String);

const char *estado[3] = {"conectado", "desconectado", "conectado"}; // Estados conexión

// Funciín Inicia Conexion WiFi
void ConexionWiFi()
{
    Serial.println("");

    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.config(ip, gateway, subnet);
    WiFi.begin(ssid, password);

    Serial.print("iniciado Conexion:\t");
    Serial.println(ssid);

    PantallaConexion(estado[1]); // Pinta en Pantalla el estado de la conexión "pantalla.h"

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    PantallaConexion(estado[2]);

    Serial.println("Conexion establecida");
    Serial.print("IP Address:\t");
    Serial.println(WiFi.localIP());

    // Inicio UDP
    Serial.println("Iniciando UDP...");
    Udp.begin(localPort);
    Serial.print("localPort: ");
    Serial.println(localPort);

    delay(5000);
}
////// FIN CONEXIÓN WIFI ////////////////

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