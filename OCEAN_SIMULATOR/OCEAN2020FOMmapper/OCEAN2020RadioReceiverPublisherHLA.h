/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/

//! \file OCEAN2020RadioReceiverPublisherHLA.h
//! \brief Contains the DtOCEAN2020FOMRadioReceiverPublisher class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015

#pragma once

#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl/radioReceiverPublisherHLA.h>

namespace OCEAN2020 {

	class DtOCEAN2020FOMRadioReceiverStateRepository;

	//! Instances of DtOCEAN2020FOMRadioReceiverPublisher publish
	//! EmbeddedSystem.RadioReceiver.OCEAN2020RadioReceiver objects to
	//! the network.
	//! \ingroup OCEAN2020FOM_SISOSTD00112015
	class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMRadioReceiverPublisher : public DtRadioReceiverPublisher
	{
	public:
		//! Function prototype for a function that creates a DtOCEAN2020FOMRadioReceiverStateRepository
		typedef DtOCEAN2020FOMRadioReceiverStateRepository* (*DtStateRepCreator)();

	public:
		//! Constructor.
		DtOCEAN2020FOMRadioReceiverPublisher(
			DtOCEAN2020FOMRadioReceiverStateRepository* stateRepToUse,
			DtExerciseConn* conn,
			const char* name = 0,
			const DtDDMRegionSet* regionSetToUse = 0);

		//! Constructor.
		DtOCEAN2020FOMRadioReceiverPublisher(
			DtExerciseConn* conn,
			const char* name = 0,
			const DtDDMRegionSet* regionSetToUse = 0);

		//! Constructor.
		DtOCEAN2020FOMRadioReceiverPublisher(
			RTI::ObjectClassHandle h,
			DtExerciseConn* conn,
			const char* name = 0,
			const DtDDMRegionSet* regionSetToUse = 0);

		//! Constructor that creates a publisher for an existing DtHlaObject.
		//! (DtHlaObjectWithStateRep is derived from DtHlaObject.)  Typically used
		//! in conjunction with ownership management, when you want to take
		//! ownership and begin updating some attributes of an object that you have
		//! already discovered.
		DtOCEAN2020FOMRadioReceiverPublisher(DtHlaObjectWithStateRep* obj, DtExerciseConn* conn);

		//! The Object class name (EmbeddedSystem.RadioReceiver.OCEAN2020RadioReceiver)
		static const char * objectClassName();

		//! Destructor.
		virtual ~DtOCEAN2020FOMRadioReceiverPublisher();

	protected:
		DtOCEAN2020FOMRadioReceiverPublisher(const char *name = 0, const DtDDMRegionSet *regionSetToUse = 0);

		//! Copy Constructor -- not implemented.
		DtOCEAN2020FOMRadioReceiverPublisher(const DtOCEAN2020FOMRadioReceiverPublisher& orig);

		//! Assignment operator -- not implemented.
		DtOCEAN2020FOMRadioReceiverPublisher& operator=(
			const DtOCEAN2020FOMRadioReceiverPublisher& orig);

	public:

		//! Returns a pointer to the DtOCEAN2020FOMRadioReceiverStateRepository - through
		//! which you can set or inspect current state information.
		virtual DtOCEAN2020FOMRadioReceiverStateRepository* OCEAN2020RadioReceiverStateRep();

		//! Synonym for OCEAN2020RadioReceiverStateRep().
		virtual DtOCEAN2020FOMRadioReceiverStateRepository* Osr();

	public:
		//! Give us a function to be used for creating SRs.
		static DtStateRepCreator setStateRepCreator(DtStateRepCreator creator);

	protected:
		static DtStateRepCreator theStateRepCreator;
	};

	inline DtOCEAN2020FOMRadioReceiverStateRepository* DtOCEAN2020FOMRadioReceiverPublisher::OCEAN2020RadioReceiverStateRep()
	{
		return (DtOCEAN2020FOMRadioReceiverStateRepository*)myStateRep;
	}

	inline DtOCEAN2020FOMRadioReceiverStateRepository* DtOCEAN2020FOMRadioReceiverPublisher::Osr()
	{
		return (DtOCEAN2020FOMRadioReceiverStateRepository*)myStateRep;
	}

} //end OCEAN2020

#endif
