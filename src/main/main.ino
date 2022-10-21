#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"
#include "readSisi.h"
#include "warnaSisi.h"

#define JUMLAH_SISI 5
#define ch_MAX 26

DFRobotDFPlayerMini player;


// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX 
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);


int Signal1 = 11; int Signal2 = 12; int i; int SW = 4;
MUX74HC4067 mux1(A4, 4, 5, 7, 8);
MUX74HC4067 mux2(A5, 4, 5, 7, 8);


bool newGame = true;
bool correct = false;
    
readSisi readsisi(&mux1, &mux2);
char side_done_storage[JUMLAH_SISI];
Vector<char> side_done(side_done_storage);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  softwareSerial.begin(9600);
  
  mux1.signalPin(Signal1, INPUT, DIGITAL);
  mux2.signalPin(Signal2, INPUT, DIGITAL);

  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  pinMode(pinCA, OUTPUT);
  pinMode(pinCB, 
  OUTPUT);
  pinMode(pinCC, OUTPUT);
  pinMode(pinCD, OUTPUT);
  pinMode(pinCE, OUTPUT);
  digitalWrite(pinCA, HIGH);
  digitalWrite(pinCB, HIGH);
  digitalWrite(pinCC, HIGH);
  digitalWrite(pinCD, HIGH);
  digitalWrite(pinCE, HIGH);

  if (!player.begin(softwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));  
  player.volume(100);  //Set volume value. From 0 to 30
}

// voice list

// yey kubus sudah terbentuk
// 1-2 -> yeey! kubus sudah terbentuk

// Masukkan "alfabet" ke "warna"
// 3-7 -> A (biru, hijau, kuning, merah, oranye)
// 8-12 -> B
// ....
// (22-1)*5+2+1-22*5+2 -> 108-112 -> V


// tepat sekali, keren


// coba lagi ya


// Selamat kamu berhasil menyelesaikan puzzle


// Biru, kuning, hijau, dll


// A-Z


void loop() {
  // biru -> sisi A
  // hijau -> sisi B
  // kuning -> sisi C
  // merah -> sisi D
  // oranye -> sisi E

  while(newGame){
    static unsigned long timer = millis();
    char side = 'A';

    setupWarna(side, 'B');
    nyalaSisi();
    char letter = 'b';

    player.play(voiceId(side, letter));
    player.pause();


    // blocking
      while(!correct){
        checkSide(side, letter);
      }
    newGame = false;
  }

}







void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

void checkSide(char side, char letter){
  correct = (readsisi.getCharacter(side) == letter);
}


char pickRandSide(){
  char alpha[ch_MAX] = { 'A', 'B', 'C', 'D', 'E' };
                          
  char result;
  result =  alpha[rand() % ch_MAX];
  
  side_done.push_back(result);
  int i=0;
  while(i<JUMLAH_SISI){
    if(result == side_done[i]){
      result=alpha[rand() % ch_MAX];
      i=0;
    }
    i++;
  }


  return result;
}

char pickRandLetter()
{
    char alpha[ch_MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };
    char result;
        result =  alpha[rand() % ch_MAX];

    return result;
}


int voiceId(char side, char letter){
   char sides[] = {'A', 'B', 'C', 'D', 'E'};
   char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
   int side_index = 0;
   int letter_index = 0;

   
   for(int i = 0; i < 5; i++){
    if(side == sides[i]){
      side_index = i+1;
    }
  }

   for(int i = 0; i < ch_MAX; i++){
    if(letter == letters[i]){
      letter_index = i+1;
    }
  }
  // (22-1)*5+2+1-22*5+2 -> 108-112 -> V

  int id_voice = ((letter_index) * 5) + 2 + side_index;
  return id_voice;
  
}
