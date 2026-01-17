/*
     File:       HIToolbox/Icons.h
 
     Contains:   Icon Utilities and Icon Services Interfaces.
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 1990-2001 by Apple Computer, Inc. All rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __ICONS__
#define __ICONS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __QUICKDRAW__
#include <QD/Quickdraw.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif

#ifndef __CODEFRAGMENTS__
#include <CarbonCore/CodeFragments.h>
#endif

#ifndef __COREGRAPHICS__
#include <CoreGraphics/CoreGraphics.h>
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

/* The following are icons for which there are both icon suites and SICNs. */
/* Avoid using icon resources if possible. Use IconServices instead. */
enum {
  kGenericDocumentIconResource  = -4000,
  kGenericStationeryIconResource = -3985,
  kGenericEditionFileIconResource = -3989,
  kGenericApplicationIconResource = -3996,
  kGenericDeskAccessoryIconResource = -3991,
  kGenericFolderIconResource    = -3999,
  kPrivateFolderIconResource    = -3994,
  kFloppyIconResource           = -3998,
  kTrashIconResource            = -3993,
  kGenericRAMDiskIconResource   = -3988,
  kGenericCDROMIconResource     = -3987
};

/* The following are icons for which there are SICNs only. */
/* Avoid using icon resources if possible. Use IconServices instead. */
enum {
  kDesktopIconResource          = -3992,
  kOpenFolderIconResource       = -3997,
  kGenericHardDiskIconResource  = -3995,
  kGenericFileServerIconResource = -3972,
  kGenericSuitcaseIconResource  = -3970,
  kGenericMoverObjectIconResource = -3969
};

/* The following are icons for which there are icon suites only. */
/* Avoid using icon resources if possible. Use IconServices instead. */
enum {
  kGenericPreferencesIconResource = -3971,
  kGenericQueryDocumentIconResource = -16506,
  kGenericExtensionIconResource = -16415,
  kSystemFolderIconResource     = -3983,
  kHelpIconResource             = -20271,
  kAppleMenuFolderIconResource  = -3982
};

/* Obsolete. Use named constants defined above. */
enum {
  genericDocumentIconResource   = kGenericDocumentIconResource,
  genericStationeryIconResource = kGenericStationeryIconResource,
  genericEditionFileIconResource = kGenericEditionFileIconResource,
  genericApplicationIconResource = kGenericApplicationIconResource,
  genericDeskAccessoryIconResource = kGenericDeskAccessoryIconResource,
  genericFolderIconResource     = kGenericFolderIconResource,
  privateFolderIconResource     = kPrivateFolderIconResource,
  floppyIconResource            = kFloppyIconResource,
  trashIconResource             = kTrashIconResource,
  genericRAMDiskIconResource    = kGenericRAMDiskIconResource,
  genericCDROMIconResource      = kGenericCDROMIconResource,
  desktopIconResource           = kDesktopIconResource,
  openFolderIconResource        = kOpenFolderIconResource,
  genericHardDiskIconResource   = kGenericHardDiskIconResource,
  genericFileServerIconResource = kGenericFileServerIconResource,
  genericSuitcaseIconResource   = kGenericSuitcaseIconResource,
  genericMoverObjectIconResource = kGenericMoverObjectIconResource,
  genericPreferencesIconResource = kGenericPreferencesIconResource,
  genericQueryDocumentIconResource = kGenericQueryDocumentIconResource,
  genericExtensionIconResource  = kGenericExtensionIconResource,
  systemFolderIconResource      = kSystemFolderIconResource,
  appleMenuFolderIconResource   = kAppleMenuFolderIconResource
};

/* Avoid using icon resources if possible. Use IconServices instead. */
enum {
  kStartupFolderIconResource    = -3981,
  kOwnedFolderIconResource      = -3980,
  kDropFolderIconResource       = -3979,
  kSharedFolderIconResource     = -3978,
  kMountedFolderIconResource    = -3977,
  kControlPanelFolderIconResource = -3976,
  kPrintMonitorFolderIconResource = -3975,
  kPreferencesFolderIconResource = -3974,
  kExtensionsFolderIconResource = -3973,
  kFontsFolderIconResource      = -3968,
  kFullTrashIconResource        = -3984
};

/* Obsolete. Use named constants defined above. */
enum {
  startupFolderIconResource     = kStartupFolderIconResource,
  ownedFolderIconResource       = kOwnedFolderIconResource,
  dropFolderIconResource        = kDropFolderIconResource,
  sharedFolderIconResource      = kSharedFolderIconResource,
  mountedFolderIconResource     = kMountedFolderIconResource,
  controlPanelFolderIconResource = kControlPanelFolderIconResource,
  printMonitorFolderIconResource = kPrintMonitorFolderIconResource,
  preferencesFolderIconResource = kPreferencesFolderIconResource,
  extensionsFolderIconResource  = kExtensionsFolderIconResource,
  fontsFolderIconResource       = kFontsFolderIconResource,
  fullTrashIconResource         = kFullTrashIconResource
};

/* The following icon types can only be used as an icon element */
/* inside a 'icns' icon family */
enum {
  kThumbnail32BitData           = 'it32',
  kThumbnail8BitMask            = 't8mk'
};

enum {
  kHuge1BitMask                 = 'ich#',
  kHuge4BitData                 = 'ich4',
  kHuge8BitData                 = 'ich8',
  kHuge32BitData                = 'ih32',
  kHuge8BitMask                 = 'h8mk'
};

/* The following icon types can be used as a resource type */
/* or as an icon element type inside a 'icns' icon family */
enum {
  kLarge1BitMask                = 'ICN#',
  kLarge4BitData                = 'icl4',
  kLarge8BitData                = 'icl8',
  kLarge32BitData               = 'il32',
  kLarge8BitMask                = 'l8mk',
  kSmall1BitMask                = 'ics#',
  kSmall4BitData                = 'ics4',
  kSmall8BitData                = 'ics8',
  kSmall32BitData               = 'is32',
  kSmall8BitMask                = 's8mk',
  kMini1BitMask                 = 'icm#',
  kMini4BitData                 = 'icm4',
  kMini8BitData                 = 'icm8'
};

/*  Icon Variants */
/* These can be used as an element of an 'icns' icon family */
/* or as a parameter to GetIconRefVariant */
enum {
  kTileIconVariant              = 'tile',
  kRolloverIconVariant          = 'over',
  kDropIconVariant              = 'drop',
  kOpenIconVariant              = 'open',
  kOpenDropIconVariant          = 'odrp'
};

/* Obsolete. Use names defined above. */
enum {
  large1BitMask                 = kLarge1BitMask,
  large4BitData                 = kLarge4BitData,
  large8BitData                 = kLarge8BitData,
  small1BitMask                 = kSmall1BitMask,
  small4BitData                 = kSmall4BitData,
  small8BitData                 = kSmall8BitData,
  mini1BitMask                  = kMini1BitMask,
  mini4BitData                  = kMini4BitData,
  mini8BitData                  = kMini8BitData
};

