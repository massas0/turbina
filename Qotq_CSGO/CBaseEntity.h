#pragma once
#include "SDK.h"

class C_BaseEntity {
public:
	bool IsPlayer();
	bool IsWeapon();
	ICollideable* GetCollideable();
	const model_t* GetModel();
	bool SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
	ClientClass* GetClientClass();
	int GetIndex();
	int GetFlags();
	Vector GetViewOffset();
	Vector GetEyePos();
	int GetHealth();
	int GetTeam();
	bool GetDormant();
	Vector GetOrigin();
	Vector GetPunchAngles();
	CBaseHandle hActiveWeapon();
	C_BaseWeapon* GetActiveWeapon();
	const matrix3x4_t& GetCoordinateFrame();
	Vector GetHitboxPos(int hitbox_id);
	bool GetHitboxPos(int hitbox, Vector &output);
	Vector GetBonePos(int bone);
	bool CanSeePlayer(C_BaseEntity* player, int hitbox);
	bool CanSeePlayer(C_BaseEntity* player, const Vector& pos);
	bool bSpotted();
	int GetArmor();
	int DrawModel(int flags, uint8_t alpha);
	void* GetClientRenderable();
	int GetTickBase();
	int GetMoney();
	MoveType_t GetMoveType();
};
