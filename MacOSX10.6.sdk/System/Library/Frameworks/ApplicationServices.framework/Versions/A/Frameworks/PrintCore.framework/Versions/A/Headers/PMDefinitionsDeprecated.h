#if !__LP64__

/*
     File:       PrintCore/PMDefinitionsDeprecated.h
 
     Contains:   Deprecated Carbon Printing Manager Interfaces.
 
     Copyright (c) 1998-2006,2008 Apple Inc. All Rights Reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PMDEFINITIONS_DEPRECATED__
#define __PMDEFINITIONS_DEPRECATED__

#if PRAGMA_ONCE
#pragma once
#endif

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

/* Printing objects */
typedef struct OpaquePMPrintContext*    PMPrintContext;
typedef struct OpaquePMDialog*          PMDialog;
enum {
  kSizeOfTPrint                 = 120   /* size of old TPrint record */
};

// Ticket items cannot be locked in 10.5 and later.
enum {
  kPMLocked                     = true
};

typedef UInt16 PMColorMode;
enum {
  kPMBlackAndWhite              = 1,
  kPMGray                       = 2,
  kPMColor                      = 3,
  kPMColorModeDuotone           = 4,    /* 2 channels */
  kPMColorModeSpecialColor      = 5     /* to allow for special colors such as metalic, light cyan, etc. */
};

/* Constants to define the ColorSync Intents. These intents may be used */
/* to set an intent part way through a page or for an entire document. */
typedef UInt32 PMColorSyncIntent;
enum {
  kPMColorIntentUndefined       = 0x0000, /* User or application have not declared an intent, use the printer's default. */
  kPMColorIntentAutomatic       = 0x0001, /* Automatically match for photos and graphics anywhere on the page. */
  kPMColorIntentPhoto           = 0x0002, /* Use Photographic (cmPerceptual) intent for all contents. */
  kPMColorIntentBusiness        = 0x0004, /* Use Business Graphics (cmSaturation) intent for all contents. */
  kPMColorIntentRelColor        = 0x0008, /* Use Relative Colormetrics (Logo Colors) for the page. */
  kPMColorIntentAbsColor        = 0x0010, /* Use absolute colormetric for the page. */
  kPMColorIntentUnused          = 0xFFE0 /* Remaining bits unused at this time. */
};

/* Unused duplex binding directions: */
typedef UInt16 PMDuplexBinding;
enum {
  kPMDuplexBindingLeftRight     = 1,
  kPMDuplexBindingTopDown       = 2
};


typedef UInt32 PMTag;
enum {
                                        /* common tags */
  kPMCurrentValue               = 'curr', /* current setting or value */
  kPMDefaultValue               = 'dflt', /* default setting or value */
  kPMMinimumValue               = 'minv', /* the minimum setting or value */
  kPMMaximumValue               = 'maxv', /* the maximum setting or value */
                                        /* profile tags */
  kPMSourceProfile              = 'srcp', /* source profile */
                                        /* resolution tags */
  kPMMinRange                   = 'mnrg', /* Min range supported by a printer */
  kPMMaxRange                   = 'mxrg', /* Max range supported by a printer */
  kPMMinSquareResolution        = 'mins', /* Min with X and Y resolution equal */
  kPMMaxSquareResolution        = 'maxs', /* Max with X and Y resolution equal */
  kPMDefaultResolution          = 'dftr' /* printer default resolution */
};

/* Useful Constants for PostScript Injection */
enum {
  kPSPageInjectAllPages         = -1,   /* specifies to inject on all pages */
  kPSInjectionMaxDictSize       = 5     /* maximum size of a dictionary used for PSInjection */
};

/* PostScript Injection values for kPSInjectionPlacementKey */
typedef UInt16 PSInjectionPlacement;
enum {
  kPSInjectionBeforeSubsection  = 1,
  kPSInjectionAfterSubsection   = 2,
  kPSInjectionReplaceSubsection = 3
};

/* PostScript Injection values for kPSInjectionSectionKey */
typedef SInt32 PSInjectionSection;
enum {
                                        /* Job */
  kInjectionSectJob             = 1,    /* CoverPage */
  kInjectionSectCoverPage       = 2
};

