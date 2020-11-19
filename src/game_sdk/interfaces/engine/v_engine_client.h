#pragma once
#include <math/qangle.h>
#include <math/matrix.h>
#include <stdint.h>
#include <d3d9.h>
#include <d3d9.h>


typedef struct player_info_s {
	int64_t __pad0;
	int xuid_low;
	int xuid_high;
	char m_player_name[256];
	int m_user_id;
	char m_steam_id[33];
	unsigned int m_steam3_id;
	char m_friends_name[256];
	bool m_is_fake_player;
	bool m_is_hltv;
	unsigned int m_custom_files[4];
	unsigned char m_files_downloaded;
} player_info_t;


typedef struct InputContextHandle_t__* input_context_handle_t;
struct client_textmessage_t;
class model_t;
class surf_info;
class i_material;
class c_sentence;
class c_audio_source;
class audio_state_t;
class i_spatial_query;
class i_material_system;
class c_phys_collide;
class i_achievement_mngr;
class i_net_channel_info;
class isp_shared_memory;
class c_gamestats_data;
class key_values;
class c_steam_api_context;
struct frustum_t;
class pfn_demo_custom_data_callback;

class VEngineClient
{
public:
	int get_local_player()			//Get LocalPlayer INDEX. NOT OBJECT!
	{
		using orig_fn = int(__thiscall*)(VEngineClient*);
		return (*(orig_fn**)this)[12](this);
	}

	float get_last_time_stamp()
	{
		using orig_fn = float(__thiscall*)(VEngineClient*);
		return(*(orig_fn**)this)[14](this);
	}

	const char* get_level_name()
	{
		using orig_fn = const char* (__thiscall*)(VEngineClient*);
		return(*(orig_fn**)this)[53](this);
	}
	bool is_in_game()
	{
		using orig_fn = bool(__thiscall*)(VEngineClient*);
		return(*(orig_fn**)this)[26](this);					//26
	}

	bool get_player_info(int index, player_info_t* info)
	{
		using orig_fn = bool(__thiscall*)(VEngineClient*, int, player_info_t*);
		return(*(orig_fn**)this)[8](this, index, info);
	}

	const VMatrix& get_view_matrix()
	{
		using orig_fn = const VMatrix& (__thiscall*)(VEngineClient*);
		return(*(orig_fn**)this)[36](this);
	}

	void get_screen_size(int& width, int& height) {
		using original_fn = void(__thiscall*)(VEngineClient*, int&, int&);
		return (*(original_fn**)this)[5](this, width, height);
	}

	void get_view_angles(QAngle& Angle)
	{
		using original_fn = void(__thiscall*)(VEngineClient*, Vector&);
		return (*(original_fn**)this)[19](this, Angle);
	}

	void set_view_angles(QAngle& Angle)
	{
		using original_fn = void(__thiscall*)(VEngineClient*, Vector&);
		return (*(original_fn**)this)[20](this, Angle);
	}
	int get_max_clients()
	{
		using orig_fn = int(__thiscall*)(VEngineClient*);
		return(*(orig_fn**)this)[21](this);
	}

	bool is_taking_screenshot()
	{
		using fn = bool(__thiscall*)(VEngineClient*);
		return (*(fn**)this)[86](this); //86
	}
};