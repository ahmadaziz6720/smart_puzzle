#ifndef WARNASISI_H
#define WARNASISI_H

#include <Arduino.h>
#include <RGBLed.h>

extern int pinCA;
extern int pinCB;
extern int pinCC;
extern int pinCD;
extern int pinCE;
extern int pinRed;
extern int pinGreen;
extern int pinBlue;

#define INTERVAL 1
#define SISI_COUNT_MAX 5


extern String red;
extern String green;
extern String blue; 

extern int jumlah_red;
extern int jumlah_green;
extern int jumlah_blue;
extern unsigned long timer;


void setupWarna(char sisi, char warna, char prevWarna=' ');
void nyalaSisi();
void matiSisi();
void removeWarna(char sisi, char warna);
#endif