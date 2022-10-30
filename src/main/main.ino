#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"
#include "readSisi.h"
#include "warnaSisi.h"
#include "Vector.h"
#include "neotimer.h"

#define JUMLAH_SISI 5
#define ch_MAX 26
#define MUX_PINS 15
DFRobotDFPlayerMini player;


// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX 
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

  
int Signal1 = 11; int Signal2 = 12; int i; int SW = 4;
MUX74HC4067 mux1(A4, 4, 5, 7, 8);
MUX74HC4067 mux2(A5, 4, 5, 7, 8);


bool gameover = true;
bool correct = false;
    
readSisi readsisi(&mux1, &mux2);
char side_done_storage[JUMLAH_SISI];
Vector<char> side_done(side_done_storage);
char char_done_storage[ch_MAX];
Vector<char> char_done(char_done_storage);
int total_side_done = 0;

int upButtonState = 0;
int lastUpButtonState = 0;
int downButtonState = 0;
int lastDownButtonState = 0;
int level = 1;

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
  pinMode(pinCB, OUTPUT);
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
#define KUBUS_TERBENTUK 1
// Masukkan "alfabet" ke "warna"
// 3-7 -> A (biru, hijau, kuning, merah, oranye)
// 8-12 -> B
// ....
// (22-1)*5+2+1-22*5+2 -> 108-112 -> V

// 128-132 -> Z

// tepat sekali, keren 133-134
#define TEPAT_SEKALI 133

// coba lagi ya 135-137
#define COBA_LAGI_YA 135

// Selamat kamu berhasil menyelesaikan puzzle 138-139
#define SELAMAT 138



void loop() {
  // biru -> sisi A
  // hijau -> sisi B
  // kuning -> sisi C
  // merah -> sisi D
  // oranye -> sisi E
  while(gameover){
    if(total_side_done == JUMLAH_SISI){
      player.play(SELAMAT);
      int prevtime = millis();
      int currtime = millis();
      while(currtime - prevtime < 5000){
        nyalaSisi();
        currtime = millis();
      }
    }
   
    total_side_done = 0;
    // pilih level
    updateGameLevel();
    // check for done building
//    Serial.println("checking done rakit");
    if(isDoneRakit()){
      reset();
      player.play(KUBUS_TERBENTUK);
      int prevtime = millis();
      int currtime = millis();
      delay(5000);
    }
  }

  char side = pickRandSide();
  char letter = pickRandLetter();
  
  setupWarna(side, 'B', ' ');
  
  nyalaSisi();
  player.play(voiceId(side, letter));

  
 
  correct = false;
  while(!correct){
    
     
    
    if(!isWaitingForInput()){
      
      checkSide(side, letter);
      if(!correct){
        setupWarna(side, 'R', 'B');
        nyalaSisi();
        for(int i =0;i<total_side_done-1;i++){
            setupWarna(side_done[i], 'G', ' ');
            nyalaSisi();
        }
        player.play(COBA_LAGI_YA);
        int prevtime = millis();
        int currtime = millis();
        while(currtime - prevtime < 2000){
          nyalaSisi();
          currtime = millis();
        }
        
      }
      else if(correct){
        Serial.println("Correct");
        setupWarna(side, 'G', 'R');
        nyalaSisi();
        for(int i =0;i<total_side_done-1;i++){
            setupWarna(side_done[i], 'G', ' ');
            nyalaSisi();
        }   
        player.play(TEPAT_SEKALI); 
        int prevtime = millis();
        int currtime = millis();
        while(currtime - prevtime <  5000){
          nyalaSisi();
          currtime = millis();
        } 
      }
    }
    nyalaSisi();
  }

   
  
      
  

}

void reset(){
  side_done.clear();
    char_done.clear();
    total_side_done = 0;
    for(int i=0;i<JUMLAH_SISI;i++){
      side_done_storage[i] = ' ';
      char_done_storage[i] = ' ';
      side_done[i] = ' ';
      char_done[i] = ' ';
    }
    gameover=false;
    matiSisi();
    removeWarna('A', 'R');
    removeWarna('B', 'R');
    removeWarna('C', 'R');
    removeWarna('D', 'R');
    removeWarna('E', 'R');
    removeWarna('A', 'G');
    removeWarna('B', 'G');
    removeWarna('C', 'G');
    removeWarna('D', 'G');
    removeWarna('E', 'G');
    removeWarna('A', 'B');
    removeWarna('B', 'B');
    removeWarna('C', 'B');
    removeWarna('D', 'B');
    removeWarna('E', 'B');

}


