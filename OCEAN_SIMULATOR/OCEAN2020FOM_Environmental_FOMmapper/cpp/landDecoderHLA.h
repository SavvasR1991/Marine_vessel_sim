/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**hobjDecHeader.tlt
*********************************************************************/
 
//! \file landDecoderHLA.h
//! \brief Contains the DtOCEAN2020FOMLandDecoder class declaration.
//! \ingroup OCEAN2020FOM_Environmental
 
#pragma once
 
#if DtHLA 
 
#include "VS_EnvironmentDecoderHLA.h"
#include "dllExport.h"
 
namespace OCEAN2020 {
 
class DtOCEAN2020FOMLandStateRepository;
 
//! Instances of DtOCEAN2020FOMLandDecoder are used to decode
//! data from the network into DtOCEAN2020FOMLandStateRepository objects.
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtOCEAN2020FOMLandDecoder : public DtOCEAN2020FOMVS_EnvironmentDecoder
{
public:
   //! Default constructor.
   DtOCEAN2020FOMLandDecoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMLandDecoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMLandDecoder(const DtOCEAN2020FOMLandDecoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMLandDecoder& operator=(const DtOCEAN2020FOMLandDecoder& orig);
 
public:
   //! Creates an instance of DtOCEAN2020FOMLandDecoder.
   static DtHlaStateDecoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
protected:
   
//! Decodes LandRegionId from attrs into rep.
   static void decodeLandRegionId(
      DtOCEAN2020FOMLandStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes TerrainType from attrs into rep.
   static void decodeTerrainType(
      DtOCEAN2020FOMLandStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes SnowAccumulation from attrs into rep.
   static void decodeSnowAccumulation(
      DtOCEAN2020FOMLandStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);
   
//! Decodes IceAccretion from attrs into rep.
   static void decodeIceAccretion(
      DtOCEAN2020FOMLandStateRepository* rep,
      const RTI::AttributeHandleValuePairSet& attrs,
      int pairSetIndex);

};
 
} //end OCEAN2020
 
#endif
