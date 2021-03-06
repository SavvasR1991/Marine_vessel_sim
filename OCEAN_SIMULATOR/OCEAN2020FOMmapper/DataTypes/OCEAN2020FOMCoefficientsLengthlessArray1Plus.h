/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**defineHLAlengthlessVarArrayHeader.tlt
*********************************************************************/

#pragma once

#include "../dllExportOCEAN2020FOM_SISOSTD00112015.h"
#include "OCEAN2020FOM_SISOSTD00112015Enums.h"
#include <vlutil/vlMachineTypes.h>
#include <vlutil/vlString.h>
#include <vl/globalObjectDesignator.h>
#include <vlpi/netStructs.h>
#include <vlpi/entityType.h>
#include <vlpi/entityIdentifier.h>
#include <matrix/vlVector.h>
#include <vector>

namespace OCEAN2020 {

//! \class  DtOCEAN2020FOMCoefficientsLengthlessArray1Plus
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMCoefficientsLengthlessArray1Plus
{
public:
   DtOCEAN2020FOMCoefficientsLengthlessArray1Plus();

   ~DtOCEAN2020FOMCoefficientsLengthlessArray1Plus();

   DtOCEAN2020FOMCoefficientsLengthlessArray1Plus(const DtOCEAN2020FOMCoefficientsLengthlessArray1Plus& orig);

   DtOCEAN2020FOMCoefficientsLengthlessArray1Plus& operator=(const DtOCEAN2020FOMCoefficientsLengthlessArray1Plus& orig);

   virtual void setCoefficientsLengthlessArray1Plus(const std::vector<DtFloat32>& val);
   virtual const std::vector<DtFloat32>& coefficientsLengthlessArray1Plus() const;
   
   bool operator==(const DtOCEAN2020FOMCoefficientsLengthlessArray1Plus& other) const;
   bool operator!=(const DtOCEAN2020FOMCoefficientsLengthlessArray1Plus& other) const;
   
   int netSize() const;
   static int octetBoundary();
   unsigned int getPaddingSize(unsigned int byteOffset, unsigned int boundary) const;

   void writeToBuffer( char* buffer ) const;
   void fillFromBuffer( const char* buffer, int bufferSize, int offset );

   virtual void printData() const;

   virtual void printDataToStream(std::ostream &) const;
protected:
   
std::vector<DtFloat32> myCoefficientsLengthlessArray1Plus;
};

DT_DLL_OCEAN2020FOM_SISOSTD00112015 std::ostream& operator<<(std::ostream& stream, const DtOCEAN2020FOMCoefficientsLengthlessArray1Plus&);

} //end OCEAN2020
