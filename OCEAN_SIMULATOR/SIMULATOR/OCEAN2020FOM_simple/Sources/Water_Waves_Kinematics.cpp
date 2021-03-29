#include "Water_Waves_Kinematics.h"

/*************************************** ENVIROMENTAL_ELEMENTS.CPP *************************************************/
// [1] Enviromental_Elements() 						    constructor
// [2] ~Enviromental_Elements()					        destructor
// [3] bool set_enviromental_elements()					Set enviromental FOM to enviromental elements
// [4] void setWaterColumn()							set up water column vector to memory
// [5] void setWaterSurface()							set up water surface vector to memory
// [6] void created_2d_Water_Surface_field();			create 2D Field
// [7] void created_3d_Water_Current_field();			create 3D Field
// [8] void calculate_water_surface_2d_disruption();	Calculate 2d water surface disruptions
// [9] void calculate_water_current_3d_disruption();	Calculate 3d water currents disruptions
// [10] void set_enviromental_disruption_for_point();	Set up disruption to vessel
// [11] MESSAGES AVAILABILITY							check if FOM messages are available 
// [12] SEGMENTS GETTERS/SETTERS						Segments getters and setters
// [13] WaterColumns GETTERS							WaterColumns getters
// [14] Watersurface GETTERS							Watersurface getters
/*************************************** ENVIROMENTAL_ELEMENTS.CPP *************************************************/

#include <math.h>
#include <cmath> 
#define earthRadiusKm 6371.0

double slope_wave_calculation(double A, double l, double f, double t, double theta) {

	return A * (2 * PI / l) * sin(f * t + theta);
}
double deg2rad(double deg) {
	return (deg * M_PI / 180);
}
double rad2deg(double rad) {
	return (rad * 180 / M_PI);
}
boolean isBounded(double top, double left,	double bottom, double right,double latitude, double longitude) {
	/* Check latitude bounds first. */
	if (top >= latitude && latitude >= bottom) {
		if (left <= right && left <= longitude && longitude <= right) {
			return true;
		}
		else if (left > right && (left <= longitude || longitude <= right)) {
			return true;
		}
	}
	return false;
}
int compareAngles(double sourceAngle, double otherAngle)
{
	// sourceAngle and otherAngle should be in the range -180 to 180
	double difference = otherAngle - sourceAngle;

	if (difference < -180.0f)
		difference += 360.0f;
	if (difference > 180.0f)
		difference -= 360.0f;

	if (difference > 0.0f)
		return 1;
	if (difference < 0.0f)
		return -1;

	return 0;
}

//[1]
/************* Constructor **************************/
Water_Waves_Kinematics::Water_Waves_Kinematics(double refLat, double reflong, double refDepth) {
	std::cout << "---- Watercolumn receiver created" << std::endl;
	std::cout << "---- Watersurface receiver created" << std::endl;
	this->wcol_available = false;
	this->wsur_available = false;
	this->refLat = refLat;
	this->reflong = reflong;
	this->refDepth = refDepth;
}

//[2]
/************* Distructor ***************************/
Water_Waves_Kinematics::~Water_Waves_Kinematics() {
	std::cout << "---- Enviromental Water Waves receivers Deleted" << std::endl;
}

