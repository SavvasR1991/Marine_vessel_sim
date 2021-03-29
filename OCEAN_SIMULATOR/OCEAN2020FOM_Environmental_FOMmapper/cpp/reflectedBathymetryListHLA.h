/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**hrefListHeader.tlt
*********************************************************************/
 
//! \file reflectedBathymetryListHLA.h
//! \brief Contains the DtReflectedOCEAN2020FOMBathymetryList class declaration.
//! \ingroup OCEAN2020FOM_Environmental
 
#pragma once
 
#if DtHLA
 
#include "dllExport.h"
#include <vl/reflectedObjectListHLA.h>
#include "reflectedBathymetryHLA.h"
 
namespace OCEAN2020 {
 
//! Instances of DtReflectedOCEAN2020FOMBathymetryList manage a list of
//! DtReflectedOCEAN2020FOMBathymetry objects.
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtReflectedOCEAN2020FOMBathymetryList : public DtReflectedObjectList
{
public:
   //! Constructor. 
   DtReflectedOCEAN2020FOMBathymetryList(DtExerciseConn* exConn,
      const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Constructor - only subscribe to the RTI::ObjectClassHandles
   //! in handleList.
   DtReflectedOCEAN2020FOMBathymetryList(DtExerciseConn* exConn,
      const DtList *handleList, const DtDDMRegionSet* regionSetToUse = 0);
 
   //! Destructor.
   virtual ~DtReflectedOCEAN2020FOMBathymetryList();
 
private:
 
   //! Copy constructor not implemented - cannot be copied.
   DtReflectedOCEAN2020FOMBathymetryList(const DtReflectedOCEAN2020FOMBathymetryList& orig);
 
   //! Assignment operator not implemented - cannot be copied.
   DtReflectedOCEAN2020FOMBathymetryList& operator=(const DtReflectedOCEAN2020FOMBathymetryList&orig);
 
public:
 
   //! Look up by identifier.
   virtual DtReflectedOCEAN2020FOMBathymetry* lookup(
#if DtHLA_1516
      RTI::ObjectInstanceHandle id);
#else
      RTI::ObjectHandle id);
#endif
 
   //! Look up by name.
   virtual DtReflectedOCEAN2020FOMBathymetry* lookup(
      const DtGlobalObjectDesignator& objName);
 
   //! Get the first reflected object in the list.
   virtual DtReflectedOCEAN2020FOMBathymetry* first() const;
 
   //! Get the last reflected object in the list.
   virtual DtReflectedOCEAN2020FOMBathymetry* last() const;
 
   //! Bathymetry added callback registration
   virtual void addBathymetryAdditionCallback(
      DtOCEAN2020FOMBathymetryCallbackFunction cb, void* userData);
 
   //! Bathymetry added callback deregistration
   virtual void removeBathymetryAdditionCallback(
      DtOCEAN2020FOMBathymetryCallbackFunction cb, void* userData);
 
   //! Bathymetry removed callback registration
   virtual void addBathymetryRemovalCallback(
      DtOCEAN2020FOMBathymetryCallbackFunction cb, void* userData);
 
   //! Bathymetry removed callback deregistration
   virtual void removeBathymetryRemovalCallback(
      DtOCEAN2020FOMBathymetryCallbackFunction cb, void* userData);
 
protected:
 
   //! Override of virtual function.  Here, we create a DtReflectedOCEAN2020FOMBathymetry
   virtual DtReflectedObject* newReflectedObject(DtHlaObject* obj) const;
 
   //! Called from processDiscoverObject() after a remote Bathymetry has
   //! been added to the list.  Default implementation prints a message.
   //! Subclasses can override this function to add functionality on
   //! addition.  obj will be an instance of a class derived from DtReflectedObj.
   virtual void objectAdded(DtReflectedObject* obj);
 
};
 
} //end OCEAN2020
 
#endif