#include "camera.h"

#include <math.h>

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