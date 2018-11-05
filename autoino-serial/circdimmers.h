/*
   Este fonte tem funções para ligar, desligar e setar os dimmers
*/

#define ligDes(X) X == 1 ? " ligado" : " desligado"

typedef struct Circdimmer
{
  int pinoRele;  // Pino digital de que aciona o switch de energia AC
  int ligado;      // Se switch de energia AC está ligado ou não
  int encSW;
  int counter;
  int oldPos;
  String nome;     // Nome do dimmer
} Circdimmer;

void statusCircdimmer(Circdimmer *circdm)
{
  (*circdm).ligado = !digitalRead((*circdm).pinoRele);
}

// Imprime dados do circdimmer
void imprimeDadosCircdimmer(Circdimmer *circdm, Dimmer *dimmer, int ic)
{
  Serial.print("circdimmer ");
  Serial.print(ic);
  Serial.print(" pinoRele ");
  Serial.print((*circdm).pinoRele);
  Serial.print(" ligado ");
  Serial.print((*circdm).ligado);
  Serial.print(" nome ");
  Serial.print((*circdm).nome);
  Serial.print(" pinoSwitchVal ");
  Serial.print(digitalRead((*circdm).pinoRele));
  Serial.print(" Dimmer.getValue ");
  Serial.print((*dimmer).getValue());
  Serial.print(" Dimmer.getState ");
  Serial.print((*dimmer).getState());

  Serial.println();
}

// Seta os pinos dos circdimmer (somente relé)
void setaPinoCircdimmer(Circdimmer *circdm, int dimmer)
{
  pinMode((*circdm).pinoRele, OUTPUT);
  digitalWrite((*circdm).pinoRele, HIGH);
  pinMode((*circdm).encSW, HIGH);
  delay(50);
  statusCircdimmer(circdm);
#ifdef DEBUGCIRCUITO
  imprimeDadosCircdimmer(circdm, dimmer);
#endif
}

// Troca de LOW para HIGH no pino do switch
void switchCircdimmer(Circdimmer *circdm)
{
  digitalWrite((*circdm).pinoRele, !digitalRead((*circdm).pinoRele));
}

// Liga circuito
void ligaCircdimmer(Circdimmer *circdm)
{
  statusCircdimmer(circdm);
#ifdef DEBUGCIRCUITO
  Serial.print("circdimmer ");
  Serial.print((*circdm).nome);
  Serial.print(" esta");
  Serial.print(ligDes((*circdm).ligado));
  Serial.println();
#endif
  if (!(*circdm).ligado)
    switchCircdimmer(circdm);
}

// Desliga circuito
void desligaCircdimmer(Circdimmer *circdm)
{
  statusCircdimmer(circdm);
#ifdef DEBUGCIRCUITO
  Serial.print("circdimmer ");
  Serial.print((*circdm).nome);
  Serial.print(" esta");
  Serial.print(ligDes((*circdm).ligado));
  Serial.println();
#endif
  if ((*circdm).ligado)
    switchCircdimmer(circdm);
}
