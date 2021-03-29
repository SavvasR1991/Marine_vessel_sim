#pragma once
#ifndef GEOMETRY_FUNCTIONS_H
#define GEOMETRY_FUNCTIONS_H

#include <iostream>
#include <math.h>
#include <vector>
#include <list>
#include "Square_2D.h"
#include "Square_3D.h"
#include "Data_Constant_Values.h"

#define PI 3.14159265358979
#define R 6371000


namespace {
	/****************** GEOMETRY FUNCTIONS ********************/

	double angle_degree_normalization(double theta) {
		if (theta < 0) {
			theta = 360 + theta;
		}
		else if (theta > 360) {
			theta = theta - 360;
		}
		return theta;
	}

	double degrees_to_radians(double degrees) {
		return (degrees * (PI / 180));
	}

	double radians_to_degrees(double radian) {
		return (radian * (180 / PI));
	}

	double point_distance(double x0, double y0, double x1, double y1) {
		return sqrt(pow((x0 - x1), 2) + pow((y0 - y1), 2));
	}

	double point_distance_3d(double x0, double y0, double z0, double x1, double y1, double z1) {
		return sqrt(pow((x0 - x1), 2) + pow((y0 - y1), 2) + pow((z0 - z1), 2));
	}

	double angle_between_2d_points(double x0, double y0, double x1, double y1) {
		double angle = atan2((y1 - y0), (x1 - x0));
		double deggrees = radians_to_degrees(angle);
		return angle_degree_normalization(deggrees);
	}

	double angle_between_3d_points(double x0, double y0, double z0, double x1, double y1, double z1) {
		double angle_1, angle_2, angle;
		double third_side;
		double length = point_distance_3d(x0, y0, z0, x1, y1, z1);
		if (z1 != z0) {
			if (z1 > 0 && z0 > 0) {
				third_side = sqrt((length*length) - (abs(z1 - z0)*(abs(z1 - z0))));
			}
			else if (z1 < 0 && z0 < 0) {
				third_side = sqrt((length*length) - (abs(abs(z1) - abs(z0))*(abs(abs(z1) - abs(z0)))));
			}
			else {
				third_side = sqrt((length*length) - (abs(abs(z1) + abs(z0))*(abs(abs(z1) + abs(z0)))));
			}
			angle_1 = radians_to_degrees(acos(third_side / length));
			angle_2 = 90 - angle_1;

			if (z1 > z0) {
				angle = angle_1;
			}
			else {
				angle = 90 + angle_1;

			}
			return angle;

		}
		else {

			return 0;
		}
	}

	void move_to_direction(double &x0, double &y0, double d, double theta) {
		double theta_rad = degrees_to_radians(theta);
		x0 = x0 + d * cos(theta_rad);
		y0 = y0 + d * sin(theta_rad);
	}

	void move_to_direction_3d(double &x0, double &y0, double &z0, double d, double theta_xy, double theta_yz) {
		double theta_rad_xy = degrees_to_radians(theta_xy);
		double theta_rad_yz = degrees_to_radians(theta_yz);

		x0 = x0 + d * cos(theta_rad_xy)*cos(theta_yz);
		y0 = y0 + d * sin(theta_rad_xy)*cos(theta_yz);
		z0 = z0 + d * sin(theta_rad_yz);
	}

	bool point_is_in_range(double x0, double y0, double x1, double y1, double radius) {
		if (pow((x0 - x1), 2) + pow((y0 - y1), 2) < pow(radius, 2)) {
			return true;
		}
		else {
			return false;
		}
	}

	bool point_is_in_range_3d(double x0, double y0, double z0, double x1, double y1, double z1, double radius) {
		if (pow((x0 - x1), 2) + pow((y0 - y1), 2) + pow((z0 - z1), 2) < pow(radius, 2)) {
			return true;
		}
		else {
			return false;
		}
	}

