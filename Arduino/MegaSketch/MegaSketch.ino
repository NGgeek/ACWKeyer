#include <genieArduino.h>
#define screentone 1
#define screenspeed 0
#define toUno Serial2

const byte numChars = 64;
char recievedChars[numChars];
char recievedData;
boolean newData = false;
int speed = 15;
int ditlength = 1.2 / speed;
int dahlength = ditlength * 3;
int tonefreq = 600;

Genie genie;
#define RESETLINE 4


void myGenieEventHandler(void){
  genieFrame Event;
  genie.DequeueEvent(&Event);
  

  if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_SLIDER, screentone))
  {
    tonefreq = genie.GetEventData(&Event);
    genie.WriteObject(GENIE_OBJ_LED_DIGITS, screentone, tonefreq);
    sendfreq();
  }
  if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_SLIDER, screenspeed))
  {
    speed = genie.GetEventData(&Event);
    genie.WriteObject(GENIE_OBJ_LED_DIGITS, screenspeed, speed);
    sendspeed();
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(200000);
  genie.Begin(Serial1);
  toUno.begin(9600);

  genie.AttachEventHandler(myGenieEventHandler);

  pinMode(RESETLINE, OUTPUT);
  digitalWrite(RESETLINE, 0);
  delay(100);
  digitalWrite(RESETLINE, 1);
  
  genie.WriteContrast(1);
  Serial.println("Starting....");
  genie.WriteStr(0, GENIE_VERSION);
  delay(3000);
  Serial.println("Connecting to Uno");
  toUno.println("Hello, uno!");
  Serial.println("Hello, World!");
  Serial.println("Beginning");
}


void loop() {
  genie.WriteObject(GENIE_OBJ_LED_DIGITS, screenspeed, speed);
  genie.WriteObject(GENIE_OBJ_LED_DIGITS, screentone, tonefreq);
  genie.DoEvents();

}
void sendspeed(){
  Serial.println("Sending updated speed");
  toUno.println("<speed: >");
  recWithEndMarker();
  if(recievedChars == "go" ){
    Serial.println("Recieved conf from uno");
    toUno.println(speed);
  }
  
}
void sendfreq(){
  Serial.println("Sending updated freq");
  toUno.println("<freq: >");
  recWithEndMarker();
  if(recievedChars == "go" ){
    Serial.println("Recieved Conf from uno");
    toUno.println(tonefreq);
  }
}

int recWithEndMarker() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    
    while (toUno.available() > 0 && newData == false) {
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