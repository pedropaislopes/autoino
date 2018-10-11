#include "circuitos.h"

/********************************************
   Este arquivo tem dados, setup e e parte do loop para circuitos
*/

const int nCircuitos = 1;
Circuito circuitos[nCircuitos];

// Define dados dos circuitos
void defineCircuitos(void)
{
    circuitos[0].pinoSwitch = 4;
    circuitos[0].pinoSensor = A1;
    circuitos[0].sensorDesl = 10;
    circuitos[0].sensorLig = 100;
    circuitos[0].nome = "LED_vermelho";
  /*
    circuitos[1].pinoSwitch = 4;
    circuitos[1].pinoSensor = -1;
    circuitos[1].sensorDesl = 10;
    circuitos[1].sensorLig = 1000;
    circuitos[1].nome = "LED_verde";
    circuitos[2].pinoSwitch = 5;
    circuitos[2].pinoSensor = -1;
    circuitos[2].sensorDesl = 10;
    circuitos[2].sensorLig = 1000;
    circuitos[2].nome = "LED_amarelo";
    circuitos[3].pinoSwitch = 8;
    circuitos[3].pinoSensor = A4;
    circuitos[3].sensorDesl = 60;
    circuitos[3].sensorLig = 120;
    circuitos[3].nome = "lamp_teste";
    circuitos[4].pinoSwitch = 4;
    circuitos[4].pinoSensor = -1;
    circuitos[4].sensorDesl = 10;
    circuitos[4].sensorLig = 1000;
    circuitos[4].nome = "LED_verde";
    circuitos[5].pinoSwitch = 4;
    circuitos[5].pinoSensor = -1;
    circuitos[5].sensorDesl = 10;
    circuitos[5].sensorLig = 1000;
    circuitos[5].nome = "LED_verde";
    circuitos[6].pinoSwitch = 4;
    circuitos[6].pinoSensor = -1;
    circuitos[6].sensorDesl = 10;
    circuitos[6].sensorLig = 1000;
    circuitos[6].nome = "LED_verde";
    circuitos[7].pinoSwitch = 4;
    circuitos[7].pinoSensor = -1;
    circuitos[7].sensorDesl = 10;
    circuitos[7].sensorLig = 1000;
    circuitos[7].nome = "LED_verde";
  */
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
