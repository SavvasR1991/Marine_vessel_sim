#include "Simulator.h"

/*************************************** SIMULATOR.CPP *************************************************/
// [1] Simulator() constructor,						    constructor
// [2] ~Simulator()								        destructor
// [3] void start_simulator(int, char*, int, int,int)   set total number of nodes and types
// [4] void start_simulator(int argc, char* argv[])		START SIMULATION MAIN FUNCTION
// [5] void setUpTeam();							    create ship team
// [6] void cleanUp();									clean up, delete simulation
// [7] void listen();									get enviromentals from listen
// [8] void talk();										move team and publish
// [9] void generateEvent(DtTime dt, Dt3dPoint);	    generate event, ex unknown node movement
// [10] void setUpConnection(int, char *argv[])		    setup connection 
// [11] void start_simulation();					    start simulation
/*************************************** SIMULATOR.CPP *************************************************/

/******************************************************************************/
/*************************** TxRxLink FUNCTIONS *******************************/
/******************************************************************************/
void StartResumeCb(DtStartResumeInteraction* StartResumeInt, void* /*usr*/)
{
	std::cout << "Start Resume Interaction Interaction from " << std::endl;
	StartResumeInt->printData();
}
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
void TxRx_Link_OnReqInterCB(DtOCEAN2020FOMTxRx_Link_OnReqInter* inter, void* /*usr*/)
{
	std::cout << "Received TxRx_Link_OnReqInter Interaction." << std::endl;
	*inter;
}
void TxRx_Link_OffReqInterCB(DtOCEAN2020FOMTxRx_Link_OffReqInter* inter, void* /*usr*/)
{
	std::cout << "Received TxRx_Link_OffReqInter Interaction." << std::endl;
	*inter;
}
void MineEventReportInterCB(DtOCEAN2020FOMMineEventReportInter* inter, void* /*usr*/)
{
	std::cout << "Received MineEventReportInter Interaction.\n" << std::endl;
	*inter;
}

/******************************************************************************/
/********************** CONSTRUCTOR/ DESTRUCTOR *******************************/
/******************************************************************************/
//[1]
/***************** Simulator ********************/
Simulator::Simulator() { printf("Simulator: created\n");}

//[2]
/***************** ~Simulator *******************/
Simulator::~Simulator(){ printf("Simulator: end\n");}

/******************************************************************************/
/*************************** SIMULATOR FUNCTIONS ******************************/
/******************************************************************************/

