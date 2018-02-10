#include "Config.h"

#include "Settings.h"
#include <winerror.h>
#pragma warning( disable : 4091)
#include <ShlObj.h>
#include <string>
#include <sstream>
#include "ESP.h"
#include "Hooks.h"

const char* get_weapon_name(int iWeaponID)
{
	switch (iWeaponID)
	{
	default:
		return "none";
	case WEAPON_DEAGLE:
		return "deagle";
	case WEAPON_ELITE:
		return "duals";
	case WEAPON_FIVESEVEN:
		return "five7";
	case WEAPON_GLOCK:
		return "glock";
	case WEAPON_AK47:
		return "ak47";
	case WEAPON_AUG:
		return "aug";
	case WEAPON_AWP:
		return "awp";
	case WEAPON_FAMAS:
		return "famas";
	case WEAPON_G3SG1:
		return "g3sg1";
	case WEAPON_GALILAR:
		return "galil";
	case WEAPON_M249:
		return "m249";
	case WEAPON_M4A1:
		return "m4a4";
	case WEAPON_MAC10:
		return "mac10";
	case WEAPON_P90:
		return "p90";
	case WEAPON_UMP45:
		return "ump45";
	case WEAPON_XM1014:
		return "xm1014";
	case WEAPON_BIZON:
		return "bizon";
	case WEAPON_MAG7:
		return "mag7";
	case WEAPON_NEGEV:
		return "negev";
	case WEAPON_SAWEDOFF:
		return "sawedoff";
	case WEAPON_TEC9:
		return "tec9";
	case WEAPON_TASER:
		return "taser";
	case WEAPON_USP_SILENCER:
		return "usp-s";
	case WEAPON_MP7:
		return "mp7";
	case WEAPON_MP9:
		return "mp9";
	case WEAPON_NOVA:
		return "nova";
	case WEAPON_P250:
		return "p250";
	case WEAPON_SCAR20:
		return "scar20";
	case WEAPON_SG556:
		return "sg556";
	case WEAPON_SSG08:
		return "ssg08";
	case WEAPON_M4A1_SILENCER:
		return "m4a1-s";
	case WEAPON_HKP2000:
		return "p2000";
	case WEAPON_CZ75A:
		return "cz75";
	case WEAPON_REVOLVER:
		return "revolver";
	case WEAPON_BAYONET:
		return "bayonet";
	case WEAPON_KNIFE_BUTTERFLY:
		return "butterfly";
	case WEAPON_KNIFE_FALCHION:
		return "falshion";
	case WEAPON_KNIFE_FLIP:
		return "flip";
	case WEAPON_KNIFE_GUT:
		return "gut";
	case WEAPON_KNIFE_KARAMBIT:
		return "karambit";
	case WEAPON_KNIFE_M9_BAYONET:
		return "m9";
	case WEAPON_KNIFE_TACTICAL:
		return "huntsman";
	case WEAPON_KNIFE_SURVIVAL_BOWIE:
		return "bowie";
	case WEAPON_KNIFE_PUSH:
		return "daggers";
	}
}

