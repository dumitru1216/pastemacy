#pragma once
#include "../g_inc.hpp"

namespace gideon {
    class c_fakelag {
    public:
        void estimate_max_choke( c_usercmd* c );
        void choke( c_usercmd* c );

        void force_choke( int v, bool force = false );

        int max_choke = 1;

    private:
        void estimate( int style );
        int variance( int limit, int variance );

        bool noclamp = false;
        float speed = 0.f;
        bool fluctate = false;
        int fl_tick = 0;
        int last_change = 0;
    };
}