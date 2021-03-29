/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**hpubHeader.tlt
*********************************************************************/
 
//! \file VS_EnvironmentPublisherHLA.h
//! \brief Contains the DtOCEAN2020FOMVS_EnvironmentPublisher class declaration.
//! \ingroup OCEAN2020FOM_Environmental
 
#pragma once
 
#if DtHLA
 
#include <vl/objectPublisherHLA.h>
#include "dllExport.h"
 
namespace OCEAN2020 {
 
class DtOCEAN2020FOMVS_EnvironmentStateRepository;
 
//! Instances of DtOCEAN2020FOMVS_EnvironmentPublisher publish
//! VS_Environment objects to
//! the network.
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtOCEAN2020FOMVS_EnvironmentPublisher : public DtObjectPublisher
{
public:
   //! Function prototype for a function that creates a DtOCEAN2020FOMVS_EnvironmentStateRepository
   typedef DtOCEAN2020FOMVS_EnvironmentStateRepository* (*DtStateRepCreator)();
 
public:
   //! Constructor.
   DtOCEAN2020FOMVS_EnvironmentPublisher(
      DtOCEAN2020FOMVS_EnvironmentStateRepository* stateRepToUse,
      DtExerciseConn* conn,
      const char* name = 0,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor.
   DtOCEAN2020FOMVS_EnvironmentPublisher(
      RTI::ObjectClassHandle h,
      DtExerciseConn* conn,
      const char* name = 0,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor.
   DtOCEAN2020FOMVS_EnvironmentPublisher(
      DtExerciseConn* conn,
      const char* name = 0,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor that creates a publisher for an existing DtHlaObject.
   //! (DtHlaObjectWithStateRep is derived from DtHlaObject.)  Typically used
   //! in conjunction with ownership management, when you want to take
   //! ownership and begin updating some attributes of an object that you have
   //! already discovered.
   DtOCEAN2020FOMVS_EnvironmentPublisher( DtHlaObjectWithStateRep* obj, DtExerciseConn* conn);
 
   //! The Object class name (VS_Environment)
   static const char * objectClassName();
   
   //! Destructor.
   virtual ~DtOCEAN2020FOMVS_EnvironmentPublisher();
 
private:
   //! Copy Constructor -- not implemented.
   DtOCEAN2020FOMVS_EnvironmentPublisher(const DtOCEAN2020FOMVS_EnvironmentPublisher& orig);
 
   //! Assignment operator -- not implemented.
   DtOCEAN2020FOMVS_EnvironmentPublisher& operator=(
      const DtOCEAN2020FOMVS_EnvironmentPublisher& orig);
 
public:
 
   //! Returns a pointer to the DtOCEAN2020FOMVS_EnvironmentStateRepository - through
   //! which you can set or inspect current state information.
   virtual DtOCEAN2020FOMVS_EnvironmentStateRepository* VS_EnvironmentStateRep();
 
   //! Synonym for VS_EnvironmentStateRep().
   virtual DtOCEAN2020FOMVS_EnvironmentStateRepository* Vsr();
 
public:
   //! Give us a function to be used for creating SRs.
   static DtStateRepCreator setStateRepCreator(DtStateRepCreator creator);
 
protected:
   static DtStateRepCreator theStateRepCreator;
};
 
inline DtOCEAN2020FOMVS_EnvironmentStateRepository* DtOCEAN2020FOMVS_EnvironmentPublisher::VS_EnvironmentStateRep()
{
   return (DtOCEAN2020FOMVS_EnvironmentStateRepository*) myStateRep;
}
 
inline DtOCEAN2020FOMVS_EnvironmentStateRepository* DtOCEAN2020FOMVS_EnvironmentPublisher::Vsr()
{
   return (DtOCEAN2020FOMVS_EnvironmentStateRepository*) myStateRep;
}
 
} //end OCEAN2020
 
#endif
