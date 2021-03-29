/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/

//! \file reflectedOCEAN2020RadioTransmitterListHLA.h
//! \brief Contains the DtReflectedOCEAN2020FOMRadioTransmitterList class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015

#pragma once

#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"
#include "reflectedOCEAN2020RadioTransmitterHLA.h"

//VRLINK include
#include <vl/reflectedRadioTransmitterListHLA.h>

namespace OCEAN2020 {

	//! Instances of DtReflectedOCEAN2020FOMRadioTransmitterList manage a list of
	//! DtReflectedOCEAN2020FOMRadioTransmitter objects.
	//! \ingroup OCEAN2020FOM_SISOSTD00112015
	class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtReflectedOCEAN2020FOMRadioTransmitterList : public DtReflectedRadioTransmitterList
	{
	public:
		//! Constructor. 
		DtReflectedOCEAN2020FOMRadioTransmitterList(
			DtExerciseConn* exConn,
			const DtDDMRegionSet* regionSetToUse = 0,
			const DtString &updateRateTag = DtString(""));

		//! Constructor - only subscribe to the RTI::ObjectClassHandles
		//! in handleList.
		DtReflectedOCEAN2020FOMRadioTransmitterList(
			DtExerciseConn* exConn,
			const DtList *handleList,
			const DtDDMRegionSet* regionSetToUse = 0,
			const DtString &updateRateTag = DtString(""));

		//! Destructor.
		virtual ~DtReflectedOCEAN2020FOMRadioTransmitterList();

	private:

		//! Copy constructor not implemented - cannot be copied.
		DtReflectedOCEAN2020FOMRadioTransmitterList(const DtReflectedOCEAN2020FOMRadioTransmitterList& orig);

		//! Assignment operator not implemented - cannot be copied.
		DtReflectedOCEAN2020FOMRadioTransmitterList& operator=(const DtReflectedOCEAN2020FOMRadioTransmitterList&orig);

	public:

		//! Look up by identifier.
		virtual DtReflectedOCEAN2020FOMRadioTransmitter* lookup(
#if DtHLA_1516
			RTI::ObjectInstanceHandle id);
#else
			RTI::ObjectHandle id);
#endif

		//! Look up by name.
		virtual DtReflectedOCEAN2020FOMRadioTransmitter* lookup(
			const DtGlobalObjectDesignator& objName);

		//! Get the first reflected object in the list.
		virtual DtReflectedOCEAN2020FOMRadioTransmitter* first() const;

		//! Get the last reflected object in the list.
		virtual DtReflectedOCEAN2020FOMRadioTransmitter* last() const;

		//! OCEAN2020RadioTransmitter added callback registration
		virtual void addOCEAN2020RadioTransmitterAdditionCallback(
			DtOCEAN2020FOMRadioTransmitterCallbackFunction cb, void* userData);

		//! OCEAN2020RadioTransmitter added callback deregistration
		virtual void removeOCEAN2020RadioTransmitterAdditionCallback(
			DtOCEAN2020FOMRadioTransmitterCallbackFunction cb, void* userData);

		//! OCEAN2020RadioTransmitter removed callback registration
		virtual void addOCEAN2020RadioTransmitterRemovalCallback(
			DtOCEAN2020FOMRadioTransmitterCallbackFunction cb, void* userData);

		//! OCEAN2020RadioTransmitter removed callback deregistration
		virtual void removeOCEAN2020RadioTransmitterRemovalCallback(
			DtOCEAN2020FOMRadioTransmitterCallbackFunction cb, void* userData);

	protected:

		//! Override of virtual function.  Here, we create a DtReflectedOCEAN2020FOMRadioTransmitter
		virtual DtReflectedObject* newReflectedObject(DtHlaObject* obj) const;

		//! Called from processDiscoverObject() after a remote OCEAN2020RadioTransmitter has
		//! been added to the list.  Default implementation prints a message.
		//! Subclasses can override this function to add functionality on
		//! addition.  obj will be an instance of a class derived from DtReflectedObj.
		virtual void objectAdded(DtReflectedObject* obj);

	};

} //end OCEAN2020

#endif
