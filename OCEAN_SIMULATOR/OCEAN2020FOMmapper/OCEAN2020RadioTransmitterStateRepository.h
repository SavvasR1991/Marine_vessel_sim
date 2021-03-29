/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file OCEAN2020RadioTransmitterStateRepository.h
//! \brief Contains the DtOCEAN2020FOMRadioTransmitterStateRepository class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once

//Project include
#include "DataTypes/OCEAN2020FOM_SISOSTD00112015Enums.h"
#include "DataTypes/OCEAN2020FOMTxHarmonicLeveldBArray.h"
#include "DataTypes/OCEAN2020FOMTxSpuriousLeveldBArray.h"
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <matrix/vlVector.h>
#include <vector>
#include <vl/globalObjectDesignator.h>
#include <vl/hlaLogicalTime.h>
#include <vl/hlaLogicalTimeInterval.h>
#include <vl/radioTransmitterRepository.h>
#include <vlpi/entityIdentifier.h>
#include <vlpi/entityType.h>
#include <vlutil/vlString.h>
 

namespace OCEAN2020 {
 
//! Instances of DtOCEAN2020FOMRadioTransmitterStateRepository are used to store state data for
//! EmbeddedSystem.RadioTransmitter.OCEAN2020RadioTransmitter objects.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMRadioTransmitterStateRepository : public DtRadioTransmitterRepository
{
public:
   //! Constructor.
   DtOCEAN2020FOMRadioTransmitterStateRepository();
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMRadioTransmitterStateRepository();
 
   //! Copy Constructor.
   DtOCEAN2020FOMRadioTransmitterStateRepository(const DtOCEAN2020FOMRadioTransmitterStateRepository& orig);
 
   //! Assignment Operator.
   DtOCEAN2020FOMRadioTransmitterStateRepository& operator=(const DtOCEAN2020FOMRadioTransmitterStateRepository& orig);
 
   //! Return a copy/empty object of the same type as this.
   virtual DtStateRepository* clone(bool copy) const;
 
   //! Create a DtOCEAN2020FOMRadioTransmitterStateRepository.
   static DtOCEAN2020FOMRadioTransmitterStateRepository* create();
   
   //! Print data to the DtInfo stream
   virtual void printData() const;
 
   //! Print data to the specified stream
   virtual void printDataToStream(std::ostream& stream) const;
 

   //! Set the TransmitterMaxGaindB.
   virtual void setTransmitterMaxGaindB(DtFloat32 val);
 
   //! Get the TransmitterMaxGaindB."
   virtual DtFloat32 transmitterMaxGaindB() const;

   //! Set the TransmitterChannelBandwidthHz.
   virtual void setTransmitterChannelBandwidthHz(DtFloat32 val);
 
   //! Get the TransmitterChannelBandwidthHz."
   virtual DtFloat32 transmitterChannelBandwidthHz() const;

   //! Set the TransmitterAntiJammingTechnique.
   virtual void setTransmitterAntiJammingTechnique(const DtAntiJammingTechniqueEnum& val);
 
   //! Get the TransmitterAntiJammingTechnique."
   virtual const DtAntiJammingTechniqueEnum& transmitterAntiJammingTechnique() const;

   //! Set the TransmitterType.
   virtual void setTransmitterType(const DtTxRxTypeEnum& val);
 
   //! Get the TransmitterType."
   virtual const DtTxRxTypeEnum& transmitterType() const;

   //! Set the TransmitterHarmonicLevelAboveFunddB.
   virtual void setTransmitterHarmonicLevelAboveFunddB(const DtOCEAN2020FOMTxHarmonicLeveldBArray& val);
 
   //! Get the TransmitterHarmonicLevelAboveFunddB."
   virtual const DtOCEAN2020FOMTxHarmonicLeveldBArray& transmitterHarmonicLevelAboveFunddB() const;

   //! Set the TransmitterBroadbandNoisePowerDensity.
   virtual void setTransmitterBroadbandNoisePowerDensity(DtFloat32 val);
 
   //! Get the TransmitterBroadbandNoisePowerDensity."
   virtual DtFloat32 transmitterBroadbandNoisePowerDensity() const;

   //! Set the TransmitterSpuriousLevelAbovefunddB.
   virtual void setTransmitterSpuriousLevelAbovefunddB(const DtOCEAN2020FOMTxSpuriousLeveldBArray& val);
 
   //! Get the TransmitterSpuriousLevelAbovefunddB."
   virtual const DtOCEAN2020FOMTxSpuriousLeveldBArray& transmitterSpuriousLevelAbovefunddB() const;

   //! Set the OperatingFrequency.
   virtual void setOperatingFrequency(DtU64 val);
 
   //! Get the OperatingFrequency."
   virtual DtU64 operatingFrequency() const;

   //! Set the ChannelBandwidth.
   virtual void setChannelBandwidth(DtFloat32 val);
 
   //! Get the ChannelBandwidth."
   virtual DtFloat32 channelBandwidth() const;

protected:
   DtFloat32 myTransmitterMaxGaindB;
   DtFloat32 myTransmitterChannelBandwidthHz;
   DtAntiJammingTechniqueEnum myTransmitterAntiJammingTechnique;
   DtTxRxTypeEnum myTransmitterType;
   DtOCEAN2020FOMTxHarmonicLeveldBArray myTransmitterHarmonicLevelAboveFunddB;
   DtFloat32 myTransmitterBroadbandNoisePowerDensity;
   DtOCEAN2020FOMTxSpuriousLeveldBArray myTransmitterSpuriousLevelAbovefunddB;
   DtU64 myOperatingFrequency;
   DtFloat32 myChannelBandwidth;
};

} //end OCEAN2020
