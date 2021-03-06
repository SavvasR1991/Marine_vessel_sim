/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**hrefListHeader.tlt
*********************************************************************/
 
//! \file reflectedAirColumnListHLA.h
//! \brief Contains the DtReflectedOCEAN2020FOMAirColumnList class declaration.
//! \ingroup OCEAN2020FOM_Environmental
 
#pragma once
 
#if DtHLA
 
#include "dllExport.h"
#include <vl/reflectedObjectListHLA.h>
#include "reflectedAirColumnHLA.h"
 
namespace OCEAN2020 {
 
//! Instances of DtReflectedOCEAN2020FOMAirColumnList manage a list of
//! DtReflectedOCEAN2020FOMAirColumn objects.
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtReflectedOCEAN2020FOMAirColumnList : public DtReflectedObjectList
{
public:
   //! Constructor. 
   DtReflectedOCEAN2020FOMAirColumnList(DtExerciseConn* exConn,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor - only subscribe to the RTI::ObjectClassHandles
   //! in handleList.
   DtReflectedOCEAN2020FOMAirColumnList(DtExerciseConn* exConn,
      const DtList *handleList, const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Destructor.
   virtual ~DtReflectedOCEAN2020FOMAirColumnList();
 
private:
 
   //! Copy constructor not implemented - cannot be copied.
   DtReflectedOCEAN2020FOMAirColumnList(const DtReflectedOCEAN2020FOMAirColumnList& orig);
 
   //! Assignment operator not implemented - cannot be copied.
   DtReflectedOCEAN2020FOMAirColumnList& operator=(const DtReflectedOCEAN2020FOMAirColumnList&orig);
 
public:
 
   //! Look up by identifier.
   virtual DtReflectedOCEAN2020FOMAirColumn* lookup(
#if DtHLA_1516
      RTI::ObjectInstanceHandle id);
#else
      RTI::ObjectHandle id);
#endif
 
   //! Look up by name.
   virtual DtReflectedOCEAN2020FOMAirColumn* lookup(
      const DtGlobalObjectDesignator& objName);
 
   //! Get the first reflected object in the list.
   virtual DtReflectedOCEAN2020FOMAirColumn* first() const;
 
   //! Get the last reflected object in the list.
   virtual DtReflectedOCEAN2020FOMAirColumn* last() const;
 
   //! AirColumn added callback registration
   virtual void addAirColumnAdditionCallback(
      DtOCEAN2020FOMAirColumnCallbackFunction cb, void* userData);
 
   //! AirColumn added callback deregistration
   virtual void removeAirColumnAdditionCallback(
      DtOCEAN2020FOMAirColumnCallbackFunction cb, void* userData);
 
   //! AirColumn removed callback registration
   virtual void addAirColumnRemovalCallback(
      DtOCEAN2020FOMAirColumnCallbackFunction cb, void* userData);
 
   //! AirColumn removed callback deregistration
   virtual void removeAirColumnRemovalCallback(
      DtOCEAN2020FOMAirColumnCallbackFunction cb, void* userData);
 
protected:
 
   //! Override of virtual function.  Here, we create a DtReflectedOCEAN2020FOMAirColumn
   virtual DtReflectedObject* newReflectedObject(DtHlaObject* obj) const;
 
   //! Called from processDiscoverObject() after a remote AirColumn has
   //! been added to the list.  Default implementation prints a message.
   //! Subclasses can override this function to add functionality on
   //! addition.  obj will be an instance of a class derived from DtReflectedObj.
   virtual void objectAdded(DtReflectedObject* obj);
 
};
 
} //end OCEAN2020
 
#endif
