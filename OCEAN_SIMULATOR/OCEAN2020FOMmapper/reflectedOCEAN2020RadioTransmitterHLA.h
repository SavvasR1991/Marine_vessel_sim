/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/

//! \file <!HlaRefObj!>.h
//! \brief Contains the DtReflectedOCEAN2020FOMRadioTransmitter class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015

#pragma once

#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"
#include "OCEAN2020RadioTransmitterStateRepository.h"

//VRLINK include
#include <vl/reflectedRadioTransmitterHLA.h>

namespace OCEAN2020 {

	class DtReflectedOCEAN2020FOMRadioTransmitter;

	//! Signature of the callback function that takes a DtReflectedOCEAN2020FOMRadioTransmitter
	//! and user data
	//! \ingroup OCEAN2020FOM_SISOSTD00112015
	typedef void(*DtOCEAN2020FOMRadioTransmitterCallbackFunction)(
		DtReflectedOCEAN2020FOMRadioTransmitter* obj, void* userData);

	//! Instances of DtReflectedOCEAN2020FOMRadioTransmitter are used to represent a
	//! simulated HLAobjectRoot.EmbeddedSystem.RadioTransmitter.OCEAN2020RadioTransmitter
	//! object reflected across a network. 
	//! \ingroup OCEAN2020FOM_SISOSTD00112015
	class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtReflectedOCEAN2020FOMRadioTransmitter : public DtReflectedRadioTransmitter
	{
	public:
		//! Function prototype for functions that create a
		//! DtOCEAN2020FOMRadioTransmitterStateRepository.
		typedef DtOCEAN2020FOMRadioTransmitterStateRepository* (*DtStateRepCreator)();

	public:
		//! Constructor.
		DtReflectedOCEAN2020FOMRadioTransmitter(DtHlaObject* obj, DtExerciseConn* exConn);

		//! Destructor.
		virtual ~DtReflectedOCEAN2020FOMRadioTransmitter();

		//! Returns the OCEAN2020RadioTransmitter's state repository.
		virtual DtOCEAN2020FOMRadioTransmitterStateRepository* OCEAN2020RadioTransmitterStateRep() const;

		//! Shorter version of lifeformRep.
		virtual DtOCEAN2020FOMRadioTransmitterStateRepository* Osr() const;

		//! Returns the next reflected OCEAN2020RadioTransmitter in the 
		//! DtReflectedOCEAN2020FOMRadioTransmitterList.
		virtual DtReflectedOCEAN2020FOMRadioTransmitter* next() const;

		//! Returns the previous reflected OCEAN2020RadioTransmitter in the 
		//! DtReflectedOCEAN2020FOMRadioTransmitterList.
		virtual DtReflectedOCEAN2020FOMRadioTransmitter* prev() const;

		//! Returns the next reflected OCEAN2020RadioTransmitter. Will cycle back to the first 
		//! remote OCEAN2020RadioTransmitter in the DtReflectedOCEAN2020FOMRadioTransmitterList.
		virtual DtReflectedOCEAN2020FOMRadioTransmitter* wrapNext() const;

		//! Returns the previous reflected OCEAN2020RadioTransmitter. Will cycle back to the first 
		//! remote OCEAN2020RadioTransmitter in the DtReflectedOCEAN2020FOMRadioTransmitterList.
		virtual DtReflectedOCEAN2020FOMRadioTransmitter* wrapPrev() const;

		//! Add a callback that is called when the DtReflectedOCEAN2020FOMRadioTransmitter is
		//! updated.
		virtual void addPostUpdateCallback(
			DtOCEAN2020FOMRadioTransmitterCallbackFunction cb, void* userData);

		//! Remove the callback that is called when the DtReflectedOCEAN2020FOMRadioTransmitter
		//! is updated.
		virtual void removePostUpdateCallback(
			DtOCEAN2020FOMRadioTransmitterCallbackFunction cb, void* userData);

	public:
		//! Set the function to be called for creating state repositories.
		static DtStateRepCreator setStateRepCreator(DtStateRepCreator creator);

	protected:
		//! Copy Constructor not implemented.
		DtReflectedOCEAN2020FOMRadioTransmitter(const DtReflectedOCEAN2020FOMRadioTransmitter& orig);

		//! Assignment operator not implemented.
		DtReflectedOCEAN2020FOMRadioTransmitter& operator=(const DtReflectedOCEAN2020FOMRadioTransmitter& orig);

	protected:
		//! The function called to create state repositories.
		static DtStateRepCreator theStateRepCreator;
	};

	inline DtOCEAN2020FOMRadioTransmitterStateRepository* DtReflectedOCEAN2020FOMRadioTransmitter::OCEAN2020RadioTransmitterStateRep() const
	{
		return (DtOCEAN2020FOMRadioTransmitterStateRepository*)myStateRep;
	}

	inline DtOCEAN2020FOMRadioTransmitterStateRepository* DtReflectedOCEAN2020FOMRadioTransmitter::Osr() const
	{
		return (DtOCEAN2020FOMRadioTransmitterStateRepository*)myStateRep;
	}

} //end OCEAN2020

#endif
