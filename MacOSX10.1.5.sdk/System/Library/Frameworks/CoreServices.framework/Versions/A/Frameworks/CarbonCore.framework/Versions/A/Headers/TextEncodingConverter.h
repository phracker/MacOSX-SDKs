/*
     File:       CarbonCore/TextEncodingConverter.h
 
     Contains:   Text Encoding Conversion Interfaces.
 
     Version:    CarbonCore-317~6
 
     Copyright:  © 1994-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __TEXTENCODINGCONVERTER__
#define __TEXTENCODINGCONVERTER__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __TEXTCOMMON__
#include <CarbonCore/TextCommon.h>
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

typedef OSType                          TECPluginSignature;
typedef UInt32                          TECPluginVersion;
/* plugin signatures */
enum {
  kTECSignature                 = 'encv',
  kTECUnicodePluginSignature    = 'puni',
  kTECJapanesePluginSignature   = 'pjpn',
  kTECChinesePluginSignature    = 'pzho',
  kTECKoreanPluginSignature     = 'pkor'
};


/* converter object reference */
typedef struct OpaqueTECObjectRef*      TECObjectRef;
typedef struct OpaqueTECSnifferObjectRef*  TECSnifferObjectRef;
typedef OSType                          TECPluginSig;
struct TECConversionInfo {
  TextEncoding        sourceEncoding;
  TextEncoding        destinationEncoding;
  UInt16              reserved1;
  UInt16              reserved2;
};
typedef struct TECConversionInfo        TECConversionInfo;
/* return number of encodings types supported by user's configuraton of the encoding converter */
/*
 *  TECCountAvailableTextEncodings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.1 and later
 */
extern OSStatus 
TECCountAvailableTextEncodings(ItemCount * numberEncodings);


/* fill in an array of type TextEncoding passed in by the user with types of encodings the current configuration of the encoder can handle. */
/*
 *  TECGetAvailableTextEncodings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECGetAvailableTextEncodings(
  TextEncoding   availableEncodings[],
  ItemCount      maxAvailableEncodings,
  ItemCount *    actualAvailableEncodings);


/* return number of from-to encoding conversion pairs supported  */
/*
 *  TECCountDirectTextEncodingConversions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECCountDirectTextEncodingConversions(ItemCount * numberOfEncodings);


/* fill in an array of type TextEncodingPair passed in by the user with types of encoding pairs the current configuration of the encoder can handle. */
/*
 *  TECGetDirectTextEncodingConversions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECGetDirectTextEncodingConversions(
  TECConversionInfo   availableConversions[],
  ItemCount           maxAvailableConversions,
  ItemCount *         actualAvailableConversions);


/* return number of encodings a given encoding can be converter into */
/*
 *  TECCountDestinationTextEncodings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECCountDestinationTextEncodings(
  TextEncoding   inputEncoding,
  ItemCount *    numberOfEncodings);


/* fill in an array of type TextEncodingPair passed in by the user with types of encodings pairs the current configuration of the encoder can handle. */
/*
 *  TECGetDestinationTextEncodings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECGetDestinationTextEncodings(
  TextEncoding   inputEncoding,
  TextEncoding   destinationEncodings[],
  ItemCount      maxDestinationEncodings,
  ItemCount *    actualDestinationEncodings);


/* get info about a text encoding */
/*
 *  TECGetTextEncodingInternetName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.1 and later
 */
extern OSStatus 
TECGetTextEncodingInternetName(
  TextEncoding   textEncoding,
  Str255         encodingName);


/*
 *  TECGetTextEncodingFromInternetName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.1 and later
 */
extern OSStatus 
TECGetTextEncodingFromInternetName(
  TextEncoding *     textEncoding,
  ConstStr255Param   encodingName);


/* create/dispose converters */
/*
 *  TECCreateConverter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.1 and later
 */
extern OSStatus 
TECCreateConverter(
  TECObjectRef *  newEncodingConverter,
  TextEncoding    inputEncoding,
  TextEncoding    outputEncoding);


/*
 *  TECCreateConverterFromPath()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECCreateConverterFromPath(
  TECObjectRef *       newEncodingConverter,
  const TextEncoding   inPath[],
  ItemCount            inEncodings);


/*
 *  TECDisposeConverter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.1 and later
 */
extern OSStatus 
TECDisposeConverter(TECObjectRef newEncodingConverter);