/* Alignment type values. */
enum {
  kAlignNone                    = 0x00,
  kAlignVerticalCenter          = 0x01,
  kAlignTop                     = 0x02,
  kAlignBottom                  = 0x03,
  kAlignHorizontalCenter        = 0x04,
  kAlignAbsoluteCenter          = kAlignVerticalCenter | kAlignHorizontalCenter,
  kAlignCenterTop               = kAlignTop | kAlignHorizontalCenter,
  kAlignCenterBottom            = kAlignBottom | kAlignHorizontalCenter,
  kAlignLeft                    = 0x08,
  kAlignCenterLeft              = kAlignVerticalCenter | kAlignLeft,
  kAlignTopLeft                 = kAlignTop | kAlignLeft,
  kAlignBottomLeft              = kAlignBottom | kAlignLeft,
  kAlignRight                   = 0x0C,
  kAlignCenterRight             = kAlignVerticalCenter | kAlignRight,
  kAlignTopRight                = kAlignTop | kAlignRight,
  kAlignBottomRight             = kAlignBottom | kAlignRight
};

/* Obsolete. Use names defined above. */
enum {
  atNone                        = kAlignNone,
  atVerticalCenter              = kAlignVerticalCenter,
  atTop                         = kAlignTop,
  atBottom                      = kAlignBottom,
  atHorizontalCenter            = kAlignHorizontalCenter,
  atAbsoluteCenter              = kAlignAbsoluteCenter,
  atCenterTop                   = kAlignCenterTop,
  atCenterBottom                = kAlignCenterBottom,
  atLeft                        = kAlignLeft,
  atCenterLeft                  = kAlignCenterLeft,
  atTopLeft                     = kAlignTopLeft,
  atBottomLeft                  = kAlignBottomLeft,
  atRight                       = kAlignRight,
  atCenterRight                 = kAlignCenterRight,
  atTopRight                    = kAlignTopRight,
  atBottomRight                 = kAlignBottomRight
};

typedef SInt16                          IconAlignmentType;
/* Transform type values. */
enum {
  kTransformNone                = 0x00,
  kTransformDisabled            = 0x01,
  kTransformOffline             = 0x02,
  kTransformOpen                = 0x03,
  kTransformLabel1              = 0x0100,
  kTransformLabel2              = 0x0200,
  kTransformLabel3              = 0x0300,
  kTransformLabel4              = 0x0400,
  kTransformLabel5              = 0x0500,
  kTransformLabel6              = 0x0600,
  kTransformLabel7              = 0x0700,
  kTransformSelected            = 0x4000,
  kTransformSelectedDisabled    = kTransformSelected | kTransformDisabled,
  kTransformSelectedOffline     = kTransformSelected | kTransformOffline,
  kTransformSelectedOpen        = kTransformSelected | kTransformOpen
};

/* Obsolete. Use names defined above. */
enum {
  ttNone                        = kTransformNone,
  ttDisabled                    = kTransformDisabled,
  ttOffline                     = kTransformOffline,
  ttOpen                        = kTransformOpen,
  ttLabel1                      = kTransformLabel1,
  ttLabel2                      = kTransformLabel2,
  ttLabel3                      = kTransformLabel3,
  ttLabel4                      = kTransformLabel4,
  ttLabel5                      = kTransformLabel5,
  ttLabel6                      = kTransformLabel6,
  ttLabel7                      = kTransformLabel7,
  ttSelected                    = kTransformSelected,
  ttSelectedDisabled            = kTransformSelectedDisabled,
  ttSelectedOffline             = kTransformSelectedOffline,
  ttSelectedOpen                = kTransformSelectedOpen
};

typedef SInt16                          IconTransformType;
/* Selector mask values. */
enum {
  kSelectorLarge1Bit            = 0x00000001,
  kSelectorLarge4Bit            = 0x00000002,
  kSelectorLarge8Bit            = 0x00000004,
  kSelectorLarge32Bit           = 0x00000008,
  kSelectorLarge8BitMask        = 0x00000010,
  kSelectorSmall1Bit            = 0x00000100,
  kSelectorSmall4Bit            = 0x00000200,
  kSelectorSmall8Bit            = 0x00000400,
  kSelectorSmall32Bit           = 0x00000800,
  kSelectorSmall8BitMask        = 0x00001000,
  kSelectorMini1Bit             = 0x00010000,
  kSelectorMini4Bit             = 0x00020000,
  kSelectorMini8Bit             = 0x00040000,
  kSelectorHuge1Bit             = 0x01000000,
  kSelectorHuge4Bit             = 0x02000000,
  kSelectorHuge8Bit             = 0x04000000,
  kSelectorHuge32Bit            = 0x08000000,
  kSelectorHuge8BitMask         = 0x10000000,
  kSelectorAllLargeData         = 0x000000FF,
  kSelectorAllSmallData         = 0x0000FF00,
  kSelectorAllMiniData          = 0x00FF0000,
  kSelectorAllHugeData          = (long)0xFF000000,
  kSelectorAll1BitData          = kSelectorLarge1Bit | kSelectorSmall1Bit | kSelectorMini1Bit | kSelectorHuge1Bit,
  kSelectorAll4BitData          = kSelectorLarge4Bit | kSelectorSmall4Bit | kSelectorMini4Bit | kSelectorHuge4Bit,
  kSelectorAll8BitData          = kSelectorLarge8Bit | kSelectorSmall8Bit | kSelectorMini8Bit | kSelectorHuge8Bit,
  kSelectorAll32BitData         = kSelectorLarge32Bit | kSelectorSmall32Bit | kSelectorHuge32Bit,
  kSelectorAllAvailableData     = (long)0xFFFFFFFF
};


/* Obsolete. Use names defined above. */
enum {
  svLarge1Bit                   = kSelectorLarge1Bit,
  svLarge4Bit                   = kSelectorLarge4Bit,
  svLarge8Bit                   = kSelectorLarge8Bit,
  svSmall1Bit                   = kSelectorSmall1Bit,
  svSmall4Bit                   = kSelectorSmall4Bit,
  svSmall8Bit                   = kSelectorSmall8Bit,
  svMini1Bit                    = kSelectorMini1Bit,
  svMini4Bit                    = kSelectorMini4Bit,
  svMini8Bit                    = kSelectorMini8Bit,
  svAllLargeData                = kSelectorAllLargeData,
  svAllSmallData                = kSelectorAllSmallData,
  svAllMiniData                 = kSelectorAllMiniData,
  svAll1BitData                 = kSelectorAll1BitData,
  svAll4BitData                 = kSelectorAll4BitData,
  svAll8BitData                 = kSelectorAll8BitData,
  svAllAvailableData            = kSelectorAllAvailableData
};

