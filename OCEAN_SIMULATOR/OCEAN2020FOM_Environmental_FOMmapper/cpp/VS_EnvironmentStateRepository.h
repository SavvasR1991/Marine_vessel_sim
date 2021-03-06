/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**stateRepHeader.tlt
*********************************************************************/
 
//! \file VS_EnvironmentStateRepository.h
//! \brief Contains the DtOCEAN2020FOMVS_EnvironmentStateRepository class declaration.
//! \ingroup OCEAN2020FOM_Environmental
 
#pragma once
 
#include "dllExport.h"
#include <vl/stateRepository.h>
#include <matrix/vlVector.h>
#include <vl/globalObjectDesignator.h>
#include <vl/hlaLogicalTime.h>
#include <vl/hlaLogicalTimeInterval.h>
#include <vlpi/entityType.h>
#include <vlpi/entityIdentifier.h>
#include <vlutil/vlString.h>
#include "DataTypes/OCEAN2020FOM_EnvironmentalEnums.h"
#include <vector>
 

namespace OCEAN2020 {
 
//! Instances of DtOCEAN2020FOMVS_EnvironmentStateRepository are used to store state data for
//! VS_Environment objects.
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtOCEAN2020FOMVS_EnvironmentStateRepository : public DtStateRepository
{
public:
   //! Constructor.
   DtOCEAN2020FOMVS_EnvironmentStateRepository();
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMVS_EnvironmentStateRepository();
 
   //! Copy Constructor.
   DtOCEAN2020FOMVS_EnvironmentStateRepository(const DtOCEAN2020FOMVS_EnvironmentStateRepository& orig);
 
   //! Assignment Operator.
   DtOCEAN2020FOMVS_EnvironmentStateRepository& operator=(const DtOCEAN2020FOMVS_EnvironmentStateRepository& orig);
 
   //! Return a copy/empty object of the same type as this.
   virtual DtStateRepository* clone(bool copy) const;
 
   //! Create a DtOCEAN2020FOMVS_EnvironmentStateRepository.
   static DtOCEAN2020FOMVS_EnvironmentStateRepository* create();
   
   //! Print data to the DtInfo stream
   virtual void printData() const;
 
   //! Print data to the specified stream
   virtual void printDataToStream(std::ostream& stream) const;
 

   //! Set the NumRows.
   virtual void setNumRows(DtU32 val);
 
   //! Get the NumRows."
   virtual DtU32 numRows() const;

   //! Set the NumColumns.
   virtual void setNumColumns(DtU32 val);
 
   //! Get the NumColumns."
   virtual DtU32 numColumns() const;

   //! Set the NWCornerLatitude.
   virtual void setNWCornerLatitude(DtFloat64 val);
 
   //! Get the NWCornerLatitude."
   virtual DtFloat64 NWCornerLatitude() const;

   //! Set the NWCornerLongitude.
   virtual void setNWCornerLongitude(DtFloat64 val);
 
   //! Get the NWCornerLongitude."
   virtual DtFloat64 NWCornerLongitude() const;

   //! Set the SECornerLatitude.
   virtual void setSECornerLatitude(DtFloat64 val);
 
   //! Get the SECornerLatitude."
   virtual DtFloat64 SECornerLatitude() const;

   //! Set the SECornerLongitude.
   virtual void setSECornerLongitude(DtFloat64 val);
 
   //! Get the SECornerLongitude."
   virtual DtFloat64 SECornerLongitude() const;

protected:
   DtU32 myNumRows;
   DtU32 myNumColumns;
   DtFloat64 myNWCornerLatitude;
   DtFloat64 myNWCornerLongitude;
   DtFloat64 mySECornerLatitude;
   DtFloat64 mySECornerLongitude;
};

} //end OCEAN2020
