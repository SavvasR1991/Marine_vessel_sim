/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file AISEncoderHLA.h
//! \brief Contains the DtOCEAN2020FOMAISEncoder class declaration.
 
#pragma once
 
#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl\baseEmbeddedSystemEncoder.h>

namespace OCEAN2020 {
 
class DtOCEAN2020FOMAISStateRepository;
 
//! Instances of DtOCEAN2020FOMAISEncoder encode data
//! from DtOCEAN2020FOMAISStateRepository objects to the net
//! structures to be sent to the network.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMAISEncoder : public DtBaseEmbeddedSystemEncoder
{
public:
 
   //! Default constructor.
   DtOCEAN2020FOMAISEncoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMAISEncoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMAISEncoder(const DtOCEAN2020FOMAISEncoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMAISEncoder& operator=(const DtOCEAN2020FOMAISEncoder& orig);
 
public:
   //! Function that creates a DtOCEAN2020FOMAISEncoder.
   static DtHlaStateEncoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
   
protected:

   //! Return true if ClassType needs to be sent
   //! to the network, false otherwise.
   static bool needClassType(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes ClassType from rep into attrs.
   static void encodeClassType(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if COG needs to be sent
   //! to the network, false otherwise.
   static bool needCOG(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes COG from rep into attrs.
   static void encodeCOG(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if Destination needs to be sent
   //! to the network, false otherwise.
   static bool needDestination(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes Destination from rep into attrs.
   static void encodeDestination(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if ETA needs to be sent
   //! to the network, false otherwise.
   static bool needETA(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes ETA from rep into attrs.
   static void encodeETA(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if IMO needs to be sent
   //! to the network, false otherwise.
   static bool needIMO(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes IMO from rep into attrs.
   static void encodeIMO(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if Latitude needs to be sent
   //! to the network, false otherwise.
   static bool needLatitude(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes Latitude from rep into attrs.
   static void encodeLatitude(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if Longitude needs to be sent
   //! to the network, false otherwise.
   static bool needLongitude(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes Longitude from rep into attrs.
   static void encodeLongitude(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if MMSI needs to be sent
   //! to the network, false otherwise.
   static bool needMMSI(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes MMSI from rep into attrs.
   static void encodeMMSI(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if Name needs to be sent
   //! to the network, false otherwise.
   static bool needName(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes Name from rep into attrs.
   static void encodeName(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if NavigationStatus needs to be sent
   //! to the network, false otherwise.
   static bool needNavigationStatus(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes NavigationStatus from rep into attrs.
   static void encodeNavigationStatus(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if SOG needs to be sent
   //! to the network, false otherwise.
   static bool needSOG(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes SOG from rep into attrs.
   static void encodeSOG(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if TB needs to be sent
   //! to the network, false otherwise.
   static bool needTB(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes TB from rep into attrs.
   static void encodeTB(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if TH needs to be sent
   //! to the network, false otherwise.
   static bool needTH(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes TH from rep into attrs.
   static void encodeTH(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if TurnRate needs to be sent
   //! to the network, false otherwise.
   static bool needTurnRate(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes TurnRate from rep into attrs.
   static void encodeTurnRate(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if UTC_s needs to be sent
   //! to the network, false otherwise.
   static bool needUTC_s(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes UTC_s from rep into attrs.
   static void encodeUTC_s(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if UTC_TimeStamp needs to be sent
   //! to the network, false otherwise.
   static bool needUTC_TimeStamp(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes UTC_TimeStamp from rep into attrs.
   static void encodeUTC_TimeStamp(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if RCS needs to be sent
   //! to the network, false otherwise.
   static bool needRCS(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes RCS from rep into attrs.
   static void encodeRCS(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if VesselLength needs to be sent
   //! to the network, false otherwise.
   static bool needVesselLength(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes VesselLength from rep into attrs.
   static void encodeVesselLength(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if VesselWidth needs to be sent
   //! to the network, false otherwise.
   static bool needVesselWidth(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes VesselWidth from rep into attrs.
   static void encodeVesselWidth(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if VesselType needs to be sent
   //! to the network, false otherwise.
   static bool needVesselType(
      const DtOCEAN2020FOMAISStateRepository& stateRep, 
      const DtOCEAN2020FOMAISStateRepository& asSeenByRemote);
 
   //! Encodes VesselType from rep into attrs.
   static void encodeVesselType(
      const DtOCEAN2020FOMAISStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

};
 
} //end OCEAN2020
 
#endif
