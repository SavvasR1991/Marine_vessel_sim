/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file OCEAN2020RadioTransmitterDecoderHLA.h
//! \brief Contains the DtOCEAN2020FOMRadioTransmitterDecoder class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once
 
#if DtHLA 

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl\radioTransmitterDecoderHLA.h>
 
namespace OCEAN2020 {
 
class DtOCEAN2020FOMRadioTransmitterStateRepository;
 
//! Instances of DtOCEAN2020FOMRadioTransmitterDecoder are used to decode
//! data from the network into DtOCEAN2020FOMRadioTransmitterStateRepository objects.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMRadioTransmitterDecoder : public DtRadioTransmitterDecoder
{
public:
   //! Default constructor.
   DtOCEAN2020FOMRadioTransmitterDecoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMRadioTransmitterDecoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMRadioTransmitterDecoder(const DtOCEAN2020FOMRadioTransmitterDecoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMRadioTransmitterDecoder& operator=(const DtOCEAN2020FOMRadioTransmitterDecoder& orig);
 
public:
   //! Creates an instance of DtOCEAN2020FOMRadioTransmitterDecoder.
   static DtHlaStateDecoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
protected:
   
//! Decodes TransmitterMaxGaindB from attrs into rep.
   static void decodeTransmitterMaxGaindB(
      DtOCEAN2020FOMRadioTransmitterStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes TransmitterChannelBandwidthHz from attrs into rep.
   static void decodeTransmitterChannelBandwidthHz(
      DtOCEAN2020FOMRadioTransmitterStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes TransmitterAntiJammingTechnique from attrs into rep.
   static void decodeTransmitterAntiJammingTechnique(
      DtOCEAN2020FOMRadioTransmitterStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes TransmitterType from attrs into rep.
   static void decodeTransmitterType(
      DtOCEAN2020FOMRadioTransmitterStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes TransmitterHarmonicLevelAboveFunddB from attrs into rep.
   static void decodeTransmitterHarmonicLevelAboveFunddB(
      DtOCEAN2020FOMRadioTransmitterStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes TransmitterBroadbandNoisePowerDensity from attrs into rep.
   static void decodeTransmitterBroadbandNoisePowerDensity(
      DtOCEAN2020FOMRadioTransmitterStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes TransmitterSpuriousLevelAbovefunddB from attrs into rep.
   static void decodeTransmitterSpuriousLevelAbovefunddB(
      DtOCEAN2020FOMRadioTransmitterStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);

//! Decodes OperatingFrequency from attrs into rep.
   static void decodeOperatingFrequency(
      DtOCEAN2020FOMRadioTransmitterStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes ChannelBandwidth from attrs into rep.
   static void decodeChannelBandwidth(
      DtOCEAN2020FOMRadioTransmitterStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);

};
 
} //end OCEAN2020
 
#endif
