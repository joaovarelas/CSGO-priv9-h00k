#pragma once

#include <iostream>
#include <cstdlib>



// don't ask about this garbage code. I just didn't feel like changing anything and moving stuff around.
typedef float vec_t;
typedef unsigned int uint32;




#define FLOAT32_NAN BitsToFloat( FLOAT32_NAN_BITS )
#define VALVE_RAND_MAX 0x7FFF
#define Assert(_exp)	
#define FLOAT32_NAN_BITS     (uint32)0x7FC00000	// not a number!
#define VEC_T_NAN FLOAT32_NAN



vec_t BitsToFloat(uint32 i);

uint32 const FloatBits(const vec_t &f);

inline bool IsFinite(const vec_t &f);


class QAngle
{
public:
	// Members
	vec_t x, y, z;

	// Construction/destruction
	QAngle(void)
	{
#ifdef _DEBUG
#ifdef VECTOR_PARANOIA
		// Initialize to NAN to catch errors
		x = y = z = VEC_T_NAN;
#endif
#endif
	}

	QAngle(vec_t X, vec_t Y, vec_t Z)
	{
		x = X; y = Y; z = Z;
	}
	//	QAngle(RadianEuler const &angles);	// evil auto type promotion!!!

	// Allow pass-by-value
	//operator QAngleByValue &() { return *((QAngleByValue *)(this)); }
	//operator const QAngleByValue &() const { return *((const QAngleByValue *)(this)); }

	// Initialization
	void Init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f)
	{
		x = ix; y = iy; z = iz;
	}

	void Random(vec_t minVal, vec_t maxVal)
	{
		x = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
		y = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
		z = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
	}

	// Got any nasty NAN's?
	bool IsValid()
	{
		return IsFinite(x) && IsFinite(y) && IsFinite(z);
	}

	void Invalidate()
	{
		//#ifdef _DEBUG
		//#ifdef VECTOR_PARANOIA
		x = y = z = VEC_T_NAN;
		//#endif
		//#endif
	}

	// array access...
	vec_t operator[](int i) const;

	vec_t& operator[](int i)
	{
		Assert((i >= 0) && (i < 3));
		return ((vec_t*)this)[i];
	}

	// Base address...
	vec_t* Base();
	vec_t const* Base() const;

	// equality
	//bool operator==(const QAngle& v) const;
	//bool operator!=(const QAngle& v) const;

	// arithmetic operations
	//QAngle&	operator+=(const QAngle &v);
	//QAngle&	operator-=(const QAngle &v);
	//QAngle&	operator*=(float s);
	//QAngle&	operator/=(float s);

	// Get the vector's magnitude.
	vec_t	Length() const;
	vec_t	LengthSqr() const;

	// negate the QAngle components
	//void	Negate(); 

	// Dump QAngle output
	__inline void dump(const char* name)
	{
		printf("%s: %.2f %.2f %.2f\n", name, x, y, z);
	}

	// No assignment operators either...
	//QAngle& operator=(const QAngle& src);

#ifndef VECTOR_NO_SLOW_OPERATIONSw
	// copy constructors

	// arithmetic operations
	QAngle	operator-(void) const;


	QAngle	operator+(const QAngle& v) const;
	QAngle	operator-(const QAngle& v) const;
	QAngle	operator*(float fl) const;
	QAngle	operator/(float fl) const;
#else

private:
	// No copy constructors allowed if we're in optimal mode
	QAngle(const QAngle& vOther);

#endif
};



