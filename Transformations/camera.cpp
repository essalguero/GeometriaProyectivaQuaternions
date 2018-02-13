#include "camera.h"

#include <math.h>

int xPrev, yPrev;

extern CAMERA camera;

using namespace std;
// TODO
// devuelve los valores de distancia de los planos a partir del fov horizontal
FRUSTUM makeFrustum(double fovX, double aspectRatio, double nearValue, double farValue)
{
	const double DEG2RAD = 3.14159265 / 180;

	double tangent = 0; // tangent of half fovX
	double width = 0; // half width of near plane
	double height = 0; // half height of near plane

	FRUSTUM ret;
	// TODO : rellenar valores de ret

	tangent = tan(fovX / 2 * DEG2RAD);   // tangent of half fovY
	height = nearValue * tangent;          // half height of near plane
	width = height * aspectRatio;

	ret.bottom = -height;
	ret.farValue = farValue;
	ret.left = -width;
	ret.nearValue = nearValue;
	ret.right = width;
	ret.top = height;

	return ret;
}

MATRIX4 lookAt(VECTOR3D eyePosition, VECTOR3D target, VECTOR3D upVector)
{
	VECTOR3D forward, xSide, yUp;
	MATRIX3 mRot;
	MATRIX4 m4;

	// Como z apunta hacia fuera de la pantalla (z negativo entra en pantalla), el orden de la resta cambia
	//forward = Substract(target, eyePosition);
	forward = Substract(eyePosition, target);

	xSide = CrossProduct(upVector, forward);

	yUp = CrossProduct(forward, xSide);

	// Normalizar los vectores
	forward = Normalize(forward);
	xSide = Normalize(xSide);
	yUp = Normalize(yUp);

	mRot.column0 = xSide;
	mRot.column1 = yUp;
	mRot.column2 = forward;

	m4 = InverseOrthogonalMatrix(mRot, eyePosition);

	return m4;
}


//En la siguiente función (uptadeEulerOrientation): utilizando los valores yaw, pitch, roll, y las
//funciones anteriores QuaternionFromAngleAxis y Multiply (cuaternio), actualiza la estructura EULER
//encadenando tres giros en los tres ejes X, Y y Z.
void updateEulerOrientation(EULER& euler)
{
	
	QUATERNION qPitch = QuaternionFromAngleAxis(euler.pitch, camera.up);

	VECTOR3D vectorYaw = CrossProduct(camera.up, camera.direction);

	QUATERNION qYaw = QuaternionFromAngleAxis(euler.yaw, vectorYaw);

	QUATERNION rotation = Multiply(qPitch, qYaw);
	
	euler.orientation = rotation;

	camera.up = RotateWithQuaternion(camera.up, qYaw);
}

//En la siguiente función (getForward): obtén un vector forward a partir del vector -Z, transformando
//dicho vector con la orientación obtenida en la función anterior.
VECTOR3D getForward(EULER euler)
{
	VECTOR3D ret;

	return ret;
}

//Para controlar la cámara tienes que obtener los cambios de posición del ratón y transformarlos
//en ejes EULER (yaw y pitch). La cámara debe mirar guiada por el ratón. Utiliza para ello las
//siguientes funciones de GLUT:
void HandleMouseMotion(int x, int y)\
{
	cout << "Active -> x: " << x << "\ty: " << y << endl;



	EULER rotacionEuler;
	rotacionEuler.yaw = (y - yPrev) / 100;
	rotacionEuler.pitch = (x - xPrev) / 100;

	updateEulerOrientation(rotacionEuler);

}

void HandleMousePassiveMotion(int x, int y)
{
	//cout << "Pasive -> x: " << x << "\ty: " << y << endl;


	xPrev = x;
	yPrev = y;


	
	
}
