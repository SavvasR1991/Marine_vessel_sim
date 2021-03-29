/*+*******************************************************************************
#
# Project    : OCEAN 2020 (EDA)
#
# Original   : 2019/06/25
#
# Copyright (c) 2019 ANTYCIP SIMULATION
#*******************************************************************************-*/
 
//! \file OCEAN2020RadioReceiverStateRepository.h
//! \brief Contains the DtOCEAN2020FOMRadioReceiverStateRepository class declaration.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
 
#pragma once

//Project include
#include "DataTypes/OCEAN2020FOM_SISOSTD00112015Enums.h"
#include "DataTypes/OCEAN2020FOMAntennaPatternVariantStruct.h"
#include "DataTypes/OCEAN2020FOMRxSpuriousLeveldBArray.h"
#include "dllExportOCEAN2020FOM_SISOSTD00112015.h"

//VRLINK include
#include <matrix/vlVector.h>
#include <vector>
#include <vl/globalObjectDesignator.h>
#include <vl/hlaLogicalTime.h>
#include <vl/hlaLogicalTimeInterval.h>
#include <vl/radioReceiverRepository.h>
#include <vlpi/entityIdentifier.h>
#include <vlpi/entityType.h>
#include <vlutil/vlString.h>
 

namespace OCEAN2020 {
 
//! Instances of DtOCEAN2020FOMRadioReceiverStateRepository are used to store state data for
//! EmbeddedSystem.RadioReceiver.OCEAN2020RadioReceiver objects.
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMRadioReceiverStateRepository : public DtRadioReceiverRepository
{
public:
   //! Constructor.
   DtOCEAN2020FOMRadioReceiverStateRepository();
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMRadioReceiverStateRepository();
 
   //! Copy Constructor.
   DtOCEAN2020FOMRadioReceiverStateRepository(const DtOCEAN2020FOMRadioReceiverStateRepository& orig);
 
   //! Assignment Operator.
   DtOCEAN2020FOMRadioReceiverStateRepository& operator=(const DtOCEAN2020FOMRadioReceiverStateRepository& orig);
 
   //! Return a copy/empty object of the same type as this.
   virtual DtStateRepository* clone(bool copy) const;
 
   //! Create a DtOCEAN2020FOMRadioReceiverStateRepository.
   static DtOCEAN2020FOMRadioReceiverStateRepository* create();
   
   //! Print data to the DtInfo stream
   virtual void printData() const;
 
   //! Print data to the specified stream
   virtual void printDataToStream(std::ostream& stream) const;
 

   //! Set the ReceiverMaxGaindB.
   virtual void setReceiverMaxGaindB(DtFloat32 val);
 
   //! Get the ReceiverMaxGaindB."
   virtual DtFloat32 receiverMaxGaindB() const;

   //! Set the Sensitivity.
   virtual void setSensitivity(DtFloat32 val);
 
   //! Get the Sensitivity."
   virtual DtFloat32 sensitivity() const;

   //! Set the AntennaPatternData.
   virtual void setAntennaPatternData(const DtOCEAN2020FOMAntennaPatternVariantStruct& val);
 
   //! Get the AntennaPatternData."
   virtual const DtOCEAN2020FOMAntennaPatternVariantStruct& antennaPatternData() const;

   //! Set the ReceiverAntiJammingTechnique.
   virtual void setReceiverAntiJammingTechnique(const DtAntiJammingTechniqueEnum& val);
 
   //! Get the ReceiverAntiJammingTechnique."
   virtual const DtAntiJammingTechniqueEnum& receiverAntiJammingTechnique() const;

   //! Set the ReceiverType.
   virtual void setReceiverType(const DtTxRxTypeEnum& val);
 
   //! Get the ReceiverType."
   virtual const DtTxRxTypeEnum& receiverType() const;

   //! Set the ReceiverShapeFactor.
   virtual void setReceiverShapeFactor(DtFloat32 val);
 
   //! Get the ReceiverShapeFactor."
   virtual DtFloat32 receiverShapeFactor() const;

   //! Set the ReceiverSpuriousLevel.
   virtual void setReceiverSpuriousLevel(const DtOCEAN2020FOMRxSpuriousLeveldBArray& val);
 
   //! Get the ReceiverSpuriousLevel."
   virtual const DtOCEAN2020FOMRxSpuriousLeveldBArray& receiverSpuriousLevel() const;

   //! Set the ReceiverChannelBandwidthHz.
   virtual void setReceiverChannelBandwidthHz(DtFloat32 val);
 
   //! Get the ReceiverChannelBandwidthHz."
   virtual DtFloat32 receiverChannelBandwidthHz() const;

   //! Set the FrequencyBandwidth.
   virtual void setFrequencyBandwidth(DtFloat32 val);
 
   //! Get the FrequencyBandwidth."
   virtual DtFloat32 frequencyBandwidth() const;

   //! Set the Frequency.
   virtual void setFrequency(DtU64 val);
 
   //! Get the Frequency."
   virtual DtU64 frequency() const;

   //! Set the OperatingFrequency.
   virtual void setOperatingFrequency(DtU64 val);
 
   //! Get the OperatingFrequency."
   virtual DtU64 operatingFrequency() const;

   //! Set the ChannelBandwidth.
   virtual void setChannelBandwidth(DtFloat32 val);
 
   //! Get the ChannelBandwidth."
   virtual DtFloat32 channelBandwidth() const;

   //! Set the NoiseFigure.
   virtual void setNoiseFigure(DtFloat32 val);
 
   //! Get the NoiseFigure."
   virtual DtFloat32 noiseFigure() const;

protected:
   DtFloat32 myReceiverMaxGaindB;
   DtFloat32 mySensitivity;
   DtOCEAN2020FOMAntennaPatternVariantStruct myAntennaPatternData;
   DtAntiJammingTechniqueEnum myReceiverAntiJammingTechnique;
   DtTxRxTypeEnum myReceiverType;
   DtFloat32 myReceiverShapeFactor;
   DtOCEAN2020FOMRxSpuriousLeveldBArray myReceiverSpuriousLevel;
   DtFloat32 myReceiverChannelBandwidthHz;
   DtFloat32 myFrequencyBandwidth;
   DtU64 myFrequency;
   DtU64 myOperatingFrequency;
   DtFloat32 myChannelBandwidth;
   DtFloat32 myNoiseFigure;   
};

} //end OCEAN2020
