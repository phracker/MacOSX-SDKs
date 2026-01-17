/*
     File:       HIToolbox/MacTextEditor.h
 
     Contains:   Interfaces for Multilingual Text Engine (MLTE)
 
     Version:    HIToolbox-145.33~1
 
     Copyright:  © 1996-2003 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __MACTEXTEDITOR__
#define __MACTEXTEDITOR__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifndef __DRAG__
#include <HIToolbox/Drag.h>
#endif

#ifndef __MACWINDOWS__
#include <HIToolbox/MacWindows.h>
#endif

#ifndef __EVENTS__
#include <HIToolbox/Events.h>
#endif

#ifndef __CARBONEVENTS__
#include <HIToolbox/CarbonEvents.h>
#endif

#ifndef __HIVIEW__
#include <HIToolbox/HIView.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k


/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Various Defs                                                                                      */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
typedef struct OpaqueTXNObject*         TXNObject;
typedef struct OpaqueTXNFontMenuObject*  TXNFontMenuObject;
typedef UInt32                          TXNFrameID;
typedef UInt32                          TXNVersionValue;
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Error Status                                                                                      */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  MLTE status errors assigned is -22000 through -22039.  See MacError.h for -22000 to -22018.         */
enum {
  kTXNDisabledFunctionalityErr  = -22019 /*This routine's functionality is disabled.*/
};

/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Feature Bits                                                                                      */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  Useful for the TXNVersionInformation API.                                                           */
enum {
  kTXNWillDefaultToATSUIBit     = 0,
  kTXNWillDefaultToCarbonEventBit = 1
};


typedef OptionBits TXNFeatureBits;
enum {
  kTXNWillDefaultToATSUIMask    = 1L << kTXNWillDefaultToATSUIBit,
  kTXNWillDefaultToCarbonEventMask = 1L << kTXNWillDefaultToCarbonEventBit
};

/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Initialization Bits                                                                               */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  Useful for the TXNInitTextension API.                                                               */
enum {
  kTXNWantMoviesBit             = 0,
  kTXNWantSoundBit              = 1,
  kTXNWantGraphicsBit           = 2,
  kTXNAlwaysUseQuickDrawTextBit = 3,
  kTXNUseTemporaryMemoryBit     = 4
};


typedef OptionBits TXNInitOptions;
enum {
  kTXNWantMoviesMask            = 1L << kTXNWantMoviesBit,
  kTXNWantSoundMask             = 1L << kTXNWantSoundBit,
  kTXNWantGraphicsMask          = 1L << kTXNWantGraphicsBit,
  kTXNAlwaysUseQuickDrawTextMask = 1L << kTXNAlwaysUseQuickDrawTextBit,
  kTXNUseTemporaryMemoryMask    = 1L << kTXNUseTemporaryMemoryBit
};

/* Default constants  */
#define kTXNDefaultFontName             ((StringPtr)NULL)
enum {
  kTXNDefaultFontSize           = 0x000C0000
};

enum {
  kTXNDefaultFontStyle          = normal
};

/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • FrameOption Bits                                                                                  */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  Useful for the TXNNewObject and TXNCreateObject APIs.                                               */
enum {
  kTXNDrawGrowIconBit           = 0,
  kTXNShowWindowBit             = 1,
  kTXNWantHScrollBarBit         = 2,
  kTXNWantVScrollBarBit         = 3,
  kTXNNoTSMEverBit              = 4,
  kTXNReadOnlyBit               = 5,
  kTXNNoKeyboardSyncBit         = 6,
  kTXNNoSelectionBit            = 7,
  kTXNSaveStylesAsSTYLResourceBit = 8,
  kOutputTextInUnicodeEncodingBit = 9,
  kTXNDoNotInstallDragProcsBit  = 10,
  kTXNAlwaysWrapAtViewEdgeBit   = 11,
  kTXNDontDrawCaretWhenInactiveBit = 12,
  kTXNDontDrawSelectionWhenInactiveBit = 13,
  kTXNSingleLineOnlyBit         = 14,
  kTXNDisableDragAndDropBit     = 15,
  kTXNUseQDforImagingBit        = 16,
  kTXNMonostyledTextBit         = 17,
  kTXNDoFontSubstitutionBit     = 22
};



/*
 *  TXNFrameOptions
 *  
 *  Summary:
 *    Defines the initial behavior of an MLTE object created with
 *    TXNCreateObject/TXNNewObject.
 *  
 *  Discussion:
 *    These masks can be combined and passed to
 *    TXNCreateObject/TXNNewObject to define the initial behavior of a
 *    new object.
 */
typedef OptionBits TXNFrameOptions;
enum {

  /*
   * Indicates that the frame will have a size box.
   */
  kTXNDrawGrowIconMask          = 1L << kTXNDrawGrowIconBit,

  /*
   * Indicates that the window associated with the text object will be
   * displayed when the object is created.  The application no longer
   * needs to call the ShowWindow function from the Window Manager;
   * MLTE will do this for you.
   */
  kTXNShowWindowMask            = 1L << kTXNShowWindowBit,

  /*
   * Indicates that the frame will have a horizontal scrollbar. The
   * scrollbar will be enabled upon creation.  If there are multiple
   * MLTE objects in the same window, the client will need to
   * explicitly disable the scrollbars for those inactive MLTE objects.
   *  Use TXNSetScrollbarState to deactivate the scrollbar.
   */
  kTXNWantHScrollBarMask        = 1L << kTXNWantHScrollBarBit,

  /*
   * Indicates that the frame will have a vertical scrollbar. The
   * scrollbar will be enabled upon creation.  If there are multiple
   * MLTE objects in the same window, the client will need to
   * explicitly disable the scrollbars for those inactive MLTE objects.
   *  Use TXNSetScrollbarState to deactivate the scrollbar.
   */
  kTXNWantVScrollBarMask        = 1L << kTXNWantVScrollBarBit,

  /*
   * Deprecated.  Previously used to indicate that the Text Services
   * Manager would not be used.  Versions of MLTE newer than 1.4 rely
   * on the Text Services Manager to support Unicode.
   */
  kTXNNoTSMEverMask             = 1L << kTXNNoTSMEverBit,

  /*
   * Indicates that the text object will be read-only.  It is
   * equivalent to setting the object into NoUserIO mode, via the tag
   * kTXNNoUserIOTag in TXNSetTXNObjectControls. See description in
   * individual API to determine if the API will still work in NoUserIO
   * mode.
   */
  kTXNReadOnlyMask              = 1L << kTXNReadOnlyBit,

  /*
   * Indicates that keyboard synchronization will not occur.
   */
  kTXNNoKeyboardSyncMask        = 1L << kTXNNoKeyboardSyncBit,

  /*
   * Indicates that the user shouldn't be able to set the insertion
   * point or make a selection.
   */
  kTXNNoSelectionMask           = 1L << kTXNNoSelectionBit,

  /*
   * Indicates that the text style will be saved as a
   * kTXNMultipleStylesPerTextDocumentResType resource.  You can set
   * this to assure compatibility with SimpleText.  If you use
   * kTXNMultipleStylesPerTextDocumentResType resources to save style
   * info, your documents can have as many styles as you'd like. 
   * However tabs are not saved.  If you don't use this mask, plain
   * text files are saved as kTXNSingleStylePerTextDocumentResType
   * resources, and only the first style in the document is saved. 
   * (Your application is expected to apply all style changes to the
   * entire document.)  If you save files with a
   * kTXNSingleStylePerTextDocumentResType resource, their output is
   * similar to those output by CodeWarrior, BBEdit, and MPW.
   */
  kTXNSaveStylesAsSTYLResourceMask = 1L << kTXNSaveStylesAsSTYLResourceBit,

  /*
   * Indicates that plain text will be saved as Unicode.
   */
  kOutputTextInUnicodeEncodingMask = 1L << kOutputTextInUnicodeEncodingBit,

  /*
   * Indicates that MLTE will not install its own drag handler for the
   * text object.  This can be used if the client wants to install
   * their own handler.
   */
  kTXNDoNotInstallDragProcsMask = 1L << kTXNDoNotInstallDragProcsBit,

  /*
   * Indicates that lines will wrap at the edge of the view rectangle.
   */
  kTXNAlwaysWrapAtViewEdgeMask  = 1L << kTXNAlwaysWrapAtViewEdgeBit,

  /*
   * Indicates that the caret shouldn't be drawn when the text object
   * doesn't have focus.
   */
  kTXNDontDrawCaretWhenInactiveMask = 1L << kTXNDontDrawCaretWhenInactiveBit,

  /*
   * Indicates that the selection (if one) shouldn't be drawn when the
   * text object doesn't have focus.
   */
  kTXNDontDrawSelectionWhenInactiveMask = 1L << kTXNDontDrawSelectionWhenInactiveBit,

  /*
   * Indicates that the text object will not scroll vertically,
   * horizontal scrolling will stop when the end of the text is visible
   * (plus any right margin), and there will be no limit to the width
   * of the text.
   */
  kTXNSingleLineOnlyMask        = 1L << kTXNSingleLineOnlyBit,

  /*
   * Indicates that drag and drop will not be allowed in the text
   * object.
   */
  kTXNDisableDragAndDropMask    = 1L << kTXNDisableDragAndDropBit,

  /*
   * Indicates that QuickDraw will be used for imaging instead of the
   * default CoreGraphics (Quartz). [X-only]
   */
  kTXNUseQDforImagingMask       = 1L << kTXNUseQDforImagingBit,

  /*
   * Indicates that the text object will keep in single style no matter
   * what kind of changes made to the object. [X-only]
   */
  kTXNMonostyledTextMask        = 1L << kTXNMonostyledTextBit,

  /*
   * Indicates that ATSUI font substitution will be used. [X-only]
   */
  kTXNDoFontSubstitutionMask    = 1L << kTXNDoFontSubstitutionBit
};

/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • TextBox Option Bits                                                                               */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  Useful for TXNDrawUnicodeTextBox and TXNDrawCFStringTextBox APIs.                                   */
enum {
  kTXNSetFlushnessBit           = 0,
  kTXNSetJustificationBit       = 1,
  kTXNUseFontFallBackBit        = 2,
  kTXNRotateTextBit             = 3,
  kTXNUseVerticalTextBit        = 4,
  kTXNDontUpdateBoxRectBit      = 5,
  kTXNDontDrawTextBit           = 6,
  kTXNUseCGContextRefBit        = 7,
  kTXNImageWithQDBit            = 8,
  kTXNDontWrapTextBit           = 9
};


/*
 *  TXNTextBoxOptions
 *  
 *  Summary:
 *    Defines how text will be drawn by one of the TXNxxxDrawTextBox
 *    API.
 *  
 *  Discussion:
 *    These masks can be combined and added to a TXNTextBoxOptionsData
 *    structure to be passed to a TXNxxxDrawTextBox API.
 */
typedef OptionBits TXNTextBoxOptions;
enum {

  /*
   * Indicates that the text will be flush according to the line
   * direction.
   */
  kTXNSetFlushnessMask          = 1L << kTXNSetFlushnessBit,

  /*
   * Indicates that the text will be justified in the direction that
   * the text is displayed.  Horizontal text will be justified
   * horizontally, but not vertically.  Vertical text will be justified
   * vertically, but not horizontally.
   */
  kTXNSetJustificationMask      = 1L << kTXNSetJustificationBit,

  /*
   * Indicates that ATSUI font substitution (that searches for a font
   * that has a matching character) will be used.
   */
  kTXNUseFontFallBackMask       = 1L << kTXNUseFontFallBackBit,

  /*
   * Indicates that the text will be rotated.  The amount of rotation
   * is given in the rotation field of the TXNTextBoxOptionsData
   * structure and is in units of degrees (negative values indicate
   * clockwise rotation).
   */
  kTXNRotateTextMask            = 1L << kTXNRotateTextBit,

  /*
   * Indicates that the text will be displayed vertically from top to
   * bottom.
   */
  kTXNUseVerticalTextMask       = 1L << kTXNUseVerticalTextBit,

  /*
   * Indicates that the specified rectangle will not be updated.  If
   * you use this mask when you call a TXNDrawxxxTextBox function, the
   * funtion does not update the right coordinate (bottom coordinate if
   * kTXNUseVerticalTextMask is used) of the specified rectangle to
   * accommodate the longest line for text.
   */
  kTXNDontUpdateBoxRectMask     = 1L << kTXNDontUpdateBoxRectBit,

  /*
   * Indicates that the size of the text will be returned but the text
   * box will not be drawn.
   */
  kTXNDontDrawTextMask          = 1L << kTXNDontDrawTextBit,

  /*
   * Indicates that the client has provided a CGContext to be used for
   * CG imaging inside the text box. [X-only]
   */
  kTXNUseCGContextRefMask       = 1L << kTXNUseCGContextRefBit,

  /*
   * Indicates that imaging will be done using QuickDraw instead of the
   * default CoreGraphics. [X-only]
   */
  kTXNImageWithQDMask           = 1L << kTXNImageWithQDBit,

  /*
   * Indicates that text should not be wrapped. [X-only]
   */
  kTXNDontWrapTextMask          = 1L << kTXNDontWrapTextBit
};

