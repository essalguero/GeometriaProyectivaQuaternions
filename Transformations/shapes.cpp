
#include "GLInclude.h"
#include "shapes.h"

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
	
	for (auto &vector3d = line.P.begin(); vector3d != line.P.end(); ++vector3d)
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

}void drawAxis(){
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
	drawLine(lineZ, colorZ, true);}