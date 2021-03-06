#include "camera.h"

#include <math.h>


extern CAMERA camera;
extern EULER rotacionEuler;

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


//En la siguiente funcion (uptadeEulerOrientation): utilizando los valores yaw, pitch, roll, y las
//funciones anteriores QuaternionFromAngleAxis y Multiply (cuaternio), actualiza la estructura EULER
//encadenando tres giros en los tres ejes X, Y y Z.
void updateEulerOrientation(EULER& euler)
{




	VECTOR3D xAxis = Normalize(CrossProduct(camera.up, camera.direction));
	VECTOR3D upAxis = Normalize(CrossProduct(camera.direction, xAxis));

	VECTOR3D direction = RotateWithQuaternion(camera.direction, QuaternionFromAngleAxis(rotacionEuler.yaw, xAxis));
	direction = RotateWithQuaternion(direction, QuaternionFromAngleAxis(rotacionEuler.pitch, upAxis));

	//Hay que actualizar los parametros de la camara puesto que son estos los que se utilizan en
	// la funcion Display (Marcada como funcion de pintado para OpenGL). Si se llamara a lookAt
	// para actualizar la camara, la matriz generada se sobreescribiria en la siguiente llamada
	// a display, puesto que display tambien llama a lookAt (pasando los vectores de la camara)
	camera.direction = direction;
	camera.up = upAxis;


}

VECTOR3D getUp(EULER euler)
{
	VECTOR3D ret;

	//ret = RotateWithQuaternion({0, 0, -1}, euler.orientation);
	ret = Normalize(camera.up);
	return ret;
}

//En la siguiente funciÃ³n (getForward): obtÃ©n un vector forward a partir del vector -Z, transformando
//dicho vector con la orientaciÃ³n obtenida en la funciÃ³n anterior.
VECTOR3D getForward(EULER euler)
{
	VECTOR3D ret;

	ret = Normalize(camera.direction);
	return ret;
}