//[3]
void Simulator::start_simulator(int argc, char* argv[])
{
	std::string simulation_num = "Simulation_1";
	USER_INIT_DATA user;

	std::cout << "Simulator: Start .." << std::endl;
	double commnents_js = json_reader_data(simulation_num, "Enable_comments");
	double logs_js = json_reader_data(simulation_num, "Enable_Logs");

	char commnents;
	if (commnents_js == 0) {
		commnents = 'n';
		print_color_message("- No comments enabled\n", 14);
	}
	else {
		commnents = 'y';
		print_color_message("- Comments enabled\n", 10);
	}

	char logs;
	if (logs_js == 0) {
		logs = 'n';
		print_color_message("- No Logs enabled\n", 14);
	}
	else {
		logs = 'y';
		print_color_message("- Logs enabled\n", 10);
	}

	user.uxv_num = json_reader_data(simulation_num, "Number_Vessel");
	user.uxv_subwater = json_reader_data(simulation_num, "Number_under_water_vessels");
	user.uxv_surface = json_reader_data(simulation_num, "Number_Surface_water_vessels");

	user.refLatitude = json_reader_data(simulation_num, "Ship_center_x");
	user.refLongitude = json_reader_data(simulation_num, "Ship_center_y");
	user.refHeight = json_reader_data(simulation_num, "Ship_center_z");
	user.ship_range = json_reader_data(simulation_num, "Ship_Range_meters");
	user.ship_id = json_reader_data(simulation_num, "Ship_Id");

	user.uxv_surface_length = json_reader_data(simulation_num, "Vessel_surface_X_Axis_dims_meters");
	user.uxv_surface_width = json_reader_data(simulation_num, "Vessel_surface_Y_Axis_dims_meters");
	user.uxv_surface_heigth = json_reader_data(simulation_num, "Vessel_surface_Z_Axis_dims_meters");
	user.uxv_surface_sensor_range = json_reader_data(simulation_num, "Vessel_surface_Range_radar_meters");
	user.angle_surface_speed = json_reader_data(simulation_num, "Vessel_surface_Speed_angular_degrees_per_sec");
	user.ACCELERATION_surface = json_reader_data(simulation_num, "Vessel_surface_Acceleration_MAX_met_per_sec_2");
	user.DECELERATION_surface = json_reader_data(simulation_num, "Vessel_surface_Decelaration_MAX_met_per_sec_2");
	user.MAXIMUM_SPEED_surface = json_reader_data(simulation_num, "Vessel_surface_Speed_MAX_met_per_sec");
	user.uxv_surface_mass = json_reader_data(simulation_num, "Vessel_surface_mass");

	user.uxv_subwater_length = json_reader_data(simulation_num, "Vessel_subwater_X_Axis_dims_meters");
	user.uxv_subwater_width = json_reader_data(simulation_num, "Vessel_subwater_Y_Axis_dims_meters");
	user.uxv_subwater_heigth = json_reader_data(simulation_num, "Vessel_subwater_Z_Axis_dims_meters");
	user.uxv_subwater_sensor_range = json_reader_data(simulation_num, "Vessel_subwater_Range_radar_meters");
	user.angle_subwater_speed = json_reader_data(simulation_num, "Vessel_subwater_Speed_angular_degrees_per_sec");
	user.ACCELERATION_subwater = json_reader_data(simulation_num, "Vessel_subwater_Acceleration_MAX_met_per_sec_2");
	user.DECELERATION_subwater = json_reader_data(simulation_num, "Vessel_subwater_Decelaration_MAX_met_per_sec_2");
	user.MAXIMUM_SPEED_subwater = json_reader_data(simulation_num, "Vessel_subwater_Speed_MAX_met_per_sec");
	user.uxv_subwater_mass = json_reader_data(simulation_num, "Vessel_subwater_mass");

	user.MAXIMUM_REVERSE_SPEED = json_reader_data(simulation_num, "Vessel_Reverse_Speed_MAX_met_per_sec");

	set_up_simulator(argc, argv, user, commnents, logs);
}


void Simulator::set_up_simulator(int argc, char* argv[],USER_INIT_DATA user,char commnents, char logs) {

	//***************** Initialize simulator attributes *****************//

	//************ Vessels quandity ************//
	this->uxv_team_init_data.uxv_num = user.uxv_num;						//Total number of vessels, given by user																												
	this->uxv_team_init_data.uxv_subwater = user.uxv_subwater;			//Total number of subwater vessels, given by user
	this->uxv_team_init_data.uxv_surface = user.uxv_surface;				//Total number of surface vessels, given by user

	//************ Elements dimensions *********//
	this->uxv_team_init_data.uxv_length_sur = user.uxv_surface_length;				//Initial Length
	this->uxv_team_init_data.uxv_width_sur = user.uxv_surface_width;					//Initial Width
	this->uxv_team_init_data.uxv_heigth_sur = user.uxv_surface_heigth;				//Initial Height

	this->uxv_team_init_data.uxv_length_sub = user.uxv_subwater_length;				//Initial Length
	this->uxv_team_init_data.uxv_width_sub = user.uxv_subwater_width;					//Initial Width
	this->uxv_team_init_data.uxv_heigth_sub = user.uxv_subwater_heigth;				//Initial Height

	this->uxv_team_init_data.ship_range = user.ship_range;				//ship range

	//************ Reference coordinates *******//
	this->uxv_team_init_data.refLatitude = user.refLatitude;				//Initial Latitude
	this->uxv_team_init_data.refLongitude = user.refLongitude;			//Initial Longitude
	this->uxv_team_init_data.refHeight = user.refHeight;					//Initial Longitude

	//************ Vessel radar ranges ********//
	this->uxv_team_init_data.uxv_sensor_range_sub = user.uxv_subwater_sensor_range;				// sensors range
	this->uxv_team_init_data.uxv_sensor_range_sur = user.uxv_surface_sensor_range;				// sensors range

	this->uxv_team_init_data.uxv_sensor_depth_range = user.uxv_sensor_depth_range;	// sensors range

	//************ Vessel speeds *************//
	this->uxv_team_init_data.angle_speed_sur = user.angle_surface_speed;						//ship range
	this->uxv_team_init_data.ACCELERATION_sur = user.ACCELERATION_surface;					//sensor speed
	this->uxv_team_init_data.MAXIMUM_SPEED_sur =user.MAXIMUM_SPEED_surface;					//sensor speed
	this->uxv_team_init_data.DECELERATION_sur = user.DECELERATION_surface;					//sensor speed
	this->uxv_team_init_data.uxv_subwater_mass = user.uxv_subwater_mass;

	this->uxv_team_init_data.angle_speed_sub = user.angle_subwater_speed;						//ship range
	this->uxv_team_init_data.ACCELERATION_sub = user.ACCELERATION_subwater;					//sensor speed
	this->uxv_team_init_data.MAXIMUM_SPEED_sub = user.MAXIMUM_SPEED_subwater;					//sensor speed
	this->uxv_team_init_data.DECELERATION_sub = user.DECELERATION_subwater;
	this->uxv_team_init_data.uxv_surface_mass = user.uxv_surface_mass;

	this->uxv_team_init_data.MAXIMUM_REVERSE_SPEED = user.MAXIMUM_REVERSE_SPEED;	//sensor speed

	this->cycles = 0;
	this->commnents = commnents;
	this->logs = logs;
	this->start(argc, argv);
	this->cleanUp();

}


