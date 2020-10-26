#pragma once
#ifndef NAVIGATION_UXV_SYSTEM_H
#define NAVIGATION_UXV_SYSTEM_H
#include "Navigation_UxV_System.h"

/*************************** VESSEL NAVIGATION INTERFACE *****************************/
class Navigation_UxV_System {	//System plotting movements
	private:
		virtual void move() = 0;

		virtual void accelerate() = 0;
		virtual void decelerate() = 0;

		virtual void speed_balancing_equalizer() = 0;

		virtual void angle_balancing_equalizer() = 0;

		virtual bool radar_detection(double, double, double, double, double) = 0;
		virtual bool depth_detection(double, double, double, double, double) = 0;

		virtual char* display_compass_direction(double, double, double, double) = 0;
};

#endif
