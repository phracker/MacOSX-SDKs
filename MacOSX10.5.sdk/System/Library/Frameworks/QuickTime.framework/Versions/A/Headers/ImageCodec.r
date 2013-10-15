/*
     File:       ImageCodec.r
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1990-2006 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __IMAGECODEC_R__
#define __IMAGECODEC_R__

#ifndef __CORESERVICES_R__
#include <CoreServices/CoreServices.r>
#endif

#include <CoreServices/CoreServices.r>
#include <QuickTime/ImageCompression.r>
#define codecSuggestedBufferSentinel 	'sent'				/*  codec public resource containing suggested data pattern to put past end of data buffer  */
#define kParameterTitleName 			'name'
#define kParameterTitleID 				1

#define kParameterWhatName 				'what'
#define kParameterWhatID 				1

#define kParameterVersionName 			'vers'
#define kParameterVersionID 			1

#define kParameterRepeatableName 		'pete'
#define kParameterRepeatableID 			1


   #define kParameterRepeatableTrue    long { "1" }
   #define kParameterRepeatableFalse   long { "0" }

#define kParameterAlternateCodecName 	'subs'
#define kParameterAlternateCodecID 		1

#define kParameterSourceCountName 		'srcs'
#define kParameterSourceCountID 		1

#define kEffectMajorClassType 			'clsa'
#define kEffectMajorClassID 			1


    #define kGeneratorMajorClass        OSType { "genr" }
    #define kFilterMajorClass           OSType { "filt" }
    #define kTransitionMajorClass       OSType { "tran" }
    #define kCompositorMajorClass       OSType { "comp" }
    #define kMiscMajorClass             OSType { "misc" }

#define kEffectMinorClassType 			'clsi'
#define kEffectMinorClassID 			1
#define kEffectMinorClassNameType 		'clsn'
#define kEffectMinorClassNameID 		1


    #define kGeneratorMinorClass        OSType { "genr" }
    #define kRenderMinorClass            OSType { "rend" }
    #define kFilterMinorClass           OSType { "filt" }
    #define kArtisticMinorClass         OSType { "arts" }
    #define kBlurMinorClass               OSType { "blur" }
    #define kSharpenMinorClass            OSType { "shrp" }
    #define kDistortMinorClass            OSType { "dist" }
    #define kNoiseMinorClass          OSType { "nois" }
    #define kAdjustmentMinorClass     OSType { "adst" }
    #define kTransitionMinorClass       OSType { "tran" }
    #define kWipeMinorClass             OSType { "wipe" }
    #define k3DMinorClass               OSType { "pzre" }
    #define kCompositorMinorClass       OSType { "comp" }
    #define kEffectsMinorClass          OSType { "fxfx" }
    #define kMiscMinorClass             OSType { "misc" }

#define kEffectPresetType 				'peff'
#define kPresetNameType 				'pnam'
#define kPresetNameID 					1
#define kPresetPreviewPictureType 		'ppct'
#define kPresetPreviewPictureID 		1
#define kPresetSettingsType 			'psst'
#define kPresetSettingsID 				1

#define kParameterDependencyName 		'deep'
#define kParameterDependencyID 			1


   #define kParameterListDependsUponColorProfiles  OSType { "prof" }
  #define kParameterListDependsUponFonts          OSType { "font" }

#define kParameterEnumList 				'enum'
#define kParameterAtomTypeAndID 		'type'

       #define kNoAtom                         OSType { "none" }
      #define kAtomNoFlags                    long { "0" }
       #define kAtomNotInterpolated            long { "1" }
       #define kAtomInterpolateIsOptional      long { "2" }
       #define kAtomMayBeIndexed               long { "4" }
       #define kAtomNotInterpMayBeIndexed      long { "5" }
       #define kAtomOptionalInterpMayBeIndexed long { "6" }

#define kParameterProperty 				'prop'
#define kParameterDataType 				'data'

       #define kParameterTypeDataLong      long { "2" }
       #define kParameterTypeDataFixed     long { "3" }
       #define kParameterTypeDataRGBValue  long { "8" }
       #define kParameterTypeDataDouble    long { "11" }
      #define kParameterTypeDataText      OSType { "text" }
      #define kParameterTypeDataEnum      OSType { "enum" }
      #define kParameterTypeDataBitField  OSType { "bool" }
      #define kParameterTypeDataImage     OSType { "imag" }

#define kParameterDataRange 			'rang'

       #define kParameterImageNoFlags      long { "0" }
       #define kParameterImageIsPreset     long { "1" }


       #define kStandardPresetGroup        OSType { "pset" }

