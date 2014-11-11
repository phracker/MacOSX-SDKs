/*
     File:       IconsCore.h
 
     Contains:   Icon Utilities and Icon Services Interfaces.
 
     Copyright:  (c) 2003-2012 by Apple Inc. All rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/

*/

#ifndef __ICONSCORE__
#define __ICONSCORE__

#ifndef __CARBONCORE__
#include <CarbonCore/CarbonCore.h>
#endif

#ifndef __OSSERVICES__
#include <OSServices/OSServices.h>
#endif


#include <Availability.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
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

/* IconRefs identify cached icon data. IconRef 0 is invalid.*/
typedef struct OpaqueIconRef* IconRef;

	
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
  kComputerIcon                 = 'root',
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
  kUnknownFSObjectIcon          = 'unfs',
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
  kAppleExtrasFolderIcon        = 0x616578C4/*'aexÄ'*/,
  kAppleMenuFolderIcon          = 'amnu',
  kApplicationsFolderIcon       = 'apps',
  kApplicationSupportFolderIcon = 'asup',
  kAssistantsFolderIcon         = 0x617374C4/*'astÄ'*/,
  kColorSyncFolderIcon          = 'prof',
  kContextualMenuItemsFolderIcon = 'cmnu',
  kControlPanelDisabledFolderIcon = 'ctrD',
  kControlPanelFolderIcon       = 'ctrl',
  kControlStripModulesFolderIcon = 0x736476C4/*'sdvÄ'*/,
  kDocumentsFolderIcon          = 'docs',
  kExtensionsDisabledFolderIcon = 'extD',
  kExtensionsFolderIcon         = 'extn',
  kFavoritesFolderIcon          = 'favs',
  kFontsFolderIcon              = 'font',
  kHelpFolderIcon               = (int)0xC4686C70/*'Ählp' */,
  kInternetFolderIcon           = 0x696E74C4/*'intÄ'*/,
  kInternetPlugInFolderIcon     = (int)0xC46E6574/*'Änet' */,
  kInternetSearchSitesFolderIcon = 'issf',
  kLocalesFolderIcon            = (int)0xC46C6F63/*'Äloc' */,
  kMacOSReadMeFolderIcon        = 0x6D6F72C4/*'morÄ'*/,
  kPublicFolderIcon             = 'pubf',
  kPreferencesFolderIcon        = 0x707266C4/*'prfÄ'*/,
  kPrinterDescriptionFolderIcon = 'ppdf',
  kPrinterDriverFolderIcon      = (int)0xC4707264/*'Äprd' */,
  kPrintMonitorFolderIcon       = 'prnt',
  kRecentApplicationsFolderIcon = 'rapp',
  kRecentDocumentsFolderIcon    = 'rdoc',
  kRecentServersFolderIcon      = 'rsrv',
  kScriptingAdditionsFolderIcon = (int)0xC4736372/*'Äscr' */,
  kSharedLibrariesFolderIcon    = (int)0xC46C6962/*'Älib' */,
  kScriptsFolderIcon            = 0x736372C4/*'scrÄ'*/,
  kShutdownItemsDisabledFolderIcon = 'shdD',
  kShutdownItemsFolderIcon      = 'shdf',
  kSpeakableItemsFolder         = 'spki',
  kStartupItemsDisabledFolderIcon = 'strD',
  kStartupItemsFolderIcon       = 'strt',
  kSystemExtensionDisabledFolderIcon = 'macD',
  kSystemFolderIcon             = 'macs',
  kTextEncodingsFolderIcon      = (int)0xC4746578/*'Ätex' */,
  kUsersFolderIcon              = 0x757372C4/*'usrÄ'*/,
  kUtilitiesFolderIcon          = 0x757469C4/*'utiÄ'*/,
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
  kToolbarHomeIcon              = 'thom',
  kToolbarAdvancedIcon          = 'tbav',
  kToolbarInfoIcon              = 'tbin',
  kToolbarLabelsIcon            = 'tblb',
  kToolbarApplicationsFolderIcon = 'tAps',
  kToolbarDocumentsFolderIcon   = 'tDoc',
  kToolbarMovieFolderIcon       = 'tMov',
  kToolbarMusicFolderIcon       = 'tMus',
  kToolbarPicturesFolderIcon    = 'tPic',
  kToolbarPublicFolderIcon      = 'tPub',
  kToolbarDesktopFolderIcon     = 'tDsk',
  kToolbarDownloadsFolderIcon   = 'tDwn',
  kToolbarLibraryFolderIcon     = 'tLib',
  kToolbarUtilitiesFolderIcon   = 'tUtl',
  kToolbarSitesFolderIcon       = 'tSts'
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
  kIconServicesNormalUsageFlag  = 0x00000000,
  kIconServicesNoBadgeFlag      = 0x00000001, /* available on Panther and later */
  kIconServicesUpdateIfNeededFlag = 0x00000002 /* available on Panther and later */
};


