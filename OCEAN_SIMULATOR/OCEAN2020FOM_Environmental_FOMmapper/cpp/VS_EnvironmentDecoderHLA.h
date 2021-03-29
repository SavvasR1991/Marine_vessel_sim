/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**hobjDecHeader.tlt
*********************************************************************/
 
//! \file VS_EnvironmentDecoderHLA.h
//! \brief Contains the DtOCEAN2020FOMVS_EnvironmentDecoder class declaration.
//! \ingroup OCEAN2020FOM_Environmental
 
#pragma once
 
#if DtHLA 
 
#include <vl/hlaStateDecoder.h>
#include "dllExport.h"
 
namespace OCEAN2020 {
 
class DtOCEAN2020FOMVS_EnvironmentStateRepository;
 
//! Instances of DtOCEAN2020FOMVS_EnvironmentDecoder are used to decode
//! data from the network into DtOCEAN2020FOMVS_EnvironmentStateRepository objects.
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtOCEAN2020FOMVS_EnvironmentDecoder : public DtHlaStateDecoder
{
public:
   //! Default constructor.
   DtOCEAN2020FOMVS_EnvironmentDecoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMVS_EnvironmentDecoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMVS_EnvironmentDecoder(const DtOCEAN2020FOMVS_EnvironmentDecoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMVS_EnvironmentDecoder& operator=(const DtOCEAN2020FOMVS_EnvironmentDecoder& orig);
 
public:
   //! Creates an instance of DtOCEAN2020FOMVS_EnvironmentDecoder.
   static DtHlaStateDecoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
protected:
   
//! Decodes NumRows from attrs into rep.
   static void decodeNumRows(
      DtOCEAN2020FOMVS_EnvironmentStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes NumColumns from attrs into rep.
   static void decodeNumColumns(
      DtOCEAN2020FOMVS_EnvironmentStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes NWCornerLatitude from attrs into rep.
   static void decodeNWCornerLatitude(
      DtOCEAN2020FOMVS_EnvironmentStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes NWCornerLongitude from attrs into rep.
   static void decodeNWCornerLongitude(
      DtOCEAN2020FOMVS_EnvironmentStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes SECornerLatitude from attrs into rep.
   static void decodeSECornerLatitude(
      DtOCEAN2020FOMVS_EnvironmentStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes SECornerLongitude from attrs into rep.
   static void decodeSECornerLongitude(
      DtOCEAN2020FOMVS_EnvironmentStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);

};
 
} //end OCEAN2020
 
#endif
