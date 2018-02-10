#pragma once
struct SSettings
{

	struct {

		struct {
			bool enable_aimbot;
			bool silent_aim;
			bool on_key;
			int  key;
			float  fov;
			float  rcs;
			int  hitbox;
			bool auto_shoot;
		}Rifles;

		struct
		{
			bool enable_aimbot;
			bool silent_aim;
			bool auto_pistol;
			bool on_key;
			int  key;
			float  fob;
			float  rcs;
			int  hitbox;
			bool auto_shoot;
		}Pistols;
		struct
		{
			bool enable_aimbot;
			bool silent_aim;
			bool on_key;
			int  key;
			float  fov;
			float  rcs;
			int  hitbox;
			bool auto_shoot;
		}Snipers;

	}legitbot;

	struct{
		
		bool team_glow;
		float team_glow_color[3] = { 0.f, 1.f ,0.35f };
		bool team_esp;
		float team_esp_color[3] = { 0.f, 1.f ,0.35f };
		bool team_espname;
		float team_espname_color[3] = { 0.f, 1.f ,0.35f };
		bool team_espweapon;
		float team_espweapon_color[3] = { 0.f, 1.f ,0.35f };
		bool team_health;
		bool team_money;
		float team_money_color[3] = { 0.f, 1.f ,0.f };
		int team_chams;
		float team_chams_color[3] = { 0.f, 1.f ,0.95f };
		bool team_chams_ignorez;
		float team_chamsz_color[3] = { 0.f, 1.f ,0.35f };

		bool enemy_glow;
		float enemy_glow_color[3] = { 1.f, 0.3f ,0.f };
		bool enemy_esp;
		float enemy_esp_color[3] = { 1.f, 0.3f ,0.f };
		bool enemy_espname;
		float enemy_espname_color[3] = { 1.f, 0.3f ,0.f };
		bool enemy_espweapon;
		float enemy_espweapon_color[3] = { 1.f, 0.3f ,0.f };
		bool enemy_health;
		bool enemy_money;
		float enemy_espmoney_color[3] = { 0.f, 1.f , 0.f };
		int enemy_chams;
		float enemy_chams_color[3] = { 1.f, 0.79f , 0.f };
		bool enemy_chams_ignorez;
		float enemy_chamsz_color[3] = { 1.f, 0.35f , 0.f };

		bool other_glowbomb;
		float other_glowbomb_color[3] = { 0.85f, 0.76f ,1.f };
		bool other_espbomb;
		float other_espbomb_color[3] = { 1.f, 0.5f ,0.f };
		bool other_bombtime;
		bool other_bombdamage;

	}visuals;

	struct {
		bool bhop;
		bool auto_accept;
		bool anti_untrust = true;
	}misc;

	struct {

		char config_name[52] = "default";
		int current_config;

	}config;

}; extern SSettings g_Settings;