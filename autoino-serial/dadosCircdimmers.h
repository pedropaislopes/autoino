#include "Dimmer.h"
#include "circdimmers.h"

/********************************************
   Este arquivo tem dados, setup e e parte do loop para Circdimmers
*/

Dimmer dimmers[] = {
//  Dimmer(3, DIMMER_RAMP)
};

const int nCircdimmers = 0;
int interrpAntesCircdimmers[nCircdimmers];
Circdimmer circdimmers[nCircdimmers];

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

  Serial.println("------------------ DADOS DOS DIMMERS ------------------");
  for (int i = 0; i < nCircdimmers; i++)
  {
    dimmers[i].begin();

    setaPinoCircdimmer(&circdimmers[i], i);

    desligaCircdimmer(&circdimmers[i]);
    dimmers[i].off();

    interrpAntesCircdimmers[i] = circdimmers[i].valInterrp;

    imprimeDadosCircdimmer(&circdimmers[i], &dimmers[i], i);
  }
}

void acaoCircdimmer()
{
  // Realiza ação de acordo com mensagem recebida
  if (integerFromPC >= 0 && integerFromPC < nCircdimmers)
  {

    if (messageFromPC[0] == 'b')
    {
      int brilho = (int)floatFromPC *  11;

      if (brilho > 0 && circdimmers[integerFromPC].brilho == 0)
      {
        ligaCircdimmer(&circdimmers[integerFromPC]);
        dimmers[integerFromPC].set(brilho, 1);
      }

      if (brilho == 0 && circdimmers[integerFromPC].brilho > 0)
      {
        dimmers[integerFromPC].set(brilho, 0);
        desligaCircdimmer(&circdimmers[integerFromPC]);
      }

      if (brilho > 0 && circdimmers[integerFromPC].brilho > 0)
        dimmers[integerFromPC].set(brilho);

      circdimmers[integerFromPC].brilho = (int)floatFromPC;
    }

    if (messageFromPC[0] == 't')
    {
      Serial.println("------------------ DADOS DOS DIMMERS ------------------");
      for (int i = 0; i < nCircdimmers; i++)
      {
        imprimeDadosCircdimmer(&circdimmers[i], &dimmers[i], i);
      }
    }

  }
}

void interrpCircdimmers()
{

  for (int i = 0; i < nCircdimmers; i++)
  {
    if (interrpAntesCircdimmers[i] != circdimmers[i].valInterrp)
    {

      if (circdimmers[i].brilho == 0)
      {
        ligaCircdimmer(&circdimmers[integerFromPC]);
        dimmers[integerFromPC].set(99, 1);
        circdimmers[i].brilho = 9;
      }

      else
      {
        dimmers[integerFromPC].set(0, 0);
        desligaCircdimmer(&circdimmers[integerFromPC]);
        circdimmers[i].brilho = 0;
      }

      interrpAntesCircdimmers[i] = circdimmers[i].valInterrp;
    }
  }
}
