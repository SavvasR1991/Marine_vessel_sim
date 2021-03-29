/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file OCEAN2020RadioReceiverEncoderHLA.h
//! \brief Contains the DtOCEAN2020FOMRadioReceiverEncoder class declaration.
 
#pragma once
 
#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl\radioReceiverEncoderHLA.h>
 
namespace OCEAN2020 {
 
class DtOCEAN2020FOMRadioReceiverStateRepository;
 
//! Instances of DtOCEAN2020FOMRadioReceiverEncoder encode data
//! from DtOCEAN2020FOMRadioReceiverStateRepository objects to the net
//! structures to be sent to the network.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMRadioReceiverEncoder : public DtRadioReceiverEncoder
{
public:
 
   //! Default constructor.
   DtOCEAN2020FOMRadioReceiverEncoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMRadioReceiverEncoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMRadioReceiverEncoder(const DtOCEAN2020FOMRadioReceiverEncoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMRadioReceiverEncoder& operator=(const DtOCEAN2020FOMRadioReceiverEncoder& orig);
 
public:
   //! Function that creates a DtOCEAN2020FOMRadioReceiverEncoder.
   static DtHlaStateEncoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
   
protected:

   //! Return true if ReceiverMaxGaindB needs to be sent
   //! to the network, false otherwise.
   static bool needReceiverMaxGaindB(
      const DtOCEAN2020FOMRadioReceiverStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioReceiverStateRepository& asSeenByRemote);
 
   //! Encodes ReceiverMaxGaindB from rep into attrs.
   static void encodeReceiverMaxGaindB(
      const DtOCEAN2020FOMRadioReceiverStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if ReceiverSensitivitydBm needs to be sent
   //! to the network, false otherwise.
   static bool needSensitivity(
      const DtOCEAN2020FOMRadioReceiverStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioReceiverStateRepository& asSeenByRemote);
 
   //! Encodes ReceiverSensitivitydBm from rep into attrs.
   static void encodeSensitivity(
      const DtOCEAN2020FOMRadioReceiverStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if AntennaPatternData needs to be sent
   //! to the network, false otherwise.
   static bool needAntennaPatternData(
      const DtOCEAN2020FOMRadioReceiverStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioReceiverStateRepository& asSeenByRemote);
 
   //! Encodes AntennaPatternData from rep into attrs.
   static void encodeAntennaPatternData(
      const DtOCEAN2020FOMRadioReceiverStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if ReceiverAntiJammingTechnique needs to be sent
   //! to the network, false otherwise.
   static bool needReceiverAntiJammingTechnique(
      const DtOCEAN2020FOMRadioReceiverStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioReceiverStateRepository& asSeenByRemote);
 
   //! Encodes ReceiverAntiJammingTechnique from rep into attrs.
   static void encodeReceiverAntiJammingTechnique(
      const DtOCEAN2020FOMRadioReceiverStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if ReceiverType needs to be sent
   //! to the network, false otherwise.
   static bool needReceiverType(
      const DtOCEAN2020FOMRadioReceiverStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioReceiverStateRepository& asSeenByRemote);
 
   //! Encodes ReceiverType from rep into attrs.
   static void encodeReceiverType(
      const DtOCEAN2020FOMRadioReceiverStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if ReceiverShapeFactor needs to be sent
   //! to the network, false otherwise.
   static bool needReceiverShapeFactor(
      const DtOCEAN2020FOMRadioReceiverStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioReceiverStateRepository& asSeenByRemote);
 
   //! Encodes ReceiverShapeFactor from rep into attrs.
   static void encodeReceiverShapeFactor(
      const DtOCEAN2020FOMRadioReceiverStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if ReceiverSpuriousLevel needs to be sent
   //! to the network, false otherwise.
   static bool needReceiverSpuriousLevel(
      const DtOCEAN2020FOMRadioReceiverStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioReceiverStateRepository& asSeenByRemote);
 
   //! Encodes ReceiverSpuriousLevel from rep into attrs.
   static void encodeReceiverSpuriousLevel(
      const DtOCEAN2020FOMRadioReceiverStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if ReceiverChannelBandwidthHz needs to be sent
   //! to the network, false otherwise.
   static bool needReceiverChannelBandwidthHz(
      const DtOCEAN2020FOMRadioReceiverStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioReceiverStateRepository& asSeenByRemote);
 
   //! Encodes ReceiverChannelBandwidthHz from rep into attrs.
   static void encodeReceiverChannelBandwidthHz(
      const DtOCEAN2020FOMRadioReceiverStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if FrequencyBandwidth needs to be sent
   //! to the network, false otherwise.
   static bool needFrequencyBandwidth(
      const DtOCEAN2020FOMRadioReceiverStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioReceiverStateRepository& asSeenByRemote);
 
   //! Encodes FrequencyBandwidth from rep into attrs.
   static void encodeFrequencyBandwidth(
      const DtOCEAN2020FOMRadioReceiverStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if Frequency needs to be sent
   //! to the network, false otherwise.
   static bool needFrequency(
      const DtOCEAN2020FOMRadioReceiverStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioReceiverStateRepository& asSeenByRemote);
 
   //! Encodes Frequency from rep into attrs.
   static void encodeFrequency(
      const DtOCEAN2020FOMRadioReceiverStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if OperatingFrequency needs to be sent
   //! to the network, false otherwise.
   static bool needOperatingFrequency(
      const DtOCEAN2020FOMRadioReceiverStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioReceiverStateRepository& asSeenByRemote);
 
   //! Encodes OperatingFrequency from rep into attrs.
   static void encodeOperatingFrequency(
      const DtOCEAN2020FOMRadioReceiverStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if ChannelBandwidth needs to be sent
   //! to the network, false otherwise.
   static bool needChannelBandwidth(
      const DtOCEAN2020FOMRadioReceiverStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioReceiverStateRepository& asSeenByRemote);
 
   //! Encodes ChannelBandwidth from rep into attrs.
   static void encodeChannelBandwidth(
      const DtOCEAN2020FOMRadioReceiverStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if NoiseFigure needs to be sent
   //! to the network, false otherwise.
   static bool needNoiseFigure(
      const DtOCEAN2020FOMRadioReceiverStateRepository& stateRep, 
      const DtOCEAN2020FOMRadioReceiverStateRepository& asSeenByRemote);
 
   //! Encodes NoiseFigure from rep into attrs.
   static void encodeNoiseFigure(
      const DtOCEAN2020FOMRadioReceiverStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

};
 
} //end OCEAN2020
 
#endif
