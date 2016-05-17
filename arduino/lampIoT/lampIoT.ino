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
// switchLeftGraph: notice if save to variable left
#include <ArduinoJson.h>
#include <MsTimer2.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
# define portSer 115200
#define CHA 3
int pinLed =13;
int pinLedMotion =12;
long analogSound = 20;
int numClap =0;
boolean stateLight = LOW ;
int index=0;
int checkIndexInGraph;
int motionPin = 4;
int switchLeftGraph =1;

int leftGraph[6],rightGraph[6];
int indexLeft=0,indexRight=0;
int countTopLeftGraph=0,countTopRightGraph=0;
int maxLeftGraph=0,maxRightGraph=0;
int matchGraph=1;
int sumLeft=0,sumRight=0;
int passiveInfrared=1;


//Variable WIFI

SoftwareSerial ser(10, 11); //RX=10,TX=11
const String ssid ="TungTruong";
const String pass = "cohangxom@321";
const String linkAPISensor = "127.0.0.1";

const String idlamp="TriLamp1";

void setupWifi(){
      ser.begin(portSer);
      ser.println("AT+CWMODE=1\n");
      ser.println("AT+CWJAP=\""+ ssid +"\",\""+pass+"\"\r\n"); 
      ser.println("AT+RST");
 

}
void upData(){
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += linkAPISensor;
  cmd += "\",8000";
  ser.println(cmd);
  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }
  String getStr = "GET /api-post/?sound=30";
//  getStr+=analogSound;
  getStr+="&passiveInfrared=40";
//  getStr+=passiveInfrared;
  getStr+="&idlamp=123abcd";
//  getStr+=idlamp;
  getStr += "\r\n\r\n";
  //Send length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);

  if(ser.find(">")){
    ser.print(getStr);
  }
  else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }

  delay(3000);
  //Send data
}


void getData(){
  Serial.println("AT+CIPMUX=0"); // set to single connection mode
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += linkAPISensor;
  cmd += "\",8000";
  Serial.println(cmd);
  //lcdSerial.println(cmd);
  if(Serial.find("Error")) return;
  
  cmd = "GET /apiusers/";
//  cmd += LOCATIONID;
//  cmd +=".json";
  cmd += " HTTP/1.1\r\nHost: "+linkAPISensor+"\r\n\r\n";
  Serial.print(F("AT+CIPSEND="));
  Serial.println(cmd.length());
  if(Serial.find(">")){
    //lcdSerial.print(">");
  }else{
    Serial.println(F("AT+CIPCLOSE"));
    delay(1000);
    return;
  }
  Serial.print(cmd);
  
}




void setup() {
  // put your setup code here, to run once:
  Serial.begin(portSer); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  setupWifi();
  pinMode(CHA, INPUT_PULLUP);
  pinMode(motionPin, INPUT_PULLUP);
  pinMode(pinLed,OUTPUT);  
  pinMode(pinLedMotion,OUTPUT);  
  // Active clap clap to enable led
  attachInterrupt(1, encoder, RISING); 
  
  MsTimer2::set(100, saveAnalogSound); // 5ms period
  MsTimer2::start();
}

void loop() {
  if (ser.available()) {
    Serial.write(ser.read());
  }
  if (Serial.available()) {
    ser.write(Serial.read());
  }
  upData();
}


void encoder()
  {
      analogSound+=1;
  }
int checkClap(int Amp){
  
}
int checkTop(int graph[6],int *maxGraph,int indexGraph){
  if(graph[indexGraph]>graph[indexGraph-1])*maxGraph=graph[indexGraph];
  return (index>=3 && (graph[indexGraph-2]<graph[indexGraph-1]&&graph[indexGraph]<graph[indexGraph-1]));
}
void processAnalogSound(int analogSound,int *countTop,int *indexGraph,int *maxGraph,int *sumGraph,int graph[6]){
    if(*indexGraph<6){
       // Serial.println("Dang xu ly");
           if(*indexGraph>0){      
             if(*countTop>1) matchGraph=0;
             else{
                if(checkTop(graph,maxGraph,*indexGraph)){
                  *maxGraph=graph[(*indexGraph)-1];
                  (*countTop)++;
                }
                
                graph[(*indexGraph)++]=analogSound;
                checkIndexInGraph= index;
                *sumGraph+=analogSound;
              //  Serial.println("Save");
             }
           }
           else{
            //  Serial.println(*indexGraph);
              graph[(*indexGraph)++]=analogSound;
              checkIndexInGraph= index;
              *sumGraph+=analogSound;
              *maxGraph=analogSound;
             // Serial.println(*indexGraph);
           }
    }
    else matchGraph=0;
}

void resetValue(){
  indexLeft=0;
  indexRight=0;
  matchGraph=1;
  switchLeftGraph=1;
  countTopRightGraph=0;
  countTopLeftGraph=0;
  maxLeftGraph=0;
  maxRightGraph=0;
  sumLeft=0;
  sumRight=0;

}
int isMatch(){
  return analogSound==0&&switchLeftGraph==0&&matchGraph&& abs(maxLeftGraph - maxRightGraph)<750 && indexLeft>1&& indexLeft<6&&indexRight>1&&indexRight<6&&index-checkIndexInGraph==1&&(sumLeft+sumRight)>1000&&(sumLeft+sumRight)<2800; 
}
void resetIndex(){
  index=0;
}
void saveAnalogSound()
{
  index ++;
 // Serial.println(analogSound);
  if(analogSound <1000 && analogSound >0&& matchGraph){
    if((index-checkIndexInGraph)<=4&&(index-checkIndexInGraph)>1&&switchLeftGraph==1){
      switchLeftGraph=0;
    }
    if(switchLeftGraph) processAnalogSound(analogSound,&countTopLeftGraph,&indexLeft,&maxLeftGraph,&sumLeft,leftGraph);
    else  processAnalogSound(analogSound,&countTopRightGraph,&indexRight,&maxRightGraph,&sumRight,rightGraph);
  }
  
  if(matchGraph==0||((index-checkIndexInGraph)>4)){
    resetValue();
  }
  if(isMatch()){
    Serial.println("Begin1");
    for(int i=0;i<indexLeft;i++){
      Serial.println(leftGraph[i]);
    }
    Serial.println("End1");
    Serial.println("Begin2");
    for(int i=0;i<indexRight;i++){
      Serial.println(rightGraph[i]);
    }
    Serial.println("End2");
    stateLight=!stateLight;
    digitalWrite(pinLed,stateLight);
    resetValue();
  }

  analogSound=0;
  if(index>30000) resetIndex();
}