/* PostScript Injection values for kPSInjectionSubSectionKey */
typedef SInt32 PSInjectionSubsection;
enum {
  kInjectionSubPSAdobe          = 1,    /* %!PS-Adobe           */
  kInjectionSubPSAdobeEPS       = 2,    /* %!PS-Adobe-3.0 EPSF-3.0    */
  kInjectionSubBoundingBox      = 3,    /* BoundingBox          */
  kInjectionSubEndComments      = 4,    /* EndComments          */
  kInjectionSubOrientation      = 5,    /* Orientation          */
  kInjectionSubPages            = 6,    /* Pages            */
  kInjectionSubPageOrder        = 7,    /* PageOrder          */
  kInjectionSubBeginProlog      = 8,    /* BeginProlog          */
  kInjectionSubEndProlog        = 9,    /* EndProlog          */
  kInjectionSubBeginSetup       = 10,   /* BeginSetup          */
  kInjectionSubEndSetup         = 11,   /* EndSetup             */
  kInjectionSubBeginDefaults    = 12,   /* BeginDefaults       */
  kInjectionSubEndDefaults      = 13,   /* EndDefaults          */
  kInjectionSubDocFonts         = 14,   /* DocumentFonts       */
  kInjectionSubDocNeededFonts   = 15,   /* DocumentNeededFonts       */
  kInjectionSubDocSuppliedFonts = 16,   /* DocumentSuppliedFonts  */
  kInjectionSubDocNeededRes     = 17,   /* DocumentNeededResources    */
  kInjectionSubDocSuppliedRes   = 18,   /* DocumentSuppliedResources*/
  kInjectionSubDocCustomColors  = 19,   /* DocumentCustomColors     */
  kInjectionSubDocProcessColors = 20,   /* DocumentProcessColors  */
  kInjectionSubPlateColor       = 21,   /* PlateColor          */
  kInjectionSubPageTrailer      = 22,   /* PageTrailer           */
  kInjectionSubTrailer          = 23,   /* Trailer              */
  kInjectionSubEOF              = 24,   /* EOF                 */
  kInjectionSubBeginFont        = 25,   /* BeginFont          */
  kInjectionSubEndFont          = 26,   /* EndFont              */
  kInjectionSubBeginResource    = 27,   /* BeginResource       */
  kInjectionSubEndResource      = 28,   /* EndResource          */
  kInjectionSubPage             = 29,   /* Page               */
  kInjectionSubBeginPageSetup   = 30,   /* BeginPageSetup        */
  kInjectionSubEndPageSetup     = 31    /* EndPageSetup          */
};

/* Document format strings */
#define kPMDocumentFormatPICT           CFSTR("application/vnd.apple.printing-pict")
#define kPMDocumentFormatPICTPS         CFSTR("application/vnd.apple.printing-pict-ps")
#define kPMDocumentFormatPICTPSwPSNormalizer  CFSTR("application/vnd.apple.printing-pict-ps-viapsnormalizer")
/* Data format strings */
#define kPMDataFormatPDF                kPMDocumentFormatPDF
#define kPMDataFormatPS                 kPMDocumentFormatPostScript
#define kPMDataFormatPICT               kPMDocumentFormatPICT
#define kPMDataFormatPICTwPS            kPMDocumentFormatPICTPS

/* Graphic context strings */
#define kPMGraphicsContextQuickdraw     CFSTR("com.apple.graphicscontext.quickdraw")

/* PostScript Injection Dictionary Keys */
#define kPSInjectionSectionKey          CFSTR("section")
#define kPSInjectionSubSectionKey       CFSTR("subsection")
#define kPSInjectionPageKey             CFSTR("page")
#define kPSInjectionPlacementKey        CFSTR("place")
#define kPSInjectionPostScriptKey       CFSTR("psdata")
/* PDF Workflow Keys */
#define kPDFWorkflowForlderURLKey       CFSTR("folderURL")

#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif	/* __PMDEFINITIONS_DEPRECATED__ */

#endif /* !__LP64__ */
