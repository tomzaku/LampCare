
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

#include "clapclap.h"
#include "Ticker.h"
//WIFI

#include <ESP8266WiFi.h>
#include <GDBStub.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>


#define USE_SERIAL Serial
const char* ssid[] = {"TungTruong","Molly coffee T1"};
const char* password[] = {"cohangxom@321","111111111"};

const int wifiIndex = 0;
//ENDWIFI


//LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
// D6 sda ; D7 SCL

//ENDLCD


struct TimeLamp{
  int hours;
  int minutes;
  int seconds;
};
TimeLamp *_timeLamp; 

#define pinPassiveInfrared D4

#define pinSound 5
#define pinLed D3
long count = 0,pretimerClapClap=0,timerCount=0;
int timerClapClap=0;
int timeSendData=0;
ClapClap clapclap(pinSound,110,350,100);

int analogSound=0;
int stateLed = HIGH;

Ticker ticker;

void setupLCD(){
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Hello TomLe");
}


void setupWifi(){
    Serial.println();
    Serial.println();
    Serial.println();
    for(uint8_t t = 4; t > 0; t--) {
      Serial.printf("[SETUP] WAIT %d...\n", t);
      Serial.flush();
      delay(1000);
    }
    Serial.println(ssid[wifiIndex]);
    Serial.println(password[wifiIndex]);
     WiFi.begin(ssid[wifiIndex], password[wifiIndex]);
     while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("......");
      }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
 // setupWifi();
 // setupLCD();
 // getData();
  
  pinMode(pinSound, INPUT_PULLUP);
  pinMode(pinLed, OUTPUT);
  pinMode(pinPassiveInfrared,INPUT_PULLUP);
  attachInterrupt(5, encoder, RISING); 
  ticker.attach(0.1,timeClapClap)  ;
  ticker.attach(1.0,increaseSecond);
}

void increaseSecond(){
  if(++_timeLamp->seconds>60){
    _timeLamp->seconds =0;
    if(++_timeLamp->minutes>60){
      _timeLamp->minutes = 0;
      if(++_timeLamp->hours>23){
        _timeLamp->hours =0;
      }
    }
  }
  USE_SERIAL.println(">>>");
  USE_SERIAL.println(_timeLamp->seconds);
  
}

void loop() {
   
      
}

void timeClapClap(){
  USE_SERIAL.println(analog);

  if(clapclap.checkClapClap(analogSound)){
      stateLed = !stateLed;
      pinMode(pinLed,stateLed);
  }
  timerCount++;
  if(timerCount%100==0){
      postSensorData(analogSound,digitalRead(pinPassiveInfrared));
  }

    analogSound=0;
}



void postSensorData(int analogSound,int digitalPI){
 Serial.printf(">>>>> %d, %d\n",analogSound,digitalPI);
// HTTPClient httpSensor;
// httpSensor.begin("http://skymarsch.xyz/api/users/");
//// httpSensor.setAuthorization("tomle","newlife1");
// httpSensor.addHeader("Content-Type", "application/json");
// String payload  = "{\"sound\":33,\"passiveInfrared\":1,\"lamp\":1}";
// String payload1 = "{\"email\":\"sadsadasdqweewq@gmail.com\",\"username\":\"thienkhonggay\",\"first_name\":\"Tri\",\"last_name\":\"le\",\"password\":\"thien123\",\"confirm_password\":\"thien123\"}";
// Serial.println(payload1);
// int httpCode = httpSensor.POST(payload1);
// Serial.println("<<<<<<>>>>");
// Serial.println(httpCode);
}

void getSensorMethod(int analogSound,int digitalPI){
  
}

void getData(){
      // wait for WiFi connection

    if(WiFi.status()== WL_CONNECTED) {
        int count=0;
        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        char* url = "http://45.55.140.232:9900/api-time/datetime/?format=json";
        Serial.printf("GET url = ");
        Serial.println(url);
        http.begin("http://45.55.140.232:9900/api-time/datetime/?format=json"); //HTTP
        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                char editedJson[payload.length()];

                for(int i=0;i<payload.length();i++){
                  if(payload[i]!='\n'&&payload[i]!='\t'&&payload[i]!=' '){
                    editedJson[count++]= payload[i];
                  }
                }
                editedJson[count]='\0';
                USE_SERIAL.println("JSON EDIT:");
                USE_SERIAL.println(editedJson);
              
                 StaticJsonBuffer<300> jsonBuffer;

                JsonObject& json1 = jsonBuffer.parseObject(editedJson);
                USE_SERIAL.println("TEST:::: " );
                
                const int hours = json1["hours"];
                USE_SERIAL.println(hours);
                const int minutes = json1["minutes"];
                const int seconds = json1["seconds"];
                
                _timeLamp->hours=hours;
                _timeLamp->minutes=minutes;
                _timeLamp->seconds=seconds;
               
                lcd.setCursor(0,1);

                 
    

            } else {
           USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
         }
        }
        http.end();
    }

}

void encoder()
  {
      analogSound+=1;

  }
  

