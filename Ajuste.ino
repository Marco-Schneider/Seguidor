//Calculando o ajuste do motor

double ajuste (unsigned int position)
{
  int erro  = objetivoLinha - position;

  integral = integral + erro;
  
  double  ajuste = 1*(KP*erro + KD*(ultimoErro - erro) + KI*integral);

  return  ajuste;
}
