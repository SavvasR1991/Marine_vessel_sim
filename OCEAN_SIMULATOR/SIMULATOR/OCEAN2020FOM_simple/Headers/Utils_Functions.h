#pragma once
#ifndef UTILS_FUNCTIONS_H
#define UTILS_FUNCTIONS_H

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <math.h>
#include <Windows.h>
#include <matrix/3dPoint.h>
#include "Point.h"
#include "General_functions.h"
#include "Geometry_Functions.h"


#define PI 3.14159265358979

using namespace std;
/****************** UTILS NAMESPACE FUNCTIONS *********************/

namespace {

	void create_patroling_reference_points(std::list<Point*> &list_in, double radar_radius, double xc, double yc, double xa, double ya, double xb, double yb, double z) {
		double patroling_length = point_distance(xc, yc, xa, ya);
		double deploy_length = 400;
		int chunks = 10;// (patroling_length) / (100 / NORMALIZER_GEODIC_MINUTES_TO_METERS);
		//cout << patroling_length << " " << deploy_length << " " << chunks << " "<< endl;
		double theta_chunk_left = angle_between_2d_points(xc, yc, xa, ya);
		double theta_chunk_right = angle_between_2d_points(xc, yc, xb, yb);

		double x_left = xc;
		double y_left = yc;

		double x_right = xc;
		double y_right = yc;

		Point *point_left;
		Point *point_right;

		radar_radius = 100;
		for (int i = 0; i < chunks; i++) {

			move_to_direction(x_left, y_left, radar_radius, theta_chunk_left);
			move_to_direction(x_right, y_right, radar_radius, theta_chunk_right);
			if (point_distance(x_left, y_left, xc, yc) >= deploy_length) {
				point_left = new Point(x_left, y_left, z);
				point_right = new Point(x_right, y_right, z);

				list_in.push_back(point_left);
				list_in.push_back(point_right);
			}
		}
	}

	void create_patroling_reference_points_in_cycles(std::list<Point*> &list_in, double vessel_area_radius, double ship_range, double refLatitude, double refLongitude, double refHeight) {
		int cycle_points = 10;
		int init_cycle_points = (int)(cycle_points / 2);

		double x, y, theta;
		double actinia = vessel_area_radius;
		double actinia_addition_2 = vessel_area_radius * 2.0;
		double actinia_addition_3 = ship_range / actinia_addition_2;
		double actinia_addition = ship_range / actinia_addition_3;

		while (actinia <= ship_range) {
			theta = degrees_to_radians(360.0 / cycle_points);
			for (int j = 0; j < cycle_points; j++) {
				x = refLatitude + actinia * cos(j * theta);
				y = refLongitude + actinia * sin(j * theta);
				list_in.push_back(new Point(x, y, refHeight));
			}
			cycle_points = cycle_points + init_cycle_points;
			actinia = actinia + actinia_addition;
		}
	}

	void create_patroling_reference_points_in_semi_cycles(std::list<Point*> &list_in, double vessel_area_radius, double ship_range, double refLatitude, double refLongitude, double refHeight, std::string direction) {
		int theta_start;
		if (direction.find("1") != std::string::npos) {
			theta_start = 0;
		}
		else {
			theta_start = degrees_to_radians(180.0);
		}
		int cycle_points = 8;
		int init_cycle_points = (int)(cycle_points / 2);

		double x, y, theta;
		double actinia = 400;
		double actinia_addition_2 = vessel_area_radius * 2.0;
		double actinia_addition_3 = ship_range / actinia_addition_2;
		double actinia_addition = 100;// ship_range / actinia_addition_3;

		while (actinia <= ship_range) {
			theta = degrees_to_radians(180.0 / cycle_points);
			for (int j = 0; j < cycle_points; j++) {
				x = refLatitude + actinia * cos(j * theta + theta_start);
				y = refLongitude + actinia * sin(j * theta + theta_start);
				list_in.push_back(new Point(x, y, refHeight));
			}
			cycle_points = cycle_points + init_cycle_points;
			actinia = actinia + actinia_addition;
		}
	}

	float sign(Dt3dPoint p1, Dt3dPoint p2, Dt3dPoint p3)
	{
		return (p1.x() - p3.x()) * (p2.y() - p3.y()) - (p2.x() - p3.x()) * (p1.y() - p3.y());
	}

	bool PointInTriangle(Dt3dPoint pt, Dt3dPoint v1, Dt3dPoint v2, Dt3dPoint v3)
	{
		float d1, d2, d3;
		bool has_neg, has_pos;

		d1 = sign(pt, v1, v2);
		d2 = sign(pt, v2, v3);
		d3 = sign(pt, v3, v1);

		has_neg = (d1 <= 0) || (d2 <= 0) || (d3 <= 0);
		has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

		return !(has_neg && has_pos);
	}

