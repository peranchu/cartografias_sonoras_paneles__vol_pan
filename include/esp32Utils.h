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

//Prototipo Función
void PantallaConexion(String);

const char *estado[3] = {"conectado", "desconectado", "conectado"};

void ConexionWiFi(){
    Serial.println("");

    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.config(ip, gateway, subnet);
    WiFi.begin(ssid, password);

    Serial.print("iniciado Conexion:\t");
    Serial.println(ssid);

    PantallaConexion(estado[1]);   // "pantalla.h"

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    PantallaConexion(estado[2]);

    Serial.println("Conexion establecida");
    Serial.print("IP Address:\t");
    Serial.println(WiFi.localIP());

    //Inicio UDP
    Serial.println("Iniciando UDP...");
    Udp.begin(localPort);
    Serial.print("localPort: ");
    Serial.println(localPort);

    delay(5000);
}