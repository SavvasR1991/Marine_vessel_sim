#pragma once
#ifndef OCEAN_FEDERATES_HEADERS_H
#define OCEAN_FEDERATES_HEADERS_H

/****************************************************************************
 * Copyright (c) 2017 VT MAK
 * All rights reserved.
 ****************************************************************************/

 //Project include
#include "mineEventReportInterHLA.h"
#include "mosaicSeabedStateRepository.h"
#include "OCEAN2020EntityStateRepository.h"
#include "OCEAN2020RadioReceiverStateRepository.h"
#include "OCEAN2020RadioTransmitterStateRepository.h"
#include "OCEAN2020EntityPublisherHLA.h"
#include "OCEAN2020RadioTransmitterPublisherHLA.h"
#include "OCEAN2020RadioReceiverPublisherHLA.h"
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
#include "sensorSettingsInterHLA.h"
#include "txRx_Link_OffReqInterHLA.h"
#include "txRx_Link_OnReqInterHLA.h"
#include "txRxLink_objStateRepository.h"
#include "txRxLink_objPublisherHLA.h"
#include "VS_EnvironmentStateRepository.h"
#include "VS_EnvironmentPublisherHLA.h"
#include "waterColumnStateRepository.h"
#include "waterSurfaceStateRepository.h"
#include "waterColumnPublisherHLA.h"
#include "waterSurfacePublisherHLA.h"

#include <vl/entityPublisher.h>
#include <vl/entityStateRepository.h>
#include <vl/exerciseConn.h>
#include <vl/exerciseConnInitializer.h>
#include <vl/fireInteraction.h>
#include <vl/iffPublisher.h>
#include <vl/topoView.h>
#include <vlpi/entityTypes.h>
#include <vlutil/vlMiniDumper.h>
#include <vlutil/vlProcessControl.h>
#include <vlutil/vlRtiMismatchException.h>
#include <vl/environmentProcessRepository.h>
#include <vl/fomMapper.h>
#include <vl/reflectedEntity.h>
#include <vl/reflectedEntityList.h>
#include <vl/reflectedEnvironmentProcess.h>
#include <vl/reflectedEnvironmentProcessList.h>
#include <vl/signalInteraction.h>
#include <vl/startResumeInteraction.h>

#include <map>
#include <list>
#include <cmath>
#include <limits>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <WinBase.h>
#include <matrix/3dPoint.h>
#include <algorithm>
#include <stdexcept>

#include "Data_Constant_Values.h"
#include "Point.h"
#include "Sector.h"
#include "UxV_Jobs.h"
#include "JSON_Reader.h"
#include "Area_Obstacle.h"
#include "Data_Stuctures.h"
#include "Shadow_Team.h"
#include "Utils_Functions.h"
#include "General_functions.h"
#include "Geometry_Functions.h"
#include "Collision_avoidance.h"
#include "Predictor_Position.h"
#include "Water_Waves_Kinematics.h"

using namespace std;
using namespace OCEAN2020;
using namespace std::chrono;


#endif