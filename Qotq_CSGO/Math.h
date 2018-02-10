#include <cmath>
#define _USE_MATH_DEFINES
#include "SDK.h"

namespace Math {
	void VectorTransform(const Vector in1, matrix3x4_t in2, Vector &out);
	Vector CalculateAngle(const Vector& in, Vector out);
	void AngleVectors(const QAngle& angles, Vector& forward);
	void VectorAngles(const Vector& forward, QAngle& angles);
	void SinCos(float radians, float* sine, float* cosine);
	double deg2rad(double deg);
	double rad2deg(double rad);
};