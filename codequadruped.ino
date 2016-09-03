#include <Servo.h> 
#include <ALLBOT.h>
#include <SoftwareSerial.h>

#define FRENTE 97
#define DIREITA 98
#define ESQUERDA 100
#define START 122
#define SELECT 120

SoftwareSerial btSerial (4, 8); //RX, TX
ALLBOT BOT(8);

//velocidade padrao de execucao de comandos
int tempo = 80; 
byte comando = 0;
int vezes = 4;

enum MotorName {
  hipFrontLeft,
  hipFrontRight,
  hipRearLeft,
  hipRearRight,
  kneeFrontLeft,
  kneeFrontRight,
  kneeRearLeft,
  kneeRearRight
};

void setup() {
  //(nome, pino, anguloIncial, servo:invertidoOUnao, affset);
  BOT.attach(hipFrontRight,   3,  90, 0, -45);
  BOT.attach(kneeFrontRight,  5,  0,  1, 50);
  
  BOT.attach(hipRearRight,    6,  90, 0, -50);
  BOT.attach(kneeRearRight,   9,  0,  0, 30);
  
  BOT.attach(hipRearLeft,     10, 90, 1, 10);
  BOT.attach(kneeRearLeft,    11,  0, 1, 20);
  
  BOT.attach(hipFrontLeft,    12,  90, 1, 40);
  BOT.attach(kneeFrontLeft,   2,  0, 0, 25); 

  btSerial.begin (57600);
  delay(500);
}


void loop() {
  //tem coisa pra eu ler?
  if (btSerial.available()){
    byte temp = btSerial.read();
    if (temp == START){
      executarComando();
    }else{
      comando = temp;
    }
  }
}

void executarComando (){
  switch(comando){
    case FRENTE: 
        for (int i = 0; i < vezes; i++){
          andarFrente(tempo); 
        }
        break;
    case DIREITA:
        for (int i = 0; i< vezes; i++){
          girarDireita(tempo);
        } 
        break;
    case ESQUERDA:
        for (int i = 0; i< vezes; i++){
           girarEsquerda(tempo);
        }
        break;
    case SELECT:
        for (int i =0; i < 1; i++){
          tchau(tempo*4);        
        }
  }
}

void tchau (int speedms){
  BOT.move(kneeFrontRight, 130);
  BOT.animate(speedms);
  for (int i = 0; i < vezes; i++){
    BOT.move(hipFrontRight, 120);
    BOT.animate(speedms);
    BOT.move(hipFrontRight, 60);
    BOT.animate(speedms);
  }
  BOT.move(kneeFrontRight, 0);
  BOT.move(hipFrontRight, 90);
  BOT.animate(speedms);
}

void andarFrente (int speedms){
  //(nome, posicao)
  int max = 120;
  int min = 80;

  BOT.move(kneeFrontRight, 45);
  BOT.animate(speedms / 2);
  //BOT.move(hipFrontRight, 111);
  BOT.move(hipFrontRight, max);
  BOT.move(hipRearRight, min);
  BOT.move(hipRearLeft, min);
  BOT.move(hipFrontLeft, min);
  BOT.animate(speedms);
  BOT.move(kneeFrontRight, 0);
  BOT.animate(speedms / 2);

  max = 110;
  min = 70;
  //levantando joelhos opostos
  BOT.move(kneeFrontLeft, 45);
  BOT.animate(speedms / 2);
  BOT.move(hipFrontRight, max);
  //BOT.move(hipFrontRight, 104);
  BOT.move(hipRearRight, min);
  BOT.move(hipRearLeft, min);
  BOT.move(hipFrontLeft, max);
  BOT.animate(speedms);
  BOT.move(kneeFrontLeft, 0);
  BOT.animate(speedms / 2);

  max = 100;
  min = 60;
  //levantando joelhos opostos
  BOT.move(kneeRearLeft, 45);
  BOT.animate(speedms / 2);
  //BOT.move(hipFrontRight, 97);
  BOT.move(hipFrontRight, max);
  BOT.move(hipRearRight, min);
  BOT.move(hipRearLeft, max);
  BOT.move(hipFrontLeft, max);
  BOT.animate(speedms);
  BOT.move(kneeRearLeft, 0);
  BOT.animate(speedms / 2);

  max = 90;
  BOT.move(kneeRearRight, 45);
  BOT.animate(speedms / 2);
  BOT.move(hipFrontRight, max);
  BOT.move(hipRearRight, max);
  BOT.move(hipRearLeft, max);
  BOT.move(hipFrontLeft, max);
  BOT.animate(speedms);
  BOT.move(kneeRearRight, 0);
  BOT.animate(speedms / 2);

}

void girarEsquerda (int speedms){
  BOT.move(hipFrontRight, 70);
  BOT.move(hipFrontLeft, 110);

  BOT.move(hipRearRight, 70);
  BOT.move(hipRearLeft, 110);

  //arruma pata direita dianteira
  BOT.move(kneeFrontRight, 45);
  BOT.animate(speedms / 2);
  BOT.move(hipFrontRight, 90);
  BOT.animate(speedms);
  BOT.move(kneeFrontRight, 0);
  BOT.animate(speedms/2);

  //arruma pata esquerda traseira
  BOT.move(kneeRearLeft, 45);
  BOT.animate(speedms / 2);
  BOT.move(hipRearLeft, 90);
  BOT.animate(speedms);
  BOT.move(kneeRearLeft, 0);
  BOT.animate(speedms/2);

  //arruma pata esquerda dianteira
  BOT.move(kneeFrontLeft, 45);
  BOT.animate(speedms / 2);
  BOT.move(hipFrontLeft, 90);
  BOT.animate(speedms);
  BOT.move(kneeFrontLeft, 0);
  BOT.animate(speedms/2);
  
  //arruma pata direita traseira
  BOT.move(kneeRearRight, 45);
  BOT.animate(speedms / 2);
  BOT.move(hipRearRight, 90);
  BOT.animate(speedms);
  BOT.move(kneeRearRight, 0);
  BOT.animate(speedms/2);
}

void girarDireita (int speedms){
  BOT.move(hipFrontRight, 110);
  BOT.move(hipFrontLeft, 70);

  BOT.move(hipRearRight, 110);
  BOT.move(hipRearLeft, 70);

  //arruma pata direita dianteira
  BOT.move(kneeFrontRight, 45);
  BOT.animate(speedms / 2);
  BOT.move(hipFrontRight, 90);
  BOT.animate(speedms);
  BOT.move(kneeFrontRight, 0);
  BOT.animate(speedms/2);

  //arruma pata esquerda traseira
  BOT.move(kneeRearLeft, 45);
  BOT.animate(speedms / 2);
  BOT.move(hipRearLeft, 90);
  BOT.animate(speedms);
  BOT.move(kneeRearLeft, 0);
  BOT.animate(speedms/2);

  //arruma pata esquerda dianteira
  BOT.move(kneeFrontLeft, 45);
  BOT.animate(speedms / 2);
  BOT.move(hipFrontLeft, 90);
  BOT.animate(speedms);
  BOT.move(kneeFrontLeft, 0);
  BOT.animate(speedms/2);
  
  //arruma pata direita traseira
  BOT.move(kneeRearRight, 45);
  BOT.animate(speedms / 2);
  BOT.move(hipRearRight, 90);
  BOT.animate(speedms);
  BOT.move(kneeRearRight, 0);
  BOT.animate(speedms/2);
}


