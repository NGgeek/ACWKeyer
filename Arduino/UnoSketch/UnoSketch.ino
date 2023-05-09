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
    while(recievedChars != "Hello, uno!"){
        recWithEndMarker();
        Serial.print(".");
    }
}

void setup(){
    Serial.begin(9600);
    Serial.println("Starting...");
    toMega.begin(9600); 
    pinMode(ditPin, INPUT);
    pinMode(dahPin, INPUT);
    pinMode(Speaker, OUTPUT);
    connectToMega();
    Serial.println(".");
    Serial.println("Connected to Mega!");
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
    if(recievedChars == "speed: "){
        toMega.println("<go>");
        if(toMega.available() > 0) {
            speed = toMega.parseInt();
        }
        Serial.print("Changing speed to ");
        Serial.println(speed);
    }
    if(recievedChars == "freq: "){
        toMega.println("<go>");
        if(toMega.available() > 0) {
            tonefreq = toMega.parseInt();
        }
        Serial.print("Changing frequency to ");
        Serial.println(tonefreq);
    }
}

int recWithEndMarker() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    
    while (toMega.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                recievedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                recievedChars[ndx] = '\0';
                recvInProgress = true;
                ndx = 0;
                newData = true;
            }
        }    
        else if (rc == startMarker){
            recvInProgress = true;
        }   
    }
}