//[3]
/************* set_enviromental_elements ************/
bool Water_Waves_Kinematics::set_enviromental_elements(DtReflectedOCEAN2020FOMWaterSurfaceList* refList_VS_EnvironmentWaterSurface, DtReflectedOCEAN2020FOMWaterColumnList* refList_VS_EnvironmentWaterColumn)
{
	this->wcol_available = false;
	this->wsur_available = false;

	if ( refList_VS_EnvironmentWaterColumn->first() || refList_VS_EnvironmentWaterSurface->first())
	{
		if (refList_VS_EnvironmentWaterColumn->first())
		{
			DtOCEAN2020FOMWaterColumnStateRepository *first_VS_EnvironmentWaterColumnSR = refList_VS_EnvironmentWaterColumn->first()->waterColumnStateRep();
			setWaterColumn(first_VS_EnvironmentWaterColumnSR);
			created_3d_Water_Current_field();

		}
		if (refList_VS_EnvironmentWaterSurface->first())
		{
			DtOCEAN2020FOMWaterSurfaceStateRepository *first_VS_EnvironmentWaterSurfaceSR = refList_VS_EnvironmentWaterSurface->first()->waterSurfaceStateRep();
			setWaterSurface(first_VS_EnvironmentWaterSurfaceSR);
			created_2d_Water_Surface_field();
		}
		return (this->wcol_available | this->wsur_available);
	}
	else {
		return false;
	}

}

//[4]
/************* setWaterColumn  **********************/
void Water_Waves_Kinematics::setWaterColumn(DtOCEAN2020FOMWaterColumnStateRepository *first_VS_EnvironmentWaterColumnSR) {
	this->first_VS_EnvironmentWaterColumnSR = first_VS_EnvironmentWaterColumnSR;
}

//[5]
/************* setWaterSurface **********************/
void Water_Waves_Kinematics::setWaterSurface(DtOCEAN2020FOMWaterSurfaceStateRepository *first_VS_EnvironmentWaterSurfaceSR) {
	this->first_VS_EnvironmentWaterSurfaceSR = first_VS_EnvironmentWaterSurfaceSR;
}

//[6]
/*********** created_2d_Water_Surface_field *********/
void Water_Waves_Kinematics::created_2d_Water_Surface_field() {
	FOM_table_surface_vess.clear();

	DtFloat64 x_NW = this->getWaterSurfaceNWCornerLongitude();
	DtFloat64 y_NW = this->getWaterSurfaceNWCornerLatitude();

	DtFloat64 x_SE = this->getWaterSurfaceSECornerLongitude();
	DtFloat64 y_SE = this->getWaterSurfaceSECornerLatitude();

	bool if_center_in_storm = isBounded(y_NW, x_NW, y_SE, x_SE, this->refLat, this->reflong);
	
	if (if_center_in_storm) {

		int x_segments = this->getWaterSurfaceNumRows();
		int y_segments = this->getWaterSurfaceNumColumns();
		this->x_segments_2d = x_segments;
		this->y_segments_2d = y_segments;
		print_color_message("------- GET WaterSurface data : (" + to_string(x_segments) + "x" + to_string(y_segments) + ")\n", 10);
		print_color_message("-----------> (" + to_string(x_NW) + "," + to_string(y_NW) + ")->(" + to_string(x_SE) + "," + to_string(y_SE) + ")\n", 10);

		DtFloat64 current_frequency;
		DtFloat64 current_direction;
		DtFloat64 current_height;
		vector<Square_2d*> square_field_table;
		create_2d_grid(square_field_table, x_NW, y_NW, x_SE, y_SE, x_segments, y_segments);
		if (square_field_table.size() > 0) {
			int current_counter = 0;
			for (std::vector<Square_2d*>::iterator it = std::begin(square_field_table); it != std::end(square_field_table); ++it) {
				try
				{
					if (!this->first_VS_EnvironmentWaterSurfaceSR->wave_frequency().variableLengthFloat32Array().empty()) {
						int size_v = this->first_VS_EnvironmentWaterSurfaceSR->wave_frequency().variableLengthFloat32Array().size();
						if (size_v > current_counter) {
							current_frequency = this->first_VS_EnvironmentWaterSurfaceSR->wave_frequency().variableLengthFloat32Array()[current_counter];
							if (std::isnan(current_frequency)) {
								current_frequency = 0;
							}
						}
						else {
							current_frequency = 0;
						}
					}
					else {
						current_frequency = 0;
					}
				}
				catch (...) {
					current_frequency = 0;
				}

				try
				{
					if (!this->first_VS_EnvironmentWaterSurfaceSR->wave_direction().variableLengthFloat32Array().empty()) {
						int size_v = this->first_VS_EnvironmentWaterSurfaceSR->wave_direction().variableLengthFloat32Array().size();
						if (size_v > current_counter) {
							current_direction = this->first_VS_EnvironmentWaterSurfaceSR->wave_direction().variableLengthFloat32Array()[current_counter];
							if (std::isnan(current_direction)) {
								current_direction = 0;
							}
						}
						else {
							current_direction = 0;
						}
					}
					else {
						current_direction = 0;
					}
				}
				catch (...) {
					current_direction = 0;
				}

				try
				{
					if (!this->first_VS_EnvironmentWaterSurfaceSR->wave_height().variableLengthFloat32Array().empty()) {
						int size_v = this->first_VS_EnvironmentWaterSurfaceSR->wave_height().variableLengthFloat32Array().size();
						if (size_v > current_counter) {
							current_height = this->first_VS_EnvironmentWaterSurfaceSR->wave_height().variableLengthFloat32Array()[current_counter];
							if (std::isnan(current_height)) {
								current_height = 0;
							}
						}
						else {
							current_height = 0;
						}
					}
					else {
						current_height = 0;
					}
				}
				catch (...) {
					current_height = 0;
				}

				FOM_table_surface_vess.push_back(new ENVIROMENTAL_SURFACE_WATER_FIELD((*it), current_frequency, current_direction, current_height, current_counter));
				current_counter++;
			}
			this->wsur_available = true;
		}
		else {
			this->wsur_available = false;
		}
	}
	else {
		this->wsur_available = false;
	}
}

