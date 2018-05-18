#include <math.h>
#include <stdio.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <msp430.h>
#include <p2switches.h>
#include <abCircle.h>
#include "drawing.h"

#define GREEN_LED BIT6

#define PLANETARY 1
#define SUN 2
#define STANDSTILL 3
#define RESTART 4
#define WAIT 5
#define LOSS 6
#define VICTORY 7;


u_int bgColor = COLOR_BLACK;
u_int vicConditions[6];
u_int signalArray[6];
int redrawScreen = 1;
int mercIndex, venusIndex, earthIndex, marsIndex = 0;

typedef struct _pointSeq{
  unsigned char xCoord[30];
  unsigned char yCoord[30];
} coords;

coords merc = {{79, 72, 57, 49, 56, 71, 79, 72, 57, 49, 56, 70, 80, -1, -1, -1, -1},
	       {80, 93, 93, 80, 67, 67, 80, 93, 93, 80, 67, 67, 80, -1, -1, -1, -1}};

coords earth = {{104, 102, 95, 84, 71, 57, 44, 33, 26, 24, 26, 33, 44, 57, 71, 84, 95, 102, 104, -1, -1, -1, -1},
		{81, 92, 104, 115, 119, 119, 114, 105, 94, 80, 66, 54, 45, 41, 41, 45, 54, 66, 80, -1, -1, -1, -1}};

coords venus = {{94, 87, 69, 49, 36, 36, 49, 69, 87, 87, 94, 87, 69, 49, 36, 36, 49, 69, 87, -1, -1, -1, -1},
		{81, 99, 110, 106, 90, 70, 54, 50, 61, 80, 81, 99, 110, 106, 90, 70, 54, 50, 61, -1, -1, -1, -1}};

coords mars = {{109, 107, 103, 96, 87, 76, 64, 52, 42, 32, 25, 21, 19, 21, 25, 32, 42, 52, 64, 76, 86, 96, 103, 107, 109, -1, -1, -1, -1},
	       {81, 92, 103, 11, 119, 123, 125, 123, 119, 112, 103, 92, 80, 68, 57, 48, 41, 37, 34, 37, 41, 48, 57, 68, 80, -1, -1, -1, -1}};

Layer pLayer4 = {
  (AbShape *)&circle2,
  {(screenWidth/2)+40, (screenHeight/2)+40},
  {0,0},{0,0},
  COLOR_RED,
  0,
};

Layer pLayer3 = {
  (AbShape *)&circle4,
  {(screenWidth/2)+30, (screenHeight/2)+30},
  {0,0}, {0,0},
  COLOR_DARK_GREEN,
  &pLayer4,
};

Layer pLayer2 = {
  (AbShape *) &circle4,
  {(screenWidth/2)+20, (screenHeight/2)+20},
  {0,0}, {0,0},
  COLOR_GRAY,
  &pLayer3,
};

Layer pLayer1 = {
  (AbShape *)&circle2,
  {(screenWidth/2)+16, (screenHeight/2)+10},
  {0,0}, {0,0},
  COLOR_BLUE,
  &pLayer2,
};
Layer sLayer = {
  (AbShape *)&circle14,
  {(screenWidth/2), (screenHeight/2)},
  {5,5}, {5,5},
  COLOR_ORANGE_RED,
  &pLayer1,
};

void movLayerDraw(Layer *layers, coords xy, int index){
  if(xy.xCoord[index] != -1 && xy.yCoord[index] != -1){
    int x = xy.xCoord[index];
    int y = xy.yCoord[index]; 
    Vec2 pixelPos = {x, y};
    u_int color = bgColor;
    layers->pos = pixelPos;
  }
}

void giveSignal(Layer* sLayer, u_int signalNumber){
  if(signalNumber == 1)
    sLayer->color = COLOR_RED;
  else if(signalNumber == 2)
    sLayer->color = COLOR_ORANGE;
  else if(signalNumber == 3)
    sLayer->color = COLOR_WHITE;
  else
    sLayer->color = COLOR_YELLOW;
}
void resetSLayer(Layer* sLayer){
  sLayer->color = COLOR_ORANGE_RED;
}

void startRespond(Layer *pLayer, u_int pLayerNumber){
  if(pLayerNumber == 1)
    pLayer->color = COLOR_RED;
  else if(pLayerNumber == 2)
    pLayer->color = COLOR_WHITE;
  else if(pLayerNumber == 3)
    pLayer->color = COLOR_BLUE;
  else if(pLayerNumber == 4)
    pLayer->color = COLOR_ORANGE;
  
}
void stopRespond(Layer *pLayer, u_int pLayerNumber){
  if(pLayerNumber == 1)
    pLayer->color = COLOR_BLUE;
  else if(pLayerNumber == 2)
    pLayer->color = COLOR_GRAY;
  else if(pLayerNumber == 3)
    pLayer->color = COLOR_DARK_GREEN;
  else if(pLayerNumber == 4)
    pLayer->color = COLOR_RED;
}

