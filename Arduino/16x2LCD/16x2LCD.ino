#include <LiquidCrystal.h>

#define speaker 8
#define ditpin 7
#define datpin  6
#define scrollbutton 9
#define upbutton 10

int speed = 15;
int ditlength = 1.2 / speed;
int datlength = ditlength * 3;
int tonefreq = 600;
int menu = 1;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(ditpin, INPUT);
  pinMode(datpin, INPUT);
  pinMode(speaker, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Hello, World!");
  delay(2000);
  lcd.clear();
}

void updatemenu() {
  switch(menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.print(">Speed: ");
      lcd.setCursor(9,0);
      lcd.print(speed);
      lcd.setCursor(0,1);
      lcd.print(" Tone: ");
      lcd.setCursor(8,1);
      lcd.print(tonefreq);
      break;
    case 2:
      lcd.clear();
      lcd.print(" Speed: ");
      lcd.setCursor(9,0);
      lcd.print(speed);
      lcd.setCursor(0,1);
      lcd.print(">Tone: ");
      lcd.setCursor(8,1);
      lcd.print(tonefreq);
    case 3:
      menu = 1;
      break;

  }
}

void dit(){
  tone(speaker, tonefreq, ditlength);
  delay(ditlength);
}
void dat(){
  tone(speaker, tonefreq, datlength);
  delay(ditlength);
}
void loop() {
  updatemenu();
  if(digitalRead(ditpin) == HIGH){
    if(digitalRead(datpin) == HIGH) {
      dit();
      dat();
    }
    else{
      dit();
    }
  
  if(digitalRead(datpin) == HIGH){
    if(digitalRead(ditpin) == HIGH){
      dat();
      dit();
    }
    else{
      dat();
    }  
  }
  if(digitalRead(scrollbutton) == HIGH){
    menu++;
    updatemenu();
  }
  if(digitalRead(upbutton) == HIGH){
    switch(menu){
      case 1:
        if(speed<150){
          speed = speed + 5;
        }
        else if(speed>=150){
          speed = 15;
        }
      case 2:
        if(tonefreq<1000){
          tonefreq = tonefreq + 25;
        }
        else if(tonefreq>=1000){
          tonefreq = 300;
        }
    }
    updatemenu();
  }
}
}