//[7]
/************* created_3d_Water_Current_field *******/
void Water_Waves_Kinematics::created_3d_Water_Current_field() {
	FOM_table_subwater_vess.clear();

	double x_NW = this->getWaterColumnNWCornerLongitude();
	double y_NW = this->getWaterColumnNWCornerLatitude();

	double x_SE = this->getWaterColumnSECornerLongitude();
	double y_SE = this->getWaterColumnSECornerLatitude();

	double z_Lower_layer = this->getWaterColumnShallowerLayer();
	double z_Deeper_layer = this->getWaterColumnDeeperLayer();
	bool if_center_in_storm = isBounded(y_NW, x_NW, y_SE, x_SE, this->refLat, this->reflong);
	if (if_center_in_storm && this->refDepth <= z_Lower_layer && this->refDepth >= z_Deeper_layer) {
		int x_segments = this->getWaterColumnNumRows();
		int y_segments = this->getWaterColumnNumColumns();
		int z_segments = this->getWaterColumnNumberOfLayers();

		this->set_x_segments_3d(x_segments);
		this->set_y_segments_3d(y_segments);
		this->set_z_segments_3d(z_segments);
		print_color_message("------- GET WaterColumn data  : (" + to_string(x_segments) + "x" + to_string(y_segments) + "x" + to_string(z_segments) + ")\n", 10);
		print_color_message("-----------> (" + to_string(x_NW) + "," + to_string(y_NW) + "," + to_string(z_Lower_layer) + ")->(" + to_string(x_SE) + "," + to_string(y_SE) + ","+ to_string(z_Deeper_layer)+") "+ +"\n", 10);

		DtFloat64 current_intensity = 0;
		DtFloat64 current_direction = 0;
		DtFloat64 current_salinity = 0;
		DtFloat64 current_temperature = 0;
		DtFloat64 current_height = 0;
		vector<Square_3d*> square_field_table;

		create_3d_grid(square_field_table, x_NW, y_NW, z_Lower_layer, x_SE, y_SE, z_Deeper_layer, x_segments, y_segments, z_segments);
		if (square_field_table.size() > 0) {
			int current_counter = 0;
			for (std::vector<Square_3d*>::iterator it = std::begin(square_field_table); it != std::end(square_field_table); ++it) {
				try
				{
					if (!this->first_VS_EnvironmentWaterColumnSR->current_intensity().variableLengthFloat64Array().empty()) {
						int size_v = this->first_VS_EnvironmentWaterColumnSR->current_intensity().variableLengthFloat64Array().size();
						if (size_v > current_counter) {
							current_intensity = this->first_VS_EnvironmentWaterColumnSR->current_intensity().variableLengthFloat64Array()[current_counter];
							if (std::isnan(current_intensity)) {
								current_intensity = 0;
							}
						}
						else {
							current_intensity = 0;
						}
					}
					else {
						current_intensity = 0;
					}
				}
				catch (...) {
					current_intensity = 0;
				}

				try
				{
					if (!this->first_VS_EnvironmentWaterColumnSR->current_direction().variableLengthFloat64Array().empty()) {
						int size_v = this->first_VS_EnvironmentWaterColumnSR->current_direction().variableLengthFloat64Array().size();
						if (size_v > current_counter) {
							current_direction = this->first_VS_EnvironmentWaterColumnSR->current_direction().variableLengthFloat64Array()[current_counter];
							if (std::isnan(current_direction)) {
								current_direction = 0;
							}
						}
						else {
							current_direction = 0;
						}
					}
					else {
						current_direction = 0;
					}
				}
				catch (...) {
					current_direction = 0;
				}
				try
				{
					if (!this->first_VS_EnvironmentWaterColumnSR->current_direction().variableLengthFloat64Array().empty()) {
						int size_v = this->first_VS_EnvironmentWaterColumnSR->salinity().variableLengthFloat64Array().size();
						if (size_v > current_counter) {
							current_salinity = this->first_VS_EnvironmentWaterColumnSR->salinity().variableLengthFloat64Array()[current_counter];
							if (std::isnan(current_salinity)) {
								current_salinity = 0;
							}
						}
						else {
							current_salinity = 0;
						}
					}
					else {
						current_salinity = 0;
					}
				}
				catch (...) {
					current_salinity = 0;
				}
				try
				{
					if (!this->first_VS_EnvironmentWaterColumnSR->current_direction().variableLengthFloat64Array().empty()) {
						int size_v = this->first_VS_EnvironmentWaterColumnSR->temperature().variableLengthFloat64Array().size();
						if (size_v > current_counter) {
							current_temperature = this->first_VS_EnvironmentWaterColumnSR->temperature().variableLengthFloat64Array()[current_counter];
							if (std::isnan(current_temperature)) {
								current_temperature = 0;
							}
						}
						else {
							current_temperature = 0;
						}
					}
					else {
						current_temperature = 0;
					}
				}
				catch (...) {
					current_temperature = 0;
				}
				FOM_table_subwater_vess.push_back(new ENVIROMENTAL_CURRENT_WATER_FIELD((*it), current_intensity, current_direction, current_salinity, current_temperature, current_height, current_counter));
				current_counter++;
			}
			this->wcol_available = true;
		}
		else {
			this->wcol_available = false;
		}
	}
	else {
		this->wcol_available = false;
	}
}

