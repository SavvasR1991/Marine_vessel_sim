/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file <!HlaRefObj!>.h
//! \brief Contains the DtReflectedOCEAN2020FOMAIS class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once
 
#if DtHLA

//Project include
#include "AISStateRepository.h"
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl/reflectedObjectHLA.h>

 
namespace OCEAN2020 {
 
class DtReflectedOCEAN2020FOMAIS;
 
//! Signature of the callback function that takes a DtReflectedOCEAN2020FOMAIS
//! and user data
//! \ingroup OCEAN2020FOM_SISOSTD00112015
typedef void (*DtOCEAN2020FOMAISCallbackFunction)(
   DtReflectedOCEAN2020FOMAIS* obj, void* userData);
 
//! Instances of DtReflectedOCEAN2020FOMAIS are used to represent a
//! simulated HLAobjectRoot.EmbeddedSystem.AIS
//! object reflected across a network. 
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtReflectedOCEAN2020FOMAIS : public DtReflectedObject
{
public:
   //! Function prototype for functions that create a
   //! DtOCEAN2020FOMAISStateRepository.
   typedef DtOCEAN2020FOMAISStateRepository* (*DtStateRepCreator)();
 
public:
   //! Constructor.
   DtReflectedOCEAN2020FOMAIS(DtHlaObject* obj, DtExerciseConn* exConn);
 
   //! Destructor.
   virtual ~DtReflectedOCEAN2020FOMAIS();
 
   //! Returns the AIS's state repository.
   virtual DtOCEAN2020FOMAISStateRepository* AISStateRep() const;
 
   //! Shorter version of lifeformRep.
   virtual DtOCEAN2020FOMAISStateRepository* Asr() const;
 
   //! Returns the next reflected AIS in the 
   //! DtReflectedOCEAN2020FOMAISList.
   virtual DtReflectedOCEAN2020FOMAIS* next() const;
 
   //! Returns the previous reflected AIS in the 
   //! DtReflectedOCEAN2020FOMAISList.
   virtual DtReflectedOCEAN2020FOMAIS* prev() const;
 
   //! Returns the next reflected AIS. Will cycle back to the first 
   //! remote AIS in the DtReflectedOCEAN2020FOMAISList.
   virtual DtReflectedOCEAN2020FOMAIS* wrapNext() const;
 
   //! Returns the previous reflected AIS. Will cycle back to the first 
   //! remote AIS in the DtReflectedOCEAN2020FOMAISList.
   virtual DtReflectedOCEAN2020FOMAIS* wrapPrev() const;
 
   //! Add a callback that is called when the DtReflectedOCEAN2020FOMAIS is
   //! updated.
   virtual void addPostUpdateCallback(
      DtOCEAN2020FOMAISCallbackFunction cb, void* userData);
 
   //! Remove the callback that is called when the DtReflectedOCEAN2020FOMAIS
   //! is updated.
   virtual void removePostUpdateCallback(
      DtOCEAN2020FOMAISCallbackFunction cb, void* userData);
 
public:
   //! Set the function to be called for creating state repositories.
   static DtStateRepCreator setStateRepCreator(DtStateRepCreator creator);
 
protected:
   //! Copy Constructor not implemented.
   DtReflectedOCEAN2020FOMAIS(const DtReflectedOCEAN2020FOMAIS& orig);
 
   //! Assignment operator not implemented.
   DtReflectedOCEAN2020FOMAIS& operator=(const DtReflectedOCEAN2020FOMAIS& orig);
 
protected:
   //! The function called to create state repositories.
   static DtStateRepCreator theStateRepCreator;
};
 
inline DtOCEAN2020FOMAISStateRepository* DtReflectedOCEAN2020FOMAIS::AISStateRep() const
{ 
   return (DtOCEAN2020FOMAISStateRepository*) myStateRep;
}
 
inline DtOCEAN2020FOMAISStateRepository* DtReflectedOCEAN2020FOMAIS::Asr() const
{
   return (DtOCEAN2020FOMAISStateRepository*) myStateRep;
}
 
} //end OCEAN2020
 
#endif
