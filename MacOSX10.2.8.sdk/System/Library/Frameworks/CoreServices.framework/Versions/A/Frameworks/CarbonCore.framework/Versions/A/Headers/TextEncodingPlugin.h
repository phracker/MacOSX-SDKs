/*
     File:       CarbonCore/TextEncodingPlugin.h
 
     Contains:   Required interface for Text Encoding Converter-Plugins
 
     Version:    CarbonCore-472~1
 
     Copyright:  © 1996-2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __TEXTENCODINGPLUGIN__
#define __TEXTENCODINGPLUGIN__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __TEXTCOMMON__
#include <CarbonCore/TextCommon.h>
#endif

#ifndef __TEXTENCODINGCONVERTER__
#include <CarbonCore/TextEncodingConverter.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#pragma options align=mac68k

/*
  ####################################################################################
        Constants
  ####################################################################################
*/
/*
   This constant is needed for MacOS X development only. It is the name in which the
   function to grab the plugin's dispatch table must go by. 
*/
#define kTECMacOSXDispatchTableNameString   "ConverterPluginGetPluginDispatchTable"
/*
  ####################################################################################
        Structs
  ####################################################################################
*/
struct TECBufferContextRec {
  TextPtr             textInputBuffer;
  TextPtr             textInputBufferEnd;
  TextPtr             textOutputBuffer;
  TextPtr             textOutputBufferEnd;

  TextEncodingRunPtr  encodingInputBuffer;
  TextEncodingRunPtr  encodingInputBufferEnd;
  TextEncodingRunPtr  encodingOutputBuffer;
  TextEncodingRunPtr  encodingOutputBufferEnd;
};
typedef struct TECBufferContextRec      TECBufferContextRec;
struct TECPluginStateRec {

  UInt8               state1;
  UInt8               state2;
  UInt8               state3;
  UInt8               state4;

  UInt32              longState1;
  UInt32              longState2;
  UInt32              longState3;
  UInt32              longState4;
};
typedef struct TECPluginStateRec        TECPluginStateRec;
struct TECConverterContextRec {

                                              /* public - manipulated externally and by plugin*/
  Ptr                 pluginRec;
  TextEncoding        sourceEncoding;
  TextEncoding        destEncoding;
  UInt32              reserved1;
  UInt32              reserved2;
  TECBufferContextRec  bufferContext;
                                              /* private - manipulated only within Plugin*/
  UInt32              contextRefCon;
  ProcPtr             conversionProc;
  ProcPtr             flushProc;
  ProcPtr             clearContextInfoProc;
  UInt32              options1;
  UInt32              options2;
  TECPluginStateRec   pluginState;
};
typedef struct TECConverterContextRec   TECConverterContextRec;
struct TECSnifferContextRec {
                                              /* public - manipulated externally*/
  Ptr                 pluginRec;
  TextEncoding        encoding;
  ItemCount           maxErrors;
  ItemCount           maxFeatures;
  TextPtr             textInputBuffer;
  TextPtr             textInputBufferEnd;
  ItemCount           numFeatures;
  ItemCount           numErrors;
                                              /* private - manipulated only within Plugin*/
  UInt32              contextRefCon;
  ProcPtr             sniffProc;
  ProcPtr             clearContextInfoProc;
  TECPluginStateRec   pluginState;
};
typedef struct TECSnifferContextRec     TECSnifferContextRec;
/*
  ####################################################################################
        Functional Messages
  ####################################################################################
*/

