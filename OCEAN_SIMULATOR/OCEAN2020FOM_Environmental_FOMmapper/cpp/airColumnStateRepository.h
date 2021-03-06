/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**stateRepHeader.tlt
*********************************************************************/
 
//! \file airColumnStateRepository.h
//! \brief Contains the DtOCEAN2020FOMAirColumnStateRepository class declaration.
//! \ingroup OCEAN2020FOM_Environmental
 
#pragma once
 
#include "dllExport.h"
#include "VS_EnvironmentStateRepository.h"
#include <matrix/vlVector.h>
#include <vl/globalObjectDesignator.h>
#include <vl/hlaLogicalTime.h>
#include <vl/hlaLogicalTimeInterval.h>
#include <vlpi/entityType.h>
#include <vlpi/entityIdentifier.h>
#include <vlutil/vlString.h>
#include "DataTypes/OCEAN2020FOM_EnvironmentalEnums.h"
#include <vector>
 
#include "DataTypes/OCEAN2020FOMVariableLengthFloat32Array.h"
#include "DataTypes/OCEAN2020FOMVariableLengthFloat64Array.h"

namespace OCEAN2020 {
 
//! Instances of DtOCEAN2020FOMAirColumnStateRepository are used to store state data for
//! VS_Environment.AirColumn objects.
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtOCEAN2020FOMAirColumnStateRepository : public DtOCEAN2020FOMVS_EnvironmentStateRepository
{
public:
   //! Constructor.
   DtOCEAN2020FOMAirColumnStateRepository();
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMAirColumnStateRepository();
 
   //! Copy Constructor.
   DtOCEAN2020FOMAirColumnStateRepository(const DtOCEAN2020FOMAirColumnStateRepository& orig);
 
   //! Assignment Operator.
   DtOCEAN2020FOMAirColumnStateRepository& operator=(const DtOCEAN2020FOMAirColumnStateRepository& orig);
 
   //! Return a copy/empty object of the same type as this.
   virtual DtStateRepository* clone(bool copy) const;
 
   //! Create a DtOCEAN2020FOMAirColumnStateRepository.
   static DtOCEAN2020FOMAirColumnStateRepository* create();
   
   //! Print data to the DtInfo stream
   virtual void printData() const;
 
   //! Print data to the specified stream
   virtual void printDataToStream(std::ostream& stream) const;
 

   //! Set the NumberOfLayers.
   virtual void setNumberOfLayers(DtInt32 val);
 
   //! Get the NumberOfLayers."
   virtual DtInt32 numberOfLayers() const;

   //! Set the LowerLayer.
   virtual void setLowerLayer(DtFloat64 val);
 
   //! Get the LowerLayer."
   virtual DtFloat64 lowerLayer() const;

   //! Set the HigherLayer.
   virtual void setHigherLayer(DtFloat64 val);
 
   //! Get the HigherLayer."
   virtual DtFloat64 higherLayer() const;

   //! Set the Layers.
   virtual void setLayers(const DtOCEAN2020FOMVariableLengthFloat32Array& val);
 
   //! Get the Layers."
   virtual const DtOCEAN2020FOMVariableLengthFloat32Array& layers() const;

   //! Set the SunAzimuth.
   virtual void setSunAzimuth(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the SunAzimuth."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& sunAzimuth() const;

   //! Set the SunElevation.
   virtual void setSunElevation(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the SunElevation."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& sunElevation() const;

   //! Set the FogCloudDensity.
   virtual void setFogCloudDensity(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the FogCloudDensity."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& fogCloudDensity() const;

   //! Set the GustDirection.
   virtual void setGustDirection(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the GustDirection."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& gustDirection() const;

   //! Set the GustDuration.
   virtual void setGustDuration(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the GustDuration."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& gustDuration() const;

   //! Set the GustIntensity.
   virtual void setGustIntensity(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the GustIntensity."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& gustIntensity() const;

   //! Set the RainfallRate.
   virtual void setRainfallRate(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the RainfallRate."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& rainfallRate() const;

   //! Set the RelativeHumidity.
   virtual void setRelativeHumidity(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the RelativeHumidity."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& relativeHumidity() const;

   //! Set the SnowfallRate.
   virtual void setSnowfallRate(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the SnowfallRate."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& snowfallRate() const;

   //! Set the SolarRadiation.
   virtual void setSolarRadiation(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the SolarRadiation."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& solarRadiation() const;

   //! Set the SustainedWindDirection.
   virtual void setSustainedWindDirection(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the SustainedWindDirection."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& sustainedWindDirection() const;

   //! Set the SustainedWindIntensity.
   virtual void setSustainedWindIntensity(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the SustainedWindIntensity."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& sustainedWindIntensity() const;

   //! Set the Temperature.
   virtual void setTemperature(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the Temperature."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& temperature() const;

   //! Set the WindShear.
   virtual void setWindShear(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the WindShear."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& windShear() const;

   //! Set the Pressure.
   virtual void setPressure(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the Pressure."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& pressure() const;

protected:
   DtInt32 myNumberOfLayers;
   DtFloat64 myLowerLayer;
   DtFloat64 myHigherLayer;
   DtOCEAN2020FOMVariableLengthFloat32Array myLayers;
   DtOCEAN2020FOMVariableLengthFloat64Array mySunAzimuth;
   DtOCEAN2020FOMVariableLengthFloat64Array mySunElevation;
   DtOCEAN2020FOMVariableLengthFloat64Array myFogCloudDensity;
   DtOCEAN2020FOMVariableLengthFloat64Array myGustDirection;
   DtOCEAN2020FOMVariableLengthFloat64Array myGustDuration;
   DtOCEAN2020FOMVariableLengthFloat64Array myGustIntensity;
   DtOCEAN2020FOMVariableLengthFloat64Array myRainfallRate;
   DtOCEAN2020FOMVariableLengthFloat64Array myRelativeHumidity;
   DtOCEAN2020FOMVariableLengthFloat64Array mySnowfallRate;
   DtOCEAN2020FOMVariableLengthFloat64Array mySolarRadiation;
   DtOCEAN2020FOMVariableLengthFloat64Array mySustainedWindDirection;
   DtOCEAN2020FOMVariableLengthFloat64Array mySustainedWindIntensity;
   DtOCEAN2020FOMVariableLengthFloat64Array myTemperature;
   DtOCEAN2020FOMVariableLengthFloat64Array myWindShear;
   DtOCEAN2020FOMVariableLengthFloat64Array myPressure;
};

} //end OCEAN2020
