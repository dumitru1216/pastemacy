#pragma once
#include "../includes.h"

#include "prediction/prediction.hpp"
#include "lag-comp/lc.hpp"

namespace gideon {
	__forceinline typedef unsigned int ptr;

	add_macro( c_prediction, g_prediction )
	add_macro( c_lc, g_lag_compensation )
}