void ConfigSystem::Setup()
{

	SetupValue(g_Settings.visuals.team_chams, 0, "Visuals-Team", "Chams");
	SetupValue(g_Settings.visuals.team_chams_ignorez, false, "Visuals-Team", "ChamsZ");
	SetupValue(g_Settings.visuals.team_esp, false, "Visuals-Team", "Box");
	SetupValue(g_Settings.visuals.team_espname, false, "Visuals-Team", "Name");
	SetupValue(g_Settings.visuals.team_espweapon, false, "Visuals-Team", "Weapon");
	SetupValue(g_Settings.visuals.team_glow, false, "Visuals-Team", "Glow");
	SetupValue(g_Settings.visuals.team_health, false, "Visuals-Team", "Health");
	SetupValue(g_Settings.visuals.team_money, false, "Visuals-Team", "Money");

	SetupValue(g_Settings.visuals.enemy_chams, 0, "Visuals-Enemy", "Chams");
	SetupValue(g_Settings.visuals.enemy_chams_ignorez, false, "Visuals-Enemy", "ChamsZ");
	SetupValue(g_Settings.visuals.enemy_esp, false, "Visuals-Enemy", "Box");
	SetupValue(g_Settings.visuals.enemy_espname, false, "Visuals-Enemy", "Name");
	SetupValue(g_Settings.visuals.enemy_espweapon, false, "Visuals-Enemy", "Weapon");
	SetupValue(g_Settings.visuals.enemy_glow, false, "Visuals-Enemy", "Glow");
	SetupValue(g_Settings.visuals.enemy_health, false, "Visuals-Enemy", "Health");
	SetupValue(g_Settings.visuals.enemy_money, false, "Visuals-Enemy", "Money");

	SetupValue(g_Settings.visuals.other_bombdamage, false, "Visuals-Other", "Bomb-Damage");
	SetupValue(g_Settings.visuals.other_bombtime, false, "Visuals-Other", "Bomb-Time");
	SetupValue(g_Settings.visuals.other_espbomb, false, "Visuals-Other", "Bomb-Esp");
	SetupValue(g_Settings.visuals.other_glowbomb, false, "Visuals-Other", "Bomb-Glow");

	SetupValue(g_Settings.visuals.team_chams_color[0], 0.f, "Colors", "Team-Cham-ColorR"); 
	SetupValue(g_Settings.visuals.team_chams_color[1], 1.f, "Colors", "Team-Cham-ColorG");
	SetupValue(g_Settings.visuals.team_chams_color[2], 0.95f, "Colors", "Team-Cham-ColorB");
	SetupValue(g_Settings.visuals.team_chamsz_color[0], 0.f, "Colors", "Team-ChamZ-ColorR"); 
	SetupValue(g_Settings.visuals.team_chamsz_color[1], 1.f, "Colors", "Team-ChamZ-ColorG");
	SetupValue(g_Settings.visuals.team_chamsz_color[2], 0.35f, "Colors", "Team-ChamZ-ColorB");
	SetupValue(g_Settings.visuals.team_money_color[0], 0.f, "Colors", "Team-Money-ColorR");
	SetupValue(g_Settings.visuals.team_money_color[1], 1.f, "Colors", "Team-Money-ColorG");
	SetupValue(g_Settings.visuals.team_money_color[2], 0.f, "Colors", "Team-Money-ColorB");
	SetupValue(g_Settings.visuals.team_espname_color[0], 0.f, "Colors", "Team-Name-ColorR"); 
	SetupValue(g_Settings.visuals.team_espname_color[1], 1.f, "Colors", "Team-Name-ColorG");
	SetupValue(g_Settings.visuals.team_espname_color[2], 0.35f, "Colors", "Team-Name-ColorB");
	SetupValue(g_Settings.visuals.team_espweapon_color[0], 0.f, "Colors", "Team-Weapon-ColorR");
	SetupValue(g_Settings.visuals.team_espweapon_color[1], 1.f, "Colors", "Team-Weapon-ColorG");
	SetupValue(g_Settings.visuals.team_espweapon_color[2], 0.35f, "Colors", "Team-Weapon-ColorB");
	SetupValue(g_Settings.visuals.team_glow_color[0], 0.f, "Colors", "Team-Glow-ColorR");
	SetupValue(g_Settings.visuals.team_glow_color[1], 1.f, "Colors", "Team-Glow-ColorG");
	SetupValue(g_Settings.visuals.team_glow_color[2], 0.35f, "Colors", "Team-Glow-ColorB");
	SetupValue(g_Settings.visuals.team_esp_color[0], 0.f, "Colors", "Team-ESP-ColorR");
	SetupValue(g_Settings.visuals.team_esp_color[1], 1.f, "Colors", "Team-ESP-ColorG");
	SetupValue(g_Settings.visuals.team_esp_color[2], 0.35f, "Colors", "Team-ESP-ColorB");

	SetupValue(g_Settings.visuals.enemy_chams_color[0], 1.f, "Colors", "Enemy-Cham-ColorR"); // { 1.f, 0.79f , 0.f };
	SetupValue(g_Settings.visuals.enemy_chams_color[1], 0.79f, "Colors", "Enemy-Cham-ColorG");
	SetupValue(g_Settings.visuals.enemy_chams_color[2], 0.f, "Colors", "Enemy-Cham-ColorB");
	SetupValue(g_Settings.visuals.enemy_chamsz_color[0], 1.f, "Colors", "Enemy-ChamZ-ColorR"); // { 1.f, 0.35f , 0.f };
	SetupValue(g_Settings.visuals.enemy_chamsz_color[1], 0.35f, "Colors", "Enemy-ChamZ-ColorG");
	SetupValue(g_Settings.visuals.enemy_chamsz_color[2], 0.f, "Colors", "Enemy-ChamZ-ColorB");
	SetupValue(g_Settings.visuals.enemy_espmoney_color[0], 0.f, "Colors", "Enemy-Money-ColorR");
	SetupValue(g_Settings.visuals.enemy_espmoney_color[1], 1.f, "Colors", "Enemy-Money-ColorG");
	SetupValue(g_Settings.visuals.enemy_espmoney_color[2], 0.f, "Colors", "Enemy-Money-ColorB");
	SetupValue(g_Settings.visuals.enemy_espname_color[0], 1.f, "Colors", "Enemy-Name-ColorR"); // { 1.f, 0.3f ,0.f };
	SetupValue(g_Settings.visuals.enemy_espname_color[1], 0.3f, "Colors", "Enemy-Name-ColorG");
	SetupValue(g_Settings.visuals.enemy_espname_color[2], 0.f, "Colors", "Enemy-Name-ColorB");
	SetupValue(g_Settings.visuals.enemy_espweapon_color[0], 1.f, "Colors", "Enemy-Weapon-ColorR");
	SetupValue(g_Settings.visuals.enemy_espweapon_color[1], 0.3f, "Colors", "Enemy-Weapon-ColorG");
	SetupValue(g_Settings.visuals.enemy_espweapon_color[2], 0.f, "Colors", "Enemy-Weapon-ColorB");
	SetupValue(g_Settings.visuals.enemy_glow_color[0], 1.f, "Colors", "Enemy-Glow-ColorR");
	SetupValue(g_Settings.visuals.enemy_glow_color[1], 0.3f, "Colors", "Enemy-Glow-ColorG");
	SetupValue(g_Settings.visuals.enemy_glow_color[2], 0.f, "Colors", "Enemy-Glow-ColorB");
	SetupValue(g_Settings.visuals.enemy_esp_color[0], 1.f, "Colors", "Enemy-ESP-ColorR");
	SetupValue(g_Settings.visuals.enemy_esp_color[1], 0.3f, "Colors", "Enemy-ESP-ColorG");
	SetupValue(g_Settings.visuals.enemy_esp_color[2], 0.f, "Colors", "Enemy-ESP-ColorB");
	SetupValue(g_Settings.visuals.other_glowbomb_color[0], 0.85f, "Colors", "Other-ESP-BombGlowR"); //{ 0.85f, 0.76f ,1.f };
	SetupValue(g_Settings.visuals.other_glowbomb_color[1], 0.76f, "Colors", "Other-ESP-BombGlowG");
	SetupValue(g_Settings.visuals.other_glowbomb_color[2], 1.f, "Colors", "Other-ESP-BombGlowB");
	SetupValue(g_Settings.visuals.other_espbomb_color[0], 1.f, "Colors", "Other-ESP-BombESPR"); 
	SetupValue(g_Settings.visuals.other_espbomb_color[1], 0.5f, "Colors", "Other-ESP-BombESPG");
	SetupValue(g_Settings.visuals.other_espbomb_color[2], 0.f, "Colors", "Other-ESP-BombESPB");

	SetupValue(g_Settings.misc.bhop, false, "Misc", "Bhop");
	SetupValue(g_Settings.misc.auto_accept, false, "Misc", "Auto-Accept");
	SetupValue(g_Settings.misc.anti_untrust, true, "Misc", "Anti-Untrust");

}


