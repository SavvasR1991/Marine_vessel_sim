/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**defineHLAfixedArrayHeader.tlt
*********************************************************************/

#pragma once

#include "../dllExportOCEAN2020FOM_SISOSTD00112015.h"
#include "OCEAN2020FOM_SISOSTD00112015Enums.h"
#include <vlutil/vlMachineTypes.h>
#include <matrix/vlVector.h>
#include <vl/globalObjectDesignator.h>
#include <vlpi/entityType.h>
#include <vlpi/entityIdentifier.h>
#include <vlutil/vlString.h>
#include <vector>
namespace OCEAN2020 {

//! \class  DtOCEAN2020FOMTxHarmonicLeveldBArray
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMTxHarmonicLeveldBArray
{
public:
   DtOCEAN2020FOMTxHarmonicLeveldBArray();
   ~DtOCEAN2020FOMTxHarmonicLeveldBArray();
   DtOCEAN2020FOMTxHarmonicLeveldBArray(const DtOCEAN2020FOMTxHarmonicLeveldBArray& orig);
   DtOCEAN2020FOMTxHarmonicLeveldBArray& operator=(const DtOCEAN2020FOMTxHarmonicLeveldBArray& orig);


   virtual void setTxHarmonicLeveldBArrayItem(int index, DtFloat32& val);
   virtual void setTxHarmonicLeveldBArray(const DtFloat32 val[4]);

   virtual const DtFloat32* txHarmonicLeveldBArrayItem(int index) const;
   virtual const DtFloat32* txHarmonicLeveldBArray() const;
   
   bool operator==(const DtOCEAN2020FOMTxHarmonicLeveldBArray& other) const;
   bool operator!=(const DtOCEAN2020FOMTxHarmonicLeveldBArray& other) const;
   
   int netSize() const;
   static int octetBoundary();
   unsigned int getPaddingSize(unsigned int byteOffset, unsigned int boundary) const;

   void writeToBuffer( char* buffer ) const;
   void fillFromBuffer( const char* buffer, int bufferSize, int offset );

   virtual void printData() const;

   virtual void printDataToStream(std::ostream &) const;
   
protected:

    DtFloat32 myTxHarmonicLeveldBArray[4];
};

DT_DLL_OCEAN2020FOM_SISOSTD00112015 std::ostream& operator<<(std::ostream& stream, const DtOCEAN2020FOMTxHarmonicLeveldBArray&);
} //end OCEAN2020