/*
  kIconServicesCatalogInfoMask - Minimal bitmask for use with
    GetIconRefFromFileInfo(). Use this mask with FSGetCatalogInfo
    before calling GetIconRefFromFileInfo(). Please note kFSCatInfoFinderXInfo flag is
    valid only on MacOS X and must be cleared from CatalogInfoMask before
    passing to GetIconRefFromFileInfo while running under MacOS 9 (or error will be returned)
*/
enum {
  kIconServicesCatalogInfoMask  = (kFSCatInfoNodeID | kFSCatInfoParentDirID | kFSCatInfoVolume | kFSCatInfoNodeFlags | kFSCatInfoFinderInfo | kFSCatInfoFinderXInfo | kFSCatInfoUserAccess | kFSCatInfoPermissions | kFSCatInfoContentMod)
};


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
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
GetIconRefOwners(
  IconRef   theIconRef,
  UInt16 *  owners)                                           __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
   AcquireIconRef
   This routine increments the reference count for the IconRef
*/

/*
 *  AcquireIconRef()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
AcquireIconRef(IconRef theIconRef)                            __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*
   ReleaseIconRef
   
   This routine decrements the reference count for the IconRef.
   
   When the reference count reaches 0, all memory allocated for the icon
   is disposed. Any subsequent use of the IconRef is invalid.
*/

/*
 *  ReleaseIconRef()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
ReleaseIconRef(IconRef theIconRef)                            __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




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
   This call is deprecated. Please use GetIconRefFromFileInfo() instead.
*/

#if !__LP64__
/*
 *  GetIconRefFromFile()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
GetIconRefFromFile(
  const FSSpec *  theFile,
  IconRef *       theIconRef,
  SInt16 *        theLabel)                                   __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_5, __IPHONE_NA, __IPHONE_NA);




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

#endif  /* !__LP64__ */

/*
 *  GetIconRef()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
GetIconRef(
  SInt16     vRefNum,
  OSType     creator,
  OSType     iconType,
  IconRef *  theIconRef)                                      __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




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
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
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
  IconRef *  theIconRef)                                      __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


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
 *  Mac OS X threading:
 *    Thread safe since version 10.2
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
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
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
  SInt16 *                 outLabel)               /* can be NULL */ __OSX_AVAILABLE_STARTING(__MAC_10_1, __IPHONE_NA);