//[8]
/******* calculate_water_surface_2d_disruption *******/
void Water_Waves_Kinematics::calculate_water_surface_2d_disruption(FOM_EVENT *event, double x, double y, double angle_hor, double vel, ENVIROMENTAL_SURFACE_WATER_FIELD* field, double L, double B, double T, double mass, int counter) {

	event->set_z_dis(0.0);
	event->set_angle_ver_dis(0.0);

	float water_density = 1;
	double wave_direction = degrees_to_radians(angle_degree_normalization(field->get_WaterSurfaceSE_wave_direction()-90));
	double wave_frequency = field->get_WaterSurfaceSE_wave_frequency();
	double wave_height = field->get_WaterSurfaceSE_wave_height();
	double wave_speed = 1.56 * (1 / wave_frequency);
	double constant_1 = fabs(water_density * GRAVITY*B*L*T);
	double wave_slope = slope_wave_calculation(wave_height, wave_speed, wave_frequency, counter, 0);
	double x_force = constant_1 * cos(wave_direction) * fabs(wave_slope);
	double y_force = constant_1 * sin(wave_direction) * fabs(wave_slope);
	double disr_angle = 0;
	double disr_velocity = 0;
	double vel_x = vel * cos((DtDeg2Rad(angle_hor)));
	double vel_y = vel * sin((DtDeg2Rad(angle_hor)));

	double a_x = (x_force / (mass*20));
	double a_y = (y_force / (mass*20));

	vel_x = vel_x + a_x;
	vel_y = vel_y + a_y;


	if (vel <= 0.0001) {
		disr_angle = (0.0);
		disr_velocity = 0.0;
	}
	else {
		disr_velocity = sqrt(vel_x*vel_x + vel_y * vel_y);

		disr_angle = angle_degree_normalization(DtRad2Deg(atan2(vel_y, vel_x)));
		double angle_diff = (disr_angle - angle_hor);
		angle_diff = std::fmod((angle_diff + 180), 360) - 180;
		angle_diff = std::fabs(angle_diff);
		if (compareAngles(angle_hor, disr_angle) == 1) {
			disr_angle = angle_diff;
		}
		else if (compareAngles(angle_hor, disr_angle) == -1) {
			disr_angle = -angle_diff;
		}
		else {
			disr_angle = (0.0);
		}
	}

	event->set_angle_hor_dis(disr_angle);
	event->set_velocity(disr_velocity);
	event->set_incoming_event_message();
}

