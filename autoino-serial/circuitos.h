/****************************************************
Este fonte implementa funções e struct para trabalhar com circuitos
*/

//#define DEBUGCIRCUITO 1
//#define DEBUGCIRCUITOSTATUS 1
//#define DEBUGSERIALINPUT 1
#define ligDes(X) X == 1 ? " ligado" : " desligado"

typedef struct circuito
{
  int pinoSwitch;   // Pino digital de acionamento do relê
  int pinoSensor;   // Pino analógico do sensor de tensão
  // Se nagativo então "ligado" = digitalRead(pinoSwitch)
  int sensorDesl;   // Valor máximo que o sensor apresenta quando circuito desligado
  int sensorLig;    // Valor mínimo que o sensor apresenta quando circuito ligado
  int ligado;       // Status do circuito a(0 = desligado / 1 = ligado)
  String nome;      // Nome do circuito
} Circuito;

// Obtém status do circuito e atualiza membro da struct "ligado"
void statusCircuito(Circuito *circ)
{
  int val, valAntes;
  if ((*circ).pinoSensor < 0)
  {
    val = digitalRead((*circ).pinoSwitch) * 1000;
    valAntes = val;
  }
  else
  {
    valAntes = analogRead((*circ).pinoSensor);
    delay(50);
    val = analogRead((*circ).pinoSensor);
  }
  if(valAntes > (*circ).sensorDesl && val > (*circ).sensorDesl)
    (*circ).ligado = 1;
  if(valAntes < (*circ).sensorLig  && val < (*circ).sensorLig )
    (*circ).ligado = 0;
#ifdef DEBUGCIRCUITOSTATUS
  Serial.print("circuito ");
  Serial.print((*circ).nome);
  Serial.print(" sensorTensao ");
  Serial.println(val);
#endif
}

// Imprime dados do circuito
void imprimeDadosCircuito(Circuito *circ)
{
  Serial.print("pinoSwitch ");
  Serial.print((*circ).pinoSwitch);
  Serial.print(" pinoSensor ");
  Serial.print((*circ).pinoSensor);
  Serial.print(" sensorDesl ");
  Serial.print((*circ).sensorDesl);
  Serial.print(" sensorLig ");
  Serial.print((*circ).sensorLig);
  Serial.print(" ligado ");
  Serial.print((*circ).ligado);
  Serial.print(" nome ");
  Serial.print((*circ).nome);
  Serial.print(" pinoSwitchVal ");
  Serial.print(digitalRead((*circ).pinoSwitch));
  Serial.print(" pinoSensorVal ");
  Serial.print(analogRead((*circ).pinoSensor));
  Serial.println();
}

// Seta os pinos dos circuitos
void setaPinoCircuito(Circuito *circ)
{
  pinMode((*circ).pinoSwitch, OUTPUT);
  digitalWrite((*circ).pinoSwitch, HIGH);
  pinMode((*circ).pinoSensor, INPUT);
  statusCircuito(circ);
#ifdef DEBUGCIRCUITO
  imprimeDadosCircuito(circ);
#endif
}

// Troca de LOW para HIGH no pino do switch
void switchCircuito(Circuito *circ)
{
  digitalWrite((*circ).pinoSwitch, !digitalRead((*circ).pinoSwitch));
}

// Liga circuito
void ligaCircuito(Circuito *circ)
{
  statusCircuito(circ);
#ifdef DEBUGCIRCUITO
  Serial.print("circuito ");
  Serial.print((*circ).nome);
  Serial.print(" esta");
  Serial.print(ligDes((*circ).ligado));
  Serial.println();
#endif
  if (!(*circ).ligado)
    switchCircuito(circ);
}

// Desliga circuito
void desligaCircuito(Circuito *circ)
{
  statusCircuito(circ);
#ifdef DEBUGCIRCUITO
  Serial.print("circuito ");
  Serial.print((*circ).nome);
  Serial.print(" esta");
  Serial.print(ligDes((*circ).ligado));
  Serial.println();
#endif
  if ((*circ).ligado)
    switchCircuito(circ);
}