typedef UInt32                          IconSelectorValue;
typedef CALLBACK_API( OSErr , IconActionProcPtr )(ResType theType, Handle *theIcon, void *yourDataPtr);
typedef CALLBACK_API( Handle , IconGetterProcPtr )(ResType theType, void *yourDataPtr);
typedef STACK_UPP_TYPE(IconActionProcPtr)                       IconActionUPP;
typedef STACK_UPP_TYPE(IconGetterProcPtr)                       IconGetterUPP;
/*
 *  NewIconActionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern IconActionUPP
NewIconActionUPP(IconActionProcPtr userRoutine);

/*
 *  NewIconGetterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern IconGetterUPP
NewIconGetterUPP(IconGetterProcPtr userRoutine);

/*
 *  DisposeIconActionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeIconActionUPP(IconActionUPP userUPP);

/*
 *  DisposeIconGetterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeIconGetterUPP(IconGetterUPP userUPP);

/*
 *  InvokeIconActionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeIconActionUPP(
  ResType        theType,
  Handle *       theIcon,
  void *         yourDataPtr,
  IconActionUPP  userUPP);

/*
 *  InvokeIconGetterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Handle
InvokeIconGetterUPP(
  ResType        theType,
  void *         yourDataPtr,
  IconGetterUPP  userUPP);

typedef IconGetterProcPtr               IconGetter;
typedef IconActionProcPtr               IconAction;
/* CIconHandle, GetCIcon(), PlotCIcon(), and DisposeCIcon() moved here from Quickdraw.h*/
struct CIcon {
  PixMap              iconPMap;               /*the icon's pixMap*/
  BitMap              iconMask;               /*the icon's mask*/
  BitMap              iconBMap;               /*the icon's bitMap*/
  Handle              iconData;               /*the icon's data*/
  SInt16              iconMaskData[1];        /*icon's mask and BitMap data*/
};
typedef struct CIcon                    CIcon;
typedef CIcon *                         CIconPtr;
typedef CIconPtr *                      CIconHandle;
/*
 *  GetCIcon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern CIconHandle 
GetCIcon(SInt16 iconID);


/*
 *  PlotCIcon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PlotCIcon(
  const Rect *  theRect,
  CIconHandle   theIcon);


/*
 *  DisposeCIcon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
DisposeCIcon(CIconHandle theIcon);



/* GetIcon and PlotIcon moved here from ToolUtils*/
/*
 *  GetIcon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Handle 
GetIcon(SInt16 iconID);


/*
 *  PlotIcon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern void 
PlotIcon(
  const Rect *  theRect,
  Handle        theIcon);




/*
    Note:   IconSuiteRef and IconCacheRef should be an abstract types, 
            but too much source code already relies on them being of type Handle.
*/
typedef Handle                          IconSuiteRef;
typedef Handle                          IconCacheRef;
/* IconRefs are 32-bit values identifying cached icon data. IconRef 0 is invalid.*/
typedef struct OpaqueIconRef*           IconRef;
/*
 *  PlotIconID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
PlotIconID(
  const Rect *        theRect,
  IconAlignmentType   align,
  IconTransformType   transform,
  SInt16              theResID);


/*
 *  NewIconSuite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
NewIconSuite(IconSuiteRef * theIconSuite);


/*
 *  AddIconToSuite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AddIconToSuite(
  Handle         theIconData,
  IconSuiteRef   theSuite,
  ResType        theType);


/*
 *  GetIconFromSuite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetIconFromSuite(
  Handle *       theIconData,
  IconSuiteRef   theSuite,
  ResType        theType);


/*
 *  ForEachIconDo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
ForEachIconDo(
  IconSuiteRef        theSuite,
  IconSelectorValue   selector,
  IconActionUPP       action,
  void *              yourDataPtr);


/*
 *  GetIconSuite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetIconSuite(
  IconSuiteRef *      theIconSuite,
  SInt16              theResID,
  IconSelectorValue   selector);


/*
 *  DisposeIconSuite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DisposeIconSuite(
  IconSuiteRef   theIconSuite,
  Boolean        disposeData);


/*
 *  PlotIconSuite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
PlotIconSuite(
  const Rect *        theRect,
  IconAlignmentType   align,
  IconTransformType   transform,
  IconSuiteRef        theIconSuite);


/*
 *  MakeIconCache()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
MakeIconCache(
  IconCacheRef *  theCache,
  IconGetterUPP   makeIcon,
  void *          yourDataPtr);


/*
 *  LoadIconCache()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
LoadIconCache(
  const Rect *        theRect,
  IconAlignmentType   align,
  IconTransformType   transform,
  IconCacheRef        theIconCache);


/*
 *  PlotIconMethod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
PlotIconMethod(
  const Rect *        theRect,
  IconAlignmentType   align,
  IconTransformType   transform,
  IconGetterUPP       theMethod,
  void *              yourDataPtr);


/*
 *  GetLabel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetLabel(
  SInt16      labelNumber,
  RGBColor *  labelColor,
  Str255      labelString);


/*
 *  PtInIconID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
PtInIconID(
  Point               testPt,
  const Rect *        iconRect,
  IconAlignmentType   align,
  SInt16              iconID);


/*
 *  PtInIconSuite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
PtInIconSuite(
  Point               testPt,
  const Rect *        iconRect,
  IconAlignmentType   align,
  IconSuiteRef        theIconSuite);


/*
 *  PtInIconMethod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
PtInIconMethod(
  Point               testPt,
  const Rect *        iconRect,
  IconAlignmentType   align,
  IconGetterUPP       theMethod,
  void *              yourDataPtr);


/*
 *  RectInIconID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
RectInIconID(
  const Rect *        testRect,
  const Rect *        iconRect,
  IconAlignmentType   align,
  SInt16              iconID);


/*
 *  RectInIconSuite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
RectInIconSuite(
  const Rect *        testRect,
  const Rect *        iconRect,
  IconAlignmentType   align,
  IconSuiteRef        theIconSuite);


/*
 *  RectInIconMethod()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern Boolean 
RectInIconMethod(
  const Rect *        testRect,
  const Rect *        iconRect,
  IconAlignmentType   align,
  IconGetterUPP       theMethod,
  void *              yourDataPtr);


/*
 *  IconIDToRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
IconIDToRgn(
  RgnHandle           theRgn,
  const Rect *        iconRect,
  IconAlignmentType   align,
  SInt16              iconID);


/*
 *  IconSuiteToRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
IconSuiteToRgn(
  RgnHandle           theRgn,
  const Rect *        iconRect,
  IconAlignmentType   align,
  IconSuiteRef        theIconSuite);


/*
 *  IconMethodToRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
IconMethodToRgn(
  RgnHandle           theRgn,
  const Rect *        iconRect,
  IconAlignmentType   align,
  IconGetterUPP       theMethod,
  void *              yourDataPtr);


/*
 *  SetSuiteLabel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetSuiteLabel(
  IconSuiteRef   theSuite,
  SInt16         theLabel);


/*
 *  GetSuiteLabel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern SInt16 
GetSuiteLabel(IconSuiteRef theSuite);


/*
 *  GetIconCacheData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetIconCacheData(
  IconCacheRef   theCache,
  void **        theData);


/*
 *  SetIconCacheData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetIconCacheData(
  IconCacheRef   theCache,
  void *         theData);


/*
 *  GetIconCacheProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetIconCacheProc(
  IconCacheRef     theCache,
  IconGetterUPP *  theProc);


/*
 *  SetIconCacheProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetIconCacheProc(
  IconCacheRef    theCache,
  IconGetterUPP   theProc);


/*
 *  PlotIconHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
PlotIconHandle(
  const Rect *        theRect,
  IconAlignmentType   align,
  IconTransformType   transform,
  Handle              theIcon);


/*
 *  PlotSICNHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
PlotSICNHandle(
  const Rect *        theRect,
  IconAlignmentType   align,
  IconTransformType   transform,
  Handle              theSICN);


/*
 *  PlotCIconHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
PlotCIconHandle(
  const Rect *        theRect,
  IconAlignmentType   align,
  IconTransformType   transform,
  CIconHandle         theCIcon);












/*
   IconServices is an efficient mechanism to share icon data amongst multiple 
   clients. It avoids duplication of data; it provides efficient caching, 
   releasing memory when the icon data is no longer needed; it can provide
   the appropriate icon for any filesystem object; it can provide commonly 
   used icons (caution, note, help...); it is Appearance-savvy: the icons
   are switched when appropriate.
   IconServices refer to cached icon data using IconRef, a 32-bit opaque
   value. IconRefs are reference counted. When there are no more "owners" 
   of an IconRef, the memory used by the icon bitmap is disposed of.
   Two files of same type and creator with no custom icon will have the same IconRef.
   Files with custom icons will have their own IconRef.
*/

