#include "includes.h"
#include "backend/config/config_new.h"
void Hooks::PaintTraverse( VPANEL panel, bool repaint, bool force ) {
	static VPANEL tools{}, zoom{};

	// cache CHudZoom panel once.
	if( !zoom && FNV1a::get( g_csgo.m_panel->GetName( panel ) ) == HASH( "HudZoom" ) )
		zoom = panel;

	// cache tools panel once.
	if( !tools && panel == g_csgo.m_engine_vgui->GetPanel( PANEL_TOOLS ) )
		tools = panel;

	// render hack stuff.
	if( panel == tools )
		g_cl.OnPaint( );

	// don't call the original function if we want to remove the scope.
	if( panel == zoom && settings.noscope ) // not it should work
		return;
		
	g_hooks.m_panel.GetOldMethod< PaintTraverse_t >( IPanel::PAINTTRAVERSE )( this, panel, repaint, force );
}