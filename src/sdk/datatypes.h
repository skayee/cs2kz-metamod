#pragma once
#ifndef _WIN32
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses"
#endif
#ifndef _WIN32
#pragma clang diagnostic pop
#endif
#include "ehandle.h"
#include "sdk/entity/ccsplayercontroller.h"
#include "sdk/entity/cbasetrigger.h"

struct TransmitInfo
{
	CBitVec<16384> *m_pTransmitEdict;
};

enum ObserverMode_t : uint8_t
{
	OBS_MODE_NONE = 0x0,
	OBS_MODE_FIXED = 0x1,
	OBS_MODE_IN_EYE = 0x2,
	OBS_MODE_CHASE = 0x3,
	OBS_MODE_ROAMING = 0x4,
	OBS_MODE_DIRECTED = 0x5,
	NUM_OBSERVER_MODES = 0x6,
};

enum MsgDest : int32_t
{
	HUD_PRINTNOTIFY = 1,
	HUD_PRINTCONSOLE = 2,
	HUD_PRINTTALK = 3,
	HUD_PRINTCENTER = 4,
	HUD_PRINTTALK2 = 5, // Not sure what the difference between this and HUD_PRINTTALK is...
	HUD_PRINTALERT = 6
};

enum InputBitMask_t : uint64_t
{
	IN_NONE = 0x0,
	IN_ALL = 0xffffffffffffffff,
	IN_ATTACK = 0x1,
	IN_JUMP = 0x2,
	IN_DUCK = 0x4,
	IN_FORWARD = 0x8,
	IN_BACK = 0x10,
	IN_USE = 0x20,
	IN_TURNLEFT = 0x80,
	IN_TURNRIGHT = 0x100,
	IN_MOVELEFT = 0x200,
	IN_MOVERIGHT = 0x400,
	IN_ATTACK2 = 0x800,
	IN_RELOAD = 0x2000,
	IN_SPEED = 0x10000,
	IN_JOYAUTOSPRINT = 0x20000,
	IN_FIRST_MOD_SPECIFIC_BIT = 0x100000000,
	IN_USEORRELOAD = 0x100000000,
	IN_SCORE = 0x200000000,
	IN_ZOOM = 0x400000000,
	IN_LOOK_AT_WEAPON = 0x800000000,
};

// Sound stuff.

typedef uint32 SoundEventGuid_t;

struct SndOpEventGuid_t
{
	SoundEventGuid_t m_nGuid;
	uint64 m_hStackHash;
};

// used with EmitSound_t
enum gender_t : uint8
{
	GENDER_NONE = 0x0,
	GENDER_MALE = 0x1,
	GENDER_FEMALE = 0x2,
	GENDER_NAMVET = 0x3,
	GENDER_TEENGIRL = 0x4,
	GENDER_BIKER = 0x5,
	GENDER_MANAGER = 0x6,
	GENDER_GAMBLER = 0x7,
	GENDER_PRODUCER = 0x8,
	GENDER_COACH = 0x9,
	GENDER_MECHANIC = 0xA,
	GENDER_CEDA = 0xB,
	GENDER_CRAWLER = 0xC,
	GENDER_UNDISTRACTABLE = 0xD,
	GENDER_FALLEN = 0xE,
	GENDER_RIOT_CONTROL = 0xF,
	GENDER_CLOWN = 0x10,
	GENDER_JIMMY = 0x11,
	GENDER_HOSPITAL_PATIENT = 0x12,
	GENDER_BRIDE = 0x13,
	GENDER_LAST = 0x14,
};