	char * compass_direction_in_string(double curr_x, double curr_y, double target_x, double target_y) {
		char * compass_brackets[9] = { "N", "NE", "E", "SE", "S", "SW", "W", "NW", "N" };
		double delta_x = target_x - curr_x;
		double delta_y = target_y - curr_y;
		double degrees_final;
		int compass_look_up;

		double degrees_temp = radians_to_degrees(atan2(delta_x, delta_y));
		if (degrees_temp < 0) {
			degrees_final = 360 + degrees_temp;
		}
		else {
			degrees_final = degrees_temp;
		}
		compass_look_up = (int)(round(degrees_final / 45));
		return compass_brackets[compass_look_up];
	}

	void orthoProjection(double ax, double ay, double bx, double by, double cx, double cy, double &xp, double &yp) {
		double abx = bx - ax;
		double aby = by - ay;
		double	acx = cx - ax;
		double	acy = cy - ay;
		double	t = (abx * acx + aby * acy) / (abx * abx + aby * aby);
		xp = ax + t * abx;
		yp = ay + t * aby;
	}

	void get_point_by_relevant_radius(double ax, double ay, double bx, double by, double cx, double cy, double radius, double &xt, double &yt) {
		double xp, yp;
		orthoProjection(ax, ay, bx, by, cx, cy, xp, yp);

		double d = point_distance(xp, yp, cx, cy);
		double t = radius / d;
		xt = (1 - t)*cx + t * (xp);
		yt = (1 - t)*cy + t * (yp);
	}

	double critical_path_decelaration_calculation(double velocity, double decelaration) {
		double distance_coverted = 0;
		while (velocity > 0) {
			distance_coverted += velocity;
			velocity -= decelaration;
		}
		return distance_coverted;
	}

	int check_acceleration_deceleration(double &acceleration, double max_acc, double distance, double &velocity, double angle_deviation_hor, double dt) {
		if (velocity <= 0) {
			if (angle_deviation_hor >= 3) {
				acceleration = 0;
				return 1;
			}
			else {
				acceleration = max_acc;
				return 0;
			}
		}
		else {
			if (angle_deviation_hor >= 3 || (critical_path_decelaration_calculation(velocity, max_acc) >= (distance - velocity - max_acc))) {
				acceleration = -5*max_acc;
				double ve = 0.0;// velocity - 5 * max_acc;
				if (ve <= 0) {
					velocity = 0.0;
					acceleration = 0.0;
				}
				return 1;
			}
			else {
				acceleration = max_acc;
				return 0;

			}
		}
	}

	void sub_rectangles(vector<Square_2d*> &table, int factor_x, int factor_y, double westlimit, double southlimit, double eastlimit, double northlimit) {
		double lat_adj_factor = double(northlimit - southlimit) / double(factor_x);
		double lon_adj_factor = double(eastlimit - westlimit) / double(factor_y);

		vector<double> lat_list;
		vector<double> lon_list;

		for (int i = 0; i < factor_x + 1; i++) {
			lon_list.push_back(westlimit);
			westlimit += lon_adj_factor;
		}
		for (int i = 0; i < factor_y + 1; i++) {
			lat_list.push_back(southlimit);
			southlimit += lat_adj_factor;
		}
		for (int j = 0; j < (lat_list.size()) - 1; j++) {

			for (int i = 0; i < (lon_list.size()) - 1; i++) {
				Point a(lon_list[i], lat_list[j], 0.0);
				Point b(lon_list[i + 1], lat_list[j], 0.0);
				Point c(lon_list[i], lat_list[j + 1], 0.0);
				Point d(lon_list[i + 1], lat_list[j + 1], 0.0);
				table.push_back(new Square_2d(a, b, c, d));
			}
		}
	}

	void create_2d_grid(vector<Square_2d*> &table, double x1, double y1, double x3, double y3, int factor_x, int factor_y) {
		sub_rectangles(table, factor_x, factor_y, x1, y1, x3, y3);
	}

