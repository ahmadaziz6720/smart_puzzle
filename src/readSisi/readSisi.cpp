#include "readSisi.h"
#include <Arduino.h>

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
  char sides[5] = {'A', 'B', 'C', 'D', 'E'};
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
      huruf_int+= mux1->read(index*5+i)* power(2, i);
    }
  }
  else{
    index -= 3;
    for(int i=0;i<5;i++){
      huruf_int+= mux2->read(index*5+i)* power(2, i);
    }
  }
  
  
  
  if(huruf_int == 0 || huruf_int > 26){
    return ' ';
  }
  return int_to_char[huruf_int-1];
}



