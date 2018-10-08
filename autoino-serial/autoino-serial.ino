#include "serialinput.h"
#include "dadosCircuitos.h"
#include "dadosCircdimmers.h"

void setup() {

  Serial.begin(9600);

  // Setup dos circuitos
  setupCircuitos();

  // Setup dos dimmers
  setupCircdimmers();

  Serial.println("Pronto");
  
}

void loop() {

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
    //      - s: troca estado do switch
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

  // Imprime status dos circuitos
  imprimeStatusCircuitos();

  imprimeStatusCircdimmers();

}