//[9]
/******* calculate_water_current_3d_disruption *******/
void Water_Waves_Kinematics::calculate_water_current_3d_disruption(FOM_EVENT *event, double x, double y, double z, double angle_hor, double angle_ver,double vel, double angle_vel_hor, double angle_vel_ver,ENVIROMENTAL_CURRENT_WATER_FIELD* field, double mass, double radius) {
	
	float wave_direction = angle_degree_normalization(field->get_SubWater_wave_direction() - 90);
	float wave_intensity = field->get_SubWater_wave_intensity();
	float wave_height = field->get_SubWater_wave_height();
	float wave_temperature = field->get_SubWater_wave_temperature();
	float wave_salinity = field->get_SubWater_wave_salinity();

	double disr_velocity = 0.0;
	double disr_angle = 0.0;
	double a0 = 999.842594;
	double a1 = 6.793953e-2;
	double a2 = -9.095290e-3;
	double a3 = 1.001685e-4;
	double a4 = -1.120083e-6;
	double a5 = 6.536332e-9;
	double ρsmow = a0 + a1*wave_temperature + a2*pow(wave_temperature,2) + a3*pow(wave_temperature, 3) + a4*pow(wave_temperature, 4) + a5*pow(wave_temperature, 5);
	double B1 = 8.2449e-1 + -4.08993 - 3 * wave_temperature + 7.6438e-5 * pow(wave_temperature, 2) + -8.2467e-7 *pow(wave_temperature, 3) + 5.3875e-9*pow(wave_temperature, 4);
	double C1 = -5.7246e-3 + 1.0227e-4 * wave_temperature + -1.6546e-6 *pow(wave_temperature, 2);
	double d0 = 4.8314e-4;
	double water_density = ρsmow + B1 * wave_salinity + C1 * pow(wave_salinity, 1.5) + d0 * pow(wave_salinity, 2);
	double Force_drag;
	double Force_inertia = 0;
	double Force_Subwater_Current_Total;
	double drag_coeff = 0.82;
	double inertia_coeff = 1.0;

	Force_drag = (double) 0.5 * (double)drag_coeff* (double)water_density * (double)radius * (double)wave_intensity;
	Force_Subwater_Current_Total = fabs(Force_drag + Force_inertia);
	
	double vel_x = vel * cos((DtDeg2Rad(angle_hor)));
	double vel_y = vel * sin((DtDeg2Rad(angle_hor)));

	double Force_Subwater_Current_Total_x = (Force_Subwater_Current_Total)* cos(DtDeg2Rad(wave_direction));
	double Force_Subwater_Current_Total_y = (Force_Subwater_Current_Total)* sin(DtDeg2Rad(wave_direction));

	double a_x = (Force_Subwater_Current_Total_x / (mass*10));
	double a_y = (Force_Subwater_Current_Total_y / (mass*10));


	vel_x = vel_x + a_x;
	vel_y = vel_y + a_y;

	if (vel <= 0.0001) {
		disr_angle = (0.0);
		disr_velocity = 0.0;
	}
	else {
		disr_velocity = sqrt(vel_x*vel_x + vel_y * vel_y);

		disr_angle = angle_degree_normalization(DtRad2Deg(atan2(vel_y, vel_x)));
		double angle_diff = (disr_angle - angle_hor);
		angle_diff = std::fmod((angle_diff + 180), 360) - 180;
		angle_diff = std::fabs(angle_diff);
		if (compareAngles(angle_hor, disr_angle) == 1) {
			disr_angle = angle_diff;
		}
		else if (compareAngles(angle_hor, disr_angle) == -1) {
			disr_angle = -angle_diff;
		}
		else {
			disr_angle = (0.0);
		}
	}

	event->set_angle_hor_dis(disr_angle);
	event->set_velocity(disr_velocity);

	event->set_incoming_event_message();

}