/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • TextBox Options Data                                                                              */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
struct TXNTextBoxOptionsData {
  TXNTextBoxOptions   optionTags;
  Fract               flushness;
  Fract               justification;
  Fixed               rotation;
  void *              options;                /* for future use*/
};
typedef struct TXNTextBoxOptionsData    TXNTextBoxOptionsData;
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • File Types                                                                                        */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  Useful for TXNNewObject and TXNSave APIs.                                                           */
typedef OSType TXNFileType;
enum {
  kTXNTextensionFile            = 'txtn',
  kTXNTextFile                  = 'TEXT',
  kTXNPictureFile               = 'PICT',
  kTXNMovieFile                 = 'MooV',
  kTXNSoundFile                 = 'sfil',
  kTXNAIFFFile                  = 'AIFF',
  kTXNUnicodeTextFile           = 'utxt'
};



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Text Encoding Types                                                                               */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  Useful for TXNNewObject and TXNSave APIs. Only kTXNTextEditStyleFrameType is supported at this time.                                                        *|*/
typedef UInt32 TXNPermanentTextEncodingType;
enum {
  kTXNSystemDefaultEncoding     = 0,
  kTXNMacOSEncoding             = 1,
  kTXNUnicodeEncoding           = 2
};

/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Data Types                                                                                        */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
typedef OSType TXNDataType;
enum {
  kTXNTextData                  = 'TEXT',
  kTXNPictureData               = 'PICT',
  kTXNMovieData                 = 'moov',
  kTXNSoundData                 = 'snd ',
  kTXNUnicodeTextData           = 'utxt',
  kTXNTextAndMultimediaData     = 'txtn',
  kTXNRichTextFormatData        = 'RTF '
};

/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Action Keys                                                                                       */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
typedef UInt32 TXNActionKey;
enum {
  kTXNTypingAction              = 0,
  kTXNCutAction                 = 1,
  kTXNPasteAction               = 2,
  kTXNClearAction               = 3,
  kTXNChangeFontAction          = 4,
  kTXNChangeFontColorAction     = 5,
  kTXNChangeFontSizeAction      = 6,
  kTXNChangeStyleAction         = 7,
  kTXNAlignLeftAction           = 8,
  kTXNAlignCenterAction         = 9,
  kTXNAlignRightAction          = 10,
  kTXNDropAction                = 11,
  kTXNMoveAction                = 12,
  kTXNFontFeatureAction         = 13,
  kTXNFontVariationAction       = 14,
  kTXNUndoLastAction            = 1024  /*use if none of the above apply*/
};

/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Format Setting Constants                                                                          */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
typedef SInt8 TXNTabType;
enum {
  kTXNRightTab                  = -1,
  kTXNLeftTab                   = 0,
  kTXNCenterTab                 = 1
};

struct TXNTab {
  SInt16              value;
  TXNTabType          tabType;
  UInt8               filler;
};
typedef struct TXNTab                   TXNTab;
enum {
  kTXNLeftToRight               = 0,
  kTXNRightToLeft               = 1
};

enum {
  kTXNFlushDefault              = 0,    /*flush according to the line direction */
  kTXNFlushLeft                 = 1,
  kTXNFlushRight                = 2,
  kTXNCenter                    = 4,
  kTXNFullJust                  = 8,
  kTXNForceFullJust             = 16    /*flush left and right for all lines */
};

/*
  In version 1.2 of MLTE and later you can change the top, left and right margins. 
  The bottom margin is a placeholder for possible future enhancements. 
*/
struct TXNMargins {
  SInt16              topMargin;
  SInt16              leftMargin;
  SInt16              bottomMargin;
  SInt16              rightMargin;
};
typedef struct TXNMargins               TXNMargins;
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Control Tags                                                                                      */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
typedef FourCharCode TXNControlTag;
enum {
  kTXNLineDirectionTag          = 'lndr', /*not functional when userIO is not allowed.*/
  kTXNJustificationTag          = 'just', /*not functional when userIO is not allowed.*/
  kTXNIOPrivilegesTag           = 'iopv',
  kTXNSelectionStateTag         = 'slst',
  kTXNInlineStateTag            = 'inst',
  kTXNWordWrapStateTag          = 'wwrs',
  kTXNKeyboardSyncStateTag      = 'kbsy',
  kTXNAutoIndentStateTag        = 'auin',
  kTXNTabSettingsTag            = 'tabs',
  kTXNRefConTag                 = 'rfcn',
  kTXNMarginsTag                = 'marg',
  kTXNFlattenMoviesTag          = 'flat',
  kTXNDoFontSubstitution        = 'fSub', /*note : this could degrade performance greatly in the case of large documents.*/
  kTXNNoUserIOTag               = 'nuio',
  kTXNUseCarbonEvents           = 'cbcb',
  kTXNDrawCaretWhenInactiveTag  = 'dcrt', /*when using CG on OS X, this tag will be ignored.  Caret will not be drawn when inactive.*/
  kTXNDrawSelectionWhenInactiveTag = 'dsln',
  kTXNDisableDragAndDropTag     = 'drag',
  kTXNSingleLevelUndoTag        = 'undo', /*set this state during creation of the object. Switching Undo level back and forth is not recommended.*/
  kTXNVisibilityTag             = 'visb' /*set the visibility state of the object  */
};


/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Convenience Constants for TXNGet/SetTXNControls                                                   */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
enum {
  kTXNClearThisControl          = (long)0xFFFFFFFF, /*to clear an object control setting*/
  kTXNClearTheseFontFeatures    = (long)0x80000000 /*to clear atsui font feature(s)*/
};

/* kTXNIOPrivilegesTag*/
enum {
  kTXNReadWrite                 = false,
  kTXNReadOnly                  = true
};

/* kTXNSelectionStateTag*/
enum {
  kTXNSelectionOn               = true,
  kTXNSelectionOff              = false
};

/* kTXNInlineStateTag*/
enum {
  kTXNUseInline                 = false,
  kTXNUseBottomline             = true
};

/* kTXNWordWrapStateTag*/
enum {
  kTXNAutoWrap                  = false,
  kTXNNoAutoWrap                = true
};

/* kTXNKeyboardSyncStateTag*/
enum {
  kTXNSyncKeyboard              = false,
  kTXNNoSyncKeyboard            = true
};

/* kTXNAutoIndentStateTag*/
enum {
  kTXNAutoIndentOff             = false,
  kTXNAutoIndentOn              = true
};

/* kTXNDrawCaretWhenInactiveTag*/
enum {
  kTXNDontDrawCaretWhenInactive = false,
  kTXNDrawCaretWhenInactive     = true
};

/* kTXNDrawSelectionWhenInactiveTag*/
enum {
  kTXNDontDrawSelectionWhenInactive = false,
  kTXNDrawSelectionWhenInactive = true
};

/* kTXNDisableDragAndDropTag*/
enum {
  kTXNEnableDragAndDrop         = false,
  kTXNDisableDragAndDrop        = true
};

/* Formatting info */
union TXNControlData {
  UInt32              uValue;
  SInt32              sValue;
  TXNTab              tabValue;
  TXNMargins *        marginsPtr;
};
typedef union TXNControlData            TXNControlData;
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Offset/Selection Constants                                                                        */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
typedef UInt32 TXNOffset;
enum {
  kTXNUseCurrentSelection       = (unsigned long)0xFFFFFFFF,
  kTXNStartOffset               = 0,
  kTXNEndOffset                 = 0x7FFFFFFF
};

/* Useful for TXNShowSelection API.*/
enum {
  kTXNShowStart                 = false,
  kTXNShowEnd                   = true
};

/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Resource Constants                                                                                */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/* Useful for saving document                                                                           */
enum {
  kTXNSingleStylePerTextDocumentResType = 'MPSR',
  kTXNMultipleStylesPerTextDocumentResType = 'styl'
};


/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • URL Constants                                                                                     */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/* Currently not available.  Will be implemented in the future.                                         */
typedef UInt32 TXNHyperLinkState;
enum {
  kTXNLinkNotPressed            = 0,
  kTXNLinkWasPressed            = 1,
  kTXNLinkTracking              = 3
};

/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Type Attributes / ATSUI Features and Variations                                                                               */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  Since MLTE currently uses ATSUI by default, the available face types for kTXNQDFontStyleAttribute   */
/*  are limited by what's available in ATSUI.  Currently, MLTE supports types defined in MacTypes.h     */
/*  which are normal, bold, italic, underline, condensed, and extended.  An alternative is to use           */
/*  available QD compatibility tags defined in ATSUUnicode.h.                                           */
typedef FourCharCode TXNTypeRunAttributes;
enum {
  kTXNQDFontNameAttribute       = 'fntn',
  kTXNQDFontFamilyIDAttribute   = 'font',
  kTXNQDFontSizeAttribute       = 'size',
  kTXNQDFontStyleAttribute      = 'face',
  kTXNQDFontColorAttribute      = 'klor',
  kTXNTextEncodingAttribute     = 'encd',
  kTXNATSUIFontFeaturesAttribute = 'atfe',
  kTXNATSUIFontVariationsAttribute = 'atva',
  kTXNURLAttribute              = 'urla',
  kTXNATSUIStyle                = 'astl'
};

/*  kTXNQDFontSizeAttributeSize is obsolete and incorrect font sizes are always returned as a Fixed     */
/*  value, just as  they are passed to MLTE.  Use kTXNFontSizeAttributeSize instead.                    */
typedef ByteCount TXNTypeRunAttributeSizes;
enum {
  kTXNQDFontNameAttributeSize   = sizeof(Str255),
  kTXNQDFontFamilyIDAttributeSize = sizeof(SInt16),
  kTXNQDFontSizeAttributeSize   = sizeof(SInt16), /* obsolete*/
  kTXNQDFontStyleAttributeSize  = sizeof(Style),
  kTXNQDFontColorAttributeSize  = sizeof(RGBColor),
  kTXNTextEncodingAttributeSize = sizeof(TextEncoding),
  kTXNFontSizeAttributeSize     = sizeof(Fixed),
  kTXNATSUIStyleSize            = sizeof(ATSUStyle)
};


struct TXNATSUIFeatures {
  ItemCount           featureCount;
  ATSUFontFeatureType * featureTypes;
  ATSUFontFeatureSelector * featureSelectors;
};
typedef struct TXNATSUIFeatures         TXNATSUIFeatures;
struct TXNATSUIVariations {
  ItemCount           variationCount;
  ATSUFontVariationAxis * variationAxis;
  ATSUFontVariationValue * variationValues;
};
typedef struct TXNATSUIVariations       TXNATSUIVariations;
union TXNAttributeData {
  void *              dataPtr;
  UInt32              dataValue;
  TXNATSUIFeatures *  atsuFeatures;
  TXNATSUIVariations * atsuVariations;
  CFURLRef            urlReference;
};
typedef union TXNAttributeData          TXNAttributeData;
struct TXNTypeAttributes {
  TXNTypeRunAttributes  tag;
  ByteCount           size;
  TXNAttributeData    data;
};
typedef struct TXNTypeAttributes        TXNTypeAttributes;
/*
  kTXNNoFontVariations is returned in the dataValue field when the caller as asked
  to see if the variation is continuous and there was no variation in the continuous range
*/
enum {
  kTXNDontCareTypeSize          = (long)0xFFFFFFFF,
  kTXNDontCareTypeStyle         = 0xFF,
  kTXNIncrementTypeSize         = 0x00000001,
  kTXNDecrementTypeSize         = (long)0x80000000,
  kTXNUseScriptDefaultValue     = -1,
  kTXNNoFontVariations          = 0x7FFF
};


/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Style Continuous Bits                                                                             */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/* Useful for TXNGetContinuousTypeAttributes API.                                                       */
enum {
  kTXNFontContinuousBit         = 0,
  kTXNSizeContinuousBit         = 1,
  kTXNStyleContinuousBit        = 2,
  kTXNColorContinuousBit        = 3,
  kTXNATSUIStyleContinuousBit   = 4
};

typedef OptionBits TXNContinuousFlags;
enum {
  kTXNFontContinuousMask        = 1L << kTXNFontContinuousBit,
  kTXNSizeContinuousMask        = 1L << kTXNSizeContinuousBit,
  kTXNStyleContinuousMask       = 1L << kTXNStyleContinuousBit,
  kTXNColorContinuousMask       = 1L << kTXNColorContinuousBit,
  kTXNATSUIStyleContinuousMask  = 1L << kTXNATSUIStyleContinuousBit
};

/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Match Options Bits                                                                                */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/* Useful for TXNFind API.                                                                              */
enum {
  kTXNIgnoreCaseBit             = 0,
  kTXNEntireWordBit             = 1,
  kTXNUseEncodingWordRulesBit   = 31
};

typedef OptionBits TXNMatchOptions;
enum {
  kTXNIgnoreCaseMask            = 1L << kTXNIgnoreCaseBit,
  kTXNEntireWordMask            = 1L << kTXNEntireWordBit,
  kTXNUseEncodingWordRulesMask  = (unsigned long)(1L << kTXNUseEncodingWordRulesBit)
};

struct TXNMatchTextRecord {
  const void *        iTextPtr;
  SInt32              iTextToMatchLength;
  TextEncoding        iTextEncoding;
};
typedef struct TXNMatchTextRecord       TXNMatchTextRecord;
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Fonts Description                                                                                 */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
struct TXNMacOSPreferredFontDescription {
  UInt32              fontID;
  Fixed               pointSize;
  TextEncoding        encoding;
  Style               fontStyle;
};
typedef struct TXNMacOSPreferredFontDescription TXNMacOSPreferredFontDescription;
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Background                                                                                        */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*constants & typedefs for setting the background*/
typedef UInt32 TXNBackgroundType;
enum {
  kTXNBackgroundTypeRGB         = 1
};


/*
   The TXNBackgroundData is left as a union so that it can be expanded
   in the future to support other background types
*/
union TXNBackgroundData {
  RGBColor            color;
};
typedef union TXNBackgroundData         TXNBackgroundData;
struct TXNBackground {
  TXNBackgroundType   bgType;
  TXNBackgroundData   bg;
};
typedef struct TXNBackground            TXNBackground;
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Count Option Bits                                                                                 */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  Options for TXNGet/ClearActionChangeCount to decide what type(s) of action count to use.            */
enum {
  kTXNTextInputCountBit         = 0,
  kTXNRunCountBit               = 1
};

