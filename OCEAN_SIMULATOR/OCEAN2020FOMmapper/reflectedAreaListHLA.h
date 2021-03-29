/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file reflectedAreaListHLA.h
//! \brief Contains the DtReflectedOCEAN2020FOMAreaList class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once
 
#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"
#include "reflectedAreaHLA.h"

//VRLINK include
#include <vl/reflectedEntityListHLA.h>
 
namespace OCEAN2020 {
 
//! Instances of DtReflectedOCEAN2020FOMAreaList manage a list of
//! DtReflectedOCEAN2020FOMArea objects.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtReflectedOCEAN2020FOMAreaList : public DtReflectedEntityList
{
public:
   //! Constructor. 
   DtReflectedOCEAN2020FOMAreaList(DtExerciseConn* exConn,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor - only subscribe to the RTI::ObjectClassHandles
   //! in handleList.
   DtReflectedOCEAN2020FOMAreaList(DtExerciseConn* exConn,
      const DtList *handleList, const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Destructor.
   virtual ~DtReflectedOCEAN2020FOMAreaList();
 
private:
 
   //! Copy constructor not implemented - cannot be copied.
   DtReflectedOCEAN2020FOMAreaList(const DtReflectedOCEAN2020FOMAreaList& orig);
 
   //! Assignment operator not implemented - cannot be copied.
   DtReflectedOCEAN2020FOMAreaList& operator=(const DtReflectedOCEAN2020FOMAreaList&orig);
 
public:
 
   //! Look up by identifier.
   virtual DtReflectedOCEAN2020FOMArea* lookup(
#if DtHLA_1516
      RTI::ObjectInstanceHandle id);
#else
      RTI::ObjectHandle id);
#endif
 
   //! Look up by name.
   virtual DtReflectedOCEAN2020FOMArea* lookup(
      const DtGlobalObjectDesignator& objName);
 
   //! Get the first reflected object in the list.
   virtual DtReflectedOCEAN2020FOMArea* first() const;
 
   //! Get the last reflected object in the list.
   virtual DtReflectedOCEAN2020FOMArea* last() const;
 
   //! Area added callback registration
   virtual void addAreaAdditionCallback(
      DtOCEAN2020FOMAreaCallbackFunction cb, void* userData);
 
   //! Area added callback deregistration
   virtual void removeAreaAdditionCallback(
      DtOCEAN2020FOMAreaCallbackFunction cb, void* userData);
 
   //! Area removed callback registration
   virtual void addAreaRemovalCallback(
      DtOCEAN2020FOMAreaCallbackFunction cb, void* userData);
 
   //! Area removed callback deregistration
   virtual void removeAreaRemovalCallback(
      DtOCEAN2020FOMAreaCallbackFunction cb, void* userData);
 
protected:
 
   //! Override of virtual function.  Here, we create a DtReflectedOCEAN2020FOMArea
   virtual DtReflectedObject* newReflectedObject(DtHlaObject* obj) const;
 
   //! Called from processDiscoverObject() after a remote Area has
   //! been added to the list.  Default implementation prints a message.
   //! Subclasses can override this function to add functionality on
   //! addition.  obj will be an instance of a class derived from DtReflectedObj.
   virtual void objectAdded(DtReflectedObject* obj);
 
};
 
} //end OCEAN2020
 
#endif
