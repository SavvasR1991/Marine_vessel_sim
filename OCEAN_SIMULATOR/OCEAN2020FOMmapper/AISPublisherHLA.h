/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file AISPublisherHLA.h
//! \brief Contains the DtOCEAN2020FOMAISPublisher class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once
 
#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl/objectPublisherHLA.h>
 
namespace OCEAN2020 {
 
class DtOCEAN2020FOMAISStateRepository;
 
//! Instances of DtOCEAN2020FOMAISPublisher publish
//! EmbeddedSystem.AIS objects to
//! the network.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMAISPublisher : public DtObjectPublisher
{
public:
   //! Function prototype for a function that creates a DtOCEAN2020FOMAISStateRepository
   typedef DtOCEAN2020FOMAISStateRepository* (*DtStateRepCreator)();
 
public:
   //! Constructor.
   DtOCEAN2020FOMAISPublisher(
      DtOCEAN2020FOMAISStateRepository* stateRepToUse,
      DtExerciseConn* conn,
      const char* name = 0,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor.
   DtOCEAN2020FOMAISPublisher(
      RTI::ObjectClassHandle h,
      DtExerciseConn* conn,
      const char* name = 0,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor.
   DtOCEAN2020FOMAISPublisher(
      DtExerciseConn* conn,
      const char* name = 0,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor that creates a publisher for an existing DtHlaObject.
   //! (DtHlaObjectWithStateRep is derived from DtHlaObject.)  Typically used
   //! in conjunction with ownership management, when you want to take
   //! ownership and begin updating some attributes of an object that you have
   //! already discovered.
   DtOCEAN2020FOMAISPublisher( DtHlaObjectWithStateRep* obj, DtExerciseConn* conn);
 
   //! The Object class name (EmbeddedSystem.AIS)
   static const char * objectClassName();
   
   //! Destructor.
   virtual ~DtOCEAN2020FOMAISPublisher();
 
private:
   //! Copy Constructor -- not implemented.
   DtOCEAN2020FOMAISPublisher(const DtOCEAN2020FOMAISPublisher& orig);
 
   //! Assignment operator -- not implemented.
   DtOCEAN2020FOMAISPublisher& operator=(
      const DtOCEAN2020FOMAISPublisher& orig);
 
public:
 
   //! Returns a pointer to the DtOCEAN2020FOMAISStateRepository - through
   //! which you can set or inspect current state information.
   virtual DtOCEAN2020FOMAISStateRepository* AISStateRep();
 
   //! Synonym for AISStateRep().
   virtual DtOCEAN2020FOMAISStateRepository* Asr();
 
public:
   //! Give us a function to be used for creating SRs.
   static DtStateRepCreator setStateRepCreator(DtStateRepCreator creator);
 
protected:
   static DtStateRepCreator theStateRepCreator;
};
 
inline DtOCEAN2020FOMAISStateRepository* DtOCEAN2020FOMAISPublisher::AISStateRep()
{
   return (DtOCEAN2020FOMAISStateRepository*) myStateRep;
}
 
inline DtOCEAN2020FOMAISStateRepository* DtOCEAN2020FOMAISPublisher::Asr()
{
   return (DtOCEAN2020FOMAISStateRepository*) myStateRep;
}
 
} //end OCEAN2020
 
#endif
