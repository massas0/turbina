#include "ESP.h"
void CESP::Start() {
	for (int i = 0; i <= g_pEntityList->GetHighestEntityIndex(); i++) {
		auto pLocal = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());
		auto pEntity = g_pEntityList->GetClientEntity(i);
		if (!pEntity) continue;

		auto EntityClass = pEntity->GetClientClass();

		if (pEntity == pLocal) continue;
		if (pEntity->GetDormant()) continue;

		if (g_Settings.visuals.other_espbomb)
		{
			if (EntityClass->m_ClassID == ClassId_CPlantedC4)
				DrawBombPlanted(pEntity, EntityClass);
			if (EntityClass->m_ClassID == ClassId_CC4)
				DrawBomb(pEntity, EntityClass);
		}

		if (pEntity->GetHealth() < 1) continue;
		RECT EspRect;
		player_info_t info;
		EspRect = GetBox(pEntity);
		g_pEngine->GetPlayerInfo(pEntity->GetIndex(), &info);

		ImColor EnemyBoxC(g_Settings.visuals.enemy_esp_color[2], g_Settings.visuals.enemy_esp_color[1], g_Settings.visuals.enemy_esp_color[0]);
		ImColor AllieBoxC(g_Settings.visuals.team_esp_color[2], g_Settings.visuals.team_esp_color[1], g_Settings.visuals.team_esp_color[0]);

		ImColor EnemyNameC(g_Settings.visuals.enemy_espname_color[2], g_Settings.visuals.enemy_espname_color[1], g_Settings.visuals.enemy_espname_color[0]);
		ImColor AllieNameC(g_Settings.visuals.team_espname_color[2], g_Settings.visuals.team_espname_color[1], g_Settings.visuals.team_espname_color[0]);

		ImColor EnemyWepC(g_Settings.visuals.enemy_espweapon_color[2], g_Settings.visuals.enemy_espweapon_color[1], g_Settings.visuals.enemy_espweapon_color[0]);
		ImColor AllieWepC(g_Settings.visuals.team_espweapon_color[2], g_Settings.visuals.team_espweapon_color[1], g_Settings.visuals.team_espweapon_color[0]);

		ImColor EnemyMonC(g_Settings.visuals.enemy_espmoney_color[2], g_Settings.visuals.enemy_espmoney_color[1], g_Settings.visuals.enemy_espmoney_color[0]);
		ImColor AllieMonC(g_Settings.visuals.team_money_color[2], g_Settings.visuals.team_money_color[1], g_Settings.visuals.team_money_color[0]);

		if (g_Settings.visuals.enemy_esp && pEntity->GetTeam() != pLocal->GetTeam())
			PlayerBox(pEntity, EspRect, EnemyBoxC);
		if (g_Settings.visuals.enemy_espname && pEntity->GetTeam() != pLocal->GetTeam())
			PlayerName(pEntity, EspRect, info, EnemyNameC);
		if (g_Settings.visuals.enemy_espweapon && pEntity->GetTeam() != pLocal->GetTeam())
			PlayerWeapon(pEntity, EspRect, EnemyWepC);
		if (g_Settings.visuals.enemy_health && pEntity->GetTeam() != pLocal->GetTeam())
			PlayerHealth(pEntity, EspRect);
		if (g_Settings.visuals.enemy_money && pEntity->GetTeam() != pLocal->GetTeam())
			PlayerMoney(pEntity, EspRect, EnemyMonC);

		if (g_Settings.visuals.team_esp && pEntity->GetTeam() == pLocal->GetTeam())
			PlayerBox(pEntity, EspRect, AllieBoxC);
		if (g_Settings.visuals.team_espname && pEntity->GetTeam() == pLocal->GetTeam())
			PlayerName(pEntity, EspRect, info, AllieNameC);
		if (g_Settings.visuals.team_espweapon && pEntity->GetTeam() == pLocal->GetTeam())
			PlayerWeapon(pEntity, EspRect, AllieWepC);
		if (g_Settings.visuals.team_health && pEntity->GetTeam() == pLocal->GetTeam())
			PlayerHealth(pEntity, EspRect);
		if (g_Settings.visuals.team_money && pEntity->GetTeam() == pLocal->GetTeam())
			PlayerMoney(pEntity, EspRect, AllieMonC);
	}
}

void CESP::DrawBomb(C_BaseEntity* pEntity, ClientClass* cClass)
{
	ImColor BombC(g_Settings.visuals.other_espbomb_color[2], g_Settings.visuals.other_espbomb_color[1], g_Settings.visuals.other_espbomb_color[0]);

	Vector vOrig; Vector vScreen;
	vOrig = pEntity->GetOrigin();

	if (WorldToScreen(vOrig, vScreen))
	{
		Draw->String(F_ESP, true, vScreen.x, vScreen.y, (Color)BombC, "Dropped C4");
	}
}

