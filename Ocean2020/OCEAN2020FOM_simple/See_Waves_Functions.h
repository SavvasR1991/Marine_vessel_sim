#pragma once
#ifndef SEE_WAVES_FUNCTIONS_H
#define SEE_WAVES_FUNCTIONS_H

#include <math.h>

namespace {

	double slope_wave_calculation(double A, double l, double f, double t, double theta) {

		return A * (2 * PI / l) * sin(f * t + theta);
	}
}
#endif