void ConfigSystem::SetupValue(int &value, int def, std::string category, std::string name)
{
	value = def;
	ints.push_back(new ConfigValue<int>(category, name, &value));
}

void ConfigSystem::SetupValue(float &value, float def, std::string category, std::string name)
{
	value = def;
	floats.push_back(new ConfigValue<float>(category, name, &value));
}

void ConfigSystem::SetupValue(bool &value, bool def, std::string category, std::string name)
{
	value = def;
	bools.push_back(new ConfigValue<bool>(category, name, &value));
}

void ConfigSystem::Save()
{
	static char path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
	{
		char szCmd[256];
		sprintf(szCmd, "\\Turbina Configs\\%s.ini", g_Settings.config.config_name);

		folder = std::string(path) + "\\Turbina Configs\\";
		file = std::string(path) + szCmd;
	}

	CreateDirectoryA(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileStringA(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileStringA(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileStringA(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void ConfigSystem::Load()
{
	static char path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
	{
		char szCmd[256];
		sprintf(szCmd, "\\Turbina Configs\\%s.ini", g_Settings.config.config_name);

		folder = std::string(path) + "\\Turbina Configs\\";
		file = std::string(path) + szCmd;
	}

	CreateDirectoryA(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileStringA(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileStringA(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileStringA(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}

ConfigSystem* Config = new ConfigSystem();