//Hands On Lab - G&S
//Proyecto IoTCentral

#include <Servo.h>                                        // Incluimos la libreria Servo
const int trigPin = 10;                                   // Asignamos el pin digital 10 para el Trigger del sensor
const int echoPin = 11;                                   // Asignamos el pin digital 11 para el Echo del sensor
long duration;                                            // Creamos la variable "duration"
int distance;                                             // Creamos la variable "distancia"
Servo myServo;                                            // Declaramos la variable para llamar al servo
int i;

//DHT11
#include "DHT.h"
#define DHTPIN 9                                          // Pin donde está conectado el sensor
#define DHTTYPE DHT11                                     // Descomentar si se usa el DHT 11
DHT dht(DHTPIN, DHTTYPE);                                 // Indicar el pin y tipo de DHT usados
float dht_h;                                              // Leemos el valor de la Humedad
float dht_t;                                              // Leemos el valor de la temperatura en grados Celsius
float dht_f;                                              // Leemos el valor de la temperatura en grados Fahrenheit

//Potenciometro
const int analogInPin = A1;                               // Asignamos el pin analogico 1
const int led = 6;                                        // Asignamos el pin PWM 6 (~)
int valorsensor = 0;                                      // Valor de lectura para el sensor
int intensidad = 0;                                       // Valor pwm de salida 

//LDR
const int ledPin = 6;                                     // Puerto asigado al led
const int ldrPin = A0;                                    // Puerto asignado al LDR
int ldrStatus;

//toazure
String dataDeEnvio;                                       // Cadena para comunicacion serial a python


void setup() {
  //Ultrasonido
  pinMode(trigPin, OUTPUT);                               // Pin configurado en modo Salida
  pinMode(echoPin, INPUT);                                // Pin configurado en modo Entrada

  //Servomotor
  Serial.begin(9600);                                     // Iniciailzamos la comunicación serial a 9600 baudios
  myServo.attach(12);                                     // asignamos el puerto al servo

  //DHT11
  dht.begin();                                            //Inicializamos la cominucacion con DHT

  //LDR
  pinMode(ledPin, OUTPUT);                                // Pin configurado en modo Salida
  pinMode(ldrPin, INPUT);                                 // Pin configurado en modo Entrada
}


void loop() {
 servom();                                                // Inicializamos la funcion servom()
}

void executeReadData()                                    // Creamos la funcion 
{
 dht11();                                                 // inicializamos las funciones:
 potenciometro();
 lightSensor();                                           
 toazure();
}
void servom(){                                            // Creamos la funcion
  for(i=60;i<=90;i++){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();

  executeReadData();                                      // Inicializamos la funcion
  }
  for(i=90;i>60;i--){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();

  executeReadData();                                      // Inicializamos la funcion
  }
}
int calculateDistance(){                                  // Creamos la funcion para el calculo de la distancia
  digitalWrite(trigPin, LOW);                             // Apagado de envio señal trig para limpieza de repector echo
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);                            // Encendido de envio señal trig
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);                             // Apagado de envio señal trig
  duration = pulseIn(echoPin, HIGH);                      // Recepcion de señal por el echo
  distance= duration*0.034/2;                             // Calculo de la distancia en base a la velocidad del sonido
  return distance;                                        // Retornamos el valor de la distancia para la visualizacion en el monitoring
}

void dht11(){                                             // Creamos la funcion para el DHT11
  delay(100);
  dht_h = dht.readHumidity();                             //Leemos la Humedad
  dht_t = dht.readTemperature();                          //Leemos la temperatura en grados Celsius
  dht_f = dht.readTemperature(true);                      //Leemos la temperatura en grados Fahrenheit
}

void potenciometro(){                                     // Creamos la funcion para el Potenciometro
  valorsensor = analogRead(analogInPin);                  // leer los valores analogicos
  intensidad = map(valorsensor, 0, 1023, 0, 255);         // mapeamos y convertimos el rango de valores para la salida
  analogWrite(led, intensidad);                           // escribimos el valor analogico de la salida
  delay(2);                                               // esperamos 2 milisegundos
}

void lightSensor(){                                       // Creamos la funcion para el LDR
  ldrStatus = analogRead(ldrPin);                         // Leemos el valor
  if (ldrStatus <= 600) {                                 // Condicionamos el encendido del LED
    analogWrite(ledPin, intensidad);                      // El LED se enciende con la intencidad generada por el poteciometro
    }
    
  else {
    analogWrite(ledPin, 0);                               // Apagamos el LED
    }
}

void toazure(){                                           // Creamos la funcion para el ToAzure
  // creamos la cadena de informacion que será enviada por serial a python y desde ahi hacia AZURE IOT CENTRAL
  dataDeEnvio = "U"+String(distance)+"|"+"T"+String(dht_t)+"|"+"H"+String(dht_h)+"|"+"L"+String(ldrStatus)+"|"+"P"+String(intensidad)+"|"+"S"+String(i)+"?";  
  Serial.println(dataDeEnvio);                            // Envio de dator por el Serial
}
