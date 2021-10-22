//Hands On Lab - G&S

const int analogInPin = A1;                                     // Asignamos el pin analogico 1
const int led = 6;                                              // Asignamos el pin PWM 6 (PWM~)
int valorsensor = 0;                                            // valor de lectura para el sensor
int intensidad = 0;                                             // Valor pwm de salida 

void setup() {
 Serial.begin(9600);                                            // Inicializamos el monitor serial a 9600 bps
}

void loop() {
 
 valorsensor = analogRead(analogInPin);                         // Leer los valores analogicos
 intensidad = map(valorsensor, 0, 1023, 0, 255);                // Mapeamos y convertimos el rango de valores para la salida
 analogWrite(led, intensidad);                                  // Escribimos el valor analogico de la salida

//visualizamos los valores en el monitor serial:
 Serial.print("sensor = " ); 
 Serial.print(valorsensor);                                     // Imprimimos en el monitor Serial
 Serial.print("\t output = "); 
 Serial.println(intensidad);

 delay(2);                                                      // Espera de 2 milisegundos
}
