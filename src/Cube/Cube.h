#ifndef CUBE_H
#define CUBE_H
#include <Arduino.h>
#include <Vector.h>
#include <MUX74HC4067.h>

class readSisi{
    private:
        MUX74HC4067 *mux1;
        MUX74HC4067 *mux2;
    public:
        readSisi(MUX74HC4067 *mux1, MUX74HC4067 *mux2);
        char getCharacter(char sisi);
};

extern int pinCA;
extern int pinCB;
extern int pinCC;
extern int pinCD;
extern int pinCE;
extern int pinRed;
extern int pinGreen;
extern int pinBlue;

#define DELAY_TIME 1
#define SISI_COUNT_MAX 5

extern unsigned long currTime;
extern unsigned long prevTime;

extern char red[SISI_COUNT_MAX];
extern char green[SISI_COUNT_MAX];
extern char blue[SISI_COUNT_MAX];
extern char blank[SISI_COUNT_MAX];

void setupWarna(char sisi, char warna);
void nyalaSisi();
void pilihSisi(char sisi);
void pilihWarna(char warna);

#endif