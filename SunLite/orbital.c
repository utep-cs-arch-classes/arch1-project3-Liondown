#include <math.h>
#include <stdio.h>

typedef struct _points{
  unsigned int xCoord[24];
  unsigned int yCoord[24];
} points;

points new_PC(){

  points p;
  p.xCoord[24] = 0;
  p.yCoord[24] = 0;
  return p;
}

double degreesToRads(double degrees){
  return (degrees * (M_PI/180));
}

double parametricEquationX(double cx, double r, double x){
  return cx + (r * cos(x));
}

double parametricEquationY(double cy, double r, double y){
  return cy + (r * sin(y)); 
}

void makepoints(points p, double angle, double radius, int index){

  double rad,r = degreesToRads(angle);
  double a = angle;
  
  // remember, cos(angle) is for x, sin(angle) is for y

  // 64, 80 is the middle point
  for(int i = 0; i < index; i++){
  unsigned int x = (unsigned int) parametricEquationX(64.0, radius, rad);
  unsigned int y = (unsigned int) parametricEquationY(80.0, radius, rad);
  p.xCoord[i] = x;
  p.yCoord[i] = y;
  rad += r;
  printf("%d\t%d\n", p.xCoord[i], p.yCoord[i]);
  }
}
  


void main() {
  
  points p = new_PC();
  makepoints(p, 23, 30, 15);
  
}

