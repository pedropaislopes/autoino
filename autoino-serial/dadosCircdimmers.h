#include "Dimmer.h"
#include "circdimmers.h"

/********************************************
   Este arquivo tem dados, setup e e parte do loop para Circdimmers
*/

Dimmer dimmers[] = {
  Dimmer(13, DIMMER_RAMP),
  Dimmer(3, DIMMER_RAMP)
};

const int nCircdimmers = 2;
int interrpAntesCircdimmers[nCircdimmers];
Circdimmer circdimmers[nCircdimmers];

// Define dados dos Circdimmers
void defineCircdimmers(void)
{
  circdimmers[0].pinoSwitch = 10;
  circdimmers[0].outputA = 15;
  circdimmers[0].outputB = 16;
  circdimmers[0].counter = 0;
  circdimmers[0].nome = "CD.SCP";
  circdimmers[1].pinoSwitch = 4;
  circdimmers[1].outputA = 11;
  circdimmers[1].outputB = 12;
  circdimmers[1].counter = 0;
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

    imprimeDadosCircdimmer(&circdimmers[i], &dimmers[i], i);

    circdimmers[i].aLastState = digitalRead(circdimmers[i].outputA);
  }
}

void acaoCircdimmer()
{
  // Realiza ação de acordo com mensagem recebida
  if (integerFromPC >= 0 && integerFromPC < nCircdimmers)
  {

    if (messageFromPC[0] == 'm')
    {
      ligaCircdimmer(&circdimmers[integerFromPC]);
      dimmers[integerFromPC].set((int)floatFromPC);
    }

    if (messageFromPC[0] == 'e')
    {
      desligaCircdimmer(&circdimmers[integerFromPC]);
      dimmers[integerFromPC].set((int)floatFromPC);
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

void encoderCircdimmers()
{

  for (int i = 0; i < nCircdimmers; i++)
  {

    circdimmers[i].aState = digitalRead(circdimmers[i].outputA); // Reads the "current" state of the outputA
    // If the previous and the current state of the outputA are different, that means a Pulse has occured
    if (circdimmers[i].aState != circdimmers[i].aLastState) {
      // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise

      if (digitalRead(circdimmers[i].outputB) != circdimmers[i].aState) {

        ligaCircdimmer(&circdimmers[i]);
        circdimmers[i].counter = circdimmers[i].counter + 3;
        if (circdimmers[i].counter > 100)
          circdimmers[i].counter = 100;

      } else {

        circdimmers[i].counter = circdimmers[i].counter - 3;
        if (circdimmers[i].counter <= 0) {
          desligaCircdimmer(&circdimmers[i]);
          circdimmers[i].counter = 0;
        }

      }
    }

    dimmers[i].set(circdimmers[i].counter);
  }
}
