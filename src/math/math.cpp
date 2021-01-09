#include "math.h"
#include <math/matrix.h>
#include <interfaces.h>
#include <globals.h>

CMath* Math = new CMath();

constexpr float CMath::deg_to_rad(float val) {
	return val * (M_PI / 180.f);
}

// radians to degrees.
constexpr float CMath::rad_to_deg(float val) {
	return val * (180.f / M_PI);
}

static bool screen_transform(const Vector& in, Vector& out)
{
	static auto& w2sMatrix = Interfaces->engine->get_view_matrix();;

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

bool CMath::world_to_screen2(const Vector& in, Vector& out)
{
	if (screen_transform(in, out)) {
		out.x = (globals->screen_width / 2.0f) + (out.x * globals->screen_width) / 2.0f;
		out.y = (globals->screen_height / 2.0f) - (out.y * globals->screen_height) / 2.0f;

		return true;
	}
	return false;
}

bool CMath::world_to_screen(Vector in, Vector& out)
{
	const VMatrix w2sm = Interfaces->engine->get_view_matrix();
	float w = w2sm[3][0] * in.x + w2sm[3][1] * in.y + w2sm[3][2] * in.z + w2sm[3][3];

	if (w > 0.001f)
	{
		int width, height; width = globals->screen_width; height = globals->screen_height;

		float fl1DBw = 1 / w;
		out.x = (width / 2) + (0.5f * ((w2sm[0][0] * in.x + w2sm[0][1] * in.y + w2sm[0][2] * in.z + w2sm[0][3]) * fl1DBw) * width + 0.5f);
		out.y = (height / 2) - (0.5f * ((w2sm[1][0] * in.x + w2sm[1][1] * in.y + w2sm[1][2] * in.z + w2sm[1][3]) * fl1DBw) * height + 0.5f);
		return true;
	}
	return false;
}

float CMath::get_fov(QAngle viewAngle, QAngle aimAngle)
{
	QAngle delta = aimAngle - viewAngle;
	normalize_angles(delta);
	delta.Clamp();
	return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}