typedef OptionBits TXNCountOptions;
enum {
  kTXNTextInputCountMask        = 1L << kTXNTextInputCountBit,
  kTXNRunCountMask              = 1L << kTXNRunCountBit,
  kTXNAllCountMask              = kTXNTextInputCountMask | kTXNRunCountMask
};

/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Scrolling                                                                                         */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/* Use as a param in TXNScroll API*/
typedef UInt32 TXNScrollUnit;
enum {
  kTXNScrollUnitsInPixels       = 0,
  kTXNScrollUnitsInLines        = 1,
  kTXNScrollUnitsInViewRects    = 2
};

/* Use as a param in ScrollInfo callback*/
typedef UInt32 TXNScrollBarOrientation;
enum {
  kTXNHorizontal                = 0,
  kTXNVertical                  = 1
};

/* Use as a param in TXNActivate and TXNSetScrollbarState APIs*/
typedef Boolean TXNScrollBarState;
enum {
  kScrollBarsAlwaysActive       = true,
  kScrollBarsSyncWithFocus      = false
};

/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Draw Item Bits                                                                                    */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  Specifies which element(s) of the text object to render.   Useful in TXNDrawObject API.             */
enum {
  kTXNDrawItemScrollbarsBit     = 0,
  kTXNDrawItemTextBit           = 1,
  kTXNDrawItemTextAndSelectionBit = 2
};

typedef OptionBits TXNDrawItems;
enum {
  kTXNDrawItemScrollbarsMask    = 1L << kTXNDrawItemScrollbarsBit,
  kTXNDrawItemTextMask          = 1L << kTXNDrawItemTextBit,
  kTXNDrawItemTextAndSelectionMask = 1L << kTXNDrawItemTextAndSelectionBit,
  kTXNDrawItemAllMask           = (unsigned long)0xFFFFFFFF
};


/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Rectangle Keys                                                                                    */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  Each key corresponds to a specific bound for the object.  Useful in TXNGetHIRect API.               */

typedef UInt32                          TXNRectKey;
enum {
  kTXNViewRectKey               = 0,
  kTXNDestinationRectKey        = 1,
  kTXNTextRectKey               = 2,
  kTXNVerticalScrollBarRectKey  = 3,
  kTXNHorizontalScrollBarRectKey = 4
};


/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Carbon Events Info                                                                                */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  These are currently the only settings for the flags field of TXNCarbonEventInfo.                    */
/*  If you want the AppleEventHandlers removed use kTXNNoAppleEventHandlersMask.                        */
/*  If you want to subsequently restart AppleEvent Handlers after removing Texthandlers. Use            */
/*  kTXNRestartAppleEventHandlersMask.                                                                  */
enum {
  kTXNNoAppleEventHandlersBit   = 0,
  kTXNRestartAppleEventHandlersBit = 1
};

enum {
  kTXNNoAppleEventHandlersMask  = 1 << kTXNNoAppleEventHandlersBit,
  kTXNRestartAppleEventHandlersMask = 1 << kTXNRestartAppleEventHandlersBit
};

/* Dictionary keys currently supported in the TXNCarbonEventInfo dictionary*/
#define   kTXNTextHandlerKey                        CFSTR("TextInput")
#define   kTXNWindowEventHandlerKey                 CFSTR("WindowEvent")
#define   kTXNWindowResizeEventHandlerKey           CFSTR("WindowResize")
#define   kTXNCommandTargetKey                      CFSTR("CommandTarget")
#define   kTXNCommandUpdateKey                      CFSTR("CommandUpdate")
#define   kTXNFontMenuObjectKey                     CFSTR("FontMenuObject")
#define   kTXNActionKeyMapperKey                    CFSTR("ActionKeyMapper")
#define   kTXNWheelMouseEventHandlerKey             CFSTR("WheelMouseEvent")
#define   kTXNTSMDocumentAccessHandlerKey           CFSTR("TSMDocumentAccess")


/* Use this to pass an EventTargetRef to MLTE via the TXNSetTXNControl... call*/
struct TXNCarbonEventInfo {
  Boolean             useCarbonEvents;
  UInt8               filler;
  UInt16              flags;
  CFDictionaryRef     fDictionary;
};
typedef struct TXNCarbonEventInfo       TXNCarbonEventInfo;
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Callbacks                                                                                         */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
typedef CALLBACK_API( OSStatus , TXNFindProcPtr )(const TXNMatchTextRecord *matchData, TXNDataType iDataType, TXNMatchOptions iMatchOptions, const void *iSearchTextPtr, TextEncoding encoding, TXNOffset absStartOffset, ByteCount searchTextLength, TXNOffset *oStartMatch, TXNOffset *oEndMatch, Boolean *ofound, UInt32 refCon);
typedef CALLBACK_API( CFStringRef , TXNActionKeyMapperProcPtr )(TXNActionKey actionKey, UInt32 commandID);

typedef CALLBACK_API( void , TXNScrollInfoProcPtr )(SInt32 iValue, SInt32 iMaximumValue, TXNScrollBarOrientation iScrollBarOrientation, SInt32 iRefCon);
typedef STACK_UPP_TYPE(TXNFindProcPtr)                          TXNFindUPP;
typedef STACK_UPP_TYPE(TXNActionKeyMapperProcPtr)               TXNActionKeyMapperUPP;
typedef STACK_UPP_TYPE(TXNScrollInfoProcPtr)                    TXNScrollInfoUPP;
/*
 *  NewTXNFindUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern TXNFindUPP
NewTXNFindUPP(TXNFindProcPtr userRoutine)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewTXNActionKeyMapperUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern TXNActionKeyMapperUPP
NewTXNActionKeyMapperUPP(TXNActionKeyMapperProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewTXNScrollInfoUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern TXNScrollInfoUPP
NewTXNScrollInfoUPP(TXNScrollInfoProcPtr userRoutine)         AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  DisposeTXNFindUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeTXNFindUPP(TXNFindUPP userUPP)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeTXNActionKeyMapperUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeTXNActionKeyMapperUPP(TXNActionKeyMapperUPP userUPP)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeTXNScrollInfoUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeTXNScrollInfoUPP(TXNScrollInfoUPP userUPP)             AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;

/*
 *  InvokeTXNFindUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeTXNFindUPP(
  const TXNMatchTextRecord *  matchData,
  TXNDataType                 iDataType,
  TXNMatchOptions             iMatchOptions,
  const void *                iSearchTextPtr,
  TextEncoding                encoding,
  TXNOffset                   absStartOffset,
  ByteCount                   searchTextLength,
  TXNOffset *                 oStartMatch,
  TXNOffset *                 oEndMatch,
  Boolean *                   ofound,
  UInt32                      refCon,
  TXNFindUPP                  userUPP)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeTXNActionKeyMapperUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CFStringRef
InvokeTXNActionKeyMapperUPP(
  TXNActionKey           actionKey,
  UInt32                 commandID,
  TXNActionKeyMapperUPP  userUPP)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeTXNScrollInfoUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeTXNScrollInfoUPP(
  SInt32                   iValue,
  SInt32                   iMaximumValue,
  TXNScrollBarOrientation  iScrollBarOrientation,
  SInt32                   iRefCon,
  TXNScrollInfoUPP         userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;




/* **************************************************************************************************** */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*                                  •  MLTE APIs •                                                      */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/* **************************************************************************************************** */

/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Creating and Destroying Object                                                                    */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNCreateObject()
 *  
 *  Summary:
 *    Creates a new text object of type TXNObject, which is an opaque
 *    structure that handles text formatting.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iFrameRect:
 *      A pointer to a variable of type HIRect. The rectangle is used
 *      to specify the destination and view rectangles for the new MLTE
 *      object. A value of NULL indicates that the rectangle for the
 *      window port will be used as view and destination rectangles
 *      when the object is attached later on to the window. See
 *      TXNAttachObjectToWindowRef API below.
 *    
 *    iFrameOptions:
 *      A value of type TXNFrameOptions that specifies the options you
 *      want the object to support. “See Frame Options” in the MLTE
 *      Reference for a description of the options.
 *    
 *    oTXNObject:
 *      A pointer to a structure of type TXNObject. On return, this
 *      points to the opaque text object data structure allocated by
 *      the function. You need to pass this object to most MLTE
 *      functions.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TXNCreateObject(
  const HIRect *    iFrameRect,
  TXNFrameOptions   iFrameOptions,
  TXNObject *       oTXNObject)                               AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;




/*
 *  TXNDeleteObject()
 *  
 *  Summary:
 *    Delete a previously allocated TXNObject and all associated data
 *    structures. If the frameType is multiple frames all frames are
 *    released.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.  The text
 *      object to free.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNDeleteObject(TXNObject iTXNObject)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





/*
 *  TXNInitTextension()
 *  
 *  Summary:
 *    Initialize the Textension library.  Should be called as soon as
 *    possible after the Macintosh toolbox is initialized.  On OS 10.3
 *    or later, it's not necessary to call this routine. The cases
 *    where you may want to call this routine are: 1) A set of default
 *    fonts different from the system default is desired. 2) Want to
 *    have multimedia support 3) Want to use QuickdrawText instead of
 *    ATSUI to render the text.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iDefaultFonts:
 *      A table of font information including fontFamily ID, point
 *      size, style, and script code. The table can be NULL or can have
 *      an entry for any script for which you would like to to
 *      designate a default font.  Only a valid script number is
 *      required.  You can designate that Textension should use the
 *      default for a give script by setting the field to
 *      kTXNUseScriptDefaultValue (-1).
 *    
 *    iCountDefaultFonts:
 *      Count of entries in the iDefaultFonts parameter.
 *    
 *    iUsageFlags:
 *      Specify whether multimeida should be supported.
 *  
 *  Result:
 *    A result code indicating success or failure. Various MacOS errors
 *    are possible if something is wrong.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNInitTextension(
  const TXNMacOSPreferredFontDescription   iDefaultFonts[],          /* can be NULL */
  ItemCount                                iCountDefaultFonts,
  TXNInitOptions                           iUsageFlags)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNVersionInformation()
 *  
 *  Summary:
 *    Get the version number and a set of feature bits. 
 *    TXNVersionValue uses a NumVersion structure. See MacTypes.h for
 *    the format of the version.  Currently there are two feature bits:
 *     one for ATSUI default, another one for CarbonEvent default.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    oFeatureFlags:
 *      Pointer to a bit mask.  See TXNFeatureMask enum above. If
 *      kTXNWillDefaultToATSUIBit is set it means that by default MLTE
 *      will use ATSUI to image and measure text and will default to
 *      using Unicode to store characters.  If
 *      kTXNWillDefaultToCarbonEventBit is set, then MLTE will use
 *      carbon events by default and apple event will not be supported.
 *  
 *  Result:
 *    TXNVersionValue: Current version.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern TXNVersionValue 
TXNVersionInformation(TXNFeatureBits * oFeatureFlags)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Set/Get Window Associated with the Object                                                         */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNAttachObjectToWindowRef()
 *  
 *  Summary:
 *    Attaches a text object to a window.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.  The text
 *      object you want to attach to the input window.
 *    
 *    iWindowRef:
 *      A WindowRef for the window you want to attach the object to.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TXNAttachObjectToWindowRef(
  TXNObject   iTXNObject,
  WindowRef   iWindowRef)                                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  TXNGetWindowRef()
 *  
 *  Summary:
 *    Returns the window that the input object is attached to.
 *  
 *  Discussion:
 *    If no window is attached to the object it returns NULL.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.  The text
 *      object you want to attach to the input window.
 *  
 *  Result:
 *    The windowRef for the current window attached to the the text
 *    object.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern WindowRef 
TXNGetWindowRef(TXNObject iTXNObject)                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Event APIs                                                                                        */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNKeyDown()
 *  
 *  Summary:
 *    Process a keydown event. Note that if CJK script is installed and
 *    current font is CJK inline input will take place. This is always
 *    the case unless the application has requested the bottomline
 *    window or has turned off TSM (see initialization options above).
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque struct to apply keydown to.
 *    
 *    iEvent:
 *      The keydown event.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNKeyDown(
  TXNObject            iTXNObject,
  const EventRecord *  iEvent)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNAdjustCursor()
 *  
 *  Summary:
 *    Handle switching the cursor.  If over text area set to i-beam. 
 *    Over graphics, sound, movie, scrollbar or outside of window set
 *    to arrow.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque struct obtained from TXNCreateObject.
 *    
 *    ioCursorRgn:
 *      Region to be passed to WaitNextEvent.  Resized accordingly by
 *      TXNAdjustCursor.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNAdjustCursor(
  TXNObject   iTXNObject,
  RgnHandle   ioCursorRgn)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNClick()
 *  
 *  Summary:
 *    Process click in content region.  Takes care of scrolling,
 *    selecting text,  playing sound and movies, drag & drop, and
 *    double-clicks.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque struct obtained from TXNCreateObject.
 *    
 *    iEvent:
 *      The mousedown event.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNClick(
  TXNObject            iTXNObject,
  const EventRecord *  iEvent)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNSelectAll()
 *  
 *  Summary:
 *    Selects everything in a frame.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque struct obtained from TXNCreateObject.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNSelectAll(TXNObject iTXNObject)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNFocus()
 *  
 *  Summary:
 *    Focus the TXNObject.  Scrollbars and insertion point are made
 *    active  if iBecomingFocused is true, and inactive if false.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque struct obtained from TXNCreateObject.
 *    
 *    iBecomingFocused:
 *      true if becoming active.  false otherwise.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNFocus(
  TXNObject   iTXNObject,
  Boolean     iBecomingFocused)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNUpdate()
 *  
 *  Summary:
 *    Handle update event (i.e. draw everything in a frame.) This
 *    function calls the Toolbox BeginUpdate - EndUpdate functions for
 *    the window that was passed to TXNCreateObject.  This makes it
 *    inappropriate for windows that contain something else besides the
 *    TXNObject.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque struct obtained from TXNCreateObject.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNUpdate(TXNObject iTXNObject)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNDrawObject()
 *  
 *  Summary:
 *    Renders the current content of the TXNObject on the screen.
 *  
 *  Discussion:
 *    Redraws the object element(s) specified in the TXNDrawItems
 *    flags.  Drawing is limited to the input clip rectangle.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject. Draw into this
 *      text object.
 *    
 *    iClipRect:
 *      A pointer to a HIRect. If the rectangle is NULL, MLTE uses its
 *      view rectangle when drawing. If the rectangle is not NULL, MLTE
 *      will intersect iClipRect with the view rectangle to determine
 *      the rectangle to draw.  MLTE will not draw in area not covered
 *      by the port's clip region.  Therefore, a given clipRect larger
 *      than the port's clip region will be trimmed down.
 *    
 *    iDrawItems:
 *      A value of type TXNDrawItems. Indicates what element(s) of the
 *      object are to be drawn.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TXNDrawObject(
  TXNObject       iTXNObject,
  const HIRect *  iClipRect,
  TXNDrawItems    iDrawItems)                                 AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;




