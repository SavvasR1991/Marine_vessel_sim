/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**hobjEncHeader.tlt
*********************************************************************/
 
//! \file waterSurfaceEncoderHLA.h
//! \brief Contains the DtOCEAN2020FOMWaterSurfaceEncoder class declaration.
 
#pragma once
 
#if DtHLA
 
#include "VS_EnvironmentEncoderHLA.h"
#include "dllExport.h"
 
namespace OCEAN2020 {
 
class DtOCEAN2020FOMWaterSurfaceStateRepository;
 
//! Instances of DtOCEAN2020FOMWaterSurfaceEncoder encode data
//! from DtOCEAN2020FOMWaterSurfaceStateRepository objects to the net
//! structures to be sent to the network.
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtOCEAN2020FOMWaterSurfaceEncoder : public DtOCEAN2020FOMVS_EnvironmentEncoder
{
public:
 
   //! Default constructor.
   DtOCEAN2020FOMWaterSurfaceEncoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMWaterSurfaceEncoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMWaterSurfaceEncoder(const DtOCEAN2020FOMWaterSurfaceEncoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMWaterSurfaceEncoder& operator=(const DtOCEAN2020FOMWaterSurfaceEncoder& orig);
 
public:
   //! Function that creates a DtOCEAN2020FOMWaterSurfaceEncoder.
   static DtHlaStateEncoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
   
protected:

   //! Return true if BreakingWaveZone needs to be sent
   //! to the network, false otherwise.
   static bool needBreakingWaveZone(
      const DtOCEAN2020FOMWaterSurfaceStateRepository& stateRep, 
      const DtOCEAN2020FOMWaterSurfaceStateRepository& asSeenByRemote);
 
   //! Encodes BreakingWaveZone from rep into attrs.
   static void encodeBreakingWaveZone(
      const DtOCEAN2020FOMWaterSurfaceStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if Wave_frequency needs to be sent
   //! to the network, false otherwise.
   static bool needWave_frequency(
      const DtOCEAN2020FOMWaterSurfaceStateRepository& stateRep, 
      const DtOCEAN2020FOMWaterSurfaceStateRepository& asSeenByRemote);
 
   //! Encodes Wave_frequency from rep into attrs.
   static void encodeWave_frequency(
      const DtOCEAN2020FOMWaterSurfaceStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if Wave_height needs to be sent
   //! to the network, false otherwise.
   static bool needWave_height(
      const DtOCEAN2020FOMWaterSurfaceStateRepository& stateRep, 
      const DtOCEAN2020FOMWaterSurfaceStateRepository& asSeenByRemote);
 
   //! Encodes Wave_height from rep into attrs.
   static void encodeWave_height(
      const DtOCEAN2020FOMWaterSurfaceStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if Wave_direction needs to be sent
   //! to the network, false otherwise.
   static bool needWave_direction(
      const DtOCEAN2020FOMWaterSurfaceStateRepository& stateRep, 
      const DtOCEAN2020FOMWaterSurfaceStateRepository& asSeenByRemote);
 
   //! Encodes Wave_direction from rep into attrs.
   static void encodeWave_direction(
      const DtOCEAN2020FOMWaterSurfaceStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

};
 
} //end OCEAN2020
 
#endif