struct EmitSound_t
{
	// clang-format off
	EmitSound_t() :
		m_nChannel( 0 ),
		m_pSoundName( 0 ),
		m_flVolume( VOL_NORM ),
		m_SoundLevel( SNDLVL_NONE ),
		m_nFlags( 0 ),
		m_nPitch( PITCH_NORM ),
		m_pOrigin( 0 ),
		m_flSoundTime( 0.0f ),
		m_pflSoundDuration( 0 ),
		m_bEmitCloseCaption( true ),
		m_bWarnOnMissingCloseCaption( false ),
		m_bWarnOnDirectWaveReference( false ),
		m_nSpeakerEntity( -1 ),
		m_UtlVecSoundOrigin(),
		m_nForceGuid( 0 ),
		m_SpeakerGender( GENDER_NONE )
	{
	}

	// clang-format on
	int m_nChannel;
	const char *m_pSoundName;
	float m_flVolume;
	soundlevel_t m_SoundLevel;
	int m_nFlags;
	int m_nPitch;
	const Vector *m_pOrigin;
	float m_flSoundTime;
	float *m_pflSoundDuration;
	bool m_bEmitCloseCaption;
	bool m_bWarnOnMissingCloseCaption;
	bool m_bWarnOnDirectWaveReference;
	CEntityIndex m_nSpeakerEntity;
	CUtlVector<Vector, CUtlMemory<Vector, int>> m_UtlVecSoundOrigin;
	SoundEventGuid_t m_nForceGuid;
	gender_t m_SpeakerGender;
};

// Tracing stuff.
struct RnCollisionAttr_t
{ // Unsure, doesn't seem right either for the first few members.
	uint64_t m_nInteractsAs;
	uint64_t m_nInteractsWith;
	uint64_t m_nInteractsExclude;
	uint32_t m_nEntityId;
	uint32_t m_nOwnerId;
	uint16_t m_nHierarchyId;
	uint8_t m_nCollisionGroup;
	uint8_t m_nCollisionFunctionMask;
};

enum RnQueryObjectSet : uint32
{
	RNQUERY_OBJECTS_STATIC = 0x1,
	RNQUERY_OBJECTS_DYNAMIC = 0x2,
	RNQUERY_OBJECTS_NON_COLLIDEABLE = 0x4,
	RNQUERY_OBJECTS_KEYFRAMED_ONLY = 0x108,
	RNQUERY_OBJECTS_DYNAMIC_ONLY = 0x110,
	RNQUERY_OBJECTS_ALL = 0x7
};

enum CollisionFunctionMask_t : uint32
{
	FCOLLISION_FUNC_ENABLE_SOLID_CONTACT = 0x1,
	FCOLLISION_FUNC_ENABLE_TRACE_QUERY = 0x2,
	FCOLLISION_FUNC_ENABLE_TOUCH_EVENT = 0x4,
	FCOLLISION_FUNC_ENABLE_SELF_COLLISIONS = 0x8,
	FCOLLISION_FUNC_IGNORE_FOR_HITBOX_TEST = 0x10,
	FCOLLISION_FUNC_ENABLE_TOUCH_PERSISTS = 0x20,
};

struct alignas(16) trace_t_s2
{
	void *m_pSurfaceProperties;
	CBaseEntity *m_pEnt;
	void *m_pHitbox;
	void *m_hBody;
	void *m_hShape;
	uint64_t contents;
	Vector traceunknown[2];
	uint8_t padding[2];
	RnCollisionAttr_t m_ShapeAttributes;
	Vector startpos;
	Vector endpos;
	Vector planeNormal;
	Vector traceunknown1;
	float traceunknown2;
	float fraction;
	uint8_t traceunknown3[4];
	uint16_t traceunknown4;
	uint8_t traceType;
	bool startsolid;
};

static_assert(offsetof(trace_t_s2, startpos) == 120);
static_assert(offsetof(trace_t_s2, endpos) == 132);
static_assert(offsetof(trace_t_s2, startsolid) == 183);
static_assert(offsetof(trace_t_s2, fraction) == 172);

struct touchlist_t
{
	Vector deltavelocity;
	trace_t_s2 trace;
};

struct RnQueryAttr_t
{
	uint64 m_nInteractsWith {};
	uint64 m_nInteractsExclude {};
	uint64 m_nInteractsAs {};

