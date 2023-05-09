#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3
#define ditPin 4
#define dahPin 5
#define Speaker 6

const byte numChars = 64;
char recievedChars[numChars];
boolean newData = false;
int speed = 15;
int ditlength = 1.2 / speed;
int dahlength = ditlength * 3;
int tonefreq = 600;

SoftwareSerial toMega(rxPin, txPin);
void connectToMega(){
    Serial.println("Connecting to Mega...");
    while(true){
      toMega.readBytes(recievedChars, 11);
      Serial.println(".");
      delay(100);
      if(recievedChars == "Hello, uno!"){
        goto connected;
      }
    }
    connected:
    Serial.println("Connected!");
}

void setup(){
    Serial.begin(9600);
    Serial.println("Starting...");
    toMega.begin(9600); 
    pinMode(ditPin, INPUT);
    pinMode(dahPin, INPUT);
    pinMode(Speaker, OUTPUT);
    connectToMega();
}

void keydit() {
  tone(Speaker, tonefreq, ditlength);
  Serial.println("Keyed a dit");
  delay(ditlength);
  if(digitalRead(dahPin)==HIGH){
    keydit();
    delay(ditlength);
    tone(Speaker, tonefreq, dahlength);
  }
}

void keydah() {
  tone(Speaker, tonefreq, dahlength);
  delay(ditlength);
  Serial.println("Keyed a dah");
  if(digitalRead(ditPin)==HIGH){
    keydah();
    delay(ditlength);
    keydah();
  }
}

void loop(){
  
  if(digitalRead(ditPin)==HIGH){
      Serial.println("Recieved a dit");
      keydit();
  }

  if(digitalRead(dahPin)==HIGH){
      Serial.println("Recieved a dah");
      keydah();
  }
  
}

