#include "vector.h"

#include <cmath>
#include <limits>
#include <algorithm>

void VectorCopy(const Vector& src, Vector& dst) {
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}
void VectorLerp(const Vector& src1, const Vector& src2, vec_t t, Vector& dest) {
	dest.x = src1.x + (src2.x - src1.x) * t;
	dest.y = src1.y + (src2.y - src1.y) * t;
	dest.z = src1.z + (src2.z - src1.z) * t;
}
float VectorLength(const Vector& v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
void VectorCrossProduct(const Vector& a, const Vector& b, Vector& result) {
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
}
vec_t NormalizeVector(Vector& v) {
	vec_t l = v.Length();
	if (l != 0.0f) {
		v /= l;
	}
	else {
		v.x = v.y = v.z = 0.0f;
	}
	return l;
}

Vector::Vector(void) {
	Invalidate();
}
Vector::Vector(vec_t X, vec_t Y, vec_t Z) {
	x = X;
	y = Y;
	z = Z;
}
Vector::Vector(vec_t* clr) {
	x = clr[0];
	y = clr[1];
	z = clr[2];
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

void Vector::Init(vec_t ix, vec_t iy, vec_t iz) {
	x = ix; y = iy; z = iz;
}

Vector Vector::Normalized() const {
	Vector res = *this;
	vec_t l = res.Length();
	if (l != 0.0f) {
		res /= l;
	}
	else {
		res.x = res.y = res.z = 0.0f;
	}
	return res;
}
vec_t Vector::NormalizeInPlace() {
	return NormalizeVector(*this);
}

void Vector::Random(vec_t minVal, vec_t maxVal) {
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
}

// This should really be a single opcode on the PowerPC (move r0 onto the vec reg)
void Vector::Zero() {
	x = y = z = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

Vector& Vector::operator=(const Vector& vOther) {
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}


//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
vec_t& Vector::operator[](int i) {
	return ((vec_t*)this)[i];
}

vec_t Vector::operator[](int i) const {
	return ((vec_t*)this)[i];
}


//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
vec_t* Vector::Base() {
	return (vec_t*)this;
}

vec_t const* Vector::Base() const {
	return (vec_t const*)this;
}

//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------

bool Vector::IsValid() const {
	return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
}

//-----------------------------------------------------------------------------
// Invalidate
//-----------------------------------------------------------------------------

void Vector::Invalidate() {
	//#ifdef _DEBUG
	//#ifdef Vector_PARANOIA
	x = y = z = std::numeric_limits<float>::infinity();
	//#endif
	//#endif
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

bool Vector::operator==(const Vector& src) const {
	return (src.x == x) && (src.y == y) && (src.z == z);
}

bool Vector::operator!=(const Vector& src) const {
	return (src.x != x) || (src.y != y) || (src.z != z);
}

//-----------------------------------------------------------------------------
// Math
//-----------------------------------------------------------------------------
void Vector::Clamp()
{
	while (this->x < -180.0f)
		this->x += 360.0f;

	while (this->x > 180.0f)
		this->x -= 360.0f;

	if (this->x > 89.0f)
		this->x = 89.0f;

	if (this->x < -89.0f)
		this->x = -89.0f;

	while (this->y < -180.0f)
		this->y += 360.0f;

	while (this->y > 180.0f)
		this->y -= 360.0f;

	this->z = 0.0f;
}

Vector Vector::Clamped() const
{
	auto vec = *this;
	vec.Clamp();
	return vec;
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------
void	Vector::CopyToArray(float* rgfl) const {
	rgfl[0] = x, rgfl[1] = y, rgfl[2] = z;
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------
// #pragma message("TODO: these should be SSE")

void Vector::Negate() {
	x = -x; y = -y; z = -z;
}

// get the component of this Vector parallel to some other given Vector
Vector Vector::ProjectOnto(const Vector& onto) {
	return onto * (this->Dot(onto) / (onto.LengthSqr()));
}

// FIXME: Remove
// For backwards compatability
void	Vector::MulAdd(const Vector& a, const Vector& b, float scalar) {
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
	z = a.z + b.z * scalar;
}

Vector VectorLerp(const Vector& src1, const Vector& src2, vec_t t) {
	Vector result;
	VectorLerp(src1, src2, t, result);
	return result;
}

vec_t Vector::Dot(const Vector& b) const {
	return (x * b.x + y * b.y + z * b.z);
}
void VectorClear(Vector& a) {
	a.x = a.y = a.z = 0.0f;
}

vec_t Vector::Length(void) const {
	return sqrt(x * x + y * y + z * z);
}

// check a point against a box
bool Vector::WithinAABox(Vector const& boxmin, Vector const& boxmax) {
	return (
		(x >= boxmin.x) && (x <= boxmax.x) &&
		(y >= boxmin.y) && (y <= boxmax.y) &&
		(z >= boxmin.z) && (z <= boxmax.z)
		);
}

//-----------------------------------------------------------------------------
// Get the distance from this Vector to the other one 
//-----------------------------------------------------------------------------
vec_t Vector::DistTo(const Vector& vOther) const {
	Vector delta;
	delta = *this - vOther;
	return delta.Length();
}

//-----------------------------------------------------------------------------
// Returns a Vector with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------
Vector Vector::Min(const Vector& vOther) const {
	return Vector(x < vOther.x ? x : vOther.x,
		y < vOther.y ? y : vOther.y,
		z < vOther.z ? z : vOther.z);
}

Vector Vector::Max(const Vector& vOther) const {
	return Vector(x > vOther.x ? x : vOther.x,
		y > vOther.y ? y : vOther.y,
		z > vOther.z ? z : vOther.z);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

Vector Vector::operator-(void) const {
	return Vector(-x, -y, -z);
}

Vector Vector::operator+(const Vector& v) const {
	return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator-(const Vector& v) const {
	return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator*(float fl) const {
	return Vector(x * fl, y * fl, z * fl);
}

Vector Vector::operator*(const Vector& v) const {
	return Vector(x * v.x, y * v.y, z * v.z);
}

Vector Vector::operator/(float fl) const {
	return Vector(x / fl, y / fl, z / fl);
}

Vector Vector::operator/(const Vector& v) const {
	return Vector(x / v.x, y / v.y, z / v.z);
}

Vector operator*(float fl, const Vector& v) {
	return v * fl;
}

//-----------------------------------------------------------------------------
// cross product
//-----------------------------------------------------------------------------

Vector Vector::Cross(const Vector& vOther) const {
	Vector res;
	VectorCrossProduct(*this, vOther, res);
	return res;
}



//vec3_t::vec3_t(void) {
//	x = y = z = 0.0f;
//}
//
//vec3_t::vec3_t(float fx, float fy, float fz) {
//	x = fx;
//	y = fy;
//	z = fz;
//}
//
//vec3_t::~vec3_t(void) {
//};
//
//void vec3_t::init(float ix, float iy, float iz) {
//	x = ix; y = iy; z = iz;
//}
//
//void vec3_t::clamp(void) {
//	x = std::clamp(x, -89.0f, 89.0f);
//	y = std::clamp(std::remainder(y, 360.0f), -180.0f, 180.0f);
//	z = std::clamp(z, -50.0f, 50.0f);
//}
//
//vec3_t vec3_t::clamped() {
//	vec3_t clamped = *this;
//	clamped.clamp();
//	return clamped;
//}
//
//float vec3_t::distance_to(const vec3_t& other) {
//	vec3_t delta;
//	delta.x = x - other.x;
//	delta.y = y - other.y;
//	delta.z = z - other.z;
//
//	return delta.length();
//}
//
//void vec3_t::normalize() {
//	x = std::isfinite(x) ? std::remainderf(x, 360.0f) : 0.0f;
//	y = std::isfinite(y) ? std::remainderf(y, 360.0f) : 0.0f;
//	z = 0.0f;
//}
//
//vec3_t vec3_t::normalized(void) {
//	vec3_t vec(*this);
//	vec.normalize();
//
//	return vec;
//}
//
//float vec3_t::length(void) {
//	float root = 0.0f, sqsr = this->length_sqr();
//
//	__asm        sqrtss xmm0, sqsr
//	__asm        movss root, xmm0
//
//	return root;
//}
//
//float vec3_t::length_sqr(void) {
//	auto sqr = [](float n) {
//		return static_cast<float>(n * n);
//	};
//
//	return (sqr(x) + sqr(y) + sqr(z));
//}
//
//float vec3_t::length_2d_sqr(void) const {
//	return (x * x + y * y);
//}
//
//float vec3_t::dot(const vec3_t other) {
//	return (x * other.x + y * other.y + z * other.z);
//}
//
//float vec3_t::dot(const float* other) {
//	const vec3_t& a = *this;
//
//	return(a.x * other[0] + a.y * other[1] + a.z * other[2]);
//}