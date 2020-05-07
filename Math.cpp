#include "SDK.h"

extern Interfaces::Engine* Engine;


static bool Math::screen_transform(const Vector& in, Vector& out)
{
	static auto& w2sMatrix = Engine->WorldToScreenMatrix();

	out.x = w2sMatrix.m[0][0] * in.x + w2sMatrix.m[0][1] * in.y + w2sMatrix.m[0][2] * in.z + w2sMatrix.m[0][3];
	out.y = w2sMatrix.m[1][0] * in.x + w2sMatrix.m[1][1] * in.y + w2sMatrix.m[1][2] * in.z + w2sMatrix.m[1][3];
	out.z = 0.0f;

	float w = w2sMatrix.m[3][0] * in.x + w2sMatrix.m[3][1] * in.y + w2sMatrix.m[3][2] * in.z + w2sMatrix.m[3][3];

	if (w < 0.001f) {
		out.x *= 100000;
		out.y *= 100000;
		return false;
	}

	out.x /= w;
	out.y /= w;

	return true;
}

bool Math::WorldToScreen(const Vector& in, Vector& out)
{
	if (screen_transform(in, out)) {
		int w, h;
		Engine->GetScreenSize(w, h);

		out.x = (w / 2.0f) + (out.x * w) / 2.0f;
		out.y = (h / 2.0f) - (out.y * h) / 2.0f;

		return true;
	}
	return false;
}


float Math::GetFov(const QAngle& viewAngle, const QAngle& aimAngle)
{

	QAngle delta;
	delta.x = aimAngle.x - viewAngle.x;
	delta.y = aimAngle.y - viewAngle.y;
	delta.z = aimAngle.z - viewAngle.z;
	Math::NormalizeAngles(delta);

	return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}

void Math::AngleVectors(const QAngle &angles, Vector& forward)
{
	Assert(s_bMathlibInitialized);
	Assert(forward);

	float sp, sy, cp, cy;

	Math::SinCos(DEG2RAD(angles.x), &sy, &cy);
	Math::SinCos(DEG2RAD(angles.y), &sp, &cp);

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
}

void Math::SinCos(float a, float* s, float*c)
{
	*s = sin(a);
	*c = cos(a);
}

QAngle Math::CalcAngle(const Vector& vecDiff) // nuggah expects vecDiff to be [Destination Vector]-[Source Vector]
{
	return QAngle(std::atan2(-vecDiff.z, vecDiff.Length2D())*RADPI, std::atan2(vecDiff.y, vecDiff.x)*RADPI, 0.0f);
}

void Math::NormalizeAngles(QAngle& angle)
{
	while (angle.x > 89.0f)
		angle.x -= 180.f;

	while (angle.x < -89.0f)
		angle.x += 180.f;

	while (angle.y > 180.f)
		angle.y -= 360.f;

	while (angle.y < -180.f)
		angle.y += 360.f;
}

inline float Math::NormalizeAngle(float flAng)
{
	if (!std::isfinite(flAng))
		return 0.0f;


	return std::remainder(flAng, 360.0f);
}

void Math::ClampViewAngles(QAngle& vecAng)
{
	vecAng.x = max(-89.0f, min(89.0f, NormalizeAngle(vecAng.x)));
	vecAng.y = NormalizeAngle(vecAng.y);
	vecAng.z = 0.0f;
}


float Math::VectorNormalize(Vector& v)
{
	float flLength = v.Length();

	if (!flLength)
		v.Set();
	else
		v /= flLength;


	return flLength;
}

void Math::CalcAngleYawOnly(Vector src, Vector dst, Vector &angles)
{
	Vector delta = src - dst;
	double hyp = delta.Length2D();
	angles.y = (atan(delta.y / delta.x) * 57.295779513082f);
	//	angles.x = (atan(delta.z / hyp) * 57.295779513082f);
	angles[2] = 0.00;

	if (delta.x >= 0.0)
		angles.y += 180.0f;
}