void CESP::DrawBombPlanted(C_BaseEntity* pEntity, ClientClass* cClass)
{
	ImColor BombC(g_Settings.visuals.other_espbomb_color[2], g_Settings.visuals.other_espbomb_color[1], g_Settings.visuals.other_espbomb_color[0]);

	auto local = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());

	C_BaseWeapon *BombWeapon = (C_BaseWeapon *)pEntity;
	Vector vOrig; Vector vScreen;
	vOrig = pEntity->GetOrigin();
	bool adopted = true;
	CCSBomb* BombC4 = (CCSBomb*)pEntity;
	int BlowTime = BombC4->GetC4BlowTime();
	float time = BlowTime - (g_pGlobalVars->interval_per_tick * local->GetTickBase());

	if (adopted)
	{
		int screenx, screeny;
		g_pEngine->GetScreenSize(screenx, screeny);

		if (WorldToScreen(vOrig, vScreen))
		{
			if (g_Settings.visuals.other_bombtime)
			{
				if (time > 0.01f && !BombC4->IsBombDefused())
				{
					char buffer[32];
					sprintf_s(buffer, "Bomb: %.1f", time);
					Draw->String(F_ESP, false, vScreen.x, vScreen.y, (Color)BombC, buffer);
					Draw->String(F_ESP, false, screeny * 0.8, screenx / 2, (Color)BombC, buffer);
					if (g_Settings.visuals.other_bombdamage)
					{
						float flDistance = local->GetEyePos().DistTo(pEntity->GetEyePos());
						float a = 450.7f;
						float b = 75.68f;
						float c = 789.2f;
						float d = ((flDistance - b) / c);
						float flDamage = a * exp(-d * d);

						float damage = float((std::max)((int)ceilf(CSGO_Armor(flDamage, local->GetArmor())), 0));


						char BombAlive[32];
						sprintf_s(BombAlive, sizeof(BombAlive) - 1, "Damage: %.0f", damage);
						if (time > -2.f)
						{
							if (damage >= local->GetHealth())
							{
								Draw->String(F_ESP, false, screeny / 2, screenx * 0.8 + 30, Color::Red, BombAlive);
							}
							else if (local->GetHealth() > damage)
							{
								Draw->String(F_ESP, false, screeny / 2, screenx * 0.8 + 30, Color::Green, BombAlive);
							}
						}
					}
				}
				if (BombC4->GetBombDefuser() > 0)
				{
					char defuse[32];

					float countdown = BombC4->GetC4DefuseCountDown() - (local->GetTickBase() * g_pGlobalVars->interval_per_tick);
					sprintf_s(defuse, "Defusing: %.1f", countdown);
					if (time > countdown)
						Draw->String(F_ESP, true, screeny / 2, screenx * 0.8 + 15, Color::Green, defuse);
					else
						Draw->String(F_ESP, true, screeny / 2, screenx * 0.8 + 15, Color::Red, "Defusing: No Time");
				}
			}
			else
			{
				Draw->String(F_ESP, true, vScreen.x, vScreen.y, (Color)BombC, "Bomb");
				if (BombC4->GetBombDefuser() > 0)
				{
					Draw->String(F_ESP, true, screeny * 0.82, screenx / 2, Color::White, "Bomb is being defused");
				}
			}
		}
	}
}

