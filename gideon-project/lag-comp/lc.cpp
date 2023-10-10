#include "lc.hpp"

namespace gideon {
	void c_lc::populate( Player* p ) {
		auto& v = players[ p->index( ) ];

		auto rm = std::vector<c_lag_record>( );
		for ( auto& r : v ) {
			if ( !is_valid( r ) )
				rm.push_back( r );
		}

		for ( auto r : rm )
			v.erase( std::find( v.begin( ), v.end( ), r ) );

		c_lag_record lr;
		if ( !v.empty( ) )
			lr.last_sent_tick = v.back( ).last_sent_tick;

		auto as = p->m_PlayerAnimState( );

		p->SetAbsOrigin( p->m_vecOrigin( ) );
		p->update_anim_state( ( CCSGOPlayerAnimState* )as, { 
			p->m_angEyeAngles( ).x, p->m_angEyeAngles( ).y 
		} ); // should be fine

		/* store this shit */
		as->m_eye_pitch = p->m_angEyeAngles( ).x;
		as->m_eye_yaw = p->m_angEyeAngles( ).y;

		*( ptr* )( ( ptr )p + 0xA30 ) = g_csgo.m_globals->m_frame;
		*( ptr* )( ( ptr )p + 0xA28 ) = 0;

		/* setup */
		p->m_fEffects( ) |= EF_NOINTERP;
		p->m_vecAbsVelocity( ) = p->m_vecVelocity( );
		p->InvalidateBoneCache( );
		p->SetupBones( lr.bones, 128, 0x7FF00, lr.tickbase * g_csgo.m_globals->m_interval );
		p->m_fEffects( ) &= ~EF_NOINTERP;

		lr.abspos = p->GetAbsOrigin( );
		lr.origin = p->m_vecOrigin( );
		lr.eyes = {
			p->m_angEyeAngles( ).x, p->m_angEyeAngles( ).y
		};
		lr.health = p->m_iHealth( );
		lr.entnum = p->index( );
		lr.tickbase = p->m_nTickBase( );
		// lr.absyaw = as->abs;
		lr.flags = p->m_fFlags( );
		lr.simtime = p->m_flSimulationTime( );
		lr.tick = game::TIME_TO_TICKS( lr.simtime );
		lr.allow_attack = ( !v.empty( ) ? ( v.back( ).last_sent_tick - g_csgo.m_globals->m_tick_count <= 6 ) : true );
		lr.lc_tick = !v.empty( ) ? ( v.back( ).simtime != p->m_flSimulationTime( ) ? lr.tick : v.back( ).lc_tick ) : g_csgo.m_globals->m_tick_count;
		lr.mins = !v.empty( ) ? ( v.back( ).simtime != p->m_flSimulationTime( ) ? p->get_collider_offset( )->mins : v.back( ).mins ) : p->get_collider_offset( )->mins;
		lr.maxs = !v.empty( ) ? ( v.back( ).simtime != p->m_flSimulationTime( ) ? p->get_collider_offset( )->maxs : v.back( ).maxs ) : p->get_collider_offset( )->maxs;

		if ( v.size( ) > 1 )
			lr.delta = v.back( ).delta;

		memcpy( lr.layers, p->m_AnimOverlay( ), sizeof( C_AnimationLayer ) * 13 );
		memcpy( lr.poseparams, p->m_flPoseParameter( ), sizeof( float ) * 24 );

		v.push_back( lr );
	}
}