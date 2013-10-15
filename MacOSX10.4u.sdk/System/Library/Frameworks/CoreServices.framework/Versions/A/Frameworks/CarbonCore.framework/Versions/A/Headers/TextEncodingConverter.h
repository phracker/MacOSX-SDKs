/*
     File:       CarbonCore/TextEncodingConverter.h
 
     Contains:   Text Encoding Conversion Interfaces.
 
     Version:    CarbonCore-682.26~1
 
     Copyright:  © 1994-2006 by Apple Computer, Inc., all rights reserved.
 
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

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

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

/*
 *  TECInternetNameUsageMask
 *  
 *  Discussion:
 *    Mask values that control the mapping between TextEncoding and
 *    IANA charset name or MIB enum.
 */
typedef UInt32 TECInternetNameUsageMask;
enum {
                                        /* Use one of the following*/

  /*
   * Use the default type of mapping given other usage information
   * (none currently defined).
   */
  kTECInternetNameDefaultUsageMask = 0,

  /*
   * Use the closest possible match between TextEncoding value and IANA
   * charset name or MIB enum
   */
  kTECInternetNameStrictUsageMask = 1,

  /*
   * When mapping from IANA charset name or MIB enum to TextEncoding,
   * map to the largest superset of the encoding specified by the
   * charset name or MIB enum (i.e. be tolerant). When mapping from
   * TextEncoding to IANA charset name or MIB enum, typically map to
   * the most generic or widely recognized charset name or MIB enum.
   */
  kTECInternetNameTolerantUsageMask = 2
};

/* Special values for MIB enums */
enum {
  kTEC_MIBEnumDontCare          = -1
};


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
TECCountAvailableTextEncodings(ItemCount * numberEncodings)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *    actualAvailableEncodings)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
TECCountDirectTextEncodingConversions(ItemCount * numberOfEncodings) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *         actualAvailableConversions)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *    numberOfEncodings)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *    actualDestinationEncodings)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  Str255         encodingName)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ConstStr255Param   encodingName)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  TextEncoding    outputEncoding)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount            inEncodings)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TECDisposeConverter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.1 and later
 */
extern OSStatus 
TECDisposeConverter(TECObjectRef newEncodingConverter)        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
TECClearConverterContextInfo(TECObjectRef encodingConverter)  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ByteCount *    actualOutputLength)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ByteCount *    actualOutputLength)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *    numberOfEncodings)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *    actualSubEncodings)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TECGetEncodingList()
 *  
 *  Parameters:
 *    
 *    encodingConverter:
 *      The encodingConverter to return the encoding list for
 *    
 *    numEncodings:
 *      On exit, the number of encodings in encodingList
 *    
 *    encodingList:
 *      On exit, a handle containing numEncodings values of type
 *      TextEncoding, for each known encoding.  Do not dispose of this
 *      handle.
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
  Handle *       encodingList)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  const TextEncoding   outputEncodings[])                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *       actualOutEncodingRuns)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *       actualOutEncodingRuns)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *  numberEncodings)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *    actualAvailableEncodings)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *  numberEncodings)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *    actualAvailableEncodings)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
TECCountAvailableSniffers(ItemCount * numberOfEncodings)      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *    actualAvailableSniffers)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount              numTextEncodings)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ConstTextPtr          inputBuffer,
  ByteCount             inputBufferLength,
  TextEncoding          testEncodings[],
  ItemCount             numTextEncodings,
  ItemCount             numErrsArray[],
  ItemCount             maxErrs,
  ItemCount             numFeaturesArray[],
  ItemCount             maxFeatures)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TECDisposeSniffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECDisposeSniffer(TECSnifferObjectRef encodingSniffer)        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TECClearSnifferContextInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.2 and later
 */
extern OSStatus 
TECClearSnifferContextInfo(TECSnifferObjectRef encodingSniffer) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TECSetBasicOptions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   in TextEncodingConverter 1.5 and later
 */
extern OSStatus 
TECSetBasicOptions(
  TECObjectRef   encodingConverter,
  OptionBits     controlFlags)                                AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/* Map TextEncoding values to/from IANA charset names and/or MIB enums, with usage control */
/*
 *  TECCopyTextEncodingInternetNameAndMIB()
 *  
 *  Summary:
 *    Converts a TextEncoding value to an IANA charset name and/or a
 *    MIB enum value
 *  
 *  Discussion:
 *    Given a TextEncoding value, this function maps it to an IANA
 *    charset name (if encodingNamePtr is non-NULL) and/or a MIB enum
 *    value (if mibEnumPtr is non-NULL), as specified by the usage
 *    parameter.
 *  
 *  Parameters:
 *    
 *    textEncoding:
 *      A TextEncoding value to map to a charset name and/or MIB enum.
 *    
 *    usage:
 *      Specifies the type of mapping desired (see
 *      TECInternetNameUsageMask above).
 *    
 *    encodingNamePtr:
 *      If non-NULL, is a pointer to a CStringRef for an immutable
 *      CFString created by this function; when the caller is finished
 *      with it, the caller must dispose of it by calling CFRelease.
 *    
 *    mibEnumPtr:
 *      If non-NULL, is a pointer to an SInt32 that will be set to the
 *      appropriate MIB enum value, or to 0 (or kTEC_MIBEnumDontCare)
 *      if there is no appropriate MIB enum value (valid MIB enums
 *      begin at 3).
 *  
 *  Result:
 *    The function returns paramErr if encodingNamePtr and mibEnumPtr
 *    are both NULL. It returns kTextUnsupportedEncodingErr if it has
 *    no data for the supplied textEncoding. It returns noErr if it
 *    found useful data.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TECCopyTextEncodingInternetNameAndMIB(
  TextEncoding               textEncoding,
  TECInternetNameUsageMask   usage,
  CFStringRef *              encodingNamePtr,       /* can be NULL */
  SInt32 *                   mibEnumPtr)            /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  TECGetTextEncodingFromInternetNameOrMIB()
 *  
 *  Summary:
 *    Converts an IANA charset name or a MIB enum value to a
 *    TextEncoding value
 *  
 *  Discussion:
 *    If encodingName is non-NULL, this function treats it as an IANA
 *    charset name and maps it to a TextEncoding value; in this case
 *    mibEnum is ignored, and may be set to kTEC_MIBEnumDontCare.
 *    Otherwise, this function maps the mibEnum to a TextEncoding
 *    value. In either case, the mapping is controlled by the usage
 *    parameter. The textEncodingPtr parameter must be non-NULL.
 *  
 *  Result:
 *    The function returns paramErr if textEncodingPtr is NULL. It
 *    returns kTextUnsupportedEncodingErr if it has no data for the
 *    supplied encodingName or mibEnum. It returns noErr if it found
 *    useful data.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TECGetTextEncodingFromInternetNameOrMIB(
  TextEncoding *             textEncodingPtr,
  TECInternetNameUsageMask   usage,
  CFStringRef                encodingName,
  SInt32                     mibEnum)                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;






#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __TEXTENCODINGCONVERTER__ */

