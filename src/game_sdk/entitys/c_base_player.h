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
	NETVAR("DT_BaseCombatCharacter", "m_hActiveWeapon", ActiveWeaponHandle, uintptr_t);
	NETVAR("DT_BasePlayer", "m_vecVelocity[0]", get_velocity, Vector);
	
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

		color.SetColor(r, g, b);
		return color;
	}

	//void set_view_angels(QAngle& ang)
	//{
	//	using fn = void(__thiscall*)(CBasePlayer*, QAngle&);
	//	return (*(fn**)this)[444](this, ang);
	//}
};