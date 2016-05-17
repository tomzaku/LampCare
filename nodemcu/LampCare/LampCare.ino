/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <GDBStub.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "clapclap.h"

#define USE_SERIAL Serial
const char* ssid = "TungTruong";
const char* password = "cohangxom@321";
const int pinSound =5;
ESP8266WiFiMulti WiFiMulti;
struct UserData{
  char name[32];
  char company[32];
};
UserData* userData; 


void setup() {

    USE_SERIAL.begin(115200);
   // USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

   WiFiMulti.addAP(ssid, password);

}


void loop() {
    // wait for WiFi connection

    if((WiFiMulti.run() == WL_CONNECTED)) {
        int count=0;
        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
//        http.begin("http://jsonplaceholder.typicode.com/users/1"); //HTTP
        http.begin("http://query.yahooapis.com/v1/public/yql?q=select%20item.condition%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D\"danang\")&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys"); //HTTP

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
              
                 StaticJsonBuffer<500> jsonBuffer;

                JsonObject& json1 = jsonBuffer.parseObject(editedJson);
                USE_SERIAL.println("TEST:::: " );
                
                const char* nameChar = json1["query"]["results"]["channel"]["item"]["condition"]["code"];
                
//
//                strcpy(userData->name, json1["name"]);
//                strcpy(userData->company, json1["company"]["name"]);
                USE_SERIAL.println("FINISH:");
                USE_SERIAL.println(nameChar);
                 
    

            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(10000);
}

