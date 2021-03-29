#pragma once

#ifndef WATER_WAVES_KINEMATICS_H
#define WATER_WAVES_KINEMATICS_H

#include "OCEAN2020EntityStateRepository.h"
#include "OCEAN2020RadioReceiverStateRepository.h"
#include "OCEAN2020RadioTransmitterStateRepository.h"
#include "reflectedAISHLA.h"
#include "reflectedAISListHLA.h"
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
#include <vl/entityStateRepository.h>
#include <vl/environmentProcessRepository.h>

#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <tchar.h>

#include "Utils_Functions.h"
#include "Data_Stuctures.h"
#include "Geometry_Functions.h"


using namespace OCEAN2020;

class Water_Waves_Kinematics {

private:
	/***************************************************/
	/***** Enviromental_Elements ATTRIBUTES ************/
	/***************************************************/

	//************ FOM COLUMNS ***********//
	DtOCEAN2020FOMWaterColumnStateRepository *first_VS_EnvironmentWaterColumnSR;
	DtOCEAN2020FOMWaterSurfaceStateRepository *first_VS_EnvironmentWaterSurfaceSR;
	DtOCEAN2020FOMRadioReceiverStateRepository* first_VS_EnvironmentRadioReceiverSR;
	//************ MESSAGES *************//
	bool enviromental_available;
	bool wcol_available;
	bool wsur_available;
	bool radio_receiver_available;

	//************ SEGMENTS *************//
	int x_segments_2d;
	int y_segments_2d;
	int x_segments_3d;
	int y_segments_3d;
	int z_segments_3d;

	double refLat;
	double reflong;
	double refDepth;

	double MAX_Vessel_speed_surface;
	//************ FUNCTIONS ************//
	void setWaterColumn(DtOCEAN2020FOMWaterColumnStateRepository *);
	void setWaterSurface(DtOCEAN2020FOMWaterSurfaceStateRepository *);

	void created_2d_Water_Surface_field();
	void created_3d_Water_Current_field();

	void calculate_water_surface_2d_disruption(FOM_EVENT *event, double, double, double, double, ENVIROMENTAL_SURFACE_WATER_FIELD*, double, double, double, double,int);
	void calculate_water_current_3d_disruption(FOM_EVENT *event, double, double, double, double, double, double, double, double, ENVIROMENTAL_CURRENT_WATER_FIELD*, double, double);

public:
	/****** FOM VECTORS 2D/3D *********************/
	vector<ENVIROMENTAL_SURFACE_WATER_FIELD*> FOM_table_surface_vess;
	vector<ENVIROMENTAL_CURRENT_WATER_FIELD*> FOM_table_subwater_vess;

	/******* CONTSTRUCTOR /DESTRUCTOR ************/
	Water_Waves_Kinematics(double refLat, double reflong, double);
	~Water_Waves_Kinematics();

	/******* Enviromental_Elements FUNCTIONS *****/
	bool set_enviromental_elements(DtReflectedOCEAN2020FOMWaterSurfaceList*, DtReflectedOCEAN2020FOMWaterColumnList*);
	void set_enviromental_disruption_for_point(std::string,FOM_EVENT *,double,double,double, double, double,double,double,double, std::string,double,double,double,double,double,int);
	bool water_wave_messages_available();
	bool water_currect_messages_available();

	/******* SEGMENTS GETTERS/SETTERS *************/
	int get_x_segments_2d();
	int get_y_segments_2d();
	int get_x_segments_3d();
	int get_y_segments_3d();
	int get_z_segments_3d();

	void set_x_segments_2d(int);
	void set_y_segments_2d(int);
	void set_x_segments_3d(int);
	void set_y_segments_3d(int);
	void set_z_segments_3d(int);

	/********* WaterColumns GETTERS ****************/
	DtU32 getWaterColumnNumRows();
	DtU32 getWaterColumnNumColumns();
	DtFloat64 getWaterColumnNWCornerLatitude();
	DtFloat64 getWaterColumnNWCornerLongitude();
	DtFloat64 getWaterColumnSECornerLatitude();
	DtFloat64 getWaterColumnSECornerLongitude();
	DtInt32 getWaterColumnNumberOfLayers();
	DtInt32 getWaterColumnShallowerLayer();
	DtInt32 getWaterColumnDeeperLayer();
	DtOCEAN2020FOMVariableLengthFloat32Array getWaterColumnLayers();

	/************* Watersurface GETTERS ************/
	DtU32 getWaterSurfaceNumRows();
	DtU32 getWaterSurfaceNumColumns();
	DtFloat64 getWaterSurfaceNWCornerLatitude();
	DtFloat64 getWaterSurfaceNWCornerLongitude();
	DtFloat64 getWaterSurfaceSECornerLatitude();
	DtFloat64 getWaterSurfaceSECornerLongitude();
	DtOCEAN2020FOMVariableLengthFloat32Array getWaterSurfaceSE_wave_frequency_array();
	DtOCEAN2020FOMVariableLengthFloat32Array getWaterSurfaceSE_wave_direction_array();
	DtOCEAN2020FOMVariableLengthFloat32Array getWaterSurfaceSE_wave_height_array();

	void created_2d_Water_Surface_field_T(DtFloat64, DtFloat64, DtFloat64, DtFloat64, DtFloat64, DtFloat64, DtFloat64, int, int);
	void created_3d_Water_Current_field_T(DtFloat64, DtFloat64, DtFloat64, DtFloat64, DtFloat64, DtFloat64, DtFloat64, DtFloat64, DtFloat64, DtFloat64, int, int, int);
};


#endif
