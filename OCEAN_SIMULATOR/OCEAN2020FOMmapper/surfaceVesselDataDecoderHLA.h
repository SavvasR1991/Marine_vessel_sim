/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file surfaceVesselDataDecoderHLA.h
//! \brief Contains the DtOCEAN2020FOMSurfaceVesselDataDecoder class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once
 
#if DtHLA 

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl\platformDecoder.h>
 
namespace OCEAN2020 {
 
class DtOCEAN2020EntityStateRepository;
 
//! Instances of DtOCEAN2020FOMSurfaceVesselDataDecoder are used to decode
//! data from the network into DtOCEAN2020EntityStateRepository objects.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMSurfaceVesselDataDecoder : public DtPlatformDecoder
{
public:
   //! Default constructor.
   DtOCEAN2020FOMSurfaceVesselDataDecoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMSurfaceVesselDataDecoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMSurfaceVesselDataDecoder(const DtOCEAN2020FOMSurfaceVesselDataDecoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMSurfaceVesselDataDecoder& operator=(const DtOCEAN2020FOMSurfaceVesselDataDecoder& orig);
 
public:
   //! Creates an instance of DtOCEAN2020FOMSurfaceVesselDataDecoder.
   static DtHlaStateDecoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
protected:
   
	//! Decodes DimensionLength from attrs into rep.
	static void decodeDimensionLength(
		DtOCEAN2020EntityStateRepository* rep,
		const RTI::AttributeHandleValuePairSet& attrs,
		int pairSetIndex);

	//! Decodes DimensionWidth from attrs into rep.
	static void decodeDimensionWidth(
		DtOCEAN2020EntityStateRepository* rep,
		const RTI::AttributeHandleValuePairSet& attrs,
		int pairSetIndex);

	//! Decodes DimensionHeight from attrs into rep.
	static void decodeDimensionHeight(
		DtOCEAN2020EntityStateRepository* rep,
		const RTI::AttributeHandleValuePairSet& attrs,
		int pairSetIndex);

};
 
} //end OCEAN2020
 
#endif
