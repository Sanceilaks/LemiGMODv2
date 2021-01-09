#pragma once
#include "qangle.h"
#include "vector.h"
#include "matrix.h"
#include "vector2d.h"
#include "vector4d.h"
#include <algorithm>	//C4067

#pragma warning( push )
#pragma warning( disable : 4067) //4244

#ifdef min
#undef min;
#endif

#ifdef max
#undef max;
#endif

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.

// NJS: Inlined to prevent floats from being autopromoted to doubles, as with the old system.
#ifndef RAD2DEG
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif

#ifndef DEG2RAD
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif

enum
{
	FRUSTUM_RIGHT = 0,
	FRUSTUM_LEFT = 1,
	FRUSTUM_TOP = 2,
	FRUSTUM_BOTTOM = 3,
	FRUSTUM_NEARZ = 4,
	FRUSTUM_FARZ = 5,
	FRUSTUM_NUMPLANES = 6
};

struct vrect_t
{
	int				x, y, width, height;
	vrect_t* pnext;
};

struct Box {
	float x, y, w, h;
	Box() = default;
	Box(float x, float y, float w, float h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
};

class CMath
{
public:
	constexpr float deg_to_rad(float val);
	constexpr float rad_to_deg(float val);

	bool world_to_screen2(const Vector& in, Vector& out);
	bool world_to_screen(Vector in, Vector& out);
	float get_fov(QAngle viewAngle, QAngle aimAngle);

	template< typename t = float >
	void clamp(t& val, t& min, t& max) {
		// check type.
		static_assert(std::is_arithmetic< t >::value, "clamp only integral types.");
		val = (t)_mm_cvtss_f32(
			_mm_min_ss(_mm_max_ss(_mm_set_ss((float)val), _mm_set_ss((float)min)),
				_mm_set_ss((float)max))
		);
	}

	template < typename t >
	t fclamp(t in, t low, t high) 
	{
		#ifdef min
		#undef min;
		#endif
		#ifdef max
		#undef max;
		#endif
		return std::min(std::max(in, low), high);
	}
}; extern CMath* Math;


#pragma warning( pop )