void main(){
  P1DIR |= GREEN_LED;
  P1OUT |= GREEN_LED;

  configureClocks();
  lcd_init();
  p2sw_init(1);

  layerInit(&sLayer);
  //  drawString5x7(10,10, "switches:", COLOR_GREEN, COLOR_BLUE);

  layerDraw(&sLayer);
  //  enableWDTInterrupts();
  or_sr(0x8);

  for(;;){
    while(!redrawScreen){
      P1OUT &= ~GREEN_LED;
      or_sr(0x10);
    }
    P1OUT |= GREEN_LED;
      redrawScreen = 0;
      while(1){
      // change pLayer coords
      movLayerDraw(&pLayer1, merc, mercIndex);
      movLayerDraw(&pLayer2, venus, venusIndex);
      movLayerDraw(&pLayer3, earth, earthIndex);
      movLayerDraw(&pLayer4, mars, marsIndex);

      // draws updated pLayers with new coords
      layerDraw(&sLayer);

      // updating indeces to indicate which elements to obtain
      if(mercIndex < 13)
	mercIndex++;
      else
	mercIndex = 0;

      if(venusIndex < 22)
  	venusIndex++;
      else
  	venusIndex = 0;

      if(earthIndex < 22)
	earthIndex++;
      else
	earthIndex = 0;

      if(marsIndex < 28)
	marsIndex++;
      else
	marsIndex = 0;
      }
  }
}
  

  //  enableWDTInterrupts();
  
  /***
  while(1){
    //    clearScreen(COLOR_BLACK);
    //   layerInit(&sLayer);
    merc.xCoord[xIndex] = xElement1;
    merc.yCoord[yIndex] = yElement1;
    if(xElement1 == -1 && yElement1 == -1)
      break;
    //   venus.xCoord[xIndex] = xElement2;
    Layer p1 = _planMessage(pLayer1, COLOR_BLUE, xElement1, yElement1);
    //    Layer p2 = _planMessage(pLayer2, COLOR_GRAY);
    //    Layer p3 = _planMessage(pLayer3, COLOR_GREEN);
    //   Layer p4 = _planMessage(pLayer4, COLOR_RED);
    **/
//    for(;;){
//     while(!redrawScreen){
//      P1OUT &= ~GREEN_LED;
//     or_sr(0x10);
//  }
//     P1OUT |= GREEN_LED;
     
//    }
//  }
  //  redrawScreen = 0;
  
    //   redrawScreen = 0;
    //    merc.xCoord[xIndex] = xElement1;
    //    merc.yCoord[yIndex] = yElement1;
    //    Vec2 pixelPos = {xElement1, yElement1};
    //    pLayer1.pos = pixelPos;
    //    layerDraw(&sLayer);
    //    layerDraw(&pLayer1);
    //    xIndex += 1;
    //    yIndex += 1;
    //    if(merc.xCoord[xIndex] = -1 && merc.xCoord[yindex] == -1){
    //      xIndex, yIndex = 0;




   /***  while(1){
    u_int switches = p2sw_read(), i, prevColor;
    char str[5];
    boolean toDraw = true;
    for(i = 0; i < 4; i++){
      str[i] = (switches & (1<<i)) ? '-' : '0'+i;

      if(str[i] == 0){
	prevColor = COLOR_BLUE;
	respond(&pLayer1, COLOR_WHITE);
	}
      }
      else if(str[i] == 1){
	prevColor = COLOR_GRAY;
	respond(&pLayer2, COLOR_WHITE);
	layerDraw(&sLayer);
      }
      else if(str[i] == 2){
	prevColor = COLOR_SKY_BLUE;
	respond(&pLayer3, COLOR_GREEN);
	layerDraw(&sLayer);
      }
      else{
	prevColor = COLOR_RED;
	respond(&pLayer4, COLOR_ORANGE);
	layerDraw(&sLayer);
      }
	
    }
    str[4] = 0;
    drawString5x7(20,20, str, COLOR_GREEN, COLOR_BLUE);
  }
}
   ***/

  //***  initPhase();
  //  int round = 1;
  //boolean isDone = false;
  
  // while(!isDone){
  // makeSunTurn(sLayer);
  // makeEarthTurn(pLayer1);
    
  //if(isStandStill() != isDone)
  //  round++;
  //else if(round == PHASE_COUNT)
  //  isVictory = isDone;
  //}


  //}

/****
void wdt_c_halder(){
    
  static short count = 0;
  int index = 0;
  P1OUT |= GREEN_LED;
  count++;
  u_int switches = p2sw_read(), i;
  char str[5];
  if(count == 15){
    movLayerDraw(&pLayer1, merc, count);
        for(i = 0; i < 4; i++)
          str[i] = (switches & (1<<i)) ? 0: 1;
	
	if(str[0]){
	  startRespond(&pLayer1, 1);
	}
	else{
	  stopRespond(&pLayer1, 1);
	}
	/**
	if(str[1]){
	}
	else{
	}
	if(str[2]){
	}
	else{
	}
	if(str[3]){
	}

	
    //    clearScreen(COLOR_BLACK);
    drawString5x7(20,20, "Not Drawn To Scale", COLOR_GREEN, COLOR_RED);
    index++;
    if(p2sw_read())
      redrawScreen = 1;
    count = 0;
  }
  P1OUT &= ~GREEN_LED;
}
****/