//[4]
/************ start_simulation ******************/
void Simulator::start(int argc, char* argv[])
{
	DtINIT_MINIDUMPER("Talk");

	print_color_message("----------------------------- INITIALIZATION  -------------------------------\n", 1);
	this->b_changeval = false;this->b_once = false;

	DtVrlApplicationInitializer initializer_listen(argc, argv, "VR-Link Listen");
	initializer_listen.parseCmdLine();

	DtVrlApplicationInitializer initializer(argc, argv, "VR-Link Talk");
	initializer.parseCmdLine();

	// Set the default FED File, executable, and version listen
	initializer_listen.setFedFileName(DtDefaultRpr2Fom);
	initializer_listen.setExecName("OCEAN2020");
	initializer_listen.setRprFomVersion(2.0);
	initializer_listen.setRprFomRevision(3);

	// Set the default FED File, executable, and version talk
	initializer.setFedFileName(DtDefaultRpr2Fom);
	initializer.setExecName("OCEAN2020");
	initializer.setRprFomVersion(2.0);
	initializer.setRprFomRevision(3);

	//Add custom FOM modules
#ifdef DtHLA_1516_EVOLVED
	std::vector<DtString> fomModules;
	fomModules.push_back("OCEAN2020FOM_COMMCE_v1.0.xml");
	fomModules.push_back("OCEAN2020FOM_Environmental_v1.0.xml");
	fomModules.push_back("OCEAN2020FOM_SISO-STD-001.1-2015.xml");

	initializer_listen.setFomModules(fomModules);
	initializer.setFomModules(fomModules);
#endif

#ifdef NDEBUG
	initializer_listen.setFomMapperLibName("libOCEAN2020FOM1516e_64");
	initializer.setFomMapperLibName("libOCEAN2020FOM1516e_64");
#else
	initializer_listen.setFomMapperLibName("libOCEAN2020FOM1516e_64d");
	initializer.setFomMapperLibName("libOCEAN2020FOM1516e_64d");
#endif
	try
	{
		DtExerciseConn::InitializationStatus status = DtExerciseConn::DtINIT_SUCCESS;
		print_color_message("\n-------------------------- CONNECTION CREATION LISTEN ------------------- \n",1);
		this->exConn_listen = new DtExerciseConn(initializer_listen, &status);
		print_color_message("\n-------------------------- CONNECTION CREATION TALK --------------------- \n",1);
		this->exConn = new DtExerciseConn(initializer, &status);

		if (status != 0)
		{
			print_color_message("Error creating exercise connection.\n", 12);
			system("pause");
			exit(-1);
		}

	}
	catch (DtVlRtiMismatchException)
	{
		print_color_message("Mismatching RTI compiler Version. Please reconfigure your environmen\n", 12);
		system("pause");
		exit(-1);
	}
	
	/***************************************************
	** Create an object to manage Reflected TxRxLink_obj
	****************************************************/
	DtReflectedOCEAN2020FOMTxRxLink_objList* refList_TxRxLink_obj;
	refList_TxRxLink_obj = new DtReflectedOCEAN2020FOMTxRxLink_objList(this->exConn_listen);
	refList_TxRxLink_obj->addTxRxLink_objAdditionCallback(discoverObject_TxRxLink_obj, 0);
	refList_TxRxLink_obj->addTxRxLink_objRemovalCallback(removeObject_TxRxLink_obj, 0);

	/**************************************************************
	** Register a callback to handle TxRx_Link_OnReq interactions.
	****************************************************************/
	DtOCEAN2020FOMTxRx_Link_OnReqInter::addCallback(this->exConn_listen, TxRx_Link_OnReqInterCB, NULL);

	/**************************************************************
	** Register a callback to handle TxRx_Link_OffReq interactions.
	****************************************************************/
	DtOCEAN2020FOMTxRx_Link_OffReqInter::addCallback(this->exConn_listen, TxRx_Link_OffReqInterCB, NULL);

	// Initialize VR-Link time.
	DtClock* clock = this->exConn->clock();

	//Shutdown handler in order to smoothly end if the HLA exercise shuts down
	int forever = 1;
#ifdef DtHLA
	this->exConn_listen->addRtiErrorCb(&DtRtiShutdownHandler, &forever);
	this->exConn->addRtiErrorCb(&DtRtiShutdownHandler, &forever);
#endif

	print_color_message("\n-------------------------- FOMS SET UP ----------------------------------\n",1);
	/******************** Class object TxRxLink_obj creation *****************************/
	this->TxRxLink_objPub = new DtOCEAN2020FOMTxRxLink_objPublisher(this->exConn);
	this->TxRx_Link_OnReqInter.setTx_HostObjectID("Tx_HostObjectID");
	this->TxRx_Link_OnReqInter.setRx_HostObjectID("Rx_HostObjectID");
	this->TxRx_Link_OnReqInter.setFrequencyHopping(654845615);
	this->TxRx_Link_OffReqinter.setTx_HostObjectID("Tx_HostObjectID");
	this->TxRx_Link_OffReqinter.setRx_HostObjectID("Rx_HostObjectID");

	//********************** Create FOMS to listen from the connection *******************/
	this->refList_VS_Environment = new DtReflectedOCEAN2020FOMVS_EnvironmentList(this->exConn_listen);
	this->refList_VS_EnvironmentAirColumn = new DtReflectedOCEAN2020FOMAirColumnList(this->exConn_listen);
	this->refList_VS_EnvironmentLand = new DtReflectedOCEAN2020FOMLandList(this->exConn_listen);
	this->refList_VS_EnvironmentWaterColumn = new DtReflectedOCEAN2020FOMWaterColumnList(this->exConn_listen);
	this->refList_VS_EnvironmentWaterSurface = new DtReflectedOCEAN2020FOMWaterSurfaceList(this->exConn_listen);

	//********************** Create FOMS to talk to the connection **********************/
	this->Ocean2020radioTransmitterPub = new DtRadioTransmitterPublisher(this->exConn);
	this->Ocean2020radioTransmitterSR = (DtOCEAN2020FOMRadioTransmitterStateRepository*)Ocean2020radioTransmitterPub->tsr();
	this->Ocean2020radioTransmitterSR->setEntityId(DtEntityIdentifier(1, 304, 13));
	this->Ocean2020radioTransmitterSR->setHostId("Ocean2020RdTX1-104-13");

	print_color_message("\n-------------------------- TEAM CREATION -------------------------------- \n",1);
	setUpTeam();

	print_color_message("\n-------------------------- ENVIROMENTALS CREATION ----------------------- \n",1);
	this->enviromental_elements = new Enviromental_Elements();

	print_color_message("\n-------------------------- EVENT RECEIVER CREATION ---------------------- \n",1);
	this->team_event = new EVENT();
	this->team_event->setEvent(EVENT_MESSAGE::NO_MESSAGE);

	print_color_message("\n-------------------------- START SIMULATION ----------------------------- \n",10);
	print_color_message("-------------------------- Press q + enter to stop simulation\n", 13);

	system("pause");

	DtU8 valU8;DtFloat32 val_f;DtTime dt = 0.05;DtTime simTime = 0;int sendCounter = 0;
	clock->init();

	try
	{
		while (forever)
		{
			// Check if user hit 'q' to quit.
			if (keybrdTick() == -1)
				break;

			// Tell VR-Link the current value of simulation time.
			clock->setSimTime(simTime);

			// Process any incoming messages.
			this->exConn->drainInput();
			this->exConn_listen->drainInput();


			simTime += dt;
			if ((int)clock->elapsedRealTime() % 2 == 0)
			{
				/***************** LISTEN *************************/
				this->listen();
				
				/***************** TALK ***************************/
				this->talk(dt, simTime);
				this->cycles = this->cycles + 1;

			}
			//Update boolean variable to alternate value to be applied
			this->b_changeval = !this->b_changeval;

			//freeze boolean once
			if (!this->b_once)
			{
				this->b_once = true;
			}
			// Wait till real time equals simulation time of next step.
			DtSleep(simTime - clock->elapsedRealTime());
			
		}
	}
	DtCATCH_AND_WARN(std::cout);
}