#define kParameterDataBehavior 			'ditl'

   // items edited via typing
     #define kParameterItemEditText      OSType { "edit" }
      #define kParameterItemEditLong      OSType { "long" }
      #define kParameterItemEditFixed     OSType { "fixd" }
      #define kParameterItemEditDouble    OSType { "doub" }

 // items edited via control(s)
     #define kParameterItemPopUp         OSType { "popu" }
      #define kParameterItemRadioCluster  OSType { "radi" }
      #define kParameterItemCheckBox      OSType { "chex" }
      #define kParameterItemControl       OSType { "cntl" }
      
   // special user items
      #define kParameterItemLine          OSType { "line" }
      #define kParameterItemColorPicker   OSType { "pick" }
      #define kParameterItemGroupDivider  OSType { "divi" }
      #define kParameterItemStaticText    OSType { "stat" }
      #define kParameterItemDragImage     OSType { "imag" }



       // flags valid for lines and groups
        #define kGraphicsNoFlags            long { "0" }
       #define kGraphicsFlagsGray          long { "1" }

      // flags valid for groups
      #define kGroupNoFlags                       long { "0" }
       #define kGroupAlignText                     long { "65536" }
       #define kGroupSurroundBox                   long { "131072" }
      #define kGroupMatrix                        long { "262144" }
      #define kGroupNoName                        long { "524288" }
      #define kGroupSurroundWithGray              long { "131073" }
      #define kGroupSurroundWithGrayAlign         long { "196609" }
      #define kGroupSurroundWithGrayNoName        long { "655361" }
      #define kGroupSurroundWithGrayAlignNoName   long { "720897" }
      #define kGroupAlignTextNoName               long { "589824" }
      
       // flags valid for popup/radiocluster/checkbox/control
     #define kDisableControl         long { "1" }
       #define kDisableWhenNotEqual    long { "1" }
       #define kDisableWhenEqual       long { "17" }
      #define kDisableWhenLessThan    long { "33" }
      #define kDisableWhenGreaterThan long { "49" }

     // flags valid for popups
      #define kPopupStoreAsString     long { "65536" }

#define kParameterDataUsage 			'use '

       #define kParameterUsagePixels           OSType { "pixl" }
      #define kParameterUsageRectangle        OSType { "rect" }
      #define kParameterUsagePoint            OSType { "xy  " }
      #define kParameterUsage3DPoint          OSType { "xyz " }
      #define kParameterUsageDegrees          OSType { "degr" }
      #define kParameterUsageRadians          OSType { "rads" }
      #define kParameterUsagePercent          OSType { "pcnt" }
      #define kParameterUsageSeconds          OSType { "secs" }
      #define kParameterUsageMilliseconds     OSType { "msec" }
      #define kParameterUsageMicroseconds     OSType { "µsec" }
      #define kParameterUsage3by3Matrix       OSType { "3by3" }
      #define kParameterUsageCircularDegrees  OSType { "degc" }
      #define kParameterUsageCircularRadians  OSType { "radc" }

#define kParameterDataDefaultItem 		'dflt'
#define kParameterInfoLongName 			'©nam'
#define kParameterInfoCopyright 		'©cpy'
#define kParameterInfoDescription 		'©inf'
#define kParameterInfoWindowTitle 		'©wnt'
#define kParameterInfoPicture 			'©pix'
#define kParameterInfoManufacturer 		'©man'
#define kParameterInfoIDs 				1


type 'cdec' {
 hex string;
};


type 'cdci' {
 pstring[31];
   hex integer version;
   hex integer revlevel;
  hex longint vendor;
    hex longint decompressFlags;
   hex longint compressFlags;
 hex longint formatFlags;
   byte        compressionAccuracy;
   byte        decompressionAccuracy;
 integer     compressionSpeed;
  integer     decompressionSpeed;
    byte        compressionLevel;
  byte        resvd;
 integer     minimumHeight;
 integer     minimumWidth;
  integer     decompressPipelineLatency;
 integer     compressPipelineLatency;
   longint     privateData;
};


#define    compressorComponentType         'imco'
#define  decompressorComponentType       'imdc'


/* Resource type used for the creation of parameter description atoms */
type 'atms' {
    longint;    // root atom count
 
   array AtomArray {
      literal longint;        // atomType
        longint;                // atomID
      longint noChildren = 0; // children
        longint =  $$CountOf(AtomData);
        array AtomData {
           switch {
           case long:
             key literal longint = 'long';
              pstring;            // data
            case short:
                key literal longint = 'shrt';
              pstring;            // data
            case noMininumFixed:
               key literal longint = 'nmiF';
              pstring = "";       // data
            case noMaximumFixed:
               key literal longint = 'nmaF';
              pstring = "";       // data
            case noMininumDouble:
              key literal longint = 'nmiD';
              pstring = "";       // data
            case noMaximumDouble:
              key literal longint = 'nmaD';
              pstring = "";       // data
            case fixed:
                key literal longint = 'fixd';
              pstring;            // data
            case double:
               key literal longint = 'doub';
              pstring;            // data
            case string:
               key literal longint = 'str ';
              pstring;            // data
            case lstring:
              key literal longint = 'lstr';
  LongStringStart:    longint = ((LongStringEnd[$$ArrayIndex(AtomArray),$$ArrayIndex(AtomData)] - LongStringStart[$$ArrayIndex(AtomArray),$$ArrayIndex(AtomData)]) >> 3) - 4;
                hex string [$$Word(LongStringStart[$$ArrayIndex(AtomArray),$$ArrayIndex(AtomData)]) - 4];
  LongStringEnd:
         case OSType:
               key literal longint = 'osty';
              pstring;            // data
            };
         
       };
 };
};

/* used by decompressors to list their AVI file four cc's */
type 'avvd' {
  array {
        literal longint;                    /* avi four cc type */
 };
};

/* used by compressors to list their AVI file four cc's */
type 'avvc' {
    array {
        literal longint;                    /* avi four cc type */
 };
};

/* used by compressors to list their supported compress pixel format surfaces */
type 'cpix' {
  array {
        literal longint;
   };
};

/* Codec Compression Options - to limit UI in the standard compression dialog */
#define kCodecCompressionDefaultOptions        0x00000000
#define kCodecCompressionNoQuality           0x00000001

type 'ccop' {
  longint;
};


#endif /* __IMAGECODEC_R__ */

