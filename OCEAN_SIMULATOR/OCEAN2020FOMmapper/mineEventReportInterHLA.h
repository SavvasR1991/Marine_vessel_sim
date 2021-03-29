/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file mineEventReportInterHLA.h
//! \brief Contains the DtOCEAN2020FOMMineEventReportInter class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once
 
#if DtHLA 

//Project include
#include "DataTypes/OCEAN2020FOM_SISOSTD00112015Enums.h"
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <matrix/vlVector.h>
#include <vl/eventReportInteraction.h>
#include <vl/globalObjectDesignator.h>
#include <vl/hlaLogicalTime.h>
#include <vl/hlaLogicalTimeInterval.h>
#include <vlpi/entityIdentifier.h>
#include <vlpi/entityType.h>
#include <vlutil/vlString.h>

 
class DtExerciseConn;
 namespace OCEAN2020 {
 
class DtOCEAN2020FOMMineEventReportInter;
 
//! DtOCEAN2020FOMMineEventReportInter  callback function signature.
typedef void (*DtOCEAN2020FOMMineEventReportInterCb) (DtOCEAN2020FOMMineEventReportInter* inter, 
   void* usr);
 
//! Instances of DtOCEAN2020FOMMineEventReportInter are used to store state data for
//! EventReport.MineEventReport interactions.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMMineEventReportInter : public DtEventReportInteraction
{
public:
 
   //! Constructor.
   DtOCEAN2020FOMMineEventReportInter();
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMMineEventReportInter();
 
   //! Copy constructor.
   DtOCEAN2020FOMMineEventReportInter(const DtOCEAN2020FOMMineEventReportInter& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMMineEventReportInter& operator=(const DtOCEAN2020FOMMineEventReportInter& orig);
 
   //! Print the interaction's data.
   virtual void printData() const;
 
   //! Print the interaction's data to the specified stream
   virtual void printDataToStream(std::ostream& stream) const;
   

      
   //! Name of the interaction. (Not necessarily the ClassName from the FOM.)
   virtual const char* name() const { return "DtOCEAN2020FOMMineEventReportInter"; }
 
public:
 
   //! Create a DtOCEAN2020FOMMineEventReportInter.
   //! Caller is responsible for deletion.
   static DtInteraction* create();
 
   //! Add (register)/Remove (deregister) function to be called when
   //! interaction occurs.
   static void addCallback(DtExerciseConn* conn,
      DtOCEAN2020FOMMineEventReportInterCb cb, void* usr,
      DtDDMRegionSP region = DtDDMRegionSP());
   static void removeCallback(DtExerciseConn* conn,
      DtOCEAN2020FOMMineEventReportInterCb cb, void* usr,
      DtDDMRegionSP region = DtDDMRegionSP());
 
protected:
   virtual const char* interactionClassToUse(DtExerciseConn* exConn) const;
 
   virtual DtInteractionDecoder* createDecoder(DtExerciseConn* exConn) const;
   virtual DtInteractionEncoder* createEncoder(DtExerciseConn* exConn) const;
      
      
protected:

};

} //end OCEAN2020
 
#endif
