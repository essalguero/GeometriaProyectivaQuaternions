#ifndef _GEOMETRIA_PROYECTIVA_CAMERA_H_
#define _GEOMETRIA_PROYECTIVA_CAMERA_H_

#include "math3d.h"
#include <iostream>

using namespace std;

typedef struct {
	VECTOR3D position;
	VECTOR3D direction;
	VECTOR3D up;

	double aperture;    // in degrees
	int screenwidth, screenheight;

} CAMERA;

typedef struct {
	float yaw; // Rotation around the Y axis.
	float pitch; // Rotation around the X axis.
	float roll; // Rotation around the Z axis.
	QUATERNION orientation; // Cached quaternion equivalent of this euler object.
} EULER;



typedef struct {
	double left;
	double right;
	double bottom;
	double top;
	double nearValue;
	double farValue;
} FRUSTUM;

FRUSTUM makeFrustum(double fovX, double aspectRatio, double nearValue, double farValue);

// TODO
MATRIX4 lookAt(VECTOR3D eyePosition, VECTOR3D target, VECTOR3D upVector);

VECTOR3D getUp(EULER euler);

VECTOR3D getForward(EULER euler);

void updateEulerOrientation(EULER& euler);

void HandleMouseMotion(int x, int y);

void HandleMousePassiveMotion(int x, int y);


#endif
