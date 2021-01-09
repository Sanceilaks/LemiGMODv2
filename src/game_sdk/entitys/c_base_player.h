#pragma once
#include "c_base_entity.h"
#include <string>
#include <tools/color.h>

enum EMoveType
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4,
	MAX_MOVETYPE
};

class CBasePlayer : public CBaseEntity
{
public:
	NETVAR("DT_BasePlayer", "m_fFlags", get_flags, int);
	NETVAR("DT_BasePlayer", "m_vecViewOffset[0]", get_view_offset, Vector);
	NETVAR("DT_BasePlayer", "m_hActiveWeapon", active_weapon_handle, uintptr_t);
	NETVAR("DT_BasePlayer", "m_vecVelocity[0]", get_velocity, Vector);
	NETVAR("DT_BasePlayer", "hMyWeapons", get_weapons, uintptr_t);
	NETVAR("DT_BasePlayer", "m_bloodColor", get_blood_color, Color);
	NETVAR("DT_BasePlayer", "m_Local", get_local, uintptr_t);
	NETVAR("DT_BasePlayer", "m_iAmmo", get_ammo, int);
	NETVAR("DT_BasePlayer", "m_fOnTarget", get_on_target, int);
	NETVAR("DT_BasePlayer", "m_nTickBase", get_tick_base, float);
	NETVAR("DT_BasePlayer", "m_nNextThinkTick", get_next_think_tick, float);
	NETVAR("DT_BasePlayer", "m_flFriction", get_friction, float);
	NETVAR("DT_BasePlayer", "flDeathTime", get_death_time, float);
	NETVAR("DT_BasePlayer", "deadflag", get_dead_flag, int);
	NETVAR("DT_BasePlayer", "m_iDefaultFOV", get_default_fov, int);
	NETVAR("DT_BasePlayer", "m_hVehicle", get_vehicle_handle, uintptr_t);
	NETVAR("DT_BasePlayer", "m_iObserverMode", get_observer_mode, int);
	NETVAR("DT_BasePlayer", "m_hObserverTarget", get_observer_target_handle, uintptr_t);
		
	int get_move_type()
	{
		auto glua = Interfaces->lua_shared->get_interface(LUA::Type::client);
		
		if (!glua)
			return {};

		glua->PushSpecial((int)LUA::Special::glob);
		glua->GetField(-1, "Entity");
		glua->PushNumber(this->get_index());
		glua->Call(1, 1);

		glua->GetField(-1, "GetMoveType");
		glua->Push(-2);
		glua->Call(1, 1);

		int type = static_cast<int>(glua->GetNumber(-1));
		glua->Pop(3);

		return type;
	}
		
	
	static CBasePlayer* get_local_player()
	{
		return (CBasePlayer*)Interfaces->entity_list->get_entity_by_index(Interfaces->engine->get_local_player());
	}

	inline std::string get_name()
	{
		auto glua = Interfaces->lua_shared->get_interface(LUA::Type::client);

		if (!glua)
			return {};

		glua->PushSpecial((int)LUA::Special::glob);
		glua->GetField(-1, "Entity");
		glua->PushNumber(this->get_index());
		glua->Call(1, 1);

		glua->GetField(-1, "Name");
		glua->Push(-2);
		glua->Call(1, 1);

		std::string name = glua->GetString(-1);
		glua->Pop(3);

		return name;
	}

	inline Color get_team_color()
	{
		auto glua = Interfaces->lua_shared->get_interface(LUA::Type::client);
		Color color;
		int r, g, b;

		if (!glua)
			return Color(0, 0, 0);

		glua->PushSpecial((int)LUA::Special::glob);

		glua->PushSpecial((int)LUA::Special::glob);
		glua->GetField(-1, "team");
		glua->GetField(-1, "GetColor");
		glua->PushNumber(this->get_team_num());
		glua->Call(1, 1);

		glua->PushString("r");
		glua->GetTable(-2);
		r = glua->GetNumber(-1);
		glua->Pop();

		glua->PushString("g");
		glua->GetTable(-2);
		g = glua->GetNumber(-1);
		glua->Pop();

		glua->PushString("b");
		glua->GetTable(-2);
		b = glua->GetNumber(-1);
		glua->Pop();

		glua->Pop(4);

		color.set_color(r, g, b);
		return color;
	}

	//void set_view_angels(QAngle& ang)
	//{
	//	using fn = void(__thiscall*)(CBasePlayer*, QAngle&);
	//	return (*(fn**)this)[444](this, ang);
	//}
};