/* GetIconRefFromTypeInfo*/
/*
 *  GetIconRefFromTypeInfo()
 *  
 *  Summary:
 *    Create an IconRef for a type information.
 *  
 *  Discussion:
 *    Creates IconRef based on provided type info. Any of the input
 *    parameters can be zero (meaning it is unknown). Returns generic
 *    document icon in case if all parameters are zeroes. Calling the
 *    routine with non zero inCreator and inType and zero inExtension
 *    and inMIMEType is equivalent to GetIconRef(kOnSystemDisk,
 *    inCreator, inType).
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inCreator:
 *      The creator.
 *    
 *    inType:
 *      The type.
 *    
 *    inExtension:
 *      The extension.
 *    
 *    inMIMEType:
 *      The MIME type.
 *    
 *    inUsageFlags:
 *      The usage flags for this call (use
 *      kIconServicesNormalUsageFlag).
 *    
 *    outIconRef:
 *      The output IconRef for the routine.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
GetIconRefFromTypeInfo(
  OSType                   inCreator,
  OSType                   inType,
  CFStringRef              inExtension,
  CFStringRef              inMIMEType,
  IconServicesUsageFlags   inUsageFlags,
  IconRef *                outIconRef)                        __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);



/* GetIconRefFromIconFamilyPtr*/
/*
 *  GetIconRefFromIconFamilyPtr()
 *  
 *  Summary:
 *    Create an IconRef for the IconFamilyPtr.
 *  
 *  Discussion:
 *    This routine creates IconRef for the IconFamilyPtr.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inIconFamilyPtr:
 *      The icon data
 *    
 *    inSize:
 *      The icon data size
 *    
 *    outIconRef:
 *      The output IconRef for the routine.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetIconRefFromIconFamilyPtr(
  const IconFamilyResource *  inIconFamilyPtr,
  Size                        inSize,
  IconRef *                   outIconRef)                     __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);


/* GetIconRefFromComponent*/
/*
 *  GetIconRefFromComponent()
 *  
 *  Summary:
 *    Create an IconRef for the component.
 *  
 *  Discussion:
 *    Creates IconRef based on componentIconFamily field of component's
 *    'thng' resource.. This routine increments the reference count of
 *    the IconRef. Call ReleaseIconRef() when you're done with it.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    inComponent:
 *      A component identifier.
 *    
 *    outIconRef:
 *      The output IconRef for the routine.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.5 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetIconRefFromComponent(
  Component   inComponent,
  IconRef *   outIconRef)                                     __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);


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
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
RegisterIconRefFromIconFamily(
  OSType             creator,
  OSType             iconType,
  IconFamilyHandle   iconFamily,
  IconRef *          theIconRef)                              __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
   RegisterIconRefFromResource
   
   Registers an IconRef from a resouce file.  
   Lower-case creators are reserved for the system.
   The icon data to be fetched is either classic icon data or an icon family.  
   The 'icns' icon family is searched for before the classic icon data.
   This routine increments the reference count of the IconRef. Call ReleaseIconRef() 
   when you're done with it.
*/

#if !__LP64__
/*
 *  RegisterIconRefFromResource()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
RegisterIconRefFromResource(
  OSType          creator,
  OSType          iconType,
  const FSSpec *  resourceFile,
  SInt16          resourceID,
  IconRef *       theIconRef)                                 __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_5, __IPHONE_NA, __IPHONE_NA);


/* RegisterIconRefFromFSRef*/
#endif  /* !__LP64__ */

/*
 *  RegisterIconRefFromFSRef()
 *  
 *  Discussion:
 *    This routine registers an IconRef from a ".icns" file and
 *    associates it with a creator/type pair.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
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
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
RegisterIconRefFromFSRef(
  OSType         creator,
  OSType         iconType,
  const FSRef *  iconFile,
  IconRef *      theIconRef)                                  __OSX_AVAILABLE_STARTING(__MAC_10_1, __IPHONE_NA);


/*
   UnregisterIconRef
   
   Removes the specified icon from the icon cache (if there are no users of it).  
   If some clients are using this iconRef, then the IconRef will be removed when the 
   last user calls ReleaseIconRef.
*/

/*
 *  UnregisterIconRef()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
UnregisterIconRef(
  OSType   creator,
  OSType   iconType)                                          __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




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
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
UpdateIconRef(IconRef theIconRef)                             __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




/*
   OverrideIconRefFromResource
   
   This routines replaces the bitmaps of the specified IconRef with the ones
   in the specified resource file.
*/

#if !__LP64__
/*
 *  OverrideIconRefFromResource()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
OverrideIconRefFromResource(
  IconRef         theIconRef,
  const FSSpec *  resourceFile,
  SInt16          resourceID)                                 __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_5, __IPHONE_NA, __IPHONE_NA);




/*
   OverrideIconRef
   
   This routines replaces the bitmaps of the specified IconRef with the ones
   from the new IconRef.
*/

#endif  /* !__LP64__ */

/*
 *  OverrideIconRef()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
OverrideIconRef(
  IconRef   oldIconRef,
  IconRef   newIconRef)                                       __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
   RemoveIconRefOverride
   This routine remove an override if one was applied to the icon and 
   reverts back to the original bitmap data.
*/

