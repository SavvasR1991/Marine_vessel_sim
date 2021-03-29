/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**hinterHeader.tlt
*********************************************************************/
 
//! \file txRx_Link_OnReqInterHLA.h
//! \brief Contains the DtOCEAN2020FOMTxRx_Link_OnReqInter class declaration.
//! \ingroup OCEAN2020FOM_COMMCE
 
#pragma once
 
#if DtHLA 
 
#include "dllExport.h"
#include <vl/interactionWithEncDec.h>
#include "DataTypes/OCEAN2020FOM_COMMCEEnums.h"
#include <vlutil/vlString.h>
#include <vl/globalObjectDesignator.h>
#include <vl/hlaLogicalTime.h>
#include <vl/hlaLogicalTimeInterval.h>
#include <vlpi/entityType.h>
#include <vlpi/entityIdentifier.h>
#include <matrix/vlVector.h>
 
 
class DtExerciseConn;
 namespace OCEAN2020 {
 
class DtOCEAN2020FOMTxRx_Link_OnReqInter;
 
//! DtOCEAN2020FOMTxRx_Link_OnReqInter  callback function signature.
typedef void (*DtOCEAN2020FOMTxRx_Link_OnReqInterCb) (DtOCEAN2020FOMTxRx_Link_OnReqInter* inter, 
   void* usr);
 
//! Instances of DtOCEAN2020FOMTxRx_Link_OnReqInter are used to store state data for
//! TxRx_Link_OnReq interactions.
//! \ingroup OCEAN2020FOM_COMMCE
class DT_DLL_OCEAN2020FOM_COMMCE DtOCEAN2020FOMTxRx_Link_OnReqInter : public DtInteractionWithEncDec
{
public:
 
   //! Constructor.
   DtOCEAN2020FOMTxRx_Link_OnReqInter();
 
   //! Destructor.
   virtual ~DtOCEAN2020FOMTxRx_Link_OnReqInter();
 
   //! Copy constructor.
   DtOCEAN2020FOMTxRx_Link_OnReqInter(const DtOCEAN2020FOMTxRx_Link_OnReqInter& orig);
 
   //! Assignment operator.
   DtOCEAN2020FOMTxRx_Link_OnReqInter& operator=(const DtOCEAN2020FOMTxRx_Link_OnReqInter& orig);
 
   //! Print the interaction's data.
   virtual void printData() const;
 
   //! Print the interaction's data to the specified stream
   virtual void printDataToStream(std::ostream& stream) const;
   

   //! FrequencyHopping mutator.
   virtual void setFrequencyHopping(DtU64 val);
 
   //! FrequencyHopping accessor.
   virtual DtU64 frequencyHopping() const;
 


   //! Rx_HostObjectID mutator.
   virtual void setRx_HostObjectID(const DtGlobalObjectDesignator& val);
 
   //! Rx_HostObjectID accessor.
   virtual const DtGlobalObjectDesignator& rx_HostObjectID() const;
 


   //! Tx_HostObjectID mutator.
   virtual void setTx_HostObjectID(const DtGlobalObjectDesignator& val);
 
   //! Tx_HostObjectID accessor.
   virtual const DtGlobalObjectDesignator& tx_HostObjectID() const;
 


      
   //! Name of the interaction. (Not necessarily the ClassName from the FOM.)
   virtual const char* name() const { return "DtOCEAN2020FOMTxRx_Link_OnReqInter"; }
 
public:
 
   //! Create a DtOCEAN2020FOMTxRx_Link_OnReqInter.
   //! Caller is responsible for deletion.
   static DtInteraction* create();
 
   //! Add (register)/Remove (deregister) function to be called when
   //! interaction occurs.
   static void addCallback(DtExerciseConn* conn,
      DtOCEAN2020FOMTxRx_Link_OnReqInterCb cb, void* usr,
      DtDDMRegionSP region = DtDDMRegionSP());
   static void removeCallback(DtExerciseConn* conn,
      DtOCEAN2020FOMTxRx_Link_OnReqInterCb cb, void* usr,
      DtDDMRegionSP region = DtDDMRegionSP());
 
protected:
   virtual const char* interactionClassToUse(DtExerciseConn* exConn) const;
 
   virtual DtInteractionDecoder* createDecoder(DtExerciseConn* exConn) const;
   virtual DtInteractionEncoder* createEncoder(DtExerciseConn* exConn) const;
      
      
protected:
   DtU64 myFrequencyHopping;
   DtGlobalObjectDesignator myRx_HostObjectID;
   DtGlobalObjectDesignator myTx_HostObjectID;

};

} //end OCEAN2020
 
#endif