/*
 *  TXNForceUpdate()
 *  
 *  Summary:
 *    Force a frame to be updated.  Very much like toolbox call
 *    InvalRect.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNForceUpdate(TXNObject iTXNObject)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNGetSleepTicks()
 *  
 *  Summary:
 *    Depending on state of window get the appropriate sleep time to be
 *    passed to WaitNextEvent.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Result:
 *    A UInt32 value of the appropriate sleep time.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern UInt32 
TXNGetSleepTicks(TXNObject iTXNObject)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  TXNIdle()
 *  
 *  Summary:
 *    Do necessary Idle time processing. Typically flash the cursor. If
 *    a TextService is active pass a NULL event to the Text Service so
 *    it gets  time.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNIdle(TXNObject iTXNObject)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNGrowWindow()
 *  
 *  Summary:
 *    Handle mouse-down in grow region.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iEvent:
 *      The mousedown event
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNGrowWindow(
  TXNObject            iTXNObject,
  const EventRecord *  iEvent)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNZoomWindow()
 *  
 *  Summary:
 *    Handle mouse-down in zoom.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iPart:
 *      Value returned by FindWindow
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNZoomWindow(
  TXNObject   iTXNObject,
  SInt16      iPart)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Redo/Undo                                                                                         */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNCanUndo()
 *  
 *  Summary:
 *    Use this to determine if the Undo item in Edit menu should be
 *    highlighted or not. Tells you if last command was undoable.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    oTXNActionKey:
 *      The key code that the caller can use to pick a string to
 *      describe the undoable action in the undo item.  Pass in NULL if
 *      the string isn't needed.
 *  
 *  Result:
 *    Boolean: If True the last command is undoable and the undo item
 *    in the menu should be active.  If false last command cannot be
 *    undone and undo should be grayed in the menu.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern Boolean 
TXNCanUndo(
  TXNObject       iTXNObject,
  TXNActionKey *  oTXNActionKey)       /* can be NULL */      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  TXNUndo()
 *  
 *  Summary:
 *    Undo the last command.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNUndo(TXNObject iTXNObject)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNCanRedo()
 *  
 *  Summary:
 *    Use this to determine if the current item on the undo stack is
 *    redoable.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    oTXNActionKey:
 *      The key code that the caller can use to pick a string to
 *      describe the redoable action in the redo item.  Pass in NULL if
 *      the string isn't needed.
 *  
 *  Result:
 *    If it returns true, then the redo item in the edit menu should be
 *    active.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern Boolean 
TXNCanRedo(
  TXNObject       iTXNObject,
  TXNActionKey *  oTXNActionKey)       /* can be NULL */      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNRedo()
 *  
 *  Summary:
 *    Redo the last command.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNRedo(TXNObject iTXNObject)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNClearUndo()
 *  
 *  Summary:
 *    Purge the undo stack
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   in Textension not yet available
 */
extern OSStatus 
TXNClearUndo(TXNObject iTXNObject)                            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Editing                                                                                           */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNCut()
 *  
 *  Summary:
 *    Cut the current selection to the clipboard.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNCut(TXNObject iTXNObject)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNCopy()
 *  
 *  Summary:
 *    Copy current selection to the clipboard.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNCopy(TXNObject iTXNObject)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNPaste()
 *  
 *  Summary:
 *    Paste from the clipboard.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNPaste(TXNObject iTXNObject)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNClear()
 *  
 *  Summary:
 *    Clear the current selection.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNClear(TXNObject iTXNObject)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNIsScrapPastable()
 *  
 *  Summary:
 *    Test to see if the current scrap contains data that is supported
 *    by Textension.  Used to determine if Paste item in Edit menu
 *    should be active or inactive. The types of data supported depends
 *    on what data types were specified in the TXNInitTextension
 *    options.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Result:
 *    Boolean: True if data type in Clipboard is supported.  False if
 *    not a supported data type.  If result is True the Paste item in
 *    the menu can be highlighted.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern Boolean 
TXNIsScrapPastable(void)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Selection                                                                                         */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNGetSelection()
 *  
 *  Summary:
 *    Get the absolute offsets of the current selection.  Embedded
 *    graphics, sound, etc. each count as one character.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    oStartOffset:
 *      Absolute beginning of the current selection.
 *    
 *    oEndOffset:
 *      End of current selection.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNGetSelection(
  TXNObject    iTXNObject,
  TXNOffset *  oStartOffset,
  TXNOffset *  oEndOffset)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNShowSelection()
 *  
 *  Summary:
 *    Scroll the current selection into view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iShowEnd:
 *      If true the end of the selection is scrolled into view. If
 *      false the beginning of selection is scrolled into view.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNShowSelection(
  TXNObject   iTXNObject,
  Boolean     iShowEnd)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  TXNIsSelectionEmpty()
 *  
 *  Summary:
 *    Call to find out if the current selection is empty. Use this to
 *    determine if Paste, Cut, Copy, Clear should be highlighted in
 *    Edit menu.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Result:
 *    Boolean: True if current selection is empty (i.e. start offset ==
 *    end offset). False if selection is not empty.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern Boolean 
