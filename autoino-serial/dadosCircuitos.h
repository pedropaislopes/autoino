#include "circuitos.h"

/********************************************
   Este arquivo tem dados, setup e e parte do loop para circuitos
*/

const int nCircuitos = 5;
Circuito circuitos[nCircuitos];

// Define dados dos circuitos
void defineCircuitos(void)
{
    circuitos[0].pinoSwitch = 9;
    circuitos[0].pinoSensor = A7;
    circuitos[0].sensorDesl = 20;
    circuitos[0].sensorLig = 40;
    circuitos[0].nome = "CI.P";
    circuitos[1].pinoSwitch = 8;
    circuitos[1].pinoSensor = A6;
    circuitos[1].sensorDesl = 20;
    circuitos[1].sensorLig = 40;
    circuitos[1].nome = "CI.M2";
    circuitos[2].pinoSwitch = 7;
    circuitos[2].pinoSensor = A5;
    circuitos[2].sensorDesl = 20;
    circuitos[2].sensorLig = 40;
    circuitos[2].nome = "CI.M4";
    circuitos[3].pinoSwitch = 6;
    circuitos[3].pinoSensor = A4;
    circuitos[3].sensorDesl = 20;
    circuitos[3].sensorLig = 40;
    circuitos[3].nome = "CI.C2";
    circuitos[4].pinoSwitch = 5;
    circuitos[4].pinoSensor = A3;
    circuitos[4].sensorDesl = 20;
    circuitos[4].sensorLig = 40;
    circuitos[4].nome = "CI.C4";
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
