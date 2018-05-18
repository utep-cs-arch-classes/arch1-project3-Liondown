

typedef struct SunColors_s{
  u_int colorSet[4];
} sunColors;

typedef struct PlanetaryColors{
  u_int colorSet2[4];
} planColors;

Layer pLayer = {
  (AbShape *)&circle19,
  {screenWidth/10, screenHeigh/10},
  {0,0},{0,0}
  COLOR_BLUE,
  