	uint32 m_nEntityIdToIgnore = -1;
	uint32 m_nEntityControllerIdToIgnore = -1;

	uint32 m_nOwnerEntityIdToIgnore = -1;
	uint32 m_nControllerOwnerEntityIdToIgnore = -1;

	uint16 m_nHierarchyId {};
	uint16 m_nControllerHierarchyId {};

	uint16 m_nObjectSetMask {};
	uint8_t m_nCollisionGroup {};

	union
	{
		uint8 m_Flags {};

		struct
		{
			uint8 m_bHitSolid: 1;
			uint8 m_bHitSolidRequiresGenerateContacts: 1;
			uint8 m_bHitTrigger: 1;
			uint8 m_bShouldIgnoreDisabledPairs: 1;

			uint8 m_bUnkFlag1: 1;
			uint8 m_bUnkFlag2: 1;
			uint8 m_bUnkFlag3: 1;
			uint8 m_bUnkFlag4: 1;
		};
	};

	bool m_bIterateEntities;
};

class CTraceFilterS2
{
public:
	RnQueryAttr_t attr;

	virtual ~CTraceFilterS2() {}

	virtual bool ShouldHitEntity(CBaseEntity *other)
	{
		return false;
	}
};

class CTraceFilterPlayerMovementCS : public CTraceFilterS2
{
};

// TODO: Remove this!
struct CCheckTransmitInfoS2
{
	CBitVec<16384> *m_pTransmitEdict;
	uint8 unk[1000];
};

struct SubtickMove
{
	float when;
	uint64 button;
	bool pressed;
};

// Size: 0xF8
class CMoveData
{
public:
	CMoveData() = default;

	CMoveData(const CMoveData &source)
		// clang-format off
		: moveDataFlags {source.moveDataFlags}, 
		m_nPlayerHandle {source.m_nPlayerHandle},
		m_vecAbsViewAngles {source.m_vecAbsViewAngles},
		m_vecViewAngles {source.m_vecViewAngles},
		m_vecLastMovementImpulses {source.m_vecLastMovementImpulses},
		m_flForwardMove {source.m_flForwardMove}, 
		m_flSideMove {source.m_flSideMove}, 
		m_flUpMove {source.m_flUpMove},
		m_flSubtickFraction {source.m_flSubtickFraction}, 
		m_vecVelocity {source.m_vecVelocity}, 
		m_vecAngles {source.m_vecAngles},
		m_bHasSubtickInputs {source.m_bHasSubtickInputs},
		m_collisionNormal {source.m_collisionNormal},
		m_groundNormal {source.m_groundNormal}, 
		m_vecAbsOrigin {source.m_vecAbsOrigin},
		m_nGameModeMovedPlayer {source.m_nGameModeMovedPlayer},
		m_outWishVel {source.m_outWishVel},
		m_vecOldAngles {source.m_vecOldAngles}, 
		m_flMaxSpeed {source.m_flMaxSpeed}, 
		m_flClientMaxSpeed {source.m_flClientMaxSpeed},
		m_flSubtickAccelSpeed {source.m_flSubtickAccelSpeed}, 
		m_bJumpedThisTick {source.m_bJumpedThisTick},
		m_bOnGround {source.m_bOnGround},
		m_bShouldApplyGravity {source.m_bShouldApplyGravity}, 
		m_bGameCodeMovedPlayer {source.m_bGameCodeMovedPlayer}
	// clang-format on
	{
		for (int i = 0; i < source.m_AttackSubtickMoves.Count(); i++)
		{
			this->m_AttackSubtickMoves.AddToTail(source.m_AttackSubtickMoves[i]);
		}
		for (int i = 0; i < source.m_SubtickMoves.Count(); i++)
		{
			this->m_SubtickMoves.AddToTail(source.m_SubtickMoves[i]);
		}
		for (int i = 0; i < source.m_TouchList.Count(); i++)
		{
			this->m_TouchList.AddToTail(source.m_TouchList[i]);
		}
	}

public:
	uint8_t moveDataFlags;
	CHandle<CCSPlayerPawn> m_nPlayerHandle;
	QAngle m_vecAbsViewAngles;
	QAngle m_vecViewAngles;
	Vector m_vecLastMovementImpulses;
	float m_flForwardMove;
	float m_flSideMove; // Warning! Flipped compared to CS:GO, moving right gives negative value
	float m_flUpMove;
	float m_flSubtickFraction;
	Vector m_vecVelocity;
	Vector m_vecAngles;
	CUtlVector<SubtickMove> m_SubtickMoves;
	CUtlVector<SubtickMove> m_AttackSubtickMoves;
	bool m_bHasSubtickInputs;
	CUtlVector<touchlist_t> m_TouchList;
	Vector m_collisionNormal;
	Vector m_groundNormal; // unsure
	Vector m_vecAbsOrigin;
	bool m_nGameModeMovedPlayer;
	Vector m_outWishVel;
	Vector m_vecOldAngles;
	float m_flMaxSpeed;
	float m_flClientMaxSpeed;
	float m_flSubtickAccelSpeed; // Related to ground acceleration subtick stuff with sv_stopspeed and friction
	bool m_bJumpedThisTick;      // something to do with basevelocity and the tick the player jumps
	bool m_bOnGround;
	bool m_bShouldApplyGravity;
	bool m_bGameCodeMovedPlayer; // true if usercmd cmd number == (m_nGameCodeHasMovedPlayerAfterCommand + 1)
};

