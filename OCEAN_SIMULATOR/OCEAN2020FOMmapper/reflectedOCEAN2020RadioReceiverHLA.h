/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/

//! \file <!HlaRefObj!>.h
//! \brief Contains the DtReflectedOCEAN2020FOMRadioReceiver class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015

#pragma once

#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"
#include "OCEAN2020RadioReceiverStateRepository.h"

//VRLINK include
#include <vl/reflectedRadioReceiverHLA.h>

namespace OCEAN2020 {

	class DtReflectedOCEAN2020FOMRadioReceiver;

	//! Signature of the callback function that takes a DtReflectedOCEAN2020FOMRadioReceiver
	//! and user data
	//! \ingroup OCEAN2020FOM_SISOSTD00112015
	typedef void(*DtOCEAN2020FOMRadioReceiverCallbackFunction)(
		DtReflectedOCEAN2020FOMRadioReceiver* obj, void* userData);

	//! Instances of DtReflectedOCEAN2020FOMRadioReceiver are used to represent a
	//! simulated HLAobjectRoot.EmbeddedSystem.RadioReceiver.OCEAN2020RadioReceiver
	//! object reflected across a network. 
	//! \ingroup OCEAN2020FOM_SISOSTD00112015
	class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtReflectedOCEAN2020FOMRadioReceiver : public DtReflectedRadioReceiver
	{
	public:
		//! Function prototype for functions that create a
		//! DtOCEAN2020FOMRadioReceiverStateRepository.
		typedef DtOCEAN2020FOMRadioReceiverStateRepository* (*DtStateRepCreator)();

	public:
		//! Constructor.
		DtReflectedOCEAN2020FOMRadioReceiver(DtHlaObject* obj, DtExerciseConn* exConn);

		//! Destructor.
		virtual ~DtReflectedOCEAN2020FOMRadioReceiver();

		//! Returns the OCEAN2020RadioReceiver's state repository.
		virtual DtOCEAN2020FOMRadioReceiverStateRepository* OCEAN2020RadioReceiverStateRep() const;

		//! Shorter version of lifeformRep.
		virtual DtOCEAN2020FOMRadioReceiverStateRepository* Osr() const;

		//! Returns the next reflected OCEAN2020RadioReceiver in the 
		//! DtReflectedOCEAN2020FOMRadioReceiverList.
		virtual DtReflectedOCEAN2020FOMRadioReceiver* next() const;

		//! Returns the previous reflected OCEAN2020RadioReceiver in the 
		//! DtReflectedOCEAN2020FOMRadioReceiverList.
		virtual DtReflectedOCEAN2020FOMRadioReceiver* prev() const;

		//! Returns the next reflected OCEAN2020RadioReceiver. Will cycle back to the first 
		//! remote OCEAN2020RadioReceiver in the DtReflectedOCEAN2020FOMRadioReceiverList.
		virtual DtReflectedOCEAN2020FOMRadioReceiver* wrapNext() const;

		//! Returns the previous reflected OCEAN2020RadioReceiver. Will cycle back to the first 
		//! remote OCEAN2020RadioReceiver in the DtReflectedOCEAN2020FOMRadioReceiverList.
		virtual DtReflectedOCEAN2020FOMRadioReceiver* wrapPrev() const;

		//! Add a callback that is called when the DtReflectedOCEAN2020FOMRadioReceiver is
		//! updated.
		virtual void addPostUpdateCallback(
			DtOCEAN2020FOMRadioReceiverCallbackFunction cb, void* userData);

		//! Remove the callback that is called when the DtReflectedOCEAN2020FOMRadioReceiver
		//! is updated.
		virtual void removePostUpdateCallback(
			DtOCEAN2020FOMRadioReceiverCallbackFunction cb, void* userData);

	public:
		//! Set the function to be called for creating state repositories.
		static DtStateRepCreator setStateRepCreator(DtStateRepCreator creator);

	protected:
		//! Copy Constructor not implemented.
		DtReflectedOCEAN2020FOMRadioReceiver(const DtReflectedOCEAN2020FOMRadioReceiver& orig);

		//! Assignment operator not implemented.
		DtReflectedOCEAN2020FOMRadioReceiver& operator=(const DtReflectedOCEAN2020FOMRadioReceiver& orig);

	protected:
		//! The function called to create state repositories.
		static DtStateRepCreator theStateRepCreator;
	};

	inline DtOCEAN2020FOMRadioReceiverStateRepository* DtReflectedOCEAN2020FOMRadioReceiver::OCEAN2020RadioReceiverStateRep() const
	{
		return (DtOCEAN2020FOMRadioReceiverStateRepository*)myStateRep;
	}

	inline DtOCEAN2020FOMRadioReceiverStateRepository* DtReflectedOCEAN2020FOMRadioReceiver::Osr() const
	{
		return (DtOCEAN2020FOMRadioReceiverStateRepository*)myStateRep;
	}

} //end OCEAN2020

#endif
