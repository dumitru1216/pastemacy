#pragma once
#include "../../includes.h"

class CSettings
{
public:
	// returns true/false whether the function succeeds, usually returns false if file doesn't exist
	bool Save( std::string file_name );
	bool Load( std::string file_name );

	void CreateConfig( ); // creates a blank config

	std::vector<std::string> GetConfigs( );

	// ragebot.
	bool	  enable; //
	bool body_aimm;

	bool hitbox_selection;

	bool	  silent;
	int	  selection;
	bool	  fov;
	int		  fov_amount;
	bool hitbox[ 5 ];
	bool hitbox_history[6];
	bool multipoint[4];
	int		  scale;
	int		  body_scale;
	int		  minimal_damage;
	bool	  minimal_damage_hp;
	bool	  penetrate;
	int		  penetrate_minimal_damage;
	bool	  penetrate_minimal_damage_hp;
	bool      knifebot;
	bool	  zeusbot;

	bool kilffed;
	bool rodgol;

	bool hitsotyu_chams;
	int hitsotyu_chams_color[ 4 ] = { 255, 255, 255, 255 };
	int last_tick_key;

	// col2.
	int      zoom;
	bool      nospread;
	bool      norecoil;
	bool      hitchance;
	int	      hitchance_amount;
	bool      lagfix;
	bool	  correct; // 
	//MultiDropdown baim1;
	//MultiDropdown baim2;
	int        baim_hp;
	int       baim_key;

	// antiaim
	bool enable_aa;
	bool edge;
	int mode;

	int pitch_stand;
	int yaw_stand;
	int jitter_range_stand;
	int rot_range_stand;
	int rot_speed_stand;
	int rand_update_stand;
	int dir_stand;
	int dir_time_stand;
	int dir_custom_stand;
	int dir_lock;
	int base_angle_stand;
	int body_fake_stand;

	// col 2.
	int fake_yaw;
	int fake_relative;
	int fake_jitter_range;

	bool      lag_enable;
	//MultiDropdown lag_active;
	int    lag_mode;
	int    lag_limit;
	bool    lag_land;

	// visuals
	//MultiDropdown box;
	bool   box_enemy;
	Color   box_friendly;
	bool      dormant;
	bool      offscreen;
	Color   offscreen_color;
	//MultiDropdown name;
	//MultiDropdown health;
	//MultiDropdown flags_enemy;
	//MultiDropdown flags_friendly;
	//MultiDropdown weapon;
	int      weapon_mode;
	bool      ammo;
	bool      lby_update;
	Color   lby_update_color;

	// col2.
	//MultiDropdown skeleton;
	Color   skeleton_enemy;
	Color   skeleton_friendly;

	//MultiDropdown glow;
	Color   glow_enemy;
	Color   glow_friendly;
	int        glow_blend;
	//MultiDropdown chams_enemy;
	Color   chams_enemy_vis;
	Color   chams_enemy_invis;
	int        chams_enemy_blend;
	bool      chams_enemy_history;
	Color   chams_enemy_history_col;
	int        chams_enemy_history_blend;
	//MultiDropdown chams_friendly;
	Color   chams_friendly_vis;
	Color   chams_friendly_invis;
	int        chams_friendly_blend;
	bool      chams_local;
	Color   chams_local_col;
	int        chams_local_blend;
	bool      chams_local_scope;

	bool      items;
	bool      ammo_dropped;
	Color   item_color;
	bool      proj;
	Color   proj_color;
	//MultiDropdown proj_range;
	Color   proj_range_color;
	//MultiDropdown planted_c4;
	bool      disableteam;
	int	  world;
	bool      transparent_props;
	bool      enemy_radar;

	// col2.
	bool      novisrecoil;
	bool      nosmoke;
	bool      nofog;
	bool      noflash;
	bool      noscope;
	bool      fov_visuals;
	int        fov_amt;
	bool      fov_scoped;
	bool      viewmodel_fov;
	int        viewmodel_fov_amt;
	bool      spectators;
	bool      force_xhair;
	bool      spread_xhair;
	Color   spread_xhair_col;
	int        spread_xhair_blend;
	bool      pen_crosshair;
	//MultiDropdown indicators;
	bool      tracers;
	bool      impact_beams;
	Color   impact_beams_color;
	Color   impact_beams_hurt_color;
	int        impact_beams_time;
	int       thirdperson;

	int selected_id;
	bool enable_skinchanger;

	int skin_glock;
	int skin_deagle;

	int skin_elite;
	int skin_awp;
	int skin_ssg;
	int skin_auto_ct;
	int skin_auto_t;
	int skin_usp;
	int skin_revolver;
	int skin_tec;
	bool cltang;
	int fakewalkke;

	int weapon_seed;
	int weapon_wear;

	int box_color[ 4 ] = { 255, 255, 255, 255 };
	int name_color[ 4 ] = { 255, 255, 255, 255 };
	int weapon_color[ 4 ] = { 255, 255, 255, 255 };
	int skeleton_color[ 4 ] = { 255, 255, 255, 255 };
	int ammo_bar_color[ 4 ] = { 255, 255, 255, 255 };

	int chams_color_v[ 4 ] = { 255, 255, 255, 255 };
	int chams_color_iv[ 4 ] = { 255, 255, 255, 255 };

	int local_color_chams[ 4 ] = { 255, 255, 255, 255 };
	int menu_color[ 4 ] = { 255, 255, 255, 255 };
	bool local_chams;
	bool local_blend;

	int autobuyy;

	int knife_changer;


	bool night_mode;
	bool indicator_enable;
	bool hitmarker;
	bool proj_ranages;
	bool skeleton_esp;

	bool name_esp;
	bool weapon_esp;
	bool esp_icon_weapon;
	bool ammo_esp;
	bool lby_update_esp;
	bool health_esp;
	bool flags_esp;
	bool unlock_inve;
	bool enemy_glow;
	bool bullet_tracers;
	bool removefog;
	bool enemy_chams;
	bool damagelog;

	bool grenade_tracer;
	bool fullbrigan;
	bool force_xharir;
	bool remove_team;
	bool fov_while_scoped;

	bool noflashs;

	int tp_key;
	int key_style;

	bool dick_hop;
	bool autostopp;
	bool dick_strafe;

	bool vfov;
	int v_fov_am;
	bool planted_c4;

	int prediction_mode;

private:
}; extern CSettings settings;