
#include "GLInclude.h"
#include "shapes.h"

#include "math3d.h"
#include "camera.h"

extern CAMERA camera;

void drawDot(VECTOR3D position, float sradius, COLOUR color)
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);


	VECTOR3D p[4], n[4];
	int STEP = 30;
	for (int i = 0; i<360; i += STEP) {
		for (int j = -90; j<90; j += STEP) {

			p[0].x = sradius * cos(j*DTOR) * cos(i*DTOR);
			p[0].y = sradius * sin(j*DTOR);
			p[0].z = sradius * cos(j*DTOR) * sin(i*DTOR);
			n[0] = p[0];

			p[1].x = sradius * cos((j + STEP)*DTOR) * cos(i*DTOR);
			p[1].y = sradius * sin((j + STEP)*DTOR);
			p[1].z = sradius * cos((j + STEP)*DTOR) * sin(i*DTOR);
			n[1] = p[1];

			p[2].x = sradius * cos((j + STEP)*DTOR) * cos((i + STEP)*DTOR);
			p[2].y = sradius * sin((j + STEP)*DTOR);
			p[2].z = sradius * cos((j + STEP)*DTOR) * sin((i + STEP)*DTOR);
			n[2] = p[2];

			p[3].x = sradius * cos(j*DTOR) * cos((i + STEP)*DTOR);
			p[3].y = sradius * sin(j*DTOR);
			p[3].z = sradius * cos(j*DTOR) * sin((i + STEP)*DTOR);
			n[3] = p[3];

			glBegin(GL_POLYGON);
			if (i % (STEP * 4) == 0)
				glColor3f(color.r, color.g, color.b);
			else
				glColor3f(color.r*0.5, color.g*0.5, color.b*0.5);
			for (int k = 0; k<4; k++) {
				glNormal3f(n[k].x, n[k].y, n[k].z);
				glVertex3f(p[k].x, p[k].y, p[k].z);
			}
			glEnd();
		}
	}

	glPopMatrix();
}

void drawLine(LINE line, COLOUR color, bool doDrawDots)
{
	glColor3f(color.r, color.g, color.b);
	// usa GL_LINE_STRIP en modo inmediato (glBegin/glEnd)
	// enviar puntos a OpenGL usando glVertex3f

	glBegin(GL_LINE_STRIP);

	for (auto vector3d = line.P.begin(); vector3d != line.P.end(); ++vector3d)
	{
		glVertex3f(vector3d->x, vector3d->y, vector3d->z);
	}

	glEnd();

	glBegin(GL_POINTS);
	if (doDrawDots)
	{
		drawDot(*line.P.begin(), 0.1f);
		drawDot(*(line.P.end() - 1), 0.1f, color);
	}
	glEnd();

}

void drawAxis() {
	// Definir las lineas de los ejes
	LINE lineX;
	LINE lineY;
	LINE lineZ;

	// Definir los colores de los ejes
	COLOUR colorX;
	COLOUR colorY;
	COLOUR colorZ;

	// Definir los vectores para los ejes
	VECTOR3D origen, puntoX, puntoY, puntoZ;

	// Punto de origen
	origen.x = 0.0;
	origen.y = 0.0;
	origen.z = 0.0;

	// Vector eje X
	puntoX.x = 1.0;
	puntoX.y = 0;
	puntoX.z = 0;

	lineX.P.push_back(origen);
	lineX.P.push_back(puntoX);

	colorX.r = 1.0;
	colorX.g = 0;
	colorX.b = 0;

	drawLine(lineX, colorX, true);


	// Vector eje Y
	puntoY.x = 0;
	puntoY.y = 1.0;
	puntoY.z = 0;

	lineY.P.push_back(origen);
	lineY.P.push_back(puntoY);

	colorY.r = 0;
	colorY.g = 1.0;
	colorY.b = 0;

	drawLine(lineY, colorY, true);


	// Vector Eje Z
	puntoZ.x = 0;
	puntoZ.y = 0;
	puntoZ.z = 1.0;

	lineZ.P.push_back(origen);
	lineZ.P.push_back(puntoZ);

	colorZ.r = 0;
	colorZ.g = 0;
	colorZ.b = 1.0;
	drawLine(lineZ, colorZ, true);

}


