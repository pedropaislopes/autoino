#include "Dimmer.h"
#include "circdimmers.h"

/********************************************
 * Este arquivo tem dados, setup e e parte do loop para Circdimmers
 */

Dimmer dimmers[] = {
  Dimmer(3, DIMMER_RAMP)
};

const int nCircdimmers = 1;
int statusAntesCircdimmers[nCircdimmers];
Circdimmer circdimmers[nCircdimmers];

//Dimmer dimmers[] = {
//  (3, DIMMER_RAMP)
//};

// Define dados dos Circdimmers
void defineCircdimmers(void)
{
  circdimmers[0].pinoSwitch = 4;
  circdimmers[0].pinoInterrp = A0;
  circdimmers[0].brilho = 0;
  circdimmers[0].nome = "dimmer_teste";
}

void setupCircdimmers()
{
  defineCircdimmers();

  // Define dimmers PWM
  for(int i = 0; i < nCircdimmers; i++)
    dimmers[i].begin();

  // Setando pinos
  for (int i = 0; i < nCircdimmers; i++)
    setaPinoCircdimmer(&circdimmers[i], i);

  delay(1000);

  // Desligando os Circdimmers
  for (int i = 0; i < nCircdimmers; i++)
  {
    desligaCircdimmer(&circdimmers[i]);
    dimmers[i].set(circdimmers[i].brilho, 0);
  }    

  // Preenchendo statusAntesCircdimmers
  for (int i = 0; i < nCircdimmers; i++)
    statusAntesCircdimmers[i] = circdimmers[i].ligado;

  // Imprime dados dos dimmers
  Serial.println("------------------ DADOS DOS DIMMERS ------------------");
  for (int i = 0; i < nCircdimmers; i++)
    imprimeDadosCircdimmer(&circdimmers[i], &dimmers[i], i);
}

void acaoCircdimmer()
{
  // Realiza ação de acordo com mensagem recebida
  if (strcmp(messageFromPC, "d") == 0)
    if (integerFromPC >= 0 && integerFromPC < nCircdimmers)
    {
      if (floatFromPC > 0 && circdimmers[integerFromPC].brilho == 0)
      {      
        ligaCircdimmer(&circdimmers[integerFromPC]);
        dimmers[integerFromPC].set((int)floatFromPC, 1);
      }
      if (floatFromPC == 0 && circdimmers[integerFromPC].brilho > 0)
      {
        dimmers[integerFromPC].off();
        desligaCircdimmer(&circdimmers[integerFromPC]);
      }
      if (floatFromPC > 0 && circdimmers[integerFromPC].brilho > 0) 
        dimmers[integerFromPC].set((int)floatFromPC);

      circdimmers[integerFromPC].brilho = (int)floatFromPC;
    }
        
  if (strcmp(messageFromPC, "u") == 0)
  {
   Serial.println("------------------ DADOS DOS DIMMERS ------------------");
   for (int i = 0; i < nCircdimmers; i++)
    {
      imprimeDadosCircdimmer(&circdimmers[i], &dimmers[i], i);
    }
  }
}

void imprimeStatusCircdimmers()
{
  // Controle de mudança do status dos Circdimmers
  bool imprime = 0;
  for (int i = 0; i < nCircdimmers; i++)
  {
    statusCircdimmer(&circdimmers[i]);
    if (statusAntesCircdimmers[i] != circdimmers[i].ligado)
      imprime = 1;
  }
  if (imprime)
  {
    for (int i = 0; i < nCircdimmers; i++)
    {
      Serial.print(i);
      Serial.print(circdimmers[i].ligado);
    }
    Serial.println();
    for (int i = 0; i < nCircdimmers; i++)
      statusAntesCircdimmers[i] = circdimmers[i].ligado;
  }
}
