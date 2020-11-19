///////////////////////
//                   //
//  table LED strip  //
//    controller     //
//       nòva        //
//      Raffons      //
//     Dicroico      //
//                   //
///////////////////////

// QUANDO I PIN ANALOG SONO ALTO (255), I LED SONO SPENTI !

#define bluePin A0
#define greenPin A1
#define redPin A2

#define button 2

const int shortPressTime = 1500;
const int longPressTime = 3000;
const int threshold = 1;
const long interval = 1000;           // interval at which to blink (milliseconds)

unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;

int lastState = LOW;  
int currentState;  
long pressDuration;
int flag;  
int loopFlag;
 
int r0 = 255; int g0 = 58; int b0 = 44; //red
int r1 = 250; int g1 = 100; int b1 = 200; //violet
int r2 = 243; int g2 = 189; int b2 = 72; //yellow
int r3 = 0; int g3 = 0; int b3 = 255; //blue

void setup() {
  // set the digital pin as output:
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(button, INPUT);
  SetColor(250,100,200);
}

void loop() {
    currentState = digitalRead(button);
    if(lastState == LOW && currentState == HIGH) {        // button is pressed
      pressedTime = millis(); }
    else if(lastState == HIGH && currentState == LOW) { // button is released
      releasedTime = millis();
      pressDuration = releasedTime - pressedTime;

      if( pressDuration > longPressTime ) {
        loopcol();  
        loopFlag = 1; }// se ho premuto il pulsante per più tempo
      else if( pressDuration > shortPressTime ) {
        flag = fixcol(flag);  
        loopFlag = 0; }// se ho premuto il pulsante per più tempo
      else if ( pressDuration > threshold ) {
         shutoff();  
         loopFlag = 0; }// se ho premuto il pulsante per poco tempo 
    }

    if ( loopFlag == 1 ) { 
      loopcol(); 
    }
    lastState = currentState; // save the the last state 
}

void SetColor(int red, int green, int blue) {
  analogWrite(redPin, 255-red);
  analogWrite(greenPin, 255-green);
  analogWrite(bluePin, 255-blue);  
}

void loopcol() {
  SetColor(r0,g0,b0);
  delay(interval);
  SetColor(r1,g1,b1);
  delay(interval);
  SetColor(r2,g2,b2);
  delay(interval);
  SetColor(r3,g3,b3);
  delay(interval);
}

int fixcol(int flag) {
  if (flag == 0) 
    { 
      SetColor(r0,g0,b0);
      flag = flag +1;
      return flag;
    }
   else if (flag == 1) 
    { 
      SetColor(r1,g1,b1);
      flag = flag +1;
      return flag;
    }
   else if (flag == 2) 
    { 
      SetColor(r2,g2,b2);
      flag = flag +1;
      return flag;
    }
   else if (flag == 3) 
    { 
      SetColor(r3,g3,b3);
      flag = 0;
      return flag;
    }
}

void shutoff() {
  SetColor(0,0,0);
}
