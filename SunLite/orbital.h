#include <math.h>
#include <stdio.h>


typedef struct _points{
  int xCoords[24];
  int yCoords[24];
} points;


points new_PC();

double degreesToRadians(double degrees);

double parametricEquationX(double cx, double r, double x);

double parametricEquationY(double cy, double r, double y);

void makepoints(points p, double angle, double radius, double index);
