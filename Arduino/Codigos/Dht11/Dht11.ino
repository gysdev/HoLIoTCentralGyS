//Hands On Lab - G&S

#include "DHT.h"                                            // Incluir la libreria DHT
#define DHTPIN 9                                            // Pin donde está conectado el sensor
#define DHTTYPE DHT11                                       // Sensor DHT 11
//#define DHTTYPE DHT22                                     // Sensor DHT22

DHT dht(DHTPIN, DHTTYPE);                                   // Indicar el pin y tipo de DHT usados

void setup() {
  Serial.begin(9600);                                       //Iniciailzamos la comunicación serial a 9600 baudios
  dht.begin();                                              //Inicializamos la cominucacion con DHT
}
void loop() {
  delay(2000);
  float h = dht.readHumidity();                             // Leemos el valor de la Humedad
  float t = dht.readTemperature();                          // Leemos el valor de la temperatura en grados Celsius
  float f = dht.readTemperature(true);                      // Leemos el valor de la temperatura en grados Fahrenheit

  Serial.print("Humedad ");
  Serial.print(h);
  Serial.print(" %t");
  Serial.print(" || Temperatura: ");                        // Imprimimos en el monitor Serial
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.println(" *F");
}
