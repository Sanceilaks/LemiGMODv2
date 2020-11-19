#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>

typedef float vec_t;

class Vector
{
public:
	// Members
	vec_t x, y, z;

	// Construction/destruction:
	Vector(void);
	Vector(vec_t X, vec_t Y, vec_t Z);
	Vector(vec_t* clr);

	// Initialization
	void Init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f);
	// TODO (Ilya): Should there be an init that takes a single float for consistency?

	// Got any nasty NAN's?
	bool IsValid() const;
	void Invalidate();

	// array access...
	vec_t operator[](int i) const;
	vec_t& operator[](int i);

	// Base address...
	vec_t* Base();
	vec_t const* Base() const;

	// Initialization methods
	void Random(vec_t minVal, vec_t maxVal);
	void Zero(); ///< zero out a Vector

	// equality
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;

	//Math operations
	void Clamp();
	Vector Clamped() const;

	const std::string& parse()
	{
		return std::string("x = ") + std::to_string(this->x) + std::string("\ty = ") + std::to_string(this->y) +
			std::string("\tz = ") + std::to_string(this->z);
	}

	// arithmetic operations
	Vector& operator+=(const Vector& v) {
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	Vector& operator-=(const Vector& v) {
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	Vector& operator*=(float fl) {
		x *= fl;
		y *= fl;
		z *= fl;
		return *this;
	}

	Vector& operator*=(const Vector& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	Vector& operator/=(const Vector& v) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	// this ought to be an opcode.
	Vector& operator+=(float fl) {
		x += fl;
		y += fl;
		z += fl;
		return *this;
	}

	// this ought to be an opcode.
	Vector& operator/=(float fl) {
		x /= fl;
		y /= fl;
		z /= fl;
		return *this;
	}
	Vector& operator-=(float fl) {
		x -= fl;
		y -= fl;
		z -= fl;
		return *this;
	}

	// negate the Vector components
	void	Negate();

	// Get the Vector's magnitude.
	vec_t	Length() const;

	// Get the Vector's magnitude squared.
	vec_t LengthSqr(void) const {
		return (x * x + y * y + z * z);
	}

	// return true if this Vector is (0,0,0) within tolerance
	bool IsZero(float tolerance = 0.01f) const {
		return (x > -tolerance && x < tolerance&&
			y > -tolerance && y < tolerance&&
			z > -tolerance && z < tolerance);
	}

	vec_t	NormalizeInPlace();
	Vector	Normalized() const;
	bool	IsLengthGreaterThan(float val) const;
	bool	IsLengthLessThan(float val) const;

	// check if a Vector is within the box defined by two other Vectors
	bool WithinAABox(Vector const& boxmin, Vector const& boxmax);

	// Get the distance from this Vector to the other one.
	vec_t	DistTo(const Vector& vOther) const;

	// Get the distance from this Vector to the other one squared.
	// NJS: note, VC wasn't inlining it correctly in several deeply nested inlines due to being an 'out of line' .  
	// may be able to tidy this up after switching to VC7
	vec_t DistToSqr(const Vector& vOther) const {
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.LengthSqr();
	}

	// Copy
	void	CopyToArray(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual Vector equation (because it's done per-component
	// rather than per-Vector).
	void	MulAdd(const Vector& a, const Vector& b, float scalar);

	// Dot product.
	vec_t	Dot(const Vector& vOther) const;

	// assignment
	Vector& operator=(const Vector& vOther);

	// 2d
	vec_t	Length2D(void) const {
		return sqrt(x * x + y * y);
	}
	vec_t	Length2DSqr(void) const;

	/// get the component of this Vector parallel to some other given Vector
	Vector  ProjectOnto(const Vector& onto);

	// copy constructors
	//	Vector(const Vector &vOther);

	// arithmetic operations
	Vector	operator-(void) const;

	Vector	operator+(const Vector& v) const;
	Vector	operator-(const Vector& v) const;
	Vector	operator*(const Vector& v) const;
	Vector	operator/(const Vector& v) const;
	Vector	operator*(float fl) const;
	Vector	operator/(float fl) const;

	// Cross product between two Vectors.
	Vector	Cross(const Vector& vOther) const;

	// Returns a Vector with the min or max in X, Y, and Z.
	Vector	Min(const Vector& vOther) const;
	Vector	Max(const Vector& vOther) const;
};

void VectorCopy(const Vector& src, Vector& dst);
float VectorLength(const Vector& v);
void VectorLerp(const Vector& src1, const Vector& src2, vec_t t, Vector& dest);
void VectorCrossProduct(const Vector& a, const Vector& b, Vector& result);
vec_t NormalizeVector(Vector& v);


class __declspec(align(16)) VectorAligned : public Vector {
public:
	inline VectorAligned(void) {};
	inline VectorAligned(vec_t X, vec_t Y, vec_t Z) {
		Init(X, Y, Z);
	}

public:
	explicit VectorAligned(const Vector& vOther) {
		Init(vOther.x, vOther.y, vOther.z);
	}

	VectorAligned& operator=(const Vector& vOther) {
		Init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	//VectorAligned& operator=(const VectorAligned& vOther) {
	//	_mm_store_ps(Base(), _mm_load_ps(vOther.Base()));
	//	return *this;
	//}

	float w;
};
FORCEINLINE void VectorSubtract(const Vector& a, const Vector& b, Vector& c)
{
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}
FORCEINLINE void VectorAdd(const Vector& a, const Vector& b, Vector& c)
{
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

//struct cplane_t
//{
//	Vector normal;
//	float dist;
//	unsigned char type;			// for fast side tests
//	unsigned char signbits;		// signx + (signy<<1) + (signz<<1)
//	unsigned char pad[2];
//
//	cplane_t() {}
//
//private:
//	// No copy constructors allowed if we're in optimal mode
//	cplane_t(const cplane_t& vOther);
//};

//class vec3_t {
//public:
//	vec3_t();
//	vec3_t(float, float, float);
//	~vec3_t();
//
//	float x, y, z;
//
//	vec3_t& operator+=(const vec3_t& v) {
//		x += v.x; y += v.y; z += v.z; return *this;
//	}
//	vec3_t& operator-=(const vec3_t& v) {
//		x -= v.x; y -= v.y; z -= v.z; return *this;
//	}
//	vec3_t& operator*=(float v) {
//		x *= v; y *= v; z *= v; return *this;
//	}
//	vec3_t operator+(const vec3_t& v) {
//		return vec3_t{ x + v.x, y + v.y, z + v.z };
//	}
//	vec3_t operator-(const vec3_t& v) {
//		return vec3_t{ x - v.x, y - v.y, z - v.z };
//	}
//	vec3_t operator*(float fl) const {
//		return vec3_t(x * fl, y * fl, z * fl);
//	}
//	vec3_t operator*(const vec3_t& v) const {
//		return vec3_t(x * v.x, y * v.y, z * v.z);
//	}
//	vec3_t& operator/=(float fl) {
//		x /= fl;
//		y /= fl;
//		z /= fl;
//		return *this;
//	}
//	auto operator-(const vec3_t& other) const -> vec3_t {
//		auto buf = *this;
//
//		buf.x -= other.x;
//		buf.y -= other.y;
//		buf.z -= other.z;
//
//		return buf;
//	}
//
//	auto operator/(float other) const {
//		vec3_t vec;
//		vec.x = x / other;
//		vec.y = y / other;
//		vec.z = z / other;
//		return vec;
//	}
//
//	float& operator[](int i) {
//		return ((float*)this)[i];
//	}
//	float operator[](int i) const {
//		return ((float*)this)[i];
//	}
//
//	inline float Length2D() const {
//		return sqrt((x * x) + (y * y));
//	}
//	void crossproduct(vec3_t v1, vec3_t v2, vec3_t cross_p) const {
//		cross_p.x = (v1.y * v2.z) - (v1.z * v2.y); //i
//		cross_p.y = -((v1.x * v2.z) - (v1.z * v2.x)); //j
//		cross_p.z = (v1.x * v2.y) - (v1.y * v2.x); //k
//	}
//
//	vec3_t cross(const vec3_t& vOther) const {
//		vec3_t res;
//		crossproduct(*this, vOther, res);
//		return res;
//	}
//
//	void init(float ix, float iy, float iz);
//	void clamp();
//	vec3_t clamped();
//	vec3_t normalized();
//	float distance_to(const vec3_t& other);
//	void normalize();
//	float length();
//	float length_sqr();
//	float length_2d_sqr(void) const;
//	float dot(const vec3_t other);
//	float dot(const float* other);
//};
//
//inline vec3_t operator*(float lhs, const vec3_t& rhs) {
//	return vec3_t(rhs.x * lhs, rhs.x * lhs, rhs.x * lhs);
//}