/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/

//! \file reflectedOCEAN2020RadioReceiverListHLA.h
//! \brief Contains the DtReflectedOCEAN2020FOMRadioReceiverList class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015

#pragma once

#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"
#include "reflectedOCEAN2020RadioReceiverHLA.h"

//VRLINK include
#include <vl/reflectedRadioReceiverListHLA.h>

namespace OCEAN2020 {

	//! Instances of DtReflectedOCEAN2020FOMRadioReceiverList manage a list of
	//! DtReflectedOCEAN2020FOMRadioReceiver objects.
	//! \ingroup OCEAN2020FOM_SISOSTD00112015
	class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtReflectedOCEAN2020FOMRadioReceiverList : public DtReflectedRadioReceiverList
	{
	public:
		//! Constructor. 
		DtReflectedOCEAN2020FOMRadioReceiverList(
			DtExerciseConn* exConn,
			const DtDDMRegionSet* regionSetToUse = 0,
			const DtString &updateRateTag = DtString(""));

		//! Constructor - only subscribe to the RTI::ObjectClassHandles
		//! in handleList.
		DtReflectedOCEAN2020FOMRadioReceiverList(
			DtExerciseConn* exConn,
			const DtList *handleList,
			const DtDDMRegionSet* regionSetToUse = 0,
			const DtString &updateRateTag = DtString(""));

		//! Destructor.
		virtual ~DtReflectedOCEAN2020FOMRadioReceiverList();

	protected:

		//! Copy constructor -  not implemented - cannot be copied.
		DtReflectedOCEAN2020FOMRadioReceiverList(const DtReflectedOCEAN2020FOMRadioReceiverList& orig);

		//! Assignment operator -  not implemented - cannot be copied.
		DtReflectedOCEAN2020FOMRadioReceiverList& operator=(const DtReflectedOCEAN2020FOMRadioReceiverList&orig);

		//! Override of virtual function.  Here, we create a DtReflectedOCEAN2020FOMRadioReceiver
		virtual DtReflectedObject* newReflectedObject(DtHlaObject* obj) const;

		//! Called from processDiscoverObject() after a remote OCEAN2020RadioReceiver has
		//! been added to the list.  Default implementation prints a message.
		//! Subclasses can override this function to add functionality on
		//! addition.  obj will be an instance of a class derived from DtReflectedObj.
		virtual void objectAdded(DtReflectedObject* obj);

	public:

		//! Look up by identifier.
		virtual DtReflectedOCEAN2020FOMRadioReceiver* lookup(
#if DtHLA_1516
			RTI::ObjectInstanceHandle id);
#else
			RTI::ObjectHandle id);
#endif

		//! Look up by name.
		virtual DtReflectedOCEAN2020FOMRadioReceiver* lookup(
			const DtGlobalObjectDesignator& objName);

		//! Get the first reflected object in the list.
		virtual DtReflectedOCEAN2020FOMRadioReceiver* first() const;

		//! Get the last reflected object in the list.
		virtual DtReflectedOCEAN2020FOMRadioReceiver* last() const;

		//! OCEAN2020RadioReceiver added callback registration
		virtual void addOCEAN2020RadioReceiverAdditionCallback(
			DtOCEAN2020FOMRadioReceiverCallbackFunction cb, void* userData);

		//! OCEAN2020RadioReceiver added callback deregistration
		virtual void removeOCEAN2020RadioReceiverAdditionCallback(
			DtOCEAN2020FOMRadioReceiverCallbackFunction cb, void* userData);

		//! OCEAN2020RadioReceiver removed callback registration
		virtual void addOCEAN2020RadioReceiverRemovalCallback(
			DtOCEAN2020FOMRadioReceiverCallbackFunction cb, void* userData);

		//! OCEAN2020RadioReceiver removed callback deregistration
		virtual void removeOCEAN2020RadioReceiverRemovalCallback(
			DtOCEAN2020FOMRadioReceiverCallbackFunction cb, void* userData);

	};

} //end OCEAN2020

#endif
