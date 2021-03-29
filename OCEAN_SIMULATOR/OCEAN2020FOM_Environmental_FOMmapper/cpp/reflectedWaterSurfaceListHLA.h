/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**hrefListHeader.tlt
*********************************************************************/
 
//! \file reflectedWaterSurfaceListHLA.h
//! \brief Contains the DtReflectedOCEAN2020FOMWaterSurfaceList class declaration.
//! \ingroup OCEAN2020FOM_Environmental
 
#pragma once
 
#if DtHLA
 
#include "dllExport.h"
#include <vl/reflectedObjectListHLA.h>
#include "reflectedWaterSurfaceHLA.h"
 
namespace OCEAN2020 {
 
//! Instances of DtReflectedOCEAN2020FOMWaterSurfaceList manage a list of
//! DtReflectedOCEAN2020FOMWaterSurface objects.
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtReflectedOCEAN2020FOMWaterSurfaceList : public DtReflectedObjectList
{
public:
   //! Constructor. 
   DtReflectedOCEAN2020FOMWaterSurfaceList(DtExerciseConn* exConn,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor - only subscribe to the RTI::ObjectClassHandles
   //! in handleList.
   DtReflectedOCEAN2020FOMWaterSurfaceList(DtExerciseConn* exConn,
      const DtList *handleList, const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Destructor.
   virtual ~DtReflectedOCEAN2020FOMWaterSurfaceList();
 
private:
 
   //! Copy constructor not implemented - cannot be copied.
   DtReflectedOCEAN2020FOMWaterSurfaceList(const DtReflectedOCEAN2020FOMWaterSurfaceList& orig);
 
   //! Assignment operator not implemented - cannot be copied.
   DtReflectedOCEAN2020FOMWaterSurfaceList& operator=(const DtReflectedOCEAN2020FOMWaterSurfaceList&orig);
 
public:
 
   //! Look up by identifier.
   virtual DtReflectedOCEAN2020FOMWaterSurface* lookup(
#if DtHLA_1516
      RTI::ObjectInstanceHandle id);
#else
      RTI::ObjectHandle id);
#endif
 
   //! Look up by name.
   virtual DtReflectedOCEAN2020FOMWaterSurface* lookup(
      const DtGlobalObjectDesignator& objName);
 
   //! Get the first reflected object in the list.
   virtual DtReflectedOCEAN2020FOMWaterSurface* first() const;
 
   //! Get the last reflected object in the list.
   virtual DtReflectedOCEAN2020FOMWaterSurface* last() const;
 
   //! WaterSurface added callback registration
   virtual void addWaterSurfaceAdditionCallback(
      DtOCEAN2020FOMWaterSurfaceCallbackFunction cb, void* userData);
 
   //! WaterSurface added callback deregistration
   virtual void removeWaterSurfaceAdditionCallback(
      DtOCEAN2020FOMWaterSurfaceCallbackFunction cb, void* userData);
 
   //! WaterSurface removed callback registration
   virtual void addWaterSurfaceRemovalCallback(
      DtOCEAN2020FOMWaterSurfaceCallbackFunction cb, void* userData);
 
   //! WaterSurface removed callback deregistration
   virtual void removeWaterSurfaceRemovalCallback(
      DtOCEAN2020FOMWaterSurfaceCallbackFunction cb, void* userData);
 
protected:
 
   //! Override of virtual function.  Here, we create a DtReflectedOCEAN2020FOMWaterSurface
   virtual DtReflectedObject* newReflectedObject(DtHlaObject* obj) const;
 
   //! Called from processDiscoverObject() after a remote WaterSurface has
   //! been added to the list.  Default implementation prints a message.
   //! Subclasses can override this function to add functionality on
   //! addition.  obj will be an instance of a class derived from DtReflectedObj.
   virtual void objectAdded(DtReflectedObject* obj);
 
};
 
} //end OCEAN2020
 
#endif