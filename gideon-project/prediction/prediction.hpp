#pragma once
#include "../g_inc.hpp"

namespace gideon {
	class c_prediction {
	public:
		void save( );
		void restore( );

	private:
		float servertime{};
		float frametime;
		int tickcount;
	};
}