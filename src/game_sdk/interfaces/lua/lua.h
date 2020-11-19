#pragma once
#include <cstdint>
#include <string>

namespace LUA		//thx Nixware-GMOD https://github.com/Nixer1337/Nixware-GMOD
{
	enum class Type
	{
		client,
		server,
		menu
	};

	enum class Special
	{
		glob,
		env,
		reg
	};

	enum class LuaType
	{
		TYPE_INVALID = -1,
		TYPE_NIL,
		TYPE_BOOL,
		TYPE_LIGHTUSERDATA,
		TYPE_NUMBER,
		TYPE_STRING,
		TYPE_TABLE,
		TYPE_FUNCTION,
		TYPE_USERDATA,
		TYPE_THREAD,

		TYPE_ENTITY,
		TYPE_VECTOR,
		TYPE_ANGLE,
		TYPE_PHYSOBJ,
		TYPE_SAVE,
		TYPE_RESTORE,
		TYPE_DAMAGEINFO,
		TYPE_EFFECTDATA,
		TYPE_MOVEDATA,
		TYPE_RECIPIENTFILTER,
		TYPE_USERCMD,
		TYPE_SCRIPTEDVEHICLE,

		TYPE_MATERIAL,
		TYPE_PANEL,
		TYPE_PARTICLE,
		TYPE_PARTICLEEMITTER,
		TYPE_TEXTURE,
		TYPE_USERMSG,

		TYPE_CONVAR,
		TYPE_IMESH,
		TYPE_MATRIX,
		TYPE_SOUND,
		TYPE_PIXELVISHANDLE,
		TYPE_DLIGHT,
		TYPE_VIDEO,
		TYPE_FILE,

		TYPE_PLAYER = TYPE_ENTITY,
	};



	//typedef int(*tluaL_loadstring)(lua_State* state, const char* s);
	//typedef int(*tluaL_loadfile)(lua_State* state, const char* s);


	using number_t = double;



