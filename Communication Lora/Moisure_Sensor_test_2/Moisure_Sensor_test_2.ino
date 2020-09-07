#include <WiFi.h>  // Utilisation de la librairie WiFi.h
#include <WiFiMulti.h>
#include <Arduino.h>
#include <HTTPClient.h>
#include "gravity_soil_moisture_sensor.h"

#define USE_SERIAL Serial
#define moisturePIN 15
#define moistureTYPE "gravity_soil_moisture_sensor.h"

GravitySoilMoistureSensor gravity_sensor;
WiFiMulti wifiMulti;

const char* ssid = "POP_SENSORS";  // Mettre votre SSID Wifi
const char* password = "P0PS3NS0RS!";  // Mettre votre mot de passe Wifi

int PinLed=2;


void setup() {

  pinMode(PinLed,OUTPUT);
  Serial.begin(115200);
    uint8_t pin = 15;

    if (!gravity_sensor.Setup(pin)) {
        Serial.println("Le capteur d'humidité au sol n'a pas été détecté.");
        while(1);
    } else {
        Serial.println("Le capteur d'humidité au sol est opérationnel !");
    }
Serial.println("\n");
  WiFi.begin(ssid,password);  // Initialisation avec WiFi.begin / ssid et password
  Serial.print("Attente de connexion ...");  // Message d'attente de connexion
  while(WiFi.status() != WL_CONNECTED)  // Test connexion
{Serial.print(".");  // Affiche des points .... tant que connexion n'est pas OK
delay(100);}
  Serial.println("\n");
  Serial.println("Connexion établie !");  // Affiche connexion établie

}


void loop() {

 uint16_t value = gravity_sensor.Read(15);
int a = 40.95;
int b = 100;
float sensorConvert = value / a;
float sensorConvert1 = b - sensorConvert;
Serial.printf("Valeur de l'entrée analogique du capteur : %d\n", value);
Serial.print("Ce qui donne ");
Serial.print(sensorConvert1);
Serial.println("% d'humidité.");
if (sensorConvert1 < 35) {digitalWrite(PinLed,HIGH);}
else {digitalWrite(PinLed,LOW);}

int h = sensorConvert1


if ((wifiMulti.run() == WL_CONNECTED)) { // Si c'est connecté, ça fait ce qu'il y a en dessous
    HTTPClient http; // va créer un objet qui s'appelle HTTPClient qui va permettre de lancer des requêtes en HTTP
    USE_SERIAL.println("[DEBG] " + String(h));

    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
    http.begin("http://node03.popschool-willems.fr/#flow/b7090afb.bd8ce/H/" + String(h)); //HTTP => démarre connexion vers le serveur mentionné

    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET(); // soumet une requête de type "get", puis récupère résultat qui sera collée dans HTTP

    // httpCode will be negative on error
    if (httpCode > 0) { // si c'est supérieur à 0, il refait un test)
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) { // Si ça s'est bien passé, il refait une variable où il met le getString puis affiche à l'écran => on a reçu un code 200
        String payload = http.getString();
        USE_SERIAL.println(payload);
        if (payload == "ON") {
          digitalWrite(4, HIGH);
        }
        if (payload == "OFF") {
          digitalWrite(4, LOW);
        }
      }
    } else { // sinon, il dit que ça ne fonctionne pas
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();    }

    delay(5000);
}

void montrerValeurCapteur()
{
    valeurCapteur = analogRead(pin); // lire la pin analogique et mettre la valeur dans valeurCapteur
    Serial.println(valeurCapteur); // communiquer au moniteur sériel la valeur du capteur.
}