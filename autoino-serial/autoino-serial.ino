#include <SimpleDHT.h>

#include "serialinput.h"
#include "dadosCircuitos.h"
#include "dadosCircdimmers.h"
#include "imprime.h"

int pinDHT22 = 14;
SimpleDHT22 dht22(pinDHT22);
long prevMillisDHT = 0;
const long intervalDHT = 3000;

void setup() {

  Serial.begin(9600);

  // Setup dos circuitos
  setupCircuitos();

  // Setup dos dimmers
  setupCircdimmers();

  // Setup da impressão de status
  setupImprime();

  Serial.println("Pronto");

}

void loop() {

  unsigned long currMillisDHT = millis();
  float humidity;
  float temperature;

  if (currMillisDHT - prevMillisDHT > intervalDHT)
  {
    prevMillisDHT = currMillisDHT;
    dht22.read2(&temperature, &humidity, NULL);

  }

  // Atualiza brilho do dimmer de acordo com interruptor dos circdimmers
  interrpCircdimmers();

  // Obtendo string da serial
  recvWithStartEndMarkers();

  if (newData == true) {
    strcpy(tempChars, receivedChars);
    // this temporary copy is necessary to protect the original data
    //   because strtok() used in parseData() replaces the commas with \0

    // Como é formado um dado recebido na serial
    // <X,Y,Z>
    // - X: comando. Pode ser:
    //   - c?: circuito
    //   - d?: dimmer
    //   Onde ? pode ser:
    //      - l: liga
    //      - d: desliga
    //      - t: status de todos os circuitos ou dimmers
    // - Y: número do circuito ou dimmer
    // - Z: valor do brilho (só vale para dimmer, é ignorado para circuito)
    //
    parseData();

    // Ações dos circuitos
    acaoCircuito();

    // Ações dos dimmers
    acaoCircdimmer();

    newData = false;
  }

  // Imprime status
  acaoImprime(humidity, temperature);

}
