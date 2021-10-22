//Hands On Lab - G&S

const int Trigger = 10;               //Asignamos el pin digital 10 para el Trigger del sensor
const int Echo = 11;                  //Asignamos el pin digital 11 para el Echo del sensor

void setup() {
  Serial.begin(9600);                 //Iniciailzamos la comunicación serial a 9600 baudios
  pinMode(Trigger, OUTPUT);           //pin configurado en modo Salida
  pinMode(Echo, INPUT);               //Pin configurado en modo Entrada
  digitalWrite(Trigger, LOW);         //Inicializamos el pin con 0
}

void loop(){
  long t;                             //Variable de timepo que demora en llegar el eco
  long d;                             //Variable de distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);              //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH);            //obtenemos el ancho del pulso
  d = t/59;                           //escalamos el tiempo a una distancia en cm
  
  Serial.print("Distancia: ");
  Serial.print(d);                    //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  delay(100);                         //Hacemos una pausa de 100ms
}