	void create_3d_grid(vector<Square_3d*> &table3d, double x1, double y1, double z1, double x3, double y3, double z3, int factor_x, int factor_y, int factor_z) {
		vector<Square_2d*> table;
		create_2d_grid(table, x1, y1, x3, y3, factor_x, factor_y);
		double z_dis = abs(abs(z3) - abs(z1));
		double z_segments = float(z_dis) / float(factor_z);
		Point *a, *b, *c, *d, *e, *f, *g, *h;
		a = new Point();
		b = new Point();
		c = new Point();
		d = new Point();

		for (int i = 0; i < factor_z; i++) {
			for (vector<Square_2d *>::iterator it = table.begin(); it != table.end(); ++it) {
				a->set_x((*it)->getPointA_x());
				a->set_y((*it)->getPointA_y());
				a->set_z(z1);

				b->set_x((*it)->getPointB_x());
				b->set_y((*it)->getPointB_y());
				b->set_z(z1);

				c->set_x((*it)->getPointC_x());
				c->set_y((*it)->getPointC_y());
				c->set_z(z1);

				d->set_x((*it)->getPointD_x());
				d->set_y((*it)->getPointD_y());
				d->set_z(z1);

				e = (*it)->getPointA();
				e->set_z(z1 - z_segments);

				f = (*it)->getPointB();
				f->set_z(z1 - z_segments);

				g = (*it)->getPointC();
				g->set_z(z1 - z_segments);

				h = (*it)->getPointD();
				h->set_z(z1 - z_segments);

				table3d.push_back(new Square_3d(a, b, c, d, e, f, g, h));
			}
			z1 = z1 - z_segments;
		}
	}

	bool point_inside_2d_area(Square_2d* area, double x, double y) {
		if (x >= area->getPointC_x() &&
			x <= area->getPointB_x() &&
			y >= area->getPointC_y() &&
			y <= area->getPointB_y())
		{
			return true;
		}
		return false;
	}

	bool point_inside_3d_area(Square_3d* area, double x, double y, double z) {
		if (x > area->getPointA_x() && x <= area->getPointH_x() && y < area->getPointA_y() && y >= area->getPointH_y() && z <  area->getPointA_z() && z >= area->getPointH_z()) {
			return true;
		}
		return false;
	}

	bool circles_intersection(double x1, double y1, double x2, double y2, double r1, double r2)
	{
		double distSq = point_distance(x1, y1, x2, y2);
		double radSumSq = (r1 + r2);
		if (distSq <= radSumSq)
			return true;
		else
			return false;
	}

	double findAngleOfRotation(double target_x, double target_y, double fieldWidth, double fieldHeight) {
		double sinOfAngle, angle;

		if (target_x >= fieldWidth && target_y >= fieldHeight) {  // top right
			sinOfAngle = (target_x - fieldWidth) / point_distance(target_x, target_y, fieldWidth, fieldHeight);
		}
		else if (target_x >= fieldWidth && target_y < fieldHeight) { // bottom right
			sinOfAngle = (target_x - fieldWidth) / point_distance(target_x, target_y, fieldWidth, fieldHeight);
		}
		else if (target_x < fieldWidth && target_y >= fieldHeight) { // top left
			sinOfAngle = (fieldWidth - target_x) / point_distance(target_x, target_y, fieldWidth, fieldHeight);
		}
		else if (target_x < fieldWidth && target_y < fieldHeight) { // bottom left
			sinOfAngle = (fieldWidth - target_x) / point_distance(target_x, target_y, fieldWidth, fieldHeight);
		}
		else {
			sinOfAngle = 0;
		}
		angle = asin(sinOfAngle);

		return angle;
	}

