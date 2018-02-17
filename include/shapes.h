#ifndef _GEOMETRIA_PROYECTIVA_SHAPES_H_
#define _GEOMETRIA_PROYECTIVA_SHAPES_H_

#include "GLInclude.h"
#include "math3d.h"
#include <vector>

using namespace std;

typedef struct {
	std::vector<VECTOR3D> P;
} LINE;


void drawDot(VECTOR3D position, float sradius = 1, COLOUR color = grey);

//TODO
void drawLine(LINE line, COLOUR color = grey, bool doDrawDots = false);
void drawAxis();


void drawBox(VECTOR3D positionBox, float ancho, float alto, float fondo, COLOUR topColor, COLOUR frontColor, COLOUR leftColor);
void drawMuro(VECTOR3D initialPosition, int alto, int ancho, COLOUR topColor, COLOUR frontColor, COLOUR leftColor);
void drawSuelo(VECTOR3D initialPosition, int ancho, int fondo, COLOUR topColor, COLOUR frontColor, COLOUR leftColor);
void drawScene();
void drawBuildings();
void drawBuilding(VECTOR3D initialPosition, int alto, int ancho, int fondo, COLOUR topColor, COLOUR frontColor, COLOUR leftColor);

void drawTrees();
void drawTree(VECTOR3D initialPosition);


#endif
