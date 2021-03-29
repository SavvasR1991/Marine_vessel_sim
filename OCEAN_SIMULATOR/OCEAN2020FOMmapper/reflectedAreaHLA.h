/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file <!HlaRefObj!>.h
//! \brief Contains the DtReflectedOCEAN2020FOMArea class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once
 
#if DtHLA

//Project include
#include "areaStateRepository.h"
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl/reflectedEntityHLA.h>
 
namespace OCEAN2020 {
 
class DtReflectedOCEAN2020FOMArea;
 
//! Signature of the callback function that takes a DtReflectedOCEAN2020FOMArea
//! and user data
//! \ingroup OCEAN2020FOM_SISOSTD00112015
typedef void (*DtOCEAN2020FOMAreaCallbackFunction)(
   DtReflectedOCEAN2020FOMArea* obj, void* userData);
 
//! Instances of DtReflectedOCEAN2020FOMArea are used to represent a
//! simulated HLAobjectRoot.BaseEntity.PhysicalEntity.Sensor.Area
//! object reflected across a network. 
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtReflectedOCEAN2020FOMArea : public DtReflectedEntity
{
public:
   //! Function prototype for functions that create a
   //! DtOCEAN2020FOMAreaStateRepository.
   typedef DtOCEAN2020FOMAreaStateRepository* (*DtStateRepCreator)();
 
public:
   //! Constructor.
   DtReflectedOCEAN2020FOMArea(DtHlaObject* obj, DtExerciseConn* exConn);
 
   //! Destructor.
   virtual ~DtReflectedOCEAN2020FOMArea();
 
   //! Returns the Area's state repository.
   virtual DtOCEAN2020FOMAreaStateRepository* areaStateRep() const;
 
   //! Shorter version of lifeformRep.
   virtual DtOCEAN2020FOMAreaStateRepository* asr() const;
 
   //! Returns the next reflected Area in the 
   //! DtReflectedOCEAN2020FOMAreaList.
   virtual DtReflectedOCEAN2020FOMArea* next() const;
 
   //! Returns the previous reflected Area in the 
   //! DtReflectedOCEAN2020FOMAreaList.
   virtual DtReflectedOCEAN2020FOMArea* prev() const;
 
   //! Returns the next reflected Area. Will cycle back to the first 
   //! remote Area in the DtReflectedOCEAN2020FOMAreaList.
   virtual DtReflectedOCEAN2020FOMArea* wrapNext() const;
 
   //! Returns the previous reflected Area. Will cycle back to the first 
   //! remote Area in the DtReflectedOCEAN2020FOMAreaList.
   virtual DtReflectedOCEAN2020FOMArea* wrapPrev() const;
 
   //! Add a callback that is called when the DtReflectedOCEAN2020FOMArea is
   //! updated.
   virtual void addPostUpdateCallback(
      DtOCEAN2020FOMAreaCallbackFunction cb, void* userData);
 
   //! Remove the callback that is called when the DtReflectedOCEAN2020FOMArea
   //! is updated.
   virtual void removePostUpdateCallback(
      DtOCEAN2020FOMAreaCallbackFunction cb, void* userData);
 
public:
   //! Set the function to be called for creating state repositories.
   static DtStateRepCreator setStateRepCreator(DtStateRepCreator creator);
 
protected:
   //! Copy Constructor not implemented.
   DtReflectedOCEAN2020FOMArea(const DtReflectedOCEAN2020FOMArea& orig);
 
   //! Assignment operator not implemented.
   DtReflectedOCEAN2020FOMArea& operator=(const DtReflectedOCEAN2020FOMArea& orig);
 
protected:
   //! The function called to create state repositories.
   static DtStateRepCreator theStateRepCreator;
};
 
inline DtOCEAN2020FOMAreaStateRepository* DtReflectedOCEAN2020FOMArea::areaStateRep() const
{ 
   return (DtOCEAN2020FOMAreaStateRepository*) myStateRep;
}
 
inline DtOCEAN2020FOMAreaStateRepository* DtReflectedOCEAN2020FOMArea::asr() const
{
   return (DtOCEAN2020FOMAreaStateRepository*) myStateRep;
}
 
} //end OCEAN2020
 
#endif