//[5]
/****************** setUpTeam ********************/
void Simulator::setUpTeam()
{
	this->uxv_team = new UxV_Team(this->uxv_team_init_data, this->exConn, this->commnents, this->logs);	//Create the vessel's team
}

//[6]
/****************** cleanUp **********************/
void Simulator::cleanUp()
{
	print_color_message("\n-------------------- Simulator: clean up --------------------\n",11);

	print_color_message("\n------------ Delete Enviromental receivers ---------\n",3);
	delete this->enviromental_elements;

	print_color_message("\n------------ Delete Event receiver -----------------\n",3);
	delete this->team_event;

	print_color_message("\n------------ Delete UxV Team -----------------------\n",3);
	delete this->uxv_team;

	print_color_message("\n------------ Delete Enviromental FOMS --------------\n",3);
	delete this->TxRxLink_objPub;
	delete this->refList_VS_EnvironmentAirColumn;
	delete this->refList_VS_EnvironmentLand;
	delete this->refList_VS_EnvironmentWaterColumn;
	delete this->refList_VS_EnvironmentWaterSurface;
	delete this->refList_VS_Environment;

	print_color_message("\n------------ Delete Publishers --------------------\n",3);
	delete this->Ocean2020radioTransmitterPub;

	print_color_message("\n------------ Delete connections -------------------\n",3);
	delete this->exConn;
	delete this->exConn_listen;
}


