/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**stateRepHeader.tlt
*********************************************************************/
 
//! \file waterColumnStateRepository.h
//! \brief Contains the DtOCEAN2020FOMWaterColumnStateRepository class declaration.
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
 
//! Instances of DtOCEAN2020FOMWaterColumnStateRepository are used to store state data for
//! VS_Environment.WaterColumn objects.
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtOCEAN2020FOMWaterColumnStateRepository : public DtOCEAN2020FOMVS_EnvironmentStateRepository
{
public:
   //! Constructor.
   DtOCEAN2020FOMWaterColumnStateRepository();
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMWaterColumnStateRepository();
 
   //! Copy Constructor.
   DtOCEAN2020FOMWaterColumnStateRepository(const DtOCEAN2020FOMWaterColumnStateRepository& orig);
 
   //! Assignment Operator.
   DtOCEAN2020FOMWaterColumnStateRepository& operator=(const DtOCEAN2020FOMWaterColumnStateRepository& orig);
 
   //! Return a copy/empty object of the same type as this.
   virtual DtStateRepository* clone(bool copy) const;
 
   //! Create a DtOCEAN2020FOMWaterColumnStateRepository.
   static DtOCEAN2020FOMWaterColumnStateRepository* create();
   
   //! Print data to the DtInfo stream
   virtual void printData() const;
 
   //! Print data to the specified stream
   virtual void printDataToStream(std::ostream& stream) const;
 

   //! Set the NumberOfLayers.
   virtual void setNumberOfLayers(DtInt32 val);
 
   //! Get the NumberOfLayers."
   virtual DtInt32 numberOfLayers() const;

   //! Set the WaterDepth.
   virtual void setWaterDepth(const DtOCEAN2020FOMVariableLengthFloat32Array& val);
 
   //! Get the WaterDepth."
   virtual const DtOCEAN2020FOMVariableLengthFloat32Array& waterDepth() const;

   //! Set the ShallowerLayer.
   virtual void setShallowerLayer(DtInt32 val);
 
   //! Get the ShallowerLayer."
   virtual DtInt32 shallowerLayer() const;

   //! Set the DeeperLayer.
   virtual void setDeeperLayer(DtInt32 val);
 
   //! Get the DeeperLayer."
   virtual DtInt32 deeperLayer() const;

   //! Set the Current_intensity.
   virtual void setCurrent_intensity(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the Current_intensity."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& current_intensity() const;

   //! Set the Current_direction.
   virtual void setCurrent_direction(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the Current_direction."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& current_direction() const;

   //! Set the Salinity.
   virtual void setSalinity(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the Salinity."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& salinity() const;

   //! Set the Temperature.
   virtual void setTemperature(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the Temperature."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& temperature() const;

   //! Set the Transparency.
   virtual void setTransparency(const DtOCEAN2020FOMVariableLengthFloat64Array& val);
 
   //! Get the Transparency."
   virtual const DtOCEAN2020FOMVariableLengthFloat64Array& transparency() const;

protected:
   DtInt32 myNumberOfLayers;
   DtOCEAN2020FOMVariableLengthFloat32Array myWaterDepth;
   DtInt32 myShallowerLayer;
   DtInt32 myDeeperLayer;
   DtOCEAN2020FOMVariableLengthFloat64Array myCurrent_intensity;
   DtOCEAN2020FOMVariableLengthFloat64Array myCurrent_direction;
   DtOCEAN2020FOMVariableLengthFloat64Array mySalinity;
   DtOCEAN2020FOMVariableLengthFloat64Array myTemperature;
   DtOCEAN2020FOMVariableLengthFloat64Array myTransparency;
};

} //end OCEAN2020
