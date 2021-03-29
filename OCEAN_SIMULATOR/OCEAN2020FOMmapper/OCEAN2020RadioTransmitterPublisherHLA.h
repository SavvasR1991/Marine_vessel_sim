/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/

//! \file OCEAN2020RadioTransmitterPublisherHLA.h
//! \brief Contains the DtOCEAN2020FOMRadioTransmitterPublisher class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015

#pragma once

#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl/radioTransmitterPublisherHLA.h>

namespace OCEAN2020 {

	class DtOCEAN2020FOMRadioTransmitterStateRepository;

	//! Instances of DtOCEAN2020FOMRadioTransmitterPublisher publish
	//! EmbeddedSystem.RadioTransmitter.OCEAN2020RadioTransmitter objects to
	//! the network.
	//! \ingroup OCEAN2020FOM_SISOSTD00112015
	class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMRadioTransmitterPublisher : public DtRadioTransmitterPublisher
	{
	public:
		//! Function prototype for a function that creates a DtOCEAN2020FOMRadioTransmitterStateRepository
		typedef DtOCEAN2020FOMRadioTransmitterStateRepository* (*DtStateRepCreator)();

	public:
		//! Constructor.
		DtOCEAN2020FOMRadioTransmitterPublisher(
			DtOCEAN2020FOMRadioTransmitterStateRepository* stateRepToUse,
			DtExerciseConn* conn,
			const char* name = 0,
			const DtDDMRegionSet* regionSetToUse = 0);

		//! Constructor.
		DtOCEAN2020FOMRadioTransmitterPublisher(
			RTI::ObjectClassHandle h,
			DtExerciseConn* conn,
			const char* name = 0,
			const DtDDMRegionSet* regionSetToUse = 0);

		//! Constructor.
		DtOCEAN2020FOMRadioTransmitterPublisher(
			DtExerciseConn* conn,
			const char* name = 0,
			const DtDDMRegionSet* regionSetToUse = 0);

		//! Constructor that creates a publisher for an existing DtHlaObject.
		//! (DtHlaObjectWithStateRep is derived from DtHlaObject.)  Typically used
		//! in conjunction with ownership management, when you want to take
		//! ownership and begin updating some attributes of an object that you have
		//! already discovered.
		DtOCEAN2020FOMRadioTransmitterPublisher(DtHlaObjectWithStateRep* obj, DtExerciseConn* conn);

		//! The Object class name (EmbeddedSystem.RadioTransmitter.OCEAN2020RadioTransmitter)
		static const char * objectClassName();

		//! Destructor.
		virtual ~DtOCEAN2020FOMRadioTransmitterPublisher();

	protected:
		DtOCEAN2020FOMRadioTransmitterPublisher(const char *name = 0, const DtDDMRegionSet *regionSetToUse = 0);

		//! Copy Constructor -- not implemented.
		DtOCEAN2020FOMRadioTransmitterPublisher(const DtOCEAN2020FOMRadioTransmitterPublisher& orig);

		//! Assignment operator -- not implemented.
		DtOCEAN2020FOMRadioTransmitterPublisher& operator=(
			const DtOCEAN2020FOMRadioTransmitterPublisher& orig);

	public:

		//! Returns a pointer to the DtOCEAN2020FOMRadioTransmitterStateRepository - through
		//! which you can set or inspect current state information.
		virtual DtOCEAN2020FOMRadioTransmitterStateRepository* OCEAN2020RadioTransmitterStateRep();

		//! Synonym for OCEAN2020RadioTransmitterStateRep().
		virtual DtOCEAN2020FOMRadioTransmitterStateRepository* Osr();

	public:
		//! Give us a function to be used for creating SRs.
		static DtStateRepCreator setStateRepCreator(DtStateRepCreator creator);

	protected:
		static DtStateRepCreator theStateRepCreator;
	};

	inline DtOCEAN2020FOMRadioTransmitterStateRepository* DtOCEAN2020FOMRadioTransmitterPublisher::OCEAN2020RadioTransmitterStateRep()
	{
		return (DtOCEAN2020FOMRadioTransmitterStateRepository*)myStateRep;
	}

	inline DtOCEAN2020FOMRadioTransmitterStateRepository* DtOCEAN2020FOMRadioTransmitterPublisher::Osr()
	{
		return (DtOCEAN2020FOMRadioTransmitterStateRepository*)myStateRep;
	}

} //end OCEAN2020

#endif
