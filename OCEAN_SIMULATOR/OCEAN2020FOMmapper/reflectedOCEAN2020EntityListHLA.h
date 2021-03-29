/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/

//! \file reflectedOCEAN2020EntityListHLA.h
//! \brief Contains the DtReflectedOCEAN2020EntityList class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015

#pragma once

#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"
#include "reflectedOCEAN2020EntityHLA.h"

//VRLINK include
#include <vl/reflectedEntityListHLA.h>

namespace OCEAN2020 {

	//! Instances of DtReflectedOCEAN2020EntityList manage a list of
	//! DtReflectedOCEAN2020Entity objects.
	//! \ingroup OCEAN2020FOM_SISOSTD00112015
	class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtReflectedOCEAN2020EntityList : public DtReflectedEntityList
	{
	public:

		//! Constructor that uses subscription criteria from the exConn's fomMapper.
		DtReflectedOCEAN2020EntityList(
			DtExerciseConn *exConn, 
			bool smoothCapable = false, 
			const DtDDMRegionSet *regionSetToUse = 0);

		//! Constructor. 
		DtReflectedOCEAN2020EntityList(
			DtExerciseConn *exConn, 
			const DtString &updateRateTag, 
			bool smoothCapable = false, 
			const DtDDMRegionSet *regionSetToUse = 0);

		//! Constructor that uses a handle list as subscription criteria.
		DtReflectedOCEAN2020EntityList(
			DtExerciseConn *exConn, 
			const DtList *handleList, 
			bool smoothCapable = false, 
			const DtDDMRegionSet *regionSetToUse = 0);

		//! Constructor. 
		DtReflectedOCEAN2020EntityList(
			DtExerciseConn *exConn, 
			const DtList *handleList, 
			const DtString &updateRateTag, 
			bool smoothCapable = false, 
			const DtDDMRegionSet *regionSetToUse = 0);

		//! Destructor.
		virtual ~DtReflectedOCEAN2020EntityList();

	protected:

		//! Copy constructor -  not implemented - cannot be copied.
		DtReflectedOCEAN2020EntityList(const DtReflectedOCEAN2020EntityList& orig);

		//! Assignment operator -  not implemented - cannot be copied.
		DtReflectedOCEAN2020EntityList& operator=(const DtReflectedOCEAN2020EntityList&orig);

		//! Override of virtual function.  Here, we create a DtReflectedOCEAN2020Entity
		virtual DtReflectedObject* newReflectedObject(DtHlaObject* obj) const;

		//! Create a remote OCEAN2020entity object for the HLA object.
		virtual DtReflectedEntity* newReflectedEntity(DtHlaObject *obj) const;

		//! Create a remote OCEAN2020entity object for the HLA object.
		virtual DtReflectedOCEAN2020Entity* newReflectedOCEAN2020Entity(DtHlaObject *obj) const;

		////! Called from processDiscoverObject() after a remote OCEAN2020entity has
		////! been added to the list.  Default implementation prints a message.
		////! Subclasses can override this function to add functionality on
		////! addition.  obj will be an instance of a class derived from DtReflectedObj.
		//virtual void objectAdded(DtReflectedObject* obj);

		////! Called by objectAdded (which is called from processDiscoverObject()) after a remote entity has been added to the list. 
		//virtual void entityAdded(DtReflectedEntity *ent);

	public:

		//! Look up by identifier.
		virtual  DtReflectedOCEAN2020Entity* lookup(
#if DtHLA_1516
			RTI::ObjectInstanceHandle id);
#else
			RTI::ObjectHandle id);
#endif

		//! Look up by name.
		virtual  DtReflectedOCEAN2020Entity* lookup(const DtGlobalObjectDesignator& objName);

		//! Look up by entity Id.
		virtual  DtReflectedOCEAN2020Entity* lookup(const DtEntityIdentifier &entityId);

		//! Get the first reflected object in the list.
		virtual  DtReflectedOCEAN2020Entity* first() const;

		//! Get the last reflected object in the list.
		virtual  DtReflectedOCEAN2020Entity* last() const;

		//! OCEAN2020Entity added callback registration
		virtual void addOCEAN2020EntityAdditionCallback(DtOCEAN2020EntityCallbackFunction cb, void* userData);

		//! OCEAN2020Entity added callback deregistration
		virtual void removeOCEAN2020EntityAdditionCallback(DtOCEAN2020EntityCallbackFunction cb, void* userData);

		//! OCEAN2020Entity removed callback registration
		virtual void addOCEAN2020EntityRemovalCallback(DtOCEAN2020EntityCallbackFunction cb, void* userData);

		//! OCEAN2020Entity removed callback deregistration
		virtual void removeOCEAN2020EntityRemovalCallback(DtOCEAN2020EntityCallbackFunction cb, void* userData);

	};

} //end OCEAN2020

#endif
