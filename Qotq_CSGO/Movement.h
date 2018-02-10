#pragma once
#include "SDK.h"
class CMovement {
public:
	void Bhop(C_BaseEntity* pLocal, CUserCmd* cmd);
}; extern CMovement* g_pMovement;