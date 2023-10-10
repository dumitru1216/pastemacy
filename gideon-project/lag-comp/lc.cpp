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

	void c_lc::clear( ) {
		players.clear( );
	}

	std::vector<c_lag_record>& c_lc::get( Player* p ) {
		return players[ p->index( ) ];
	}

	void c_lc::clear( int i ) {
		players[ i ].clear( );
	}

	bool c_lc::is_valid( c_lag_record& lc ) {
		auto chan = g_csgo.m_cl->m_net_channel;
		if (!chan)
			return false;

		static auto sv_maxunlag = g_csgo.m_cvar->FindVar( HASH( "sv_maxunlag" ) );
		if ( !sv_maxunlag )
			return false;

		auto dead_time = game::TICKS_TO_TIME( g_csgo.m_cl->m_server_count ) + chan->GetLatency( 0 ) - sv_maxunlag->GetFloat( );
		if ( dead_time >= lc.simtime )
			return true;

		auto correct = std::clamp( get_lerptime( ) + chan->GetLatency( 0 ), 0.f, sv_maxunlag->GetFloat( ) );
		return fabsf( correct - ( g_cl.m_local->m_nTickBase( ) - lc.simtime ) ) <= sv_maxunlag->GetFloat( );
	}

	float c_lc::get_lerptime( ) {
		static auto cl_interp = g_csgo.m_cvar->FindVar( HASH( "cl_interp" ) );
		static auto cl_interp_ratio = g_csgo.m_cvar->FindVar( HASH( "cl_interp_ratio" ) );
		static auto cl_updaterate = g_csgo.m_cvar->FindVar( HASH( "cl_updaterate" ) );

		return std::fmax( cl_interp->GetFloat( ), cl_interp_ratio->GetFloat( ) / cl_updaterate->GetFloat( ) );
	}

}