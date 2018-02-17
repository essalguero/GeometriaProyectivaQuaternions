#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GLInclude.h"
#include "camera.h"
#include "shapes.h"


#include "math3d.h"


#define NEAR_VALUE 0.1
#define FAR_VALUE 4000


void Display(void);
void Init(void);
void Render(void);
void Lighting(void);
void InitCamera(int);
void HandleKeyboard(unsigned char key, int x, int y);
void HandleReshape(int, int);
void HandleIdle(void);

int fullscreen = FALSE;

int currentbutton = -1;
double rotatespeed = 3;
double tSpeed = 0.05;
float t = 0;

CAMERA camera;
FRUSTUM centerFrustum;

double rotateangle = 0;


int xPrev = INT_MIN;
int yPrev = INT_MIN;

EULER rotacionEuler;

void testMultiply() {
	VECTOR3D v1{ 1, 0, 0 };
	VECTOR3D v2{ 0, 1, 0 };
	VECTOR3D v3{ 0, 0, 1 };

	QUATERNION q1 = Vector3DToQuaternion(v1);

	QUATERNION q2 = Vector3DToQuaternion(v2);

	QUATERNION q3 = Vector3DToQuaternion(v3);

	QUATERNION q4;
	q4.s = -3;
	q4.v = { 6, 7, -8 };


	QUATERNION q5;
	q5.s = 1;
	q5.v = { 12, -7, -11 };


	QUATERNION result01 = Multiply(q1, q2);
	QUATERNION result02 = Multiply(q1, q3);
	QUATERNION result03 = Multiply(q3, q3);
	QUATERNION result04 = Multiply(q4, q5); // Resultado debe ser (-114, (-163, -2, -101))

	QUATERNION q1Conjugado = Conjugate(q1);
	QUATERNION multConjugado01 = Multiply(q1, q1Conjugado);

	QUATERNION q5Conjugado = Conjugate(q5);
	QUATERNION multConjugado05 = Multiply(q5, q5Conjugado);

	return;
}


void testQuaternionFromToVectors()
{
	VECTOR3D v1{ 1, 0, 0 };
	VECTOR3D v2{ 0, 1, 0 };
	VECTOR3D v3{ 0, 0, 1 };

	QUATERNION q1 = Vector3DToQuaternion(v1);


	QUATERNION q2 = Vector3DToQuaternion(v2);

	QUATERNION q3 = Vector3DToQuaternion(v3);

	QUATERNION retQ1 = QuaternionFromToVectors(v1, v2);
	VECTOR3D retV1 = RotateWithQuaternion(v1, retQ1);


	QUATERNION retQ2 = QuaternionFromToVectors(v1, v3);
	VECTOR3D retV2 = RotateWithQuaternion(v1, retQ2);


	QUATERNION retQ3 = QuaternionFromToVectors(v2, v3);
	VECTOR3D retV3 = RotateWithQuaternion(v2, retQ3);
}


void test()
{
	testMultiply();

	testQuaternionFromToVectors();

}

int main(int argc, char **argv)
{
	camera.screenwidth = 600;
	camera.screenheight = 400;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("Geometria Proyectiva");
	if (fullscreen)
		glutFullScreen();
	glutDisplayFunc(Display);
	glutReshapeFunc(HandleReshape);
	glutReshapeWindow(camera.screenwidth, camera.screenheight);
	glutIdleFunc(HandleIdle);
	glutKeyboardFunc(HandleKeyboard);
	Init();
	InitCamera(0);
	Lighting();

	glutMotionFunc(HandleMouseMotion);
	glutPassiveMotionFunc(HandleMousePassiveMotion);

	/*
	Funciones de test añadidas para comprobar que las funciones pedidas estan
	implementadas correctamente
	*/
	test();


	cout << "    Opciones disponibles" << endl << endl;
	cout << "w: Avanzar" << endl;
	cout << "a: Desplazarse a la Izquierda" << endl;
	cout << "s: Retroceder" << endl;
	cout << "d: Desplazarse a la Derecha" << endl;
	cout << "t: Avanzar de manera rapida" << endl;
	cout << "g: Retroceder de manera rapida" << endl;
	cout << "h: Reiniciar la camara" << endl;
	cout << "q: Salir" << endl;
	cout << "Esc: Salir" << endl << endl << endl;

	cout << "Para girar la camara, mover el raton mientras se pulsa alguno de los botones del raton" << endl;

	glutMainLoop();
	return(0);
}

