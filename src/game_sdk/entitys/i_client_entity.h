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
	virtual IClientUnknown* GetIClientUnknown() = 0;
	virtual Vector const& GetRenderOrigin() = 0;
	virtual QAngle const& GetRenderAngles() = 0;
	virtual bool					ShouldDraw() = 0;
	virtual bool					IsTransparent() = 0;
	virtual bool					UsesPowerOfTwoFrameBufferTexture() = 0;
	virtual bool					UsesFullFrameBufferTexture() = 0;
	virtual ClientShadowHandle_t	GetShadowHandle() = 0;
	virtual ClientRenderHandle_t& RenderHandle() = 0;
	virtual void* GetModel() = 0;
	virtual void					draw_model(int flags) = 0;
	virtual int						GetBody() = 0;
	virtual void					ComputeFxBled() = 0;
	virtual int						GetFxBlend() = 0;
	virtual void					GetColorModulation(float* color) = 0;
	virtual bool					LODTest() = 0;
	virtual bool					SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;
	virtual void					SetupWeights(const matrix3x4_t* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights) = 0;
	virtual void					DoAnimationEvents(void) = 0;
	virtual IPVSNotify* GetPVSNotifyInterface() = 0;
	virtual void					GetRenderBounds(Vector& mins, Vector& maxs) = 0;
	virtual void					GetRenderBoundsWorldspace(Vector& mins, Vector& maxs) = 0;
	virtual void					GetShadowRenderBounds(Vector& mins, Vector& maxs, ShadowType_t shadowType) = 0;
	virtual bool					ShouldReceiveProjectedTextures(int flags) = 0;
	virtual bool					GetShadowCastDistance(float* pDist, ShadowType_t shadowType) const = 0;
	virtual bool					GetShadowCastDirection(Vector* pDirection, ShadowType_t shadowType) const = 0;
	virtual bool					IsShadowDirty() = 0;
	virtual void					MarkShadowDirty(bool bDirty) = 0;
	virtual IClientRenderable* GetShadowParent() = 0;
	virtual IClientRenderable* FirstShadowChild() = 0;
	virtual IClientRenderable* NextShadowPeer() = 0;
	virtual ShadowType_t			ShadowCastType() = 0;
	virtual void					CreateModelInstance() = 0;
	virtual void*	GetModelInstance() = 0;
	virtual const matrix3x4_t& RenderableToWorldTransform() = 0;
	virtual int						LookupAttachment(const char* pAttachmentName) = 0;
	virtual	bool					GetAttachment(int number, Vector& origin, QAngle& angles) = 0;
	virtual bool					GetAttachment(int number, matrix3x4_t& matrix) = 0;
	virtual float* GetRenderClipPlane(void) = 0;
	virtual int						GetSkin() = 0;
	virtual bool					IsTwoPass(void) = 0;
	virtual void					OnThreadedDrawSetup() = 0;
	virtual bool					UsesFlexDelayedWeights() = 0;
	virtual void					RecordToolMessage() = 0;
	virtual bool					IgnoresZBuffer(void) const = 0;

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