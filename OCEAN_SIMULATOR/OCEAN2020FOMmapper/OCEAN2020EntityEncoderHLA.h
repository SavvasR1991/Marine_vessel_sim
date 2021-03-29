/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/

//! \file OCEAN2020PlatformEncoderHLA.h
//! \brief Contains the DtOCEAN2020FOMEntityEncoder class declaration.

#pragma once

#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl\platformEncoder.h>

namespace OCEAN2020 {

	class DtOCEAN2020EntityStateRepository;

	//! Instances of DtOCEAN2020FOMAreaEncoder encode data
	//! from DtOCEAN2020EntityStateRepository objects to the net
	//! structures to be sent to the network.
	//! \ingroup OCEAN2020FOM_SISOSTD00112015
	class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMEntityEncoder : public DtPlatformEncoder
	{
	public:

		//! Default constructor.
		DtOCEAN2020FOMEntityEncoder(
			DtExerciseConn* exConn,
			DtObjClassDesc* classDesc);

		//! Destructor.
		virtual ~DtOCEAN2020FOMEntityEncoder();

		//! Copy constructor.
		DtOCEAN2020FOMEntityEncoder(const DtOCEAN2020FOMEntityEncoder& orig);

		//! Assignment operator.
		DtOCEAN2020FOMEntityEncoder& operator=(const DtOCEAN2020FOMEntityEncoder& orig);

	public:
		//! Function that creates a DtOCEAN2020FOMAreaEncoder.
		static DtHlaStateEncoder* create(
			DtExerciseConn* exConn,
			DtObjClassDesc* classDesc);

	protected:

		//****************************************************
		// Sensor attributes from RPR_FOM_v2.0_1516-2010
		//****************************************************

		//! Return true if AntennaRaised needs to be sent
		//! to the network, false otherwise.
		static bool needAntennaRaised(
			const DtOCEAN2020EntityStateRepository& stateRep,
			const DtOCEAN2020EntityStateRepository& asSeenByRemote);

		//! Encodes AntennaRaised from rep into attrs.
		static void encodeAntennaRaised(
			const DtOCEAN2020EntityStateRepository& rep,
			RTI::AttributeHandleValuePairSet* attrs,
			RTI::AttributeHandle attrHandle);

		//! Return true if BlackoutLightsOn needs to be sent
		//! to the network, false otherwise.
		static bool needBlackoutLightsOn(
			const DtOCEAN2020EntityStateRepository& stateRep,
			const DtOCEAN2020EntityStateRepository& asSeenByRemote);

		//! Encodes BlackoutLightsOn from rep into attrs.
		static void encodeBlackoutLightsOn(
			const DtOCEAN2020EntityStateRepository& rep,
			RTI::AttributeHandleValuePairSet* attrs,
			RTI::AttributeHandle attrHandle);

		//! Return true if LightsOn needs to be sent
		//! to the network, false otherwise.
		static bool needLightsOn(
			const DtOCEAN2020EntityStateRepository& stateRep,
			const DtOCEAN2020EntityStateRepository& asSeenByRemote);

		//! Encodes LightsOn from rep into attrs.
		static void encodeLightsOn(
			const DtOCEAN2020EntityStateRepository& rep,
			RTI::AttributeHandleValuePairSet* attrs,
			RTI::AttributeHandle attrHandle);

		//! Return true if InteriorLightsOn needs to be sent
		//! to the network, false otherwise.
		static bool needInteriorLightsOn(
			const DtOCEAN2020EntityStateRepository& stateRep,
			const DtOCEAN2020EntityStateRepository& asSeenByRemote);

		//! Encodes InteriorLightsOn from rep into attrs.
		static void encodeInteriorLightsOn(
			const DtOCEAN2020EntityStateRepository& rep,
			RTI::AttributeHandleValuePairSet* attrs,
			RTI::AttributeHandle attrHandle);

		//! Return true if MissionKill needs to be sent
		//! to the network, false otherwise.
		static bool needMissionKill(
			const DtOCEAN2020EntityStateRepository& stateRep,
			const DtOCEAN2020EntityStateRepository& asSeenByRemote);

		//! Encodes MissionKill from rep into attrs.
		static void encodeMissionKill(
			const DtOCEAN2020EntityStateRepository& rep,
			RTI::AttributeHandleValuePairSet* attrs,
			RTI::AttributeHandle attrHandle);

		//*******************************************************
		// End of Sensor attributes from RPR_FOM_v2.0_1516-2010
		//*******************************************************


		//! Return true if ASBHeight needs to be sent
		//! to the network, false otherwise.
		static bool needASBHeight(
			const DtOCEAN2020EntityStateRepository& stateRep,
			const DtOCEAN2020EntityStateRepository& asSeenByRemote);

		//! Encodes ASBHeight from rep into attrs.
		static void encodeASBHeight(
			const DtOCEAN2020EntityStateRepository& rep,
			RTI::AttributeHandleValuePairSet* attrs,
			RTI::AttributeHandle attrHandle);

		//! Return true if Area_Id needs to be sent
		//! to the network, false otherwise.
		static bool needArea_Id(
			const DtOCEAN2020EntityStateRepository& stateRep,
			const DtOCEAN2020EntityStateRepository& asSeenByRemote);

		//! Encodes Area_Id from rep into attrs.
		static void encodeArea_Id(
			const DtOCEAN2020EntityStateRepository& rep,
			RTI::AttributeHandleValuePairSet* attrs,
			RTI::AttributeHandle attrHandle);

		//! Return true if Area_Type needs to be sent
		//! to the network, false otherwise.
		static bool needArea_Type(
			const DtOCEAN2020EntityStateRepository& stateRep,
			const DtOCEAN2020EntityStateRepository& asSeenByRemote);

		//! Encodes Area_Type from rep into attrs.
		static void encodeArea_Type(
			const DtOCEAN2020EntityStateRepository& rep,
			RTI::AttributeHandleValuePairSet* attrs,
			RTI::AttributeHandle attrHandle);

		//! Return true if Vertices needs to be sent
		//! to the network, false otherwise.
		static bool needVertices(
			const DtOCEAN2020EntityStateRepository& stateRep,
			const DtOCEAN2020EntityStateRepository& asSeenByRemote);

		//! Encodes Vertices from rep into attrs.
		static void encodeVertices(
			const DtOCEAN2020EntityStateRepository& rep,
			RTI::AttributeHandleValuePairSet* attrs,
			RTI::AttributeHandle attrHandle);

	};

} //end OCEAN2020

#endif