	int point_in_sector(double x, double y, std::map<int, std::vector<Dt3dPoint>> sectors, std::map<int, bool> &sector_surface_status_available) {
		if (!sectors.empty()) {
			Dt3dPoint A, B, C, X = Dt3dPoint(x, y, 0);
			bool inside = false;
			double xx;
			double yy;
			double th;

			for (std::map<int, std::vector<Dt3dPoint>>::iterator it = std::begin(sectors); it != std::end(sectors); ++it)
			{
				//cout << (it)->first << " " << (it)->second.at(0).x() << " " << (it)->second.at(0).y() << endl;
				A = (it)->second.at(0);
				B = (it)->second.at(1);
				C = (it)->second.at(2);

				xx = A.x();
				yy = A.y();
				th = radians_to_degrees(atan2((A.y() - C.y()), (A.x() - C.x())));
				move_to_direction(xx, yy, 1150.0, th);
				A.setX(xx);
				A.setY(yy);

				xx = B.x();
				yy = B.y();
				th = radians_to_degrees(atan2((B.y() - C.y()), (B.x() - C.x())));
				move_to_direction(xx, yy, 1150.0, th);
				B.setX(xx);
				B.setY(yy);
				inside = PointInTriangle(X, A, B, C);
				if (inside) {
					if (sector_surface_status_available[(it)->first] == false) {
						sector_surface_status_available[(it)->first] = true;
						return (it)->first;
					}
					else {
						return -1;
					}
				}
			}
		}
		return -1;
	}

	void oversight_segment_calculator(double x1, double y1, double  x2, double y2, int number, int segmemts, std::vector<double> &segmentation_x, std::vector<double> &segmentation_y) {

		std::vector<double> observed_x_cycle;
		std::vector<double>	observed_y_cycle;
		double myradians = atan2(y2 - (y1 + y2) / 2, x2 - (x1 + x2) / 2);
		int cycle_points = 40;
		double theta = degrees_to_radians(180.0 / cycle_points);
		double distance_n, myradians_n, theta_n, x0, y0, x, y;
		double distance = sqrt(((x1 - x2)*(x1 - x2)) + ((y1 - y2)*(y1 - y2)));

		double xp = (x1 + x2) / 2.0 + (distance / 2.0) * cos(0 * theta + myradians);
		double yp = (y1 + y2) / 2.0 + (distance / 2.0) * sin(0 * theta + myradians);
		observed_x_cycle.push_back(xp);
		observed_y_cycle.push_back(yp);


		for (int j = 1; j <= cycle_points; j++) {
			x = (x1 + x2) / 2.0 + (distance / 2.0) * cos(j * theta + myradians);
			y = (y1 + y2) / 2.0 + (distance / 2.0) * sin(j * theta + myradians);


			distance_n = sqrt(((xp - x)*(xp - x)) + ((yp - y)*(yp - y)));

			myradians_n = atan2((y - yp), (x - xp));
			theta_n = degrees_to_radians(90.0);

			x0 = (x + xp) / 2 + (distance_n)* cos(theta_n + myradians_n);
			y0 = (y + yp) / 2 + (distance_n)* sin(theta_n + myradians_n);

			observed_x_cycle.push_back(x0);
			observed_y_cycle.push_back(y0);

			observed_x_cycle.push_back((x + xp) / 2.0);
			observed_y_cycle.push_back((y + yp) / 2.0);

			myradians_n = atan2((yp - y), (xp - x));
			x0 = (x + xp) / 2.0 + (distance_n)* cos(theta_n + myradians_n);
			y0 = (y + yp) / 2.0 + (distance_n)* sin(theta_n + myradians_n);
			observed_x_cycle.push_back(x0);
			observed_y_cycle.push_back(y0);

			observed_x_cycle.push_back(x);
			observed_y_cycle.push_back(y);

			xp = x;
			yp = y;
		}
		int counter = 0;
		for (int i = 0; i < observed_x_cycle.size(); i++) {
			if (counter > number* ((observed_x_cycle).size() / segmemts) && counter <= (number + 1)* ((observed_x_cycle).size() / segmemts)) {
				segmentation_x.push_back(observed_x_cycle.at(i));
				segmentation_y.push_back(observed_y_cycle.at(i));
			}
			counter = counter + 1;
		}
	}

	/****************** CREATE TIME STAMP *********************/
	std::string getTimestamp() {
		time_t now = time(0);
		char* dt = ctime(&now);
		std::string time_stamp(dt);
		for (int i = 0; i < time_stamp.length(); i++) {
			if (time_stamp[i] == ' ' || time_stamp[i] == ':') {
				time_stamp[i] = '_';
			}
		}
		return time_stamp.substr(0, time_stamp.size() - 1);
	}

	/****************** KEY TO STOP PROGRAMM ******************/
	int keybrdTick()
	{
		char *keyPtr = DtPollBlockingInputLine();
		if (keyPtr && (*keyPtr == 'q' || *keyPtr == 'Q'))
			return -1;
		else if (keyPtr && (*keyPtr == 'r' || *keyPtr == 'R'))
			return 1;
		else
			return 0;
	}

