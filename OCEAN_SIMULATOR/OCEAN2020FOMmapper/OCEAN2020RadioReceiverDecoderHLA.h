/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file OCEAN2020RadioReceiverDecoderHLA.h
//! \brief Contains the DtOCEAN2020FOMRadioReceiverDecoder class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once
 
#if DtHLA 

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl\radioReceiverDecoderHLA.h>
 
namespace OCEAN2020 {
 
class DtOCEAN2020FOMRadioReceiverStateRepository;
 
//! Instances of DtOCEAN2020FOMRadioReceiverDecoder are used to decode
//! data from the network into DtOCEAN2020FOMRadioReceiverStateRepository objects.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMRadioReceiverDecoder : public DtRadioReceiverDecoder
{
public:
   //! Default constructor.
   DtOCEAN2020FOMRadioReceiverDecoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMRadioReceiverDecoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMRadioReceiverDecoder(const DtOCEAN2020FOMRadioReceiverDecoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMRadioReceiverDecoder& operator=(const DtOCEAN2020FOMRadioReceiverDecoder& orig);
 
public:
   //! Creates an instance of DtOCEAN2020FOMRadioReceiverDecoder.
   static DtHlaStateDecoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
protected:
   
//! Decodes ReceiverMaxGaindB from attrs into rep.
   static void decodeReceiverMaxGaindB(
      DtOCEAN2020FOMRadioReceiverStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes Sensitivity from attrs into rep.
   static void decodeSensitivity(
      DtOCEAN2020FOMRadioReceiverStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes AntennaPatternData from attrs into rep.
   static void decodeAntennaPatternData(
      DtOCEAN2020FOMRadioReceiverStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes ReceiverAntiJammingTechnique from attrs into rep.
   static void decodeReceiverAntiJammingTechnique(
      DtOCEAN2020FOMRadioReceiverStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes ReceiverType from attrs into rep.
   static void decodeReceiverType(
      DtOCEAN2020FOMRadioReceiverStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes ReceiverShapeFactor from attrs into rep.
   static void decodeReceiverShapeFactor(
      DtOCEAN2020FOMRadioReceiverStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes ReceiverSpuriousLevel from attrs into rep.
   static void decodeReceiverSpuriousLevel(
      DtOCEAN2020FOMRadioReceiverStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes ReceiverChannelBandwidthHz from attrs into rep.
   static void decodeReceiverChannelBandwidthHz(
      DtOCEAN2020FOMRadioReceiverStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes FrequencyBandwidth from attrs into rep.
   static void decodeFrequencyBandwidth(
      DtOCEAN2020FOMRadioReceiverStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);

//! Decodes Frequency from attrs into rep.
   static void decodeFrequency(
      DtOCEAN2020FOMRadioReceiverStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes OperatingFrequency from attrs into rep.
   static void decodeOperatingFrequency(
      DtOCEAN2020FOMRadioReceiverStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes ChannelBandwidth from attrs into rep.
   static void decodeChannelBandwidth(
      DtOCEAN2020FOMRadioReceiverStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes NoiseFigure from attrs into rep.
   static void decodeNoiseFigure(
      DtOCEAN2020FOMRadioReceiverStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);

};
 
} //end OCEAN2020
 
#endif
