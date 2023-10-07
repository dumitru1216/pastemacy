#include "includes.h"
#include "backend/config/config_new.h"
void Hooks::OnRenderStart( ) {
	// call og.
	g_hooks.m_view_render.GetOldMethod< OnRenderStart_t >( CViewRender::ONRENDERSTART )( this );

	if( settings.fov_visuals ) {
		if ( g_cl.m_local && g_cl.m_local->m_bIsScoped( ) ) {
			if ( settings.fov_while_scoped ) {
				if ( g_cl.m_local->GetActiveWeapon( )->m_zoomLevel( ) != 2 ) {
					g_csgo.m_view_render->m_view.m_fov = settings.fov_amount;
				}
				else {
					g_csgo.m_view_render->m_view.m_fov += 45.f;
				}
			}
		}

		else g_csgo.m_view_render->m_view.m_fov = settings.fov_amount;
	}

	if ( settings.vfov )
		g_csgo.m_view_render->m_view.m_viewmodel_fov = settings.v_fov_am;
}

void Hooks::RenderView( const CViewSetup &view, const CViewSetup &hud_view, int clear_flags, int what_to_draw ) {
	// ...

	g_hooks.m_view_render.GetOldMethod< RenderView_t >( CViewRender::RENDERVIEW )( this, view, hud_view, clear_flags, what_to_draw );
}

void Hooks::Render2DEffectsPostHUD( const CViewSetup &setup ) {
	if( !settings.noflashs )
		g_hooks.m_view_render.GetOldMethod< Render2DEffectsPostHUD_t >( CViewRender::RENDER2DEFFECTSPOSTHUD )( this, setup );
}

void Hooks::RenderSmokeOverlay( bool unk ) {
	// do not render smoke overlay.
	if( !settings.nosmoke )
		g_hooks.m_view_render.GetOldMethod< RenderSmokeOverlay_t >( CViewRender::RENDERSMOKEOVERLAY )( this, unk );
}
