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

    if (messageFromPC[0] == 'l')
    {
      ligaCircdimmer(&circdimmers[integerFromPC]);
    }

    if (messageFromPC[0] == 'd')
    {
      desligaCircdimmer(&circdimmers[integerFromPC]);
    }

    if (messageFromPC[0] == 'b')
    {
      ligaCircdimmer(&circdimmers[integerFromPC]);
      dimmers[integerFromPC].set((int)floatFromPC);
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

      if (circdimmers[i].ligado == 0)
      {
        ligaCircdimmer(&circdimmers[i]);
        dimmers[i].set(100);
      }

      else
      {
        desligaCircdimmer(&circdimmers[i]);
      }

      interrpAntesCircdimmers[i] = circdimmers[i].valInterrp;
    }
  }
}
