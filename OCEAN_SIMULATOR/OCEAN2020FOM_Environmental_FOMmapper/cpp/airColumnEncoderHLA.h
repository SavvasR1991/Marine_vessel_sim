/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**hobjEncHeader.tlt
*********************************************************************/
 
//! \file airColumnEncoderHLA.h
//! \brief Contains the DtOCEAN2020FOMAirColumnEncoder class declaration.
 
#pragma once
 
#if DtHLA
 
#include "VS_EnvironmentEncoderHLA.h"
#include "dllExport.h"
 
namespace OCEAN2020 {
 
class DtOCEAN2020FOMAirColumnStateRepository;
 
//! Instances of DtOCEAN2020FOMAirColumnEncoder encode data
//! from DtOCEAN2020FOMAirColumnStateRepository objects to the net
//! structures to be sent to the network.
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtOCEAN2020FOMAirColumnEncoder : public DtOCEAN2020FOMVS_EnvironmentEncoder
{
public:
 
   //! Default constructor.
   DtOCEAN2020FOMAirColumnEncoder(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMAirColumnEncoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMAirColumnEncoder(const DtOCEAN2020FOMAirColumnEncoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMAirColumnEncoder& operator=(const DtOCEAN2020FOMAirColumnEncoder& orig);
 
public:
   //! Function that creates a DtOCEAN2020FOMAirColumnEncoder.
   static DtHlaStateEncoder* create(
      DtExerciseConn* exConn,
      DtObjClassDesc* classDesc);
   
protected:

   //! Return true if NumberOfLayers needs to be sent
   //! to the network, false otherwise.
   static bool needNumberOfLayers(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes NumberOfLayers from rep into attrs.
   static void encodeNumberOfLayers(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if LowerLayer needs to be sent
   //! to the network, false otherwise.
   static bool needLowerLayer(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes LowerLayer from rep into attrs.
   static void encodeLowerLayer(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if HigherLayer needs to be sent
   //! to the network, false otherwise.
   static bool needHigherLayer(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes HigherLayer from rep into attrs.
   static void encodeHigherLayer(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if Layers needs to be sent
   //! to the network, false otherwise.
   static bool needLayers(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes Layers from rep into attrs.
   static void encodeLayers(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if SunAzimuth needs to be sent
   //! to the network, false otherwise.
   static bool needSunAzimuth(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes SunAzimuth from rep into attrs.
   static void encodeSunAzimuth(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if SunElevation needs to be sent
   //! to the network, false otherwise.
   static bool needSunElevation(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes SunElevation from rep into attrs.
   static void encodeSunElevation(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if FogCloudDensity needs to be sent
   //! to the network, false otherwise.
   static bool needFogCloudDensity(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes FogCloudDensity from rep into attrs.
   static void encodeFogCloudDensity(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if GustDirection needs to be sent
   //! to the network, false otherwise.
   static bool needGustDirection(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes GustDirection from rep into attrs.
   static void encodeGustDirection(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if GustDuration needs to be sent
   //! to the network, false otherwise.
   static bool needGustDuration(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes GustDuration from rep into attrs.
   static void encodeGustDuration(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if GustIntensity needs to be sent
   //! to the network, false otherwise.
   static bool needGustIntensity(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes GustIntensity from rep into attrs.
   static void encodeGustIntensity(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if RainfallRate needs to be sent
   //! to the network, false otherwise.
   static bool needRainfallRate(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes RainfallRate from rep into attrs.
   static void encodeRainfallRate(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if RelativeHumidity needs to be sent
   //! to the network, false otherwise.
   static bool needRelativeHumidity(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes RelativeHumidity from rep into attrs.
   static void encodeRelativeHumidity(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if SnowfallRate needs to be sent
   //! to the network, false otherwise.
   static bool needSnowfallRate(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes SnowfallRate from rep into attrs.
   static void encodeSnowfallRate(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if SolarRadiation needs to be sent
   //! to the network, false otherwise.
   static bool needSolarRadiation(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes SolarRadiation from rep into attrs.
   static void encodeSolarRadiation(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if SustainedWindDirection needs to be sent
   //! to the network, false otherwise.
   static bool needSustainedWindDirection(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes SustainedWindDirection from rep into attrs.
   static void encodeSustainedWindDirection(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if SustainedWindIntensity needs to be sent
   //! to the network, false otherwise.
   static bool needSustainedWindIntensity(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes SustainedWindIntensity from rep into attrs.
   static void encodeSustainedWindIntensity(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if Temperature needs to be sent
   //! to the network, false otherwise.
   static bool needTemperature(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes Temperature from rep into attrs.
   static void encodeTemperature(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if WindShear needs to be sent
   //! to the network, false otherwise.
   static bool needWindShear(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes WindShear from rep into attrs.
   static void encodeWindShear(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

   //! Return true if Pressure needs to be sent
   //! to the network, false otherwise.
   static bool needPressure(
      const DtOCEAN2020FOMAirColumnStateRepository& stateRep, 
      const DtOCEAN2020FOMAirColumnStateRepository& asSeenByRemote);
 
   //! Encodes Pressure from rep into attrs.
   static void encodePressure(
      const DtOCEAN2020FOMAirColumnStateRepository& rep,
      RTI::AttributeHandleValuePairSet* attrs,
      RTI::AttributeHandle attrHandle);

};
 
} //end OCEAN2020
 
#endif
