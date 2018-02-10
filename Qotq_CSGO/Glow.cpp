#include "Glow.h"

void CGlow::Start() {
	auto GlowObjectManager = g_pGlowObjectManager;
	CGlowObjectManager::GlowObjectDefinition_t* glowEntity;
	auto local = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());

	ImColor Allie = ImColor(g_Settings.visuals.team_glow_color[2], g_Settings.visuals.team_glow_color[1], g_Settings.visuals.team_glow_color[0], 0.70f);
	ImColor Enemy = ImColor(g_Settings.visuals.enemy_glow_color[2], g_Settings.visuals.enemy_glow_color[1], g_Settings.visuals.enemy_glow_color[0], 0.70f);
	ImColor Bomb = ImColor(g_Settings.visuals.other_glowbomb_color[2], g_Settings.visuals.other_glowbomb_color[1], g_Settings.visuals.other_glowbomb_color[0], 0.95f);

	for (int i = 0; i < GlowObjectManager->size; i++)
	{
		glowEntity = &GlowObjectManager->m_GlowObjectDefinitions[i];
		auto Entity = glowEntity->getEntity();
		if (!Entity) continue;
		auto EntityClass = Entity->GetClientClass();
		/*
		if (EntityClass->m_ClassID == ClassId_CCSPlayer) {
			

			if (Entity->GetTeam() == local->GetTeam() && g_Settings.visuals.team_glow)
			{
				glowEntity->set((Color)Allie);
			}
			if (Entity->GetTeam() != local->GetTeam() && g_Settings.visuals.enemy_glow)
			{
				glowEntity->set((Color)Enemy);
			}


		}
		if (EntityClass->m_ClassID == ClassId_CC4 || EntityClass->m_ClassID == ClassId_CPlantedC4)
		{
			glowEntity->set((Color)Bomb);
		}*/

		switch (EntityClass->m_ClassID)
		{
			case ClassId_CCSPlayer: 
				if (Entity->GetTeam() == local->GetTeam() && g_Settings.visuals.team_glow)
				{
					glowEntity->set((Color)Allie);
				}
				if (Entity->GetTeam() != local->GetTeam() && g_Settings.visuals.enemy_glow)
				{
					glowEntity->set((Color)Enemy);
				}
				break;

			case ClassId_CC4:
				if (g_Settings.visuals.other_glowbomb)
					glowEntity->set((Color)Bomb);
				break;
			case ClassId_CPlantedC4:
				if (g_Settings.visuals.other_glowbomb)
					glowEntity->set((Color)Bomb);
				break;
		}

	}
}