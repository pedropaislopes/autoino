#include <ArduinoJson.h>

int undef = -1;

// Criando json
const size_t bufferSize = 2 * JSON_ARRAY_SIZE(8) + JSON_OBJECT_SIZE(2);
DynamicJsonBuffer jsonBuffer(bufferSize);
JsonObject& root = jsonBuffer.createObject();
JsonArray& circuito = root.createNestedArray("circuito");
JsonArray& dimmer = root.createNestedArray("dimmer");

void setupImprime()
{


  for (int i = 0; i < 8; i++)
  {
    circuito.add(undef);
    dimmer.add(undef);
  }

}

void acaoImprime()
{

  int imprime = 0;

  for (int i = 0; i < 8; i++)
  {
    if (circuito.get<int>(i) != circuitos[i].ligado || dimmer.get<int>(i) != circdimmers[i].brilho)
    {
      imprime = 1;

      // Atualiza json
      circuito.set(i, circuitos[i].ligado);
      dimmer.set(i, circdimmers[i].brilho);

    }

  }

  if (imprime == 1)
  {
    root.printTo(Serial);
    Serial.println();
  }

}
