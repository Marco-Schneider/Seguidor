//Calculando o ajuste do motor

int ajuste (unsigned int position)
{
  int erro  = objetivoLinha - position;

  integral = integral + erro;
  
  int ajuste = KP*erro + KD*(ultimoErro - erro) + KI*integral;

  return ajuste;
}
