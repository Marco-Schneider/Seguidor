#include <SparkFun_TB6612.h>
#include <SerialBluetooth
#include <QTRSensors.h>

//---------DEFINIÇÃO DO ARRAY DE SENSORES---------//
QTRSensors qtr;

const uint8_t SensorCount = 8; 
uint16_t sensorValues[SensorCount];

//------------------------------------------------//

//---------DEFINIÇÃO DOS MOTORES-----------------//
#define velocidadeMaxima 120

//Ponte H
#define AIN1 5
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 3
#define PWMB 9
#define STBY 6

//Offset
const int offsetA = 1;
const int offsetB = 1;

//Motor esquerdo
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

//Motor direito
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
//-----------------------------------------------//

//PID------
const float KP = 0.0040;
const float KD = 0.0003;
const float KI = 0.000;
float integral = 0;
float ultimoErro = 0;
float objetivoLinha = 2350;
//---------

//Variáveis auxiliares
float soma = 0;
float media = 0;
float tempoAntes = 0;
float limiteInferior = 0;
float limiteSuperior = 0;


void setup() {
  Serial.begin(9600);
  calibrateSensors();

  tempoAntes = millis();

}

void loop() {
//  if (millis() - tempoAntes >= 500)
//  {
//    qtr.calibrate();
//    tempoAntes = millis();
//  }

  float position = qtr.readLineWhite(sensorValues);

  //PRINT DA POSICAO
  /*
  Serial.print("Posicao: ");
  Serial.println(position);
  for (int i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print(" | ");
  }
  Serial.println("");
  */

  float limite = (limiteSuperior - limiteInferior)/2;
  float novaPosicaoLinha = map(position - limiteInferior - (limite), limiteInferior, limiteSuperior,0,10);
  //PRINT DA NOVA POSICAO LIDA
  Serial.println(position - limiteInferior - (limite));
//  Serial.print("Posicao nova: ");
  Serial.println(novaPosicaoLinha);

  if (abs(position) > 200){
    digitalWrite(LED_BUILTIN, HIGH);
  }else{
    digitalWrite(LED_BUILTIN, LOW);
  }

  float correcao = calculatePID(novaPosicaoLinha/125);
  ultimoErro = novaPosicaoLinha/125;
  Serial.println("---------------");
  Serial.print("Erro da linha: ");
  Serial.println(ultimoErro);
  Serial.print("Posicao da linha (nova): ");
  Serial.println(novaPosicaoLinha);
  Serial.print("Valor de correcao: ");
  Serial.println(correcao);
  float speed = 0;
  if(180 + abs(correcao)/2 > 255) speed = velocidadeMaxima - abs(correcao)/2;
  motor1.drive(velocidadeMaxima - speed);
  motor2.drive(velocidadeMaxima + speed);
  
  Serial.print("Velocidade esquerdo: ");
  Serial.println(constrain(velocidadeMaxima + correcao, 0, velocidadeMaxima));
  //motor1.drive();
  
  Serial.print("Velocidade direito: ");
  Serial.println(constrain(velocidadeMaxima - correcao, 0, velocidadeMaxima));
  //motor2.drive(constrain(velocidadeMaxima - correcao, 0, velocidadeMaxima));
  delay(50);
  
  

}
