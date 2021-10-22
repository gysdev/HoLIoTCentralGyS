//Hands On Lab - G&S
//Usar resistencia 100k - Pull down --> una resistencia conectada una extremidad a la señal de salida y la otra extremidad a GND

const int ledPin = 6;                                     //puerto digital asignado al LED (este puerto tambien es PWM)
const int ldrPin = A0;                                    //puerto analogico asignado al LDR

void setup() {
  Serial.begin(9600);                                     //Configuracion de la velocidad de transmision de datos del monitor serial, 9600 baudios
  pinMode(ledPin, OUTPUT);                                //Configuracion del LED como puerto de Salida
  pinMode(ldrPin, INPUT);                                 //configuracion del LDR como puerto de Entrada

}

void loop() {
  int ldrStatus = analogRead(ldrPin);
  if (ldrStatus <= 400) {                                 //condicion del estado del LDR
    digitalWrite(ledPin, HIGH);                           //Escribir digitalmente un estado de ENCENDIDO sobre el LED
    Serial.print("Esta Oscuro, Encender el LED : ");      //Imprimir en el monitor serial el texto
    Serial.println(ldrStatus);                            //Imprimir en el monitor seria el valor del LDR
  } 
  
  else {
    digitalWrite(ledPin, LOW);                            //Escribir digitalmente un estado de ENCENDIDO sobre el LED
    Serial.print("Esta Iluminado, Apagar el LED : ");     //Imprimir en el monitor serial el texto
    Serial.println(ldrStatus);                            //Imprimir en el monitor seria el valor del LDR
    }
}
