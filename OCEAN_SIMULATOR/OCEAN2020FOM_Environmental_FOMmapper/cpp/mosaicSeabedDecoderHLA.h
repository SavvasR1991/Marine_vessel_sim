/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**hobjDecHeader.tlt
*********************************************************************/
 
//! \file mosaicSeabedDecoderHLA.h
//! \brief Contains the DtOCEAN2020FOMMosaicSeabedDecoder class declaration.
//! \ingroup OCEAN2020FOM_Environmental
 
#pragma once
 
#if DtHLA 
 
#include "VS_EnvironmentDecoderHLA.h"
#include "dllExport.h"
 
namespace OCEAN2020 {
 
class DtOCEAN2020FOMMosaicSeabedStateRepository;
 
//! Instances of DtOCEAN2020FOMMosaicSeabedDecoder are used to decode
//! data from the network into DtOCEAN2020FOMMosaicSeabedStateRepository objects.
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtOCEAN2020FOMMosaicSeabedDecoder : public DtOCEAN2020FOMVS_EnvironmentDecoder
{
public:
   //! Default constructor.
   DtOCEAN2020FOMMosaicSeabedDecoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMMosaicSeabedDecoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMMosaicSeabedDecoder(const DtOCEAN2020FOMMosaicSeabedDecoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMMosaicSeabedDecoder& operator=(const DtOCEAN2020FOMMosaicSeabedDecoder& orig);
 
public:
   //! Creates an instance of DtOCEAN2020FOMMosaicSeabedDecoder.
   static DtHlaStateDecoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
protected:
   
//! Decodes BT_Clutter from attrs into rep.
   static void decodeBT_Clutter(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes BT_Clutter_Var from attrs into rep.
   static void decodeBT_Clutter_Var(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes BT_Posidonia from attrs into rep.
   static void decodeBT_Posidonia(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes BT_Posidonia_Var from attrs into rep.
   static void decodeBT_Posidonia_Var(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes BT_PosidoniaRipples from attrs into rep.
   static void decodeBT_PosidoniaRipples(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes BT_PosidoniaRipples_Var from attrs into rep.
   static void decodeBT_PosidoniaRipples_Var(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes BT_Ripples from attrs into rep.
   static void decodeBT_Ripples(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes BT_Ripples_Var from attrs into rep.
   static void decodeBT_Ripples_Var(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes BT_SMO from attrs into rep.
   static void decodeBT_SMO(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes BT_SMO_Var from attrs into rep.
   static void decodeBT_SMO_Var(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes BT_Ripple_Angl from attrs into rep.
   static void decodeBT_Ripple_Angl(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes BT_Ripple_Angl_Var from attrs into rep.
   static void decodeBT_Ripple_Angl_Var(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes Clusters from attrs into rep.
   static void decodeClusters(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes DPCA from attrs into rep.
   static void decodeDPCA(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes Lacunarity from attrs into rep.
   static void decodeLacunarity(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes Py_b0 from attrs into rep.
   static void decodePy_b0(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes Py_b1 from attrs into rep.
   static void decodePy_b1(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes Py_b2 from attrs into rep.
   static void decodePy_b2(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes Ripple from attrs into rep.
   static void decodeRipple(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes RRM_E from attrs into rep.
   static void decodeRRM_E(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes RRM_var from attrs into rep.
   static void decodeRRM_var(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes SurveyStatus from attrs into rep.
   static void decodeSurveyStatus(
      DtOCEAN2020FOMMosaicSeabedStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);

};
 
} //end OCEAN2020
 
#endif