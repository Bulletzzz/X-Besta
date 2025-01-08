#include <Servo.h>
String leituraserial;
//Criação de variaveis e designação de portas

unsigned long TI = millis();;
unsigned long TA;
unsigned long TAD = millis();
Servo left_right;
Servo up_down;
Servo atira;
int atirou = 0;
int ligado = 0;
int ligado2 = 0;
int RND = 0;
void setup()
{
  left_right.attach(3);
  up_down.attach(5);
  atira.attach(6);
  atira.write(0);
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
pinMode(2, INPUT_PULLUP);
pinMode(4, INPUT_PULLUP);
}


void loop()
//"joguinho" que atira aleatoriamente
{
while(Serial.available()){
  if(digitalRead(7) == LOW) {
    ligado = 1;
    TI = millis();
    RND = random(10,16);
    }
  while(ligado == 1){
    leituraserial = Serial.readStringUntil('\r');
    Serial.println(leituraserial);
    int eixo_x = leituraserial.substring(0, leituraserial.indexOf(',')).toInt();
    int eixo_y = leituraserial.substring(leituraserial.indexOf(',') + 1).toInt();

    int y = map(eixo_y, 0, 720, 30, 150);
    int x = map(eixo_x, 0, 1280, 150, 30);
    left_right.write(x);
    up_down.write(y);
    if (millis() - TI > RND*1000) {
      atira.write(40);
      atirou = 1;
    }
    if (millis() - TI > ((RND+0.2)*1000) && atirou == 1) {
      atira.write(0);
      atirou = 0;
      ligado = 0;
    }}


//Sistema de que segue a face e dispara apenas se o segundo botão for pressionado
    int botao = digitalRead(2);
    if (botao == LOW) {
      ligado2 = 1;
      delay(500);}
    while(ligado2 == 1) {
    leituraserial = Serial.readStringUntil('\r');
    Serial.println(leituraserial);
    int eixo_x = leituraserial.substring(0, leituraserial.indexOf(',')).toInt();
    int eixo_y = leituraserial.substring(leituraserial.indexOf(',') + 1).toInt();
    int y = map(eixo_y, 0, 720, 30, 150);
    int x = map(eixo_x, 0, 1280, 150, 30);
    left_right.write(x);
    up_down.write(y);
    if (digitalRead(4) == LOW){
      TI = millis();
      atira.write(40);
      atirou = 1;
    }
    if (((millis() - TI) > 200) && atirou == 1) {
      atira.write(0);
      atirou = 0;
  }
    botao = digitalRead(2);
    if (botao == LOW) {
      ligado2 = 0;
      delay(500);}
    }
  }
}