//[10]
/******* set_enviromental_disruption_for_point *******/
void Water_Waves_Kinematics::set_enviromental_disruption_for_point(std::string name, FOM_EVENT* event, double x, double y, double z,double angle_hor, double angle_ver, double vel, double angle_vel_h, double angle_vel_v, std::string type,	double B, double L, double T, double mass, double radius, int counter) {
	bool if_center_in_storm = false;
	int icounter = 1;
	bool once = true;
	if (type.compare("SURFACE")==0) {
		for (std::vector<ENVIROMENTAL_SURFACE_WATER_FIELD*>::iterator it = std::begin(this->FOM_table_surface_vess); it != std::end(this->FOM_table_surface_vess); ++it)
		{
			if_center_in_storm = isBounded((*it)->get_2d_square()->getPointA_y(), (*it)->get_2d_square()->getPointA_x(), (*it)->get_2d_square()->getPointD_y(), (*it)->get_2d_square()->getPointD_x(), this->refLat, this->reflong);
			if (if_center_in_storm) {
				if (((*it)->get_WaterSurfaceSE_wave_direction() > 0) && ((*it)->get_WaterSurfaceSE_wave_frequency() > 0) && ((*it)->get_WaterSurfaceSE_wave_height() > 0)) {
					print_color_message("--- " + name + " , surfacewave [" + to_string(icounter) + "]\n", COLOR_TEXT::RED_COLOR);
					calculate_water_surface_2d_disruption(event, x, y, angle_hor, vel, (*it), B, L, T, mass, counter);
				}
				else {
					event->cleanFOM_evaluator();
				}
				break;
			}
			icounter++;
		}
	}
	else {
		for (std::vector<ENVIROMENTAL_CURRENT_WATER_FIELD*>::iterator it = std::begin(this->FOM_table_subwater_vess); it != std::end(this->FOM_table_subwater_vess); ++it)
		{
			if_center_in_storm = isBounded((*it)->get_3d_square()->getPointA_y(), (*it)->get_3d_square()->getPointA_x(), (*it)->get_3d_square()->getPointD_y(), (*it)->get_3d_square()->getPointD_x(), this->refLat, this->reflong);
			if (if_center_in_storm && this->refDepth <= (*it)->get_3d_square()->getPointA_z() && this->refDepth >= (*it)->get_3d_square()->getPointH_z()) {
				print_color_message("--- " + name + " , subwater ["+to_string(icounter) +"]\n", COLOR_TEXT::RED_COLOR);
				calculate_water_current_3d_disruption(event, x, y, z, angle_hor, angle_ver, vel, angle_vel_h, angle_vel_v, (*it), mass, radius);
				break;
			}
			icounter++;
		}
	}
}

