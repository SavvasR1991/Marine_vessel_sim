/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**hrefObjHeader.tlt
*********************************************************************/
 
//! \file <!HlaRefObj!>.h
//! \brief Contains the DtReflectedOCEAN2020FOMMosaicSeabed class declaration.
//! \ingroup OCEAN2020FOM_Environmental
 
#pragma once
 
#if DtHLA
 
#include <vl/reflectedObjectHLA.h>
#include "dllExport.h"
#include "mosaicSeabedStateRepository.h"
 
namespace OCEAN2020 {
 
class DtReflectedOCEAN2020FOMMosaicSeabed;
 
//! Signature of the callback function that takes a DtReflectedOCEAN2020FOMMosaicSeabed
//! and user data
//! \ingroup OCEAN2020FOM_Environmental
typedef void (*DtOCEAN2020FOMMosaicSeabedCallbackFunction)(
   DtReflectedOCEAN2020FOMMosaicSeabed* obj, void* userData);
 
//! Instances of DtReflectedOCEAN2020FOMMosaicSeabed are used to represent a
//! simulated HLAobjectRoot.VS_Environment.MosaicSeabed
//! object reflected across a network. 
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtReflectedOCEAN2020FOMMosaicSeabed : public DtReflectedObject
{
public:
   //! Function prototype for functions that create a
   //! DtOCEAN2020FOMMosaicSeabedStateRepository.
   typedef DtOCEAN2020FOMMosaicSeabedStateRepository* (*DtStateRepCreator)();
 
public:
   //! Constructor.
   DtReflectedOCEAN2020FOMMosaicSeabed(DtHlaObject* obj, DtExerciseConn* exConn);
 
   //! Destructor.
   virtual ~DtReflectedOCEAN2020FOMMosaicSeabed();
 
   //! Returns the MosaicSeabed's state repository.
   virtual DtOCEAN2020FOMMosaicSeabedStateRepository* mosaicSeabedStateRep() const;
 
   //! Shorter version of lifeformRep.
   virtual DtOCEAN2020FOMMosaicSeabedStateRepository* msr() const;
 
   //! Returns the next reflected MosaicSeabed in the 
   //! DtReflectedOCEAN2020FOMMosaicSeabedList.
   virtual DtReflectedOCEAN2020FOMMosaicSeabed* next() const;
 
   //! Returns the previous reflected MosaicSeabed in the 
   //! DtReflectedOCEAN2020FOMMosaicSeabedList.
   virtual DtReflectedOCEAN2020FOMMosaicSeabed* prev() const;
 
   //! Returns the next reflected MosaicSeabed. Will cycle back to the first 
   //! remote MosaicSeabed in the DtReflectedOCEAN2020FOMMosaicSeabedList.
   virtual DtReflectedOCEAN2020FOMMosaicSeabed* wrapNext() const;
 
   //! Returns the previous reflected MosaicSeabed. Will cycle back to the first 
   //! remote MosaicSeabed in the DtReflectedOCEAN2020FOMMosaicSeabedList.
   virtual DtReflectedOCEAN2020FOMMosaicSeabed* wrapPrev() const;
 
   //! Add a callback that is called when the DtReflectedOCEAN2020FOMMosaicSeabed is
   //! updated.
   virtual void addPostUpdateCallback(
      DtOCEAN2020FOMMosaicSeabedCallbackFunction cb, void* userData);
 
   //! Remove the callback that is called when the DtReflectedOCEAN2020FOMMosaicSeabed
   //! is updated.
   virtual void removePostUpdateCallback(
      DtOCEAN2020FOMMosaicSeabedCallbackFunction cb, void* userData);
 
public:
   //! Set the function to be called for creating state repositories.
   static DtStateRepCreator setStateRepCreator(DtStateRepCreator creator);
 
protected:
   //! Copy Constructor not implemented.
   DtReflectedOCEAN2020FOMMosaicSeabed(const DtReflectedOCEAN2020FOMMosaicSeabed& orig);
 
   //! Assignment operator not implemented.
   DtReflectedOCEAN2020FOMMosaicSeabed& operator=(const DtReflectedOCEAN2020FOMMosaicSeabed& orig);
 
protected:
   //! The function called to create state repositories.
   static DtStateRepCreator theStateRepCreator;
};
 
inline DtOCEAN2020FOMMosaicSeabedStateRepository* DtReflectedOCEAN2020FOMMosaicSeabed::mosaicSeabedStateRep() const
{ 
   return (DtOCEAN2020FOMMosaicSeabedStateRepository*) myStateRep;
}
 
inline DtOCEAN2020FOMMosaicSeabedStateRepository* DtReflectedOCEAN2020FOMMosaicSeabed::msr() const
{
   return (DtOCEAN2020FOMMosaicSeabedStateRepository*) myStateRep;
}
 
} //end OCEAN2020
 
#endif
