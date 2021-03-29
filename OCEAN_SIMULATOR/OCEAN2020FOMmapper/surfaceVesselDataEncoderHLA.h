/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file surfaceVesselDataEncoderHLA.h
//! \brief Contains the DtOCEAN2020FOMSurfaceVesselDataEncoder class declaration.
 
#pragma once
 
#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl\platformEncoder.h>
 
namespace OCEAN2020 {
 
class DtOCEAN2020EntityStateRepository;
 
//! Instances of DtOCEAN2020FOMSurfaceVesselDataEncoder encode data
//! from DtOCEAN2020EntityStateRepository objects to the net
//! structures to be sent to the network.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMSurfaceVesselDataEncoder : public DtPlatformEncoder
{
public:
 
   //! Default constructor.
   DtOCEAN2020FOMSurfaceVesselDataEncoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMSurfaceVesselDataEncoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMSurfaceVesselDataEncoder(const DtOCEAN2020FOMSurfaceVesselDataEncoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMSurfaceVesselDataEncoder& operator=(const DtOCEAN2020FOMSurfaceVesselDataEncoder& orig);
 
public:
   //! Function that creates a DtOCEAN2020FOMSurfaceVesselDataEncoder.
   static DtHlaStateEncoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
   
protected:

	//! Return true if DimensionLength needs to be sent
	//! to the network, false otherwise.
	static bool needDimensionLength(
		const DtOCEAN2020EntityStateRepository& stateRep,
		const DtOCEAN2020EntityStateRepository& asSeenByRemote);

	//! Encodes DimensionLength from rep into attrs.
	static void encodeDimensionLength(
		const DtOCEAN2020EntityStateRepository& rep,
		RTI::AttributeHandleValuePairSet* attrs,
		RTI::AttributeHandle attrHandle);

	//! Return true if DimensionWidth needs to be sent
	//! to the network, false otherwise.
	static bool needDimensionWidth(
		const DtOCEAN2020EntityStateRepository& stateRep,
		const DtOCEAN2020EntityStateRepository& asSeenByRemote);

	//! Encodes DimensionWidth from rep into attrs.
	static void encodeDimensionWidth(
		const DtOCEAN2020EntityStateRepository& rep,
		RTI::AttributeHandleValuePairSet* attrs,
		RTI::AttributeHandle attrHandle);

	//! Return true if DimensionHeight needs to be sent
	//! to the network, false otherwise.
	static bool needDimensionHeight(
		const DtOCEAN2020EntityStateRepository& stateRep,
		const DtOCEAN2020EntityStateRepository& asSeenByRemote);

	//! Encodes DimensionHeight from rep into attrs.
	static void encodeDimensionHeight(
		const DtOCEAN2020EntityStateRepository& rep,
		RTI::AttributeHandleValuePairSet* attrs,
		RTI::AttributeHandle attrHandle);

};
 
} //end OCEAN2020
 
#endif