TXNIsSelectionEmpty(TXNObject iTXNObject)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNSetSelection()
 *  
 *  Summary:
 *    Set the current selection.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iStartOffset:
 *      New beginning.
 *    
 *    iEndOffset:
 *      New end.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNSetSelection(
  TXNObject   iTXNObject,
  TXNOffset   iStartOffset,
  TXNOffset   iEndOffset)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Set/Get Type Attributes                                                                           */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNGetContinuousTypeAttributes()
 *  
 *  Summary:
 *    Test the current selection to see if type size, style, color
 *    and/or font are continuous. That is is the current selection made
 *    up of one font, one font size, one Style, and/or one color.  On
 *    return examine the flags to see if the attributes specified were
 *    continuous.  If an attribute is continuous then the dataValue
 *    field in the TXNTypeAttributes can be examined to get the
 *    continous value.  Remember that for color you pass a ptr to an
 *    RGBColor in attr[0].data.dataPtr.
 *  
 *  Discussion:
 *    If examining kTXNATSUIStyleContinuous bit, be sure to call
 *    ATSUDisposeStyle to dispose the style that is returned from MLTE.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    oContinuousFlags:
 *      Bits which can be examined to see if type size, style, color,
 *      and/or font are continuous. Example: if ( 
 *      TXNGetContinuousTypeAttributes( txnObject, &flags, 1, &attr )
 *      == noErr ) { if ( flags & kTXNFontContinuousMask ) ....check a
 *      font name
 *    
 *    iCount:
 *      Count of TXNTypeAttributes records in the ioTypeAttributes
 *      array.
 *    
 *    ioTypeAttributes:
 *      Array of TXNTypeAttributes that indicate the type attributes
 *      the caller is interested in. For example, if you wanted to know
 *      if the current selection was continuous in terms of being all
 *      one same font size you could do something like this.
 *      TXNTypeAttributes       attr[1] = { TXNFontSizeAttribute,
 *      sizeof(Fixed),{ 0 } } on return  from the function if size is
 *      continuous (i.e. if the bit 3 of flags is set) then the third
 *      field (attr[0].data.dataValue) will contain the size of the
 *      font as a Fixed value.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNGetContinuousTypeAttributes(
  TXNObject             iTXNObject,
  TXNContinuousFlags *  oContinuousFlags,
  ItemCount             iCount,
  TXNTypeAttributes     ioTypeAttributes[])     /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNSetTypeAttributes()
 *  
 *  Summary:
 *    Set the current ranges font information.  Values are passed in
 *    the attributes array. Values <= sizeof(UInt32) are passed by
 *    value. > sizeof(UInt32) are passed as a pointer. That is the
 *    TXNTypeAttributes' 3rd field is a union that servers as either a
 *    32-bit integer where values can be written or a 32-bit pointer a
 *    value.  Functional in NoUserIO mode.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iAttrCount:
 *      Count of type attributes in the TXNTypeAttributes array.
 *    
 *    iAttributes:
 *      Attributes that caller would like to set.
 *    
 *    iStartOffset:
 *      Start of the range where text attributes should be changed.
 *    
 *    iEndOffset:
 *      End of the range.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNSetTypeAttributes(
  TXNObject                 iTXNObject,
  ItemCount                 iAttrCount,
  const TXNTypeAttributes   iAttributes[],
  TXNOffset                 iStartOffset,
  TXNOffset                 iEndOffset)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Set/Get Object Controls                                                                           */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNSetTXNObjectControls()
 *  
 *  Summary:
 *    Sets formatting and privileges attributes (such as justification,
 *    line direction, tab values, and read-only status) that apply to
 *    the entire text object.
 *  
 *  Discussion:
 *    On systems that use Apple Type Services for Unicode Imaging
 *    (ATSUI), the ATSUI line control attribute tags can be passed to
 *    this function in the iControlTag parameter. This is the case for
 *    all the ATSUI tags except kATSULineRotationTag. ATSUI tags are
 *    applied to the entire text object.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      The text object that identifies the document for which you want
 *      to set formatting and privileges attributes.
 *    
 *    iClearAll:
 *      A Boolean value. If you set this to true, all formatting and
 *      privileges attributes are reset to their default value. That
 *      is, true clears existing tags and resets each to its default
 *      value.  This can be done even when the object is in NoUserIO
 *      mode.
 *    
 *    iControlCount:
 *      The number of items in the iControlTags array.
 *    
 *    iControlTags:
 *      An array of values that specifies kind of data that is passed
 *      in the iControlData parameter. See “Formatting and Privileges
 *      Settings” for a description of possible values. On systems that
 *      use Apple Type Services for Unicode Imaging (ATSUI), you can
 *      also pass ATSUI attribute tag constants. See the ATSUI
 *      documentation for a description of the ATSUI constants. Can be
 *      NULL if iClearAll is true.
 *    
 *    iControlData:
 *      An array of TXNControlData unions that contain the information
 *      your application wants to set. The value you supply to the
 *      iControlTags parameter specifies how the union of type
 *      TXNControlData is treated. You must make sure that the value
 *      you assign to the iControlData parameter is the appropriate
 *      type implied by the value you passed in the iControlTags
 *      parameter. Can be NULL if iClearAll is true.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNSetTXNObjectControls(
  TXNObject              iTXNObject,
  Boolean                iClearAll,
  ItemCount              iControlCount,
  const TXNControlTag    iControlTags[],      /* can be NULL */
  const TXNControlData   iControlData[])      /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNGetTXNObjectControls()
 *  
 *  Summary:
 *    Gets the current formatting and privileges attributes (such as
 *    justification, line direction, tab values, and read-only status)
 *    for a text object.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      The text object that identifies the document to be activated.
 *      If NULL then the default value for an MLTE object is returned.
 *    
 *    iControlCount:
 *      The number of items in the iControlTags array.
 *    
 *    iControlTags:
 *      An array of values that specify the kind of formatting
 *      information you want returned in the oControlData array. See
 *      “Formatting and Privileges Settings” for a description of
 *      possible values.
 *    
 *    oControlData:
 *      An array of TXNControlData unions. On return, the array
 *      contains the information that was requested through the
 *      iControlTags array. Your application must allocate the
 *      oControlData array.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNGetTXNObjectControls(
  TXNObject             iTXNObject,          /* can be NULL */
  ItemCount             iControlCount,
  const TXNControlTag   iControlTags[],
  TXNControlData        oControlData[])                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Other Settings                                                                                    */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNSetBackground()
 *  
 *  Summary:
 *    Set the type of background the TXNObject's text, etc. is drawn
 *    onto.  At this point the background can be a color.  Functional
 *    in NoUserIO mode.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iBackgroundInfo:
 *      Struct containing information that describes the background.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNSetBackground(
  TXNObject              iTXNObject,
  const TXNBackground *  iBackgroundInfo)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNEchoMode()
 *  
 *  Summary:
 *    Put the TXNObject into echo mode. What that means is that all
 *    characters in the TXNObject have the character 'echoCharacter'
 *    substituted for the actual glyph when drawing occurs.
 *  
 *  Discussion:
 *    Note that the echoCharacter is typed as a UniChar, but this is
 *    done merely to facilitate passing any 2 byte character.  The
 *    encoding parameter actually determines the encoding used to
 *    locate a font and display a character.  Thus if you wanted to
 *    display the diamond found in the Shift-JIS encoding for MacOS you
 *    would pass in 0x86A6 for the character but an encoding that was
 *    built to represent the MacOS Japanese encoding.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from IncomingDataFilter callback.
 *    
 *    iEchoCharacter:
 *      Character to use in substitution.
 *    
 *    iEncoding:
 *      Encoding from which character is drawn.
 *    
 *    iOn:
 *      True if turning EchoMode on.  False if turning it off.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNEchoMode(
  TXNObject      iTXNObject,
  UniChar        iEchoCharacter,
  TextEncoding   iEncoding,
  Boolean        iOn)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Retrieve Run Info                                                                                 */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNCountRunsInRange()
 *  
 *  Summary:
 *    Given a range specified by the starting and ending offset return
 *    a count of the runs in that range.  Run in this case means
 *    changes in TextSyles or a graphic or sound.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iStartOffset:
 *      Start of range.
 *    
 *    iEndOffset:
 *      End of range.
 *    
 *    oRunCount:
 *      Count of runs in the range
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNCountRunsInRange(
  TXNObject    iTXNObject,
  TXNOffset    iStartOffset,
  TXNOffset    iEndOffset,
  ItemCount *  oRunCount)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  TXNGetIndexedRunInfoFromRange()
 *  
 *  Summary:
 *    Gets information about a run in a range of data.
 *  
 *  Discussion:
 *    You should first call the TXNCountRunsInRange function to get the
 *    count. The TXNTypeAttributes structure must specify the text
 *    attribute in which the application is interested. In other words,
 *    the tag field must be set. If you asked for the kTXNATSUIStyle
 *    info, you are now responsible for disposing the ATSUI style
 *    returned from the attribute array by calling ATSUDisposeStyle.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      The text object for the current text area.
 *    
 *    iIndex:
 *      The value that corresponds to the run for which you want to get
 *      information. You call the TXNCountRunsInRange function to get
 *      the number of runs in a range. The iIndex parameter is
 *      zero-based, so its possible values are from 0 to the number of
 *      runs in a range minus 1.
 *    
 *    iStartOffset:
 *      The offset at which you want to start to obtain run information.
 *    
 *    iEndOffset:
 *      The offset at which you want run information to end.
 *    
 *    oRunStartOffset:
 *      On return, a pointer to a value that identifies the start of
 *      run relative to the beginning of the text, not the beginning of
 *      the range you specified in the iStartOffset parameter.
 *    
 *    oRunEndOffset:
 *      On return, a pointer to a value that identifies the end of the
 *      run relative to the beginning of the text, not the beginning of
 *      the range you specified in the iStartOffset parameter.
 *    
 *    oRunDataType:
 *      On return, a pointer to a value that identifies the type of
 *      data in the run. See “Supported Data Types” for a description
 *      of possible values.
 *    
 *    iTypeAttributeCount:
 *      The number of font attributes.
 *    
 *    ioTypeAttributes:
 *      A pointer to a structure of type TXNTypeAttributes. On input,
 *      you specify the attribute (such as size) in the tag field and
 *      the attribute size in the size field. You can pass NULL for the
 *      data field. On return, the data field contains the attribute
 *      data. The data field is a union that serves either as a 32-bit
 *      integer or a 32-bit pointer, depending on the size field.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNGetIndexedRunInfoFromRange(
  TXNObject            iTXNObject,
  ItemCount            iIndex,
  TXNOffset            iStartOffset,
  TXNOffset            iEndOffset,
  TXNOffset *          oRunStartOffset,           /* can be NULL */
  TXNOffset *          oRunEndOffset,             /* can be NULL */
  TXNDataType *        oRunDataType,              /* can be NULL */
  ItemCount            iTypeAttributeCount,
  TXNTypeAttributes *  ioTypeAttributes)          /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Set/Get Data                                                                                      */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNDataSize()
 *  
 *  Summary:
 *    Return the size in bytes of the characters in a given TXNObject.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Result:
 *    The bytes required to hold the characters.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern ByteCount 
TXNDataSize(TXNObject iTXNObject)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNGetData()
 *  
 *  Summary:
 *    Copy the data in the range specified by startOffset and endOffset.
 *  
 *  Discussion:
 *    This function should be used in conjunction with TXNNextDataRun. 
 *    The client would call TXNCountRunsInRange to the number of data
 *    runs in a given range.  The client can then walk the runs with
 *    the function TXNGetIndexedRunInfoFromRange. 
 *    TXNGetIndexedRunInfoFromRange lets you examine each runs type and
 *    text attributes. For each data run of interest (i.e. one whose
 *    data the caller wanted to look at) the client would call
 *    TXNGetData. The handle passed to TXNGetData should not be
 *    allocated. TXNGetData takes care of allocating the dataHandle as
 *    necessary.  However, the caller is responsible for disposing the
 *    handle.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iStartOffset:
 *      Absolute offset from which data copy should begin.
 *    
 *    iEndOffset:
 *      Absolute offset at which data copy should end.
 *    
 *    oDataHandle:
 *      If noErr a new handle containing the requested data. The caller
 *      is responsible for disposing the handle.  Note that the handle
 *      is a copy so it can be safely disposed at any time.
 *  
 *  Result:
 *    Memory errors or TXN_IllegalToCrossDataBoundaries if offsets
 *    specify a range that crosses a data type boundary.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNGetData(
  TXNObject   iTXNObject,
  TXNOffset   iStartOffset,
  TXNOffset   iEndOffset,
  Handle *    oDataHandle)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNGetDataEncoded()
 *  
 *  Summary:
 *    Copy the data in the range specified by startOffset and endOffset.
 *  
 *  Discussion:
 *    The handle passed to TXNGetDataEncoded should not be allocated.
 *    TXNGetData takes care of allocating the dataHandle as necessary. 
 *    However, the caller is responsible for disposing the handle.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iStartOffset:
 *      Absolute offset from which data copy should begin.
 *    
 *    iEndOffset:
 *      Absolute offset at which data copy should end.
 *    
 *    oDataHandle:
 *      If noErr a new handle containing the requested data.
 *    
 *    iEncoding:
 *      should be kTXNTextData or kTXNUnicodeTextData.
 *  
 *  Result:
 *    Memory errors or  TXN_IllegalToCrossDataBoundaries if offsets
 *    specify a range that crosses a data type boundary.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNGetDataEncoded(
  TXNObject     iTXNObject,
  TXNOffset     iStartOffset,
  TXNOffset     iEndOffset,
  Handle *      oDataHandle,
  TXNDataType   iEncoding)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNSetDataFromCFURLRef()
 *  
 *  Summary:
 *    Replaces a range of data with the content of a file.
 *  
 *  Discussion:
 *    Uses URL file name extension to determine the type of the input
 *    file. If the entire content is replaced, calling TXNRevert will
 *    revert to the last saved CFURLRef.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.  Data will be
 *      added to this text object.
 *    
 *    iURL:
 *      The url referring to the file which contains the data you want
 *      to add to the object.
 *    
 *    iStartOffset:
 *      The starting offset at which to insert the file into a
 *      document.. If you want to replace the entire text content then
 *      set the iStartOffset parameter to kTXNStartOffset.
 *    
 *    iEndOffset:
 *      The ending position of the range being replaced by the file. If
 *      you want to replace the entire text content then set the
 *      iEndOffset parameter to kTXNEndOffset.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TXNSetDataFromCFURLRef(
  TXNObject   iTXNObject,
  CFURLRef    iURL,
  TXNOffset   iStartOffset,
  TXNOffset   iEndOffset)                                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;




/*
 *  TXNSetData()
 *  
 *  Summary:
 *    Replaces a range of data (text, graphics, and so forth).
 *  
 *  Discussion:
 *    Functional in NoUserIO mode.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      The text object that identifies the document in which you want
 *      to replace data.
 *    
 *    iDataType:
 *      The type of the replacement data. See “Supported Data Types”
 *      for a description of possible values.
 *    
 *    iDataPtr:
 *      A pointer to the data that will replace the data that is in the
 *      range specified by the iStartOffset and iEndOffset parameters. 
 *      Can be NULL if the start and end offsets are different.
 *    
 *    iDataSize:
 *      The size of the data to which iDataPtr points.
 *    
 *    iStartOffset:
 *      The beginning of the range of data to replace. You can use the
 *      TXNGetSelection function to get the absolute offsets of the
 *      current selection.
 *    
 *    iEndOffset:
 *      The end of the range to replace. You can use the
 *      TXNGetSelection function to get the absolute offsets of the
 *      current selection. If you want to insert text, the ending and
 *      starting offsets should be the same value.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNSetData(
  TXNObject     iTXNObject,
  TXNDataType   iDataType,
  const void *  iDataPtr,           /* can be NULL */
  ByteCount     iDataSize,
  TXNOffset     iStartOffset,
  TXNOffset     iEndOffset)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Saving Data                                                                                       */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNFlattenObjectToCFDataRef()
 *  
 *  Summary:
 *    Flattens a text object so it can be saved to disk or embedded
 *    with other data.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.  Retrieve
 *      flattened data from this text object.
 *    
 *    iTXNDataType:
 *      A value of type TXNDataType that specifies the format in which
 *      the data is written out.
 *    
 *    oDataRef:
 *      A pointer to a structure of type CFDataRef. On return the data
 *      will contain a flattened version of the iTXNObject in the
 *      format specified by iTXNDataType. Clients are responsible to
 *      retain the returned CFDataRef.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TXNFlattenObjectToCFDataRef(
  TXNObject     iTXNObject,
  TXNDataType   iTXNDataType,
  CFDataRef *   oDataRef)                                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;