/*
   Use the special creator kSystemIconsCreator to get "standard" icons 
   that are not associated with a file, such as the help icon.
   Note that all lowercase creators are reserved by Apple.
*/
enum {
  kSystemIconsCreator           = 'macs'
};


/*
   Type of the predefined/generic icons. For example, the call:
      err = GetIconRef(kOnSystemDisk, kSystemIconsCreator, kHelpIcon, &iconRef);
   will retun in iconRef the IconRef for the standard help icon.
*/

/* Generic Finder icons */
enum {
  kClipboardIcon                = 'CLIP',
  kClippingUnknownTypeIcon      = 'clpu',
  kClippingPictureTypeIcon      = 'clpp',
  kClippingTextTypeIcon         = 'clpt',
  kClippingSoundTypeIcon        = 'clps',
  kDesktopIcon                  = 'desk',
  kFinderIcon                   = 'FNDR',
  kFontSuitcaseIcon             = 'FFIL',
  kFullTrashIcon                = 'ftrh',
  kGenericApplicationIcon       = 'APPL',
  kGenericCDROMIcon             = 'cddr',
  kGenericControlPanelIcon      = 'APPC',
  kGenericControlStripModuleIcon = 'sdev',
  kGenericComponentIcon         = 'thng',
  kGenericDeskAccessoryIcon     = 'APPD',
  kGenericDocumentIcon          = 'docu',
  kGenericEditionFileIcon       = 'edtf',
  kGenericExtensionIcon         = 'INIT',
  kGenericFileServerIcon        = 'srvr',
  kGenericFontIcon              = 'ffil',
  kGenericFontScalerIcon        = 'sclr',
  kGenericFloppyIcon            = 'flpy',
  kGenericHardDiskIcon          = 'hdsk',
  kGenericIDiskIcon             = 'idsk',
  kGenericRemovableMediaIcon    = 'rmov',
  kGenericMoverObjectIcon       = 'movr',
  kGenericPCCardIcon            = 'pcmc',
  kGenericPreferencesIcon       = 'pref',
  kGenericQueryDocumentIcon     = 'qery',
  kGenericRAMDiskIcon           = 'ramd',
  kGenericSharedLibaryIcon      = 'shlb',
  kGenericStationeryIcon        = 'sdoc',
  kGenericSuitcaseIcon          = 'suit',
  kGenericURLIcon               = 'gurl',
  kGenericWORMIcon              = 'worm',
  kInternationalResourcesIcon   = 'ifil',
  kKeyboardLayoutIcon           = 'kfil',
  kSoundFileIcon                = 'sfil',
  kSystemSuitcaseIcon           = 'zsys',
  kTrashIcon                    = 'trsh',
  kTrueTypeFontIcon             = 'tfil',
  kTrueTypeFlatFontIcon         = 'sfnt',
  kTrueTypeMultiFlatFontIcon    = 'ttcf',
  kUserIDiskIcon                = 'udsk',
  kInternationResourcesIcon     = kInternationalResourcesIcon /* old name*/
};

/* Internet locations */
enum {
  kInternetLocationHTTPIcon     = 'ilht',
  kInternetLocationFTPIcon      = 'ilft',
  kInternetLocationAppleShareIcon = 'ilaf',
  kInternetLocationAppleTalkZoneIcon = 'ilat',
  kInternetLocationFileIcon     = 'ilfi',
  kInternetLocationMailIcon     = 'ilma',
  kInternetLocationNewsIcon     = 'ilnw',
  kInternetLocationNSLNeighborhoodIcon = 'ilns',
  kInternetLocationGenericIcon  = 'ilge'
};

/* Folders */
enum {
  kGenericFolderIcon            = 'fldr',
  kDropFolderIcon               = 'dbox',
  kMountedFolderIcon            = 'mntd',
  kOpenFolderIcon               = 'ofld',
  kOwnedFolderIcon              = 'ownd',
  kPrivateFolderIcon            = 'prvf',
  kSharedFolderIcon             = 'shfl'
};

/* Sharing Privileges icons */
enum {
  kSharingPrivsNotApplicableIcon = 'shna',
  kSharingPrivsReadOnlyIcon     = 'shro',
  kSharingPrivsReadWriteIcon    = 'shrw',
  kSharingPrivsUnknownIcon      = 'shuk',
  kSharingPrivsWritableIcon     = 'writ'
};


/* Users and Groups icons */
enum {
  kUserFolderIcon               = 'ufld',
  kWorkgroupFolderIcon          = 'wfld',
  kGuestUserIcon                = 'gusr',
  kUserIcon                     = 'user',
  kOwnerIcon                    = 'susr',
  kGroupIcon                    = 'grup'
};

