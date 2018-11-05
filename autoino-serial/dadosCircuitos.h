#include "circuitos.h"

/********************************************
   Este arquivo tem dados, setup e e parte do loop para circuitos
*/

const int nCircuitos = 7;
Circuito circuitos[nCircuitos];

// Define dados dos circuitos
void defineCircuitos(void)
{
    circuitos[0].pinoRele = 44;
    circuitos[0].pinoSensor = A15;
    circuitos[0].sensorDesl = 20;
    circuitos[0].sensorLig = 40;
    circuitos[0].nome = "CI.P";
    circuitos[1].pinoRele = 45;
    circuitos[1].pinoSensor = A14;
    circuitos[1].sensorDesl = 20;
    circuitos[1].sensorLig = 40;
    circuitos[1].nome = "CI.M2";
    circuitos[2].pinoRele = 46;
    circuitos[2].pinoSensor = A13;
    circuitos[2].sensorDesl = 20;
    circuitos[2].sensorLig = 40;
    circuitos[2].nome = "CI.M4";
    circuitos[3].pinoRele = 47;
    circuitos[3].pinoSensor = A12;
    circuitos[3].sensorDesl = 20;
    circuitos[3].sensorLig = 40;
    circuitos[3].nome = "CI.C2";
    circuitos[4].pinoRele = 48;
    circuitos[4].pinoSensor = A11;
    circuitos[4].sensorDesl = 20;
    circuitos[4].sensorLig = 40;
    circuitos[4].nome = "CI.C4";
    circuitos[5].pinoRele = 49;
    circuitos[5].pinoSensor = A10;
    circuitos[5].sensorDesl = 20;
    circuitos[5].sensorLig = 40;
    circuitos[5].nome = "CI.Z2";
    circuitos[6].pinoRele = 50;
    circuitos[6].pinoSensor = A9;
    circuitos[6].sensorDesl = 20;
    circuitos[6].sensorLig = 40;
    circuitos[6].nome = "CI.Z4";
}

void setupCircuitos()
{
  defineCircuitos();

  Serial.println("------------------ DADOS DOS CIRCUITOS ------------------");

  // Setando pinos e atualizando status
  for (int i = 0; i < nCircuitos; i++)
  {
    setaPinoCircuito(&circuitos[i]);

    desligaCircuito(&circuitos[i]);

    imprimeDadosCircuito(&circuitos[i], i);
  }

}

void acaoCircuito()
{

  // Realiza ação de acordo com mensagem recebida
  if (integerFromPC >= 0 && integerFromPC < nCircuitos)
  {

    if (messageFromPC[0] == 'l')
    {
      ligaCircuito(&circuitos[integerFromPC]);
    }

    if (messageFromPC[0] == 'd')
    {
      desligaCircuito(&circuitos[integerFromPC]);
    }

    if (messageFromPC[0] == 's')
    {
      Serial.println("------------------ DADOS DOS CIRCUITOS ------------------");
      for (int i = 0; i < nCircuitos; i++)
      {
        imprimeDadosCircuito(&circuitos[i], i);
      }
    }

  }
}