//[11]
/************ CHECK IS MESSAGES ARE AVAILABLE ********/
bool Water_Waves_Kinematics::water_wave_messages_available() { return this->wsur_available; }
bool Water_Waves_Kinematics::water_currect_messages_available() { return this->wcol_available; }

//[12]
/************* SEGMENTS GETTERS/SETTERS *************/
int Water_Waves_Kinematics::get_x_segments_2d() {

	return this->x_segments_2d;
}
int Water_Waves_Kinematics::get_y_segments_2d() {

	return this->y_segments_2d;
}
int Water_Waves_Kinematics::get_x_segments_3d() {

	return this->x_segments_3d;
}
int Water_Waves_Kinematics::get_y_segments_3d() {

	return this->y_segments_3d;
}
int Water_Waves_Kinematics::get_z_segments_3d() {

	return this->z_segments_3d;
}
void Water_Waves_Kinematics::set_x_segments_2d(int x) {
	this->x_segments_2d = x;
}
void Water_Waves_Kinematics::set_y_segments_2d(int y) {
	this->y_segments_2d = y;
}
void Water_Waves_Kinematics::set_x_segments_3d(int x) {
	this->x_segments_3d = x;
}
void Water_Waves_Kinematics::set_y_segments_3d(int y) {
	this->y_segments_3d = y;
}
void Water_Waves_Kinematics::set_z_segments_3d(int z) {
	this->z_segments_3d = z;
}

//[13]
/************* WaterColumns GETTERS *****************/
DtU32 Water_Waves_Kinematics::getWaterColumnNumRows()	{ return this->first_VS_EnvironmentWaterColumnSR->numRows();}
DtU32 Water_Waves_Kinematics::getWaterColumnNumColumns() { return this->first_VS_EnvironmentWaterColumnSR->numColumns();}
DtFloat64 Water_Waves_Kinematics::getWaterColumnNWCornerLatitude()  { return this->first_VS_EnvironmentWaterColumnSR->NWCornerLatitude();}
DtFloat64 Water_Waves_Kinematics::getWaterColumnNWCornerLongitude() { return this->first_VS_EnvironmentWaterColumnSR->NWCornerLongitude();}
DtFloat64 Water_Waves_Kinematics::getWaterColumnSECornerLatitude()  { return this->first_VS_EnvironmentWaterColumnSR->SECornerLatitude();}
DtFloat64 Water_Waves_Kinematics::getWaterColumnSECornerLongitude() { return this->first_VS_EnvironmentWaterColumnSR->SECornerLongitude();}
DtInt32 Water_Waves_Kinematics::getWaterColumnNumberOfLayers()	   { return this->first_VS_EnvironmentWaterColumnSR->numberOfLayers();}
DtInt32 Water_Waves_Kinematics::getWaterColumnShallowerLayer()	   { return this->first_VS_EnvironmentWaterColumnSR->shallowerLayer();}
DtInt32 Water_Waves_Kinematics::getWaterColumnDeeperLayer()		   { return this->first_VS_EnvironmentWaterColumnSR->deeperLayer();}
DtOCEAN2020FOMVariableLengthFloat32Array Water_Waves_Kinematics::getWaterColumnLayers() { return this->first_VS_EnvironmentWaterColumnSR->waterDepth(); }