/* Special folders */
enum {
  kAppearanceFolderIcon         = 'appr',
  kAppleExtrasFolderIcon        = 'aexÄ',
  kAppleMenuFolderIcon          = 'amnu',
  kApplicationsFolderIcon       = 'apps',
  kApplicationSupportFolderIcon = 'asup',
  kAssistantsFolderIcon         = 'astÄ',
  kColorSyncFolderIcon          = 'prof',
  kContextualMenuItemsFolderIcon = 'cmnu',
  kControlPanelDisabledFolderIcon = 'ctrD',
  kControlPanelFolderIcon       = 'ctrl',
  kControlStripModulesFolderIcon = 'sdvÄ',
  kDocumentsFolderIcon          = 'docs',
  kExtensionsDisabledFolderIcon = 'extD',
  kExtensionsFolderIcon         = 'extn',
  kFavoritesFolderIcon          = 'favs',
  kFontsFolderIcon              = 'font',
  kHelpFolderIcon               = 'Ählp',
  kInternetFolderIcon           = 'intÄ',
  kInternetPlugInFolderIcon     = 'Änet',
  kInternetSearchSitesFolderIcon = 'issf',
  kLocalesFolderIcon            = 'Äloc',
  kMacOSReadMeFolderIcon        = 'morÄ',
  kPublicFolderIcon             = 'pubf',
  kPreferencesFolderIcon        = 'prfÄ',
  kPrinterDescriptionFolderIcon = 'ppdf',
  kPrinterDriverFolderIcon      = 'Äprd',
  kPrintMonitorFolderIcon       = 'prnt',
  kRecentApplicationsFolderIcon = 'rapp',
  kRecentDocumentsFolderIcon    = 'rdoc',
  kRecentServersFolderIcon      = 'rsrv',
  kScriptingAdditionsFolderIcon = 'Äscr',
  kSharedLibrariesFolderIcon    = 'Älib',
  kScriptsFolderIcon            = 'scrÄ',
  kShutdownItemsDisabledFolderIcon = 'shdD',
  kShutdownItemsFolderIcon      = 'shdf',
  kSpeakableItemsFolder         = 'spki',
  kStartupItemsDisabledFolderIcon = 'strD',
  kStartupItemsFolderIcon       = 'strt',
  kSystemExtensionDisabledFolderIcon = 'macD',
  kSystemFolderIcon             = 'macs',
  kTextEncodingsFolderIcon      = 'Ätex',
  kUsersFolderIcon              = 'usrÄ',
  kUtilitiesFolderIcon          = 'utiÄ',
  kVoicesFolderIcon             = 'fvoc'
};

/* Badges */
enum {
  kAppleScriptBadgeIcon         = 'scrp',
  kLockedBadgeIcon              = 'lbdg',
  kMountedBadgeIcon             = 'mbdg',
  kSharedBadgeIcon              = 'sbdg',
  kAliasBadgeIcon               = 'abdg',
  kAlertCautionBadgeIcon        = 'cbdg'
};

/* Alert icons */
enum {
  kAlertNoteIcon                = 'note',
  kAlertCautionIcon             = 'caut',
  kAlertStopIcon                = 'stop'
};

/* Networking icons */
enum {
  kAppleTalkIcon                = 'atlk',
  kAppleTalkZoneIcon            = 'atzn',
  kAFPServerIcon                = 'afps',
  kFTPServerIcon                = 'ftps',
  kHTTPServerIcon               = 'htps',
  kGenericNetworkIcon           = 'gnet',
  kIPFileServerIcon             = 'isrv'
};

/* Toolbar icons */
enum {
  kToolbarCustomizeIcon         = 'tcus',
  kToolbarDeleteIcon            = 'tdel',
  kToolbarFavoritesIcon         = 'tfav',
  kToolbarHomeIcon              = 'thom'
};

/* Other icons */
enum {
  kAppleLogoIcon                = 'capl',
  kAppleMenuIcon                = 'sapl',
  kBackwardArrowIcon            = 'baro',
  kFavoriteItemsIcon            = 'favr',
  kForwardArrowIcon             = 'faro',
  kGridIcon                     = 'grid',
  kHelpIcon                     = 'help',
  kKeepArrangedIcon             = 'arng',
  kLockedIcon                   = 'lock',
  kNoFilesIcon                  = 'nfil',
  kNoFolderIcon                 = 'nfld',
  kNoWriteIcon                  = 'nwrt',
  kProtectedApplicationFolderIcon = 'papp',
  kProtectedSystemFolderIcon    = 'psys',
  kRecentItemsIcon              = 'rcnt',
  kShortcutIcon                 = 'shrt',
  kSortAscendingIcon            = 'asnd',
  kSortDescendingIcon           = 'dsnd',
  kUnlockedIcon                 = 'ulck',
  kConnectToIcon                = 'cnct',
  kGenericWindowIcon            = 'gwin',
  kQuestionMarkIcon             = 'ques',
  kDeleteAliasIcon              = 'dali',
  kEjectMediaIcon               = 'ejec',
  kBurningIcon                  = 'burn',
  kRightContainerArrowIcon      = 'rcar'
};



/*  IconServicesUsageFlags */
typedef UInt32                          IconServicesUsageFlags;
enum {
  kIconServicesNormalUsageFlag  = 0
};


/*
  kIconServicesCatalogInfoMask - Minimal bitmask for use with
    GetIconRefFromFileInfo(). Use this mask with FSGetCatalogInfo
    before calling GetIconRefFromFileInfo().
*/
enum {
  kIconServicesCatalogInfoMask  = (kFSCatInfoNodeID | kFSCatInfoParentDirID | kFSCatInfoVolume | kFSCatInfoNodeFlags | kFSCatInfoFinderInfo | kFSCatInfoFinderXInfo | kFSCatInfoUserAccess)
};


/*
 *  PlotIconRefFlags
 *  
 *  Discussion:
 *    Flags that can be passed to the PlotIconRefInContext routine.
 */

  /*
   * Draw the icon image and alpha channel.
   */
typedef UInt32 PlotIconRefFlags;
enum {
  kPlotIconRefNormalFlags       = 0L,

  /*
   * Only draw the alpha channel.
   */
  kPlotIconRefNoImage           = (1 << 1),

  /*
   * Only draw the image.
   */
  kPlotIconRefNoMask            = (1 << 2)
};



/*
    IconFamily 'icns' resources contain an entire IconFamily (all sizes and depths).  
   For custom icons, icns IconFamily resources of the custom icon resource ID are fetched first before
   the classic custom icons (individual 'ics#, ICN#, etc) are fetched.  If the fetch of the icns resource
   succeeds then the icns is looked at exclusively for the icon data.
   For custom icons, new icon features such as 32-bit deep icons are only fetched from the icns resource.
   This is to avoid incompatibilities with cut & paste of new style icons with an older version of the
   MacOS Finder.
   DriverGestalt is called with code kdgMediaIconSuite by IconServices after calling FSM to determine a
   driver icon for a particular device.  The result of the kdgMediaIconSuite call to DriverGestalt should
   be a pointer an an IconFamily.  In this manner driver vendors can provide rich, detailed drive icons
   instead of the 1-bit variety previously supported.
*/
enum {
  kIconFamilyType               = 'icns'
};


