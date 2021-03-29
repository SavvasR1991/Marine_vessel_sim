/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file submersibleVesselDataEncoderHLA.h
//! \brief Contains the DtOCEAN2020FOMSubmersibleVesselDataEncoder class declaration.
 
#pragma once
 
#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl\platformEncoder.h>
 
namespace OCEAN2020 {
 
class DtOCEAN2020EntityStateRepository;
 
//! Instances of DtOCEAN2020FOMSubmersibleVesselDataEncoder encode data
//! from DtOCEAN2020EntityStateRepository objects to the net
//! structures to be sent to the network.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMSubmersibleVesselDataEncoder : public DtPlatformEncoder
{
public:
 
   //! Default constructor.
   DtOCEAN2020FOMSubmersibleVesselDataEncoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMSubmersibleVesselDataEncoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMSubmersibleVesselDataEncoder(const DtOCEAN2020FOMSubmersibleVesselDataEncoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMSubmersibleVesselDataEncoder& operator=(const DtOCEAN2020FOMSubmersibleVesselDataEncoder& orig);
 
public:
   //! Function that creates a DtOCEAN2020FOMSubmersibleVesselDataEncoder.
   static DtHlaStateEncoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
   
protected:

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

};
 
} //end OCEAN2020
 
#endif
