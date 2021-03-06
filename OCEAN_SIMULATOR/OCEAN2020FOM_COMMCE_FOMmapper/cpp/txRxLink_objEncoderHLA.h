/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**hobjEncHeader.tlt
*********************************************************************/
 
//! \file txRxLink_objEncoderHLA.h
//! \brief Contains the DtOCEAN2020FOMTxRxLink_objEncoder class declaration.
 
#pragma once
 
#if DtHLA
 
#include <vl/hlaStateEncoder.h>
#include "dllExport.h"
 
namespace OCEAN2020 {
 
class DtOCEAN2020FOMTxRxLink_objStateRepository;
 
//! Instances of DtOCEAN2020FOMTxRxLink_objEncoder encode data
//! from DtOCEAN2020FOMTxRxLink_objStateRepository objects to the net
//! structures to be sent to the network.
//! \ingroup OCEAN2020FOM_COMMCE
class DT_DLL_OCEAN2020FOM_COMMCE DtOCEAN2020FOMTxRxLink_objEncoder : public DtHlaStateEncoder
{
public:
 
   //! Default constructor.
   DtOCEAN2020FOMTxRxLink_objEncoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMTxRxLink_objEncoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMTxRxLink_objEncoder(const DtOCEAN2020FOMTxRxLink_objEncoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMTxRxLink_objEncoder& operator=(const DtOCEAN2020FOMTxRxLink_objEncoder& orig);
 
public:
   //! Function that creates a DtOCEAN2020FOMTxRxLink_objEncoder.
   static DtHlaStateEncoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
   
protected:

   //! Return true if Capacity needs to be sent
   //! to the network, false otherwise.
   static bool needCapacity(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& stateRep, 
      const DtOCEAN2020FOMTxRxLink_objStateRepository& asSeenByRemote);
 
   //! Encodes Capacity from rep into attrs.
   static void encodeCapacity(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if Frequency needs to be sent
   //! to the network, false otherwise.
   static bool needFrequency(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& stateRep, 
      const DtOCEAN2020FOMTxRxLink_objStateRepository& asSeenByRemote);
 
   //! Encodes Frequency from rep into attrs.
   static void encodeFrequency(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if LinkStatus needs to be sent
   //! to the network, false otherwise.
   static bool needLinkStatus(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& stateRep, 
      const DtOCEAN2020FOMTxRxLink_objStateRepository& asSeenByRemote);
 
   //! Encodes LinkStatus from rep into attrs.
   static void encodeLinkStatus(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if Rx_ObjectID needs to be sent
   //! to the network, false otherwise.
   static bool needRx_ObjectID(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& stateRep, 
      const DtOCEAN2020FOMTxRxLink_objStateRepository& asSeenByRemote);
 
   //! Encodes Rx_ObjectID from rep into attrs.
   static void encodeRx_ObjectID(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if SN needs to be sent
   //! to the network, false otherwise.
   static bool needSN(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& stateRep, 
      const DtOCEAN2020FOMTxRxLink_objStateRepository& asSeenByRemote);
 
   //! Encodes SN from rep into attrs.
   static void encodeSN(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if Tx_ObjectID needs to be sent
   //! to the network, false otherwise.
   static bool needTx_ObjectID(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& stateRep, 
      const DtOCEAN2020FOMTxRxLink_objStateRepository& asSeenByRemote);
 
   //! Encodes Tx_ObjectID from rep into attrs.
   static void encodeTx_ObjectID(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if BER needs to be sent
   //! to the network, false otherwise.
   static bool needBER(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& stateRep, 
      const DtOCEAN2020FOMTxRxLink_objStateRepository& asSeenByRemote);
 
   //! Encodes BER from rep into attrs.
   static void encodeBER(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if SER needs to be sent
   //! to the network, false otherwise.
   static bool needSER(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& stateRep, 
      const DtOCEAN2020FOMTxRxLink_objStateRepository& asSeenByRemote);
 
   //! Encodes SER from rep into attrs.
   static void encodeSER(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if Modulation needs to be sent
   //! to the network, false otherwise.
   static bool needModulation(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& stateRep, 
      const DtOCEAN2020FOMTxRxLink_objStateRepository& asSeenByRemote);
 
   //! Encodes Modulation from rep into attrs.
   static void encodeModulation(
      const DtOCEAN2020FOMTxRxLink_objStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

};
 
} //end OCEAN2020
 
#endif
