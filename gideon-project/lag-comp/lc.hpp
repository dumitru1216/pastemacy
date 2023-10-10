#pragma once
#include "../g_inc.hpp"

namespace gideon {
    class c_lag_record {
    public:
        int tick;
      //  float absyaw;
        vec3_t abspos;
        vec3_t origin;
        vec3_t velocity;
        c_angle eyes;
        C_AnimationLayer layers[ 13 ];
        float poseparams[ 24 ];
        matrix3x4_t bones[ 128 ];
        int health;
        int entnum;
        int tickbase;
        bool allow_resolve;
        float simtime;
        float delta;
        bool allow_attack;
        int last_sent_tick;
        int lc_tick;
        vec3_t mins;
        vec3_t maxs;
        int flags;
        bool is_backtrack = false;

        bool operator==( c_lag_record o ) { return tick == o.tick; }
    };

    class c_lc {
    public:
        void populate( Player* p );
        void clear( );
        void clear( int i );

        std::vector<c_lag_record>& get( Player* p );

        float get_lerptime( );

    private:
        std::unordered_map<int, std::vector<c_lag_record>> players;

        bool is_valid( c_lag_record& lc );
    };

}