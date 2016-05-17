#include "clapclap.h"
#include <Arduino.h>

#include <stdlib.h>
using namespace std;
ClapClap::ClapClap(int pinSound,int  sum2GraphMin,int sum2GraphMax,int disparityTopGraph):sum2GraphMin(sum2GraphMin),sum2GraphMax(sum2GraphMax),disparityTopGraph(disparityTopGraph){}

ClapClap::ClapClap(int pinSound,float coefficient){
  sum2GraphMax = int(650*coefficient);
  sum2GraphMin = int(1500*coefficient);
  disparityTopGraph = int(250*coefficient);
}

int ClapClap::checkTop(GraphSound graphSound){
	if(graphSound.graph[graphSound.index]>graphSound.graph[graphSound.index-1])graphSound.top=graphSound.graph[graphSound.index];
  return (graphSound.index>=3 
  	&& (graphSound.graph[graphSound.index-2]<graphSound.graph[graphSound.index-1]
  	&&graphSound.graph[graphSound.index]<graphSound.graph[graphSound.index-1]));
}




int ClapClap::isMatch(){
  return analogSound==0&&switchLeftGraph==0&&matchGraph&&
  abs(leftGraph.top - rightGraph.top)<disparityTopGraph &&
   leftGraph.index>1&& leftGraph.index<6&&
   rightGraph.index>1&&rightGraph.index<6&&
   indexSound-checkIndexInGraph==1&&
   (leftGraph.sum+ rightGraph.sum)>sum2GraphMin&&(leftGraph.sum+ rightGraph.sum)<sum2GraphMax; 
}

void ClapClap::processAnalogSound(GraphSound *graphSound){
	if(graphSound->index<6){
					 if(graphSound->index==0){
              graphSound->graph[(graphSound->index)++]=analogSound;
              checkIndexInGraph= indexSound;
              graphSound->sum+=analogSound;
              graphSound->top=analogSound;
					 }else{      
             if(graphSound->countTop>1) matchGraph=0;
             else{
                if(checkTop(*graphSound)){
                  graphSound->top=graphSound->graph[graphSound->index-1];
                  (graphSound->countTop)++;
                }
                
                graphSound->graph[graphSound->index++]=analogSound;
                checkIndexInGraph= indexSound;
                graphSound->sum+=analogSound;
             }
           }
    }
    else matchGraph=0;
}


int ClapClap::checkClapClap(int analogSoundIn){
	  indexSound++;
    analogSound=analogSoundIn;
  if (analogSound< MAX_SOUND_CLAPCLAP && analogSound >0&& matchGraph){
    if ((indexSound-checkIndexInGraph)<=LENGTH_MIDDLE_GRAPS
    	&&(indexSound-checkIndexInGraph)>1&&switchLeftGraph==1){
      switchLeftGraph=0;
    }
    if(switchLeftGraph){
     processAnalogSound(&leftGraph);
   }
    else  {
      /*Debug
      for(int i=0;i<leftGraph.index;i++){
        Serial.print(">>>>");
        Serial.println(leftGraph.graph[i]);
      }*/
      processAnalogSound(&rightGraph);
    }
  }
  
  if(matchGraph==0||((indexSound-checkIndexInGraph)>4)){
    resetValue();
  }
  if(isMatch()){
    resetValue();
    return 1;
  }

  analogSound=0;
  if(indexSound>300000) resetIndex();
  return 0;
}
void ClapClap::resetValue(){
  matchGraph=1;
  switchLeftGraph=1;
  leftGraph.countTop=0;
  leftGraph.index=0;
  leftGraph.top=0;
  leftGraph.sum=0;

  rightGraph.countTop=0;
  rightGraph.index=0;
  rightGraph.top=0;
  rightGraph.sum=0;
}
void ClapClap::resetIndex(){
  indexSound=0;
}

