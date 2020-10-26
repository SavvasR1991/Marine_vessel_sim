#pragma once

#include "OCEAN2020EntityPublisherHLA.h"
#include "OCEAN2020EntityStateRepository.h"
#include "OCEAN2020RadioTransmitterPublisherHLA.h"
#include "OCEAN2020RadioTransmitterStateRepository.h"
#include "OCEAN2020RadioReceiverPublisherHLA.h"
#include "OCEAN2020RadioReceiverStateRepository.h"
#include "txRxLink_objPublisherHLA.h"
#include "txRxLink_objStateRepository.h"
#include "txRx_Link_OffReqInterHLA.h"
#include "txRx_Link_OnReqInterHLA.h"
#include "VS_EnvironmentPublisherHLA.h"
#include "VS_EnvironmentStateRepository.h"

#include <vlpi/entityTypes.h>
#include <vl/exerciseConn.h>
#include <vl/exerciseConnInitializer.h>
#include <vl/topoView.h>
#include <vl/entityPublisher.h>
#include <vl/entityStateRepository.h>
#include <vl/fireInteraction.h>
#include <vl/iffPublisher.h>

#include <vlutil/vlMiniDumper.h>
#include <vlutil/vlProcessControl.h>

#include <matrix/3dPoint.h>
#include <stdio.h>
#include <list>
#include <string>
#include <iostream>
//VC include

#include <cmath>
#include "Sector.h"

#include "UxV_Jobs.h"
#include "Data_Stuctures.h"
#include "Utils_Functions.h"
#include "General_functions.h"
#include "Geometry_Functions.h"
#include "Navigation_UxV_System.h"
#include "Point.h"

using namespace OCEAN2020;

class UxV_Vessel: public Jobs, public Navigation_UxV_System {
private:
	/**************************************************/
	/***************** VESSEL ATTRIBUTES **************/
	/**************************************************/
	int id;
	int team_id;
	int cycleCounter;

	double linear_velocity;
	double angular_velocity;

	double Max_acceleration;
	double Max_deceleration;

	double acceleration;
	double deceleration;
	double maximum_speed;
	double maximum_reverse_speed;
	int velocity_status;

	double scanning_radius;
	double depth_radius;

	double length;
	double width;
	double heigth;
	double mass;
	double vessel_area;

	std::string name;
	std::string type;
	std::string log_dir;
	std::string enviromental_attr;

	char status;
	char comments;
	char logs;

	bool detected_target;
	bool reset_mode_on;

	DtTime simTime;

	enum EVENT_MESSAGE event_message;

	/************ VESSEL FOM ****************/
	DtEntityPublisher* VesselDataPub;
	DtOCEAN2020EntityStateRepository* VesselDataSR;
	DtTopoView* VesselDataTopoView;

	/********* VESSEL SECTOR IN SHIP ********/
	Sector* sector;
	Dt3dPoint* C;
	Dt3dPoint* A;
	Dt3dPoint* B;

	std::list<Point*> patroling_points;
	list<Point*>::iterator current_patroling_point;

	/********** VESSEL KINIMATICS COORD *****/
	double reference_Longitude;
	double reference_Latitude;
	double reference_Height;

	double deploy_Longitude;
	double deploy_Latitude;
	double deploy_Height;

	double reference_theta_horizontal;
	double reference_theta_vertical;


	VESSEL_KINEMATICS *kinematics_status;
	FOM_EVENT *fom_event_evaluator;
	/********** VESSEL REF JOB **************/
	char job;

	/***************************************************/
	/***************** VESSEL CONNECTION ***************/
	/***************************************************/
	DtExerciseConn* exConn;

	/***************************************************/
	/***************** VESSEL CYCLE COMMANDS ***********/
	/***************************************************/
	EVENT_MESSAGE evaluateEvent(EVENT*);
	bool scanArea();
	bool calculateWeight(DtTime dt, std::map<std::string, TEAM_JOB_STATUS*>);
	bool execute(DtTime dt);
	bool publish_possition();
	void set_FOM_disruptions();

	/***************************************************/
	/***************** VESSEL JOBS COMMANDS ************/
	/***************************************************/
	void patroling();
	void vanguared();
	void reset();
	void inspection();
	void shadowing();
	void lock();

	/***************************************************/
	/***************** NAVIGATION JOBS *****************/
	/***************************************************/
	void move();

	void accelerate();
	void decelerate();

	void speed_balancing_equalizer();

	void angle_balancing_equalizer();

	bool radar_detection(double, double, double, double, double);
	bool depth_detection(double, double, double, double, double);

	char* display_compass_direction(double, double, double, double);

public:
	/****************** CONTSTRUCTOR /DESTRUCTOR **********************/
	UxV_Vessel(VESSEL_INIT_DATA, DtExerciseConn*,char,char);
	~UxV_Vessel();

	/****************** GETTERS /SETTERS ******************************/
	void setSector(Sector *);
	VESSEL_KINEMATICS* get_current_kinematics();
	double get_x();
	double get_y();
	double get_z();
	double get_deploy_x();
	double get_deploy_y();
	double get_deploy_z();
	double get_reference_angle_horizontal();
	double get_reference_angle_vertical();
	double get_linear_velocity();
	double get_angular_velocity();
	double get_mass();
	double get_length();
	double get_width();
	double get_craft();

	std::string getName();
	std::string getType();
	char getJob();
	char getStatus();

	/****************** TRIGGER VESSEL FOR EVENT **********************/
	bool VesselsimTick(DtTime dt, std::map<std::string, TEAM_JOB_STATUS*>, EVENT*, FOM_EVENT*, DtTime simTime, int);
};