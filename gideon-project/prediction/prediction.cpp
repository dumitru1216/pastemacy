#include "prediction.hpp"

namespace gideon {
	void c_prediction::save( ) {
		/* im just to lazy to calc server time */
		servertime = g_cl.m_local->calc_srv_time( ); /* shit pasted */

		/* main */
		frametime = g_csgo.m_globals->m_frametime;
		tickcount = g_csgo.m_globals->m_tick_count;

		/* second */
		g_csgo.m_globals->m_frametime = g_csgo.m_globals->m_interval;
		g_csgo.m_globals->m_tick_count = game::TIME_TO_TICKS( servertime );

		/* start */
		g_csgo.m_game_movement->start_track_prediction_errors( g_cl.m_local );
		g_csgo.m_move_helper->set_host( g_cl.m_local );
	}
}