//Calculando o ajuste do motor

double ajuste (unsigned int position)
{
  int erro  = objetivoLinha - position;

  integral = integral + erro;
  
  double  ajuste = KP*erro + KD*(ultimoErro - erro) + KI*integral;

  return  ajuste;
}
