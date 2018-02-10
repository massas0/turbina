#include "Chamss.h"
#include <corecrt_malloc.h>

void InitKeyValues(KeyValues* keyValues, const char* name)
{
	static DWORD sig1;
	if (!sig1)
	{
		sig1 = g_pUtils->FindPatternIDA("client.dll", "68 ? ? ? ? 8B C8 E8 ? ? ? ? 89 45 FC EB 07 C7 45 ? ? ? ? ? 8B 03 56");
		sig1 += 7;
		sig1 = sig1 + *reinterpret_cast<PDWORD_PTR>(sig1 + 1) + 5;
	}

	static auto function = (void(__thiscall*)(KeyValues*, const char*))sig1;
	function(keyValues, name);

}

void LoadFromBuffer(KeyValues* keyValues, char const* resourceName, const char* pBuffer)
{
	static DWORD offset;
	if (!offset) offset = g_pUtils->FindPatternIDA("client.dll", "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04");
	static auto function = (void(__thiscall*)(KeyValues*, char const*, const char*, void*, const char*, void*))offset;
	function(keyValues, resourceName, pBuffer, 0, 0, 0);
}

IMaterial* CreateMaterial(bool XQZ, bool Lit, bool Wireframe)
{
	static int created = 0;
	static const char tmp[] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$flat\" \"1\"\
		\n\t\"$nocull\"  \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\"  \"0\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"%i\"\
        \n}\n"
	};
	char* baseType = (Lit == true ? "VertexLitGeneric" : "UnlitGeneric");
	char material[512];
	char name[512];
	sprintf_s(material, sizeof(material), tmp, baseType, (XQZ) ? 1 : 0, (Wireframe) ? 1 : 0);
	sprintf_s(name, sizeof(name), "#Aimpulse_Chams_%i.vmt", created);
	++created;
	KeyValues* keyValues = static_cast< KeyValues* >(malloc(sizeof(KeyValues)));
	InitKeyValues(keyValues, baseType);
	LoadFromBuffer(keyValues, name, material);
	IMaterial* createdMaterial = g_pMatSystem->CreateMaterial(name, keyValues);
	createdMaterial->IncrementReferenceCount();
	return createdMaterial;
}
void CChamss::Start() {

	IMaterial *flat = CreateMaterial(false, false, false);
	IMaterial *flatZ = CreateMaterial(true, false, false);

	IMaterial *Lit = CreateMaterial(false, true, false);
	IMaterial *LitZ = CreateMaterial(true, true, false);

	IMaterial *Wire = CreateMaterial(false, false, true);
	IMaterial *WireZ = CreateMaterial(true, false, true);


	for (int i = 0; i <= g_pEngine->GetMaxClients(); i++) {
		auto pLocal = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());
		C_BaseEntity* pEntity = g_pEntityList->GetClientEntity(i);
		if (!pEntity) continue;
		if (pEntity == pLocal) continue;
		if (pEntity->GetDormant()) continue;
		if (pEntity->GetHealth() < 1) continue;

		if (g_Settings.visuals.team_chams || g_Settings.visuals.enemy_chams)
		{

			if (pEntity->GetTeam() == pLocal->GetTeam() && g_Settings.visuals.team_chams)
			{

				if (g_Settings.visuals.team_chams_ignorez)
				{
					switch (g_Settings.visuals.team_chams)
					{
					case 1:
						LitZ->ColorModulate(g_Settings.visuals.team_chamsz_color[0], g_Settings.visuals.team_chamsz_color[1], g_Settings.visuals.team_chamsz_color[2]);
						g_pMdlRender->ForcedMaterialOverride(LitZ);
						break;
					case 2:
						flatZ->ColorModulate(g_Settings.visuals.team_chamsz_color[0], g_Settings.visuals.team_chamsz_color[1], g_Settings.visuals.team_chamsz_color[2]);
						g_pMdlRender->ForcedMaterialOverride(flatZ);
						break;
					case 3:
						WireZ->ColorModulate(g_Settings.visuals.team_chamsz_color[0], g_Settings.visuals.team_chamsz_color[1], g_Settings.visuals.team_chamsz_color[2]);
						g_pMdlRender->ForcedMaterialOverride(WireZ);
						break;

					}
					pEntity->DrawModel(0x1, 255);
				}

				switch (g_Settings.visuals.team_chams)
				{
				case 1:
					Lit->ColorModulate(g_Settings.visuals.team_chams_color[0], g_Settings.visuals.team_chams_color[1], g_Settings.visuals.team_chams_color[2]);
					g_pMdlRender->ForcedMaterialOverride(Lit);
					break;
				case 2:
					flat->ColorModulate(g_Settings.visuals.team_chams_color[0], g_Settings.visuals.team_chams_color[1], g_Settings.visuals.team_chams_color[2]);
					g_pMdlRender->ForcedMaterialOverride(flat);
					break;
				case 3:
					Wire->ColorModulate(g_Settings.visuals.team_chams_color[0], g_Settings.visuals.team_chams_color[1], g_Settings.visuals.team_chams_color[2]);
					g_pMdlRender->ForcedMaterialOverride(Wire);
					break;
				}
				pEntity->DrawModel(0x1, 255);
			}

			if (pEntity->GetTeam() != pLocal->GetTeam() && g_Settings.visuals.enemy_chams)
			{

				if (g_Settings.visuals.enemy_chams_ignorez)
				{
					switch (g_Settings.visuals.team_chams)
					{
					case 1:
						LitZ->ColorModulate(g_Settings.visuals.enemy_chamsz_color[0], g_Settings.visuals.enemy_chamsz_color[1], g_Settings.visuals.enemy_chamsz_color[2]);
						g_pMdlRender->ForcedMaterialOverride(LitZ);
						break;
					case 2:
						flatZ->ColorModulate(g_Settings.visuals.enemy_chamsz_color[0], g_Settings.visuals.enemy_chamsz_color[1], g_Settings.visuals.enemy_chamsz_color[2]);
						g_pMdlRender->ForcedMaterialOverride(flatZ);
						break;
					case 3:
						WireZ->ColorModulate(g_Settings.visuals.enemy_chamsz_color[0], g_Settings.visuals.enemy_chamsz_color[1], g_Settings.visuals.enemy_chamsz_color[2]);
						g_pMdlRender->ForcedMaterialOverride(WireZ);
						break;
					}
					pEntity->DrawModel(0x1, 255);
				}

				switch (g_Settings.visuals.team_chams)
				{
				case 1:
					Lit->ColorModulate(g_Settings.visuals.enemy_chamsz_color[0], g_Settings.visuals.enemy_chamsz_color[1], g_Settings.visuals.enemy_chamsz_color[2]);
					g_pMdlRender->ForcedMaterialOverride(Lit);
					break;
				case 2:
					flat->ColorModulate(g_Settings.visuals.enemy_chamsz_color[0], g_Settings.visuals.enemy_chamsz_color[1], g_Settings.visuals.enemy_chamsz_color[2]);
					g_pMdlRender->ForcedMaterialOverride(flat);
					break;
				case 3:
					Wire->ColorModulate(g_Settings.visuals.enemy_chamsz_color[0], g_Settings.visuals.enemy_chamsz_color[1], g_Settings.visuals.enemy_chamsz_color[2]);
					g_pMdlRender->ForcedMaterialOverride(Wire);
					break;
				}

				pEntity->DrawModel(0x1, 255);
			}
			g_pMdlRender->ForcedMaterialOverride(nullptr);
		}
	}
}