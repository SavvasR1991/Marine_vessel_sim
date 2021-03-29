/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file AISStateRepository.h
//! \brief Contains the DtOCEAN2020FOMAISStateRepository class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once

//Project include
#include "DataTypes/OCEAN2020FOM_SISOSTD00112015Enums.h"
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <matrix/vlVector.h>
#include <vl/embeddedSystemRepository.h>
#include <vl/globalObjectDesignator.h>
#include <vl/hlaLogicalTime.h>
#include <vl/hlaLogicalTimeInterval.h>
#include <vlpi/entityType.h>
#include <vlpi/entityIdentifier.h>
#include <vlutil/vlString.h>
#include <vector>
 

namespace OCEAN2020 {
 
//! Instances of DtOCEAN2020FOMAISStateRepository are used to store state data for
//! EmbeddedSystem.AIS objects.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMAISStateRepository : public DtEmbeddedSystemRepository
{
public:
   //! Constructor.
   DtOCEAN2020FOMAISStateRepository();
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMAISStateRepository();
 
   //! Copy Constructor.
   DtOCEAN2020FOMAISStateRepository(const DtOCEAN2020FOMAISStateRepository& orig);
 
   //! Assignment Operator.
   DtOCEAN2020FOMAISStateRepository& operator=(const DtOCEAN2020FOMAISStateRepository& orig);
 
   //! Return a copy/empty object of the same type as this.
   virtual DtStateRepository* clone(bool copy) const;
 
   //! Create a DtOCEAN2020FOMAISStateRepository.
   static DtOCEAN2020FOMAISStateRepository* create();
   
   //! Print data to the DtInfo stream
   virtual void printData() const;
 
   //! Print data to the specified stream
   virtual void printDataToStream(std::ostream& stream) const;
 

   //! Set the ClassType.
   virtual void setClassType(const DtString& val);
 
   //! Get the ClassType."
   virtual const DtString& classType() const;

   //! Set the COG.
   virtual void setCOG(DtFloat32 val);
 
   //! Get the COG."
   virtual DtFloat32 COG() const;

   //! Set the Destination.
   virtual void setDestination(const DtString& val);
 
   //! Get the Destination."
   virtual const DtString& destination() const;

   //! Set the ETA.
   virtual void setETA(const DtString& val);
 
   //! Get the ETA."
   virtual const DtString& ETA() const;

   //! Set the IMO.
   virtual void setIMO(DtU32 val);
 
   //! Get the IMO."
   virtual DtU32 IMO() const;

   //! Set the Latitude.
   virtual void setLatitude(DtFloat64 val);
 
   //! Get the Latitude."
   virtual DtFloat64 latitude() const;

   //! Set the Longitude.
   virtual void setLongitude(DtFloat64 val);
 
   //! Get the Longitude."
   virtual DtFloat64 longitude() const;

   //! Set the MMSI.
   virtual void setMMSI(DtU32 val);
 
   //! Get the MMSI."
   virtual DtU32 MMSI() const;

   //! Set the Name.
   virtual void setName(const DtString& val);
 
   //! Get the Name."
   virtual const DtString& name() const;

   //! Set the NavigationStatus.
   virtual void setNavigationStatus(const DtString& val);
 
   //! Get the NavigationStatus."
   virtual const DtString& navigationStatus() const;

   //! Set the SOG.
   virtual void setSOG(DtFloat32 val);
 
   //! Get the SOG."
   virtual DtFloat32 SOG() const;

   //! Set the TB.
   virtual void setTB(DtFloat32 val);
 
   //! Get the TB."
   virtual DtFloat32 TB() const;

   //! Set the TH.
   virtual void setTH(DtFloat32 val);
 
   //! Get the TH."
   virtual DtFloat32 TH() const;

   //! Set the TurnRate.
   virtual void setTurnRate(DtFloat32 val);
 
   //! Get the TurnRate."
   virtual DtFloat32 turnRate() const;

   //! Set the UTC_s.
   virtual void setUTC_s(const DtString& val);
 
   //! Get the UTC_s."
   virtual const DtString& UTC_s() const;

   //! Set the UTC_TimeStamp.
   virtual void setUTC_TimeStamp(const DtString& val);
 
   //! Get the UTC_TimeStamp."
   virtual const DtString& UTC_TimeStamp() const;

   //! Set the RCS.
   virtual void setRCS(const DtString& val);
 
   //! Get the RCS."
   virtual const DtString& RCS() const;

   //! Set the VesselLength.
   virtual void setVesselLength(DtFloat32 val);
 
   //! Get the VesselLength."
   virtual DtFloat32 vesselLength() const;

   //! Set the VesselWidth.
   virtual void setVesselWidth(DtFloat32 val);
 
   //! Get the VesselWidth."
   virtual DtFloat32 vesselWidth() const;

   //! Set the VesselType.
   virtual void setVesselType(const DtString& val);
 
   //! Get the VesselType."
   virtual const DtString& vesselType() const;

protected:
   DtString myClassType;
   DtFloat32 myCOG;
   DtString myDestination;
   DtString myETA;
   DtU32 myIMO;
   DtFloat64 myLatitude;
   DtFloat64 myLongitude;
   DtU32 myMMSI;
   DtString myName;
   DtString myNavigationStatus;
   DtFloat32 mySOG;
   DtFloat32 myTB;
   DtFloat32 myTH;
   DtFloat32 myTurnRate;
   DtString myUTC_s;
   DtString myUTC_TimeStamp;
   DtString myRCS;
   DtFloat32 myVesselLength;
   DtFloat32 myVesselWidth;
   DtString myVesselType;
};

} //end OCEAN2020
