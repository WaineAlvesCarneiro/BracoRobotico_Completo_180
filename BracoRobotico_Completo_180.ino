#include <Servo.h>

Servo servoBase;
Servo servoOmbro;
Servo servoCotovelo;
Servo servoPulso;
Servo servoGarra;

const int PIN_BOTAO    = 2;
const int PIN_BASE     = 3;
const int PIN_OMBRO    = 5;
const int PIN_COTOVELO = 6;
const int PIN_PULSO    = 9;
const int PIN_GARRA    = 10;

const int DELAY_INICIAR = 500;
const int DELAY_PDRAO = 30;
const int DELAY_ESTABILIZAR = 500;

int posInicialBase = 90;
int posInicialOmbro = 0;
int posInicialCotovelo = 0;
int posInicialPulso = 0;
int posInicialGarra = 90;

int posAtualBase = 90;
int posAtualOmbro = 0;
int posAtualCotovelo = 0;
int posAtualPulso = 0;
int posAtualGarra = 90;

int destinoPegaObjetoBase = 0;
int abrirGarra = 45;
int destinoPegaObjetoPulso = 60;
int destinoPegaObjetoCotovelo = 45;
int destinoPegaObjetoOmbro = 55;
int segurarObjetoGarra = 80;
int subirPulsoParaGiraBase = 50;
int destinoSoltarObjetoBase = 180;
int baixarPulsoSoltarObjeto = 58;
int soltarObjetoGarra = 45;
int subirPulsoAposSoltarObjeto = 50;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BOTAO, INPUT_PULLUP);
  Serial.println("Iniciando motores suavemente via Arduino direto...");
  inicializacaoSuave();
  Serial.println("Pronto!");
}

void inicializacaoSuave() {
  delay(DELAY_INICIAR);

  servoOmbro.attach(PIN_OMBRO);
  servoOmbro.write(posInicialOmbro);
  delay(DELAY_INICIAR);

  servoCotovelo.attach(PIN_COTOVELO);
  servoCotovelo.write(posInicialCotovelo);
  delay(DELAY_INICIAR);

  servoPulso.attach(PIN_PULSO);
  servoPulso.write(posInicialPulso);
  delay(DELAY_INICIAR);

  servoGarra.attach(PIN_GARRA);
  servoGarra.write(posInicialGarra);
  delay(DELAY_INICIAR);

  servoBase.attach(PIN_BASE);
  servoBase.write(posInicialBase);
  delay(DELAY_INICIAR);
}

void loop() {
  if (digitalRead(PIN_BOTAO) == LOW) {
    delay(250); 
    executarCicloCompleto();
  }
}

void mover(Servo &meuServo, int &posAtual, int destino, int vel) {
  if (posAtual == destino) return;

  if (posAtual < destino) {
    for (int i = posAtual; i <= destino; i++) {
      meuServo.write(i);
      delay(vel);
    }
  } else {
    for (int i = posAtual; i >= destino; i--) {
      meuServo.write(i);
      delay(vel);
    }
  }
  posAtual = destino;
}

void executarCicloCompleto() {
  mover(servoBase, posAtualBase, destinoPegaObjetoBase, DELAY_PDRAO);
  delay(DELAY_ESTABILIZAR);

  mover(servoGarra, posAtualGarra, abrirGarra, DELAY_PDRAO);
  delay(DELAY_ESTABILIZAR);

  mover(servoPulso, posAtualPulso, destinoPegaObjetoPulso, DELAY_PDRAO);
  delay(DELAY_ESTABILIZAR);

  mover(servoCotovelo, posAtualCotovelo, destinoPegaObjetoCotovelo, DELAY_PDRAO);
  delay(DELAY_ESTABILIZAR);

  mover(servoOmbro, posAtualOmbro, destinoPegaObjetoOmbro, DELAY_PDRAO);
  delay(DELAY_ESTABILIZAR);

  mover(servoGarra, posAtualGarra, segurarObjetoGarra, DELAY_PDRAO);
  delay(DELAY_ESTABILIZAR);

  mover(servoPulso, posAtualPulso, subirPulsoParaGiraBase, DELAY_PDRAO);
  delay(DELAY_ESTABILIZAR);
  
  mover(servoBase, posAtualBase, destinoSoltarObjetoBase, DELAY_PDRAO);
  delay(DELAY_ESTABILIZAR);
  
  mover(servoPulso, posAtualPulso, baixarPulsoSoltarObjeto, DELAY_PDRAO);
  delay(DELAY_ESTABILIZAR);

  mover(servoGarra, posAtualGarra, soltarObjetoGarra, DELAY_PDRAO);
  delay(DELAY_ESTABILIZAR);

  mover(servoPulso, posAtualPulso, subirPulsoAposSoltarObjeto, DELAY_PDRAO);
  delay(DELAY_ESTABILIZAR);

  delay(2000);
  resetarParaPosicaoInicial();
}

void resetarParaPosicaoInicial() {
  mover(servoOmbro, posAtualOmbro, posInicialOmbro, DELAY_PDRAO);
  delay(DELAY_ESTABILIZAR);
  mover(servoCotovelo, posAtualCotovelo, posInicialCotovelo, DELAY_PDRAO);
  delay(DELAY_ESTABILIZAR);
  mover(servoPulso, posAtualPulso, posInicialPulso, DELAY_PDRAO);
  delay(DELAY_ESTABILIZAR);
  mover(servoGarra, posAtualGarra, posInicialGarra, DELAY_PDRAO);
  delay(DELAY_ESTABILIZAR);
  mover(servoBase, posAtualBase, posInicialBase, DELAY_PDRAO);
  delay(DELAY_ESTABILIZAR);
}