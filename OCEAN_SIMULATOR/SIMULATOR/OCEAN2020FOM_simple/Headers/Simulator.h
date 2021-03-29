#pragma once
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "UxV_Team.h"

class Simulator {

private:
	/***************************************************/
	/************** SIMULATOR ATTRIBUTES ***************/
	/***************************************************/

	/**************** CONNECTIONS ********************/
	DtExerciseConn* exConn;
	DtExerciseConn* exConn_listen;

	/************** SIMULATOR LISTEN *****************/
	DtReflectedOCEAN2020FOMVS_EnvironmentList* refList_VS_Environment;
	DtReflectedOCEAN2020FOMWaterSurfaceList* refList_VS_EnvironmentWaterSurface;
	DtReflectedOCEAN2020FOMWaterColumnList* refList_VS_EnvironmentWaterColumn;
	DtReflectedOCEAN2020FOMRadioReceiverList* refList_VS_RadioReceiver;

	/************** SIMULATOR TALK *******************/
	DtReflectedOCEAN2020FOMTxRxLink_obj * TxRxLink_objObj;
	DtOCEAN2020FOMTxRxLink_objPublisher* TxRxLink_objPub;
	DtOCEAN2020FOMTxRx_Link_OnReqInter TxRx_Link_OnReqInter;
	DtOCEAN2020FOMTxRx_Link_OffReqInter TxRx_Link_OffReqinter;

	DtOCEAN2020FOMRadioTransmitterStateRepository* Ocean2020radioTransmitterSR;
	DtRadioTransmitterPublisher* Ocean2020radioTransmitterPub;

	/************** SIMULATOR TEAM *********************/
	UxV_Team *uxv_team;							//THE SHIP AND VESSEL
	TEAM_INIT_DATA uxv_team_init_data;		    //INIT DATA FOR SHIP TEAM
	bool b_changeval;
	bool b_once;
	DtTime simTime = 0;
	int cycles;

	char commnents;
	char commnents_basic;
	char logs;
	char logs_FOMS;
	char logs_Kalman;
	char logs_metrics;

	std::vector <EVENT*> team_event;
	std::string university_tag;
	std::string scenario;

	double timer_delay;
	std::string log_dir_field;
	std::string log_dir;
	std::string log_dir_timer;
	std::string log_dir_Kalman_Filter;
	std::string log_dir_metrics;

	std::string simulation_description;

	/************** SIMULATOR ENVIROMENTALS ************/
	Water_Waves_Kinematics *enviromental_elements;

	/************** SIMULATOR TIMERS *******************/
	double SIMULATION_TIMER;
	std::chrono::milliseconds SIMULATION_TIMER_DEV;

	double ref_lat;
	double ref_lon;
	double ref_depth;
	/***************************************************/
	/************** SIMULATOR FUNCTIONS ****************/
	/***************************************************/
	void listen(bool);
	void evaluateEvent();
	void talk(DtTime dt, DtTime simTime);
	void moveVessels(DtTime dt, DtTime simTime);
	void sendRadioTransmitter(DtTime simTime);

	void simulator_main(int argc, char* argv[]);
	void read_data_from_json(int, char* argv[], std::string, std::string, std::string);
	void create_log_enviroment(std::string);
	void start(int, char *argv[], std::string, std::string);
	void cleanUp();

public:
	/****************** CONTSTRUCTOR /DESTRUCTOR **********************/
	Simulator();
	~Simulator();
	
	/****************** SIMULATOR FUNCTIONS ***************************/
	void start_simulator(int argc, char* argv[], std::string, std::string);
	void start_simulator_T(std::string, std::string, std::string, char * argv[]);
};

#endif