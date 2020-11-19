#pragma once
#include "i_client_entity.h"
#include <tools/netvars/netvars.h>
#include <cstdint>
#include <interfaces.h>

enum ECSPlayerBones {
	pelvis = 0,
	spine_0,
	spine_1,
	spine_2,
	spine_3,
	neck_0,
	head_0,
	clavicle_L,
	arm_upper_L,
	arm_lower_L,
	hand_L
};

class CCollideable
{
public:
	virtual void unknown_0() = 0;
	virtual Vector& mins() = 0;
	virtual Vector& maxs() = 0;
};


class CBaseEntity : public IClientEntity
{
public:
	NETVAR("DT_BaseEntity", "m_vecOrigin", get_origin, Vector);
	NETVAR("DT_BaseEntity", "m_vecAngles", get_angels, Vector);
	NETVAR("DT_BaseEntity", "m_nModelIndex", get_model_index, int);
	NETVAR("DT_BaseEntity", "m_iTeamNum", get_team_num, int);
	NETVAR("DT_BasePlayer", "m_vecViewOffset[0]", get_view_offset, Vector);

	inline Vector get_eye_pos() { return this->get_origin() + this->get_view_offset(); }
	static inline CBaseEntity* get_by_index(int i) { return (CBaseEntity*)Interfaces->entity_list->get_entity_by_index(i); }

	CCollideable* collideable()
	{
		using original_fn = CCollideable * (__thiscall*)(void*);
		return (*(original_fn**)this)[3](this);
	}

	bool is_alive()
	{
		using original_fn = bool(__thiscall*)(void*);
		return (*(original_fn**)this)[129](this);
	}

	bool is_player()
	{
		using original_fn = bool(__thiscall*)(void*);
		return (*(original_fn**)this)[130](this);
	}

	bool is_visible_by(CBaseEntity* from)
	{
		Ray_t ray;
		trace_t tr;
		CTraceFilter filter;
		filter.pSkip = from;

		Vector eye_pos = from->get_eye_pos();
		Vector end_pos = this->get_eye_pos();

		ray.Init(eye_pos, end_pos);

		Interfaces->engine_trace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr);


		if (tr.m_pEnt == this || tr.fraction >= 0.98f)
			return true;
		return false;
	}

	const Vector& get_entity_bone(int Bone)
	{
		matrix3x4_t boneMatrix[128];

		if (!this->SetupBones(boneMatrix, 128, 0x00000100, Interfaces->engine->get_last_time_stamp()))
			return Vector();

		matrix3x4_t hitbox = boneMatrix[Bone];

		return Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
	}
};