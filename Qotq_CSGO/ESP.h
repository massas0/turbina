#pragma once
#include "SDK.h"
class CESP {
public:
	void Start();
private:
	void DrawBomb(C_BaseEntity* pEntity, ClientClass* cClass);
	void DrawBombPlanted(C_BaseEntity* pEntity, ClientClass* cClass);
	void PlayerBox(C_BaseEntity* pEntity, RECT EspRect, ImColor BoxClr);
	void PlayerHealth(C_BaseEntity* pEntity, RECT EspRect);
	void PlayerWeapon(C_BaseEntity* pEntity, RECT EspRect, ImColor color);
	void PlayerMoney(C_BaseEntity* pEntity, RECT EspRect, ImColor color);
	void PlayerName(C_BaseEntity* pEntity, RECT EspRect, player_info_t info, ImColor color);
	void PlayerDistance(C_BaseEntity* pEntity, RECT EspRect,  C_BaseEntity* pLocal);
	RECT GetBox(C_BaseEntity* pEntity);
	bool WorldToScreen(const Vector& in, Vector& out);
}; extern CESP* g_pESP;

inline float CSGO_Armor(float flDamage, int ArmorValue)
{
	float flArmorRatio = 0.5f;
	float flArmorBonus = 0.5f;
	if (ArmorValue > 0) {
		float flNew = flDamage * flArmorRatio;
		float flArmor = (flDamage - flNew) * flArmorBonus;

		if (flArmor > static_cast<float>(ArmorValue)) {
			flArmor = static_cast<float>(ArmorValue) * (1.f / flArmorBonus);
			flNew = flDamage - flArmor;
		}

		flDamage = flNew;
	}
	return flDamage;
}