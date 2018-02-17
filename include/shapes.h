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


void drawBox(VECTOR3D positionBox, float ancho, float alto, float fondo, VECTOR3D color01, VECTOR3D color02, VECTOR3D color03);
void drawMuro(VECTOR3D initialPosition, int alto, int ancho, VECTOR3D color01, VECTOR3D color02, VECTOR3D color03);
void drawSuelo(VECTOR3D initialPosition, int ancho, int fondo, VECTOR3D color01, VECTOR3D color02, VECTOR3D color03);
void drawScene();
void drawBuildings();
void drawBuilding(VECTOR3D initialPosition, int alto, int ancho, int fondo, VECTOR3D color01, VECTOR3D color02, VECTOR3D color03);



#endif
