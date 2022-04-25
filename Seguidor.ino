#include <SparkFun_TB6612.h>
#include <QTRSensors.h>

//Teste 2
// Criando o objeto para o sensor QTR-8RC
// Não há mais uma distinção de classes entre os sensores QTR-xA e QTR-xRC
QTRSensors qtr;

//Criando o objetivo para operação dos motores
//MotorDriver md;

const uint8_t SensorCount = 8; // Número de sensores
uint16_t sensorValues[SensorCount]; //Array que armazenará as leituras de cada um dos oito sensores




//---------DEFINICAO DOS MOTORES---------//
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
//-------------------------------------//

//---------VARIAVEIS AUXILIARES--------//

//PID
const float KP = 0.040;
const float KD = 0.003;
const float KI = 0.000;
float integral = 0;
float ultimoErro = 0;
float objetivoLinha = 3500; //Para o seguidor seguir centrado

int tempoAntes; //Para auxiliar no calculo de intervalos de tempo

int leiturasBorda = 0; //Para computar quantas vezes o sensor detectou a faixa de largada e chegada
//Quando está antes da largada --> leiturasBorda = 0
//Quando o leitor detecta a faixa do circuito --> leiturasBorda = 1 --> Durante todo o trajeto leiturasBorda = 1
//Quando o sensor passar pela linha de chegada --> leiturasBorda = 2

//Variável de indicação de curvas
int curva;
bool isSensorOnCurve = false;

//Sensores de borda
#define sensorCurva 2
#define sensorFim 10
//-------------------------------------//

void setup() {
  Serial.begin(9600);
  calibrar();
  pinMode(sensorCurva, INPUT); //Sensor indicativo de curva
  pinMode(sensorFim, INPUT);  //Sensor indicativo de início término de circuito
  tempoAntes = millis();

}

void loop() {
  //Recalibrando periodicamente para tentar evitar o erro dos extremos
  if (millis() - tempoAntes >= 200)
  {
    qtr.calibrate();
    tempoAntes = millis();
  }
  int position = qtr.readLineWhite(sensorValues);

  Serial.print("Posicao: ");
  Serial.println(position);
  for (int i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print(" | ");
  }
  Serial.println("");

  float correcao = ajuste(position);
  ultimoErro = objetivoLinha - position;

  //PRINT DO ERRO / POSICAO / CORRECAO
  //  Serial.println("---------------");
  //  Serial.print("Erro da linha: ");
  //  Serial.println(ultimoErro);E
  //  Serial.print("Posicao da linha: ");
  //  Serial.println(position);
  //  Serial.print("Valor de correcao: ");
  //  Serial.println(correcao);
  //  delay(1000);
  
  //Aplicando o ajuste de velocidade aos motores
//  motor1.drive(constrain(velocidadeMaxima - correcao, 0, velocidadeMaxima));
//  motor2.drive(constrain(velocidadeMaxima + correcao, 0, velocidadeMaxima));


  //verifica_chegada();

}