void drawBoundingBox()
{
	
	drawBox({ camera.position.x, 0, camera.position.z - 800 }, 4000, 4000, 1, { .1f, .0f, .0f }, { .1f, .0f, .0f }, { .1f, .0f, .0f });
	drawBox({ camera.position.x, 0, camera.position.z + 800 }, 4000, 4000, 1, { .1f, .0f, .0f }, { .1f, .0f, .0f }, { .1f, .0f, .0f });
	drawBox({ camera.position.x, camera.position.y - 800, camera.position.z }, 4000, 1, 4000, { .1f, .0f, .0f }, { .1f, .0f, .0f }, { .1f, .0f, .0f });
	drawBox({ camera.position.x, camera.position.y + 800, camera.position.z }, 4000, 1, 4000, { .1f, .0f, .0f }, { .1f, .0f, .0f }, { .1f, .0f, .0f });
	drawBox({ camera.position.x - 800, 0, camera.position.z }, 1, 4000, 4000, { .1f, .0f, .0f }, { .1f, .0f, .0f }, { .1f, .0f, .0f });
	drawBox({ camera.position.x + 800, 0, camera.position.z }, 1, 4000, 4000, { .1f, .0f, .0f }, { .1f, .0f, .0f }, { .1f, .0f, .0f });
}

void drawScene()
{

	drawBoundingBox();

	drawBox({ 0, 0, 0 }, 1, 1, 1, { .1f, .0f, .0f }, { .1f, .0f, .0f }, { .1f, .0f, .0f });
	drawBox({ 0, 0, 40 }, 1, 1, 1, { .5f, .0f, .0f }, { .1f, .0f, .0f }, { .1f, .0f, .0f });
	drawBox({ -20, 0, 20 }, 1, 1, 1, { .5f, .0f, .0f }, { .1f, .0f, .0f }, { .1f, .0f, .0f });
	drawBox({ 20, 0, 20 }, 1, 1, 1, { .5f, .0f, .0f }, { .1f, .0f, .0f }, { .1f, .0f, .0f });

	drawMuro({ -80.2, 0, -40 }, 50, 175, { .0f, .5f, .0f }, { 0.2f, 1.0f, 0.2f }, { 0.2f, 1.0f, 0.2f });
	drawMuro({ -10.2, 3.0f, -40 }, 35, 52, { .0f, .5f, .0f }, { 0.2f, 1.0f, 0.2f }, { 0.2f, 1.0f, 0.2f });
	drawMuro({ 10.2, 0, -40 }, 50, 175, { .0f, .5f, .0f }, { 0.2f, 1.0f, 0.2f }, { 0.2f, 1.0f, 0.2f });

	drawSuelo({ -75, 0, -60 }, 7, 15, { .5f, .5f, .5f }, { .5f, .5f, .5f }, { .3f, .3f, .3f });
	drawSuelo({ 15, 0, -60 }, 7, 15, {.5f, .5f, .5f}, { .5f, .5f, .5f }, { .3f, .3f, .3f });
	drawSuelo({ -5, -0.20, -60 }, 2, 15, { 0.2f, 0.2f, 1.0f }, { 0.2f, 0.2f, 1.0f }, { 0.2f, 0.2f, 1.0f });


	drawBuildings();

	drawTrees();
	
}

