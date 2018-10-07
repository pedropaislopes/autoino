#include "serialinput.h"
#include "dadosCircuitos.h"

void setup() {

  Serial.begin(9600);

  // Setup dos circuitos
  setupCircuitos();

  Serial.println("Pronto");

}

void loop() {

  // Obtendo string da serial
  recvWithStartEndMarkers();

  if (newData == true) {
    strcpy(tempChars, receivedChars);
    // this temporary copy is necessary to protect the original data
    //   because strtok() used in parseData() replaces the commas with \0
    parseData();

    // Ações dos circuitos
    acaoCircuito();
    
    newData = false;
  }

  // Imprime status dos circuitos
  imprimeStatusCircuitos();

}