//[14]
/************* Watersurface GETTERS *****************/
DtU32 Water_Waves_Kinematics::getWaterSurfaceNumRows()	 { return this->first_VS_EnvironmentWaterSurfaceSR->numRows();}
DtU32 Water_Waves_Kinematics::getWaterSurfaceNumColumns() { return this->first_VS_EnvironmentWaterSurfaceSR->numColumns();}
DtFloat64 Water_Waves_Kinematics::getWaterSurfaceNWCornerLatitude()  { return this->first_VS_EnvironmentWaterSurfaceSR->NWCornerLatitude();}
DtFloat64 Water_Waves_Kinematics::getWaterSurfaceNWCornerLongitude() { return this->first_VS_EnvironmentWaterSurfaceSR->NWCornerLongitude();}
DtFloat64 Water_Waves_Kinematics::getWaterSurfaceSECornerLatitude()  { return this->first_VS_EnvironmentWaterSurfaceSR->SECornerLatitude();}
DtFloat64 Water_Waves_Kinematics::getWaterSurfaceSECornerLongitude() { return this->first_VS_EnvironmentWaterSurfaceSR->SECornerLongitude(); }
DtOCEAN2020FOMVariableLengthFloat32Array Water_Waves_Kinematics::getWaterSurfaceSE_wave_frequency_array() { return this->first_VS_EnvironmentWaterSurfaceSR->wave_frequency();}
DtOCEAN2020FOMVariableLengthFloat32Array Water_Waves_Kinematics::getWaterSurfaceSE_wave_height_array() { return this->first_VS_EnvironmentWaterSurfaceSR->wave_height(); }
DtOCEAN2020FOMVariableLengthFloat32Array Water_Waves_Kinematics::getWaterSurfaceSE_wave_direction_array() { return this->first_VS_EnvironmentWaterSurfaceSR->wave_direction(); }


///////////////////////////////
// 	TESTING MODE FUNCTION    //
///////////////////////////////
void Water_Waves_Kinematics::created_2d_Water_Surface_field_T(DtFloat64 x_NW, DtFloat64 y_NW,DtFloat64 x_SE, DtFloat64 y_SE,DtFloat64 current_frequency,DtFloat64 current_direction,DtFloat64 current_height,int x_segments, int y_segments) {
	FOM_table_surface_vess.clear();
	vector<Square_2d*> square_field_table;

	create_2d_grid(square_field_table, x_NW, y_NW, x_SE, y_SE, x_segments, y_segments);
	int current_counter = 0;
	for (std::vector<Square_2d*>::iterator it = std::begin(square_field_table); it != std::end(square_field_table); ++it) {
		FOM_table_surface_vess.push_back(new ENVIROMENTAL_SURFACE_WATER_FIELD((*it), current_frequency, current_direction, current_height, current_counter));
		current_counter++;
	}
}

void Water_Waves_Kinematics::created_3d_Water_Current_field_T(DtFloat64 x_NW, DtFloat64 y_NW, DtFloat64 z_NW, DtFloat64 x_SE, DtFloat64 y_SE, DtFloat64 z_SE, DtFloat64 current_intensity, DtFloat64 current_direction, DtFloat64 current_salinity, DtFloat64 current_temperature, int x_segments, int y_segments, int z_segments) {
	FOM_table_subwater_vess.clear();
	vector<Square_3d*> cube_field_table;
	DtFloat64 current_height = 1;
	create_3d_grid(cube_field_table, x_NW, y_NW,z_NW, x_SE, y_SE, z_SE, x_segments, y_segments, z_segments);
	int current_counter = 0;
	for (std::vector<Square_3d*>::iterator it = std::begin(cube_field_table); it != std::end(cube_field_table); ++it) {
		FOM_table_subwater_vess.push_back(new ENVIROMENTAL_CURRENT_WATER_FIELD((*it), current_intensity, current_direction, current_salinity, current_temperature, current_height, current_counter));
		current_counter++;
	}

}