void updateGameLevel(){
    upButtonState = mux2.read(11);
    downButtonState = mux2.read(12);
    // compare the buttonState to its previous state
    if (upButtonState != lastUpButtonState) {
      // if the state has changed, increment the counter
      if (upButtonState == HIGH) {
        // if the current state is HIGH then the button
        // went from off to on:
        level++;
        if(level >= 5) {
          level = 5;
        }
        player.play(level+138);
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state for next time through the loop
    lastUpButtonState = upButtonState;


    if (downButtonState != lastDownButtonState) {
      // if the state has changed, increment the counter
      if (downButtonState == HIGH) {
        // if the current state is HIGH then the button
        // went from off to on:
        level--;
        
        if(level <= 1){
          level = 1;
        }
        player.play(level+138);
      }
      // Delay a little bit to avoid bouncing
      delay(100);
    }

    lastDownButtonState = downButtonState;
    
    Serial.println(level);
}

bool isDoneRakit(){
  return (mux2.read(10) != 0);
}


bool isWaitingForInput(){
  int i = 0;
  for(i=0;i<MUX_PINS;i++){
    if(mux1.read(i) != 0){
      return false;
    }
  }

  for(i=0;i<9;i++){
    if(mux2.read(i) != 0){
      return false;
    }
  }

  return true;
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
  if(readsisi.getCharacter(side) == ' '){
    correct = false;
    return;
  }
  int currtime = millis();
  int prevtime = millis();
  while(currtime - prevtime < 1000){
    correct = (readsisi.getCharacter(side) == letter);
    nyalaSisi();
    currtime = millis();
  }
  
}

char pickRandSide(){
  char alpha[JUMLAH_SISI] = { 'A', 'B', 'C', 'D', 'E' };
                          
  char result;
  result =  alpha[rand() % JUMLAH_SISI];
  
  
  int i=0;
  while(i<JUMLAH_SISI){
  Serial.println(side_done[i]);
    if(result == side_done[i]){
      result=alpha[rand() % JUMLAH_SISI];
      i=-1;
    }
    i++;
  }

  side_done.push_back(result);
  total_side_done += 1;

  if(total_side_done == JUMLAH_SISI ){
    gameover = true;
  }
  return result;
}


//char pickRandSide(){
//  char alpha[JUMLAH_SISI] = {  'D', 'E' };
//                          
//  char result;
//  result =  alpha[rand() % 2];
//  
//  
//  int i=0;
//  while(i<2){
//    if(result == side_done[i]){
//      result=alpha[rand() % 2];
//      i=-1;
//    }
//    i++;
//  }
//
//  side_done.push_back(result);
//  total_side_done += 1;
//
//  if(total_side_done == 2){
//    gameover = true;
//  }
//  return result;
//}

char pickRandLetter()
{
    char alpha[ch_MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };
    char result;
    if(level != 5){
      result =  alpha[rand() % JUMLAH_SISI + (level-1)*5];
    }
    else if(level == 5){
      result =  alpha[rand() % (JUMLAH_SISI+1) + (level-1)*5];
    }
    


    int i=0;
    while(i<ch_MAX){
      if(result == char_done[i]){
        if(level != 5){
          result =  alpha[rand() % JUMLAH_SISI + (level-1)*5];
        }
        else if(level == 5){
          result =  alpha[rand() % (JUMLAH_SISI+1) + (level-1)*5];
        }
        i=-1;
      }
      i++;
    }

    char_done.push_back(result);
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
      letter_index = i;
    }
  }
  // (22-1)*5+2+1-22*5+2 -> 108-112 -> V

  // 25*5 + 2 + 5
  int id_voice = ((letter_index) * 5) + 2 + side_index;
  return id_voice;
  
}
