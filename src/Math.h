#pragma once

#include <stdint.h>
#include <math.h>
#include <cmath>

#include "QAngle.h"




#define PI 3.14159265358979323846f
#define RADPI 180.0f/PI

#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )
#define rad(a) a * 0.01745329251

typedef float matrix3x4[3][4];




class Vector
{
public:
	float x;
	float y;
	float z;

	inline void Init(float ix, float iy, float iz)
	{
		x = ix; y = iy; z = iz;
	}

	void Set(float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
	{
		x = X; y = Y; z = Z;
	}

	Vector() { x = 0; y = 0; z = 0; };
	Vector(float X, float Y, float Z) { x = X; y = Y; z = Z; };

	float operator[](int i) const { if (i == 1) return x; if (i == 2) return y; return z; };
	float& operator[](int i) { if (i == 1) return x; if (i == 2) return y; return z; };

	bool operator==(const Vector& v) { return true; }
	bool operator!=(const Vector& v) { return true; }

	inline Vector operator-(const Vector& v) { return Vector(x - v.x, y - v.y, z - v.z); }
	inline Vector operator+(const Vector& v) { return Vector(x + v.x, y + v.y, z + v.z); }
	inline Vector operator*(const int n) { return Vector(x*n, y*n, z*n); }
	inline Vector operator-() { return Vector(-x, -y, -z); }

	inline Vector operator=(const QAngle& v) { return Vector(v.x, v.y, v.z); }

	//Vector& operator/=(const Vector& v){
	//	x /= v.x; y /= v.y; z /= v.z; return *this;}


	inline Vector& operator+=(const Vector &v) { x += v.x; y += v.y; z += v.z; return *this; }
	inline Vector& operator/=(const float v) { x /= v; y /= v; z /= v; return *this; }
	float Length(void) { return sqrtf(x*x + y*y + z*z); }
	inline float Length2D(void) const { return sqrtf(x*x + y*y); }

	inline void Rotate2D(const float &f)
	{
		float _x, _y;

		float s, c;

		//SinCos(DEG2RAD(f), s, c);

		s = sin(DEG2RAD(f));
		c = cos(DEG2RAD(f));

		_x = x;
		_y = y;

		x = (_x * c) - (_y * s);
		y = (_x * s) + (_y * c);
	}

	inline Vector Normalize()
	{
		Vector vector;
		float length = this->Length();

		if (length != 0)
		{
			vector.x = x / length;
			vector.y = y / length;
			vector.z = z / length;
		}
		else
		{
			vector.x = vector.y = 0.0f; vector.z = 1.0f;
		}

		return vector;
	}



};

class __declspec(align(16))VectorAligned : public Vector
{
public:
	VectorAligned& operator=(const Vector &vOther)
	{
		Set(vOther.x, vOther.y, vOther.z);
		return *this;
	}
	float w;
};

struct VMatrix
{
	float m[4][4];

	inline float* operator[](int i)
	{
		return m[i];
	}

	inline const float* operator[](int i) const
	{
		return m[i];
	}
};

struct matrix3x4_t
{
	matrix3x4_t() {}
	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	void Init(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin)
	{
		m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
		m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
		m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	matrix3x4_t(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin)
	{
		Init(xAxis, yAxis, zAxis, vecOrigin);
	}

	inline void SetOrigin(Vector const & p)
	{
		m_flMatVal[0][3] = p.x;
		m_flMatVal[1][3] = p.y;
		m_flMatVal[2][3] = p.z;
	}

	inline void Invalidate(void)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_flMatVal[i][j] = VEC_T_NAN;
			}
		}
	}

	float *operator[](int i) { Assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
	const float *operator[](int i) const { Assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
	float *Base() { return &m_flMatVal[0][0]; }
	const float *Base() const { return &m_flMatVal[0][0]; }

	float m_flMatVal[3][4];
};



namespace Math {

	static bool screen_transform(const Vector& in, Vector& out);

	bool WorldToScreen(const Vector& in, Vector& out);

	float GetFov(const QAngle& viewAngle, const QAngle& aimAngle);


	void AngleVectors(const QAngle &angles, Vector& forward);

	void SinCos(float a, float* s, float*c);

	QAngle CalcAngle(const Vector& vecDiff); //NUGGAH


	void NormalizeAngles(QAngle& angle);
	inline float NormalizeAngle(float flAng);

	void ClampViewAngles(QAngle& vecAng);

	float VectorNormalize(Vector& v);

	void CalcAngleYawOnly(Vector src, Vector dst, Vector &angles);

}

