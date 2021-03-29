/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file AISDecoderHLA.h
//! \brief Contains the DtOCEAN2020FOMAISDecoder class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once
 
#if DtHLA 

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"
 
//VRLINK include
#include <vl\baseEmbeddedSystemDecoder.h>


namespace OCEAN2020 {
 
class DtOCEAN2020FOMAISStateRepository;
 
//! Instances of DtOCEAN2020FOMAISDecoder are used to decode
//! data from the network into DtOCEAN2020FOMAISStateRepository objects.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMAISDecoder : public DtBaseEmbeddedSystemDecoder
{
public:
   //! Default constructor.
   DtOCEAN2020FOMAISDecoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMAISDecoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMAISDecoder(const DtOCEAN2020FOMAISDecoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMAISDecoder& operator=(const DtOCEAN2020FOMAISDecoder& orig);
 
public:
   //! Creates an instance of DtOCEAN2020FOMAISDecoder.
   static DtHlaStateDecoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
protected:
   
//! Decodes ClassType from attrs into rep.
   static void decodeClassType(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes COG from attrs into rep.
   static void decodeCOG(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes Destination from attrs into rep.
   static void decodeDestination(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes ETA from attrs into rep.
   static void decodeETA(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes IMO from attrs into rep.
   static void decodeIMO(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes Latitude from attrs into rep.
   static void decodeLatitude(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes Longitude from attrs into rep.
   static void decodeLongitude(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes MMSI from attrs into rep.
   static void decodeMMSI(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes Name from attrs into rep.
   static void decodeName(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes NavigationStatus from attrs into rep.
   static void decodeNavigationStatus(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes SOG from attrs into rep.
   static void decodeSOG(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes TB from attrs into rep.
   static void decodeTB(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes TH from attrs into rep.
   static void decodeTH(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes TurnRate from attrs into rep.
   static void decodeTurnRate(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes UTC_s from attrs into rep.
   static void decodeUTC_s(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes UTC_TimeStamp from attrs into rep.
   static void decodeUTC_TimeStamp(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes RCS from attrs into rep.
   static void decodeRCS(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes VesselLength from attrs into rep.
   static void decodeVesselLength(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes VesselWidth from attrs into rep.
   static void decodeVesselWidth(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes VesselType from attrs into rep.
   static void decodeVesselType(
      DtOCEAN2020FOMAISStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);

};
 
} //end OCEAN2020
 
#endif
