/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/

//! \file reflectedOCEAN2020EntityHLA.h
//! \brief Contains the DtReflectedOCEAN2020Entity class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015

#pragma once

#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"
#include "OCEAN2020EntityStateRepository.h"

//VRLINK include
#include <vl/reflectedEntityHLA.h>

namespace OCEAN2020 {

	class DtReflectedOCEAN2020Entity;

	//! Signature of the callback function that takes a DtReflectedOCEAN2020Entity
	//! and user data
	//! \ingroup OCEAN2020FOM_SISOSTD00112015
	typedef void(*DtOCEAN2020EntityCallbackFunction)(
		DtReflectedOCEAN2020Entity* obj, void* userData);

	//! Instances of DtReflectedOCEAN2020Entity are used to represent a simulation 
	//! entity reflected across a network (i.e. this is not a full 
	//! simulation running on this machine).
	//! \ingroup OCEAN2020FOM_SISOSTD00112015
	class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtReflectedOCEAN2020Entity : public DtReflectedEntity
	{
	public:
		//! Function prototype for functions that create a
		//! DtOCEAN2020EntityStateRepository.
		typedef DtOCEAN2020EntityStateRepository* (*DtStateRepCreator)();

	public:
		//! Constructor.
		DtReflectedOCEAN2020Entity(DtHlaObject* obj, DtExerciseConn* exConn);

		//! Constructor with state rep to use passed in Note that setHlaObject() 
		//! should be called after a reflected entity is created with this method.
		DtReflectedOCEAN2020Entity(DtExerciseConn *exConn, DtOCEAN2020EntityStateRepository *esrToUse);

		//! Constructor with entity state repository creator passed in.
		DtReflectedOCEAN2020Entity(DtHlaObject *obj, DtExerciseConn *exConn, DtBaseStateRepCreator esrToUse);

		//! Destructor.
		virtual ~DtReflectedOCEAN2020Entity();

		//! Set the function to be called for creating state repositories.
		static DtStateRepCreator setStateRepCreator(DtStateRepCreator creator);

		//! Returns the OCEAN2020Entity's state repository.
		virtual DtOCEAN2020EntityStateRepository* OCEAN2020EntityReceiverStateRep() const;

		//! Shorter version of lifeformRep.
		virtual DtOCEAN2020EntityStateRepository* OEsr() const;

		//! Returns the next reflected OCEAN2020Entity in the 
		//! DtReflectedOCEAN2020EntityList.
		virtual DtReflectedOCEAN2020Entity* next() const;

		//! Returns the previous reflected OCEAN2020Entity in the 
		//! DtReflectedOCEAN2020EntityList.
		virtual DtReflectedOCEAN2020Entity* prev() const;

		//! Returns the next reflected OCEAN2020Entity. Will cycle back to the first 
		//! remote OCEAN2020Entity in the DtReflectedOCEAN2020EntityList.
		virtual DtReflectedOCEAN2020Entity* wrapNext() const;

		//! Returns the previous reflected OCEAN2020Entity. Will cycle back to the first 
		//! remote OCEAN2020Entity in the DtReflectedOCEAN2020EntityList.
		virtual DtReflectedOCEAN2020Entity* wrapPrev() const;

		//! Add a callback that is called when the DtReflectedOCEAN2020Entity is
		//! updated.
		virtual void addPostUpdateCallback(
			DtOCEAN2020EntityCallbackFunction cb, void* userData);

		//! Remove the callback that is called when the DtReflectedOCEAN2020Entity
		//! is updated.
		virtual void removePostUpdateCallback(
			DtOCEAN2020EntityCallbackFunction cb, void* userData);


	protected:
		//! Copy Constructor not implemented.
		DtReflectedOCEAN2020Entity(const DtReflectedOCEAN2020Entity& orig);

		//! Assignment operator not implemented.
		DtReflectedOCEAN2020Entity& operator=(const DtReflectedOCEAN2020Entity& orig);

	protected:
		//! The function called to create state repositories.
		static DtStateRepCreator theStateRepCreator;
	};

	inline DtOCEAN2020EntityStateRepository* DtReflectedOCEAN2020Entity::OCEAN2020EntityReceiverStateRep() const
	{
		return (DtOCEAN2020EntityStateRepository*)myStateRep;
	}

	inline DtOCEAN2020EntityStateRepository* DtReflectedOCEAN2020Entity::OEsr() const
	{
		return (DtOCEAN2020EntityStateRepository*)myStateRep;
	}

} //end OCEAN2020

#endif
