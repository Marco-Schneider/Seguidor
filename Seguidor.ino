#include <SoftwareSerial.h>
#include <SparkFun_TB6612.h>
#include <Wire.h>
#include <QTRSensors.h> 

//Teste 2
// Criando o objeto para o sensor QTR-8RC
// Não há mais uma distinção de classes entre os sensores QTR-xA e QTR-xRC
QTRSensors qtr;

//Criando o objetivo para operação dos motores
//MotorDriver md;

const uint8_t SensorCount = 8; // Número de sensores
uint16_t sensorValues[SensorCount]; //Array que armazenará as leituras de cada um dos oito sensores

// Variáveis para o PID
// Valores iniciais escolhidos a esmo
const float KP = 0.50;
const float KD = 0.002;
const float KI = 0.00;
float integral = 0;
float ultimoErro = 0;
float objetivoLinha = 3500; // Robô seguir centrado
int tempoAntes;
float soma = 0;
float somaAntes = 0;
float somatorio = 0;
int n = 0; //Quantidade de iterações do sensor

//Variável de indicação de início/término de circuito
int chegada;
bool hasFinished = true;

//Variável de indicação de curvas
int curva;
bool isSensorOnCurve = false;

//Sensores de borda
#define sensorCurva 2
#define sensorFim 10

#define VelocidadeMaxima 35

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

void setup() {
  Serial.begin(9600);
  calibrar();
  pinMode(sensorCurva, INPUT); //Sensor indicativo de curva
  pinMode(sensorFim, INPUT);  //Sensor indicativo de início término de circuito
  tempoAntes = millis();
}

void loop() {
  //Adquirindo a posição da linha sob o robô
  unsigned int position = qtr.readLineWhite(sensorValues); // Notar que sensorValues é um array de 8 elementos indicativo de cada sensor infravermelho
  float correcao = 0;
  float media = 0;
  
  if(millis() - tempoAntes >= 1000)
  {
    correcao = ajuste(soma/n);
    tempoAntes = millis();
    
    
    Serial.println(soma/n);
    soma = 0;
    n = 0;
  }
  else
  {
    if((abs(3500 - position)) > 200){
      soma = position;
      //somatorio = somaAntes + soma;
      //media = somatorio / (n + 1);
      n = n + 1;
      //somaAntes = somatorio;  
    }
    
  }

  
  //Computando o último erro
  ultimoErro = objetivoLinha - position;
  //Serial.println("---------------");
  //Serial.print("Erro da linha: ");
  //Serial.println(ultimoErro);
  //Serial.print("Posicao da linha: ");
  //Serial.println(position);
  //Serial.print("Valor de correcao: ");
  //Serial.println(correcao);

  //Aplicando o ajuste de velocidade aos motores
  motor1.drive(constrain(45 + correcao, -0.25*VelocidadeMaxima, VelocidadeMaxima));
  motor2.drive(constrain(45 - correcao, -0.25*VelocidadeMaxima, VelocidadeMaxima));
  //Serial.print("Velocidade1 = ");
  //Serial.println(constrain(VelocidadeMaxima - correcao,-0.25*VelocidadeMaxima, VelocidadeMaxima));
  //Serial.print("Velocidade2 = ");
  //Serial.println(constrain(VelocidadeMaxima + correcao, -0.25*VelocidadeMaxima, VelocidadeMaxima));
  //Serial.println("---------------");

  verifica_chegada();

}
