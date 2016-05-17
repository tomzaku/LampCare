
// Introduce with clap clap
// Clap clap will have 2 graph left and right, I sended in my folder with name graphclapclap.xml
// I have 2 leftGraph and rightGraph to make sure it was clap clap
// If clap clap 
//    Each leftGraph/rightGraph have not more 5 paragram >0
//    Summurize  of number  leftGraph/rightGraph from 650->1500
//    |Max leftGraph - Max rightGraph| <250
//    The zero between LeftGraph and rightGraph not have more 3 number
//    and finally it look like a double moutain raise up and fall down complety
//So this is my code for that

#include <stdlib.h>
#include "clapclap.h"

#define pinSound 5
#define pinLed D3
long count = 0,pretimer=0;
int timer=0;
ClapClap clapclap(pinSound,200,500,100);

int analogSound=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinSound, INPUT_PULLUP);
  pinMode(pinLed, OUTPUT);

  attachInterrupt(5, encoder, RISING); 
  Serial.begin(115200); 
  //MsTimer2::set(100, rate); // 5ms period
    //MsTimer2::start();
}
void loop() {
      timer=millis()-pretimer;
      if(timer>=100)
        {
          if(clapclap.checkClapClap(analogSound)){
            Serial.println("Check ");
          }
          Serial.println(analogSound);
          analogSound=0;
          pretimer=millis();
          }
      
}
void encoder()
  {
      analogSound+=1;

  }

