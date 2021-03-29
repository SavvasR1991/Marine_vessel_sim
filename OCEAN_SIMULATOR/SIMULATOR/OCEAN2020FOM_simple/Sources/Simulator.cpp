#include "Simulator.h"
#include "Simulator_helper_function.h"
#include "OCEAN2020FOMf18Init.h"

DtTime timeOutInterval = 12.0;     // seconds
DtTime timeThreshold = 5.0;     // seconds
double translationThreshold = 1.0; // meters
double rotationThreshold = DtDeg2Rad(3.0);  // radians

/*******************************************************************************/
/********************** SIMULATOR FUNCTIONS ************************************/
/*******************************************************************************/

//[1]
/***************** Simulator ********************/
Simulator::Simulator() { printf("Simulator: created\n");}

//[2]
/***************** ~Simulator *******************/
Simulator::~Simulator(){ printf("Simulator: end\n");}

//[3]
/************ start_simulation ******************/
void Simulator::start_simulator(int argc, char* argv[], std::string uni_tag, std::string scenario)
{
	this->university_tag = uni_tag;
	this->scenario = "Simulation_" + scenario;
	simulator_main(argc, argv);
}

//[4]
/************ start ******************************/
void Simulator::start(int argc, char* argv[], std::string simulation_num, std::string file)
{
	print_color_message("----------------------------- INITIALIZATION  ------------------------------------\n", 15);
	DtVrlApplicationInitializer initializer(argc, argv, this->university_tag );
	DtINIT_MINIDUMPER("NKUA");
	try
	{
		this->enviromental_elements = NULL;
		int pid = DtGetPid();
		DtString pidStr(pid);
		DtString appName = "NKUA " + pidStr;
		this->ref_lat = 55.704741; //55.704741, 14.813821
		this->ref_lon = 14.813821;
		DtF18Initializer initializer(argc, argv, this->university_tag, this->ref_lat, this->ref_lon);
		initializer.parseCmdLine();
		if (FILE *file = fopen("OCEAN2020f18.xml", "r"))
		{
			fclose(file);
			initializer.loadFile(DtString("OCEAN2020f18.xml"));
		}
		else
		{
			std::cout << "Error loading OCEAN2020f18.xml, file does not exist." << std::endl;
			system("pause");
			exit(-1);
		}

		initializer.setApplicationNumber(pid);
		DtString defaultF18Name(initializer.f18Name());
		defaultF18Name += " " + pidStr;
#ifdef DtHLA_1516_EVOLVED
		std::vector<DtString> fomModules;
		fomModules.push_back("OCEAN2020FOM_COMMCE_v1.1.xml");
		fomModules.push_back("OCEAN2020FOM_Environmental_v1.0.xml");
		fomModules.push_back("OCEAN2020FOM_SENSORS_v1.0.xml");
		fomModules.push_back("OCEAN2020FOM_SISO-STD-001.1-2015_v1.1.xml");
		initializer.setFomModules(fomModules);
#endif

#ifdef NDEBUG
		initializer.setFomMapperLibName("libOCEAN2020FOM1516e_64");
#else
		initializer.setFomMapperLibName("libOCEAN2020FOM1516e_64d");
#endif

#ifdef DtHLA
		// Appending PID to the object name
		DtString parsedF18Name(initializer.f18Name());
		parsedF18Name += " " + pidStr;
		initializer.setF18Name("HLA_NKUA_" + parsedF18Name);
#endif
		DtExerciseConn::InitializationStatus status = DtExerciseConn::DtINIT_SUCCESS;
		try
		{
			this->exConn = new DtExerciseConn(initializer, &status);
			this->exConn_listen = this->exConn;
		}
		catch (DtVlRtiMismatchException)
		{
			std::cerr << "Mismatching RTI compiler Version. Please reconfigure your environment" << std::endl;
			exit(-1);
		}
		if (status != 0)
		{
			std::cout << "Error creating exercise connection." << std::endl;
			exit(-1);
		}

		DtReflectedEntityList* rel = new DtReflectedEntityList(exConn);
		rel->setTimeoutInterval(timeOutInterval);
		DtEntityPublisher::setDfltRotationThreshold(rotationThreshold);
		DtEntityPublisher::setDfltTranslationThreshold(translationThreshold);
		DtEntityIdentifier entityId = DtEntityIdentifier(initializer.siteId(), initializer.applicationNumber(), initializer.entityNumber());
		DtEntityType type(initializer.entityTypeStr());
		this->ref_lat = initializer.refLatitude();//55.704741; //55.704741, 14.813821
		this->ref_lon = initializer.refLongitude(); //14.813821;
		this->ref_depth = this->uxv_team_init_data.refHeight;
		int forever = 1;
#ifdef DtHLA
		exConn->addRtiErrorCb(&DtRtiShutdownHandler, &forever);
#endif
		print_color_message("\n-------------------------- TEAM CREATION -------------------------------- \n", COLOR_TEXT::MAIN_TITLE_BLUE);
		this->uxv_team = new UxV_Team(this->uxv_team_init_data, this->exConn, this->commnents, this->commnents_basic, this->logs, this->logs_FOMS, this->logs_Kalman,this->logs_metrics, this->log_dir, this->log_dir_field, this->log_dir_timer, this->log_dir_Kalman_Filter,this->log_dir_metrics);
		print_color_message("\n-------------------------- ENVIROMENTALS CREATION ----------------------- \n", COLOR_TEXT::MAIN_TITLE_BLUE);
		this->refList_VS_Environment = new DtReflectedOCEAN2020FOMVS_EnvironmentList(this->exConn_listen);
		this->refList_VS_EnvironmentWaterColumn = new DtReflectedOCEAN2020FOMWaterColumnList(this->exConn_listen);
		this->refList_VS_EnvironmentWaterSurface = new DtReflectedOCEAN2020FOMWaterSurfaceList(this->exConn_listen);
		this->enviromental_elements = new Water_Waves_Kinematics(this->ref_lat,this->ref_lon,this->ref_depth);
		this->refList_VS_RadioReceiver= NULL;
		print_color_message("\n\n\n-------------------------- START SIMULATION ----------------------------- \n", COLOR_TEXT::MAIN_TITLE_GREEN);
		std::string segment;
		std::vector<std::string> seglist;
		std::stringstream test(this->simulation_description);
		while (std::getline(test, segment, '@'))
		{
			seglist.push_back(segment);
			print_color_message(segment + "\n", COLOR_TEXT::YELLOW_COLOR);

		}
		print_color_message("--> Press q + enter to stop simulation\n", COLOR_TEXT::YELLOW_COLOR);
		print_color_message("--> Press r + enter to reset simulation\n", COLOR_TEXT::YELLOW_COLOR);

		//********************** Initialize timers **********************/
		DtClock* clock = this->exConn->clock();
		DtTime dt = initializer.deltaTime(); simTime = 0;
		int key_pressed;
		bool reset;
		int timeser = 0;
		auto start = high_resolution_clock::now();

		while (timeser<1000) // to keep cfront quiet
		{
			clock->setSimTime(simTime);

			reset = false;
			key_pressed = keybrdTick();
			if (key_pressed == -1) { break; }
			else if (key_pressed == 1) { reset = true; }
			else { reset = false; }

			exConn->drainInput();

			this->listen(reset);

			this->talk(dt, simTime);

			DtTime sleeptime = (simTime += initializer.deltaTime()) - clock->elapsedRealTime();
			DtSleep(sleeptime); // returns immediately if negative
			timeser++;
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(stop - start);
		print_color_message("\n-------------------- Simulator: Store timers --------------------\n", 11);
		std::ofstream outfile;
		outfile.open(this->log_dir_timer, std::ios_base::app); // append instead of overwrite
		std::cout << "Simulator timers log saved to File " << this->log_dir_timer << std::endl<<std::endl;
		for (std::vector<std::string>::iterator it = seglist.begin(); it != seglist.end(); ++it) {
			outfile<<(*it) <<endl;
		}
		outfile << "\nSimulation time     : ";
		outfile << to_string(this->simTime);
		outfile << " ticks\n";
		outfile << "Simulation time	dev : ";
		outfile << to_string((double)duration.count()/ ((double)1000.0));
		outfile << " secs\n";
		outfile << "Simulation time	dev : ";
		outfile << to_string((int((double)duration.count() / ((double)1000.0) / 60) % 60)) << " min: "<< to_string(int((double)duration.count() / ((double)1000.0))%60) <<" sec: "<< to_string(int(fmod((double)duration.count() / ((double)1000.0), 1)*1000)) << " millisec"<<endl;
		outfile.close();
	}
	DtCATCH_AND_WARN(std::cout);
}

//[5]
/****************** cleanUp **********************/
void Simulator::cleanUp()
{

	print_color_message("\n-------------------- Simulator: clean up --------------------\n", COLOR_TEXT::MAIN_TITLE_GREEN);

	if (this->enviromental_elements != NULL) {
		print_color_message("\n------------ Delete Enviromental receivers ---------\n", COLOR_TEXT::CYAN_COLOR);
		delete this->enviromental_elements;
	}
	print_color_message("\n------------ Delete Event receiver -----------------\n", COLOR_TEXT::CYAN_COLOR);
	if (!this->team_event.empty()) {
		for (std::vector<EVENT*>::iterator it = std::begin((this->team_event)); it != std::end((this->team_event)); ++it) {
			delete (*it);
		}
	}
	this->team_event.clear();
	std::cout << "---- Event receiver Deleted" << std::endl;


	print_color_message("\n------------ Delete UxV Team -----------------------\n", COLOR_TEXT::CYAN_COLOR);
	delete this->uxv_team;

	try {
		if (this->enviromental_elements != NULL) {
			print_color_message("\n------------ Delete Enviromental FOMS -------------\n", COLOR_TEXT::CYAN_COLOR);
			//delete this->TxRxLink_objPub;
			delete this->refList_VS_EnvironmentWaterColumn;
			delete this->refList_VS_EnvironmentWaterSurface;
			delete this->refList_VS_Environment;
		}
	}
	catch (...) {}
	print_color_message("\n------------ Delete connections -------------------\n", COLOR_TEXT::CYAN_COLOR);
	delete this->exConn;
}

//[6]
/****************** simulator_main ***************/
void Simulator::simulator_main(int argc, char* argv[]) {
	std::string file_log = "Simulation_Logs";
	std::string file = "Input Data/Input_Data.json";

	this->read_data_from_json(argc, argv, this->scenario, file, file_log);
	this->start(argc, argv, this->scenario, file);
	this->cleanUp();
}

//[7]
/****************** LISTEN **********************/
void Simulator::listen(bool reset) {
	if (reset) {
		print_color_message("\n---------------------------- RESET ------------------------------------\n", 15);
		if (!this->team_event.empty()) {
			for (std::vector<EVENT*>::iterator it = std::begin((this->team_event)); it != std::end((this->team_event)); ++it) {
				delete (*it);
			}
		}
		this->team_event.clear();
		(this->team_event).push_back(new EVENT(EVENT_MESSAGE::RESET_VESSELS, JOB::NONE, 0, 0, 0, 0, 0, 0, 0, ""));
	}
	else {
		this->enviromental_elements->set_enviromental_elements(this->refList_VS_EnvironmentWaterSurface, this->refList_VS_EnvironmentWaterColumn);
		this->evaluateEvent();
	}
}

//[8]
/******************* TALK ***********************/
void Simulator::talk(DtTime dt, DtTime simTime) {
	print_color_message("\n---------------------------- TALK -------------------------------------\n",9,this->commnents);
	this->uxv_team->start_team_cycle(dt, &(this->team_event), simTime, this->enviromental_elements);
}

//[9]
/******************* evaluateEvent **************/
void Simulator::evaluateEvent() //Evaluate the income event and execute the relevant movements
{
	if (!this->team_event.empty()) {
		for (std::vector<EVENT*>::iterator it = std::begin((this->team_event)); it != std::end((this->team_event)); ++it) {
			delete (*it);
		}
	}
	this->team_event.clear();

	EVENT_MESSAGE event_coming = EVENT_MESSAGE::NO_MESSAGE;
	if (event_coming == EVENT_MESSAGE::TARGET_INCOMING) {
		double x = 0;
		double y = 0;
		double z = 0;
		double an = 0;
		double vel = 0;
		double id = 1;
		double area = 5;
		(this->team_event).push_back(new EVENT(EVENT_MESSAGE::TARGET_INCOMING, JOB::NONE, id, x, y, z, an, vel, area, "no_vessel"));
	}
	else if (event_coming == EVENT_MESSAGE::TASK_EXECUTION) {
		double x = 0;
		double y = 0;
		double z = 0;
		double an = 0;
		double vel = 0;
		double id = 0;
		double area = 0;
		JOB job = JOB::NONE;
		std::string vessel_name;
		(this->team_event).push_back(new EVENT(EVENT_MESSAGE::TASK_EXECUTION, job, x, y, z, an, vel, area, id, vessel_name));
	}
	else {

	}
}
