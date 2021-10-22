/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
long randNumber;
String dataDeEnvio; 
// the setup routine runs once when you press reset:
const int Trigger = 10;               //Asignamos el pin digital 10 para el Trigger del sensor
const int Echo = 11;                  //Asignamos el pin digital 11 para el Echo del sensor

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  long t;                             //Variable de timepo que demora en llegar el eco
  long d;                             //Variable de distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);              //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH);            //obtenemos el ancho del pulso
  d = t/59;                           //escalamos el tiempo a una distancia en cm
  
  randNumber = random(0, 1200);
  // print out the value you read:
  dataDeEnvio = "U"+String(d)+"|"+"T"+String(random(0, 1200))+"|"+"H"+String(random(0, 1200))+"|"+"L"+String(random(0, 1200))+"|"+"P"+String(random(0, 1200))+"|"+"S"+String(random(0, 1200))+"?";
  Serial.println(dataDeEnvio);
  delay(4000);  // delay in between reads for stability
}
