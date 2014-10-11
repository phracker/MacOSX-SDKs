/*
     File:       CarbonCore/NumberFormatting.h
 
     Contains:   Utilites for formatting numbers
 
     Version:    CarbonCore-317~6
 
     Copyright:  © 1996-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __NUMBERFORMATTING__
#define __NUMBERFORMATTING__

#ifndef __CONDITIONALMACROS__
#include <CarbonCore/ConditionalMacros.h>
#endif

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __INTLRESOURCES__
#include <CarbonCore/IntlResources.h>
#endif





#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

/*

    Here are the current System 7 routine names and the translations to the older forms.
    Please use the newer forms in all new code and migrate the older names out of existing
    code as maintainance permits.
    
    New Name                    Old Name(s)
    
    ExtendedToString            FormatX2Str
    FormatRecToString           Format2Str
    NumToString             
    StringToExtended            FormatStr2X
    StringToFormatRec           Str2Format
    StringToNum             

*/
struct NumFormatString {
  UInt8               fLength;
  UInt8               fVersion;
  char                data[254];              /* private data */
};
typedef struct NumFormatString          NumFormatString;
typedef NumFormatString                 NumFormatStringRec;
typedef short                           FormatStatus;
enum {
  fVNumber                      = 0     /* first version of NumFormatString */
};

typedef SInt8                           FormatClass;
enum {
  fPositive                     = 0,
  fNegative                     = 1,
  fZero                         = 2
};

typedef SInt8                           FormatResultType;
enum {
  fFormatOK                     = 0,
  fBestGuess                    = 1,
  fOutOfSynch                   = 2,
  fSpuriousChars                = 3,
  fMissingDelimiter             = 4,
  fExtraDecimal                 = 5,
  fMissingLiteral               = 6,
  fExtraExp                     = 7,
  fFormatOverflow               = 8,
  fFormStrIsNAN                 = 9,
  fBadPartsTable                = 10,
  fExtraPercent                 = 11,
  fExtraSeparator               = 12,
  fEmptyFormatString            = 13
};

struct FVector {
  short               start;
  short               length;
};
typedef struct FVector                  FVector;
/* index by [fPositive..fZero] */
typedef FVector                         TripleInt[3];
/*
 *  stringtonum()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  numtostring()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  StringToNum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
StringToNum(
  ConstStr255Param   theString,
  long *             theNum);


/*
 *  NumToString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
NumToString(
  long     theNum,
  Str255   theString);


/*
 *  ExtendedToString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern FormatStatus 
ExtendedToString(
  const extended80 *       x,
  const NumFormatString *  myCanonical,
  const NumberParts *      partsTable,
  Str255                   outString);


/*
 *  StringToExtended()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern FormatStatus 
StringToExtended(
  ConstStr255Param         source,
  const NumFormatString *  myCanonical,
  const NumberParts *      partsTable,
  extended80 *             x);


/*
 *  StringToFormatRec()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern FormatStatus 
StringToFormatRec(
  ConstStr255Param     inString,
  const NumberParts *  partsTable,
  NumFormatString *    outString);


/*
 *  FormatRecToString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern FormatStatus 
FormatRecToString(
  const NumFormatString *  myCanonical,
  const NumberParts *      partsTable,
  Str255                   outString,
  TripleInt                positions);



#if OLDROUTINENAMES
#define FormatX2Str(x, myCanonical, partsTable, outString)  \
         ExtendedToString( x, myCanonical, partsTable, outString)
#define FormatStr2X(source, myCanonical, partsTable, x)  \
         StringToExtended( source, myCanonical, partsTable, x)
#define Str2Format(inString, partsTable, outString)  \
         StringToFormatRec(inString, partsTable, outString)
#define Format2Str(myCanonical, partsTable, outString, positions)  \
         FormatRecToString(myCanonical, partsTable, outString, positions)
#endif  /* OLDROUTINENAMES */


#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif /* __NUMBERFORMATTING__ */