	/****************** JOB TO STRING *************************/
	const char* getJobName(char job) {
		switch (job)
		{
		case 'R': return "reset";
		case 'P': return "patroling";
		case 'I': return "inspection";
		case 'V': return "vanguard";
		case 'H': return "hunting";
		case 'L': return "lock";
		default: return "ERROR";
		}
	}

	/****************** JOB TO STRING *************************/
	const char* getStatusName(char job) {
		switch (job)
		{
		case 'A': return "active";
		case 'D': return "damaged";
		case 'I': return "immobilized";
		case 'E': return "error";
		default: return "ERROR";
		}
	}

	/****************** GET CURRENT DIRECTORY *****************/
	std::string ExePath() {
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		std::string myString = std::string(buffer).substr(0, pos);
		std::string st = myString.substr(0, myString.size() - 1);
		return st;
	}

	/****************** GET CURRENT TIMESTAMPS ****************/
	std::string currentISO8601TimeUTC() {
		auto now = std::chrono::system_clock::now();
		auto itt = std::chrono::system_clock::to_time_t(now);
		std::ostringstream ss;
		ss << std::put_time(gmtime(&itt), "%FT%TZ");
		return ss.str();
	}

	std::string currentISO8601TimeUTC_seconds() {
		auto now = std::chrono::system_clock::now();
		auto itt = std::chrono::system_clock::to_time_t(now);
		std::ostringstream ss;
		ss << std::put_time(gmtime(&itt), "%SZ");
		return ss.str();
	}

	void DtRtiShutdownHandler(const char * label, void* finished)
	{
		//This callback may occur multiple times, since it gets called
		//every time we make an RTI call with an error. So, we mark this
		//as finished and make sure that we only signal once.
		int* finishedInt = (int*)finished;
		if (*finishedInt)
		{
			DtWarn << "Shutting down: " << label << std::endl;
		}
		*finishedInt = 0; //Order a shutdown;
	}

#if _WIN32

	void print_color_message(std::string message, int color, char check) {
		if (check == 'y') {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
			std::cout << message << flush;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		std::fflush(stdout);
	}

	void print_color_message(std::string message, int color) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		std::cout << message << flush;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		std::fflush(stdout);
	}

	void print_color_message_job(std::string message) {
		int color;
		if (message == "P") {
			color = 11;
		}
		else if (message == "R") {
			color = 15;
		}
		else if (message == "I") {
			color = 13;
		}
		else if (message == "V") {
			color = 12;
		}
		else if (message == "S") {
			color = 14;
		}
		else if (message == "L") {
			color = 10;
		}
		else {
			color = 7;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		std::cout << message << flush;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		std::fflush(stdout);

	}

	void cls()
	{
		// Get the Win32 handle representing standard output.
		// This generally only has to be done once, so we make it static.
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD topLeft = { 0, 0 };

		// std::cout uses a buffer to batch writes to the underlying console.
		// We need to flush that to the console because we're circumventing
		// std::cout entirely; after we clear the console, we don't want
		// stale buffered text to randomly be written out.
		std::cout.flush();

		// Figure out the current width and height of the console window
		if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
			// TODO: Handle failure!
			abort();
		}
		DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

		DWORD written;

		// Flood-fill the console with spaces to clear it
		FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

		// Reset the attributes of every character to the default.
		// This clears all background colour formatting, if any.
		FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

		// Move the cursor back to the top left for the next sequence of writes
		SetConsoleCursorPosition(hOut, topLeft);
	}

	void setCursorPosition(int x, int y)
	{
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout.flush();
		COORD coord = { (SHORT)x, (SHORT)y };
		SetConsoleCursorPosition(hOut, coord);
	}

	void cls(HANDLE hConsole)
	{
		COORD coordScreen = { 0, 0 };    // home for the cursor 
		DWORD cCharsWritten;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD dwConSize;

		// Get the number of character cells in the current buffer. 

		if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		{
			return;
		}

		dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

		// Fill the entire screen with blanks.

		if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer 
			(TCHAR) ' ',     // Character to write to the buffer
			dwConSize,       // Number of cells to write 
			coordScreen,     // Coordinates of first cell 
			&cCharsWritten))// Receive number of characters written
		{
			return;
		}

		// Get the current text attribute.

		if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		{
			return;
		}

		// Set the buffer's attributes accordingly.

		if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer 
			csbi.wAttributes, // Character attributes to use
			dwConSize,        // Number of cells to set attribute 
			coordScreen,      // Coordinates of first cell 
			&cCharsWritten)) // Receive number of characters written
		{
			return;
		}

		// Put the cursor at its home coordinates.

		SetConsoleCursorPosition(hConsole, coordScreen);
	}

}

#endif

#endif