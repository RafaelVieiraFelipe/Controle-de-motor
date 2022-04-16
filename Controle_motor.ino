// inclusões wifi
// DEFINIÇÕES
#include "WiFiEsp.h" //INCLUSÃO DA BIBLIOTECA
#include "SoftwareSerial.h"//INCLUSÃO DA BIBLIOTECA

SoftwareSerial Serial1(6, 7);

char ssid[] = "iPhone"; //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO
char pass[] = "rafael2003";//VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO

int status = WL_IDLE_STATUS; //STATUS TEMPORÁRIO ATRIBUÍDO QUANDO O WIFI É INICIALIZADO E PERMANECE ATIVO
//ATÉ QUE O NÚMERO DE TENTATIVAS EXPIRE (RESULTANDO EM WL_NO_SHIELD) OU QUE UMA CONEXÃO SEJA ESTABELECIDA
//(RESULTANDO EM WL_CONNECTED)

WiFiEspServer server(80); //CONEXÃO REALIZADA NA PORTA 80

RingBuffer buf(8); //BUFFER PARA AUMENTAR A VELOCIDADE E REDUZIR A ALOCAÇÃO DE MEMÓRIA

int statusLed = LOW; //VARIÁVEL QUE ARMAZENA O ESTADO ATUAL DO LED (LIGADO / DESLIGADO)



//código para o robô

// INCLUSÃO DE BIBLIOTECAS
#include <A2a.h>

// DEFINIÇÕES DE PINOS
#define a1 5
#define a2 6
#define b1 11
#define b2 10 

#define endereco 0x08
#define tempoAtualizacao 10000
#define tempoConfirmacao 500

A2a arduinoSlave;

// DECLARAÇÃO DE FUNÇÕES
void configuraSlave();

// DECLARAÇÃO DE VARIÁVEIS
unsigned long controleTempo = 0;

bool comandoRecebido = false;

void setup() {
  Serial.begin(9600); //INICIALIZA A SERIAL
  Serial1.begin(9600); //INICIALIZA A SERIAL PARA O ESP8266
  WiFi.init(&Serial1); //INICIALIZA A COMUNICAÇÃO SERIAL COM O ESP8266
  WiFi.config(IPAddress(192,168,2,110)); // FAIXA DE IP DISPONÍVEL DO ROTEADOR

  //INÍCIO - VERIFICA SE O ESP8266 ESTÁ CONECTADO AO ARDUINO, CONECTA A REDE SEM FIO E INICIA O WEBSERVER
  if(WiFi.status() == WL_NO_SHIELD){
    while (true);
  }
  while(status != WL_CONNECTED){
    status = WiFi.begin(ssid, pass);
  }
  server.begin();
  //FIM - VERIFICA SE O ESP8266 ESTÁ CONECTADO AO ARDUINO, CONECTA A REDE SEM FIO E INICIA O WEBSERVER



  
  Serial.begin(9600);
  while (! Serial);

  arduinoSlave.begin();
  configuraSlave();
  
  }
  

void loop() {
  delay(200);
  int vel = 200;
  char comando = Serial.read();
  /*if(Serial.available()){*/
  while(comando == 'W'){ // Testar trocar os "if/else if" por "while"
      frente(vel);
      //motorAFrente(vel);
      //motorBFrente(vel);
      comando = Serial.read();
    }
  while(comando == 'S'){
        motorATraz(vel);
        
        motorBTraz(vel);
        comando = Serial.read();
    }
  while(comando == 'D'){
      girarHorario(vel);
      comando = Serial.read();
    }
  while(comando == 'A'){
      girarAnti(vel);
      comando = Serial.read();
    }
  while(comando == 'X'){
      motorParado();
      comando = Serial.read();
    }

  WiFiEspClient client = server.available(); //ATENDE AS SOLICITAÇÕES DO CLIENTE
  client.stop(); //FINALIZA A REQUISIÇÃO HTTP E DESCONECTA O CLIENTE
  //}
  /*else {
    Serial.println("sem comando");
  }*/

}

// IMPLEMENTO DE FUNÇÕES


void motorAFrente(int vel) {
  arduinoSlave.analogWireWrite(endereco, a1, vel);
  arduinoSlave.analogWireWrite(endereco, a2, LOW);
 
}

void motorATraz(int vel) {
  arduinoSlave.analogWireWrite(endereco, a1, LOW);
  arduinoSlave.analogWireWrite(endereco, a2, vel);
  
}

void motorBFrente(int vel) {
  arduinoSlave.analogWireWrite(endereco, b1, vel);
  arduinoSlave.analogWireWrite(endereco, b2, LOW);
  
}

void motorBTraz(int vel) {
  arduinoSlave.analogWireWrite(endereco, b1, LOW);
  arduinoSlave.analogWireWrite(endereco, b2, vel);
  
}

void motorParado() {
  arduinoSlave.digitalWireWrite(endereco, a1, LOW);
  arduinoSlave.digitalWireWrite(endereco, a2, LOW);
  arduinoSlave.digitalWireWrite(endereco, b1, LOW);
  arduinoSlave.digitalWireWrite(endereco, b2, LOW);
}

void girarHorario(int spd) {
  motorAFrente(spd);
  motorBTraz(spd);
}

void girarAnti(int spd) {
  motorATraz(spd);
  motorBFrente(spd);
}

void frente(int vel) {
  arduinoSlave.analogWireWrite(endereco, a1, vel);
  arduinoSlave.analogWireWrite(endereco, a2, LOW);
  arduinoSlave.analogWireWrite(endereco, b1, vel);
  arduinoSlave.analogWireWrite(endereco, b2, LOW);
}

void configuraSlave() {
  Serial.println("configurando pinMode do Arduino");
  arduinoSlave.pinWireMode(endereco, a1, OUTPUT);
  arduinoSlave.pinWireMode(endereco, a2, OUTPUT);
  arduinoSlave.pinWireMode(endereco, b1, OUTPUT);
  arduinoSlave.pinWireMode(endereco, b2, OUTPUT);
  arduinoSlave.pinWireMode(endereco, 12, OUTPUT);
  arduinoSlave.pinWireMode(endereco, 13, OUTPUT);
  arduinoSlave.pinWireMode(endereco, 8, OUTPUT);
  arduinoSlave.digitalWireWrite(endereco, 12, HIGH);
  arduinoSlave.digitalWireWrite(endereco, 13, HIGH);
  arduinoSlave.digitalWireWrite(endereco, 8, HIGH);
  Serial.println("Slave Configurado!");
}