struct IconFamilyElement {
  OSType              elementType;            /* 'ICN#', 'icl8', etc...*/
  Size                elementSize;            /* Size of this element*/
  unsigned char       elementData[1];
};
typedef struct IconFamilyElement        IconFamilyElement;
struct IconFamilyResource {
  OSType              resourceType;           /* Always 'icns'*/
  Size                resourceSize;           /* Total size of this resource*/
  IconFamilyElement   elements[1];

};
typedef struct IconFamilyResource       IconFamilyResource;
typedef IconFamilyResource *            IconFamilyPtr;
typedef IconFamilyPtr *                 IconFamilyHandle;
/*
  ==============================================================================
   Initialization and Termination
  ==============================================================================
*/

/*
   IconServicesInit
   
   Call this routine once per classic 68K application initialization.
   This routine does not need to be called at boot time.
*/

/*
 *  IconServicesInit()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */



/*
   IconServicesTerminate:
   
   Call this routine once from the termination of a classic 68K application.
   This routine does not need to be called at boot time.
*/

/*
 *  IconServicesTerminate()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */


/*
  ==============================================================================
   Converting data structures
  ==============================================================================
*/


/*
   IconRefToIconFamily
   This routines returns a new IconFamily that contains the data corresponding
   to the specified IconRef.
*/

/*
 *  IconRefToIconFamily()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
IconRefToIconFamily(
  IconRef             theIconRef,
  IconSelectorValue   whichIcons,
  IconFamilyHandle *  iconFamily);



/*
   IconFamilyToIconSuite
   This routine transfers the data from an icon family handle into an icon suite.
*/

/*
 *  IconFamilyToIconSuite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
IconFamilyToIconSuite(
  IconFamilyHandle    iconFamily,
  IconSelectorValue   whichIcons,
  IconSuiteRef *      iconSuite);



/*
   IconSuiteToIconFamily
   This routine transfers the data in an icon suite into an icon family.
*/

/*
 *  IconSuiteToIconFamily()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
IconSuiteToIconFamily(
  IconSuiteRef        iconSuite,
  IconSelectorValue   whichIcons,
  IconFamilyHandle *  iconFamily);



/*
   SetIconFamilyData
   Change the data of an icon family. The data is copied.
   The type can be one of the icon type, or 'PICT'.
   The data will be compressed if needed.
*/

/*
 *  SetIconFamilyData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
SetIconFamilyData(
  IconFamilyHandle   iconFamily,
  OSType             iconType,
  Handle             h);



/*
   GetIconFamilyData
   Return a copy of the data in the icon family.
   The type can be one of the icon type, or 'PICT'
   The data will be returned uncompressed.
   The handle (h) will be resized as appropriate. If no data of the 
   requested type is present, the handle size will be set to 0.
*/

/*
 *  GetIconFamilyData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
GetIconFamilyData(
  IconFamilyHandle   iconFamily,
  OSType             iconType,
  Handle             h);



/*
  ==============================================================================
   Reference counting
  ==============================================================================
*/


/*
   GetIconRefOwners
   
   This routine returns the reference count for the IconRef, or number of owners.
   
   A valid IconRef always has at least one owner.
*/

/*
 *  GetIconRefOwners()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
GetIconRefOwners(
  IconRef   theIconRef,
  UInt16 *  owners);



/*
   AcquireIconRef
   This routine increments the reference count for the IconRef
*/

/*
 *  AcquireIconRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
AcquireIconRef(IconRef theIconRef);




/*
   ReleaseIconRef
   
   This routine decrements the reference count for the IconRef.
   
   When the reference count reaches 0, all memory allocated for the icon
   is disposed. Any subsequent use of the IconRef is invalid.
*/

/*
 *  ReleaseIconRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
ReleaseIconRef(IconRef theIconRef);




/*
  ==============================================================================
   Getting an IconRef
  ==============================================================================
*/


/*
   GetIconRefFromFile
   
   This routine returns an icon ref for the specified file, folder or volume.
   The label information is provided separately, since two files with the same icon 
   but a different label would share the same iconRef. The label can be used in 
   PlotIconRef() for example.
   
   Use this routine if you have no information about the file system object. If 
   you have already done a GetCatInfo on the file and want to save some I/O, 
   call GetIconRefFromFolder() if you know it's a folder with no custom icon or 
   call GetIconRef() if it's a file with no custom icon.
   This routine increments the reference count of the returned IconRef. Call 
   ReleaseIconRef() when you're done with it.
*/

/*
 *  GetIconRefFromFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
GetIconRefFromFile(
  const FSSpec *  theFile,
  IconRef *       theIconRef,
  SInt16 *        theLabel);




/*
   GetIconRef
   
   This routine returns an icon ref for an icon in the desktop database or
   for a registered icon.
   The system registers a set of icon such as the help icon with the creator 
   code kSystemIconsCreator. See above for a list of the registered system types.
   The vRefNum is used as a hint on where to look for the icon first. Use 
   kOnSystemDisk if you don't know what to pass.
   This routine increments the reference count of the returned IconRef. Call 
   ReleaseIconRef() when you're done with it.
*/

/*
 *  GetIconRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
GetIconRef(
  SInt16     vRefNum,
  OSType     creator,
  OSType     iconType,
  IconRef *  theIconRef);




/*
   GetIconRefFromFolder
   
   This routine returns an icon ref for a folder with no custom icon.
   Use the more generic, but slightly slower, GetIconRefFromFile() if
   you don't already have the necessary info about the file.
   Attributes should be CInfoPBRec.dirInfo.ioFlAttrib for this folder.
   Access privileges should be CInfoPBRec.dirInfo.ioACUser for this folder.
   This routine increments the reference count of the IconRef. Call ReleaseIconRef() 
   when you're done with it.
*/

/*
 *  GetIconRefFromFolder()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
GetIconRefFromFolder(
  SInt16     vRefNum,
  SInt32     parentFolderID,
  SInt32     folderID,
  SInt8      attributes,
  SInt8      accessPrivileges,
  IconRef *  theIconRef);


/* GetIconRefFromFileInfo*/
/*
 *  GetIconRefFromFileInfo()
 *  
 *  Summary:
 *    This routine returns an IconRef for a file with minimal file I/O.
 *  
 *  Discussion:
 *    To minimize file operations, FSGetCatalogInfo should be called
 *    prior to calling this routine. The FSCatalogInfo should
 *    correspond to kIconServicesCatalogInfoMask The name should be
 *    fetched and passed in. If either the name or the correct catalog
 *    info is not passed in, this routine will do file operations for
 *    this information instead.
 *  
 *  Parameters:
 *    
 *    inRef:
 *      An FSRef for the target file
 *    
 *    inFileNameLength:
 *      The length of the name of the target file
 *    
 *    inFileName:
 *      The name of the target file
 *    
 *    inWhichInfo:
 *      The mask of file info already acquired.
 *    
 *    inCatalogInfo:
 *      The catalog info already acquired.
 *    
 *    inUsageFlags:
 *      The usage flags for this call (use
 *      kIconServicesNormalUsageFlag).
 *    
 *    outIconRef:
 *      The output IconRef for the routine.
 *    
 *    outLabel:
 *      The output label for the icon/file.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetIconRefFromFileInfo(
  const FSRef *            inRef,
  UniCharCount             inFileNameLength,
  const UniChar *          inFileName,             /* can be NULL */
  FSCatalogInfoBitmap      inWhichInfo,
  const FSCatalogInfo *    inCatalogInfo,          /* can be NULL */
  IconServicesUsageFlags   inUsageFlags,
  IconRef *                outIconRef,
  SInt16 *                 outLabel);


