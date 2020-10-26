#pragma once
#include "airColumnPublisherHLA.h"
#include "airColumnStateRepository.h"
#include "AISPublisherHLA.h"
#include "AISStateRepository.h"
#include "bathymetryPublisherHLA.h"
#include "bathymetryStateRepository.h"
#include "landPublisherHLA.h"
#include "landStateRepository.h"
#include "mineEventReportInterHLA.h"
#include "mosaicSeabedPublisherHLA.h"
#include "mosaicSeabedStateRepository.h"
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
#include "waterColumnPublisherHLA.h"
#include "waterColumnStateRepository.h"
#include "waterSurfacePublisherHLA.h"
#include "waterSurfaceStateRepository.h"

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
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <WinBase.h>
//VC include

#include "Sector.h"
#include "UxV_Vessel.h"
#include "Data_Stuctures.h"
#include "Utils_Functions.h"
#include "Geometry_Functions.h"
#include "Enviromental_Elements.h"

using namespace OCEAN2020;

class UxV_Team{

	private:
		/***************************************************/
		/************** UXV SHIP TEAM  ATTRIBUTES **********/
		/***************************************************/

		/********** TEAM SUMMARY DATA ***********/
		std::vector<UxV_Vessel*> team;
		std::map<std::string,TEAM_JOB_STATUS*> team_status;

		/********** SHIP DATA *******************/
		int uxv_num;
		int uxv_subwater;
		int uxv_surface;

		int team_id;
		int cycleCounter;

		double refLatitude;
		double refLongitude;
		double refHeight;

		double ship_range;

		std::string log_dir;
		std::string log_dir_field;
		/********** VESSEL DATA *****************/
		double uxv_sensor_range_sur;
		double uxv_sensor_range_sub;

		double uxv_sensor_depth_range;
		double uxv_sensor_area;

		double uxv_speed_sur;
		double angle_speed_sur;
		double ACCELERATION_sur;					//sensor speed
		double MAXIMUM_SPEED_sur;					//sensor speed
		double DECELERATION_sur;					//sensor speed
		double uxv_length_sur;
		double uxv_width_sur;
		double uxv_heigth_sur;

		double uxv_speed_sub;
		double angle_speed_sub;
		double ACCELERATION_sub;					//sensor speed
		double MAXIMUM_SPEED_sub;					//sensor speed
		double DECELERATION_sub;					//sensor speed
		double uxv_length_sub;
		double uxv_width_sub;
		double uxv_heigth_sub;

		double MAXIMUM_REVERSE_SPEED;


		bool team_reset_mode_on;
		char commnents;
		char logs;
		vector<FOM_EVENT *> fom_event;

		/***************************************************/
		/************** UXV SHIP TEAM  CONNECTION **********/
		/***************************************************/
		DtExerciseConn* myExConn;
		DtEntityType usvType;

		/***************************************************/
		/************** UXV SHIP TEAM  COMMANDS ************/
		/***************************************************/
		/******** CREATE VESSEL'S SECTORS *******/
		void create_log_enviroment();
		void initialize_team_attributes(TEAM_INIT_DATA, DtExerciseConn*);
		void deploy_UxV_vessels();
		Sector* create_Sectors(int);

		/******** PRINT VESSEL'S DATA ***********/
		void print_team_data();
		void print_team_status();

		/******** START VESSEL'S CYCLE **********/
		void evaluate_reset_mode(EVENT *event);
		void evaluate_FOM_income(Enviromental_Elements*);

		bool TeamsimTick(DtTime dt, EVENT*, DtTime simTime, Enviromental_Elements*);

	public:
		/****************** CONTSTRUCTOR /DESTRUCTOR **********************/
		UxV_Team(TEAM_INIT_DATA, DtExerciseConn*,char,char);
		~UxV_Team();

		/****************** TRIGGER TEAM FOR EVENT ************************/
		void start_team_cycle(DtTime d, EVENT*, DtTime simTime, Enviromental_Elements*);
};