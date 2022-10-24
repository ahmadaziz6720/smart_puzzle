#include "warnaSisi.h"


int pinCA = 13;
int pinCB = A0;
int pinCC = A1;
int pinCD = A2;
int pinCE = A3;
int pinRed = 6;
int pinGreen = 9;
int pinBlue = 10;


RGBLed led(pinRed, pinGreen, pinBlue, RGBLed::COMMON_CATHODE);

String red = "";
String green = "";
String blue = "";

int jumlah_red = 0;
int jumlah_green = 0;
int jumlah_blue = 0;  


bool isAlreadyWritten(char sisi, String nyala){
  for(int i=0;i<SISI_COUNT_MAX;i++){
    if(nyala[i] == sisi){
      return true;
    }
  }
  return false;
}


int findSisiId(char sisi, String nyala){
 for(int i=0;i<SISI_COUNT_MAX;i++){
 
    if(sisi == nyala[i]){
      return i;
    }
  }

  return -1;
}



void removeWarna(char sisi, char warna){
  int id;
  if(warna == 'R'){
    
    id = findSisiId(sisi, red);
    red.remove(id);
    jumlah_red--;
    
  }
  else if(warna == 'B'){
    id = findSisiId(sisi, blue);
    blue.remove(id);
    jumlah_blue--;
   
  }
  else if(warna == 'G'){
    id = findSisiId(sisi, green);
    green.remove(id);
    jumlah_green--;
    
   
  }
  
}


void pilihSisi (char sisi){
  if (sisi == ' '){
    return;
  }
  else if (sisi == 'A'){
    digitalWrite(pinCA, LOW);
  }
  else if (sisi == 'B'){
    digitalWrite(pinCB, LOW);
  }
  else if (sisi == 'C'){
    digitalWrite(pinCC, LOW);
  }
  else if (sisi == 'D'){
    digitalWrite(pinCD, LOW);
  }
  else if (sisi == 'E'){
    digitalWrite(pinCE, LOW);
  }
}




 void matiSisi(){
  digitalWrite(pinCA, HIGH);
  digitalWrite(pinCB, HIGH);
  digitalWrite(pinCC, HIGH);
  digitalWrite(pinCD, HIGH);
  digitalWrite(pinCE, HIGH);
}



void setupWarna(char sisi, char warna, char prevWarna = ' '){
  if(warna == 'R'){
    if(!isAlreadyWritten(sisi, red)){
       red = String(red + sisi);
       jumlah_red++;
    }
   
    }
  else if(warna == 'G'){
    if(!isAlreadyWritten(sisi, green)){
       green = String(green + sisi);
       jumlah_green++;
    }
   
  }
  else if(warna == 'B'){
    if(!isAlreadyWritten(sisi, blue)){
      blue = String(blue + sisi);
      jumlah_blue++;
    }
    
  }
  

   if(prevWarna != ' '){
     removeWarna(sisi, prevWarna);
  }
}



void nyalaSisi(){
  int timer = 0;
  if(millis()-timer > 0){
      for(int i=0; i<red.length(); i++){
        pilihSisi(red[i]);
      }
  }
  
  led.flash(RGBLed::RED, INTERVAL, 0);    
  
  matiSisi();

  if(millis()-timer > INTERVAL){
      for(int i=0; i<green.length(); i++){
        pilihSisi(green[i]);
      }
  }

  led.flash(RGBLed::GREEN, INTERVAL, 0);    

  matiSisi();

  if(millis()-timer > INTERVAL*2){
      for(int i=0; i<blue.length(); i++){
        pilihSisi(blue[i]);
      }
  }

  led.flash(RGBLed::BLUE, INTERVAL, 0); 

  matiSisi();
  
}