/*
 *  TXNSave()
 *  
 *  Summary:
 *    Save the contents of the document as the given type.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iType:
 *      The type of file to create.
 *    
 *    iResType:
 *      When saving file as plain TEXT the type of resource to save
 *      style information. Use kTXNMultipleStylesPerTextDocumentResType
 *      if your document contains multiple styles and you want a
 *      SimpleText like document.  Use
 *      kTXNSingleStylePerTextDocumentResType if the document has a
 *      single style and you would like a BBEdit, MPW, CW type of
 *      document.
 *    
 *    iPermanentEncoding:
 *      The encoding in which the document should be saved (Unicode,
 *      Text or System default).
 *    
 *    iFileSpecification:
 *      The file specification to which the document should be saved.
 *      The file must have been opened by the caller.  The file
 *      specification is remembered by the TXNObject and is used for
 *      any subsequent calls to TXNRevert.
 *    
 *    iDataReference:
 *      The data fork ref num.  This is used to write data to the data
 *      fork of the file. The data is written beginning at the current
 *      mark.
 *    
 *    iResourceReference:
 *      The resource fork ref num.  If the caller has specified that
 *      style information be saved as a resource (MPW or SimpleText)
 *      than this should be a valid reference to an open resource fork.
 *       If the txtn format is being used than this input value is
 *      ignored.
 *  
 *  Result:
 *    The result of writing the file.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNSave(
  TXNObject                      iTXNObject,
  TXNFileType                    iType,
  OSType                         iResType,
  TXNPermanentTextEncodingType   iPermanentEncoding,
  const FSSpec *                 iFileSpecification,
  SInt16                         iDataReference,
  SInt16                         iResourceReference)          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNRevert()
 *  
 *  Summary:
 *    Revert  to the last saved version of this document.  If the file
 *    was not previously saved the document is reverted to an empty
 *    document.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Result:
 *    A result code indicating success or failure. (such as File
 *    Manager errors)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNRevert(TXNObject iTXNObject)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Printing                                                                                          */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNPageSetup()
 *  
 *  Summary:
 *    Display the Page Setup dialog of the current default printer and
 *    react to any changes (i.e. Reformat the text if the page layout
 *    changes.)
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Result:
 *    A result code indicating success or failure. ( such as Print
 *    Manager errors )
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNPageSetup(TXNObject iTXNObject)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNPrint()
 *  
 *  Summary:
 *    Print the document.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Result:
 *    A result code indicating success or failure. ( such as Print
 *    Manager errors )
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNPrint(TXNObject iTXNObject)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Search                                                                                            */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNFind()
 *  
 *  Summary:
 *    Find a piece of text or a graphics object.
 *  
 *  Discussion:
 *    The default matching behavior is pretty simple for Text a basic
 *    binary compare is done.  If the matchOptions say to ignore case
 *    the characters to be searched are duplicated and case
 *    neutralized. This naturally can fail due to lack of memory if
 *    there is a large amount of text.  It also slows things down.  If
 *    MatchOptions say find an entire word that once a match is found
 *    an effort is made to determine if the match is a word.  The
 *    default behavior is to test the character before and after the to
 *    see if it is White space.  If the kTXNUseEncodingWordRulesBit is
 *    set than the Script Manager's FindWord function is called to make
 *    this determination. If the caller is looking for a non-text type
 *    than each non-text type in the document is returned. If more
 *    elaborate ( a regular expression processor or whatever ) is what
 *    you want then that is what the FindProc is for.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iMatchTextDataPtr:
 *      Ptr to a MatchTextRecord which contains the text to match, the
 *      length of that text and the TextEncoding the text is encoded
 *      in.  This must be there if you are looking for Text, but can be
 *      NULL if you are looking for a graphics object.
 *    
 *    iDataType:
 *      The type of data to find.  This can be any of the types defined
 *      in TXNDataType enum (TEXT, PICT, moov, snd ).  However, if
 *      PICT, moov, or snd is passed then the default behavior is to
 *      match on any non-Text object.  If you really want to find a
 *      specific type you can provide a custom find callback or ignore
 *      matches which aren't the precise type you are interested in.
 *    
 *    iMatchOptions:
 *      Options on what to search for.
 *    
 *    iStartSearchOffset:
 *      The offset at which a search should begin. The constant
 *      kTXNStartOffset specifies the start of the objects data.
 *    
 *    iEndSearchOffset:
 *      The offset at which the search should end. The constant
 *      kTXNEndOffset specifies the end of the objects data.
 *    
 *    iFindProc:
 *      A custom callback.  If will be called to match things rather
 *      than the default matching behavior.
 *    
 *    iRefCon:
 *      This can be use for whatever the caller likes.  It is passed to
 *      the FindProc (if a FindProc is provided.
 *    
 *    oStartMatchOffset:
 *      Absolute offset to start of match.  set to 0xFFFFFFFF if not
 *      match.
 *    
 *    oEndMatchOffset:
 *      Absolute offset to end of match.  Set to 0xFFFFFFFF is no match.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNFind(
  TXNObject                   iTXNObject,
  const TXNMatchTextRecord *  iMatchTextDataPtr,        /* can be NULL */
  TXNDataType                 iDataType,
  TXNMatchOptions             iMatchOptions,
  TXNOffset                   iStartSearchOffset,
  TXNOffset                   iEndSearchOffset,
  TXNFindUPP                  iFindProc,
  SInt32                      iRefCon,
  TXNOffset *                 oStartMatchOffset,
  TXNOffset *                 oEndMatchOffset)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Font Defaults                                                                                     */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNSetFontDefaults()
 *  
 *  Summary:
 *    For a given TXNObject specify the font defaults for each script.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iCount:
 *      Count of FontDescriptions.
 *    
 *    iFontDefaults:
 *      Array of FontDescriptions.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNSetFontDefaults(
  TXNObject                                iTXNObject,
  ItemCount                                iCount,
  const TXNMacOSPreferredFontDescription   iFontDefaults[])   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNGetFontDefaults()
 *  
 *  Summary:
 *    For a given TXNObject make a copy of the font defaults.
 *  
 *  Discussion:
 *    To determine how many font descriptions need to be in the array
 *    you should call this function with a NULL for the array.  iCount
 *    will return with the number of font defaults currently stored.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    ioCount:
 *      Count of FontDescriptions in the array.
 *    
 *    oFontDefaults:
 *      Array of FontDescriptins to be filled out.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNGetFontDefaults(
  TXNObject                          iTXNObject,
  ItemCount *                        ioCount,
  TXNMacOSPreferredFontDescription   oFontDefaults[])     /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Font Menu                                                                                         */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNNewFontMenuObject()
 *  
 *  Summary:
 *    Get a FontMenuObject.  Caller can extract a fontmenu from this
 *    object and pass this object to the active TXNObject to handle
 *    events in the font menu.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iFontMenuHandle:
 *      An empty menu handle (well the title is there) that the caller
 *      created via NewMenu or GetNewMenu. This menu handle should not
 *      be disposed before the returned TXNFontMenuObject has been
 *      disposed via TXNDisposeFontMenuObject.
 *    
 *    iMenuID:
 *      The MenuID for iFontMenuHandle.
 *    
 *    iStartHierMenuID:
 *      The first MenuID to use if any hierarchical menus need to be
 *      created. TXNNewFontMenuObject uses SetMenuItemHierarchicalID
 *      when creating hierarchial menus.  The iStartHierMenuID must
 *      therefor follow the rules for this function.  On systems less
 *      than system 8.5 the submenuID must be less than 255.  For
 *      systems above system 8.5 the range can be as large can be as
 *      large 32767.  However, it is important to remember that
 *      TXNNewFontMenuObject only uses iStartHierMenuID as a starting
 *      id when adding hierarchical menus.  Therefore provide plenty of
 *      room to increment this value. For example, on a system less
 *      than 8.5 it would be good to start at 175.  On systems greater
 *      than 8.5 it is probably a good idea to not use a value higher
 *      than 32000.
 *    
 *    oTXNFontMenuObject:
 *      A font menu object.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNNewFontMenuObject(
  MenuRef              iFontMenuHandle,
  SInt16               iMenuID,
  SInt16               iStartHierMenuID,
  TXNFontMenuObject *  oTXNFontMenuObject)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNGetFontMenuHandle()
 *  
 *  Summary:
 *    Get the MenuRef from the TXNFontMenuObject.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNFontMenuObject:
 *      A Font Menu Object obtained from TXNNewFontMenuObject.
 *    
 *    oFontMenuHandle:
 *      The returned font menu. Returned value could be NULL.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNGetFontMenuHandle(
  TXNFontMenuObject   iTXNFontMenuObject,
  MenuRef *           oFontMenuHandle)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#define TXNGetFontMenuRef TXNGetFontMenuHandle


/*
 *  TXNDisposeFontMenuObject()
 *  
 *  Summary:
 *    Dispose a TXNFontMenuObject and its font menu handle.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNFontMenuObject:
 *      A Font Menu Object obtained from TXNNewFontMenuObject.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNDisposeFontMenuObject(TXNFontMenuObject iTXNFontMenuObject) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNDoFontMenuSelection()
 *  
 *  Summary:
 *    Given the menuID and menu item returned by MenuSelect determine
 *    the selected font and change the current selection to be that
 *    Font.  If the input TXNObject is not active a parameter error is
 *    returned.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iTXNFontMenuObject:
 *      A Font Menu Object obtained from TXNNewFontMenuObject.
 *    
 *    iMenuID:
 *      SInt16 the ID of the selected menu.
 *    
 *    iMenuItem:
 *      The item that was selected.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNDoFontMenuSelection(
  TXNObject           iTXNObject,
  TXNFontMenuObject   iTXNFontMenuObject,
  SInt16              iMenuID,
  SInt16              iMenuItem)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  TXNPrepareFontMenu()
 *  
 *  Summary:
 *    Prepares a Font menu for display.
 *  
 *  Discussion:
 *    You should call the TXNPrepareFontMenu function just before your
 *    application opens the Font menu for your user. If the text
 *    object’s current selection is a single font, MLTE places a
 *    checkmark next to the menu item for that font.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      The text object that identifies the document with the Font menu
 *      you want to prepare. Pass NULL to display an inactive menu
 *      (dimmed).
 *    
 *    iTXNFontMenuObject:
 *      A Font menu object.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNPrepareFontMenu(
  TXNObject           iTXNObject,               /* can be NULL */
  TXNFontMenuObject   iTXNFontMenuObject)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





/*%if APPLE_ONLY_UNTIL_CARBONLIB_11*/
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Static Text Box                                                                                   */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNDrawUnicodeTextBox()
 *  
 *  Summary:
 *    Draws a Unicode string in the specified rectangle.
 *  
 *  Discussion:
 *    Client is supposed to do an EraseRect if needed. The drawing will
 *    be clipped to the rect unless the client specifies a rotation.
 *    Use kTXNUseVerticalTextMask to display text vertically (no need
 *    to use the kTXNRotateTextMask flag in this case).
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iText:
 *      Ptr to a Unicode string (UTF16 chars).
 *    
 *    iLen:
 *      Number of UniChars in iText (this is not the size of iText).
 *    
 *    ioBox:
 *      On input the text box where the text will be displayed. On
 *      return will be updated to reflect the minimum bounding Rect
 *      that will enclose the text (unless kTXNDontUpdateBoxRectMask is
 *      used).
 *    
 *    iStyle:
 *      Style to use to display the text.
 *    
 *    iOptions:
 *      Can be used to specify non-default behavior.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in Textension 1.1 and later
 */
extern OSStatus 
TXNDrawUnicodeTextBox(
  const UniChar                  iText[],
  UniCharCount                   iLen,
  Rect *                         ioBox,
  ATSUStyle                      iStyle,         /* can be NULL */
  const TXNTextBoxOptionsData *  iOptions)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  TXNDrawCFStringTextBox()
 *  
 *  Summary:
 *    Draws a CFString in the specified rectangle.
 *  
 *  Discussion:
 *    Client is supposed to do an EraseRect if needed. The drawing will
 *    be clipped to the rect unless the client specifies a rotation.
 *    Use kTXNUseVerticalTextMask to display text vertically (no need
 *    to use the kTXNRotateTextMask flag in this case).
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iText:
 *      A CFStringRef (see CFBase.h and CFString.h).
 *    
 *    ioBox:
 *      On input the text box where the text will be displayed. On
 *      return will be updated to reflect the minimum bounding Rect
 *      that will enclose the text (unless kTXNDontUpdateBoxRectMask is
 *      used).
 *    
 *    iStyle:
 *      Style to use to display the text.
 *    
 *    iOptions:
 *      Can be used to specify non-default behavior.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TXNDrawCFStringTextBox(
  CFStringRef                    iText,
  Rect *                         ioBox,
  ATSUStyle                      iStyle,         /* can be NULL */
  const TXNTextBoxOptionsData *  iOptions)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Get Line Info                                                                                     */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNGetLineCount()
 *  
 *  Summary:
 *    Get the total number of lines in the TXNObject.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    oLineTotal:
 *      On return the total number of lines in the object.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in Textension 1.1 and later
 */
extern OSStatus 
TXNGetLineCount(
  TXNObject    iTXNObject,
  ItemCount *  oLineTotal)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  TXNGetLineMetrics()
 *  
 *  Summary:
 *    Get the metrics for the specified line.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iLineNumber:
 *      The line we want the metrics for (0 based).
 *    
 *    oLineWidth:
 *      On return the width of the line (in Fixed format).
 *    
 *    oLineHeight:
 *      On return the height (ascent + descent) of the line (in Fixed
 *      format).
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in Textension 1.1 and later
 */
extern OSStatus 
TXNGetLineMetrics(
  TXNObject   iTXNObject,
  UInt32      iLineNumber,
  Fixed *     oLineWidth,
  Fixed *     oLineHeight)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Count Changes                                                                                     */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNGetChangeCount()
 *  
 *  Summary:
 *    Retrieve number of times document has been changed.
 *  
 *  Discussion:
 *    That is for every committed command (keydown, cut, copy) the
 *    value returned is count of those. This is useful for deciding if 
 *    the Save item in the File menu should be active.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Result:
 *    ItemCount: count of changes.  This is total changes since
 *    document  was created or last saved.  Not count since this
 *    routine was last called or anything like that.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern ItemCount 
TXNGetChangeCount(TXNObject iTXNObject)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNGetActionChangeCount()
 *  
 *  Summary:
 *    Retrieves the number of times the specified action(s) have
 *    occurred.
 *  
 *  Discussion:
 *    Explicit call to TXNClearActionChangeCount is needed when the
 *    counter(s) have to be reset.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iOptions:
 *      Specify the the type of action changes to be include when
 *      retrieving the count.  Choose from the TXNOptions.
 *    
 *    oCount:
 *      The number of counts returned by the function.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in Textension 1.3 and later
 */
extern OSStatus 
TXNGetActionChangeCount(
  TXNObject         iTXNObject,
  TXNCountOptions   iOptions,
  ItemCount *       oCount)                                   AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



/*
 *  TXNClearActionChangeCount()
 *  
 *  Summary:
 *    Reset the specified action counter(s) to zero.
 *  
 *  Discussion:
 *    Use kAllCountMask to reset everything.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iOptions:
 *      Specify the the type of action changes to be include when
 *      resetting the count.  Choose from the TXNOptions.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in Textension 1.3 and later
 */
extern OSStatus 
TXNClearActionChangeCount(
  TXNObject         iTXNObject,
  TXNCountOptions   iOptions)                                 AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



/*%endif*/

/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Set/Get Object Bounds                                                                             */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNSetHIRectBounds()
 *  
 *  Summary:
 *    Sets the text object's view, the destination rectangles or both.
 *  
 *  Discussion:
 *    Either of the input rectangle can be NULL. HIRect provides an
 *    uniform interface to the HIView coordinate system.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.  The bounds for
 *      this text object will be set.
 *    
 *    iViewRect:
 *      A pointer to a HIRect data structure that contains the new
 *      coordinates for the view rectangle. Pass NULL if you don’t want
 *      to change the view rectangle.
 *    
 *    iDestinationRect:
 *      A pointer to a HIRect data structure that contains the new
 *      coordinates for the destination rectangle. Pass NULL if you
 *      don’t want to change the destination rectangle.
 *    
 *    iUpdate:
 *      Pass true if you want the location of the text and scrollbars
 *      to be recalculated and redrawn, otherwise pass false.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
TXNSetHIRectBounds(
  TXNObject       iTXNObject,
  const HIRect *  iViewRect,
  const HIRect *  iDestinationRect,
  Boolean         iUpdate)                                    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  TXNGetHIRect()
 *  
 *  Summary:
 *    Gets one of the text object's bounds based on the specified
 *    TXNRectKey
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject. The specified
 *      bounds for this text object will be returned.
 *    
 *    iTXNRectKey:
 *      The value for the type of rectangle you want the function to
 *      return.
 *    
 *    oRectangle:
 *      On return, a pointer to the HIRect data structure that contains
 *      the coordinates for the requested rectangle. If a rect is not
 *      defined, a pointer to an empty rect will be returned. Note that
 *      only scrollbar rectangle may be undefined for the text object.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TXNGetHIRect(
  TXNObject    iTXNObject,
  TXNRectKey   iTXNRectKey,
  HIRect *     oRectangle)                                    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;




