#pragma once
#include "c_base_entity.h"

class CBaseCombatWeapon : public CBaseEntity
{
public:
	NETVAR("DT_BaseCombatWeapon", "m_nSequence", get_sequence, int);
	NETVAR("DT_BaseCombatWeapon", "m_nForceBone", get_froce_bone, int);
	NETVAR("DT_BaseCombatWeapon", "m_iClip1", get_clip1, int);
	NETVAR("DT_BaseCombatWeapon", "m_iClip2", get_clip2, int);
	NETVAR("DT_BaseCombatWeapon", "m_iPrimaryAmmoType", get_primary_ammo_type, int);
	NETVAR("DT_BaseCombatWeapon", "m_iSecondaryAmmoType", get_secoundary_ammo_type, int);
	NETVAR("DT_BaseCombatWeapon", "m_flNextPrimaryAttack", get_next_primary_attack, float);
	NETVAR("DT_BaseCombatWeapon", "m_flNextSecondaryAttack", get_next_secondary_attack, float);
	NETVAR("DT_BaseCombatWeapon", "m_nNextThinkTick", get_next_think_tick, int);
	NETVAR("DT_BaseCombatWeapon", "m_iState", get_state, int);
	NETVAR("DT_BaseCombatWeapon", "m_hOwner", get_owner_handle, uintptr_t);	
};