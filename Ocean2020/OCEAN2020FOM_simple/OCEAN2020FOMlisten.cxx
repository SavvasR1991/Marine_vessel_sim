/****************************************************************************
 * Copyright (c) 2017 VT MAK
 * All rights reserved.
 ****************************************************************************/

 //! \file listen.cxx
 //! \brief Contains the simple listen example.
 //! \ingroup simple

 //Project include
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

//VRLINK include
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

//VC include
#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace OCEAN2020;

int keybrdTick(void);

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

/**********************************************************
** Define a callback to process Start resume interactions.
** link to VR-Forces scenario run
***********************************************************/
void StartResumeCb(DtStartResumeInteraction* StartResumeInt, void* /*usr*/)
{
	std::cout << "Start Resume Interaction Interaction from "<< std::endl;
	StartResumeInt->printData();
}

/*************************************************
** Define callback to process TxRxLink_obj object.
**************************************************/
void updateObject_TxRxLink_obj(DtReflectedOCEAN2020FOMTxRxLink_obj* refObj, void* /*usr*/)
{
	std::cout << "Received TxRxLink_obj Update" << std::endl;
	*(refObj->txRxLink_objStateRep());
}

void discoverObject_TxRxLink_obj(DtReflectedOCEAN2020FOMTxRxLink_obj* refObj, void* /*usr*/)
{
	std::cout << "Discovered new TxRxLink_obj" << std::endl;
	std::cout << *(refObj->txRxLink_objStateRep()) << std::endl;
	refObj->addPostUpdateCallback(updateObject_TxRxLink_obj, 0);
}

void removeObject_TxRxLink_obj(DtReflectedOCEAN2020FOMTxRxLink_obj* refObj, void* /*usr*/)
{
	std::cout << "TxRxLink_obj Removed" << std::endl;
	std::cout << *(refObj->txRxLink_objStateRep()) << std::endl;
}

/*****************************************************************
** Define a callback to process TxRx_Link_OnReq interactions.
******************************************************************/
void TxRx_Link_OnReqInterCB(DtOCEAN2020FOMTxRx_Link_OnReqInter* inter, void* /*usr*/)
{
	std::cout << "Received TxRx_Link_OnReqInter Interaction." << std::endl;
	*inter;
}

/*****************************************************************
** Define a callback to process TxRx_Link_OffReq interactions.
******************************************************************/
void TxRx_Link_OffReqInterCB(DtOCEAN2020FOMTxRx_Link_OffReqInter* inter, void* /*usr*/)
{
	std::cout << "Received TxRx_Link_OffReqInter Interaction." << std::endl;
	*inter;
}

/*****************************************************************
** Define a callback to process MineEventReportInter interactions.
******************************************************************/
void MineEventReportInterCB(DtOCEAN2020FOMMineEventReportInter* inter, void* /*usr*/)
{
	std::cout << "Received MineEventReportInter Interaction.\n" << std::endl;
	*inter;
}

