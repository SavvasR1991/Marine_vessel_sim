/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**hrefListHeader.tlt
*********************************************************************/
 
//! \file reflectedWaterColumnListHLA.h
//! \brief Contains the DtReflectedOCEAN2020FOMWaterColumnList class declaration.
//! \ingroup OCEAN2020FOM_Environmental
 
#pragma once
 
#if DtHLA
 
#include "dllExport.h"
#include <vl/reflectedObjectListHLA.h>
#include "reflectedWaterColumnHLA.h"
 
namespace OCEAN2020 {
 
//! Instances of DtReflectedOCEAN2020FOMWaterColumnList manage a list of
//! DtReflectedOCEAN2020FOMWaterColumn objects.
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtReflectedOCEAN2020FOMWaterColumnList : public DtReflectedObjectList
{
public:
   //! Constructor. 
   DtReflectedOCEAN2020FOMWaterColumnList(DtExerciseConn* exConn,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor - only subscribe to the RTI::ObjectClassHandles
   //! in handleList.
   DtReflectedOCEAN2020FOMWaterColumnList(DtExerciseConn* exConn,
      const DtList *handleList, const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Destructor.
   virtual ~DtReflectedOCEAN2020FOMWaterColumnList();
 
private:
 
   //! Copy constructor not implemented - cannot be copied.
   DtReflectedOCEAN2020FOMWaterColumnList(const DtReflectedOCEAN2020FOMWaterColumnList& orig);
 
   //! Assignment operator not implemented - cannot be copied.
   DtReflectedOCEAN2020FOMWaterColumnList& operator=(const DtReflectedOCEAN2020FOMWaterColumnList&orig);
 
public:
 
   //! Look up by identifier.
   virtual DtReflectedOCEAN2020FOMWaterColumn* lookup(
#if DtHLA_1516
      RTI::ObjectInstanceHandle id);
#else
      RTI::ObjectHandle id);
#endif
 
   //! Look up by name.
   virtual DtReflectedOCEAN2020FOMWaterColumn* lookup(
      const DtGlobalObjectDesignator& objName);
 
   //! Get the first reflected object in the list.
   virtual DtReflectedOCEAN2020FOMWaterColumn* first() const;
 
   //! Get the last reflected object in the list.
   virtual DtReflectedOCEAN2020FOMWaterColumn* last() const;
 
   //! WaterColumn added callback registration
   virtual void addWaterColumnAdditionCallback(
      DtOCEAN2020FOMWaterColumnCallbackFunction cb, void* userData);
 
   //! WaterColumn added callback deregistration
   virtual void removeWaterColumnAdditionCallback(
      DtOCEAN2020FOMWaterColumnCallbackFunction cb, void* userData);
 
   //! WaterColumn removed callback registration
   virtual void addWaterColumnRemovalCallback(
      DtOCEAN2020FOMWaterColumnCallbackFunction cb, void* userData);
 
   //! WaterColumn removed callback deregistration
   virtual void removeWaterColumnRemovalCallback(
      DtOCEAN2020FOMWaterColumnCallbackFunction cb, void* userData);
 
protected:
 
   //! Override of virtual function.  Here, we create a DtReflectedOCEAN2020FOMWaterColumn
   virtual DtReflectedObject* newReflectedObject(DtHlaObject* obj) const;
 
   //! Called from processDiscoverObject() after a remote WaterColumn has
   //! been added to the list.  Default implementation prints a message.
   //! Subclasses can override this function to add functionality on
   //! addition.  obj will be an instance of a class derived from DtReflectedObj.
   virtual void objectAdded(DtReflectedObject* obj);
 
};
 
} //end OCEAN2020
 
#endif