#include "Cube.h"

int pinCA = 6;
int pinCB = 7;
int pinCC = 8;
int pinCD = 9;
int pinCE = 10;
int pinRed = 3;
int pinGreen = 4;
int pinBlue = 5;

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

 
char int_to_char[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

readSisi::readSisi(MUX74HC4067 *mux1, MUX74HC4067 *mux2){
  this->mux1 = mux1;
  this->mux2 = mux2;
}

int power(int a,int b){
  int result = 1;
  for(int i=0;i<b;i++){
    result *= a;
  }
  return result;
}

char readSisi::getCharacter(char sisi){
  char sides[5] = {'a', 'b', 'c', 'd', 'e'};
  int index = 0;

  // Mengkonvert huruf parameter abcde menjadi angka 012345, index
  for(int i = 0; i < 5; i++){
    if(sisi == sides[i]){
      index = i;
    }
  }

  int huruf_int=0;
  if(index < 3){
    // read data 5 bit per sisi
    for(int i=0;i<5;i++){
      huruf_int+= mux1->read(index*5+i+1)* power(2, i);
    }
  }
  else{
    index -= 3;
    for(int i=0;i<5;i++){
      huruf_int+= mux2->read(index*5+i+1)* power(2, i);
    }
  }
  
  
  
  if(huruf_int == 0 || huruf_int > 26){
    return ' ';
  }
  return int_to_char[huruf_int-1];
}



