/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file reflectedAISListHLA.h
//! \brief Contains the DtReflectedOCEAN2020FOMAISList class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once
 
#if DtHLA

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"
#include "reflectedAISHLA.h"

//VRLINK include
#include <vl/reflectedObjectListHLA.h>
 
namespace OCEAN2020 {
 
//! Instances of DtReflectedOCEAN2020FOMAISList manage a list of
//! DtReflectedOCEAN2020FOMAIS objects.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtReflectedOCEAN2020FOMAISList : public DtReflectedObjectList
{
public:
   //! Constructor. 
   DtReflectedOCEAN2020FOMAISList(DtExerciseConn* exConn,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor - only subscribe to the RTI::ObjectClassHandles
   //! in handleList.
   DtReflectedOCEAN2020FOMAISList(DtExerciseConn* exConn,
      const DtList *handleList, const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Destructor.
   virtual ~DtReflectedOCEAN2020FOMAISList();
 
private:
 
   //! Copy constructor not implemented - cannot be copied.
   DtReflectedOCEAN2020FOMAISList(const DtReflectedOCEAN2020FOMAISList& orig);
 
   //! Assignment operator not implemented - cannot be copied.
   DtReflectedOCEAN2020FOMAISList& operator=(const DtReflectedOCEAN2020FOMAISList&orig);
 
public:
 
   //! Look up by identifier.
   virtual DtReflectedOCEAN2020FOMAIS* lookup(
#if DtHLA_1516
      RTI::ObjectInstanceHandle id);
#else
      RTI::ObjectHandle id);
#endif
 
   //! Look up by name.
   virtual DtReflectedOCEAN2020FOMAIS* lookup(
      const DtGlobalObjectDesignator& objName);
 
   //! Get the first reflected object in the list.
   virtual DtReflectedOCEAN2020FOMAIS* first() const;
 
   //! Get the last reflected object in the list.
   virtual DtReflectedOCEAN2020FOMAIS* last() const;
 
   //! AIS added callback registration
   virtual void addAISAdditionCallback(
      DtOCEAN2020FOMAISCallbackFunction cb, void* userData);
 
   //! AIS added callback deregistration
   virtual void removeAISAdditionCallback(
      DtOCEAN2020FOMAISCallbackFunction cb, void* userData);
 
   //! AIS removed callback registration
   virtual void addAISRemovalCallback(
      DtOCEAN2020FOMAISCallbackFunction cb, void* userData);
 
   //! AIS removed callback deregistration
   virtual void removeAISRemovalCallback(
      DtOCEAN2020FOMAISCallbackFunction cb, void* userData);
 
protected:
 
   //! Override of virtual function.  Here, we create a DtReflectedOCEAN2020FOMAIS
   virtual DtReflectedObject* newReflectedObject(DtHlaObject* obj) const;
 
   //! Called from processDiscoverObject() after a remote AIS has
   //! been added to the list.  Default implementation prints a message.
   //! Subclasses can override this function to add functionality on
   //! addition.  obj will be an instance of a class derived from DtReflectedObj.
   virtual void objectAdded(DtReflectedObject* obj);
 
};
 
} //end OCEAN2020
 
#endif