/* convert text encodings */
/*
 *  TECClearConverterContextInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECClearConverterContextInfo(TECObjectRef encodingConverter);


/*
 *  TECConvertText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECConvertText(
  TECObjectRef   encodingConverter,
  ConstTextPtr   inputBuffer,
  ByteCount      inputBufferLength,
  ByteCount *    actualInputLength,
  TextPtr        outputBuffer,
  ByteCount      outputBufferLength,
  ByteCount *    actualOutputLength);


/*
 *  TECFlushText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECFlushText(
  TECObjectRef   encodingConverter,
  TextPtr        outputBuffer,
  ByteCount      outputBufferLength,
  ByteCount *    actualOutputLength);


/* one-to-many routines */
/*
 *  TECCountSubTextEncodings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECCountSubTextEncodings(
  TextEncoding   inputEncoding,
  ItemCount *    numberOfEncodings);


/*
 *  TECGetSubTextEncodings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECGetSubTextEncodings(
  TextEncoding   inputEncoding,
  TextEncoding   subEncodings[],
  ItemCount      maxSubEncodings,
  ItemCount *    actualSubEncodings);


/*
 *  TECGetEncodingList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.1 and later
 */
extern OSStatus 
TECGetEncodingList(
  TECObjectRef   encodingConverter,
  ItemCount *    numEncodings,
  Handle *       encodingList);


/*
 *  TECCreateOneToManyConverter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECCreateOneToManyConverter(
  TECObjectRef *       newEncodingConverter,
  TextEncoding         inputEncoding,
  ItemCount            numOutputEncodings,
  const TextEncoding   outputEncodings[]);


/*
 *  TECConvertTextToMultipleEncodings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECConvertTextToMultipleEncodings(
  TECObjectRef      encodingConverter,
  ConstTextPtr      inputBuffer,
  ByteCount         inputBufferLength,
  ByteCount *       actualInputLength,
  TextPtr           outputBuffer,
  ByteCount         outputBufferLength,
  ByteCount *       actualOutputLength,
  TextEncodingRun   outEncodingsBuffer[],
  ItemCount         maxOutEncodingRuns,
  ItemCount *       actualOutEncodingRuns);


/*
 *  TECFlushMultipleEncodings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECFlushMultipleEncodings(
  TECObjectRef      encodingConverter,
  TextPtr           outputBuffer,
  ByteCount         outputBufferLength,
  ByteCount *       actualOutputLength,
  TextEncodingRun   outEncodingsBuffer[],
  ItemCount         maxOutEncodingRuns,
  ItemCount *       actualOutEncodingRuns);


/* international internet info */
/*
 *  TECCountWebTextEncodings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECCountWebTextEncodings(
  RegionCode   locale,
  ItemCount *  numberEncodings);


/*
 *  TECGetWebTextEncodings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECGetWebTextEncodings(
  RegionCode     locale,
  TextEncoding   availableEncodings[],
  ItemCount      maxAvailableEncodings,
  ItemCount *    actualAvailableEncodings);


/*
 *  TECCountMailTextEncodings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECCountMailTextEncodings(
  RegionCode   locale,
  ItemCount *  numberEncodings);


/*
 *  TECGetMailTextEncodings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECGetMailTextEncodings(
  RegionCode     locale,
  TextEncoding   availableEncodings[],
  ItemCount      maxAvailableEncodings,
  ItemCount *    actualAvailableEncodings);


/* examine text encodings */
/*
 *  TECCountAvailableSniffers()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECCountAvailableSniffers(ItemCount * numberOfEncodings);


/*
 *  TECGetAvailableSniffers()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECGetAvailableSniffers(
  TextEncoding   availableSniffers[],
  ItemCount      maxAvailableSniffers,
  ItemCount *    actualAvailableSniffers);


/*
 *  TECCreateSniffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECCreateSniffer(
  TECSnifferObjectRef *  encodingSniffer,
  TextEncoding           testEncodings[],
  ItemCount              numTextEncodings);


/*
 *  TECSniffTextEncoding()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECSniffTextEncoding(
  TECSnifferObjectRef   encodingSniffer,
  TextPtr               inputBuffer,
  ByteCount             inputBufferLength,
  TextEncoding          testEncodings[],
  ItemCount             numTextEncodings,
  ItemCount             numErrsArray[],
  ItemCount             maxErrs,
  ItemCount             numFeaturesArray[],
  ItemCount             maxFeatures);


/*
 *  TECDisposeSniffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECDisposeSniffer(TECSnifferObjectRef encodingSniffer);


/*
 *  TECClearSnifferContextInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECClearSnifferContextInfo(TECSnifferObjectRef encodingSniffer);


/*
 *  TECSetBasicOptions()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in TextEncodingConverter 1.5 and later
 */




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

#endif /* __TEXTENCODINGCONVERTER__ */

