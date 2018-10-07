//#define DEBUGCIRCUITO 1
//#define DEBUGCIRCUITOSTATUS 1
//#define DEBUGSERIALINPUT 1
#include "circuitos.h"
#include "serialinput.h"

const int nCircuitos = 4;

int statusAntes[nCircuitos];

Circuito circuitos[nCircuitos];

// Define dados dos circuitos
void defineCircuitos(void)
{
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
}

void setup() {

  Serial.begin(9600);

  defineCircuitos();

  // Setando pinos
  for (int i = 0; i < nCircuitos; i++)
    setaPino(&circuitos[i]);

  delay(1000);

  // Desligando os circuitos
  for (int i = 0; i < nCircuitos; i++)
    desligaCircuito(&circuitos[i]);

  // Preenchendo statusAntes
  for (int i = 0; i < nCircuitos; i++)
    statusAntes[i] = circuitos[i].ligado;

  Serial.println("Pronto");

}

void loop() {

  // Obtendo string da serial
  recvWithStartEndMarkers();

  if (newData == true) {
    strcpy(tempChars, receivedChars);
    // this temporary copy is necessary to protect the original data
    //   because strtok() used in parseData() replaces the commas with \0
    parseData();

    // Realiza ação de acordo com mensagem recebida
    if (strcmp(messageFromPC, "s") == 0)
      if (integerFromPC >= 0 && integerFromPC < nCircuitos)
      {
        switchCircuito(&circuitos[integerFromPC]);
      }

    if (strcmp(messageFromPC, "t") == 0)
      for (int i = 0; i < nCircuitos; i++)
      {
        imprimeDadosCircuito(&circuitos[i]);
      }

    newData = false;
  }

  // Controle de mudança do status dos circuitos
  bool imprime = 0;
  for (int i = 0; i < nCircuitos; i++)
  {
    statusCircuito(&circuitos[i]);
    if (statusAntes[i] != circuitos[i].ligado)
      imprime = 1;
  }
  if (imprime)
  {
    for (int i = 0; i < nCircuitos; i++)
    {
      Serial.print(i);
      Serial.print(circuitos[i].ligado);
    }
    Serial.println();
    for (int i = 0; i < nCircuitos; i++)
      statusAntes[i] = circuitos[i].ligado;
  }

}
