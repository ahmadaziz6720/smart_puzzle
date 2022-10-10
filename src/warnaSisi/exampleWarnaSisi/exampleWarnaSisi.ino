#include <warnaSisi.h>



void setup() {
  Serial.begin(9600);
  pinMode(pinRed,OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  pinMode(pinCA,OUTPUT);
  pinMode(pinCB, OUTPUT);
  pinMode(pinCC, OUTPUT);
  pinMode(pinCD, OUTPUT);
  pinMode(pinCE, OUTPUT);
  digitalWrite(pinCA,HIGH);
  digitalWrite(pinCB,HIGH);
  digitalWrite(pinCC,HIGH);
  digitalWrite(pinCD,HIGH);
  digitalWrite(pinCE,HIGH);
}


void loop() {
  setupWarna('A', 'R');
  setupWarna('B', 'B');
  setupWarna('C', 'G');
  setupWarna('D', 'B');
  setupWarna('E', 'G');

  nyalaSisi();
}