/*
 *  TXNResizeFrame()
 *  
 *  Summary:
 *    Changes the frame's size to match the new width and height.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iWidth:
 *      New width in pixels.
 *    
 *    iHeight:
 *      New height in pixels.
 *    
 *    iTXNFrameID:
 *      Specifies the frame to move.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNResizeFrame(
  TXNObject    iTXNObject,
  UInt32       iWidth,
  UInt32       iHeight,
  TXNFrameID   iTXNFrameID)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNSetFrameBounds()
 *  
 *  Summary:
 *    Changes the frame's bounds to match the Rect.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iTop:
 *      Top of the bounds.
 *    
 *    iLeft:
 *      Left of the bounds.
 *    
 *    iBottom:
 *      Bottom of the bounds.
 *    
 *    iRight:
 *      Right of the bounds.
 *    
 *    iTXNFrameID:
 *      Specifies the frame to move.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNSetFrameBounds(
  TXNObject    iTXNObject,
  SInt32       iTop,
  SInt32       iLeft,
  SInt32       iBottom,
  SInt32       iRight,
  TXNFrameID   iTXNFrameID)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNGetViewRect()
 *  
 *  Summary:
 *    Get the rectangle describing the current view into the document.
 *    The coordinates of this rectangle will be local to the the window.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    oViewRect:
 *      The requested view rectangle.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNGetViewRect(
  TXNObject   iTXNObject,
  Rect *      oViewRect)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;






/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Layout Calculation                                                                                */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNRecalcTextLayout()
 *  
 *  Summary:
 *    Recalculates the text layout based on the new View and
 *    Destination rectangles.
 *  
 *  Discussion:
 *    Call this if you called TXNSetRectBounds with the iUpdate
 *    parameter set to false. It will also recalcuate where the
 *    scrollbars, if any, should be placed. Finally an update event
 *    will be generated so that the TXNObject is redrawn.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
TXNRecalcTextLayout(TXNObject iTXNObject)                     AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Scrolling                                                                                         */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNScroll()
 *  
 *  Discussion:
 *    TXNScroll scrolls the text within a view rectangle of the
 *    specified object by the designated number of units.  For example,
 *    you might want to scroll the text in an object in response to
 *    user input in a control other than the standard scrollbars that
 *    MLTE supplies.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iVerticalScrollUnit:
 *      Specifies what units the values in ioVerticalDelta are in.  If
 *      iVerticalScrollUnit is equal to kTXNScrollUnitsInPixels the
 *      value is treated as pixels.  If the value is
 *      kTXNScrollUnitsInLines the value is treated as a count of
 *      lines. Note that using this value is the slowest because each
 *      line must be measured before it scrolls.  Finally if
 *      kTXNScrollUnitsInViewRects the value is treated as the height
 *      of the current viewRect.
 *    
 *    iHorizontalScrollUnit:
 *      Specifies what units the values in iDh are in.  If
 *      iHorizontalScrollUnit is equal to kTXNScrollUnitsInPixels the
 *      value is treated as pixels.  If the value is
 *      kTXNScrollUnitsInLines the value is treated as a count of
 *      lines. Note that using this value for horizontal scrolling
 *      means that 16 pixels will be used to represent a line.  Finally
 *      if kTXNScrollUnitsInViewRects the value is treated as the width
 *      of the current viewRect.
 *    
 *    ioVerticalDelta:
 *      The vertical amount to scroll.  The values in ioVerticalDelta
 *      can be treated as pixels, lines or viewrects.  See the
 *      discussion of the TXNScrollUnit parameters for more information
 *      for this.  On return this will contain the number of pixels
 *      actually scrolled in the vertical direction. A positive value
 *      moves the text down.
 *    
 *    ioHorizontalDelta:
 *      The horizontal amount to scroll. The values in
 *      ioHorizontalDelta can specify a scroll amount that is pixels,
 *      lines or view rects.  Set TXNScrollUnit discussion for more
 *      information. On return this will contain the number of pixels
 *      actually scrolled in the horizontal direction. A positive value
 *      moves the text to the right.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   in Textension not yet available
 */
extern OSStatus 
TXNScroll(
  TXNObject       iTXNObject,
  TXNScrollUnit   iVerticalScrollUnit,
  TXNScrollUnit   iHorizontalScrollUnit,
  SInt32 *        ioVerticalDelta,
  SInt32 *        ioHorizontalDelta)                          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




/*
 *  TXNRegisterScrollInfoProc()
 *  
 *  Discussion:
 *    If your application is drawing and handling its own scrolling
 *    widgets use this function to register a TXNScrollInfoUPP.  If you
 *    register a TXNScrollInfoUPP it will be called every time MLTE
 *    would normally update the values and maximum values of an MLTE
 *    scrollbar. For example when the user types the return key to add
 *    a new line at the end of their text MLTE will calculate a new
 *    maximum value.  If you have registered a TXNScrollInfoUPP it will
 *    be called with this nex maximum value. To turn off the callbacks
 *    call TXNRegisterScrollInfoProc with a value of NULL for the
 *    iTXNScrollInfoUPP.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iTXNScrollInfoUPP:
 *      A universal procedure pointer.
 *    
 *    iRefCon:
 *      A refcon that is passed to the callback.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   in Textension not yet available
 */
extern void 
TXNRegisterScrollInfoProc(
  TXNObject          iTXNObject,
  TXNScrollInfoUPP   iTXNScrollInfoUPP,
  SInt32             iRefCon)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




/*
 *  TXNSetScrollbarState()
 *  
 *  Summary:
 *    Sets the state of the scrollbars
 *  
 *  Discussion:
 *    This replaces existing API TXNActivate, which was confusing to
 *    many developers, since it only activates/inactivates the
 *    scrollbar.  This is useful for activating scrollbar(s) even when
 *    the object does not have focus.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iActiveState:
 *      Boolean: if true, scrollbars will be active even if the object
 *      does not have the keyboard focus.  If false, scrollbars are
 *      synched with active state
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TXNSetScrollbarState(
  TXNObject           iTXNObject,
  TXNScrollBarState   iActiveState)                           AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;






/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Offset/Point Conversion                                                                           */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNHIPointToOffset()
 *  
 *  Summary:
 *    Gets the coordinates of the point that corresponds to a specified
 *    offset in a text object.
 *  
 *  Discussion:
 *    The coordinates of the point are in the coordinate system of the
 *    window or view owning the text object.  Note that the owner of
 *    the a text object is a view only in the case when the object is
 *    in a HITextView.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject. The text object
 *      for which you want to obtain an offset value.
 *    
 *    iHIPoint:
 *      A pointer to an HIPoint.
 *    
 *    oOffset:
 *      On return, a pointer to the offset that corresponds to the
 *      value of the iHIPoint parameter.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TXNHIPointToOffset(
  TXNObject        iTXNObject,
  const HIPoint *  iHIPoint,
  TXNOffset *      oOffset)                                   AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  TXNOffsetToHIPoint()
 *  
 *  Summary:
 *    Gets the coordinates of the point that corresponds to a specified
 *    offset in a text object.
 *  
 *  Discussion:
 *    The coordinates of the point are in the coordinate system of the
 *    window or view owning the text object.  Note that the owner of
 *    the a text object is a view only in the case when the object is
 *    in a HITextView.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject. The text object
 *      for which you want to obtain the coordinates of a point.
 *    
 *    iOffset:
 *      A text offset value.
 *    
 *    oHIPoint:
 *      On return, a pointer to the point that corresponds to the value
 *      of the iOffset parameter.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TXNOffsetToHIPoint(
  TXNObject   iTXNObject,
  TXNOffset   iOffset,
  HIPoint *   oHIPoint)                                       AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • Drag and Drop                                                                                     */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
 *  TXNDragTracker()
 *  
 *  Summary:
 *    If you ask that Drag handling procs not be installed.  Call this
 *    when your drag tracker is called and you want Textension to take
 *    over.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNNewObject.
 *    
 *    iTXNFrameID:
 *      TXNFrameID obtained from TXNNewObject.
 *    
 *    iMessage:
 *      Drag message obtained from Drag Manager.
 *    
 *    iWindow:
 *      WindowRef obtained from Drag Manager.
 *    
 *    iDragReference:
 *      DragReference obtained from Drag Manager.
 *    
 *    iDifferentObjectSameWindow:
 *      Pass true if the drag is still in the same window that it
 *      started in. False if the drag has moved into a different window.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSErr 
TXNDragTracker(
  TXNObject             iTXNObject,
  TXNFrameID            iTXNFrameID,
  DragTrackingMessage   iMessage,
  WindowRef             iWindow,
  DragReference         iDragReference,
  Boolean               iDifferentObjectSameWindow)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNDragReceiver()
 *  
 *  Summary:
 *    If you ask that Drag handling procs not be installed.  Call this
 *    when your drag receiver is called and you want Textension to take
 *    over.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNNewObject.
 *    
 *    iTXNFrameID:
 *      TXNFrameID obtained from TXNNewObject.
 *    
 *    iWindow:
 *      WindowRef obtained from Drag Manager.
 *    
 *    iDragReference:
 *      DragReference obtained from Drag Manager.
 *    
 *    iDifferentObjectSameWindow:
 *      Pass true if the drag is still in the same window that it
 *      started in. False if the drag has moved into a different window.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSErr 
TXNDragReceiver(
  TXNObject       iTXNObject,
  TXNFrameID      iTXNFrameID,
  WindowRef       iWindow,
  DragReference   iDragReference,
  Boolean         iDifferentObjectSameWindow)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;






/* **************************************************************************************************** */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*                                  • HITEXTVIEW APIs •                                                 */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/* **************************************************************************************************** */
/*==============================================================================*/
/* HITextView is a MLTE view that can be embedded in the HIView hierarchy. The  */
/* view can be embedded in an HIScrollView if scroll bars are desired and can   */
/* be used in a composited window. On creation, a TXNObject is created to back  */
/* the view. You can extract the TXNObject at any time and use a subset of the  */
/* MLTE API with that object as an argument.                                    */
/*==============================================================================*/
/* The HIObject class ID for the HITextView class. */
#define kHITextViewClassID              CFSTR("com.apple.HITextView")
/* ControlKind*/
enum {
  kControlKindHITextView        = 'hitx'
};


/*
 *  HITextViewCreate()
 *  
 *  Summary:
 *    Creates a text view. The new view is initially invisible.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inBoundsRect:
 *      The bounding box of the view. If NULL, the bounds of the view
 *      will be initialized to 0.
 *    
 *    inOptions:
 *      There are currently no options. This must be 0.
 *    
 *    inTXNFrameOptions:
 *      Any frame options desired for the TXN object creation.
 *    
 *    outTextView:
 *      On exit, contains the new view.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HITextViewCreate(
  const HIRect *    inBoundsRect,            /* can be NULL */
  OptionBits        inOptions,
  TXNFrameOptions   inTXNFrameOptions,
  HIViewRef *       outTextView)                              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  HITextViewGetTXNObject()
 *  
 *  Summary:
 *    Obtains the TXNObject that backs the text view.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inTextView:
 *      The text view that contains the TXNObject you wish to retrieve.
 *  
 *  Result:
 *    The TXNObject backing the given view.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern TXNObject 
HITextViewGetTXNObject(HIViewRef inTextView)                  AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;




/* **************************************************************************************************** */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*                                  •  DEPRECATED •                                                     */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/* **************************************************************************************************** */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • DEPRECATED CONSTANTS                                                                              */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/

typedef FourCharCode                    TXTNTag;
typedef OSStatus                        TXNErrors;
typedef void *                          TXNObjectRefcon;
#define   kTXNFontMenuRefKey    CFSTR("FontMenuRef")
/* use kTXNFontMenuObjectKey*/
struct TXNLongRect {
  SInt32              top;
  SInt32              left;
  SInt32              bottom;
  SInt32              right;
};
typedef struct TXNLongRect              TXNLongRect;
/*
    • Frame Types                                                                                       
    Useful for TXNNewObject API.  Only kTXNTextEditStyleFrameType is supported at this time.                                                                        *|
*/
typedef UInt32 TXNFrameType;
enum {
  kTXNTextEditStyleFrameType    = 1,
  kTXNPageFrameType             = 2,    /* not supported*/
  kTXNMultipleFrameType         = 3     /* not supported*/
};


/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • DEPRECATED APIs 10.2 and later                                                                    */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
  *************************************************************************************************                         
   Set the rectangle describing the current view into the document. This
   will change how much text is viewable.  Not where a line of text wraps.
   That is controlled by TXNSetFrameBoundsSize.
   Input:
        iTXNObject :    opaque Textension structure.
        
        iViewRect:      Rect of the view
         
        Deprecated. Please use TXNSetFrameBounds or TXNSetRectBounds API !!
  *************************************************************************************************
*/
/*
 *  TXNSetViewRect()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in Textension 1.3 and later
 */
extern void 
TXNSetViewRect(
  TXNObject     iTXNObject,
  const Rect *  iViewRect)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*  • DEPRECATED APIs 10.3 and later                                                                    */
