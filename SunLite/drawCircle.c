#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>

#include "abCircle.h"


u_int bgColor = COLOR_BLACK;

Layer Planet = {
  (AbShape *)&circle19,
  {screenWidth/5, screenHeight/5},
  {0,0}, {0,0},
  COLOR_BLUE,
  0
};

Layer Sun = {
  (AbShape *)&circle27,
  {screenWidth/10, screenHeight/10},
  {5,5}, {5,5},
  COLOR_YELLOW,
  0
};

int main(){

  configureClocks();
  lcd_init();

  clearScreen(COLOR_BLACK);

  layerDraw(&Planet);
  layerDraw(&Sun);

}
