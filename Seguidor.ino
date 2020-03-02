#include <QTRSensors.h> 

// Criando o objeto para o sensor QTR-8RC
// Não há mais uma distinção de classes entre os sensores QTR-xA e QTR-xRC
QTRSensors qtr;

const uint8_t SensorCount = 8; // Número de sensores
uint16_t sensorValues[SensorCount]; //Array que armazenará as leituras de cada um dos oito sensores

// Variáveis para o PID
// Valores iniciais escolhidos a esmo
const double KP = 0.03;
const double KD = 0.00;
double ultimoErro = 0;
const int objetivoLinha = 3500; // Robô seguir centrado

#define VelocidadeMaxima 255

void setup() {
  calibrar();

}

void loop() {
  // put your main code here, to run repeatedly:

}