/*——————————————————————————————————————————————————————————————————————————————————————————————————————*/
/*
  *****************************************************************************************************
   Allocates a new frame (i.e. new is called to allocate a TXNObject) and returns a pointer to the object 
   in the newDoc parameter.
   Input:
        
    iFileSpec:  If NULL you start with an empty document.  If not NULL, the file is read to obtain the 
                document contents  after the object is successfully allocated.   
                
    iWindow:    Required.  The window in which the document is going to be  displayed.  If a fileSpec is provided
                during creation, the filename is going to be used as the window title.  If iWindow is NULL, 
                TXNAttachObjectToWindow needs to be called after creation.
                
    iFrame:     If text-area does not fill the entire window.  This specifies the area to fill.  Can be NULL.  
                In  which case, the window’s portRect is used as the frame.
                                
    iFrameOptions:  Specify the options to be supported by this frame.  The available options are support 
                    for cutting and pasting  movies and sound, handle scrollbars and handle grow box in  the 
                    frame.
    iFrameType:     Specify the type of frame to be used.  In MLTE version 1.1 and earlier, only 
                    kTXNTextEditStyleFrameType is supported.
   
    iFileType:  Specify the primary file type.  If you  use  kTextensionTextFile files will be saved 
                in a private format (see xxx).  If you  want saved files to be plain text files you should 
                specify 'TEXT' here. If you specify 'TEXT' here you can use the frameOptions parameter to 
                specify  whether the TEXT files should be saved  with 'MPSR' resources or 'styl' resources.  
                These are resources which contain style information for a  file, and they  both have there 
                own limitations.  If you use 'styl' resources to save style info your documents can have as 
                many styles as you like however tabs will not be saved.  If you use 'MPSR' resources only the 
                first style in the document  will be saved (you as client are expected to apply all style  
                changes to the entire document).  If you  truly want  rich documents which can potentially 
                contain graphics and sound you should specify kTextensionTextFileOutput.  If you want a plain 
                text editor like SimpleText specify that style information by saved via ‘styl’ resources.  
                If you want files similar to those output by CW IDE, BBEdit, and MPW specify that style 
                information be saved in a ‘MPSR’ resource.
   
   Output:
    
    OSStatus:   function  result.  If anything goes wrong the error is returned.  Success must be complete.  
                That is if everything  works, but there is a failure reading a specified file the  object 
                is freed.
    oTXNObject:     Pointer to the opaque datastructure allocated by the function.  Most of the subsequent 
                    functions require that such a pointer be passed in.
                
    oTXNFrameID:    Unique ID for the frame. <Note in version 1.0 this value is always set to 0>
    iRefCon:        Caller can set this to any value.  It is retained by the
                    TXNNewObject which can later be asked to return it.
  **************************************************************************************************************
*/
/*
 *  TXNNewObject()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNNewObject(
  const FSSpec *                 iFileSpec,                /* can be NULL */
  WindowRef                      iWindow,
  const Rect *                   iFrame,                   /* can be NULL */
  TXNFrameOptions                iFrameOptions,
  TXNFrameType                   iFrameType,
  TXNFileType                    iFileType,
  TXNPermanentTextEncodingType   iPermanentEncoding,
  TXNObject *                    oTXNObject,
  TXNFrameID *                   oTXNFrameID,
  TXNObjectRefcon                iRefCon)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNTerminateTextension()
 *  
 *  Summary:
 *    Close the Textension library.  It is necessary to call this
 *    function so that Textension can correctly close down any TSM
 *    connections and do other clean up.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNTerminateTextension(void)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
  *********************************************************************************************************
    Replace the specified range with the contents of the specified file.  The data fork of the file 
    must be opened by the caller.  Functional in NoUserIO mode.
    Input:
        iTXNObject:     opaque TXNObject obtained from  TXNNewObject
        fileSpec:   HFS file reference obtained when file is opened.
        fileType:   files type.
        iFileLength: The length of data in the file that should be considered data.  This
                     parameter is available to enable callers to embed text inside their
                     own private data structures.  Note that if the data is in the Textension(txtn)
                     format this parameter is ignored since length, etc. information is
                     part of the format. Further note that if you you just want Textension
                     to read a file and you are not interested in embedding you can just pass
                     kTXNEndOffset(0x7FFFFFFF), and Textension will use the file manager to
                     determine the files length.
        iStartOffset:   start position at which to insert the file into the document.
        iEndOffset:     end position of range being replaced by the file.
    Output:
        OSStatus:   File manager error or noErr.
  ***********************************************************************************************************
*/
/*
 *  TXNSetDataFromFile()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNSetDataFromFile(
  TXNObject   iTXNObject,
  SInt16      iFileRefNum,
  OSType      iFileType,
  ByteCount   iFileLength,
  TXNOffset   iStartOffset,
  TXNOffset   iEndOffset)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
  ***********************************************************************************************************
    Convert the Textension private scrap to the public clipboard.  This should be called on suspend 
    events and before the application displays a dialog that might support cut and paste.  Or more 
    generally, whenever someone other than the Textension Shared Library needs access to the scrap data.
    This is no-op'ed out in OS X.
    Output:
         OSStatus:  Function result.  Memory Manager errors, Scrap Manager errors, noErr.
  ************************************************************************************************************
*/
/*
 *  TXNConvertToPublicScrap()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNConvertToPublicScrap(void)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
  ***********************************************************************************************************
    Convert the  public clipboard to our private scrap .  This should be called on resume 
    events and after an application has modified the scrap. Before doing work we check the validity of the public 
    scrap (date modification and type).  This is no longer needed in 10.2 and later.  Calling TXNPaste will
    automatically handle conversion from public scrap.
    Output:
         OSStatus:  Function result.  Memory Manager errors, Scrap Manager errors, noErr.
  ************************************************************************************************************  
*/
/*
 *  TXNConvertFromPublicScrap()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNConvertFromPublicScrap(void)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
  *************************************************************************************************
    Redraw the TXNObject including any scrollbars associated with the text frame.  Call this function
    in response to an update event for a window that contains multiple TXNObjects or some other graphic
    element.  The caller is responsible for calling BeginUpdate/EndUpdate in response to the update
    event.
    Input:
        iTXNObject:     opaque TXNObject to draw
        iDrawPort:  Can be NULL. If NULL the port is drawn to the port currently attached to the 
                    iTXNObject.  If not NULL drawing goes to the iDrawPort.  If drawing is done
                    to the iDrawPort selection is not updated.  This works this way so that it
                    is possible to Draw a TXNObject to a static port (i.e. print the thing without 
                    reflowing the text to match the paper size which is what TXNPrint does) 
                    and not have a line drawn where the selection would be.  If you pass an 
                    iDrawPort to an active TXNObject (i.e. editable) the selection will not be updated. In 
                    this case the selection will behave oddly until text is typed which will serve
                    to realign the selection.  Bottom-line don't pass a port in unless you want
                    static text (printed or non-editable)
  *************************************************************************************************
*/
/*
 *  TXNDraw()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern void 
TXNDraw(
  TXNObject   iTXNObject,
  GWorldPtr   iDrawPort)        /* can be NULL */             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
  ****************************************************************************************************************
    TXNAttachObjectToWindow
    If a TXNObject was initialized with a NULL window pointer use this function to attach a window
    to that object.  In version 1.0 of Textension attaching a TXNObject to more than one window
    is not supported.  Note that if a CGContextRef was passed to the TXNObject previously thru the
    API TXNSetTXNObjectControls, that CGContextRef will be ignored.  The CGContextRef associated with
    the iWindow will be used instead.  You may revert back to the previous CGContextRef by calling the
    API TXNSetTXNObjectControls with the desired CGContextRef again after calling TXNAttachObjectToWindow.
    
    Input:
        iTXNObject:         opaque TXNObject obtained from TXNNewObject.
        iWindow:            GWorldPtr that the object should be attached to
        iIsActualWindow:    Let the library know if the GWorldPtr is actually
                            a WindowRef or actually a GWorldPtr.  This is important
                            if the client is taking advantage of the editing packages
                            scrollbar support.
    Output:
        OSStatus:           function result.  paramErrs. 
  ****************************************************************************************************************
*/
/*
 *  TXNAttachObjectToWindow()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNAttachObjectToWindow(
  TXNObject   iTXNObject,
  GWorldPtr   iWindow,
  Boolean     iIsActualWindow)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
  ****************************************************************************************************************
    TXNIsObjectAttachedToWindow
    A utility function that allows a caller to check a TXNObject to see if it is attached
    to a window.
    Input:
        iTXNObject:         opaque TXNObject obtained from TXNNewObject.
    Output:
        Boolean:            function result.  True is object is attached.
                            False if TXNObject is not attached.
  ****************************************************************************************************************
*/
/*
 *  TXNIsObjectAttachedToWindow()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern Boolean 
TXNIsObjectAttachedToWindow(TXNObject iTXNObject)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  TXNIsObjectAttachedToSpecificWindow()
 *  
 *  Summary:
 *    Determines whether the given object is attached to the given
 *    window.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNNewObject.
 *    
 *    iWindow:
 *      The window to check attachment against.
 *    
 *    oAttached:
 *      true if the object is attached to the given window, false
 *      otherwise.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in Textension 1.2 and later
 */
extern OSStatus 
TXNIsObjectAttachedToSpecificWindow(
  TXNObject   iTXNObject,
  WindowRef   iWindow,
  Boolean *   oAttached)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  TXNSetRectBounds()
 *  
 *  Summary:
 *    Set the View rectangle and or the Destination rectangle.
 *  
 *  Discussion:
 *    The View rectangle controls the text you see.  The Destination
 *    rectangle controls how text is laid out.  The Scrollbar is drawn
 *    inside the View rectangle. You only need to pass in pointers for
 *    the rectangles you want to set.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNNewObject.
 *    
 *    iViewRect:
 *      The new view rectangle.  If you do not want to change the view
 *      rectangle pass NULL.
 *    
 *    iDestinationRect:
 *      The new destination rectangle.  Pass NULL if you don't want to
 *      change the destination retangle.
 *    
 *    iUpdate:
 *      If you would like the the text and where the scrollbars are
 *      placed recalculated and redrawn pass true.  If you prefer to
 *      wait on this pass false.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
TXNSetRectBounds(
  TXNObject            iTXNObject,
  const Rect *         iViewRect,              /* can be NULL */
  const TXNLongRect *  iDestinationRect,       /* can be NULL */
  Boolean              iUpdate)                               AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


/*
 *  TXNGetRectBounds()
 *  
 *  Summary:
 *    Get the values for the current View rectangle, Destination
 *    rectangle and Text rectangle.
 *  
 *  Discussion:
 *    You only need to pass in pointers for the rectangles you're
 *    interested in.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNNewObject.
 *    
 *    oViewRect:
 *      The current view rectangle
 *    
 *    oDestinationRect:
 *      The current destination rectangle
 *    
 *    oTextRect:
 *      The smallest rectangle needed to contain the current text. 
 *      This rectangle is calculated by walking the lines of text and
 *      measuring each line.  So this can be expensive.  The width of
 *      this rectangle will be the width of the longest line in the
 *      text.
 *  
 *  Result:
 *    An operating system status code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
TXNGetRectBounds(
  TXNObject      iTXNObject,
  Rect *         oViewRect,              /* can be NULL */
  TXNLongRect *  oDestinationRect,       /* can be NULL */
  TXNLongRect *  oTextRect)              /* can be NULL */    AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;



/*
 *  TXNActivate()
 *  
 *  Summary:
 *    Make the TXNObject object active in the sense that it can be
 *    scrolled if it has scrollbars. If the TXNScrollBarState parameter
 *    is true than the scrollbars will be active even when the
 *    TXNObject is not focused (i.e. insertion point not active).  See
 *    the equivalent TXNSetScrollbarState.
 *  
 *  Discussion:
 *    This function should be used if you have multiple TXNObjects in a
 *    window, and you want them all to be scrollable even though only
 *    one at a time can have the keyboard focus.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque TXNObject obtained from TXNCreateObject.
 *    
 *    iTXNFrameID:
 *      TXNFrameID obtained from TXNCreateObject.
 *    
 *    iActiveState:
 *      Boolean if true Scrollbars active even though TXNObject does
 *      not have the keyboard focus. if false scrollbars are synced
 *      with active state (i.e. a focused object has an active
 *      insertion point or selection and active scrollbars. An
 *      unfocused object has inactive selection (grayed or framed
 *      selection) and inactive scrollbars.  The latter state is the
 *      default and usually the one you use if you have one TXNObject
 *      in a window.
 *  
 *  Result:
 *    A result code indicating success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */
extern OSStatus 
TXNActivate(
  TXNObject           iTXNObject,
  TXNFrameID          iTXNFrameID,
  TXNScrollBarState   iActiveState)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
  ****************************************************************************************
    TXNPointToOffset
        
    
    Input:
        iTXNObject: An opaque TXNObject obtained from TXNNewObject.
        iPoint:     a point (in local coord.)
    Output:
        TXNOffset   :   Offset corresponding to the point
        OSStatus:   Memory, out of bounds errors.(if the point is out of the ViewRect)
  ****************************************************************************************
*/
/*
 *  TXNPointToOffset()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in Textension 1.1 and later
 */
extern OSStatus 
TXNPointToOffset(
  TXNObject    iTXNObject,
  Point        iPoint,
  TXNOffset *  oOffset)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
  ****************************************************************************************
    TXNOffsetToPoint
        
    
    Input:
        iTXNObject: An opaque TXNObject obtained from TXNNewObject.
        iOffset:    an offset
    Output:
        Point   :   Point corresponding to the offset iOffset.
        OSStatus:   Memory, out of bounds errors.
  ****************************************************************************************
*/
/*
 *  TXNOffsetToPoint()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in Textension 1.1 and later
 */
extern OSStatus 
TXNOffsetToPoint(
  TXNObject   iTXNObject,
  TXNOffset   iOffset,
  Point *     oPoint)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  TXNTSMCheck()
 *  
 *  Summary:
 *    Call this when WaitNextEvent returns false or there is no active
 *    TSMObject . The TXNObject parameter can be NULL which allows a
 *    client to call this function at any time.  This is necessary to
 *    insure input methods enough time to be reasonably responsive.
 *  
 *  Parameters:
 *    
 *    iTXNObject:
 *      Opaque struct obtained from TXNNewObject.
 *    
 *    ioEvent:
 *      The event record.  Usually a NULL event.  If the event is not
 *      an NULL event on entry, and an input method consumes the event
 *      the event should return as a NULL event.
 *  
 *  Result:
 *    Boolean: True if TSM handled this event.  False if TSM did not
 *    handle this event.
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in Textension 1.0 and later
 */




#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __MACTEXTEDITOR__ */

