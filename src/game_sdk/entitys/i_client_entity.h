#pragma once

#include <math/qangle.h>
#include <math/matrix.h>
#include <game_sdk/classes/c_client_class.h>
#include <stdint.h>

class CBaseHandle;
class IHandleEntity;
class IClientUnknown;

class IHandleEntity {
public:
	virtual							~IHandleEntity() = default;
	virtual void					set_ref_handle(const CBaseHandle& handle) = 0;
	virtual const CBaseHandle& get_handle() const = 0;
};

class IClientThinkable {
public:
	virtual IClientUnknown* get_client_unknown() = 0;
	virtual void					client_think() = 0;
	virtual void* get_think_handle() = 0;
	virtual void					set_think_handle(void* think) = 0;
	virtual void					release() = 0;
};

class IClientNetworkable {
public:
	virtual IClientUnknown* get_client_unknown() = 0;
	virtual void				release() = 0;
	virtual ClientClass* get_client_class() = 0;
	virtual void				notify_should_transmit(int state) = 0;
	virtual void				on_pre_data_changed(int update_type) = 0;
	virtual void				on_data_changed(int update_type) = 0;
	virtual void				pre_data_update(int update_type) = 0;
	virtual void				post_data_update(int update_type) = 0;
	virtual bool				is_dormant() = 0;
	virtual int					get_index() const = 0;
	virtual void				receive_message(int class_id, void* msg) = 0;		//bf_read
	virtual void* get_data_table_base_ptr() = 0;
	virtual void				set_destroyed_on_recreate_entities() = 0;
};

struct ShadowType_t;
class IPVSNotify;
struct ClientShadowHandle_t;
struct ClientRenderHandle_t;

class IClientRenderable {
public:
	virtual IClientUnknown* get_i_client_unknown() = 0;
	virtual Vector const& get_render_origin() = 0;
	virtual QAngle const& get_render_angles() = 0;
	virtual bool					should_draw() = 0;
	virtual bool					is_transparent() = 0;
	virtual bool					uses_power_of_two_frame_buffer_texture() = 0;
	virtual bool					uses_full_frame_buffer_texture() = 0;
	virtual ClientShadowHandle_t	get_shadow_handle() = 0;
	virtual ClientRenderHandle_t& render_handle() = 0;
	virtual void* get_model() = 0;
	virtual void					draw_model(int flags) = 0;
	virtual int						get_body() = 0;
	virtual void					compute_fx_bled() = 0;
	virtual int						get_fx_blend() = 0;
	virtual void					GetColorModulation(float* color) = 0;
	virtual bool					lod_test() = 0;
	virtual bool					setup_bones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;
	virtual void					setup_weights(const matrix3x4_t* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights) = 0;
	virtual void					do_animation_events(void) = 0;
	virtual IPVSNotify* get_pvs_notify_interface() = 0;
	virtual void					get_render_bounds(Vector& mins, Vector& maxs) = 0;
	virtual void					get_render_bounds_worldspace(Vector& mins, Vector& maxs) = 0;
	virtual void					get_shadow_render_bounds(Vector& mins, Vector& maxs, ShadowType_t shadowType) = 0;
	virtual bool					should_receive_projected_textures(int flags) = 0;
	virtual bool					get_shadow_cast_distance(float* pDist, ShadowType_t shadowType) const = 0;
	virtual bool					get_shadow_cast_direction(Vector* pDirection, ShadowType_t shadowType) const = 0;
	virtual bool					is_shadow_dirty() = 0;
	virtual void					mark_shadow_dirty(bool bDirty) = 0;
	virtual IClientRenderable* get_shadow_parent() = 0;
	virtual IClientRenderable* first_shadow_child() = 0;
	virtual IClientRenderable* next_shadow_peer() = 0;
	virtual ShadowType_t			shadow_cast_type() = 0;
	virtual void					create_model_instance() = 0;
	virtual void*	get_model_instance() = 0;
	virtual const matrix3x4_t& renderable_to_world_transform() = 0;
	virtual int						lookup_attachment(const char* pAttachmentName) = 0;
	virtual	bool					get_attachment(int number, Vector& origin, QAngle& angles) = 0;
	virtual bool					get_attachment(int number, matrix3x4_t& matrix) = 0;
	virtual float* get_render_clip_plane(void) = 0;
	virtual int						get_skin() = 0;
	virtual bool					is_two_pass(void) = 0;
	virtual void					on_threaded_draw_setup() = 0;
	virtual bool					uses_flex_delayed_weights() = 0;
	virtual void					record_tool_message() = 0;
	virtual bool					ignores_z_buffer(void) const = 0;

	//static uintptr_t* get_vtable() {
	//	static const auto vtable = SIG("client.dll", "55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 89 7C 24 0C").self_offset(0x4E).cast<uintptr_t*>();

	//	return vtable;
	//}
};

class CBaseEntity;
class IClientEntity;
class IClientAlphaProperty;

class IClientUnknown : public IHandleEntity {
public:
	virtual void* get_collideable() = 0;	//i_collideable
	virtual IClientNetworkable* get_client_networkable() = 0;
	virtual IClientRenderable* get_client_renderable() = 0;
	virtual IClientEntity* get_client_entity() = 0;
	virtual CBaseEntity* get_base_entity() = 0;
	virtual IClientThinkable* get_client_thinkable() = 0;
	virtual IClientAlphaProperty* get_client_alpha_property() = 0;
};

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable {
public:
	virtual void release() = 0;
};