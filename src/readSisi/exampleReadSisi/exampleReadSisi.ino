#include "readSisi.h"
#include "MUX74HC4067.h"
int Signal1 = 8; int Signal2 = 6;int i; int SW = 4;
int pot = A0; int potVal;
 MUX74HC4067 mux1(7, 12, 11, 10, 9);
 MUX74HC4067 mux2(7, 12, 11, 10, 9);

void setup()
{
  Serial.begin(9600);
  mux1.signalPin(Signal1, INPUT, DIGITAL);
  mux2.signalPin(Signal2, INPUT, DIGITAL);
}

 readSisi readsisi(&mux1, &mux2);
//=================================================
void loop()
{
  char x = readsisi.getCharacter('d');
  Serial.println(x);
}
//=================================================
