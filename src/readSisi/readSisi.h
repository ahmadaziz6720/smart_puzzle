#ifndef READSIDES_h
#define READSIDES_h

#include "Arduino.h"
#include "MUX74HC4067.h"


class readSisi{
    private:
        MUX74HC4067 *mux1;
        MUX74HC4067 *mux2;
    public:
        readSisi(MUX74HC4067 *mux1, MUX74HC4067 *mux2);
        char getCharacter(char sisi);
};


#endif