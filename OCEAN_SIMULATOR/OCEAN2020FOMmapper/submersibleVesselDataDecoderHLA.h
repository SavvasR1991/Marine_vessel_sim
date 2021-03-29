/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file submersibleVesselDataDecoderHLA.h
//! \brief Contains the DtOCEAN2020FOMSubmersibleVesselDataDecoder class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once
 
#if DtHLA 

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl\platformDecoder.h>
 
namespace OCEAN2020 {
 
class DtOCEAN2020EntityStateRepository;
 
//! Instances of DtOCEAN2020FOMSubmersibleVesselDataDecoder are used to decode
//! data from the network into DtOCEAN2020EntityStateRepository objects.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMSubmersibleVesselDataDecoder : public DtPlatformDecoder
{
public:
   //! Default constructor.
   DtOCEAN2020FOMSubmersibleVesselDataDecoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMSubmersibleVesselDataDecoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMSubmersibleVesselDataDecoder(const DtOCEAN2020FOMSubmersibleVesselDataDecoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMSubmersibleVesselDataDecoder& operator=(const DtOCEAN2020FOMSubmersibleVesselDataDecoder& orig);
 
public:
   //! Creates an instance of DtOCEAN2020FOMSubmersibleVesselDataDecoder.
   static DtHlaStateDecoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
protected:
   
//! Decodes ASBHeight from attrs into rep.
   static void decodeASBHeight(
      DtOCEAN2020EntityStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);

};
 
} //end OCEAN2020
 
#endif
