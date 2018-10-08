#include "Dimmer.h"
#include "circdimmers.h"

/********************************************
   Este arquivo tem dados, setup e e parte do loop para Circdimmers
*/

Dimmer dimmers[] = {
  Dimmer(3, DIMMER_RAMP)
};

const int nCircdimmers = 1;
int statusAntesCircdimmers[nCircdimmers];
int interrpAntesCircdimmers[nCircdimmers];
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
  for (int i = 0; i < nCircdimmers; i++)
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

  // Preenchendo status e interrp
  for (int i = 0; i < nCircdimmers; i++)
  {
    statusAntesCircdimmers[i] = circdimmers[i].brilho;
    interrpAntesCircdimmers[i] = circdimmers[i].valInterrp;
  }

  // Imprime dados dos dimmers
  Serial.println("------------------ DADOS DOS DIMMERS ------------------");
  for (int i = 0; i < nCircdimmers; i++)
    imprimeDadosCircdimmer(&circdimmers[i], &dimmers[i], i);
}

void acaoCircdimmer()
{
  // Realiza ação de acordo com mensagem recebida
  if (integerFromPC >= 0 && integerFromPC < nCircdimmers)
  {

    if (strcmp(messageFromPC, 'db') == 0)
    {
      int brilho = (int)floatFromPC *  11;

      if (brilho > 0 && circdimmers[integerFromPC].brilho == 0)
      {
        ligaCircdimmer(&circdimmers[integerFromPC]);
        dimmers[integerFromPC].set(brilho, 1);
      }

      if (brilho == 0 && circdimmers[integerFromPC].brilho > 0)
      {
        dimmers[integerFromPC].off();
        desligaCircdimmer(&circdimmers[integerFromPC]);
      }

      if (brilho > 0 && circdimmers[integerFromPC].brilho > 0)
        dimmers[integerFromPC].set(brilho);

      circdimmers[integerFromPC].brilho = (int)floatFromPC;
    }

    if (strcmp(messageFromPC, 'dt') == 0)
    {
      Serial.println("------------------ DADOS DOS DIMMERS ------------------");
      for (int i = 0; i < nCircdimmers; i++)
      {
        imprimeDadosCircdimmer(&circdimmers[i], &dimmers[i], i);
      }
    }

  }
}

void imprimeStatusCircdimmers()
{
  // Controle de mudança do status dos Circdimmers
  for (int i = 0; i < nCircdimmers; i++)
  {
    statusCircdimmer(&circdimmers[i]);
    if (statusAntesCircdimmers[i] != circdimmers[i].brilho)
      imprime = 1;
  }

  if (imprime)
  {

    Serial.print("D");
    for (int i = 0; i < 8; i++)
    {
      Serial.print(i);

      if (i < nCircdimmers)
        Serial.print(circdimmers[i].brilho);
      else
        Serial.print("0");

    }
    Serial.print(" ");

    for (int i = 0; i < nCircdimmers; i++)
    {
      statusAntesCircdimmers[i] = circdimmers[i].ligado;
      interrpAntesCircdimmers[i] = circdimmers[i].valInterrp;
    }

  }
}


void interrpCircdimmers()
{

  for (int i = 0; i < nCircdimmers; i++)
  {
    if (interrpAntesCircdimmers[i] != circdimmers[i].valInterrp)
    {

      if (circdimmers[i].ligado == 0)
      {
        ligaCircdimmer(&circdimmers[integerFromPC]);
        dimmers[integerFromPC].set(99, 1);
        circdimmers[i].brilho = 9;
      }

      else
      {
        dimmers[integerFromPC].off();
        desligaCircdimmer(&circdimmers[integerFromPC]);
        circdimmers[i].brilho = 0;
      }
    }
  }
}