	void findPointsAtSpecificDistanceFromTwoOtherPoints(double x_1, double y_1, double distanceFromPoint1, double x_2, double y_2,double distanceFromPoint2,double & solution1_x, double &solution1_y, double& solution2_x, double &solution2_y) {
		if (y_1 == y_2) {
			y_2 = y_2 + 1;
		}
		if (x_1 == x_2) {
			x_2 = x_2 + 1 ;
		}
		double a = 2 * x_2 - 2 * x_1;
		double b = 2 * y_2 - 2 * y_1;
		double c = pow(x_1, 2) + pow(y_1, 2) - pow(distanceFromPoint1, 2) - pow(x_2, 2) - pow(y_2, 2) + pow(distanceFromPoint2, 2);
		double d = -(a / b);
		double e = -(c / b);
		double g = 1 + pow(d, 2);
		double h = (2 * d * e) - (2 * x_1) - (2 * y_1 * d);
		double i = pow(x_1, 2) + pow(e, 2) - (2 * y_1 * e) + pow(y_1, 2) - pow(distanceFromPoint1, 2);
		double diakrinousa = pow(h, 2) - (4 * g * i);
		if (diakrinousa < 0) {
			diakrinousa = 0;
		}
		solution1_x = (-h + sqrt(diakrinousa)) / (2 * g);
		solution1_y = (d * solution1_x) + e;
		solution2_x = (-h - sqrt(diakrinousa)) / (2 * g);
		solution2_y = (d * solution2_x) + e;
	}

	void calculatePositionOfNodeAfterRotation(double x_target, double y_target, double xBeforeRotation, double yBeforeRotation, double angleOfRotation, double direction, double &new_point_x, double &new_point_y) {

		double t_x = 0, t_y = 0, nodeDistanceFromEvent = 0, distanceFromPoint1 = 0;
		double solution1_x, solution1_y, solution2_x, solution2_y;

		nodeDistanceFromEvent = point_distance(x_target, y_target, xBeforeRotation, yBeforeRotation);
		t_x = cos(angleOfRotation) * nodeDistanceFromEvent;
		t_y = sin(angleOfRotation) * nodeDistanceFromEvent;
		distanceFromPoint1 = sqrt(pow(t_y, 2) + pow(nodeDistanceFromEvent - t_x, 2));
		findPointsAtSpecificDistanceFromTwoOtherPoints(xBeforeRotation, yBeforeRotation, distanceFromPoint1, x_target, y_target, nodeDistanceFromEvent, solution1_x, solution1_y, solution2_x, solution2_y);

		if (direction == 0) { // clockwise
			if (xBeforeRotation <= x_target) { // left side of event
				if (solution1_y >= solution2_y) {
					new_point_x = solution1_x;
					new_point_y = solution1_y;
				}
				else {
					new_point_x = solution2_x;
					new_point_y = solution2_y;
				}
			}
			else { // right side of event
				if (solution1_y <= solution2_y) {
					new_point_x = solution1_x;
					new_point_y = solution1_y;
				}
				else {
					new_point_x = solution2_x;
					new_point_y = solution2_y;
				}
			}
		}
		else { // counter clockwise
			if (xBeforeRotation <= x_target) { // left side of event
				if (solution1_y <= solution2_y) {
					new_point_x = solution1_x;
					new_point_y = solution1_y;
				}
				else {
					new_point_x = solution2_x;
					new_point_y = solution2_y;
				}
			}
			else { // right side of even
				if (solution1_y >= solution2_y) {
					new_point_x = solution1_x;
					new_point_y = solution1_y;
				}
				else {
					new_point_x = solution2_x;
					new_point_y = solution2_y;
				}
			}
		}
	}

	void rotatePoints(double &x, double &y, double cx, double cy, double angle)
	{
		double coss = cos(angle);
		double sins = sin(angle);
		double temp;
		temp = ((x - cx)*coss - (y - cy)*sins) + cx;
		y = ((x - cx)*sins + (y - cy)*coss) + cy;
		x = temp;
	}

}
#endif