void drawBuildings()
{

	COLOUR topColor{ .5f, .9f, .5f };
	COLOUR frontColor{ .9f, .5f, .9f };
	COLOUR lateralColor{ .1f, .1f, .1f };

	// Edificios a la izquierda de la escena
	drawBuilding({ -40, 10, -80 }, 20, 10, 20, topColor, frontColor, lateralColor);
	drawBuilding({ -60, 10, -95 }, 20, 20, 20, topColor, frontColor, lateralColor);
	drawBuilding({ -35, 15, -120 }, 30, 15, 20, topColor, frontColor, lateralColor);
	drawBuilding({ -50, 10, -145 }, 20, 10, 20, topColor, frontColor, lateralColor);
	drawBuilding({ -50, 20, -170 }, 40, 30, 15, topColor, frontColor, lateralColor);
	drawBuilding({ -42, 4, -200 }, 8, 10, 20, topColor, frontColor, lateralColor);
	drawBuilding({ -62, 8, -200 }, 16, 8, 16, topColor, frontColor, lateralColor);
	drawBuilding({ -50, 14, -230 }, 28, 20, 30, topColor, frontColor, lateralColor);


	drawBuilding({ -50, 20, -370 }, 40, 30, 15, topColor, frontColor, lateralColor);
	drawBuilding({ -42, 4, -400 }, 8, 10, 20, topColor, frontColor, lateralColor);
	drawBuilding({ -62, 8, -400 }, 16, 4, 16, topColor, frontColor, lateralColor);
	drawBuilding({ -50, 14, -430 }, 28, 20, 30, topColor, frontColor, lateralColor);


	// Edificios a la derecha de la escena
	drawBuilding({ 68, 16, -75 }, 32, 20, 20, topColor, frontColor, lateralColor);
	drawBuilding({ 45, 10, -90 }, 20, 10, 20, topColor, frontColor, lateralColor);
	drawBuilding({ 25, 15, -120 }, 30, 15, 20, topColor, frontColor, lateralColor);


	drawBuilding({ 50, 20, -170 }, 40, 30, 15, topColor, frontColor, lateralColor);
	drawBuilding({ 42, 4, -200 }, 8, 10, 20, topColor, frontColor, lateralColor);
	drawBuilding({ 62, 8, -200 }, 16, 8, 16, topColor, frontColor, lateralColor);
	drawBuilding({ 50, 14, -230 }, 28, 20, 30, topColor, frontColor, lateralColor);


	drawBuilding({ 40, 10, -280 }, 20, 10, 20, topColor, frontColor, lateralColor);
	drawBuilding({ 60, 10, -295 }, 20, 20, 20, topColor, frontColor, lateralColor);
	drawBuilding({ 35, 15, -320 }, 30, 15, 20, topColor, frontColor, lateralColor);
	drawBuilding({ 50, 10, -345 }, 20, 10, 20, topColor, frontColor, lateralColor);
	drawBuilding({ 50, 20, -370 }, 40, 30, 15, topColor, frontColor, lateralColor);
	drawBuilding({ 42, 4, -400 }, 8, 10, 20, topColor, frontColor, lateralColor);
	drawBuilding({ 62, 8, -400 }, 16, 10, 16, topColor, frontColor, lateralColor);
	drawBuilding({ 50, 14, -430 }, 28, 20, 30, topColor, frontColor, lateralColor);



	

	// Edificio piramide en el centro
	drawBuilding({ 0, 4, -530 }, 8, 40, 40, topColor, frontColor, lateralColor);
	drawBuilding({ 0, 12, -530 }, 8, 30, 30, topColor, frontColor, lateralColor);
	drawBuilding({ 0, 20, -530 }, 8, 20, 20, topColor, frontColor, lateralColor);


	// Edificio escalonado
	drawBuilding({ -50, 6, -270 }, 12, 40, 40, topColor, frontColor, lateralColor);
	drawBuilding({ -55, 18, -270 }, 12, 30, 40, topColor, frontColor, lateralColor);
	drawBuilding({ -60, 30, -270 }, 12, 20, 40, topColor, frontColor, lateralColor);



}

void drawTrees()
{
	VECTOR3D leftPosition { -15.0f, 0.0f, -65.0f };
	VECTOR3D rightPosition{ 15.0f, 0.0f, -65.0f };

	float distanceToTree = -30.0f;

	for (int i = 0; i < 15; ++i)
	{
		drawTree(leftPosition);
		drawTree(rightPosition);
		leftPosition.z += distanceToTree;
		rightPosition.z += distanceToTree;
	}
}

void drawBuilding(VECTOR3D initialPosition, int alto, int ancho, int fondo, COLOUR topColor, COLOUR frontColor, COLOUR leftColor)
{
	drawBox(initialPosition, ancho, alto, fondo, topColor, frontColor, leftColor);
}

void drawMuro(VECTOR3D initialPosition, int alto, int ancho, COLOUR topColor, COLOUR frontColor, COLOUR leftColor)
{
	float anchoLadrillo = 0.4f;
	float altoLadrillo = 0.2f;
	float fondoLadrillo = altoLadrillo * 4;

	VECTOR3D currentPosition;

	for (int i = 0; i < ancho; ++i)
	{
		for (int j = 0; j < alto; ++j)
		{
			currentPosition = { initialPosition.x + (i * anchoLadrillo), initialPosition.y + (j * altoLadrillo), initialPosition.z };
			drawBox(currentPosition, anchoLadrillo, altoLadrillo, fondoLadrillo, topColor, frontColor, leftColor);
		}
	}
}