void Init(void)
{

	float fogDensity = 0.3;
	static float fog_color[] = { 0.3, 0.3, 0.3, 0.7 };

	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_DENSITY, fogDensity);
	glFogfv(GL_FOG_COLOR, fog_color);
	glFogf(GL_FOG_START, 100.0);
	glFogf(GL_FOG_END, 400.0);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_DITHER);
	glDisable(GL_CULL_FACE);

	glLineWidth(1.0);
	glPointSize(1.0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glFrontFace(GL_CW);
	glClearColor(0.0, 0.0, 0.0, 0.0);         /* Background colour */
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void Display(void)
{
	glDrawBuffer(GL_BACK_LEFT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glDrawBuffer(GL_BACK);

	//double nearValue = 0.1;
	//double farValue = 10000;
	double nearValue = NEAR_VALUE;
	double farValue = FAR_VALUE;

	double aspectRatio = camera.screenwidth / (double)camera.screenheight;
	FRUSTUM centerFrustum = makeFrustum(camera.aperture, aspectRatio, nearValue, farValue);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(camera.aperture, aspectRatio, nearValue, farValue);//QUITAR
	glFrustum(centerFrustum.left, centerFrustum.right, centerFrustum.bottom, centerFrustum.top, centerFrustum.nearValue, centerFrustum.farValue);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	VECTOR3D target = Add(camera.position, camera.direction);
	//gluLookAt(camera.position.x,camera.position.y,camera.position.z, target.x , target.y, target.z, camera.up.x,camera.up.y,camera.up.z); //QUITAR

	// TODO
	MATRIX4 lookAtMatrix = lookAt(camera.position, target, camera.up);
	glLoadMatrixf(lookAtMatrix.m);

	glViewport(0, 0, camera.screenwidth, camera.screenheight);

	Render();

	glutSwapBuffers();
}


void Render(void)
{
	GLfloat specular[4] = { 1.0,1.0,1.0,1.0 };
	GLfloat shiny[1] = { 5.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

	glPushMatrix();
	glRotatef(rotateangle, 0.0, 1.0, 0.0);

	drawAxis();
	glEnable(GL_FOG);
	drawScene();
	glDisable(GL_FOG);

	glPopMatrix();
}

void Lighting(void)
{
	GLfloat fullambient[4] = { 1.0,1.0,1.0,1.0 };
	GLfloat position[4] = { 0.0,0.0,0.0,0.0 };
	GLfloat ambient[4] = { 0.2,0.2,0.2,1.0 };
	GLfloat diffuse[4] = { 1.0,1.0,1.0,1.0 };
	GLfloat specular[4] = { 0.0,0.0,0.0,1.0 };

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	glDisable(GL_LIGHT5);
	glDisable(GL_LIGHT6);
	glDisable(GL_LIGHT7);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, fullambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
}

void HandleKeyboard(unsigned char key, int x, int y)
{
	VECTOR3D forwardVector;
	VECTOR3D upVector;
	VECTOR3D movingVector;

	switch (key) {
	case ESC:
	case 'Q':
	case 'q':
		exit(0);
		break;
	case 'R':
	case 'r':
		rotateangle += rotatespeed;
		break;

	case '+':
		t += tSpeed;
		t = t > 1 ? 1 : t;
		break;

	case '-':
		t -= tSpeed;
		t = t <0 ? 0 : t;
		break;

	case 'h':
	case 'H':
		InitCamera(0);
		break;


	case 't':
	case 'T':
		forwardVector = MultiplyWithScalar(3, getForward(rotacionEuler));
		camera.position = Add(camera.position, forwardVector);
		break;
	case 'w':
	case 'W':
		forwardVector = getForward(rotacionEuler);
		camera.position = Add(camera.position, forwardVector);
		break;

	case 'g':
	case 'G':
		forwardVector = MultiplyWithScalar(-3, getForward(rotacionEuler));
		camera.position = Add(camera.position, forwardVector);
		break;
	case 's':
	case 'S':
		forwardVector = MultiplyWithScalar(-1, getForward(rotacionEuler));
		camera.position = Add(camera.position, forwardVector);
		break;

	case 'a':
	case 'A':
		forwardVector = getForward(rotacionEuler);
		upVector = getUp(rotacionEuler);
		movingVector = CrossProduct(upVector, forwardVector);
		camera.position = Add(camera.position, movingVector);
		break;

	case 'd':
	case 'D':
		forwardVector = getForward(rotacionEuler);
		upVector = getUp(rotacionEuler);
		movingVector = MultiplyWithScalar(-1, CrossProduct(upVector, forwardVector));
		camera.position = Add(camera.position, movingVector);
		break;

	}


}

void HandleIdle(void)
{
	//    rotateangle += rotatespeed;
	glutPostRedisplay();
}

void HandleReshape(int w, int h)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	camera.screenwidth = w;
	camera.screenheight = h;
}


void InitCamera(int mode)
{
	camera.aperture = 45;

	camera.position.x = 0;
	camera.position.y = 0;
	camera.position.z = 20;

	camera.direction.x = -camera.position.x;
	camera.direction.y = -camera.position.y;
	camera.direction.z = -camera.position.z;

	camera.up.x = 0;
	camera.up.y = 1;
	camera.up.z = 0;
}

void InitEuler()
{
	rotacionEuler.yaw = 0;
	rotacionEuler.pitch = 0;
	rotacionEuler.roll = 0;

	rotacionEuler.orientation = { 1, 0, 0, 0 };
}



//Para controlar la camara tienes que obtener los cambios de posicion del raton y transformarlos
//en ejes EULER (yaw y pitch). La camara debe mirar guiada por el raton. Utiliza para ello las
//siguientes funciones de GLUT:
void HandleMouseMotion(int x, int y)
{

	//xPrev e yPrev se inicializan a INT_MIN y se comprueban antes de actualizar los angulos para evitar un salto brusco
	//al inicializar el programa
	if (xPrev != INT_MIN && yPrev != INT_MIN)
	{
		// Calcular grados de rotacion en funcion de los valores de x e y.
		// Se hace una resta de los valores antiguos y los nuevos y el resultado se considera
		// el angulo de rotacion (en grados)
		rotacionEuler.yaw = ((y - yPrev) * DTOR) * 4;
		rotacionEuler.pitch = -((x - xPrev) * DTOR) * 4;
		rotacionEuler.roll = 0;

		// Solo se realizan los calculos de los vectores de camara si alguno de los
		// angulos se ha actualizado
		if (rotacionEuler.yaw != 0 || rotacionEuler.pitch != 0)
		{
			// Actualizar los angulos de rotacion en la estructura
			updateEulerOrientation(rotacionEuler);
		}
	}

	// Guardar las nuevas coordenadas del raton para utilizarlas en la siguiente llamada a la funcion
	xPrev = x;
	yPrev = y;

}

void HandleMousePassiveMotion(int x, int y)
{
	xPrev = x;
	yPrev = y;
}
