/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**hpubHeader.tlt
*********************************************************************/
 
//! \file bathymetryPublisherHLA.h
//! \brief Contains the DtOCEAN2020FOMBathymetryPublisher class declaration.
//! \ingroup OCEAN2020FOM_Environmental
 
#pragma once
 
#if DtHLA
 
#include <vl/objectPublisherHLA.h>
#include "dllExport.h"
 
namespace OCEAN2020 {
 
class DtOCEAN2020FOMBathymetryStateRepository;
 
//! Instances of DtOCEAN2020FOMBathymetryPublisher publish
//! VS_Environment.Bathymetry objects to
//! the network.
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtOCEAN2020FOMBathymetryPublisher : public DtObjectPublisher
{
public:
   //! Function prototype for a function that creates a DtOCEAN2020FOMBathymetryStateRepository
   typedef DtOCEAN2020FOMBathymetryStateRepository* (*DtStateRepCreator)();
 
public:
   //! Constructor.
   DtOCEAN2020FOMBathymetryPublisher(
      DtOCEAN2020FOMBathymetryStateRepository* stateRepToUse,
      DtExerciseConn* conn,
      const char* name = 0,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor.
   DtOCEAN2020FOMBathymetryPublisher(
      RTI::ObjectClassHandle h,
      DtExerciseConn* conn,
      const char* name = 0,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor.
   DtOCEAN2020FOMBathymetryPublisher(
      DtExerciseConn* conn,
      const char* name = 0,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor that creates a publisher for an existing DtHlaObject.
   //! (DtHlaObjectWithStateRep is derived from DtHlaObject.)  Typically used
   //! in conjunction with ownership management, when you want to take
   //! ownership and begin updating some attributes of an object that you have
   //! already discovered.
   DtOCEAN2020FOMBathymetryPublisher( DtHlaObjectWithStateRep* obj, DtExerciseConn* conn);
 
   //! The Object class name (VS_Environment.Bathymetry)
   static const char * objectClassName();
   
   //! Destructor.
   virtual ~DtOCEAN2020FOMBathymetryPublisher();
 
private:
   //! Copy Constructor -- not implemented.
   DtOCEAN2020FOMBathymetryPublisher(const DtOCEAN2020FOMBathymetryPublisher& orig);
 
   //! Assignment operator -- not implemented.
   DtOCEAN2020FOMBathymetryPublisher& operator=(
      const DtOCEAN2020FOMBathymetryPublisher& orig);
 
public:
 
   //! Returns a pointer to the DtOCEAN2020FOMBathymetryStateRepository - through
   //! which you can set or inspect current state information.
   virtual DtOCEAN2020FOMBathymetryStateRepository* bathymetryStateRep();
 
   //! Synonym for bathymetryStateRep().
   virtual DtOCEAN2020FOMBathymetryStateRepository* bsr();
 
public:
   //! Give us a function to be used for creating SRs.
   static DtStateRepCreator setStateRepCreator(DtStateRepCreator creator);
 
protected:
   static DtStateRepCreator theStateRepCreator;
};
 
inline DtOCEAN2020FOMBathymetryStateRepository* DtOCEAN2020FOMBathymetryPublisher::bathymetryStateRep()
{
   return (DtOCEAN2020FOMBathymetryStateRepository*) myStateRep;
}
 
inline DtOCEAN2020FOMBathymetryStateRepository* DtOCEAN2020FOMBathymetryPublisher::bsr()
{
   return (DtOCEAN2020FOMBathymetryStateRepository*) myStateRep;
}
 
} //end OCEAN2020
 
#endif