	class Interface
	{
	public:
		virtual int			Top(void) = 0;
		virtual void		Push(int iStackPos) = 0;
		virtual void		Pop(int iAmt = 1) = 0;
		virtual void		GetTable(int iStackPos) = 0;
		virtual void		GetField(int iStackPos, const char* strName) = 0;
		virtual void		SetField(int iStackPos, const char* strName) = 0;
		virtual void		CreateTable() = 0;
		virtual void		SetTable(int i) = 0;
		virtual void		SetMetaTable(int i) = 0;
		virtual bool		GetMetaTable(int i) = 0;
		virtual void		Call(int iArgs, int iResults) = 0;
		virtual int			PCall(int iArgs, int iResults, int iErrorFunc) = 0;
		virtual int			Equal(int iA, int iB) = 0;
		virtual int			RawEqual(int iA, int iB) = 0;
		virtual void		Insert(int iStackPos) = 0;
		virtual void		Remove(int iStackPos) = 0;
		virtual int			Next(int iStackPos) = 0;
		virtual void* NewUserdata(unsigned int iSize) = 0;
		virtual void		ThrowError(const char* strError) = 0;
		virtual void		CheckType(int iStackPos, int iType) = 0;
		virtual void		ArgError(int iArgNum, const char* strMessage) = 0;
		virtual void		RawGet(int iStackPos) = 0;
		virtual void		RawSet(int iStackPos) = 0;
		virtual const char* GetString(int iStackPos = -1, unsigned int* iOutLen = NULL) = 0;
		virtual double			GetNumber(int iStackPos = -1) = 0;
		virtual bool			GetBool(int iStackPos = -1) = 0;
		virtual void* GetCFunction(int iStackPos = -1) = 0;
		virtual void* GetUserdata(int iStackPos = -1) = 0;
		virtual void		PushNil() = 0;
		virtual void		PushString(const char* val, unsigned int iLen = 0) = 0;
		virtual void		PushNumber(double val) = 0;
		virtual void		PushBool(bool val) = 0;
		virtual void		PushCFunction(void* val) = 0;
		virtual void		PushCClosure() = 0;
		virtual void		PushUserdata(void*) = 0;
		virtual int			ReferenceCreate() = 0;
		virtual void		ReferenceFree(int i) = 0;
		virtual void		ReferencePush(int i) = 0;
		virtual void		PushSpecial(int iType) = 0;
		virtual bool			IsType(int iStackPos, int iType) = 0;
		virtual int				GetType(int iStackPos) = 0;
		virtual const char* GetTypeName(int iType) = 0;
		virtual void			CreateMetaTableType(const char* strName, int iType) = 0;
		virtual const char* CheckString(int iStackPos = -1) = 0;
		virtual double	CheckNumber(int iStackPos = -1) = 0;
		virtual void ObjLen(int) = 0;
		virtual void GetAngle(int) = 0;
		virtual void* GetVector(int) = 0;
		virtual void PushAngle(void*) = 0;
		virtual void PushVector(void*) = 0;
		virtual void SetState() = 0;
		virtual void CreateMetaTable(char const*) = 0;
		virtual void PushMetaTable(int) = 0;
		virtual void PushUserType(void*, int) = 0;
		virtual void SetUserType(int, void*) = 0;
		virtual void Init(void*, bool) = 0;
		virtual void Shutdown(void) = 0;
		virtual void Cycle(void) = 0;
		virtual void Global(void) = 0;
		virtual void* GetObject(int) = 0;
		virtual void PushLuaObject(void*) = 0;
		virtual void PushLuaFunction() = 0;
		virtual void LuaError(char const*, int) = 0;
		virtual void TypeError(char const*, int) = 0;
		virtual void CallInternal(int, int) = 0;
		virtual void CallInternalNoReturns(int) = 0;
		virtual bool CallInternalGetBool(int) = 0;
		virtual void CallInternalGetString(int) = 0;
		virtual void CallInternalGet(int, void*) = 0;
		virtual void NewGlobalTable(char const*) = 0;
		virtual void NewTemporaryObject(void) = 0;
		virtual void isUserData(int) = 0;
		virtual void GetMetaTableObject(char const*, int) = 0;
		virtual void GetMetaTableObject(int) = 0;
		virtual void GetReturn(int) = 0;
		virtual void IsServer(void) = 0;
		virtual void IsClient(void) = 0;
		virtual void IsDedicatedServer(void) = 0;
		virtual void DestroyObject(void*) = 0;
		virtual void CreateObject(void) = 0;
		virtual void SetMember(void*, void*, void*) = 0;
		virtual void GetNewTable(void) = 0;
		virtual void SetMember(void*, float) = 0;
		virtual void SetMember(void*, float, void*) = 0;
		virtual void SetMember(void*, char const*) = 0;
		virtual void SetMember(void*, char const*, void*) = 0;
		virtual void SetIsServer(bool) = 0;
		virtual void PushLong(long) = 0;
		virtual void GetFlags(int) = 0;
		virtual void FindOnObjectsMetaTable(int, int) = 0;
		virtual void FindObjectOnTable(int, int) = 0;
		virtual void SetMemberFast(void*, int, int) = 0;
		virtual void RunString(char const* filename, char const* path, char const* stringtoun, bool run = true, bool showerrors = true) = 0;
	};

	class Shared
	{
	public:
		inline Interface* get_interface(Type state)
		{
			using orig_fn = Interface * (__thiscall*)(Shared*, Type);
			return (*(orig_fn**)this)[6](this, state);
		}

		inline int load_file(std::string s1, std::string s2, std::string s3, bool b1)
		{
			using fn = int(__thiscall*)(Shared*, std::string, std::string, std::string, bool);
			return (*(fn**)this)[7](this, s1, s2, s3, b1);
		}
	};
}