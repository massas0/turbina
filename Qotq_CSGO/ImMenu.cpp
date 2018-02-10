#include "ImMenu.h"
#include <ShlObj.h>
#include "Config.h"

std::vector<std::string> configs;

void GetConfigMassive()
{
	//get all files on folder

	configs.clear();

	static char path[MAX_PATH];
	std::string szPath1;

	if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
		return;

	szPath1 = std::string(path) + "\\Turbina Configs\\*";


	WIN32_FIND_DATA FindFileData;
	HANDLE hf;

	hf = FindFirstFile(szPath1.c_str(), &FindFileData);
	if (hf != INVALID_HANDLE_VALUE) {
		do {
			std::string filename = FindFileData.cFileName;

			if (filename == ".")
				continue;

			if (filename == "..")
				continue;

			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				if (filename.find(".ini") != std::string::npos)
				{
					configs.push_back(std::string(filename));
				}
			}
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
}

namespace ImMenu
{
	ImFont* Im_Font;
	void GuiInit(HWND window, IDirect3DDevice9 *pDevice)
	{
		ImGui_ImplDX9_Init(window, pDevice);
		auto& style = ImGui::GetStyle();

		style.ChildWindowRounding = 0.f;
		style.GrabRounding = 0.f;
		style.WindowRounding = 0.f;
		style.ScrollbarRounding = 0.f;
		style.FrameRounding = 0.5f;
		style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
		style.ItemSpacing = ImVec2(0,4);

		style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(35 / 255.f, 102 / 255.f, 147 / 255.f, 0.4f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(35 / 255.f, 102 / 255.f, 147 / 255.f, 0.6f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		style.Colors[ImGuiCol_Border] = ImVec4(232 / 255.f, 203 / 255.f, 16 / 255.f, 1.00f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(232 / 255.f, 203 / 255.f, 16 / 255.f, .80f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(232 / 255.f, 203 / 255.f, 16 / 255.f, .80f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(232 / 255.f, 203 / 255.f, 16 / 255.f, .80f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(46 / 255.f, 101 / 255.f, 242 / 255.f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(232 / 255.f, 203 / 255.f, 16 / 255.f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(232 / 255.f, 203 / 255.f, 16 / 255.f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(232 / 255.f, 203 / 255.f, 16 / 255.f, 1.00f);
		style.Colors[ImGuiCol_ComboBg] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(232 / 255.f, 203 / 255.f, 16 / 255.f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(232 / 255.f, 203 / 255.f, 16 / 255.f, 0.80f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(232 / 255.f, 203 / 255.f, 16 / 255.f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(232 / 255.f, 203 / 255.f, 16 / 255.f, .80f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(232 / 255.f, 203 / 255.f, 16 / 255.f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(232 / 255.f, 203 / 255.f, 16 / 255.f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		style.Colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
		style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_CloseButton] = ImVec4(232 / 255.f, 203 / 255.f, 16 / 255.f, 0.80f);
		style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(232 / 255.f, 203 / 255.f, 16 / 255.f, 1.00f);
		style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(232 / 255.f, 203 / 255.f, 16 / 255.f, 1.00f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.32f, 0.52f, 0.65f, 1.00f);
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);

		Im_Font = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 13);
		D3Init = true;
	}
	void Open() {

		static bool bDown = false;
		static bool bClicked = false;
		static bool bPrevMenuState = menuOpen;

		if (pressedKey[VK_INSERT])
		{
			bClicked = false;
			bDown = true;
		}
		else if (!pressedKey[VK_INSERT] && bDown)
		{
			bClicked = true;
			bDown = false;
		}
		else
		{
			bClicked = false;
			bDown = false;
		}

		if (bClicked)
		{
			menuOpen = !menuOpen;
		}

		if (bPrevMenuState != menuOpen)
		{
			std::string msg = "cl_mouseenable " + std::to_string(!menuOpen);
			g_pEngine->ExecuteClientCmd(msg.c_str());
		}

		bPrevMenuState = menuOpen;
	}
	void Draw() {
		ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
		if (ImGui::Begin("turbina cheat", &menuOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders))
		{
			static int tab; // rage, legit, visuals, misc, skins
			ImGui::BeginChild(1, ImVec2(100, -1));
			if (ImGui::Button("Rage Aimbot", ImVec2(100, 35))) tab = 4; 
			if (ImGui::Button("Legit Aimbot", ImVec2(100, 35))) tab = 3; 
			if (ImGui::Button("Visuals", ImVec2(100, 35))) tab = 2; 
			if (ImGui::Button("Skin Changer", ImVec2(100, 35))) tab = 1; 
			if (ImGui::Button("Miscellanous", ImVec2(100, 35))) tab = 0;
			ImGui::EndChild();
			
			ImGui::SameLine();
			ImGui::BeginChild(2, ImVec2(400, -1));
			ImGui::PushItemWidth(200);


			if (tab == 4) // rage
			{
				
			}

			if (tab == 3) // legit
			{
				static int stab;
				if (ImGui::Button("Rifles", ImVec2(400 / 3, 25))) stab = 0; ImGui::SameLine();
				if (ImGui::Button("Pistols", ImVec2(400 / 3, 25))) stab = 1; ImGui::SameLine();
				if (ImGui::Button("Snipers", ImVec2(400 / 3, 25))) stab = 2;

				if (stab == 0) // rifles
				{
					ImGui::Text("Rifles");
					ImGui::Separator();
				}
				else if (stab == 1) // pistols
				{
					ImGui::Text("Pistols");
					ImGui::Separator();
				}
				else if (stab == 2) // Snipers
				{
					ImGui::Text("Snipers");
					ImGui::Separator();
				}
			}

			if (tab == 2) // visuals
			{
				static int stab;
				if (ImGui::Button("Allied", ImVec2(400 / 3, 25))) stab = 0; ImGui::SameLine();
				if (ImGui::Button("Enemy", ImVec2(400 / 3, 25))) stab = 1; ImGui::SameLine();
				if (ImGui::Button("Other Visuals", ImVec2(400 / 3, 25))) stab = 2;

				if (stab == 0) // Allied team
				{
					ImGui::Text("Allied");
					ImGui::Separator();
					ImGui::Checkbox("ESP Box", &g_Settings.visuals.team_esp); ImGui::SameLine();
					ImGui::ColorEdit3("##BOXALLY", g_Settings.visuals.team_esp_color);
					ImGui::Checkbox("ESP Name", &g_Settings.visuals.team_espname); ImGui::SameLine();
					ImGui::ColorEdit3("##NAMEALLY", g_Settings.visuals.team_espname_color);
					ImGui::Checkbox("ESP Health", &g_Settings.visuals.team_health);
					ImGui::Checkbox("ESP Weapon", &g_Settings.visuals.team_espweapon); ImGui::SameLine();
					ImGui::ColorEdit3("##WEAPONALLY", g_Settings.visuals.team_espweapon_color);
					ImGui::Checkbox("ESP Money", &g_Settings.visuals.team_money); ImGui::SameLine();
					ImGui::ColorEdit3("##MONEYALLY", g_Settings.visuals.team_money_color);
					ImGui::Combo("Colored Models", &g_Settings.visuals.team_chams, "Off\0\rTextured\0\rSolid\0\rWireframe\0\0", -1);
					ImGui::ColorEdit3("##CHAMALLY", g_Settings.visuals.team_chams_color);
					ImGui::Checkbox("Colored Models Ignore-Z", &g_Settings.visuals.team_chams_ignorez); ImGui::SameLine();
					ImGui::ColorEdit3("##CHAMZALLY", g_Settings.visuals.team_chamsz_color);
					ImGui::Checkbox("Outline Glow", &g_Settings.visuals.team_glow); ImGui::SameLine();
					ImGui::ColorEdit3("##GLOWALLY", g_Settings.visuals.team_glow_color);
				}
				else if (stab == 1) // enemy team
				{
					ImGui::Text("Enemy");
					ImGui::Separator();
					ImGui::Checkbox("ESP Box", &g_Settings.visuals.enemy_esp); ImGui::SameLine();
					ImGui::ColorEdit3("##BOXENEMY", g_Settings.visuals.enemy_esp_color);
					ImGui::Checkbox("ESP Name", &g_Settings.visuals.enemy_espname); ImGui::SameLine();
					ImGui::ColorEdit3("##NAMEENEMY", g_Settings.visuals.enemy_espname_color);
					ImGui::Checkbox("ESP Health", &g_Settings.visuals.enemy_health);
					ImGui::Checkbox("ESP Weapon", &g_Settings.visuals.enemy_espweapon); ImGui::SameLine();
					ImGui::ColorEdit3("##WEAPONENEMY", g_Settings.visuals.enemy_espweapon_color);
					ImGui::Checkbox("ESP Money", &g_Settings.visuals.enemy_money); ImGui::SameLine();
					ImGui::ColorEdit3("##MONEYENEMY", g_Settings.visuals.enemy_espmoney_color);
					ImGui::Combo("Colored Models", &g_Settings.visuals.enemy_chams, "Off\0\rTextured\0\rSolid\0\rWireframe\0\0", -1); ImGui::SameLine();
					ImGui::ColorEdit3("##CHAMENEMY", g_Settings.visuals.enemy_chams_color);
					ImGui::Checkbox("Colored Models Ignore-Z", &g_Settings.visuals.enemy_chams_ignorez); ImGui::SameLine();
					ImGui::ColorEdit3("##CHAMZENEMY", g_Settings.visuals.enemy_chamsz_color);
					ImGui::Checkbox("Outline Glow", &g_Settings.visuals.enemy_glow); ImGui::SameLine();
					ImGui::ColorEdit3("##GLOWENEMY", g_Settings.visuals.enemy_glow_color);
				}
				else if (stab == 2)
				{
					static bool bomb;

					ImGui::Text("Other Visuals");
					ImGui::Separator();

					if (ImGui::Button("Bomb Options")) bomb = !bomb; 
					ImGui::SameLine();
					if (bomb)
					{
						ImGui::Text("[+]");
						ImGui::Checkbox("C4 Outline Glow", &g_Settings.visuals.other_glowbomb); ImGui::SameLine();
						ImGui::ColorEdit3("##GLOWBOMB", g_Settings.visuals.other_glowbomb_color);
						ImGui::Checkbox("C4 ESP", &g_Settings.visuals.other_espbomb); ImGui::SameLine();
						ImGui::ColorEdit3("##ESPBOMB", g_Settings.visuals.other_espbomb_color);
						ImGui::Checkbox("C4 Time", &g_Settings.visuals.other_bombtime);
						ImGui::Checkbox("C4 Damage", &g_Settings.visuals.other_bombdamage);
					}
					else
					{
						ImGui::Text("[-]");
					}
				}
				
			}

			if (tab == 1) // skins
			{

			}

			if (tab == 0) // misc
			{
				ImGui::Columns(2);
				ImGui::Checkbox("Bhop", &g_Settings.misc.bhop);
				ImGui::NextColumn();
				ImGui::Checkbox("Safe Mode", &g_Settings.misc.anti_untrust);
				ImGui::Checkbox("Auto-Accept", &g_Settings.misc.auto_accept);
				ImGui::Text("");
				ImGui::Text("");
				GetConfigMassive();
				static int selectedcfg = 0;
				static std::string cfgname = "default";
				if (ImGui::Combo("Config File", &selectedcfg, [](void* data, int idx, const char** out_text)
				{
					*out_text = configs[idx].c_str();
					return true;
				}, nullptr, configs.size(), 10))
				{
					cfgname = configs[selectedcfg];
					cfgname.erase(cfgname.length() - 4, 4);
					strcpy(g_Settings.config.config_name, cfgname.c_str());
				}

				if (ImGui::Button("Save", ImVec2(47, 20))) Config->Save();
				ImGui::SameLine();
				if (ImGui::Button("Load", ImVec2(47, 20))) Config->Load();

				if (ImGui::Button("Reset Settings", ImVec2(101, 20.f))) {
					Config->Setup();
				}

				static bool toggle;
				if (ImGui::Button("Create New Config", ImVec2(100, 20))) toggle = !toggle;
				if (toggle)
				{
					ImGui::Text("  "); ImGui::SameLine();
					ImGui::InputText("Config Name", g_Settings.config.config_name, 52);
					ImGui::Text("  "); ImGui::SameLine();
					if (ImGui::Button("Create and Save")) {
						Config->Save();
						toggle = !toggle;
					}
				}

				
			}
			ImGui::PopItemWidth();
			ImGui::EndChild();

		}ImGui::End();
	}
}