/*
  ==============================================================================
   Adding and modifying IconRef
  ==============================================================================
*/


/*
   RegisterIconRefFromIconFamily
   This routine adds a new entry to the IconRef registry. Other clients will be 
   able to access it using the (creator, iconType) pair specified here.
   Lower-case creators are reserved for the system.
   Consider using RegisterIconRefFromResource() if possible, since the data 
   registered using RegisterIconRefFromFamily() cannot be purged.
   The iconFamily data is copied and the caller is reponsible for disposing of it.
   This routine increments the reference count of the IconRef. Call ReleaseIconRef() 
   when you're done with it.
*/

/*
 *  RegisterIconRefFromIconFamily()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
RegisterIconRefFromIconFamily(
  OSType             creator,
  OSType             iconType,
  IconFamilyHandle   iconFamily,
  IconRef *          theIconRef);



/*
   RegisterIconRefFromResource
   
   Registers an IconRef from a resouce file.  
   Lower-case creators are reserved for the system.
   The icon data to be fetched is either classic icon data or an icon family.  
   The 'icns' icon family is searched for before the classic icon data.
   This routine increments the reference count of the IconRef. Call ReleaseIconRef() 
   when you're done with it.
*/

/*
 *  RegisterIconRefFromResource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
RegisterIconRefFromResource(
  OSType          creator,
  OSType          iconType,
  const FSSpec *  resourceFile,
  SInt16          resourceID,
  IconRef *       theIconRef);


/* RegisterIconRefFromFSRef*/
/*
 *  RegisterIconRefFromFSRef()
 *  
 *  Discussion:
 *    This routine registers an IconRef from a ".icns" file and
 *    associates it with a creator/type pair.
 *  
 *  Parameters:
 *    
 *    creator:
 *      The creator code for the icns file.
 *    
 *    iconType:
 *      The type code for the icns file
 *    
 *    iconFile:
 *      The FSRef of the icns file.
 *    
 *    theIconRef:
 *      The output IconRef for the routine.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RegisterIconRefFromFSRef(
  OSType         creator,
  OSType         iconType,
  const FSRef *  iconFile,
  IconRef *      theIconRef);


/*
   UnregisterIconRef
   
   Removes the specified icon from the icon cache (if there are no users of it).  
   If some clients are using this iconRef, then the IconRef will be removed when the 
   last user calls ReleaseIconRef.
*/

/*
 *  UnregisterIconRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
UnregisterIconRef(
  OSType   creator,
  OSType   iconType);




/*
   UpdateIconRef
   
   Call this routine to force an update of the data for iconRef.
   
   For example after changing an icon in the desktop database or changing the custom 
   icon of a file. Note that after _adding_ a custom icon to file or folder, you 
   need to call GetIconRefFromFile() to get a new IconRef specific to this file. 
   
   This routine does nothing if the IconRef is a registered icon.
*/

/*
 *  UpdateIconRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
UpdateIconRef(IconRef theIconRef);




/*
   OverrideIconRefFromResource
   
   This routines replaces the bitmaps of the specified IconRef with the ones
   in the specified resource file.
*/

/*
 *  OverrideIconRefFromResource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
OverrideIconRefFromResource(
  IconRef         theIconRef,
  const FSSpec *  resourceFile,
  SInt16          resourceID);




/*
   OverrideIconRef
   
   This routines replaces the bitmaps of the specified IconRef with the ones
   from the new IconRef.
*/

/*
 *  OverrideIconRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
OverrideIconRef(
  IconRef   oldIconRef,
  IconRef   newIconRef);



/*
   RemoveIconRefOverride
   This routine remove an override if one was applied to the icon and 
   reverts back to the original bitmap data.
*/

/*
 *  RemoveIconRefOverride()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
RemoveIconRefOverride(IconRef theIconRef);




/*
  ==============================================================================
   Creating composite IconRef
  ==============================================================================
*/


/*
   CompositeIconRef
   
   Superimposes an IconRef on top of another one
*/

/*
 *  CompositeIconRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
CompositeIconRef(
  IconRef    backgroundIconRef,
  IconRef    foregroundIconRef,
  IconRef *  compositeIconRef);



/*
   IsIconRefComposite
   Indicates if a given icon ref is a composite of two other icon refs (and which ones)
   If it isn't a composite, backgroundIconRef and foreGroundIconRef will be 0.
*/

/*
 *  IsIconRefComposite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
IsIconRefComposite(
  IconRef    compositeIconRef,
  IconRef *  backgroundIconRef,
  IconRef *  foregroundIconRef);




/*
  ==============================================================================
   Using IconRef
  ==============================================================================
*/

/*
   IsValidIconRef
   Return true if the iconRef passed in is a valid icon ref
*/

/*
 *  IsValidIconRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern Boolean 
IsValidIconRef(IconRef theIconRef);



/*
   PlotIconRef
   
   This routine plots the IconRef.  It mostly takes the same parameters as 
   PlotIconSuite. Pass kIconServicesNormalUsageFlag as a default value for 
   IconServicesUsageFlags.
*/

/*
 *  PlotIconRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
PlotIconRef(
  const Rect *             theRect,
  IconAlignmentType        align,
  IconTransformType        transform,
  IconServicesUsageFlags   theIconServicesUsageFlags,
  IconRef                  theIconRef);



/* PlotIconRefInContext*/
/*
 *  PlotIconRefInContext()
 *  
 *  Discussion:
 *    This routines plots an IconRef using Quartz/CoreGraphics.
 *  
 *  Parameters:
 *    
 *    inContext:
 *      The graphics context to use.
 *    
 *    inRect:
 *      The rect to plot the icon in.
 *    
 *    inAlign:
 *      The icon alignment.
 *    
 *    inTransform:
 *      The icon transform.
 *    
 *    inLabelColor:
 *      The icon label color.
 *    
 *    inFlags:
 *      The drawing flags to use (usually kPlotIconRefNormalFlags).
 *    
 *    inIconRef:
 *      The IconRef to plot.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PlotIconRefInContext(
  CGContextRef        inContext,
  const CGRect *      inRect,
  IconAlignmentType   inAlign,
  IconTransformType   inTransform,
  const RGBColor *    inLabelColor,
  PlotIconRefFlags    inFlags,
  IconRef             inIconRef);



/*
   PtInIconRef
   
   This routine indicates if testPt would hit the icon designated by iconRef.
   It mostly takes the same parameters as PtInIconSuite.
   Pass kIconServicesNormalUsageFlag as a default value for IconServicesUsageFlags.
*/


