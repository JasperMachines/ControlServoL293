#define _CAT(a, ...) a ## __VA_ARGS__
#define SWITCH_ENABLED_false 0
#define SWITCH_ENABLED_true  1
#define SWITCH_ENABLED_0     0
#define SWITCH_ENABLED_1     1
#define SWITCH_ENABLED_0x0   0
#define SWITCH_ENABLED_0x1   1
#define SWITCH_ENABLED_      1
#define ENABLED(b) _CAT(SWITCH_ENABLED_, b)
#define DISABLED(b) !ENABLED(b)


//#define SERVO1
#define SERVO2

#if ENABLED(SERVO1)
  #define MOTORA_PIN 6   //pin de control de direccion en circuito integrado L293
  #define MOTORB_PIN 7   //pin de control de direccion en circuito integrado L293
  #define ACT_POS_PIN A6 //pin analogo, potenciometro de servo-motor
 #endif

 #if ENABLED(SERVO2)
  #define MOTORA_PIN 4    //pin de control de direccion en circuito integrado L293
   #define MOTORB_PIN 5   //pin de control de direccion en circuito integrado L293
    #define ACT_POS_PIN A2  //pin analogo, potenciometro de servo-motor
 #endif

int actualposition=0;
int centerposition=512;
int destination=0;
int destinationerror=4;
int pwmlevel=0;
//int motorpinA = 6;
//int motorpinB = 7;
//int motorpinA = 4;
//int motorpinB = 5;
int destinnationpotPin = A0;

unsigned long startmillis=0;

void setup() {

  Serial.begin(115200);
pinMode(MOTORA_PIN, OUTPUT);
pinMode(MOTORB_PIN, OUTPUT);
}

void loop() {

destination = map(analogRead(destinnationpotPin),0,1024,0,180);
//actualposition=map(analogRead(actpositionpotPin),0,1024,0,180);
#if ENABLED(SERVO1)
actualposition=map(analogRead(ACT_POS_PIN),0,1024,0,180);
#endif
#if ENABLED(SERVO2)
actualposition=map(analogRead(ACT_POS_PIN),580,1024,0,180);
#endif

Serial.print("destination= ");
Serial.print(destination);
Serial.print(" actualposition= ");
Serial.println(actualposition);

if(actualposition<destination-destinationerror  || actualposition>destination+destinationerror){

if(destination<actualposition){
  pwmlevel=constrain(map((actualposition-destination),0,90,220,250),0,255);
analogWrite(MOTORB_PIN, pwmlevel);
Serial.print("A__here_pwm_");
Serial.println(pwmlevel);
delayMicroseconds(3000);
analogWrite(MOTORB_PIN, 0);
//delay(10);                       //cambia la velocidad de posicionamiento
}

if(destination>actualposition){
  
   pwmlevel=constrain(map((destination-actualposition),0,90,220,250),0,255);
analogWrite(MOTORA_PIN, pwmlevel);
Serial.print("B__here_pwm_");
Serial.println(pwmlevel);
delayMicroseconds(3000);
analogWrite(MOTORA_PIN, 0);
//delay(10);                   //cambia la velocidad de posicionamiento

}

}


}
