/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/

//! \file OCEAN2020PlatformDecoderHLA.h
//! \brief Contains the DtOCEAN2020FOMEntityDecoder class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015

#pragma once

#if DtHLA 

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl\platformDecoder.h>

namespace OCEAN2020 {

	class DtOCEAN2020EntityStateRepository;

	//! Instances of DtOCEAN2020FOMEntityDecoder are used to decode
	//! data from the network into DtOCEAN2020EntityStateRepository objects.
	//! \ingroup OCEAN2020FOM_SISOSTD00112015
	class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMEntityDecoder : public DtPlatformDecoder
	{
	public:
		//! Default constructor.
		DtOCEAN2020FOMEntityDecoder(
			DtExerciseConn* exConn,
			DtObjClassDesc* classDesc);

		//! Destructor.
		virtual ~DtOCEAN2020FOMEntityDecoder();

		//! Copy constructor.
		DtOCEAN2020FOMEntityDecoder(const DtOCEAN2020FOMEntityDecoder& orig);

		//! Assignment operator.
		DtOCEAN2020FOMEntityDecoder& operator=(const DtOCEAN2020FOMEntityDecoder& orig);

	public:
		//! Creates an instance of DtOCEAN2020FOMEntityDecoder.
		static DtHlaStateDecoder* create(
			DtExerciseConn* exConn,
			DtObjClassDesc* classDesc);

	protected:

		//****************************************************
		// Sensor attributes from RPR_FOM_v2.0_1516-2010
		//****************************************************

		//! Decodes AntennaRaised from attrs into rep.
		static void decodeAntennaRaised(
			DtOCEAN2020EntityStateRepository* rep,
			const RTI::AttributeHandleValuePairSet& attrs,
			int pairSetIndex);

		//! Decodes BlackoutLightsOn from attrs into rep.
		static void decodeBlackoutLightsOn(
			DtOCEAN2020EntityStateRepository* rep,
			const RTI::AttributeHandleValuePairSet& attrs,
			int pairSetIndex);

		//! Decodes LightsOn from attrs into rep.
		static void decodeLightsOn(
			DtOCEAN2020EntityStateRepository* rep,
			const RTI::AttributeHandleValuePairSet& attrs,
			int pairSetIndex);

		//! Decodes InteriorLightsOn from attrs into rep.
		static void decodeInteriorLightsOn(
			DtOCEAN2020EntityStateRepository* rep,
			const RTI::AttributeHandleValuePairSet& attrs,
			int pairSetIndex);

		//! Decodes MissionKill from attrs into rep.
		static void decodeMissionKill(
			DtOCEAN2020EntityStateRepository* rep,
			const RTI::AttributeHandleValuePairSet& attrs,
			int pairSetIndex);

		//*******************************************************
		// End of Sensor attributes from RPR_FOM_v2.0_1516-2010
		//*******************************************************

		//! Decodes ASBHeight from attrs into rep.
		static void decodeASBHeight(
			DtOCEAN2020EntityStateRepository* rep,
			const RTI::AttributeHandleValuePairSet& attrs,
			int pairSetIndex);

		//! Decodes Area_Id from attrs into rep.
		static void decodeArea_Id(
			DtOCEAN2020EntityStateRepository* rep,
			const RTI::AttributeHandleValuePairSet& attrs,
			int pairSetIndex);

		//! Decodes Area_Type from attrs into rep.
		static void decodeArea_Type(
			DtOCEAN2020EntityStateRepository* rep,
			const RTI::AttributeHandleValuePairSet& attrs,
			int pairSetIndex);

		//! Decodes Vertices from attrs into rep.
		static void decodeVertices(
			DtOCEAN2020EntityStateRepository* rep,
			const RTI::AttributeHandleValuePairSet& attrs,
			int pairSetIndex);

	};

} //end OCEAN2020

#endif
