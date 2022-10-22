#include "warnaSisi.h"


int pinCA = 13;
int pinCB = A0;
int pinCC = A1;
int pinCD = A2;
int pinCE = A3;
int pinRed = 6;
int pinGreen = 9;
int pinBlue = 10;


unsigned long currTime;
unsigned long prevTime;

char red[SISI_COUNT_MAX];
char green[SISI_COUNT_MAX];
char blue[SISI_COUNT_MAX];
char blank[SISI_COUNT_MAX];

Vector <char> nyalaRed(red);
Vector <char> nyalaGreen(green);
Vector <char> nyalaBlue(blue);
Vector <char> nyalaBlank(blank);

void setupWarna(char sisi, char warna){
  if(warna == 'R'){
    nyalaRed.push_back(sisi); 
    }
  else if(warna == 'G'){
    nyalaGreen.push_back(sisi);
  }
  else if(warna == 'B'){
    nyalaBlue.push_back(sisi);
  }
  else{
    nyalaBlank.push_back(sisi);
  }
}


void nyalaSisi(){
  for(int i=0; i<nyalaRed.size(); i++){
    pilihSisi(nyalaRed[i]);
    pilihWarna('R');
    prevTime = millis();
    currTime = millis();
    while((currTime - prevTime) < DELAY_TIME){
      currTime = millis();
    }
  }
  for(int i=0; i<nyalaGreen.size(); i++){
    pilihSisi(nyalaGreen[i]);
    pilihWarna('G');
    prevTime = millis();
    currTime = millis();
    while((currTime - prevTime) < DELAY_TIME){
      currTime = millis();
    }
  }

  for(int i=0; i<nyalaBlue.size(); i++){
    pilihSisi(nyalaBlue[i]);
    pilihWarna('B');
    prevTime = millis();
    currTime = millis();
    while((currTime - prevTime) < DELAY_TIME){
      currTime = millis();
    }

  }

  for(int i=0; i<nyalaBlank.size(); i++){
    pilihSisi(nyalaBlank[i]);
    pilihWarna(' ');
    prevTime = millis();
    currTime = millis();
    while((currTime - prevTime) < DELAY_TIME){
      currTime = millis();
    }

  }
  nyalaRed.clear();
  nyalaGreen.clear();
  nyalaBlue.clear();
  nyalaBlank.clear();
}




void pilihSisi (char sisi){
  if (sisi == 'A'){
    digitalWrite(pinCA, LOW);
    digitalWrite(pinCB, HIGH);
    digitalWrite(pinCC, HIGH);
    digitalWrite(pinCD, HIGH);
    digitalWrite(pinCE, HIGH);
  }
  else if (sisi == 'B'){
    digitalWrite(pinCA, HIGH);
    digitalWrite(pinCB, LOW);
    digitalWrite(pinCC, HIGH);
    digitalWrite(pinCD, HIGH);
    digitalWrite(pinCE, HIGH);
  }
  else if (sisi == 'C'){
    digitalWrite(pinCA, HIGH);
    digitalWrite(pinCB, HIGH);
    digitalWrite(pinCC, LOW);
    digitalWrite(pinCD, HIGH);
    digitalWrite(pinCE, HIGH);
  }
  else if (sisi == 'D'){
    digitalWrite(pinCA, HIGH);
    digitalWrite(pinCB, HIGH);
    digitalWrite(pinCC, HIGH);
    digitalWrite(pinCD, LOW);
    digitalWrite(pinCE, HIGH);
  }
  else if (sisi == 'E'){
    digitalWrite(pinCA, HIGH);
    digitalWrite(pinCB, HIGH);
    digitalWrite(pinCC, HIGH);
    digitalWrite(pinCD, HIGH);
    digitalWrite(pinCE, LOW);
  }
}

void pilihWarna (char warna){
  if (warna == 'R'){
    digitalWrite (pinRed,HIGH);
    digitalWrite (pinGreen,LOW);
    digitalWrite (pinBlue,LOW);
  }
    else if (warna == 'G'){
    digitalWrite (pinRed,LOW);
    digitalWrite (pinGreen,HIGH);
    digitalWrite (pinBlue,LOW);
  }
    else if (warna == 'B'){
    digitalWrite (pinRed,LOW);
    digitalWrite (pinGreen,LOW);
    digitalWrite (pinBlue,HIGH);
  }
  else if (warna == ' '){
    digitalWrite (pinRed,LOW);
    digitalWrite (pinGreen,LOW);
    digitalWrite (pinBlue,LOW);
  }
  
 }