/*
 *  RemoveIconRefOverride()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
RemoveIconRefOverride(IconRef theIconRef)                     __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




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
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
CompositeIconRef(
  IconRef    backgroundIconRef,
  IconRef    foregroundIconRef,
  IconRef *  compositeIconRef)                                __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
   IsIconRefComposite
   Indicates if a given icon ref is a composite of two other icon refs (and which ones)
   If it isn't a composite, backgroundIconRef and foreGroundIconRef will be 0.
*/

/*
 *  IsIconRefComposite()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
IsIconRefComposite(
  IconRef    compositeIconRef,
  IconRef *  backgroundIconRef,
  IconRef *  foregroundIconRef)                               __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);




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
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern Boolean 
IsValidIconRef(IconRef theIconRef)                            __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/* IsDataAvailableInIconRef*/
/*
 *  IsDataAvailableInIconRef()
 *  
 *  Summary:
 *    Check if IconRef has specific data.
 *  
 *  Discussion:
 *    This routine returns true if inIconKind icon data is availabe or
 *    can be created.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Parameters:
 *    
 *    inIconKind:
 *      The icon data kind
 *    
 *    inIconRef:
 *      The IconRef to test.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.3 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
IsDataAvailableInIconRef(
  OSType    inIconKind,
  IconRef   inIconRef)                                        __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);


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

#if !__LP64__
/*
 *  FlushIconRefs()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
FlushIconRefs(
  OSType   creator,
  OSType   iconType)                                          __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_3, __IPHONE_NA, __IPHONE_NA);



/*
   FlushIconRefsByVolume
   
   This routine disposes of the data for the icons related to the indicated volume
   if this data can be reacquired, for example if the data is provided from a 
   resource.
*/

/*
 *  FlushIconRefsByVolume()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
FlushIconRefsByVolume(SInt16 vRefNum)                         __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_3, __IPHONE_NA, __IPHONE_NA);




/*
  ==============================================================================
   Controling custom icons
  ==============================================================================
*/


/*
   SetCustomIconsEnabled
   
   Enable or disable custom icons on the specified volume.
*/

#endif  /* !__LP64__ */

/*
 *  SetCustomIconsEnabled()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
SetCustomIconsEnabled(
  SInt16    vRefNum,
  Boolean   enableCustomIcons)                                __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
   GetCustomIconsEnabled
   
   Return true if custom icons are enabled on the specified volume, false otherwise.
*/

/*
 *  GetCustomIconsEnabled()
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 8.5 and later
 */
extern OSErr 
GetCustomIconsEnabled(
  SInt16     vRefNum,
  Boolean *  customIconsEnabled)                              __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



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

#if !__LP64__
/*
 *  RegisterIconRefFromIconFile()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Thread safe since version Jagua
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 9.0 and later
 */
extern OSErr 
RegisterIconRefFromIconFile(
  OSType          creator,
  OSType          iconType,
  const FSSpec *  iconFile,
  IconRef *       theIconRef)                                 __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_5, __IPHONE_NA, __IPHONE_NA);



/*
   ReadIconFile
   Read the specified icon file into the icon family handle.
   The caller is responsible for disposing the iconFamily
*/

/*
 *  ReadIconFile()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 9.0 and later
 */
extern OSErr 
ReadIconFile(
  const FSSpec *      iconFile,
  IconFamilyHandle *  iconFamily)                             __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_5, __IPHONE_NA, __IPHONE_NA);



/*
   WriteIconFile
   Write the iconFamily handle to the specified file
*/

/*
 *  WriteIconFile()   *** DEPRECATED ***
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in IconServicesLib 9.0 and later
 */
extern OSErr 
WriteIconFile(
  IconFamilyHandle   iconFamily,
  const FSSpec *     iconFile)                                __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_5, __IPHONE_NA, __IPHONE_NA);



/* ReadIconFromFSRef*/
#endif  /* !__LP64__ */

/*
 *  ReadIconFromFSRef()
 *  
 *  Discussion:
 *    This routine reads an icon (icns) file into memory.
 *  
 *  Mac OS X threading:
 *    Not thread safe
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
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ReadIconFromFSRef(
  const FSRef *       ref,
  IconFamilyHandle *  iconFamily)                             __OSX_AVAILABLE_STARTING(__MAC_10_1, __IPHONE_NA);



#ifdef __cplusplus
}
#endif

#endif /* __ICONSCORE__ */

