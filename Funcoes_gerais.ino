//Espera-se introduzir aqui as funções referentes a leitura para indicação de início e término de circuito, bem como indicação de curvas
//Posteriormente, pretende-se implementar mais funções para tratar de maneira incremental de tais informações

void verifica_chegada()//A gente já chegou? Função aplicada ao fim do laço loop que parará o seguidor caso encontre o indicativo de término de percurso
{

  if (leiturasBorda == 2)
  {
    delay(100);
    motor1.drive(0);
    motor2.drive(0);
    delay(10000);

  }
  /*Apenas para testar
    if(millis() - tempoInicio >= 1000*10) //Caso se tenha passado cinco segundos desde o início do percurso o robô deve parar
    {
    motor1.drive(0);
    motor2.drive(0);
    Serial.println("Fim - Se passaram 10 segundos desde a calibracao");
    delay(10*1000);


    }*/
  /*chegada = digitalRead(sensorFim);
    if (chegada == 1 && hasFinished == true) //Primeira faixa indica o início
    hasFinished = false;
    else if (chegada == 1 && hasFinished == false) //Faixa indicando o fim do percurso
    hasFinished = true;

    if (hasFinished == true) //Parar
    {
    delay(500);
    motor1.drive(0);
    motor2.drive(0);
    delay(1000*15);
    }*/
}
