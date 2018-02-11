#include "math3d.h"

#include <math.h>

VECTOR3D Add(VECTOR3D a, VECTOR3D b) //Ya implementado como ejemplo.
{
	VECTOR3D ret;
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return ret;
}

VECTOR3D Substract(VECTOR3D a, VECTOR3D b)
{
	VECTOR3D ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return ret;
}

VECTOR3D Multiply(VECTOR3D a, VECTOR3D b)
{
	VECTOR3D ret;
	ret.x = a.x * b.x;
	ret.y = a.y * b.y;
	ret.z = a.z * b.z;
	return ret;
}

VECTOR3D MultiplyWithScalar(float scalar, VECTOR3D a)
{
	VECTOR3D ret;
	ret.x = a.x * scalar;
	ret.y = a.y * scalar;
	ret.z = a.z * scalar;
	return ret;
}

double Magnitude(VECTOR3D a)
{
	double valor = 0;

	valor = sqrt( (a.x * a.x) + (a.y * a.y) + (a.z * a.z) );

	return valor;
}

VECTOR3D Normalize(VECTOR3D a)
{
	VECTOR3D ret;

	double magnitudVector = Magnitude(a);

	ret.x = a.x / magnitudVector;
	ret.y = a.y / magnitudVector;
	ret.z = a.z / magnitudVector;

	return ret;
}

VECTOR3D CrossProduct(VECTOR3D a, VECTOR3D b) {

	VECTOR3D ret;

	ret.x = (a.y * b.z) - (b.y * a.z);
	ret.y = - ( (a.x * b.z) - (b.x * a.z) );
	ret.z = (a.x * b.y) - (b.x * a.y);

	return ret;
}

double DotProduct(VECTOR3D a, VECTOR3D b)
{
	double valor = 0;

	valor = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);

	return valor;
}

MATRIX3 Transpose(MATRIX3 m)
{
	MATRIX3 ret;

	ret.column0.x = m.column0.x;
	ret.column0.y = m.column1.x;
	ret.column0.z = m.column2.x;

	ret.column1.x = m.column0.y;
	ret.column1.y = m.column1.y;
	ret.column1.z = m.column2.y;

	ret.column2.x = m.column0.z;
	ret.column2.y = m.column1.z;
	ret.column2.z = m.column2.z;

	return ret;
}

VECTOR3D Transform(MATRIX3 m, VECTOR3D a)
{
	// Vector a devolver
	VECTOR3D ret;

	// Se utiliza una variable auxiliar para obtener la traspuesta de la matriz
	MATRIX3 mat = Transpose(m);

	// Se multiplica la matriz por el vector
	ret.x = DotProduct(mat.column0, a);
	ret.y = DotProduct(mat.column1, a);
	ret.z = DotProduct(mat.column2, a);

	return ret;
}

MATRIX4 InverseOrthogonalMatrix(MATRIX3 A, VECTOR3D t)
{
	MATRIX4 ret;

	MATRIX3 traspuesta = Transpose(A);

	ret.m[0] = traspuesta.column0.x;
	ret.m[1] = traspuesta.column0.y;
	ret.m[2] = traspuesta.column0.z;

	ret.m[3] = 0;

	ret.m[4] = traspuesta.column1.x;
	ret.m[5] = traspuesta.column1.y;
	ret.m[6] = traspuesta.column1.z;

	ret.m[7] = 0;

	ret.m[8] = traspuesta.column2.x;
	ret.m[9] = traspuesta.column2.y;
	ret.m[10] = traspuesta.column2.z;

	ret.m[11] = 0;


	ret.m[12] = - DotProduct(t, A.column0);
	ret.m[13] = - DotProduct(t, A.column1);
	ret.m[14] = - DotProduct(t, A.column2);
		
	ret.m[15] = 1;


	/*ret.m[0] = A.column0.x;
	ret.m[1] = A.column0.y;
	ret.m[2] = A.column0.z;

	ret.m[3] = 0;

	ret.m[4] = A.column0.x;
	ret.m[5] = A.column0.y;
	ret.m[6] = A.column0.z;

	ret.m[7] = 0;

	ret.m[8] = A.column0.x;
	ret.m[9] = A.column0.y;
	ret.m[10] = A.column0.z;

	ret.m[11] = 0;


	ret.m[12] = -DotProduct(t, A.column0);
	ret.m[13] = -DotProduct(t, A.column1);
	ret.m[14] = -DotProduct(t, A.column2);

	ret.m[15] = 1;*/
	
	return ret;
}