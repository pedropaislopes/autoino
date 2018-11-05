#include <Encoder.h>
#include "Dimmer.h"
#include "circdimmers.h"

/********************************************
   Este arquivo tem dados, setup e e parte do loop para Circdimmers
*/

Dimmer dimmers[] = {
  Dimmer(7, DIMMER_RAMP), // SCP
  Dimmer(53, DIMMER_RAMP) // VRD
};

Encoder encoders[] = {
  Encoder(19, 42), // SCP
  Encoder(18, 43)  // VRD
};

const int nCircdimmers = 2;
int interrpAntesCircdimmers[nCircdimmers];
Circdimmer circdimmers[nCircdimmers];

// Define dados dos Circdimmers
void defineCircdimmers(void)
{
  circdimmers[0].pinoRele = 52;
  circdimmers[0].encSW = 40;
  circdimmers[0].counter = 0;
  circdimmers[0].oldPos = 0;
  circdimmers[0].nome = "CD.SCP";
<<<<<<< HEAD
  circdimmers[1].pinoRele = 51;
  circdimmers[0].encSW = 41;
=======
  circdimmers[1].pinoSwitch = 4;
  circdimmers[1].outputA = 12;
  circdimmers[1].outputB = 11;
>>>>>>> 96ade752c4f9e1ba3e11545f00eca863375126e2
  circdimmers[1].counter = 0;
  circdimmers[1].oldPos = 0;
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
  long pos;
  for (int i = 0; i < nCircdimmers; i++)
  {

    pos = encoders[i].read();

    if (pos != circdimmers[i].oldPos) {

      circdimmers[i].counter = circdimmers[i].counter + (pos - circdimmers[i].oldPos);

      if (circdimmers[i].counter > 100)
        circdimmers[i].counter = 100;
      if (circdimmers[i].counter < 5)
        circdimmers[i].counter = 0;

      if (circdimmers[i].counter > 0) {

        ligaCircdimmer(&circdimmers[i]);
<<<<<<< HEAD

      } else {

        desligaCircdimmer(&circdimmers[i]);
      }
=======
        circdimmers[i].counter = circdimmers[i].counter + 10;
        if (circdimmers[i].counter > 100)
          circdimmers[i].counter = 100;

      } else {

        circdimmers[i].counter = circdimmers[i].counter - 10;
        if (circdimmers[i].counter <= 0) {
          desligaCircdimmer(&circdimmers[i]);
          circdimmers[i].counter = 0;
        }

      }
//     Serial.print(i);
//     Serial.print("Position: ");
//     Serial.println(circdimmers[i].counter);
    }
    circdimmers[i].aLastState = circdimmers[i].aState; // Updates the previous state of the outputA with the current state
>>>>>>> 96ade752c4f9e1ba3e11545f00eca863375126e2

      dimmers[i].set(circdimmers[i].counter);

      circdimmers[i].oldPos = pos;
    }
  }
}
