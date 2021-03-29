/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file mineEventReportInterDecoderHLA.h
//! \brief Contains the DtOCEAN2020FOMMineEventReportInterDecoder class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once
 
#if DtHLA 

//Project include
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <vl\eventReportDecoder.h>
 
namespace OCEAN2020 {
 
class DtOCEAN2020FOMMineEventReportInter;
 
//! Instances of DtOCEAN2020FOMMineEventReportInterDecoder are used to decode
//! data from the network into DtOCEAN2020FOMMineEventReportInter
//! objects.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMMineEventReportInterDecoder : public DtEventReportDecoder
{
public:
   //! Constructor.
   DtOCEAN2020FOMMineEventReportInterDecoder(DtExerciseConn* exConn,
      DtInterClassDesc* classDesc);
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMMineEventReportInterDecoder();
 
   //! Copy constructor.
   DtOCEAN2020FOMMineEventReportInterDecoder(const DtOCEAN2020FOMMineEventReportInterDecoder& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMMineEventReportInterDecoder& operator=(const DtOCEAN2020FOMMineEventReportInterDecoder& orig);
 
protected:

};
 
} //end OCEAN2020
 
#endif
