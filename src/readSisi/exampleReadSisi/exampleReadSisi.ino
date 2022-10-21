#include "readSisi.h"
#include "MUX74HC4067.h"
int Signal1 = 11; int Signal2 = 12; int i; int SW = 4;
 MUX74HC4067 mux1(A4, 4, 5, 7, 8);
 MUX74HC4067 mux2(A5, 4, 5, 7, 8);

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