/******************************************************************************/
/************************* LISTEN INCOMING MESSAGES ***************************/
/******************************************************************************/

//[7]
/****************** LISTEN **********************/
void Simulator::listen() {
	print_color_message("\n---------------------------- LISTEN -----------------------------------\n",9, this->commnents);
	if (!this->enviromental_elements->set_enviromental_elements(
		refList_VS_EnvironmentAirColumn, refList_VS_EnvironmentLand, refList_VS_EnvironmentWaterSurface, refList_VS_EnvironmentWaterColumn)) {
		print_color_message("----------------- NO INCOMING ENVIROMENTAL MESSAGES\n", 14,this->commnents);
	}
	else {
		print_color_message("----------------- ENVIROMENTAL UPDATED\n", 10);
	}

	this->evaluateEvent();

	if (this->team_event->getEvent() == EVENT_MESSAGE::NO_MESSAGE) {
		print_color_message("----------------- NO INCOMING EVENT MESSAGES\n",14, this->commnents);
	}
}

/******************************************************************************/
/*************************** PUBLISH MESSAGES *********************************/
/******************************************************************************/

//[8]
/******************* TALK ***********************/
void Simulator::talk(DtTime dt, DtTime simTime) {
	Dt3dPoint event;
	print_color_message("\n---------------------------- TALK -------------------------------------\n",9,this->commnents);
	/******** START EVENTS ************/

	moveVessels(dt,  simTime);
	/**** SEND RADIO TRANSMITTER ******/
	sendRadioTransmitter(simTime);
}

//[9]
/******************* generateEvent **************/
void Simulator::moveVessels(DtTime dt, DtTime simTime)	//Incoming event. The vessels will execute relevant movements
{
	this->uxv_team->start_team_cycle(dt, this->team_event, simTime,this->enviromental_elements);
}

