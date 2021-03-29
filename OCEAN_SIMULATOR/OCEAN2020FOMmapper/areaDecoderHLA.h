/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file areaDecoderHLA.h
//! \brief Contains the DtOCEAN2020FOMAreaDecoder class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once
 
#if DtHLA 

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl\sensorDecoder.h>
 
namespace OCEAN2020 {
 
class DtOCEAN2020EntityStateRepository;
 
//! Instances of DtOCEAN2020FOMAreaDecoder are used to decode
//! data from the network into DtOCEAN2020EntityStateRepository objects.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMAreaDecoder : public DtSensorDecoder
{
public:
   //! Default constructor.
   DtOCEAN2020FOMAreaDecoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMAreaDecoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMAreaDecoder(const DtOCEAN2020FOMAreaDecoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMAreaDecoder& operator=(const DtOCEAN2020FOMAreaDecoder& orig);
 
public:
   //! Creates an instance of DtOCEAN2020FOMAreaDecoder.
   static DtHlaStateDecoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
protected:
   
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
