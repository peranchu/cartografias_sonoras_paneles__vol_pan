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
"config.h"
Configuración Comunicaciones
SSID: PERANCHU
PASS: TexucaLana72
Ip 192.168.1.201
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>


const char *ssid = "PERANCHU";
const char *password = "TexucaLana72";

const IPAddress ip(192, 168, 1, 201);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);

const IPAddress outIP(192, 168, 1, 100);  // IP Ordenador que recibe los datos
const unsigned int outPort = 9999;
const unsigned int localPort = 8888;