/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/

//! \file OCEAN2020EntityPublisherHLA.h
//! \brief Contains the DtOCEAN2020FOMEntityPublisher class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015

#pragma once

#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl/entityPublisherHLA.h>

namespace OCEAN2020 {

	class DtOCEAN2020EntityStateRepository;

	//! Instances of DtOCEAN2020FOMEntityPublisher publish
	//! EmbeddedSystem.Entity.OCEAN2020Entity objects to
	//! the network.
	//! \ingroup OCEAN2020FOM_SISOSTD00112015
	class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020EntityPublisher : public DtEntityPublisher
	{
	public:
		//! Function prototype for a function that creates a DtOCEAN2020FOMEntityStateRepository
		typedef DtOCEAN2020EntityStateRepository* (*DtStateRepCreator)();

	public:
		//! Constructor.
		DtOCEAN2020EntityPublisher(
			DtOCEAN2020EntityStateRepository* stateRepToUse,
			DtExerciseConn* conn,
			const char* name = 0,
			const DtDDMRegionSet* regionSetToUse = 0);

		//! Constructor.
		DtOCEAN2020EntityPublisher(
			RTI::ObjectClassHandle handle,
			DtExerciseConn* conn,
			const char* name = 0,
			const DtDDMRegionSet* regionSetToUse = 0);

		//! Constructor.
		DtOCEAN2020EntityPublisher(
			const DtEntityType &type,
			DtExerciseConn *conn,
			const char *name = 0,
			const DtDDMRegionSet *regionSetToUse = 0);

		//! Constructor.
		DtOCEAN2020EntityPublisher(
			const DtEntityType &type,
			DtExerciseConn *conn,
			DtDeadReckonTypes algorithm,
			DtForceType forceId,
			const DtEntityType &guise = guiseSameAsType(),
			const char *name = 0,
			const DtDDMRegionSet *regionSetToUse = 0);

		//! Constructor that creates a publisher for an existing DtHlaObject.
		//! (DtHlaObjectWithStateRep is derived from DtHlaObject.)  Typically used
		//! in conjunction with ownership management, when you want to take
		//! ownership and begin updating some attributes of an object that you have
		//! already discovered.
		DtOCEAN2020EntityPublisher(DtHlaObjectWithStateRep* obj, DtExerciseConn* conn);

		//! Destructor.
		virtual ~DtOCEAN2020EntityPublisher();

		virtual void setHlaObject(
			const char *className, 
			DtHlaStateEncoder *encoder = 0, 
			DtHlaStateDecoder *decoder = 0, 
			const char *objectName = 0, 
			const DtDDMRegionSet *regionSet = 0);

		virtual void setHlaObject(
			RTI::ObjectClassHandle hand,
			DtHlaStateEncoder *encoder = 0,
			DtHlaStateDecoder *decoder = 0,
			const char *objectName = 0,
			const DtDDMRegionSet *regionSet = 0);

		virtual void setHlaObject(
			DtHlaObjectWithStateRep *obj, 
			DtHlaStateEncoder *encoder = 0, 
			DtHlaStateDecoder *decoder = 0);

	protected:
		DtOCEAN2020EntityPublisher(const char *name = 0, const DtDDMRegionSet *regionSetToUse = 0);

		//! Copy Constructor -- not implemented.
		DtOCEAN2020EntityPublisher(const DtOCEAN2020EntityPublisher& orig);

		//! Assignment operator -- not implemented.
		DtOCEAN2020EntityPublisher& operator=(
			const DtOCEAN2020EntityPublisher& orig);

		const char* objectClassNameFromType(const DtEntityType &type);

	public:

		//! Returns a pointer to the DtOCEAN2020EntityStateRepository - through
		//! which you can set or inspect current state information.
		virtual DtOCEAN2020EntityStateRepository* OCEAN2020EntityStateRep();

		//! Synonym for OCEAN2020EntityStateRep().
		virtual DtOCEAN2020EntityStateRepository* Osr();

	public:
		//! Give us a function to be used for creating SRs.
		static DtStateRepCreator setStateRepCreator(DtStateRepCreator creator);

	protected:
		static DtStateRepCreator theStateRepCreator;
	};

	inline DtOCEAN2020EntityStateRepository* DtOCEAN2020EntityPublisher::OCEAN2020EntityStateRep()
	{
		return (DtOCEAN2020EntityStateRepository*)myStateRep;
	}

	inline DtOCEAN2020EntityStateRepository* DtOCEAN2020EntityPublisher::Osr()
	{
		return (DtOCEAN2020EntityStateRepository*)myStateRep;
	}

} //end OCEAN2020

#endif
