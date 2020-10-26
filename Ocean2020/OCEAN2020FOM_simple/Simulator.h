#pragma once
#pragma once
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "airColumnStateRepository.h"
#include "AISStateRepository.h"
#include "landStateRepository.h"
#include "mineEventReportInterHLA.h"
#include "mosaicSeabedStateRepository.h"
#include "OCEAN2020EntityStateRepository.h"
#include "OCEAN2020RadioReceiverStateRepository.h"
#include "OCEAN2020RadioTransmitterStateRepository.h"
#include "reflectedAirColumnHLA.h"
#include "reflectedAirColumnListHLA.h"
#include "reflectedAISHLA.h"
#include "reflectedAISListHLA.h"
#include "reflectedBathymetryListHLA.h"
#include "reflectedBathymetryHLA.h"
#include "reflectedLandHLA.h"
#include "reflectedLandListHLA.h"
#include "reflectedMosaicSeabedHLA.h"
#include "reflectedMosaicSeabedListHLA.h"
#include "reflectedOCEAN2020EntityHLA.h"
#include "reflectedOCEAN2020EntityListHLA.h"
#include "reflectedOCEAN2020RadioTransmitterHLA.h"
#include "reflectedOCEAN2020RadioTransmitterListHLA.h"
#include "reflectedOCEAN2020RadioReceiverHLA.h"
#include "reflectedOCEAN2020RadioReceiverListHLA.h"
#include "reflectedTxRxLink_objHLA.h"
#include "reflectedTxRxLink_objListHLA.h"
#include "reflectedVS_EnvironmentHLA.h"
#include "reflectedVS_EnvironmentListHLA.h"
#include "reflectedWaterColumnHLA.h"
#include "reflectedWaterColumnListHLA.h"
#include "reflectedWaterSurfaceHLA.h"
#include "reflectedWaterSurfaceListHLA.h"
#include "txRx_Link_OffReqInterHLA.h"
#include "txRx_Link_OnReqInterHLA.h"
#include "txRxLink_objStateRepository.h"
#include "VS_EnvironmentStateRepository.h"
#include "waterColumnStateRepository.h"
#include "waterSurfaceStateRepository.h"

#include "airColumnPublisherHLA.h"
#include "airColumnStateRepository.h"
#include "AISPublisherHLA.h"
#include "AISStateRepository.h"
#include "bathymetryPublisherHLA.h"
#include "bathymetryStateRepository.h"
#include "landPublisherHLA.h"
#include "landStateRepository.h"
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

#include <vl/entityStateRepository.h>
#include <vl/environmentProcessRepository.h>
#include <vl/exerciseConn.h>
#include <vl/exerciseConnInitializer.h>
#include <vl/fireInteraction.h>
#include <vl/fomMapper.h>
#include <vl/reflectedEntity.h>
#include <vl/reflectedEntityList.h>
#include <vl/reflectedEnvironmentProcess.h>
#include <vl/reflectedEnvironmentProcessList.h>
#include <vl/signalInteraction.h>
#include <vl/startResumeInteraction.h>
#include <vl/topoView.h>
#include <vlutil/vlMiniDumper.h>
#include <vlutil/vlProcessControl.h>
#include <vlutil/vlRtiMismatchException.h>

#include <vlpi/entityTypes.h>
#include <vl/exerciseConn.h>
#include <vl/exerciseConnInitializer.h>
#include <vl/topoView.h>
#include <vl/entityPublisher.h>
#include <vl/entityStateRepository.h>
#include <vl/fireInteraction.h>
#include <vl/iffPublisher.h>
#include <vl/topoView.h>
#include <vlpi/entityTypes.h>
#include <vlutil/vlMiniDumper.h>
#include <vlutil/vlProcessControl.h>
#include <vlutil/vlRtiMismatchException.h>

#include <vlutil/vlMiniDumper.h>
#include <vlutil/vlProcessControl.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
//VC include

#include "UxV_Team.h"
#include "Enviromental_Elements.h"
#include "Data_Stuctures.h"
#include "Utils_Functions.h"
#include "JSON_Reader.h"

using namespace OCEAN2020;

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
	DtReflectedOCEAN2020FOMAirColumnList* refList_VS_EnvironmentAirColumn;
	DtReflectedOCEAN2020FOMLandList* refList_VS_EnvironmentLand;
	DtReflectedOCEAN2020FOMWaterSurfaceList* refList_VS_EnvironmentWaterSurface;
	DtReflectedOCEAN2020FOMWaterColumnList* refList_VS_EnvironmentWaterColumn;

	/************** SIMULATOR TALK *******************/
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
	char logs;
	EVENT *team_event;

	std::string log_dir_field;
	/************** SIMULATOR ENVIROMENTALS ************/
	Enviromental_Elements *enviromental_elements;

	/***************************************************/
	/************** SIMULATOR FUNCTIONS ****************/
	/***************************************************/
	void listen();
	void evaluateEvent();

	void talk(DtTime dt, DtTime simTime);
	void moveVessels(DtTime dt, DtTime simTime);
	void sendRadioTransmitter(DtTime simTime);

public:
	/****************** CONTSTRUCTOR /DESTRUCTOR **********************/
	Simulator();
	~Simulator();
	
	/****************** SIMULATOR FUNCTIONS ***************************/
	void start_simulator(int argc, char* argv[]);
	void set_up_simulator(int argc, char* argv[],USER_INIT_DATA, char,char);
	void start(int, char *argv[]);
	void setUpTeam();
	void cleanUp();
};

#endif