static_assert(offsetof(CMoveData, m_vecViewAngles) == 0x14);
static_assert(offsetof(CMoveData, m_vecVelocity) == 0x3c);
static_assert(offsetof(CMoveData, m_vecAngles) == 0x48);
static_assert(offsetof(CMoveData, m_vecAbsOrigin) == 0xc0);
static_assert(offsetof(CMoveData, m_outWishVel) == 0xd0);
static_assert(offsetof(CMoveData, m_flMaxSpeed) == 0xe8);
static_assert(offsetof(CMoveData, m_flClientMaxSpeed) == 0xec);
static_assert(offsetof(CMoveData, m_flSubtickAccelSpeed) == 0xf0);
static_assert(offsetof(CMoveData, m_bJumpedThisTick) == 0xf4);
static_assert(offsetof(CMoveData, m_bOnGround) == 0xf5);
static_assert(sizeof(CMoveData) == 248, "Class didn't match expected size");

// Custom data types goes here.

enum TurnState
{
	TURN_LEFT = -1,
	TURN_NONE = 0,
	TURN_RIGHT = 1
};

class CTraceFilterHitAllTriggers : public CTraceFilterS2
{
public:
	CTraceFilterHitAllTriggers()
	{
		attr.m_nInteractsAs = 0;
		attr.m_nInteractsExclude = 0;
		attr.m_nInteractsWith = 4;
		attr.m_nEntityIdToIgnore = -1;
		attr.m_nEntityControllerIdToIgnore = -1;
		attr.m_nOwnerEntityIdToIgnore = -1;
		attr.m_nControllerOwnerEntityIdToIgnore = -1;
		attr.m_nObjectSetMask = RNQUERY_OBJECTS_ALL;
		attr.m_nControllerHierarchyId = 0;
		attr.m_nHierarchyId = 0;
		attr.m_bIterateEntities = true;
		attr.m_nCollisionGroup = COLLISION_GROUP_DEBRIS;
		attr.m_bHitTrigger = true;
	}

	CUtlVector<CEntityHandle> hitTriggerHandles;

	virtual ~CTraceFilterHitAllTriggers()
	{
		hitTriggerHandles.Purge();
	}

	virtual bool ShouldHitEntity(CBaseEntity *other)
	{
		hitTriggerHandles.AddToTail(other->GetRefEHandle());
		return false;
	}
};