void CESP::PlayerBox(C_BaseEntity* pEntity, RECT EspRect, ImColor BoxClr){	
	Draw->OutlinedRect(EspRect.left, EspRect.top, EspRect.right - EspRect.left, EspRect.bottom - EspRect.top, (Color)BoxClr);
	Draw->OutlinedRect(EspRect.left - 1, EspRect.top - 1, EspRect.right - EspRect.left + 2, EspRect.bottom - EspRect.top + 2, Color(0, 0, 0, 255));
	Draw->OutlinedRect(EspRect.left + 1, EspRect.top + 1, EspRect.right - EspRect.left - 2, EspRect.bottom - EspRect.top - 2, Color(0, 0, 0, 255));
}
void CESP::PlayerHealth(C_BaseEntity* pEntity, RECT EspRect) {
	auto hp = pEntity->GetHealth();
	auto green = int(hp * 2.55f);
	auto red = 255 - green;
	auto height = ((EspRect.bottom - EspRect.top) * hp) / 100;
	Draw->StringRight(true, F_ESP, EspRect.left - 7, EspRect.top - 2, Color(red, green, 0, 255), "%d", pEntity->GetHealth());
	Draw->FilledRect(EspRect.left - 5, EspRect.top - 1, 3, EspRect.bottom - EspRect.top + 2, Color(0, 0, 0, 255));
	Draw->FilledRect(EspRect.left - 4, EspRect.bottom - height, 1, height, Color(red, green, 0, 255));
}
void CESP::PlayerWeapon(C_BaseEntity* pEntity, RECT EspRect, ImColor color) {
	auto weapon = pEntity->GetActiveWeapon();
	auto weapondata = weapon->GetCSWeaponData();
	Draw->String(F_ESP, true, (EspRect.left + EspRect.right) / 2, EspRect.bottom + 1, (Color)color, "%s[%d/%d]", weapon->GetWeaponName().c_str(), weapon->Clip1(), weapondata->iMaxClip1);

}
void CESP::PlayerMoney(C_BaseEntity* pEntity, RECT EspRect, ImColor color) {
	auto money = pEntity->GetMoney();
	Draw->String(F_ESP, false, EspRect.right + 3, EspRect.top + 10, (Color)color, "%d$", money);
}
void CESP::PlayerName(C_BaseEntity* pEntity, RECT EspRect,player_info_t info, ImColor color) {
	std::string name = info.szName;
	Draw->String(F_ESP, true, (EspRect.left + EspRect.right) / 2, EspRect.top - 12, (Color)color, name.c_str());

}
void CESP::PlayerDistance(C_BaseEntity* pEntity, RECT EspRect, C_BaseEntity* pLocal) {
	auto a = pLocal->GetOrigin();
	auto b = pEntity->GetOrigin();
	int distance = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2)) * 0.0254f;
	Draw->String(F_ESP, false, EspRect.right + 3, EspRect.top, Color(255, 255, 255, 255), "%dM", distance);
}
bool CESP::WorldToScreen(const Vector& in, Vector& out) {
	static ptrdiff_t ptrViewMatrix;
	if (!ptrViewMatrix)
	{
		ptrViewMatrix = static_cast<ptrdiff_t>(g_pUtils->FindPatternIDA("client.dll", "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9"));
		ptrViewMatrix += 0x3;
		ptrViewMatrix = *reinterpret_cast<uintptr_t*>(ptrViewMatrix);
		ptrViewMatrix += 176;
	}
	const matrix3x4_t& worldToScreen = *(matrix3x4_t*)ptrViewMatrix;

	int ScrW, ScrH;

	g_pEngine->GetScreenSize(ScrW, ScrH);

	float w = worldToScreen[3][0] * in[0] + worldToScreen[3][1] * in[1] + worldToScreen[3][2] * in[2] + worldToScreen[3][3];
	out.z = 0;
	if (w > 0.01)
	{
		float inverseWidth = 1 / w;
		out.x = (ScrW / 2) + (0.5 * ((worldToScreen[0][0] * in[0] + worldToScreen[0][1] * in[1] + worldToScreen[0][2] * in[2] + worldToScreen[0][3]) * inverseWidth) * ScrW + 0.5);
		out.y = (ScrH / 2) - (0.5 * ((worldToScreen[1][0] * in[0] + worldToScreen[1][1] * in[1] + worldToScreen[1][2] * in[2] + worldToScreen[1][3]) * inverseWidth) * ScrH + 0.5);
		return true;
	}
	return false;
}
RECT CESP::GetBox(C_BaseEntity* pEntity) {
	RECT rect{};
	auto collideable = pEntity->GetCollideable();

	if (!collideable)
		return rect;

	auto min = collideable->OBBMins();
	auto max = collideable->OBBMaxs();

	auto trans = pEntity->GetCoordinateFrame();

	Vector points[] = {
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	Vector pointsTransformed[8];
	for (int i = 0; i < 8; i++) {
		Math::VectorTransform(points[i], trans, pointsTransformed[i]);
	}

	Vector screen_points[8] = {};

	for (int i = 0; i < 8; i++) {
		if (!WorldToScreen(pointsTransformed[i], screen_points[i]))
			return rect;
	}

	auto left = screen_points[0].x;
	auto top = screen_points[0].y;
	auto right = screen_points[0].x;
	auto bottom = screen_points[0].y;

	for (int i = 1; i < 8; i++) {
		if (left > screen_points[i].x)
			left = screen_points[i].x;
		if (top < screen_points[i].y)
			top = screen_points[i].y;
		if (right < screen_points[i].x)
			right = screen_points[i].x;
		if (bottom > screen_points[i].y)
			bottom = screen_points[i].y;
	}
	return RECT{ (long)left, (long)bottom, (long)right, (long)top };

}