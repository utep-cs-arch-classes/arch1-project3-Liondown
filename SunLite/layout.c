#include <lcdutils.h>
#include <stdlib.h>

#include "layout.h"

#include "drawing.h"

static u_char phases[PHASE_COUNT];
static u_char responses[PHASE_COUNT];

u_char phase;
u_char index;

void initPhase(){

  phases[PHASE_COUNT] = {0};
  index = 0;
  phase = 1;
}

void makeEarthTurn(Layer *pLayer){
  //Press 0-3 buttons code goes here
  responses[index-1] = buttons;
  drawPlanetaryLayer(*pLayer, phase);
  phase = randNumber(phase);
 
}

void makeSunTurn(){
  phase = randNumber(phase);
  phases[index] = phase;
  index++;
}

boolean isStandstill(){
  if(responses[index-1] == phases[index])
    return true;
  else
    return false;
}

boolean isVictory(){
  bool condition = false;
  for(i = 0; i < PHASE_COUNT; i++){
    if(responses[i] == phases[i+1])
      condition = true;
    else
      condition = false;
  }
  return condition;
}

int randNumber(int phase){

  int r = 0;
  while(true){
    int r = rand() % 4;
    
    if(r != phase)
      return r;
    else
      continue;
  }
  return r;
}
