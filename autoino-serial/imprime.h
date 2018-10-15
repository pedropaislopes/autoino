#include <ArduinoJson.h>

int undef = -1;

// Criando json
const size_t bufferSize = 3 * JSON_ARRAY_SIZE(8) + JSON_OBJECT_SIZE(3);
DynamicJsonBuffer jsonBuffer(bufferSize);
JsonObject& root = jsonBuffer.createObject();
JsonArray& circuito = root.createNestedArray("circuito");
JsonArray& circdimmer = root.createNestedArray("circdimmer");
JsonArray& dimmer = root.createNestedArray("dimmer");

void setupImprime()
{


  for (int i = 0; i < 8; i++)
  {
    circuito.add(undef);
    circdimmer.add(undef);
    dimmer.add(undef);
  }

}

void acaoImprime()
{

  int imprime = 0;

  for (int i = 0; i < nCircuitos; i++)
  {
    statusCircuito(&circuitos[i]);

    if (circuito.get<int>(i) != circuitos[i].ligado)
    {
      imprime = 1;
      circuito.set(i, circuitos[i].ligado);
    }
  }
  for (int i = 0; i < nCircdimmers; i++)
  {
    statusCircdimmer(&circdimmers[i]);

    if (circdimmer.get<int>(i) != circdimmers[i].ligado)
    {
      imprime = 1;
      circdimmer.set(i, circdimmers[i].ligado);
    }

    if (dimmer.get<int>(i) != dimmers[i].getValue())
    {
      imprime = 1;
      dimmer.set(i, dimmers[i].getValue());
    }
  }

  if (imprime == 1)
  {
    root.printTo(Serial);
    Serial.println();
  }

}
