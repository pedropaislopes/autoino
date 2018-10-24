/*
   Este fonte tem funções para ligar, desligar e setar os dimmers
*/

#define ligDes(X) X == 1 ? " ligado" : " desligado"

typedef struct Circdimmer
{
  int pinoSwitch;  // Pino digital de que aciona o switch de energia AC
  int pinoInterrp; // Pino analógico do interruptor de parede
  int ligado;      // Se switch de energia AC está ligado ou não
  int outputA;
  int outputB;
  int aState;
  int aLastState;
  int counter;
  String nome;     // Nome do dimmer
} Circdimmer;

void statusCircdimmer(Circdimmer *circdm)
{
  (*circdm).ligado = !digitalRead((*circdm).pinoSwitch);
}

// Imprime dados do circdimmer
void imprimeDadosCircdimmer(Circdimmer *circdm, Dimmer *dimmer, int ic)
{
  Serial.print("circdimmer ");
  Serial.print(ic);
  Serial.print(" pinoSwitch ");
  Serial.print((*circdm).pinoSwitch);
  Serial.print(" ligado ");
  Serial.print((*circdm).ligado);
  Serial.print(" nome ");
  Serial.print((*circdm).nome);
  Serial.print(" pinoSwitchVal ");
  Serial.print(digitalRead((*circdm).pinoSwitch));
  Serial.print(" Dimmer.getValue ");
  Serial.print((*dimmer).getValue());
  Serial.print(" Dimmer.getState ");
  Serial.print((*dimmer).getState());

  Serial.println();
}

// Seta os pinos dos circdimmer (somente relé)
void setaPinoCircdimmer(Circdimmer *circdm, int dimmer)
{
  pinMode((*circdm).pinoSwitch, OUTPUT);
  digitalWrite((*circdm).pinoSwitch, HIGH);
  pinMode((*circdm).outputA, INPUT);
  pinMode((*circdm).outputB, INPUT);
  delay(50);
  statusCircdimmer(circdm);
#ifdef DEBUGCIRCUITO
  imprimeDadosCircdimmer(circdm, dimmer);
#endif
}

// Troca de LOW para HIGH no pino do switch
void switchCircdimmer(Circdimmer *circdm)
{
  digitalWrite((*circdm).pinoSwitch, !digitalRead((*circdm).pinoSwitch));
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
