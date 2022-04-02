#define a1 5
#define a2 6
#define b1 11
#define b2 10 

void setup() {
  Serial.begin(9600);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(8, HIGH); // provisório, precisa ir para o pino de 5V
}

void loop() { 
  delay(200);
  int vel = 200;
  char comando = Serial.read();
  if(Serial.available()){
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
  }
  else {
    Serial.println("sem comando");
  }
}

void frente(int vel) {
  analogWrite(a1, vel);
  analogWrite(a2, LOW);
  analogWrite(b1, vel);
  analogWrite(b2, LOW);
}

void motorAFrente(int vel) {
  analogWrite(a1, vel);
  analogWrite(a2, LOW);
 
}

void motorATraz(int vel) {
  analogWrite(a1, LOW);
  analogWrite(a2, vel);
  
}

void motorBFrente(int vel) {
  analogWrite(b1, vel);
  analogWrite(b2, LOW);
  
}

void motorBTraz(int vel) {
  analogWrite(b1, LOW);
  analogWrite(b2, vel);
  
}

void motorParado() {
  analogWrite(a1, LOW);
  analogWrite(a2, LOW);
  analogWrite(b1, LOW);
  digitalWrite(b2, LOW);
}

void girarHorario(int spd) {
  motorAFrente(spd);
  motorBTraz(spd);
  
}

void girarAnti(int spd) {
  motorATraz(spd);
  motorBFrente(spd);
}
