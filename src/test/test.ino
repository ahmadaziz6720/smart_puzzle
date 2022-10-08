#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX 
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

void setup() {
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);

    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);

    pinMode(12, INPUT);
    pinMode(11, INPUT);

    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT); //pwm
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT); //pwm
    pinMode(10, OUTPUT); //pwm
    pinMode(13, OUTPUT);

    Serial.begin(9600);
    softwareSerial.begin(9600);
    if (player.begin(softwareSerial)) {
      Serial.println("OK");
      player.volume(100);
      player.play(2);
      delay(5000);
      player.next();
    } else {
      Serial.println("Connecting to DFPlayer Mini failed!");
    }
}

void loop() {
  player.next();
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);

  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  analogWrite(6, 100);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  analogWrite(9, 100);
  analogWrite(10, 100);
  digitalWrite(13, HIGH);

  delay(1000);
  
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);

  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  analogWrite(6, 10);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  analogWrite(9, 10);
  analogWrite(10, 10);
  digitalWrite(13, LOW);
  delay(1000);

  Serial.print(digitalRead(11));
  Serial.print("    ");
  Serial.println(digitalRead(12));
}
