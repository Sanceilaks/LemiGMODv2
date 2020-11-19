#pragma once
#include "vector.h"


typedef Vector QAngle;


static float normalize_angel(float angle)
{
	if (angle > 180.f || angle < -180.f) {
		auto revolutions = std::round(std::abs(angle / 360.f));

		if (angle < 0.f)
			angle = angle + 360.f * revolutions;
		else
			angle = angle - 360.f * revolutions;
	}

	return angle;
}

static QAngle CalcAngle(const Vector& src, const Vector& dst)
{
	QAngle vAngle;
	Vector delta((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));
	double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);

	vAngle.x = float(atanf(float(delta.z / hyp)) * 57.295779513082f);
	vAngle.y = float(atanf(float(delta.y / delta.x)) * 57.295779513082f);
	vAngle.z = 0.0f;

	if (delta.x >= 0.0)
		vAngle.y += 180.0f;

	return vAngle;
}

static void normalize_angles(QAngle& angles)
{
	for (auto i = 0; i < 3; i++)
	{
		while (angles[i] < -180.0f)
		{
			angles[i] += 360.0f;
		}
		while (angles[i] > 180.0f)
		{
			angles[i] -= 360.0f;
		}
	}
}