/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file mineEventReportInterEncoderHLA.h
//! \brief This file provides a declaration of the class
//! DtOCEAN2020FOMMineEventReportInterEncoder.
 
#pragma once
 
#if DtHLA 

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl\eventReportEncoder.h>
 
namespace OCEAN2020 {
 
class DtOCEAN2020FOMMineEventReportInter;
 
//! Instances of DtOCEAN2020FOMMineEventReportInterEncoder are used to encode
//! data from DtOCEAN2020FOMMineEventReportInter objects into
//! network structures.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMMineEventReportInterEncoder : public DtEventReportEncoder
{
public:
   //! Constructor.
   DtOCEAN2020FOMMineEventReportInterEncoder(DtExerciseConn* exConn,
      DtInterClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMMineEventReportInterEncoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMMineEventReportInterEncoder(const DtOCEAN2020FOMMineEventReportInterEncoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMMineEventReportInterEncoder& operator=(const DtOCEAN2020FOMMineEventReportInterEncoder& orig);
 
protected:

};
 
} //end OCEAN2020
 
#endif
