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

//! \class  DtOCEAN2020FOMOctetArray3
//! \ingroup OCEAN2020FOM_SISOSTD00112015
class DT_DLL_OCEAN2020FOM_SISOSTD00112015 DtOCEAN2020FOMOctetArray3
{
public:
   DtOCEAN2020FOMOctetArray3();
   ~DtOCEAN2020FOMOctetArray3();
   DtOCEAN2020FOMOctetArray3(const DtOCEAN2020FOMOctetArray3& orig);
   DtOCEAN2020FOMOctetArray3& operator=(const DtOCEAN2020FOMOctetArray3& orig);


   virtual void setOctetArray3Item(int index, DtU8& val);
   virtual void setOctetArray3(const DtU8 val[3]);

   virtual const DtU8* octetArray3Item(int index) const;
   virtual const DtU8* octetArray3() const;
   
   bool operator==(const DtOCEAN2020FOMOctetArray3& other) const;
   bool operator!=(const DtOCEAN2020FOMOctetArray3& other) const;
   
   int netSize() const;
   static int octetBoundary();
   unsigned int getPaddingSize(unsigned int byteOffset, unsigned int boundary) const;

   void writeToBuffer( char* buffer ) const;
   void fillFromBuffer( const char* buffer, int bufferSize, int offset );

   virtual void printData() const;

   virtual void printDataToStream(std::ostream &) const;
   
protected:

    DtU8 myOctetArray3[3];
};

DT_DLL_OCEAN2020FOM_SISOSTD00112015 std::ostream& operator<<(std::ostream& stream, const DtOCEAN2020FOMOctetArray3&);
} //end OCEAN2020