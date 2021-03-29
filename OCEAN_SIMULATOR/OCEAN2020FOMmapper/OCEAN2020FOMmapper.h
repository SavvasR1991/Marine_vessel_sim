/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25 
#
# Copyright (c) 2019 ANTYCIP SIMULATION 
#*******************************************************************************-*/

//! \file OCEAN2020FOMmapper.h
//! \brief override default RPR FOM standard FOM mapper with OCEAN2020 custom FOM classes


#pragma once

#if DtHLA 

//Project include
#include "dllExport.h"

//VRLINK include
#include <vl/rprFomMapper.h>

namespace OCEAN2020
{
	class DT_DLL_OCEAN2020FOM OCEAN2020_FomMapper : public DtRprFomMapper
	{
	public:

		//! Constructor
		//! version 2.0 and revision 3 match the RPR FOM from SISO standard RPR_FOM_v2.0_1516-2010.xml
		//! Note that current VR-LINK based class DtRpRFomMapper will trigger a RTI notification error
		//! for Aggregate Entity Decoder related to attribute VariableDatums_RPR2
		//! This notification error is on roadmap to be solved for next VR-Link 5.4.1 patch release
		//! Not a blocking issue for OCEAN2020 federation.
		OCEAN2020_FomMapper(double vers = 2.0, int rev = 3);

		//! Destructor
		virtual ~OCEAN2020_FomMapper();

		//! Virtual function override.  init actually initializes most data.  It is
		//! called from DtExerciseConn constructor.  Required.
		virtual void init(DtExerciseConn* conn);

	protected:

		//! copy constructor - Not Implemented
		OCEAN2020_FomMapper(const OCEAN2020_FomMapper&orig);

		//! assignment operator - Not Implemented
		OCEAN2020_FomMapper &operator=(const OCEAN2020_FomMapper &orig);

	};

}

#endif
