#include "includes.h"
#include "backend/config/config_new.h"
bool Hooks::OverrideConfig( MaterialSystem_Config_t* config, bool update ) {
	if( settings.fullbrigan ) // fullbright, do we need that?
		config->m_nFullbright = true;

	return g_hooks.m_material_system.GetOldMethod< OverrideConfig_t >( IMaterialSystem::OVERRIDECONFIG )( this, config, update );
}