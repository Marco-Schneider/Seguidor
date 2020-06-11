//Espera-se introduzir aqui as funções referentes a leitura para indicação de início e término de circuito, bem como indicação de curvas
//Posteriormente, pretende-se implementar mais funções para tratar de maneira incremental de tais informações

void verifica_chegada()//A gente já chegou? Função aplicada ao fim do laço loop que parará o seguidor caso encontre o indicativo de término de percurso
{
  chegada = digitalRead(sensorFim);
  if (chegada == 1 && hasFinished == true) //Primeira faixa indica o início
    hasFinished = false;
  else if (chegada == 1 && hasFinished == false) //Faixa indicando o fim do percurso
    hasFinished = true;

  if (hasFinished == true) //Parar
  {
    delay(500);
    md.dcMotorRun(MOTOR_CHA, 0);
    md.dcMotorRun(MOTOR_CHB, 0);
  }
}
