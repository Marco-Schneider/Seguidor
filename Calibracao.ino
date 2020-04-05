#include <QTRSensors.h> 

void calibrar()
{
  // Configurando o sensor para a calibração
  qtr.setTypeRC(); // Visto que o sensor é o QTR-8RC
  qtr.setSensorPins((const uint8_t[]){A05, A1, A2, A3, A4, A5, A6, A7}, SensorCount); // void QTRSensors::setSensorPins(const uint8_t *pins,uint8_t sensorCount)
  qtr.setTimeout(1000);

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // Liga o LED do Arduino para indicar que a clibração está em andamento

  // Calibração durará cerca de 10 segundos
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW); // Desliga o LED do Arduino para indicar que a clibração foi finalizada 
}
