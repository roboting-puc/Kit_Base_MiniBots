//===============================
//Pines

//Buzzer
const int buzzPin = 4;

//Motores
const int ADirPin = 12;
const int pwmA = 10;

const int BDirPin = 13;
const int pwmB = 11;


//===============================
//Variables globales

const int VELOCIDAD_RUEDAS = 255;

//Bluetooth
#define CONECTION_DELAY 750

unsigned long time_now=0, last_check=0;
bool active = false;

//===============================
//Funciones Auxiliares

void avanzar(){
  //Velocidad motores
  analogWrite(pwmA, VELOCIDAD_RUEDAS);
  analogWrite(pwmB, VELOCIDAD_RUEDAS);

  //Rueda izquiera - Adelante
  //Rueda derecha - Adelante
  digitalWrite(ADirPin, HIGH);
  digitalWrite(BDirPin, HIGH);
}

void retroceder(){
  //Velocidad motores
  analogWrite(pwmA, VELOCIDAD_RUEDAS);
  analogWrite(pwmB, VELOCIDAD_RUEDAS);

  //Rueda izquiera - Atras
  //Rueda derecha - Atras
  digitalWrite(ADirPin, LOW);
  digitalWrite(BDirPin, LOW);
}

void girar_derecha(){
  //Velocidad motores
  analogWrite(pwmA, VELOCIDAD_RUEDAS);
  analogWrite(pwmB, VELOCIDAD_RUEDAS);

  //Rueda izquiera - Adelante
  //Rueda derecha - Atras
  digitalWrite(ADirPin, HIGH);
  digitalWrite(BDirPin, LOW);
}

void girar_izquierda(){
  //Velocidad motores
  analogWrite(pwmA, VELOCIDAD_RUEDAS);
  analogWrite(pwmB, VELOCIDAD_RUEDAS);

  //Rueda izquiera - Atras
  //Rueda derecha - Adelante
  digitalWrite(ADirPin, LOW);
  digitalWrite(BDirPin, HIGH);
}

void detener_motores(){
  //Velocidad motores en 0
  analogWrite(pwmA, 0);
  analogWrite(pwmB, 0);
}

//-----------------------------------
//Bluetooth

void manejar_comando(char letter){
  //STOP
  if(letter == 'S'){
      detener_motores();
      return;
  }

  active = true;
  switch (letter)
  {
  case 'F':
      avanzar();
      break;
    case 'B':
      retroceder();
      break;
    case 'L':
      girar_izquierda();
      break;
    case 'R':
      girar_derecha();
      break;
  //------------------------
  default:
      break;
  }
}


void manejar_conexion(){
  if(active && (time_now-last_check) > CONECTION_DELAY){
    detener_motores();
    active = false;
  }
}

//===============================
//Programa principal


void setup() {
  Serial.begin(9600);

  //Inicializar todo
  pinMode(buzzPin, OUTPUT);

  pinMode(ADirPin, OUTPUT);
  pinMode(pwmA, OUTPUT);

  pinMode(BDirPin, OUTPUT);
  pinMode(pwmB, OUTPUT);

  //Posicion inicial
  detener_motores();

  analogWrite(buzzPin, 128);
  delay(100);
  analogWrite(buzzPin, 0);
}


void loop(){
  time_now = millis();

  while(Serial.available()){
    last_check = time_now;
    manejar_comando(Serial.read());
  }

  //Chequear si bluetooth perdio conexion
  manejar_conexion();
}
