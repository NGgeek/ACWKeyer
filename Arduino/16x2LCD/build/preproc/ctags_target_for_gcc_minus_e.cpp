# 1 "/home/nathan/Documents/School/2022-2023/TrimesterIII/Engineering/JuniorProject/ACWKeyer/Arduino/16x2LCD/16x2LCD.ino"
# 2 "/home/nathan/Documents/School/2022-2023/TrimesterIII/Engineering/JuniorProject/ACWKeyer/Arduino/16x2LCD/16x2LCD.ino" 2







int speed = 15;
int ditlength = 1.2 / speed;
int datlength = ditlength * 3;
int tonefreq = 600;
int menu = 1;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(7, 0x0);
  pinMode(6, 0x0);
  pinMode(8, 0x1);
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
  tone(8, tonefreq, ditlength);
  delay(ditlength);
}
void dat(){
  tone(8, tonefreq, datlength);
  delay(ditlength);
}
void loop() {
  updatemenu();
  if(digitalRead(7) == 0x1){
    if(digitalRead(6) == 0x1) {
      dit();
      dat();
    }
    else{
      dit();
    }

  if(digitalRead(6) == 0x1){
    if(digitalRead(7) == 0x1){
      dat();
      dit();
    }
    else{
      dat();
    }
  }
  if(digitalRead(9) == 0x1){
    menu++;
    updatemenu();
  }
  if(digitalRead(10) == 0x1){
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
