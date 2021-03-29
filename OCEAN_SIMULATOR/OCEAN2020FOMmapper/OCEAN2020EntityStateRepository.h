/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/

//! \file OCEAN2020EntityStateRepository.h
//! \brief Contains the DtOCEAN2020EntityStateRepository class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015

#pragma once

//Project include
#include "DataTypes/OCEAN2020FOM_SISOSTD00112015Enums.h"
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <matrix/vlVector.h>
#include <vector>
#include <vl/entityStateRepository.h>
#include <vl/globalObjectDesignator.h>
#include <vl/hlaLogicalTime.h>
#include <vl/hlaLogicalTimeInterval.h>
#include <vlpi/entityIdentifier.h>
#include <vlpi/entityType.h>
#include <vlutil/vlString.h>


namespace OCEAN2020 {

	//! Instances of DtOCEAN2020EntityStateRepository are used to store state data for
	//! OCEAN2020 custom BaseEntity.PhysicalEntity.Platform.* objects.
	//! \ingroup OCEAN2020FOM_SISOSTD00112015
	class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020EntityStateRepository : public DtEntityStateRepository
	{
	public:
		//! Constructor.
		DtOCEAN2020EntityStateRepository();

		//! Destructor.
		virtual ~DtOCEAN2020EntityStateRepository();

		//! Copy Constructor.
		DtOCEAN2020EntityStateRepository(const DtOCEAN2020EntityStateRepository& orig);

		//! Assignment Operator.
		DtOCEAN2020EntityStateRepository& operator=(const DtOCEAN2020EntityStateRepository& orig);

		//! Return a copy/empty object of the same type as this.
		virtual DtStateRepository* clone(bool copy) const;

		//! Create a DtOCEAN2020EntityStateRepository.
		static DtOCEAN2020EntityStateRepository* create();

		//! Print data to the DtInfo stream
		virtual void printData() const;

		//! Print data to the specified stream
		virtual void printDataToStream(std::ostream& stream) const;

		//! Set the ASBHeight.
		virtual void setASBHeight(DtFloat64 val);

		//! Get the ASBHeight.
		virtual DtFloat64 ASBHeight() const;

		//! Set the DimensionLength.
		virtual void setDimensionLength(DtFloat32 val);

		//! Get the DimensionLength.
		virtual DtFloat32 dimensionLength() const;

		//! Set the DimensionWidth.
		virtual void setDimensionWidth(DtFloat32 val);

		//! Get the DimensionWidth.
		virtual DtFloat32 dimensionWidth() const;

		//! Set the DimensionHeight.
		virtual void setDimensionHeight(DtFloat32 val);

		//! Get the DimensionHeight.
		virtual DtFloat32 dimensionHeight() const;

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
		DtFloat64 myASBHeight;
		DtFloat32 myDimensionLength;
		DtFloat32 myDimensionWidth;
		DtFloat32 myDimensionHeight;
		DtInt32 myArea_Id;
		DtInt32 myArea_Type;
		DtString myVertices;
	};

} //end OCEAN2020
