/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file areaStateRepository.h
//! \brief Contains the DtOCEAN2020FOMAreaStateRepository class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once

//Project include
#include "DataTypes/OCEAN2020FOM_SISOSTD00112015Enums.h"
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <matrix/vlVector.h>
#include <vector>
#include <vl\entityStateRepository.h>
#include <vl/globalObjectDesignator.h>
#include <vl/hlaLogicalTime.h>
#include <vl/hlaLogicalTimeInterval.h>
#include <vlpi/entityIdentifier.h>
#include <vlpi/entityType.h>
#include <vlutil/vlString.h>
 

namespace OCEAN2020 {
 
//! Instances of DtOCEAN2020FOMAreaStateRepository are used to store state data for
//! BaseEntity.PhysicalEntity.Sensor.Area objects.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMAreaStateRepository : public DtEntityStateRepository
{
public:
   //! Constructor.
   DtOCEAN2020FOMAreaStateRepository();
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMAreaStateRepository();
 
   //! Copy Constructor.
   DtOCEAN2020FOMAreaStateRepository(const DtOCEAN2020FOMAreaStateRepository& orig);
 
   //! Assignment Operator.
   DtOCEAN2020FOMAreaStateRepository& operator=(const DtOCEAN2020FOMAreaStateRepository& orig);
 
   //! Return a copy/empty object of the same type as this.
   virtual DtStateRepository* clone(bool copy) const;
 
   //! Create a DtOCEAN2020FOMAreaStateRepository.
   static DtOCEAN2020FOMAreaStateRepository* create();
   
   //! Print data to the DtInfo stream
   virtual void printData() const;
 
   //! Print data to the specified stream
   virtual void printDataToStream(std::ostream& stream) const;
 

   //! Set the Area_Id.
   virtual void setArea_Id(DtInt32 val);
 
   //! Get the Area_Id."
   virtual DtInt32 area_Id() const;

   //! Set the Area_Type.
   virtual void setArea_Type(DtInt32 val);
 
   //! Get the Area_Type."
   virtual DtInt32 area_Type() const;

   //! Set the Vertices.
   virtual void setVertices(const DtString& val);
 
   //! Get the Vertices."
   virtual const DtString& vertices() const;

protected:
   DtInt32 myArea_Id;
   DtInt32 myArea_Type;
   DtString myVertices;
};

} //end OCEAN2020
