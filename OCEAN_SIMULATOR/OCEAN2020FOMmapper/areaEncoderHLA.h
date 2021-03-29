/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file areaEncoderHLA.h
//! \brief Contains the DtOCEAN2020FOMAreaEncoder class declaration.
 
#pragma once
 
#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl\sensorEncoder.h>
 
namespace OCEAN2020 {
 
class DtOCEAN2020EntityStateRepository;
 
//! Instances of DtOCEAN2020FOMAreaEncoder encode data
//! from DtOCEAN2020EntityStateRepository objects to the net
//! structures to be sent to the network.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMAreaEncoder : public DtSensorEncoder
{
public:
 
   //! Default constructor.
   DtOCEAN2020FOMAreaEncoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMAreaEncoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMAreaEncoder(const DtOCEAN2020FOMAreaEncoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMAreaEncoder& operator=(const DtOCEAN2020FOMAreaEncoder& orig);
 
public:
   //! Function that creates a DtOCEAN2020FOMAreaEncoder.
   static DtHlaStateEncoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
   
protected:

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