void drawBox(VECTOR3D positionBox, float ancho, float alto, float fondo, COLOUR topColor, COLOUR frontColor, COLOUR leftColor)
{
	glBegin(GL_QUADS);
	// top
	
	glColor3f(topColor.r, topColor.g, topColor.b);

	//glColor3f(0.3f, 0.9f, 0.3f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	VECTOR3D position = Add(positionBox, { -(ancho / 2.0f), (alto / 2.0f), (fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { (ancho / 2.0f), (alto / 2.0f), (fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { (ancho / 2.0f), (alto / 2.0f), -(fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { -(ancho / 2.0f), (alto / 2.0f), -(fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);

	glEnd();

	glBegin(GL_QUADS);
	// front

	glColor3f(frontColor.r, frontColor.g, frontColor.b);

	//glColor3f(0.3f, 0.3f, 0.9f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	position = Add(positionBox, { -(ancho / 2.0f), -(alto / 2.0f), (fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { (ancho / 2.0f), -(alto / 2.0f), (fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { (ancho / 2.0f), (alto / 2.0f), (fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { -(ancho / 2.0f), (alto / 2.0f), (fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);

	glEnd();

	glBegin(GL_QUADS);
	// right
	glColor3f(leftColor.r, leftColor.g, leftColor.b);

	//glColor3f(0.9f, 0.3f, 0.3f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	position = Add(positionBox, { (ancho / 2.0f), -(alto / 2.0f), (fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { (ancho / 2.0f), -(alto / 2.0f), -(fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { (ancho / 2.0f), (alto / 2.0f), -(fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { (ancho / 2.0f), (alto / 2.0f), (fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);

	glEnd();

	glBegin(GL_QUADS);
	// left
	glColor3f(leftColor.r, leftColor.g, leftColor.b);

	//glColor3f(0.3f, 0.9f, 0.9f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	position = Add(positionBox, { -(ancho / 2.0f), -(alto / 2.0f), (fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { -(ancho / 2.0f), (alto / 2.0f), (fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { -(ancho / 2.0f), (alto / 2.0f), -(fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { -(ancho / 2.0f), -(alto / 2.0f), -(fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);

	glEnd();

	glBegin(GL_QUADS);
	// bottom
	glColor3f(topColor.r, topColor.g, topColor.b);

	//glColor3f(0.9f, 0.3f, 0.9f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	position = Add(positionBox, { -(ancho / 2.0f), -(alto / 2.0f), (fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { (ancho / 2.0f), -(alto / 2.0f), (fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { (ancho / 2.0f), -(alto / 2.0f), -(fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { -(ancho / 2.0f), -(alto / 2.0f), -(fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);

	glEnd();

	glBegin(GL_QUADS);
	// back

	glColor3f(frontColor.r, frontColor.g, frontColor.b);

	//glColor3f(0.9f, 0.9f, 0.3f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	position = Add(positionBox, { (ancho / 2.0f), (alto / 2.0f), -(fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { (ancho / 2.0f), -(alto / 2.0f), -(fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { -(ancho / 2.0f), -(alto / 2.0f), -(fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);
	position = Add(positionBox, { -(ancho / 2.0f), (alto / 2.0f), -(fondo / 2.0f) });
	glVertex3f(position.x, position.y, position.z);

	glEnd();
}

void drawSuelo(VECTOR3D initialPosition, int ancho, int fondo, COLOUR topColor, COLOUR frontColor, COLOUR leftColor)
{
	float anchoLadrillo = 10.0f;
	float altoLadrillo = 0.4f;
	float fondoLadrillo = 40.0f;

	VECTOR3D currentPosition;

	for (int i = 0; i < ancho; ++i)
	{
		for (int j = 0; j < fondo; ++j)
		{
			currentPosition = { initialPosition.x + (i * anchoLadrillo), initialPosition.y, initialPosition.z - (j * fondoLadrillo) };
			drawBox(currentPosition, anchoLadrillo, altoLadrillo, fondoLadrillo, topColor, frontColor, leftColor);
		}
	}
}

void drawTree(VECTOR3D initialPosition) {
	

	COLOUR trunkColor{ 0.647059f,  0.164706f, 0.164706f };
	COLOUR leavesColour{ 0.0f, 1.0f, 0.0f };

	VECTOR3D trunkPosition = initialPosition;
	trunkPosition.y += 1.5;

	VECTOR3D leavesPosition = trunkPosition;
	leavesPosition.y += 2.5;

	drawBox(trunkPosition, 0.4, 3, 0.4, trunkColor, trunkColor, trunkColor);
	drawBox(leavesPosition, 2.34, 1.8, 2.4, leavesColour, leavesColour, leavesColour);

}
