#include "fakelag.hpp"
#include "../../backend/config/config_new.h"

namespace gideon {
    void c_fakelag::estimate_max_choke( c_usercmd* c ) {
        noclamp = false;

        if ( !( g_cl.m_local->m_fFlags( ) & FL_ONGROUND ) )
            estimate( 2 );
        else {
            if ( g_cl.m_local->m_vecVelocity( ).length( ) < 1.02f )
                estimate( 0 );
            else
                estimate( 1 );
        }

        if ( g_cl.m_weapon && g_cl.m_weapon->GetWpnData()->m_weapon_type != WEAPONTYPE_GRENADE ) {
            if ( settings.onshotdisable && c->m_buttons & IN_ATTACK )
                return force_choke( 1 );
        }
    }

    int c_fakelag::variance( int limit, int variance ) {
        auto min = ( float )limit - ( float )limit / 100.f * ( float )variance;
        return min + ( rand( ) % int( limit - min + 1 ) );
    }
}