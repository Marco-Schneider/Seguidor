//Calculando o ajuste do motor

int ajuste (unsigned int position)
{
  int erro  = objetivoLinha - position;
  
  int ajuste = KP*erro + KD*(ultimoErro - erro);

  return ajuste;
}
