#pragma once
#include <vector>
#include <game_sdk/entitys/c_base_entity.h>

class CGlowObject
{
public:
	CBaseEntity* entity;
	Color glow_color;

	bool valid()
	{
		return entity != nullptr;
	}
};


class CGlowSystem
{
private:
	std::vector<CGlowObject> glow_objects;
public:
	void add_object(CGlowObject obj);


	void render();
}; extern CGlowSystem* glow_system;