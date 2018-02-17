#include "math3d.h"

#include <math.h>

void InitCamera(int);



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

	valor = sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));

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
	ret.y = -((a.x * b.z) - (b.x * a.z));
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


	ret.m[12] = -DotProduct(t, A.column0);
	ret.m[13] = -DotProduct(t, A.column1);
	ret.m[14] = -DotProduct(t, A.column2);

	ret.m[15] = 1;

	return ret;
}

// Rotar respecto un vector director un angulo en degrees.

// Devolver un rotor con vector unitario
QUATERNION QuaternionFromAngleAxis(float angle, VECTOR3D axis)
{
	VECTOR3D vectorUnitario = Normalize(axis);

	QUATERNION rotor;
	double anguloRadianes = DTOR * angle;

	float coseno = cos(anguloRadianes / 2);
	float seno = sin(anguloRadianes / 2);

	rotor.s = coseno;
	rotor.v = MultiplyWithScalar(-seno, vectorUnitario);

	return rotor;

}

// Cuaternio necesario para transformar el vector From en el Vector To
QUATERNION QuaternionFromToVectors(VECTOR3D from, VECTOR3D to)
{
	QUATERNION fromQuaternion;
	QUATERNION toQuaternion;
	QUATERNION ret;

	VECTOR3D fromNormalized;
	VECTOR3D toNormalized;

	double cosenoAngulo;
	double angulo;

	// Se utiliza para interpolar el quaternion en la mitad del angulo formado;
	// Por eso se inicializa a 0.5
	double factor = 0.5;


	fromNormalized = Normalize(from);
	toNormalized = Normalize(to);

	// A . B = ||A|| ||B|| cos(Angulo)
	cosenoAngulo = DotProduct(from, to);

	angulo = acos(cosenoAngulo);

	fromQuaternion = Vector3DToQuaternion(fromNormalized);
	toQuaternion = Vector3DToQuaternion(toNormalized);

	ret = SLERP_Quaternion(fromQuaternion, toQuaternion, factor, angulo);

	return ret;
}

// Multiplicar dos QUATERNIONs
QUATERNION Multiply(QUATERNION a, QUATERNION b)
{
	QUATERNION ret;
	VECTOR3D v1, v2, vCross;

	// Factor de tolerancia utilizado para redondear
	float tolerancia = 0.000001;

	// Obtener escalar del nuevo QUATERNION
	ret.s = (a.s * b.s) - DotProduct(a.v, b.v);

	// Vectores intermedios para calcular la parte Vectorial del nuevo QUATERNION
	v1 = MultiplyWithScalar(a.s, b.v);
	v2 = MultiplyWithScalar(b.s, a.v);
	vCross = CrossProduct(a.v, b.v);

	// Calcular el Vector3d del nuevo QUATERNION
	ret.v = Add(v1, v2);
	ret.v = Add(ret.v, vCross);


	return ret;
}

// Invertir el signo de la parte vectorial del QUATERNION
QUATERNION Conjugate(QUATERNION a)
{
	QUATERNION aConjugado;
	aConjugado.s = a.s;
	aConjugado.v = MultiplyWithScalar(-1.0, a.v);

	return aConjugado;
}

//A es un punto que es rotado por el quaterion Q
VECTOR3D RotateWithQuaternion(VECTOR3D a, QUATERNION q)
{
	QUATERNION aQuaternion;
	QUATERNION aQuaternionRotado;
	QUATERNION qConjugado;

	aQuaternion = Vector3DToQuaternion(a);

	qConjugado = Conjugate(q);

	aQuaternionRotado = Multiply(q, Multiply(aQuaternion, qConjugado));
	return aQuaternionRotado.v;


	// Metodo alternativo para rotar el vector a con el quaternion q
	// Parece funcionar correctamente, pero ttiene problemas de redondeo
	/*t = 2 * cross(q.xyz, v)
	v' = v + q.w * t + cross(q.xyz, t)*/

	/*VECTOR3D interm = CrossProduct(q.v, a);

	VECTOR3D interm2 = MultiplyWithScalar(2, interm);

	VECTOR3D interm3 = MultiplyWithScalar(q.s, interm2);
	VECTOR3D interm4 = CrossProduct(q.v, interm2);

	VECTOR3D interm5 = Add(interm3, interm4);
	VECTOR3D ret = Add(a, interm5);

	return ret;*/

}

QUATERNION MultiplyByScalar(float scalar, QUATERNION q)
{
	QUATERNION ret;

	ret.s = scalar * q.s;
	ret.v = MultiplyWithScalar(scalar, q.v);

	return ret;
}

QUATERNION AddQuaternions(QUATERNION q1, QUATERNION q2)
{
	QUATERNION ret;
	ret.s = q1.s + q2.s;
	ret.v = Add(q1.v, q2.v);

	return ret;
}

QUATERNION Vector3DToQuaternion(VECTOR3D v)
{
	QUATERNION ret;

	ret.s = 0;
	ret.v = v;

	return ret;
}


QUATERNION SLERP_Quaternion(QUATERNION q1, QUATERNION q2, float t, double angulo)
{
	QUATERNION ret;
	QUATERNION step1;
	QUATERNION step2;



	step1 = MultiplyByScalar(sin((1 - t) * angulo) / sin(angulo), q1);

	step2 = MultiplyByScalar(sin(t * angulo) / sin(angulo), q2);

	ret = AddQuaternions(step1, step2);

	return ret;
}

