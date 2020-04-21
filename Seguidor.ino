#include "Grove_Motor_Driver_TB6612FNG.h"
#include <Wire.h>
#include <QTRSensors.h> 

// Criando o objeto para o sensor QTR-8RC
// Não há mais uma distinção de classes entre os sensores QTR-xA e QTR-xRC
QTRSensors qtr;

//Criando o objetivo para operação dos motores
MotorDriver md;

const uint8_t SensorCount = 8; // Número de sensores
uint16_t sensorValues[SensorCount]; //Array que armazenará as leituras de cada um dos oito sensores

// Variáveis para o PID
// Valores iniciais escolhidos a esmo
const double KP = 0.03;
const double KD = 0.00;
double ultimoErro = 0;
const int objetivoLinha = 3500; // Robô seguir centrado

//Variável de indicação de início/término de circuito
bool hasFinished = false;

//Variável de indicação de curvas
bool isSensorOnCurve = false;

#define sensorCurva 11
#define sensorFim 12
#define VelocidadeMaxima 255

void setup() {
  calibrar();
  pinMode(sensorCurva, INPUT); //Sensor indicativo de curva
  pinMode(sensorFim, INPUT);  //Sensor indicativo de início término de circuito
}

void loop() {
  //Adquirindo a posição da linha sob o robô
  unsigned int position = qtr.readLineWhite(sensorValues); // Notar que sensorValues é um array de 8 elementos indicativo de cada sensor infravermelho
  int correcao = ajuste(position);

  //Computando o último erro
  ultimoErro = objetivoLinha - position;

  //Aplicando o ajuste de velocidade aos motores
  md.dcMotorRun(MOTOR_CHA, constrain(VelocidadeMaxima - correcao, 0, VelocidadeMaxima));
  md.dcMotorRun(MOTOR_CHB, constrain(VelocidadeMaxima + correcao, 0, VelocidadeMaxima));

  if(sensorValues[2]>=500 && sensorValues[5]>=500) //Encuzilhada
  {
    //Avançar
    md.dcMotorRun(MOTOR_CHA, VelocidadeMaxima);
    md.dcMotorRun(MOTOR_CHB, VelocidadeMaxima);
  }

}
