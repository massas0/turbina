#include "CBaseEntity.h"
using namespace VT;
bool C_BaseEntity::IsPlayer()
{
	return VFunc<bool(__thiscall*)(C_BaseEntity*)>(this, 152)(this);
}

bool C_BaseEntity::IsWeapon()
{
	return VFunc<bool(__thiscall*)(C_BaseEntity*)>(this, 160)(this);
}
Vector C_BaseEntity::GetViewOffset()
{
	return *reinterpret_cast<Vector*>((uintptr_t)this + NetVars.m_vecViewOffset);
}

int C_BaseEntity::GetHealth()
{
	return *reinterpret_cast<int*>((uintptr_t)this + NetVars.m_iHealth);
}
int C_BaseEntity::GetTeam()
{
	return *reinterpret_cast<int*>((uintptr_t)this + NetVars.m_iTeamNum);
}
bool C_BaseEntity::GetDormant()
{
	return *reinterpret_cast<bool*>((uintptr_t)this + 0xE9);
}
ICollideable* C_BaseEntity::GetCollideable()
{
	typedef ICollideable*(__thiscall *OrigFn)(void*);
	return VFunc<OrigFn>(this, 3)(this);
}

const model_t* C_BaseEntity::GetModel()
{
	void *pRenderable = (void*)(this + 0x4);
	typedef const model_t*(__thiscall *OrigFn)(void*);
	return VFunc<OrigFn>(pRenderable, 8)(pRenderable);
}

bool C_BaseEntity::SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
{
	void *pRenderable = (void*)(this + 0x4);
	typedef bool(__thiscall *OrigFn)(void*, matrix3x4_t*, int, int, float);
	return VFunc<OrigFn>(pRenderable, 13)(pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
}

ClientClass* C_BaseEntity::GetClientClass()
{
	void *pNetworked = (void*)(this + 0x8);
	typedef ClientClass*(__thiscall *OrigFn)(void*);
	return VFunc<OrigFn>(pNetworked, 2)(pNetworked);
}
int C_BaseEntity::GetIndex()
{
	return *reinterpret_cast<int*>((uintptr_t)this + 0x64);
}
int C_BaseEntity::GetFlags()
{
	return *reinterpret_cast<int*>((uintptr_t)this + NetVars.m_fFlags);
}
Vector C_BaseEntity::GetOrigin()
{
	return *reinterpret_cast<Vector*>((uintptr_t)this + 0x134);
}
const matrix3x4_t& C_BaseEntity::GetCoordinateFrame()
{
	return *reinterpret_cast<matrix3x4_t*>((uintptr_t)this + NetVars.m_rgflCoordinateFrame);
}
Vector C_BaseEntity::GetEyePos()
{
	return (this->GetOrigin() + this->GetViewOffset());
}
Vector C_BaseEntity::GetHitboxPos(int hitbox_id)
{
	matrix3x4_t boneMatrix[MAXSTUDIOBONES];

	if (SetupBones(boneMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.0f)) {
		auto studio_model = g_pMdlInfo->GetStudiomodel(GetModel());
		if (studio_model) {
			auto hitbox = studio_model->pHitboxSet(0)->pHitbox(hitbox_id);
			if (hitbox) {
				auto
					min = Vector{},
					max = Vector{};

				Math::VectorTransform(hitbox->bbmin, boneMatrix[hitbox->bone], min);
				Math::VectorTransform(hitbox->bbmax, boneMatrix[hitbox->bone], max);

				return (min + max) / 2.0f;
			}
		}
	}
	return Vector{};
}
bool C_BaseEntity::GetHitboxPos(int hitbox, Vector &output)
{
	if (hitbox >= HITBOX_MAX)
		return false;

	const model_t *model = this->GetModel();
	if (!model)
		return false;

	studiohdr_t *studioHdr = g_pMdlInfo->GetStudiomodel(model);
	if (!studioHdr)
		return false;

	matrix3x4_t matrix[MAXSTUDIOBONES];
	if (!this->SetupBones(matrix, MAXSTUDIOBONES, 0x100, 0))
		return false;

	mstudiobbox_t *studioBox = studioHdr->pHitboxSet(0)->pHitbox(hitbox);
	if (!studioBox)
		return false;

	Vector min, max;

	Math::VectorTransform(studioBox->bbmin, matrix[studioBox->bone], min);
	Math::VectorTransform(studioBox->bbmax, matrix[studioBox->bone], max);

	output = (min + max) * 0.5f;

	return true;
}
Vector C_BaseEntity::GetBonePos(int bone)
{
	matrix3x4_t boneMatrix[MAXSTUDIOBONES];

	if (SetupBones(boneMatrix, MAXSTUDIOBONES, BONE_USED_BY_ANYTHING, 0.0f)) {
		return Vector(boneMatrix[bone][0][3], boneMatrix[bone][1][3], boneMatrix[bone][2][3]);
	}
	return Vector{};
}

bool C_BaseEntity::CanSeePlayer(C_BaseEntity* player, int hitbox)
{
	CGameTrace tr;
	Ray_t ray;
	CTraceFilter filter;
	filter.pSkip = this;

	auto endpos = player->GetHitboxPos(hitbox);

	ray.Init(GetEyePos(), endpos);
	g_pEngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr);

	return tr.hit_entity == player || tr.fraction > 0.97f;
}


bool C_BaseEntity::CanSeePlayer(C_BaseEntity* player, const Vector& pos)
{
	CGameTrace tr;
	Ray_t ray;
	CTraceFilter filter;
	filter.pSkip = this;

	auto start = GetEyePos();
	auto dir = (pos - start).Normalized();

	ray.Init(start, pos);
	g_pEngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr);

	return tr.hit_entity == player || tr.fraction > 0.97f;
}
bool C_BaseEntity::bSpotted()
{
	return *reinterpret_cast<bool*>((uintptr_t)this + 0x939);
}
int C_BaseEntity::GetArmor()
{
	return *reinterpret_cast<int*>((uintptr_t)this + NetVars.m_ArmorValue);
}
int C_BaseEntity::DrawModel(int flags, uint8_t alpha) {
	typedef bool(__thiscall *OrigFn)(void*, int, uint8_t);
	return VFunc<OrigFn>(GetClientRenderable(), 9)(GetClientRenderable(), flags, alpha);
}
void* C_BaseEntity::GetClientRenderable()
{
	return reinterpret_cast<void*>(this + 0x4);
}
int C_BaseEntity::GetTickBase()
{
	return *reinterpret_cast<int*>((uintptr_t)this + NetVars.m_nTickBase);
}
Vector C_BaseEntity::GetPunchAngles()
{
	return *reinterpret_cast<Vector*>((uintptr_t)this + NetVars.m_vecPunchAngles);
}
CBaseHandle C_BaseEntity::hActiveWeapon()
{
	return *reinterpret_cast<CBaseHandle*>((uintptr_t)this + NetVars.m_hActiveWeapon);
}
C_BaseWeapon* C_BaseEntity::GetActiveWeapon()
{
	return (C_BaseWeapon*)g_pEntityList->GetClientEntityFromHandle((CBaseHandle)hActiveWeapon());
}
MoveType_t C_BaseEntity::GetMoveType() {
	return *reinterpret_cast<MoveType_t*>((uintptr_t)this + 0x258);
}
int C_BaseEntity::GetMoney()
{
	return *reinterpret_cast<int*>((uintptr_t)this + NetVars.m_iAccountID);
}