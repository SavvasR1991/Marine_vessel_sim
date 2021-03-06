/*********************************************************************
**This file was generated by MAK Technologies' VR-Link Code Generator.
**defineHLAvariableArrayHeader.tlt
*********************************************************************/

#pragma once

#include "../dllExport.h"
#include "OCEAN2020FOM_EnvironmentalEnums.h"
#include <vlutil/vlMachineTypes.h>
#include <matrix/vlVector.h>
#include <vl/globalObjectDesignator.h>
#include <vlpi/entityType.h>
#include <vlpi/entityIdentifier.h>
#include <vlutil/vlString.h>
#include <vector>
namespace OCEAN2020 {

//! \class  DtOCEAN2020FOMVariableLengthFloat64Array
//! \ingroup OCEAN2020FOM_Environmental
class DT_DLL_OCEAN2020FOM_ENVIRONMENTAL DtOCEAN2020FOMVariableLengthFloat64Array
{
public:
   DtOCEAN2020FOMVariableLengthFloat64Array();
   ~DtOCEAN2020FOMVariableLengthFloat64Array();
   DtOCEAN2020FOMVariableLengthFloat64Array(const DtOCEAN2020FOMVariableLengthFloat64Array& orig);
   DtOCEAN2020FOMVariableLengthFloat64Array& operator=(const DtOCEAN2020FOMVariableLengthFloat64Array& orig);


   virtual void setVariableLengthFloat64Array(const std::vector<DtFloat64>& val);
   virtual const std::vector<DtFloat64>& variableLengthFloat64Array() const;
   
   bool operator==(const DtOCEAN2020FOMVariableLengthFloat64Array& other) const;
   bool operator!=(const DtOCEAN2020FOMVariableLengthFloat64Array& other) const;
   
   int netSize() const;
   static int octetBoundary();
   unsigned int getPaddingSize(unsigned int byteOffset, unsigned int boundary, unsigned int hint = 1) const;

   void writeToBuffer( char* buffer ) const;
   void fillFromBuffer( const char* buffer, int bufferSize, int offset );

   virtual void printData() const;

   virtual void printDataToStream(std::ostream &) const;
   
protected:

   std::vector<DtFloat64> myVariableLengthFloat64Array;
};

DT_DLL_OCEAN2020FOM_ENVIRONMENTAL std::ostream& operator<<(std::ostream& stream, const DtOCEAN2020FOMVariableLengthFloat64Array&);
} //end OCEAN2020