/*
 *  PtInIconRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern Boolean 
PtInIconRef(
  const Point *            testPt,
  const Rect *             iconRect,
  IconAlignmentType        align,
  IconServicesUsageFlags   theIconServicesUsageFlags,
  IconRef                  theIconRef);



/*
   RectInIconRef
   
   This routine indicates if testRect would intersect the icon designated by iconRef.
   It mostly takes the same parameters as RectInIconSuite.
   Pass kIconServicesNormalUsageFlag as a default value for IconServicesUsageFlags.
*/


/*
 *  RectInIconRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern Boolean 
RectInIconRef(
  const Rect *             testRect,
  const Rect *             iconRect,
  IconAlignmentType        align,
  IconServicesUsageFlags   iconServicesUsageFlags,
  IconRef                  theIconRef);



/*
   IconRefToRgn
   
   This routine returns a region for the icon.
   It mostly takes the same parameters as IconSuiteToRgn.
   Pass kIconServicesNormalUsageFlag as a default value for IconServicesUsageFlags.
*/

/*
 *  IconRefToRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
IconRefToRgn(
  RgnHandle                theRgn,
  const Rect *             iconRect,
  IconAlignmentType        align,
  IconServicesUsageFlags   iconServicesUsageFlags,
  IconRef                  theIconRef);



/*
   GetIconSizesFromIconRef
   
   This routine returns an IconSelectorValue indicating the depths and sizes of 
   icon data which are actually available.  It takes an IconSelectorValue 
   indicating which sizes/depths the caller is interested and returns an 
   IconSelectorValue indicating which sizes/depths exist.
   
   Caution:
   
   This is potentially an extremely expensive call as IconServices may be forced 
   to attempt fetching the data for the IconRef's sizes/depths which may result 
   in hitting the local disk or even the network to obtain the data to determine 
   which sizes/depths actually exist.
   Pass kIconServicesNormalUsageFlag as a default value for IconServicesUsageFlags.
*/

/*
 *  GetIconSizesFromIconRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
GetIconSizesFromIconRef(
  IconSelectorValue        iconSelectorInput,
  IconSelectorValue *      iconSelectorOutputPtr,
  IconServicesUsageFlags   iconServicesUsageFlags,
  IconRef                  theIconRef);




/*
  ==============================================================================
   Flushing IconRef data
  ==============================================================================
*/


/*
   FlushIconRefs
   
   Making this call will dispose of all the data for the specified icons if 
   the data can be reacquired, for example if the data is provided from a resource.
   '****' is a wildcard for all types or all creators.
*/

/*
 *  FlushIconRefs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
FlushIconRefs(
  OSType   creator,
  OSType   iconType);



/*
   FlushIconRefsByVolume
   
   This routine disposes of the data for the icons related to the indicated volume
   if this data can be reacquired, for example if the data is provided from a 
   resource.
*/

/*
 *  FlushIconRefsByVolume()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
FlushIconRefsByVolume(SInt16 vRefNum);




/*
  ==============================================================================
   Controling custom icons
  ==============================================================================
*/


/*
   SetCustomIconsEnabled
   
   Enable or disable custom icons on the specified volume.
*/

/*
 *  SetCustomIconsEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
SetCustomIconsEnabled(
  SInt16    vRefNum,
  Boolean   enableCustomIcons);



/*
   GetCustomIconsEnabled
   
   Return true if custom icons are enabled on the specified volume, false otherwise.
*/

/*
 *  GetCustomIconsEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
GetCustomIconsEnabled(
  SInt16     vRefNum,
  Boolean *  customIconsEnabled);



/*
   IsIconRefMaskEmpty
   Returns true if the mask for this icon is blank
*/

/*
 *  IsIconRefMaskEmpty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern Boolean 
IsIconRefMaskEmpty(IconRef iconRef);



/*
   GetIconRefVariant
   Icon variants allows different images to be used with different icon state.
   For example, the 'open' variant for a folder could be represented with
   an open folder.
   Given an icon ref and a desired variant, this routine returns an icon
   ref (which may be the same as the input icon ref) and a transformation 
   which should be used with PlotIconRef() to render the icon appropriately.
   The returned icon ref should be used to do hit-testing.
*/

/*
 *  GetIconRefVariant()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 9.0 and later
 */
extern IconRef 
GetIconRefVariant(
  IconRef              inIconRef,
  OSType               inVariant,
  IconTransformType *  outTransform);




/*
  ==============================================================================
   Icon files (.icns files)
  ==============================================================================
*/


/*
   RegisterIconRefFromIconFile
   This routine adds a new entry to the IconRef registry. Other clients will be 
   able to access it using the (creator, iconType) pair specified here.
   Lower-case creators are reserved for the system.
   If the creator is kSystemIconsCreator and the iconType is 0, a new IconRef
   is always returned. Otherwise, if the creator and type have already been
   registered, the previously registered IconRef is returned.
   This routine increments the reference count of the IconRef. Call ReleaseIconRef() 
   when you're done with it.
*/

/*
 *  RegisterIconRefFromIconFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 9.0 and later
 */
extern OSErr 
RegisterIconRefFromIconFile(
  OSType          creator,
  OSType          iconType,
  const FSSpec *  iconFile,
  IconRef *       theIconRef);



/*
   ReadIconFile
   Read the specified icon file into the icon family handle.
   The caller is responsible for disposing the iconFamily
*/

/*
 *  ReadIconFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 9.0 and later
 */
extern OSErr 
ReadIconFile(
  const FSSpec *      iconFile,
  IconFamilyHandle *  iconFamily);


/* ReadIconFromFSRef*/
/*
 *  ReadIconFromFSRef()
 *  
 *  Discussion:
 *    This routine reads an icon (icns) file into memory.
 *  
 *  Parameters:
 *    
 *    ref:
 *      The FSRef for the icon file.
 *    
 *    iconFamily:
 *      The handle for the icon family.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ReadIconFromFSRef(
  const FSRef *       ref,
  IconFamilyHandle *  iconFamily);



/*
   WriteIconFile
   Write the iconFamily handle to the specified file
*/

/*
 *  WriteIconFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 9.0 and later
 */
extern OSErr 
WriteIconFile(
  IconFamilyHandle   iconFamily,
  const FSSpec *     iconFile);




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

#endif /* __ICONS__ */

