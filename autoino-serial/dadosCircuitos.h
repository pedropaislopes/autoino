#include "circuitos.h"

/********************************************
   Este arquivo tem dados, setup e e parte do loop para circuitos
*/

const int nCircuitos = 5;
Circuito circuitos[nCircuitos];

// Define dados dos circuitos
void defineCircuitos(void)
{
    circuitos[1].pinoSwitch = 5;
    circuitos[1].pinoSensor = A7;
    circuitos[1].sensorDesl = 60;
    circuitos[1].sensorLig = 100;
    circuitos[1].nome = "CI.P";
    circuitos[2].pinoSwitch = 6;
    circuitos[2].pinoSensor = A6;
    circuitos[2].sensorDesl = 60;
    circuitos[2].sensorLig = 100;
    circuitos[2].nome = "CI.M2";
    circuitos[3].pinoSwitch = 7;
    circuitos[3].pinoSensor = A5;
    circuitos[3].sensorDesl = 60;
    circuitos[3].sensorLig = 100;
    circuitos[3].nome = "CI.M4";
    circuitos[4].pinoSwitch = 8;
    circuitos[4].pinoSensor = A4;
    circuitos[4].sensorDesl = 60;
    circuitos[4].sensorLig = 100;
    circuitos[4].nome = "CI.C2";
    circuitos[5].pinoSwitch = 9;
    circuitos[5].pinoSensor = A3;
    circuitos[5].sensorDesl = 60;
    circuitos[5].sensorLig = 100;
    circuitos[5].nome = "CI.C4";
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