typedef CALLBACK_API_C( OSStatus , TECPluginNewEncodingConverterPtr )(TECObjectRef *newEncodingConverter, TECConverterContextRec *plugContext, TextEncoding inputEncoding, TextEncoding outputEncoding);
typedef CALLBACK_API_C( OSStatus , TECPluginClearContextInfoPtr )(TECObjectRef encodingConverter, TECConverterContextRec *plugContext);
typedef CALLBACK_API_C( OSStatus , TECPluginConvertTextEncodingPtr )(TECObjectRef encodingConverter, TECConverterContextRec *plugContext);
typedef CALLBACK_API_C( OSStatus , TECPluginFlushConversionPtr )(TECObjectRef encodingConverter, TECConverterContextRec *plugContext);
typedef CALLBACK_API_C( OSStatus , TECPluginDisposeEncodingConverterPtr )(TECObjectRef newEncodingConverter, TECConverterContextRec *plugContext);
typedef CALLBACK_API_C( OSStatus , TECPluginNewEncodingSnifferPtr )(TECSnifferObjectRef *encodingSniffer, TECSnifferContextRec *snifContext, TextEncoding inputEncoding);
typedef CALLBACK_API_C( OSStatus , TECPluginClearSnifferContextInfoPtr )(TECSnifferObjectRef encodingSniffer, TECSnifferContextRec *snifContext);
typedef CALLBACK_API_C( OSStatus , TECPluginSniffTextEncodingPtr )(TECSnifferObjectRef encodingSniffer, TECSnifferContextRec *snifContext);
typedef CALLBACK_API_C( OSStatus , TECPluginDisposeEncodingSnifferPtr )(TECSnifferObjectRef encodingSniffer, TECSnifferContextRec *snifContext);
typedef CALLBACK_API_C( OSStatus , TECPluginGetCountAvailableTextEncodingsPtr )(TextEncoding *availableEncodings, ItemCount maxAvailableEncodings, ItemCount *actualAvailableEncodings);
typedef CALLBACK_API_C( OSStatus , TECPluginGetCountAvailableTextEncodingPairsPtr )(TECConversionInfo *availableEncodings, ItemCount maxAvailableEncodings, ItemCount *actualAvailableEncodings);
typedef CALLBACK_API_C( OSStatus , TECPluginGetCountDestinationTextEncodingsPtr )(TextEncoding inputEncoding, TextEncoding *destinationEncodings, ItemCount maxDestinationEncodings, ItemCount *actualDestinationEncodings);
typedef CALLBACK_API_C( OSStatus , TECPluginGetCountSubTextEncodingsPtr )(TextEncoding inputEncoding, TextEncoding subEncodings[], ItemCount maxSubEncodings, ItemCount *actualSubEncodings);
typedef CALLBACK_API_C( OSStatus , TECPluginGetCountAvailableSniffersPtr )(TextEncoding *availableEncodings, ItemCount maxAvailableEncodings, ItemCount *actualAvailableEncodings);
typedef CALLBACK_API_C( OSStatus , TECPluginGetTextEncodingInternetNamePtr )(TextEncoding textEncoding, Str255 encodingName);
typedef CALLBACK_API_C( OSStatus , TECPluginGetTextEncodingFromInternetNamePtr )(TextEncoding *textEncoding, ConstStr255Param encodingName);
typedef CALLBACK_API_C( OSStatus , TECPluginGetCountWebEncodingsPtr )(TextEncoding *availableEncodings, ItemCount maxAvailableEncodings, ItemCount *actualAvailableEncodings);
typedef CALLBACK_API_C( OSStatus , TECPluginGetCountMailEncodingsPtr )(TextEncoding *availableEncodings, ItemCount maxAvailableEncodings, ItemCount *actualAvailableEncodings);
/*
  ####################################################################################
        Dispatch Table Definition
  ####################################################################################
*/

enum {
  kTECPluginDispatchTableVersion1 = 0x00010000, /* 1.0 through 1.0.3 releases*/
  kTECPluginDispatchTableVersion1_1 = 0x00010001, /* 1.1 releases*/
  kTECPluginDispatchTableVersion1_2 = 0x00010002, /* 1.2 releases*/
  kTECPluginDispatchTableCurrentVersion = kTECPluginDispatchTableVersion1_2
};

struct TECPluginDispatchTable {

  TECPluginVersion    version;
  TECPluginVersion    compatibleVersion;
  TECPluginSignature  PluginID;

  TECPluginNewEncodingConverterPtr  PluginNewEncodingConverter;
  TECPluginClearContextInfoPtr  PluginClearContextInfo;
  TECPluginConvertTextEncodingPtr  PluginConvertTextEncoding;
  TECPluginFlushConversionPtr  PluginFlushConversion;
  TECPluginDisposeEncodingConverterPtr  PluginDisposeEncodingConverter;

  TECPluginNewEncodingSnifferPtr  PluginNewEncodingSniffer;
  TECPluginClearSnifferContextInfoPtr  PluginClearSnifferContextInfo;
  TECPluginSniffTextEncodingPtr  PluginSniffTextEncoding;
  TECPluginDisposeEncodingSnifferPtr  PluginDisposeEncodingSniffer;

  TECPluginGetCountAvailableTextEncodingsPtr  PluginGetCountAvailableTextEncodings;
  TECPluginGetCountAvailableTextEncodingPairsPtr  PluginGetCountAvailableTextEncodingPairs;
  TECPluginGetCountDestinationTextEncodingsPtr  PluginGetCountDestinationTextEncodings;
  TECPluginGetCountSubTextEncodingsPtr  PluginGetCountSubTextEncodings;
  TECPluginGetCountAvailableSniffersPtr  PluginGetCountAvailableSniffers;
  TECPluginGetCountWebEncodingsPtr  PluginGetCountWebTextEncodings;
  TECPluginGetCountMailEncodingsPtr  PluginGetCountMailTextEncodings;

  TECPluginGetTextEncodingInternetNamePtr  PluginGetTextEncodingInternetName;
  TECPluginGetTextEncodingFromInternetNamePtr  PluginGetTextEncodingFromInternetName;

};
typedef struct TECPluginDispatchTable   TECPluginDispatchTable;
/*
   The last prototype here is for MacOS X plugins only. TEC Plugins in MacOS X need to export a
   a function called ConverterPluginGetPluginDispatchTable with the following prototype:
   extern TECPluginDispatchTable *ConverterPluginGetPluginDispatchTable( void )
   This function will need to return a pointer to the plugin's function dispatch table 
   when called. It is important that the function be called exactly 
   "ConverterPluginGetPluginDispatchTable". TECPluginGetPluginDispatchTablePtr is a 
   function pointer to this function.
*/
typedef CALLBACK_API_C( TECPluginDispatchTable *, TECPluginGetPluginDispatchTablePtr )(void);






#pragma options align=reset


#endif /* __TEXTENCODINGPLUGIN__ */

