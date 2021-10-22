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
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int pinA0 = analogRead(A1);
  randNumber = random(0, 1200);
  // print out the value you read:
  dataDeEnvio = "U"+String(pinA0)+"|"+"T"+String(random(0, 1200))+"|"+"H"+String(random(0, 1200))+"|"+"L"+String(random(0, 1200))+"|"+"P"+String(random(0, 1200))+"|"+"S"+String(random(0, 1200))+"?";
  Serial.println(dataDeEnvio);
  delay(4000);  // delay in between reads for stability
}
