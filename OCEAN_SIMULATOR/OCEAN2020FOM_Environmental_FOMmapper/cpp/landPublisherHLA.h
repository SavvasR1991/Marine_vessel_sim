/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**hpubHeader.tlt
*********************************************************************/
 
//! \file landPublisherHLA.h
//! \brief Contains the DtOCEAN2020FOMLandPublisher class declaration.
//! \ingroup OCEAN2020FOM_Environmental
 
#pragma once
 
#if DtHLA
 
#include <vl/objectPublisherHLA.h>
#include "dllExport.h"
 
namespace OCEAN2020 {
 
class DtOCEAN2020FOMLandStateRepository;
 
//! Instances of DtOCEAN2020FOMLandPublisher publish
//! VS_Environment.Land objects to
//! the network.
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtOCEAN2020FOMLandPublisher : public DtObjectPublisher
{
public:
   //! Function prototype for a function that creates a DtOCEAN2020FOMLandStateRepository
   typedef DtOCEAN2020FOMLandStateRepository* (*DtStateRepCreator)();
 
public:
   //! Constructor.
   DtOCEAN2020FOMLandPublisher(
      DtOCEAN2020FOMLandStateRepository* stateRepToUse,
      DtExerciseConn* conn,
      const char* name = 0,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor.
   DtOCEAN2020FOMLandPublisher(
      RTI::ObjectClassHandle h,
      DtExerciseConn* conn,
      const char* name = 0,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor.
   DtOCEAN2020FOMLandPublisher(
      DtExerciseConn* conn,
      const char* name = 0,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor that creates a publisher for an existing DtHlaObject.
   //! (DtHlaObjectWithStateRep is derived from DtHlaObject.)  Typically used
   //! in conjunction with ownership management, when you want to take
   //! ownership and begin updating some attributes of an object that you have
   //! already discovered.
   DtOCEAN2020FOMLandPublisher( DtHlaObjectWithStateRep* obj, DtExerciseConn* conn);
 
   //! The Object class name (VS_Environment.Land)
   static const char * objectClassName();
   
   //! Destructor.
   virtual ~DtOCEAN2020FOMLandPublisher();
 
private:
   //! Copy Constructor -- not implemented.
   DtOCEAN2020FOMLandPublisher(const DtOCEAN2020FOMLandPublisher& orig);
 
   //! Assignment operator -- not implemented.
   DtOCEAN2020FOMLandPublisher& operator=(
      const DtOCEAN2020FOMLandPublisher& orig);
 
public:
 
   //! Returns a pointer to the DtOCEAN2020FOMLandStateRepository - through
   //! which you can set or inspect current state information.
   virtual DtOCEAN2020FOMLandStateRepository* landStateRep();
 
   //! Synonym for landStateRep().
   virtual DtOCEAN2020FOMLandStateRepository* lsr();
 
public:
   //! Give us a function to be used for creating SRs.
   static DtStateRepCreator setStateRepCreator(DtStateRepCreator creator);
 
protected:
   static DtStateRepCreator theStateRepCreator;
};
 
inline DtOCEAN2020FOMLandStateRepository* DtOCEAN2020FOMLandPublisher::landStateRep()
{
   return (DtOCEAN2020FOMLandStateRepository*) myStateRep;
}
 
inline DtOCEAN2020FOMLandStateRepository* DtOCEAN2020FOMLandPublisher::lsr()
{
   return (DtOCEAN2020FOMLandStateRepository*) myStateRep;
}
 
} //end OCEAN2020
 
#endif