/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file OCEAN2020RadioTransmitterEncoderHLA.h
//! \brief Contains the DtOCEAN2020FOMRadioTransmitterEncoder class declaration.
 
#pragma once
 
#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl\radioTransmitterEncoderHLA.h>
 
namespace OCEAN2020 {
 
class DtOCEAN2020FOMRadioTransmitterStateRepository;
 
//! Instances of DtOCEAN2020FOMRadioTransmitterEncoder encode data
//! from DtOCEAN2020FOMRadioTransmitterStateRepository objects to the net
//! structures to be sent to the network.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMRadioTransmitterEncoder : public DtRadioTransmitterEncoder
{
public:
 
   //! Default constructor.
   DtOCEAN2020FOMRadioTransmitterEncoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMRadioTransmitterEncoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMRadioTransmitterEncoder(const DtOCEAN2020FOMRadioTransmitterEncoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMRadioTransmitterEncoder& operator=(const DtOCEAN2020FOMRadioTransmitterEncoder& orig);
 
public:
   //! Function that creates a DtOCEAN2020FOMRadioTransmitterEncoder.
   static DtHlaStateEncoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
   
protected:

   //! Return true if TransmitterMaxGaindB needs to be sent
   //! to the network, false otherwise.
   static bool needTransmitterMaxGaindB(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioTransmitterStateRepository& asSeenByRemote);
 
   //! Encodes TransmitterMaxGaindB from rep into attrs.
   static void encodeTransmitterMaxGaindB(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if TransmitterChannelBandwidthHz needs to be sent
   //! to the network, false otherwise.
   static bool needTransmitterChannelBandwidthHz(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioTransmitterStateRepository& asSeenByRemote);
 
   //! Encodes TransmitterChannelBandwidthHz from rep into attrs.
   static void encodeTransmitterChannelBandwidthHz(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if TransmitterAntiJammingTechnique needs to be sent
   //! to the network, false otherwise.
   static bool needTransmitterAntiJammingTechnique(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioTransmitterStateRepository& asSeenByRemote);
 
   //! Encodes TransmitterAntiJammingTechnique from rep into attrs.
   static void encodeTransmitterAntiJammingTechnique(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if TransmitterType needs to be sent
   //! to the network, false otherwise.
   static bool needTransmitterType(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioTransmitterStateRepository& asSeenByRemote);
 
   //! Encodes TransmitterType from rep into attrs.
   static void encodeTransmitterType(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if TransmitterHarmonicLevelAboveFunddB needs to be sent
   //! to the network, false otherwise.
   static bool needTransmitterHarmonicLevelAboveFunddB(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioTransmitterStateRepository& asSeenByRemote);
 
   //! Encodes TransmitterHarmonicLevelAboveFunddB from rep into attrs.
   static void encodeTransmitterHarmonicLevelAboveFunddB(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if TransmitterBroadbandNoisePowerDensity needs to be sent
   //! to the network, false otherwise.
   static bool needTransmitterBroadbandNoisePowerDensity(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioTransmitterStateRepository& asSeenByRemote);
 
   //! Encodes TransmitterBroadbandNoisePowerDensity from rep into attrs.
   static void encodeTransmitterBroadbandNoisePowerDensity(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if TransmitterSpuriousLevelAbovefunddB needs to be sent
   //! to the network, false otherwise.
   static bool needTransmitterSpuriousLevelAbovefunddB(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioTransmitterStateRepository& asSeenByRemote);
 
   //! Encodes TransmitterSpuriousLevelAbovefunddB from rep into attrs.
   static void encodeTransmitterSpuriousLevelAbovefunddB(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if OperatingFrequency needs to be sent
   //! to the network, false otherwise.
   static bool needOperatingFrequency(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioTransmitterStateRepository& asSeenByRemote);
 
   //! Encodes OperatingFrequency from rep into attrs.
   static void encodeOperatingFrequency(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if ChannelBandwidth needs to be sent
   //! to the network, false otherwise.
   static bool needChannelBandwidth(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioTransmitterStateRepository& asSeenByRemote);
 
   //! Encodes ChannelBandwidth from rep into attrs.
   static void encodeChannelBandwidth(
      const DtOCEAN2020FOMRadioTransmitterStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

};
 
} //end OCEAN2020
 
#endif