//[10]
/******************* evaluateEvent **************/
void Simulator::evaluateEvent() //Evaluate the income event and execute the relevant movements
{
	//TODO EVENT INCOME////////////////////////////////////////////////////////////////

		// LISTER - GET EVENT
		/*if (1 == 1) {
			this->team_event->event_message == EVENT_MESSAGE::TARGET_INCOMING;
			this->team_event->target_refLatitude == 0;
			this->team_event->target_refLongitude == 0;
		}
		else if (1 == 3) {
			this->team_event->event_message == EVENT_MESSAGE::TASK_EXECUTION;
			this->team_event->job == JOB::PATROLING;
			this->team_event->job == JOB::RESET;

		}
		else {
			std::cout << "----------------- MESSAGE CAN NOT BE IMPLEMENTED. NO KNOWED ACTION." << std::endl;
			this->team_event->event_message == EVENT_MESSAGE::NO_MESSAGE;
		}*/
		//////////////////////////////////////////////////////////////////////////////
	if (this->cycles == -450) {
		this->team_event->setEvent(EVENT_MESSAGE::TASK_EXECUTION);
		this->team_event->setJob(JOB::RESET);
		print_color_message("-----------------\n", 15);
		print_color_message("----------------- INCOMING EVENT\n", 12);
		print_color_message("--------------------- ** RESET TEAM VESSELS **\n", 12);
		print_color_message("-----------------\n", 15);

	}
	else {
		this->team_event->clear_event_receiver();

	}
}

//[11]
/************** sendRadioTransmitter ************/
void Simulator::sendRadioTransmitter(DtTime simTime)		//Publish radio transmitter data
{

	/*******************************************************************************
	* Class object EmbeddedSystem.RadioTransmitter.OCEAN2020RadioTransmitter updated
	********************************************************************************/
	DtFloat32 val_f;

	this->Ocean2020radioTransmitterSR->setTransmitterMaxGaindB(38.06f + 5 * sin(simTime));
	this->Ocean2020radioTransmitterSR->setTransmitterChannelBandwidthHz(38.06f + 5 * sin(simTime));
	if (this->b_changeval)
	{
		this->Ocean2020radioTransmitterSR->setTransmitterAntiJammingTechnique(DtAntiJammingTechniqueEnum::DtAntiJammingTechniqueEnum_Tech1);
		this->Ocean2020radioTransmitterSR->setTransmitterType(DtTxRxTypeEnum::DtTxRxTypeEnum_AMcomm);
	}
	else
	{
		this->Ocean2020radioTransmitterSR->setTransmitterAntiJammingTechnique(DtAntiJammingTechniqueEnum::DtAntiJammingTechniqueEnum_Tech2);
		this->Ocean2020radioTransmitterSR->setTransmitterType(DtTxRxTypeEnum::DtTxRxTypeEnum_CWradar);
	}

	DtOCEAN2020FOMTxHarmonicLeveldBArray  RadioTXHarArray;
	for (int i = 0; i < 4; ++i)
	{
		val_f = 8652544.21522f + 52563.654f * (i + cos(simTime));
		RadioTXHarArray.setTxHarmonicLeveldBArrayItem(i, val_f);
		printf("");
	}

	this->Ocean2020radioTransmitterSR->setTransmitterHarmonicLevelAboveFunddB(RadioTXHarArray);
	this->Ocean2020radioTransmitterSR->setTransmitterBroadbandNoisePowerDensity(87652544.21522f + 635463 * cos(simTime));
	DtOCEAN2020FOMTxSpuriousLeveldBArray RadioTXSpurArray;
	for (int i = 0; i < 2; ++i)
	{
		val_f = 1853594.21522 + 936463 * (i + cos(simTime));
		RadioTXSpurArray.setTxSpuriousLeveldBArrayItem(i, val_f);
	}
	this->Ocean2020radioTransmitterSR->setTransmitterSpuriousLevelAbovefunddB(RadioTXSpurArray);
	this->Ocean2020radioTransmitterSR->setOperatingFrequency(2936463 + (int)(635463 * sin(simTime)));
	this->Ocean2020radioTransmitterSR->setChannelBandwidth(87652544.21522f + 635463 * cos(simTime));

	this->Ocean2020radioTransmitterPub->tick();
	if (this->commnents == 'y') {
		print_color_message("----- Send radio transmitter\n", 10);
		std::cout << "----- Frequency :" << 2936463 + (int)(635463 * sin(simTime)) << std::endl;
		std::cout << "----- Bandwidth :" << 87652544.21522f + 635463 * cos(simTime) << std::endl << std::endl;
	}
	fflush(stdout);
}