int main(int argc, char** argv)
{
	DtINIT_MINIDUMPER("Listen");

	try
	{
		DtVrlApplicationInitializer initializer(argc, argv, "VR-Link Listen");
		initializer.parseCmdLine();

		// Set the default FED File, executable, and version
		initializer.setFedFileName(DtDefaultRpr2Fom);
		initializer.setExecName("OCEAN2020");
		initializer.setRprFomVersion(2.0);
		initializer.setRprFomRevision(3);

		//Add custom FOM modules
		//----------------------
#ifdef DtHLA_1516_EVOLVED
		std::vector<DtString> fomModules;
		fomModules.push_back("OCEAN2020FOM_COMMCE_v1.0.xml");
		fomModules.push_back("OCEAN2020FOM_Environmental_v1.0.xml");
		fomModules.push_back("OCEAN2020FOM_SISO-STD-001.1-2015.xml");
		initializer.setFomModules(fomModules);
#endif

#ifdef NDEBUG
		initializer.setFomMapperLibName("libOCEAN2020FOM1516e_64");
#else
		initializer.setFomMapperLibName("libOCEAN2020FOM1516e_64d");
#endif

		DtExerciseConn::InitializationStatus status = DtExerciseConn::DtINIT_SUCCESS;
		DtExerciseConn* exConn = NULL;
		try
		{
			exConn = new DtExerciseConn(initializer, &status);
		}
		catch (DtVlRtiMismatchException)
		{
			std::cerr << "Mismatching RTI compiler Version. Please reconfigure your environment" << std::endl;
			return -1;
		}
		if (status != 0)
		{
			std::cout << "Error creating exercise connection." << std::endl;
			return -1;
		}

		/***************************************************
		** Create an object to manage Reflected TxRxLink_obj
		****************************************************/
		DtReflectedOCEAN2020FOMTxRxLink_objList* refList_TxRxLink_obj;
		refList_TxRxLink_obj = new DtReflectedOCEAN2020FOMTxRxLink_objList(exConn);
		refList_TxRxLink_obj->addTxRxLink_objAdditionCallback(discoverObject_TxRxLink_obj, 0);
		refList_TxRxLink_obj->addTxRxLink_objRemovalCallback(removeObject_TxRxLink_obj, 0);

		/**************************************************************
		** Register a callback to handle TxRx_Link_OnReq interactions.
		****************************************************************/
		DtOCEAN2020FOMTxRx_Link_OnReqInter::addCallback(exConn, TxRx_Link_OnReqInterCB, NULL);

		/**************************************************************
		** Register a callback to handle TxRx_Link_OffReq interactions.
		****************************************************************/
		DtOCEAN2020FOMTxRx_Link_OffReqInter::addCallback(exConn, TxRx_Link_OffReqInterCB, NULL);


		/*****************************************************
		** Create an object to manage Reflected VS_Environment
		******************************************************/
		DtReflectedOCEAN2020FOMVS_EnvironmentList* refList_VS_Environment;
		refList_VS_Environment = new DtReflectedOCEAN2020FOMVS_EnvironmentList(exConn);

		/***************************************************************
		** Create an object to manage Reflected VS_Environment.AirColumn
		****************************************************************/
		DtReflectedOCEAN2020FOMAirColumnList* refList_VS_EnvironmentAirColumn;
		refList_VS_EnvironmentAirColumn = new DtReflectedOCEAN2020FOMAirColumnList(exConn);

		/***************************************************************
		** Create an object to manage Reflected VS_Environment.Bathymetry
		****************************************************************/
		DtReflectedOCEAN2020FOMBathymetryList* refList_VS_EnvironmentBathymetry;
		refList_VS_EnvironmentBathymetry = new DtReflectedOCEAN2020FOMBathymetryList(exConn);

		/**********************************************************
		** Create an object to manage Reflected VS_Environment.Land
		***********************************************************/
		DtReflectedOCEAN2020FOMLandList* refList_VS_EnvironmentLand;
		refList_VS_EnvironmentLand = new DtReflectedOCEAN2020FOMLandList(exConn);

		/************************************************************
		** Create an object to manage Reflected VS_Environment.MosaicSeabed
		*************************************************************/
		DtReflectedOCEAN2020FOMMosaicSeabedList* refList_VS_EnvironmentMosaicSeabed;
		refList_VS_EnvironmentMosaicSeabed = new DtReflectedOCEAN2020FOMMosaicSeabedList(exConn);

		/******************************************************************
		** Create an object to manage Reflected VS_Environment.WaterColumn
		*******************************************************************/
		DtReflectedOCEAN2020FOMWaterColumnList* refList_VS_EnvironmentWaterColumn;
		refList_VS_EnvironmentWaterColumn = new DtReflectedOCEAN2020FOMWaterColumnList(exConn);

		/******************************************************************
		** Create an object to manage Reflected VS_Environment.WaterSurface
		*******************************************************************/
		DtReflectedOCEAN2020FOMWaterSurfaceList* refList_VS_EnvironmentWaterSurface;
		refList_VS_EnvironmentWaterSurface = new DtReflectedOCEAN2020FOMWaterSurfaceList(exConn);

		/*****************************************************************************************
		** Create an object to manage Reflected Entity list for Submersible / Surface / Area object
		******************************************************************************************/
		DtReflectedEntityList* refList_EntityData;
		refList_EntityData = new DtReflectedEntityList(exConn);

		/*******************************************************
		** Create an object to manage EmbeddedSystem.AIS object
		*********************************************************/
		DtReflectedOCEAN2020FOMAISList* refListOCEAN2020FOMAIS;
		refListOCEAN2020FOMAIS = new DtReflectedOCEAN2020FOMAISList(exConn);

		/********************************************************************é************************
		** Create an object to manage EmbeddedSystem.RadioTransmitter.OCEAN2020RadioTransmitter object
		**********************************************************************************************/
		//DtReflectedRadioTransmitterList* refList_OCEAN2020RadioTransmitter;
		//refList_OCEAN2020RadioTransmitter = new DtReflectedRadioTransmitterList(exConn);

		DtReflectedOCEAN2020FOMRadioTransmitterList* refList_OCEAN2020RadioTransmitter;
		refList_OCEAN2020RadioTransmitter = new DtReflectedOCEAN2020FOMRadioTransmitterList(exConn);

		/*********************************************************************************************
		** Create an object to manage EmbeddedSystem.RadioReceiver.OCEAN2020RadioReceiver object
		**********************************************************************************************/
		DtReflectedOCEAN2020FOMRadioReceiverList* refList_OCEAN2020RadioReceiver;
		refList_OCEAN2020RadioReceiver = new DtReflectedOCEAN2020FOMRadioReceiverList(exConn);

		/**************************************************************
		** Register a callback to handle MineEventReportInter interactions.
		****************************************************************/
		DtOCEAN2020FOMMineEventReportInter::addCallback(exConn, MineEventReportInterCB, NULL);


		/**********************************************************************
		** Register a callback to handle DtStartResumeInteraction interactions.
		***********************************************************************/
		DtStartResumeInteraction::addCallback(exConn, StartResumeCb, NULL);

		// Initialize VR-Link time.
		DtClock* clock = exConn->clock();

		//Shutdown handler in order to smoothly end if the HLA exercise shuts down
		int forever = 1;
#ifdef DtHLA
		exConn->addRtiErrorCb(&DtRtiShutdownHandler, &forever);
#endif

		int sendCounter = 0;

		int enviromental_send_counter = 0;
		int current_elapsedRealTime = 0;
		int previous_elapsedRealTime = -1;


		HANDLE listen_semaphore;
		HANDLE talk_semaphore;
		DWORD talk_dwRead;
		DWORD listen_dwRead;

		bool semaphore_created = false;

		while (forever)
		{
			// Check if user hit 'q' to quit.
			if (keybrdTick() == -1)
				break;

			//if ((++sendCounter % 25) == 0)
			current_elapsedRealTime = (int)clock->elapsedRealTime();
			if (current_elapsedRealTime % 5 == 0)
			{
				if (current_elapsedRealTime != previous_elapsedRealTime) {
					std::cout << "CLOCK: elapsed time " << (int)clock->elapsedRealTime() << std::endl;
				}
				previous_elapsedRealTime = current_elapsedRealTime;
				/***********************************************************************
				** Find the first entity in the reflected VS_Environment.AirColumn list
				************************************************************************/
				DtReflectedOCEAN2020FOMVS_Environment *first_VS_Environment = refList_VS_Environment->first();

				DtReflectedOCEAN2020FOMAirColumn * first_VS_EnvironmentAirColumn = refList_VS_EnvironmentAirColumn->first();
				DtReflectedOCEAN2020FOMLand * first_VS_EnvironmentLand = refList_VS_EnvironmentLand->first();
				DtReflectedOCEAN2020FOMWaterColumn * first_VS_EnvironmentWaterColumn = refList_VS_EnvironmentWaterColumn->first();
				DtReflectedOCEAN2020FOMWaterSurface * first_VS_EnvironmentWaterSurface = refList_VS_EnvironmentWaterSurface->first();

				DtReflectedOCEAN2020FOMBathymetry * first_VS_EnvironmentBathymetry = refList_VS_EnvironmentBathymetry->first();
				DtReflectedOCEAN2020FOMMosaicSeabed * first_VS_EnvironmentMosaicSeabed = refList_VS_EnvironmentMosaicSeabed->first();
				for (DtReflectedEntity* entity = refList_EntityData->first(); entity; entity = entity->next()) {}
				DtReflectedOCEAN2020FOMAIS* first_OCEAN2020FOMAIS = refListOCEAN2020FOMAIS->first();
				DtReflectedOCEAN2020FOMRadioTransmitter * first_OCEAN2020RadioTransmitter = refList_OCEAN2020RadioTransmitter->first();
				DtReflectedOCEAN2020FOMRadioReceiver* first_OCEAN2020RadioReceiver = refList_OCEAN2020RadioReceiver->first();

				if (first_VS_EnvironmentAirColumn || first_VS_EnvironmentLand || first_VS_EnvironmentWaterColumn || first_VS_EnvironmentWaterSurface)
				{
					if (!semaphore_created) {
						listen_semaphore = OpenSemaphore(
							SEMAPHORE_ALL_ACCESS,
							NULL,
							"listen_sem"
						);
						if (listen_semaphore == NULL) {
							std::cout << "ERROR while opening semaphore" << std::endl;
							exit(-1);
						}

						talk_semaphore = OpenSemaphore(
							SEMAPHORE_ALL_ACCESS,
							NULL,
							"talk_sem"
						);
						if (talk_semaphore == NULL) {
							std::cout << "ERROR while opening semaphore" << std::endl;
							exit(-1);
						}
						semaphore_created = true;
					}

					listen_dwRead = WaitForSingleObject(listen_semaphore, INFINITE);
					if (first_VS_EnvironmentAirColumn)
					{
						// Grab its state repository
						DtOCEAN2020FOMAirColumnStateRepository *first_VS_EnvironmentAirColumnSR = first_VS_EnvironmentAirColumn->airColumnStateRep();
						// Print data
						printf("----------------- GET: VS_Environment.AirColumn data -----------------\n");
						first_VS_EnvironmentAirColumnSR->printData();

						std::ofstream AirColumn("Data_AirColumn.txt");
						if (!AirColumn) { std::cerr << "ERROR creating AirColumn file" << std::endl; }
						first_VS_EnvironmentAirColumnSR->printDataToStream(AirColumn);
						enviromental_send_counter++;
					}

					/****************************************************************
					** Find the first entity in the reflected VS_Environment.Land list
					*****************************************************************/
					if (first_VS_EnvironmentLand)
					{
						// Grab its state repository
						DtOCEAN2020FOMLandStateRepository *first_VS_EnvironmentLandSR = first_VS_EnvironmentLand->landStateRep();
						// Print data
						printf("----------------- GET: VS_Environment.Land data ----------------------\n");
						first_VS_EnvironmentLandSR->printData();

						std::ofstream Land("Data_Land.txt");
						if (!Land) { std::cerr << "ERROR creating Land file" << std::endl; }
						first_VS_EnvironmentLandSR->printDataToStream(Land);
						enviromental_send_counter++;
					}

					/************************************************************************
					** Find the first entity in the reflected VS_Environment.WaterColumn list
					*************************************************************************/
					if (first_VS_EnvironmentWaterColumn)
					{
						// Grab its state repository
						DtOCEAN2020FOMWaterColumnStateRepository *first_VS_EnvironmentWaterColumnSR = first_VS_EnvironmentWaterColumn->waterColumnStateRep();
						// Print data
						printf("----------------- GET: VS_Environment.WaterColumn data ----------------\n");
						first_VS_EnvironmentWaterColumnSR->printData();

						std::ofstream WaterColumn("Data_WaterColumn.txt");
						if (!WaterColumn) { std::cerr << "ERROR creating WaterColumn file" << std::endl; }
						first_VS_EnvironmentWaterColumnSR->printDataToStream(WaterColumn);
						enviromental_send_counter++;
					}

					/********************************************************************
					** Find the first entity in the reflected VS_Environment.WaterSurface list
					*********************************************************************/
					if (first_VS_EnvironmentWaterSurface)
					{
						// Grab its state repository
						DtOCEAN2020FOMWaterSurfaceStateRepository *first_VS_EnvironmentWaterSurfaceSR = first_VS_EnvironmentWaterSurface->waterSurfaceStateRep();
						// Print data
						printf("----------------- GET: VS_Environment.WaterSurface data ----------------\n");
						first_VS_EnvironmentWaterSurfaceSR->printData();

						std::ofstream WaterSurface("Data_WaterSurface.txt");
						if (!WaterSurface) { std::cerr << "ERROR creating WaterSurface file" << std::endl; }
						first_VS_EnvironmentWaterSurfaceSR->printDataToStream(WaterSurface);
						enviromental_send_counter++;
					}

					ReleaseSemaphore(listen_semaphore, 1, NULL);
					talk_dwRead = WaitForSingleObject(talk_semaphore, INFINITE);

					printf("\n");
				}
			}

			// Tell VR-Link the current value of simulation time.
			clock->setSimTime(clock->elapsedRealTime());

			// Process any incoming messages.
			exConn->drainInput();

			//// Sleep till next iteration.
			//DtSleep(0.2);
		}
		delete exConn;
	}
	DtCATCH_AND_WARN(std::cout);
	int stop;
	std::cin >> stop;
	return 0;
}

int keybrdTick()
{
	char *keyPtr = DtPollBlockingInputLine();
	if (keyPtr && (*keyPtr == 'q' || *keyPtr == 'Q'))
		return -1;
	else
		return 0;
}