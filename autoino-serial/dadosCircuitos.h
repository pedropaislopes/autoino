#include "circuitos.h"

/********************************************
   Este arquivo tem dados, setup e e parte do loop para circuitos
*/

const int nCircuitos = 0;
int statusAntesCircuitos[nCircuitos];
Circuito circuitos[nCircuitos];

// Define dados dos circuitos
void defineCircuitos(void)
{
  /*
    circuitos[0].pinoSwitch = 3;
    circuitos[0].pinoSensor = -1;
    circuitos[0].sensorDesl = 10;
    circuitos[0].sensorLig = 1000;
    circuitos[0].nome = "LED_vermelho";
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

  // Setando pinos e atualizando status
  for (int i = 0; i < nCircuitos; i++)
    setaPinoCircuito(&circuitos[i]);

  // Desligando os circuitos
  for (int i = 0; i < nCircuitos; i++)
    desligaCircuito(&circuitos[i]);

  // Preenchendo statusAntesCircuitos
  for (int i = 0; i < nCircuitos; i++)
    statusAntesCircuitos[i] = 2;

  // Imprime dados dos circuitos
  Serial.println("------------------ DADOS DOS CIRCUITOS ------------------");
  for (int i = 0; i < nCircuitos; i++)
    imprimeDadosCircuito(&circuitos[i], i);

}

void acaoCircuito()
{
  // Realiza ação de acordo com mensagem recebida
  if (integerFromPC >= 0 && integerFromPC < nCircuitos)
  {

    if (strcmp(messageFromPC, 'cl') == 0)
    {
      ligaCircuito(&circuitos[integerFromPC]);
    }

    if (strcmp(messageFromPC, 'cd') == 0)
    {
      desligaCircuito(&circuitos[integerFromPC]);
    }

    if (strcmp(messageFromPC, 't') == 0)
    {
      Serial.println("------------------ DADOS DOS CIRCUITOS ------------------");
      for (int i = 0; i < nCircuitos; i++)
      {
        imprimeDadosCircuito(&circuitos[i], i);
      }
    }

  }
}

void imprimeStatusCircuitos()
{
  // Controle de mudança do status dos circuitos
  for (int i = 0; i < nCircuitos; i++)
  {
    statusCircuito(&circuitos[i]);
    if (statusAntesCircuitos[i] != circuitos[i].ligado)
      imprime = 1;
  }

  if (imprime)
  {

    Serial.print("C");
    for (int i = 0; i < nCircuitos; i++)
    {
      Serial.print(i);

      if (i < nCircuitos)
        Serial.print(circuitos[i].ligado);
      else
        Serial.print("0");

    }
    Serial.print(" ");

    for (int i = 0; i < nCircuitos; i++)
      statusAntesCircuitos[i] = circuitos[i].ligado;

  }
}
