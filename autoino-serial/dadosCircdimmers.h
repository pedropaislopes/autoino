#include "Dimmer.h"
#include "circdimmers.h"

/********************************************
   Este arquivo tem dados, setup e e parte do loop para Circdimmers
*/

Dimmer dimmers[] = {
    Dimmer(16, DIMMER_RAMP),
    Dimmer(3, DIMMER_RAMP)
};

const int nCircdimmers = 2;
int interrpAntesCircdimmers[nCircdimmers];
Circdimmer circdimmers[nCircdimmers];

// Define dados dos Circdimmers
void defineCircdimmers(void)
{
  circdimmers[0].pinoSwitch = 4;
  circdimmers[0].pinoInterrp = 13;
  circdimmers[0].nome = "CD.SCP";
  circdimmers[1].pinoSwitch = 10;
  circdimmers[1].pinoInterrp = 12;
  circdimmers[1].nome = "CD.VRD";
}

void setupCircdimmers()
{
  defineCircdimmers();

  Serial.println("------------------ DADOS DOS DIMMERS ------------------");
  for (int i = 0; i < nCircdimmers; i++)
  {
    dimmers[i].begin();
    dimmers[i].on();

    setaPinoCircdimmer(&circdimmers[i], i);

    desligaCircdimmer(&circdimmers[i]);

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
