#include "math.h"
void Math::VectorTransform(const Vector in1, matrix3x4_t in2, Vector &out)
{
	out[0] = in1.Dot(in2[0]) + in2[0][3];
	out[1] = in1.Dot(in2[1]) + in2[1][3];
	out[2] = in1.Dot(in2[2]) + in2[2][3];
}
Vector Math::CalculateAngle(const Vector& in, Vector out)
{
	double delta[3] = { (in[0] - out[0]), (in[1] - out[1]), (in[2] - out[2]) };
	double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
	Vector ret = Vector();
	ret.x = (float)(asinf(delta[2] / hyp) * 57.295779513082f);
	ret.y = (float)(atanf(delta[1] / delta[0]) * 57.295779513082f);
	ret.z = 0.0f;

	if (delta[0] >= 0.0)
		ret.y += 180.0f;
	return ret;
}
void Math::VectorAngles(const Vector& forward, QAngle& angles)
{
	if (forward[1] == 0.0f && forward[0] == 0.0f)
	{
		angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f; 
		angles[1] = 0.0f; 
	}
	else
	{
		angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
		angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;

		if (angles[1] > 90)
			angles[1] -= 180;
		else if (angles[1] < 90)
			angles[1] += 180;
		else if (angles[1] == 90)
			angles[1] = 0;
	}

	angles[2] = 0.0f;
}

void Math::AngleVectors(const QAngle& angles, Vector &forward)
{
	float sp, sy, cp, cy;

	SinCos(deg2rad(angles.yaw), &sy, &cy);
	SinCos(deg2rad(angles.pitch), &sp, &cp);

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
}
void Math::SinCos(float radians, float* sine, float* cosine)
{
	*sine = sin(radians);
	*cosine = cos(radians);
}
double Math::deg2rad(double deg)
{
	return deg * M_PI / 180.;
}
double Math::rad2deg(double rad)
{
	double deg = 0;
	deg = rad * (180 / M_PI);
	return deg;
}