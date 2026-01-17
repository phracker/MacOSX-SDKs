/*
     File:       CarbonCore/Folders.h
 
     Contains:   Folder Manager Interfaces.
 
     Version:    CarbonCore-682.26~1
 
     Copyright:  © 1995-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __FOLDERS__
#define __FOLDERS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint off
#endif

enum {
  kOnSystemDisk                 = -32768L, /* previously was 0x8000 but that is an unsigned value whereas vRefNum is signed*/
  kOnAppropriateDisk            = -32767, /* Generally, the same as kOnSystemDisk, but it's clearer that this isn't always the 'boot' disk.*/
                                        /* Folder Domains - Carbon only.  The constants above can continue to be used, but the folder/volume returned will*/
                                        /* be from one of the domains below.*/
  kSystemDomain                 = -32766, /* Read-only system hierarchy.*/
  kLocalDomain                  = -32765, /* All users of a single machine have access to these resources.*/
  kNetworkDomain                = -32764, /* All users configured to use a common network server has access to these resources.*/
  kUserDomain                   = -32763, /* Read/write. Resources that are private to the user.*/
  kClassicDomain                = -32762 /* Domain referring to the currently configured Classic System Folder*/
};

/*
   The ID of the last domain in the above list, used by the Folder Manager to determine if a given 
   parameter should be treated as a domain or a volume...
*/
enum {
  kLastDomainConstant           = -32761
};

enum {
  kCreateFolder                 = true,
  kDontCreateFolder             = false
};

enum {
  kSystemFolderType             = 'macs', /* the system folder */
  kDesktopFolderType            = 'desk', /* the desktop folder; objects in this folder show on the desk top. */
  kSystemDesktopFolderType      = 'sdsk', /* the desktop folder at the root of the hard drive, never the redirected user desktop folder */
  kTrashFolderType              = 'trsh', /* the trash folder; objects in this folder show up in the trash */
  kSystemTrashFolderType        = 'strs', /* the trash folder at the root of the drive, never the redirected user trash folder */
  kWhereToEmptyTrashFolderType  = 'empt', /* the "empty trash" folder; Finder starts empty from here down */
  kPrintMonitorDocsFolderType   = 'prnt', /* Print Monitor documents */
  kStartupFolderType            = 'strt', /* Finder objects (applications, documents, DAs, aliases, to...) to open at startup go here */
  kShutdownFolderType           = 'shdf', /* Finder objects (applications, documents, DAs, aliases, to...) to open at shutdown go here */
  kAppleMenuFolderType          = 'amnu', /* Finder objects to put into the Apple menu go here */
  kControlPanelFolderType       = 'ctrl', /* Control Panels go here (may contain INITs) */
  kSystemControlPanelFolderType = 'sctl', /* System control panels folder - never the redirected one, always "Control Panels" inside the System Folder */
  kExtensionFolderType          = 'extn', /* System extensions go here */
  kFontsFolderType              = 'font', /* Fonts go here */
  kPreferencesFolderType        = 'pref', /* preferences for applications go here */
  kSystemPreferencesFolderType  = 'sprf', /* System-type Preferences go here - this is always the system's preferences folder, never a logged in user's */
                                        /*    On Mac OS X, items in the temporary items folder on the boot volume will be deleted a certain amount of time after their*/
                                        /*    last access.  On non-boot volumes, items in the temporary items folder may never get deleted.  Thus, the use of the*/
                                        /*    temporary items folder on Mac OS X is discouraged, especially for long lived data.  Using this folder temporarily ( like*/
                                        /*    to write a temporary copy of a document to during a save, after which you FSpExchangeFiles() to swap the new contents with*/
                                        /*    the old version ) is certainly ok, but using the temporary items folder to cache data is not a good idea.  Instead, look*/
                                        /*    at tmpfile() and its cousins for a better way to do this kind of thing.  On Mac OS X 10.4 and later, this folder is inside a*/
                                        /*    folder named ".TemporaryItems" and in earlier versions of Mac OS X this folder is inside a folder named "Temporary Items".*/
                                        /*    On Mac OS 9.x, items in the the Temporary Items folder are never automatically deleted.  Instead, when a 9.x machine boots*/
                                        /*    up the temporary items folder on a volume ( if one still exists, and is not empty ) is moved into the trash folder on the*/
                                        /*    same volume and renamed "Rescued Items from <diskname>".   */
  kTemporaryFolderType          = 'temp' /* temporary files go here (deleted periodically, but don't rely on it.) */
};


/*
 *  FindFolder()
 *  
 *  Summary:
 *    Obtains location information for system-related directories.
 *  
 *  Discussion:
 *    For the folder type on the particular volume (specified,
 *    respectively, in the folderType and vRefNum parameters), the
 *    FindFolder function returns the directory's volume reference
 *    number in the foundVRefNum parameter and its directory ID in the
 *    foundDirID parameter.
 *    
 *    The specified folder used for a given volume might be located on
 *    a different volume in future versions of system software;
 *    therefore, do not assume the volume that you specify in vRefNum
 *    and the volume returned in foundVRefNum will be the same.
 *     
 *    Specify a volume reference number (or the constant kOnSystemDisk
 *    for the startup disk) or one of the domain constants ( on Mac OS
 *    X ) in the vRefNum parameter.
 *    
 *    Specify a four-character folder type--or the constant that
 *    represents it--in the folderType parameter.
 *    
 *    Use the constant kCreateFolder in the createFolder parameter to
 *    tell FindFolder to create a directory if it does not already
 *    exist; otherwise, use the constant kDontCreateFolder. Directories
 *    inside the System Folder are created only if the System Folder
 *    directory exists. The FindFolder function will not create a
 *    System Folder directory even if you specify the kCreateFolder
 *    constant in the createFolder parameter.
 *    
 *    The FindFolder function returns a nonzero result code if the
 *    folder isn't found, and it can also return other file system
 *    errors reported by the File Manager or Memory Manager.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    vRefNum:
 *      Pass the volume reference number of the volume on which you
 *      want to locate a directory, or a constant specifying a disk or
 *      domain.   The constants which you can use in this parameter are
 *      described in "Disk and Domain Constants".
 *      Note that, on Mac OS X, passing a volume reference number in
 *      this parameter does not make sense for most of the folder type
 *      selectors which you can specify in the folderType parameter. On
 *      Mac OS X, folders are "domain-oriented"; because there may be
 *      more than one domain on any given physical volume, asking for
 *      these folders on a per-volume basis yields undefined results.
 *      For example, if you were to request the Fonts folder
 *      (represented by the selector kFontsFolderType ) on volume -100,
 *      are you requesting the folder /System/Library/Fonts,
 *      /Library/Fonts, or ~/Fonts? On Mac OS X you should pass a disk
 *      or domain constant in this parameter.
 *    
 *    folderType:
 *      A four-character folder type, or a constant that represents the
 *      type, for the directory you want to find.
 *    
 *    createFolder:
 *      Pass the constant kCreateFolder in this parameter to create a
 *      directory if it does not already exist; otherwise, pass the
 *      constant kDontCreateFolder.
 *    
 *    foundVRefNum:
 *      The volume reference number, returned by FindFolder , for the
 *      volume containing the directory you specify in the folderType
 *      parameter.
 *    
 *    foundDirID:
 *      The directory ID number, returned by FindFolder , for the
 *      directory you specify in the folderType parameter.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FindFolder(
  short     vRefNum,
  OSType    folderType,
  Boolean   createFolder,
  short *   foundVRefNum,
  long *    foundDirID)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  FindFolderExtended()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use FindFolder instead wherever possible.
 *  
 *  Summary:
 *    Obtains location information for system-related directories.
 *  
 *  Discussion:
 *    For the folder type on the particular volume (specified,
 *    respectively, in the folderType and vRefNum parameters), the
 *    FindFolder function returns the directory's volume reference
 *    number in the foundVRefNum parameter and its directory ID in the
 *    foundDirID parameter.
 *    
 *    The specified folder used for a given volume might be located on
 *    a different volume in future versions of system software;
 *    therefore, do not assume the volume that you specify in vRefNum
 *    and the volume returned in foundVRefNum will be the same.
 *     
 *    Specify a volume reference number (or the constant kOnSystemDisk
 *    for the startup disk) or one of the domain constants ( on Mac OS
 *    X ) in the vRefNum parameter.
 *    
 *    Specify a four-character folder type--or the constant that
 *    represents it--in the folderType parameter.
 *    
 *    Use the constant kCreateFolder in the createFolder parameter to
 *    tell FindFolder to create a directory if it does not already
 *    exist; otherwise, use the constant kDontCreateFolder. Directories
 *    inside the System Folder are created only if the System Folder
 *    directory exists. The FindFolder function will not create a
 *    System Folder directory even if you specify the kCreateFolder
 *    constant in the createFolder parameter.
 *    
 *    The FindFolder function returns a nonzero result code if the
 *    folder isn't found, and it can also return other file system
 *    errors reported by the File Manager or Memory Manager.
 *     FindFolderExtended() is equivalent to FindFolder() on Mac OS X.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    vRefNum:
 *      The volume reference number (or the constant kOnSystemDisk for
 *      the startup disk) or one of the domain constants ( like
 *      kUserDomain ) of the volume or domain in which you want to
 *      locate a directory.
 *    
 *    folderType:
 *      A four-character folder type, or a constant that represents the
 *      type, for the directory you want to find.
 *    
 *    createFolder:
 *      Pass the constant kCreateFolder in this parameter to create a
 *      directory if it does not already exist; otherwise, pass the
 *      constant kDontCreateFolder.
 *    
 *    foundVRefNum:
 *      The volume reference number, returned by FindFolder , for the
 *      volume containing the directory you specify in the folderType
 *      parameter.
 *    
 *    flags:
 *      The flags passed in which control extended behaviour
 *    
 *    data:
 *      Unique data which is interpreted differently depending on the
 *      passed in flags.
 *    
 *    foundDirID:
 *      The directory ID number, returned by FindFolder , for the
 *      directory you specify in the folderType parameter.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FindFolderExtended(
  short     vRefNum,
  OSType    folderType,
  Boolean   createFolder,
  UInt32    flags,
  void *    data,
  short *   foundVRefNum,
  long *    foundDirID)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3;


/*
 *  ReleaseFolder()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This call is not needed on Mac OS X and later.
 *  
 *  Summary:
 *    On Mac OS 9.x and earlier, release any hold the system may have
 *    on a given folder on a volume so that the volume may be unmounted.
 *  
 *  Discussion:
 *    On Mac OS 9.x, the system sometimes has files open on volumes
 *    which need to be closed in order for the volume to be
 *    successfully unmounted.  This call releases any hold the Folder
 *    Manager may have for the given volume.
 *    <br> This call is unnecessary on Mac OS X and later.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    vRefNum:
 *      The vRefNum to release.
 *    
 *    folderType:
 *      The folder type to release.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
ReleaseFolder(
  short    vRefNum,
  OSType   folderType)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3;



/*
 *  FSFindFolder()
 *  
 *  Summary:
 *    FSFindFolder returns an FSRef for certain system-related
 *    directories.
 *  
 *  Discussion:
 *    For the folder type on the particular volume (specified,
 *    respectively, in the folderType and vRefNum parameters), the
 *    FindFolder function returns the FSRef of that directory. 
 *     
 *    The specified folder used for a given volume might be located on
 *    a different volume in future versions of system software;
 *    therefore, do not assume the volume that you specify in vRefNum
 *    and the volume returned in the FSRef will be the same.
 *    
 *    Specify a volume reference number (or the constant kOnSystemDisk
 *    for the startup disk) or one of the domain constants ( on Mac OS
 *    X ) in the vRefNum parameter.
 *    
 *    Specify a four-character folder type--or the constant that
 *    represents it--in the folderType parameter.
 *    
 *    Use the constant kCreateFolder in the createFolder parameter to
 *    tell FindFolder to create a directory if it does not already
 *    exist; otherwise, use the constant kDontCreateFolder. Directories
 *    inside the System Folder are created only if the System Folder
 *    directory exists. The FindFolder function will not create a
 *    System Folder directory even if you specify the kCreateFolder
 *    constant in the createFolder parameter.
 *    
 *    The FindFolder function returns a nonzero result code if the
 *    folder isn't found, and it can also return other file system
 *    errors reported by the File Manager or Memory Manager.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    vRefNum:
 *      The volume reference number (or the constant kOnSystemDisk for
 *      the startup disk) or one of the domain constants ( like
 *      kUserDomain ) of the volume or domain in which you want to
 *      locate a directory.
 *    
 *    folderType:
 *      A four-character folder type, or a constant that represents the
 *      type, for the directory you want to find.
 *    
 *    createFolder:
 *      Pass the constant kCreateFolder in this parameter to create a
 *      directory if it does not already exist; otherwise, pass the
 *      constant kDontCreateFolder.
 *    
 *    foundRef:
 *      The FSRef for the directory you specify on the volume or domain
 *      and folderType given.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
FSFindFolder(
  short     vRefNum,
  OSType    folderType,
  Boolean   createFolder,
  FSRef *   foundRef)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  FSFindFolderExtended()   *** DEPRECATED ***
 *  
 *  Summary:
 *    FSFindFolderExtended returns an FSRef for certain system-related
 *    directories.
 *  
 *  Discussion:
 *    For the folder type on the particular volume (specified,
 *    respectively, in the folderType and vRefNum parameters), the
 *    FindFolder function returns the FSRef of that directory. 
 *     
 *    The specified folder used for a given volume might be located on
 *    a different volume in future versions of system software;
 *    therefore, do not assume the volume that you specify in vRefNum
 *    and the volume returned in the FSRef will be the same.
 *    
 *    Specify a volume reference number (or the constant kOnSystemDisk
 *    for the startup disk) or one of the domain constants ( on Mac OS
 *    X ) in the vRefNum parameter.
 *    
 *    Specify a four-character folder type--or the constant that
 *    represents it--in the folderType parameter.
 *    
 *    Use the constant kCreateFolder in the createFolder parameter to
 *    tell FindFolder to create a directory if it does not already
 *    exist; otherwise, use the constant kDontCreateFolder. Directories
 *    inside the System Folder are created only if the System Folder
 *    directory exists. The FindFolder function will not create a
 *    System Folder directory even if you specify the kCreateFolder
 *    constant in the createFolder parameter.
 *    
 *    The FindFolder function returns a nonzero result code if the
 *    folder isn't found, and it can also return other file system
 *    errors reported by the File Manager or Memory Manager.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    vRefNum:
 *      The volume reference number (or the constant kOnSystemDisk for
 *      the startup disk) or one of the domain constants ( like
 *      kUserDomain ) of the volume or domain in which you want to
 *      locate a directory.
 *    
 *    folderType:
 *      A four-character folder type, or a constant that represents the
 *      type, for the directory you want to find.
 *    
 *    createFolder:
 *      Pass the constant kCreateFolder in this parameter to create a
 *      directory if it does not already exist; otherwise, pass the
 *      constant kDontCreateFolder.
 *    
 *    flags:
 *      The flags passed in which control extended behaviour
 *    
 *    data:
 *      Unique data which is interpreted differently depending on the
 *      passed in flags.
 *    
 *    foundRef:
 *      The FSRef for the directory you specify on the volume or domain
 *      and folderType given.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
FSFindFolderExtended(
  short     vRefNum,
  OSType    folderType,
  Boolean   createFolder,
  UInt32    flags,
  void *    data,
  FSRef *   foundRef)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3;



/******************************************/
/* Extensible Folder Manager declarations */
/******************************************/

/****************************/
/* Folder Manager constants */
/****************************/

enum {
  kExtensionDisabledFolderType  = 'extD',
  kControlPanelDisabledFolderType = 'ctrD',
  kSystemExtensionDisabledFolderType = 'macD',
  kStartupItemsDisabledFolderType = 'strD',
  kShutdownItemsDisabledFolderType = 'shdD',
  kApplicationsFolderType       = 'apps',
  kDocumentsFolderType          = 'docs'
};

enum {
                                        /* new constants */
  kVolumeRootFolderType         = 'root', /* root folder of a volume */
  kChewableItemsFolderType      = 'flnt', /* items deleted at boot */
  kApplicationSupportFolderType = 'asup', /* third-party items and folders */
  kTextEncodingsFolderType      = 0xC4746578/*'Ätex'*/, /* encoding tables */
  kStationeryFolderType         = 'odst', /* stationery */
  kOpenDocFolderType            = 'odod', /* OpenDoc root */
  kOpenDocShellPlugInsFolderType = 'odsp', /* OpenDoc Shell Plug-Ins in OpenDoc folder */
  kEditorsFolderType            = 'oded', /* OpenDoc editors in MacOS Folder */
  kOpenDocEditorsFolderType     = 0xC46F6466/*'Äodf'*/, /* OpenDoc subfolder of Editors folder */
  kOpenDocLibrariesFolderType   = 'odlb', /* OpenDoc libraries folder */
  kGenEditorsFolderType         = 0xC4656469/*'Äedi'*/, /* CKH general editors folder at root level of Sys folder */
  kHelpFolderType               = 0xC4686C70/*'Ählp'*/, /* CKH help folder currently at root of system folder */
  kInternetPlugInFolderType     = 0xC46E6574/*'Änet'*/, /* CKH internet plug ins for browsers and stuff */
  kModemScriptsFolderType       = 0xC46D6F64/*'Ämod'*/, /* CKH modem scripts, get 'em OUT of the Extensions folder */
  kPrinterDescriptionFolderType = 'ppdf', /* CKH new folder at root of System folder for printer descs. */
  kPrinterDriverFolderType      = 0xC4707264/*'Äprd'*/, /* CKH new folder at root of System folder for printer drivers */
  kScriptingAdditionsFolderType = 0xC4736372/*'Äscr'*/, /* CKH at root of system folder */
  kSharedLibrariesFolderType    = 0xC46C6962/*'Älib'*/, /* CKH for general shared libs. */
  kVoicesFolderType             = 'fvoc', /* CKH macintalk can live here */
  kControlStripModulesFolderType = 'sdev', /* CKH for control strip modules */
  kAssistantsFolderType         = 0x617374C4/*'astÄ'*/, /* SJF for Assistants (MacOS Setup Assistant, etc) */
  kUtilitiesFolderType          = 0x757469C4/*'utiÄ'*/, /* SJF for Utilities folder */
  kAppleExtrasFolderType        = 0x616578C4/*'aexÄ'*/, /* SJF for Apple Extras folder */
  kContextualMenuItemsFolderType = 'cmnu', /* SJF for Contextual Menu items */
  kMacOSReadMesFolderType       = 0x6D6F72C4/*'morÄ'*/, /* SJF for MacOS ReadMes folder */
  kALMModulesFolderType         = 'walk', /* EAS for Location Manager Module files except type 'thng' (within kExtensionFolderType) */
  kALMPreferencesFolderType     = 'trip', /* EAS for Location Manager Preferences (within kPreferencesFolderType; contains kALMLocationsFolderType) */
  kALMLocationsFolderType       = 'fall', /* EAS for Location Manager Locations (within kALMPreferencesFolderType) */
  kColorSyncProfilesFolderType  = 'prof', /* for ColorSyncª Profiles */
  kThemesFolderType             = 'thme', /* for Theme data files */
  kFavoritesFolderType          = 'favs', /* Favorties folder for Navigation Services */
  kInternetFolderType           = 0x696E74C4/*'intÄ'*/, /* Internet folder (root level of startup volume) */
  kAppearanceFolderType         = 'appr', /* Appearance folder (root of system folder) */
  kSoundSetsFolderType          = 'snds', /* Sound Sets folder (in Appearance folder) */
  kDesktopPicturesFolderType    = 0x647470C4/*'dtpÄ'*/, /* Desktop Pictures folder (in Appearance folder) */
  kInternetSearchSitesFolderType = 'issf', /* Internet Search Sites folder */
  kFindSupportFolderType        = 'fnds', /* Find support folder */
  kFindByContentFolderType      = 'fbcf', /* Find by content folder */
  kInstallerLogsFolderType      = 'ilgf', /* Installer Logs folder */
  kScriptsFolderType            = 0x736372C4/*'scrÄ'*/, /* Scripts folder */
  kFolderActionsFolderType      = 'fasf', /* Folder Actions Scripts folder */
  kLauncherItemsFolderType      = 'laun', /* Launcher Items folder */
  kRecentApplicationsFolderType = 'rapp', /* Recent Applications folder */
  kRecentDocumentsFolderType    = 'rdoc', /* Recent Documents folder */
  kRecentServersFolderType      = 'rsvr', /* Recent Servers folder */
  kSpeakableItemsFolderType     = 'spki', /* Speakable Items folder */
  kKeychainFolderType           = 'kchn', /* Keychain folder */
  kQuickTimeExtensionsFolderType = 'qtex', /* QuickTime Extensions Folder (in Extensions folder) */
  kDisplayExtensionsFolderType  = 'dspl', /* Display Extensions Folder (in Extensions folder) */
  kMultiprocessingFolderType    = 'mpxf', /* Multiprocessing Folder (in Extensions folder) */
  kPrintingPlugInsFolderType    = 'pplg' /* Printing Plug-Ins Folder (in Extensions folder) */
};


/* New Folder Types to accommodate the Mac OS X Folder Manager */
/* These folder types are not applicable on Mac OS 9.          */
enum {
  kDomainTopLevelFolderType     = 'dtop', /* The top-level of a Folder domain, e.g. "/System"*/
  kDomainLibraryFolderType      = 'dlib', /* the Library subfolder of a particular domain*/
  kColorSyncFolderType          = 'sync', /* Contains ColorSync-related folders*/
  kColorSyncCMMFolderType       = 'ccmm', /* ColorSync CMMs*/
  kColorSyncScriptingFolderType = 'cscr', /* ColorSync Scripting support*/
  kPrintersFolderType           = 'impr', /* Contains Printing-related folders*/
  kSpeechFolderType             = 'spch', /* Contains Speech-related folders*/
  kCarbonLibraryFolderType      = 'carb', /* Contains Carbon-specific file*/
  kDocumentationFolderType      = 'info', /* Contains Documentation files (not user documents)*/
  kDeveloperDocsFolderType      = 'ddoc', /* Contains Developer Documentation files and folders*/
  kDeveloperHelpFolderType      = 'devh', /* Contains Developer Help related files*/
  kISSDownloadsFolderType       = 'issd', /* Contains Internet Search Sites downloaded from the Internet*/
  kUserSpecificTmpFolderType    = 'utmp', /* Contains temporary items created on behalf of the current user*/
  kCachedDataFolderType         = 'cach', /* Contains various cache files for different clients*/
  kTemporaryItemsInCacheDataFolderType = 'vtmp',
  kMagicTemporaryItemsFolderType = 'mtmp',
  kFrameworksFolderType         = 'fram', /* Contains MacOS X Framework folders*/
  kPrivateFrameworksFolderType  = 'pfrm', /* Contains MacOS X Private Framework folders     */
  kClassicDesktopFolderType     = 'sdsk', /* MacOS 9 compatible desktop folder - same as */
                                        /* kSystemDesktopFolderType but with a more appropriate*/
                                        /* name for Mac OS X code.*/
  kDeveloperFolderType          = 'devf', /* Contains MacOS X Developer Resources*/
  kSystemSoundsFolderType       = 'ssnd', /* Contains Mac OS X System Sound Files ( valid in kSystemDomain, kLocalDomain, and kUserDomain )*/
  kComponentsFolderType         = 'cmpd', /* Contains Mac OS X components   ( valid in kSystemDomain, kLocalDomain, and kUserDomain )*/
  kQuickTimeComponentsFolderType = 'wcmp', /* Contains QuickTime components for Mac OS X ( valid in kSystemDomain, kLocalDomain, and kUserDomain )*/
  kCoreServicesFolderType       = 'csrv', /* Refers to the "CoreServices" folder on Mac OS X*/
  kPictureDocumentsFolderType   = 'pdoc', /* Refers to the "Pictures" folder in a users home directory*/
  kMovieDocumentsFolderType     = 'mdoc', /* Refers to the "Movies" folder in a users home directory*/
  kMusicDocumentsFolderType     = 0xB5646F63/*'µdoc'*/, /* Refers to the "Music" folder in a users home directory*/
  kInternetSitesFolderType      = 'site', /* Refers to the "Sites" folder in a users home directory*/
  kPublicFolderType             = 'pubb', /* Refers to the "Public" folder in a users home directory*/
  kAudioSupportFolderType       = 'adio', /* Refers to the Audio support folder for Mac OS X*/
  kAudioPresetsFolderType       = 'apst', /* "Presets" folder of "Audio" folder, Mac OS X 10.4 and later*/
  kAudioSoundsFolderType        = 'asnd', /* Refers to the Sounds subfolder of Audio Support*/
  kAudioSoundBanksFolderType    = 'bank', /* Refers to the Banks subfolder of the Sounds Folder*/
  kAudioAlertSoundsFolderType   = 'alrt', /* Refers to the Alert Sounds subfolder of the Sound Folder*/
  kAudioPlugInsFolderType       = 'aplg', /* Refers to the Plug-ins subfolder of the Audio Folder   */
  kAudioComponentsFolderType    = 'acmp', /* Refers to the Components subfolder of the Audio Plug-ins Folder    */
  kKernelExtensionsFolderType   = 'kext', /* Refers to the Kernel Extensions Folder on Mac OS X*/
  kDirectoryServicesFolderType  = 'dsrv', /* Refers to the Directory Services folder on Mac OS X*/
  kDirectoryServicesPlugInsFolderType = 'dplg', /* Refers to the Directory Services Plug-Ins folder on Mac OS X */
  kInstallerReceiptsFolderType  = 'rcpt', /* Refers to the "Receipts" folder in Mac OS X*/
  kFileSystemSupportFolderType  = 'fsys', /* Refers to the [domain]/Library/Filesystems folder in Mac OS X*/
  kAppleShareSupportFolderType  = 'shar', /* Refers to the [domain]/Library/Filesystems/AppleShare folder in Mac OS X*/
  kAppleShareAuthenticationFolderType = 'auth', /* Refers to the [domain]/Library/Filesystems/AppleShare/Authentication folder in Mac OS X*/
  kMIDIDriversFolderType        = 'midi', /* Refers to the MIDI Drivers folder on Mac OS X*/
  kKeyboardLayoutsFolderType    = 'klay', /* Refers to the [domain]/Library/KeyboardLayouts folder in Mac OS X*/
  kIndexFilesFolderType         = 'indx', /* Refers to the [domain]/Library/Indexes folder in Mac OS X*/
  kFindByContentIndexesFolderType = 'fbcx', /* Refers to the [domain]/Library/Indexes/FindByContent folder in Mac OS X*/
  kManagedItemsFolderType       = 'mang', /* Refers to the Managed Items folder for Mac OS X */
  kBootTimeStartupItemsFolderType = 'empz' /* Refers to the "StartupItems" folder of Mac OS X */
};

enum {
  kLocalesFolderType            = 0xC46C6F63/*'Äloc'*/, /* PKE for Locales folder */
  kFindByContentPluginsFolderType = 'fbcp' /* Find By Content Plug-ins */
};

enum {
  kUsersFolderType              = 'usrs', /* "Users" folder, contains one folder for each user. */
  kCurrentUserFolderType        = 'cusr', /* The folder for the currently logged on user. */
  kCurrentUserRemoteFolderLocation = 'rusf', /* The remote folder for the currently logged on user */
  kCurrentUserRemoteFolderType  = 'rusr', /* The remote folder location for the currently logged on user */
  kSharedUserDataFolderType     = 'sdat', /* A Shared "Documents" folder, readable & writeable by all users */
  kVolumeSettingsFolderType     = 'vsfd' /* Volume specific user information goes here */
};

enum {
  kClassicPreferencesFolderType = 'cprf' /* "Classic" folder in ~/Library/ for redirected preference files. */
};

enum {
  kAppleshareAutomountServerAliasesFolderType = 0x737276C4/*'srvÄ'*/, /* Appleshare puts volumes to automount inside this folder. */
  kPreMacOS91ApplicationsFolderType = 0x8C707073/*'Œpps'*/, /* The "Applications" folder, pre Mac OS 9.1 */
  kPreMacOS91InstallerLogsFolderType = 0x946C6766/*'”lgf'*/, /* The "Installer Logs" folder, pre Mac OS 9.1 */
  kPreMacOS91AssistantsFolderType = 0x8C7374C4/*'ŒstÄ'*/, /* The "Assistants" folder, pre Mac OS 9.1 */
  kPreMacOS91UtilitiesFolderType = 0x9F7469C4/*'ŸtiÄ'*/, /* The "Utilities" folder, pre Mac OS 9.1 */
  kPreMacOS91AppleExtrasFolderType = 0x8C6578C4/*'ŒexÄ'*/, /* The "Apple Extras" folder, pre Mac OS 9.1 */
  kPreMacOS91MacOSReadMesFolderType = 0xB56F72C4/*'µorÄ'*/, /* The "Mac OS ReadMes" folder, pre Mac OS 9.1 */
  kPreMacOS91InternetFolderType = 0x946E74C4/*'”ntÄ'*/, /* The "Internet" folder, pre Mac OS 9.1 */
  kPreMacOS91AutomountedServersFolderType = 0xA77276C4/*'§rvÄ'*/, /* The "Servers" folder, pre Mac OS 9.1 */
  kPreMacOS91StationeryFolderType = 0xBF647374/*'¿dst'*/ /* The "Stationery" folder, pre Mac OS 9.1 */
};

enum {
  kTemporaryItemsInUserDomainFolderType = 'temq',
  kAutosaveInformationFolderType = 'asav', /* ~/Library/Autosaved Information/ folder, used to store autosave information for user's applications.  Available in Mac OS X 10.4 and later.  */
  kSpotlightSavedSearchesFolderType = 'spot', /* Usually ~/Library/Saved Searches/; used by Finder and Nav/Cocoa panels to find saved Spotlight searches */
  kAutomatorWorkflowsFolderType = 'flow' /* Automator Workflows folder */
};

/* FolderDescFlags values */
enum {
  kCreateFolderAtBoot           = 0x00000002,
  kCreateFolderAtBootBit        = 1,
  kFolderCreatedInvisible       = 0x00000004,
  kFolderCreatedInvisibleBit    = 2,
  kFolderCreatedNameLocked      = 0x00000008,
  kFolderCreatedNameLockedBit   = 3,
  kFolderCreatedAdminPrivs      = 0x00000010,
  kFolderCreatedAdminPrivsBit   = 4
};

enum {
  kFolderInUserFolder           = 0x00000020,
  kFolderInUserFolderBit        = 5,
  kFolderTrackedByAlias         = 0x00000040,
  kFolderTrackedByAliasBit      = 6,
  kFolderInRemoteUserFolderIfAvailable = 0x00000080,
  kFolderInRemoteUserFolderIfAvailableBit = 7,
  kFolderNeverMatchedInIdentifyFolder = 0x00000100,
  kFolderNeverMatchedInIdentifyFolderBit = 8,
  kFolderMustStayOnSameVolume   = 0x00000200,
  kFolderMustStayOnSameVolumeBit = 9,
  kFolderManagerFolderInMacOS9FolderIfMacOSXIsInstalledMask = 0x00000400,
  kFolderManagerFolderInMacOS9FolderIfMacOSXIsInstalledBit = 10,
  kFolderInLocalOrRemoteUserFolder = kFolderInUserFolder | kFolderInRemoteUserFolderIfAvailable,
  kFolderManagerNotCreatedOnRemoteVolumesBit = 11,
  kFolderManagerNotCreatedOnRemoteVolumesMask = (1 << kFolderManagerNotCreatedOnRemoteVolumesBit),
  kFolderManagerNewlyCreatedFolderIsLocalizedBit = 12,
  kFolderManagerNewlyCreatedFolderShouldHaveDotLocalizedCreatedWithinMask = (1 << kFolderManagerNewlyCreatedFolderIsLocalizedBit)
};

typedef UInt32                          FolderDescFlags;
/* FolderClass values */
enum {
  kRelativeFolder               = 'relf',
  kRedirectedRelativeFolder     = 'rrel',
  kSpecialFolder                = 'spcf'
};

typedef OSType                          FolderClass;
/* special folder locations */
enum {
  kBlessedFolder                = 'blsf',
  kRootFolder                   = 'rotf'
};

enum {
  kCurrentUserFolderLocation    = 'cusf' /*    the magic 'Current User' folder location*/
};


enum {
  kDictionariesFolderType       = 'dict', /* Dictionaries folder */
  kLogsFolderType               = 'logs', /* Logs folder */
  kDeveloperApplicationsFolderType = 'dapp', /* Contains Developer Applications*/
  kPreferencePanesFolderType    = 'ppan' /* PreferencePanes folder, in .../Library/ */
};

typedef OSType                          FolderType;
typedef OSType                          FolderLocation;

struct FolderDesc {
  Size                descSize;
  FolderType          foldType;
  FolderDescFlags     flags;
  FolderClass         foldClass;
  FolderType          foldLocation;
  OSType              badgeSignature;
  OSType              badgeType;
  UInt32              reserved;
  StrFileName         name;                   /* Str63 on MacOS*/
};
typedef struct FolderDesc               FolderDesc;
typedef FolderDesc *                    FolderDescPtr;

typedef UInt32                          RoutingFlags;
struct FolderRouting {
  Size                descSize;
  OSType              fileType;
  FolderType          routeFromFolder;
  FolderType          routeToFolder;
  RoutingFlags        flags;
};
typedef struct FolderRouting            FolderRouting;
typedef FolderRouting *                 FolderRoutingPtr;
/* routing constants */

/*  These are bits in the .flags field of the FindFolderUserRedirectionGlobals struct*/
enum {
                                        /*    Set this bit to 1 in the .flags field of a FindFolderUserRedirectionGlobals*/
                                        /*    structure if the userName in the struct should be used as the current*/
                                        /*    "User" name*/
  kFindFolderRedirectionFlagUseDistinctUserFoldersBit = 0, /*    Set this bit to 1 and the currentUserFolderVRefNum and currentUserFolderDirID*/
                                        /*    fields of the user record will get used instead of finding the user folder*/
                                        /*    with the userName field.*/
  kFindFolderRedirectionFlagUseGivenVRefAndDirIDAsUserFolderBit = 1, /*    Set this bit to 1 and the remoteUserFolderVRefNum and remoteUserFolderDirID*/
                                        /*    fields of the user record will get used instead of finding the user folder*/
                                        /*    with the userName field.*/
  kFindFolderRedirectionFlagsUseGivenVRefNumAndDirIDAsRemoteUserFolderBit = 2
};

struct FindFolderUserRedirectionGlobals {
  UInt32              version;
  UInt32              flags;

  Str31               userName;
  short               userNameScript;

  short               currentUserFolderVRefNum;
  long                currentUserFolderDirID;

  short               remoteUserFolderVRefNum;
  long                remoteUserFolderDirID;
};
typedef struct FindFolderUserRedirectionGlobals FindFolderUserRedirectionGlobals;
typedef FindFolderUserRedirectionGlobals * FindFolderUserRedirectionGlobalsPtr;
enum {
  kFolderManagerUserRedirectionGlobalsCurrentVersion = 1
};

/*
    These are passed into FindFolderExtended(), FindFolderInternalExtended(), and
    FindFolderNewInstallerEntryExtended() in the flags field. 
*/
enum {
                                        /*    These constants only work on Mac OS 9.x.  On Mac OS X, they are ignored.*/
  kFindFolderExtendedFlagsDoNotFollowAliasesBit = 0,
  kFindFolderExtendedFlagsDoNotUseUserFolderBit = 1,
  kFindFolderExtendedFlagsUseOtherUserRecord = 0x01000000
};

typedef CALLBACK_API( OSStatus , FolderManagerNotificationProcPtr )(OSType message, void *arg, void *userRefCon);
typedef STACK_UPP_TYPE(FolderManagerNotificationProcPtr)        FolderManagerNotificationUPP;
/*
 *  NewFolderManagerNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern FolderManagerNotificationUPP
NewFolderManagerNotificationUPP(FolderManagerNotificationProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeFolderManagerNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeFolderManagerNotificationUPP(FolderManagerNotificationUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeFolderManagerNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSStatus
InvokeFolderManagerNotificationUPP(
  OSType                        message,
  void *                        arg,
  void *                        userRefCon,
  FolderManagerNotificationUPP  userUPP)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

enum {
  kFolderManagerNotificationMessageUserLogIn = 'log+', /*    Sent by system & third party software after a user logs in.  arg should point to a valid FindFolderUserRedirectionGlobals structure or nil for the owner*/
  kFolderManagerNotificationMessagePreUserLogIn = 'logj', /*    Sent by system & third party software before a user logs in.  arg should point to a valid FindFolderUserRedirectionGlobals structure or nil for the owner*/
  kFolderManagerNotificationMessageUserLogOut = 'log-', /*    Sent by system & third party software before a user logs out.  arg should point to a valid FindFolderUserRedirectionGlobals structure or nil for the owner*/
  kFolderManagerNotificationMessagePostUserLogOut = 'logp', /*    Sent by system & third party software after a user logs out.  arg should point to a valid FindFolderUserRedirectionGlobals structure or nil for the owner*/
  kFolderManagerNotificationDiscardCachedData = 'dche', /*    Sent by system & third party software when the entire Folder Manager cache should be flushed*/
  kFolderManagerNotificationMessageLoginStartup = 'stup' /*    Sent by 'Login' application the first time it starts up after each boot*/
};


/*  These get used in the options parameter of FolderManagerRegisterNotificationProc()*/
enum {
  kDoNotRemoveWhenCurrentApplicationQuitsBit = 0,
  kDoNotRemoveWheCurrentApplicationQuitsBit = kDoNotRemoveWhenCurrentApplicationQuitsBit /*    Going away soon, use kDoNotRemoveWheCurrentApplicationQuitsBit*/
};

/*  These get used in the options parameter of FolderManagerCallNotificationProcs()*/
enum {
  kStopIfAnyNotificationProcReturnsErrorBit = 31
};

/*
 *  AddFolderDescriptor()
 *  
 *  Summary:
 *    Copies the supplied information into a new folder descriptor
 *    entry in the system folder list. @discussion The
 *    AddFolderDescriptor function copies the supplied information into
 *    a new descriptor entry in the system folder list. You need to
 *    provide folder descriptors for each folder you wish the Folder
 *    Manager to be able to find via the function FindFolder. For
 *    example, a child folder located in a parent folder needs to have
 *    a descriptor created both for it and its parent folder, so that
 *    the child can be found. This function is supported under Mac OS 8
 *    and later. 
 *    On Mac OS X, folder descriptors added in one process are not
 *    visible in other processes.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    foldType:
 *      Pass a constant identifying the type of the folder you wish the
 *      Folder Manager to be able to find. See ÒFolder Type ConstantsÓ.
 *    
 *    flags:
 *      Set these flags to indicate whether a folder is created during
 *      startup, if the folder name is locked, and if the folder is
 *      created invisible; see ÒFolder Descriptor FlagsÓ.
 *    
 *    foldClass:
 *      Pass the class of the folder which you wish the Folder Manager
 *      to be able to find. The folder class determines how the
 *      foldLocation parameter is interpreted. See "Folder Descriptor
 *      Classes" for a discussion of relative and special folder
 *      classes.
 *    
 *    foldLocation:
 *      For a relative folder, specify the folder type of the parent
 *      folder of the target. For a special folder, specify the
 *      location of the folder; see ÒFolder Descriptor LocationsÓ.
 *    
 *    badgeSignature:
 *      Reserved. Pass 0.
 *    
 *    badgeType:
 *      Reserved. Pass 0.
 *    
 *    name:
 *      A string specifying the name of the desired folder. For
 *      relative folders, this is the exact name of the desired folder.
 *      For special folders, the actual target folder may have a
 *      different name than the name specified in the folder
 *      descriptor. For example, the System Folder is often given a
 *      different name, but it can still be located with FindFolder.
 *    
 *    replaceFlag:
 *      Pass a Boolean value indicating whether you wish to replace a
 *      folder descriptor that already exists for the specified folder
 *      type. If true , it replaces the folder descriptor for the
 *      specified folder type. If false , it does not replace the
 *      folder descriptor for the specified folder type.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
AddFolderDescriptor(
  FolderType              foldType,
  FolderDescFlags         flags,
  FolderClass             foldClass,
  FolderLocation          foldLocation,
  OSType                  badgeSignature,
  OSType                  badgeType,
  ConstStrFileNameParam   name,
  Boolean                 replaceFlag)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetFolderDescriptor()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    GetFolderDescriptor is deprecated on Mac OS X.
 *  
 *  Summary:
 *    Obtains the folder descriptor information for the specified
 *    folder type from the global descriptor list.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    foldType:
 *      Pass a constant identifying the type of the folder for which
 *      you wish to get descriptor information. See "Folder Type
 *      Constants".
 *    
 *    descSize:
 *      Pass the size (in bytes) of the folder descriptor structure for
 *      which a pointer is passed in the foldDesc parameter. This value
 *      is needed in order to determine the version of the structure
 *      being used.
 *    
 *    foldDesc:
 *      Pass a pointer to a folder descriptor structure. On return, the
 *      folder descriptor structure contains information from the
 *      global descriptor list for the specified folder type.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
GetFolderDescriptor(
  FolderType    foldType,
  Size          descSize,
  FolderDesc *  foldDesc)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3;


/*
 *  GetFolderTypes()
 *  
 *  Summary:
 *    Obtains the folder types contained in the global descriptor list.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    requestedTypeCount:
 *      Pass the number of FolderType values that can fit in the buffer
 *      pointed to by the theTypes parameter; see ÒFolder Type
 *      ConstantsÓ.
 *    
 *    totalTypeCount:
 *      Pass a pointer to an unsigned 32-bit integer value. On return,
 *      the value is set to the total number of FolderType values in
 *      the list. The totalTypeCount parameter may produce a value that
 *      is larger or smaller than that of the requestedTypeCount
 *      parameter. If totalTypeCount is equal to or smaller than the
 *      value passed in for requestedTypeCount and the value produced
 *      by the theTypes parameter is non-null, then all folder types
 *      were returned to the caller.
 *    
 *    theTypes:
 *      Pass a pointer to an array of FolderType values; see "Folder
 *      Type Constants". On return, the array contains the folder types
 *      for the installed descriptors. You can step through the array
 *      and call GetFolderDescriptor for each folder type. Pass null if
 *      you only want to know the number of descriptors installed in
 *      the systemÕs global list, rather than the actual folder types
 *      of those descriptors.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
GetFolderTypes(
  UInt32        requestedTypeCount,
  UInt32 *      totalTypeCount,
  FolderType *  theTypes)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RemoveFolderDescriptor()
 *  
 *  Summary:
 *    Deletes the specified folder descriptor entry from the system
 *    folder list.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    foldType:
 *      Pass a constant identifying the type of the folder for which
 *      you wish to remove a descriptor.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
RemoveFolderDescriptor(FolderType foldType)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetFolderName()
 *  
 *  Summary:
 *    Obtains the name of the specified folder.
 *  
 *  Discussion:
 *    The GetFolderName function obtains the name of the folder in the
 *    folder descriptor, not the name of the folder on the disk. The
 *    names may differ for a few special folders such as the System
 *    Folder. For relative folders, however, the actual name is always
 *    returned. You typically do not need to call this function.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    vRefNum:
 *      Pass the volume reference number (or the constant kOnSystemDisk
 *      for the startup disk) of the volume containing the folder for
 *      which you wish the name to be identified.
 *    
 *    foldType:
 *      Pass a constant identifying the type of the folder for which
 *      you wish the name to be identified. See "Folder Type Constants".
 *    
 *    foundVRefNum:
 *      On return, a pointer to the volume reference number for the
 *      volume containing the folder specified in the foldType
 *      parameter.
 *    
 *    name:
 *      On return, a string containing the title of the folder
 *      specified in the foldType and vRefNum parameters.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
GetFolderName(
  short         vRefNum,
  OSType        foldType,
  short *       foundVRefNum,
  StrFileName   name)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddFolderRouting()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Folder Manager routing is deprecated on Mac OS X.  Do not rely on
 *    this feature in your application, because support for it will be
 *    removed in a future version of the OS.
 *  
 *  Summary:
 *    Adds a folder routing structure to the global routing list.
 *  
 *  Discussion:
 *    Your application can use the AddFolderRouting function to specify
 *    how the Finder routes a given file type. 
 *    Folder Routing is deprecated on Mac OS X at this time.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    fileType:
 *      Pass the OSType of the file to be routed.
 *    
 *    routeFromFolder:
 *      Pass the folder type of the "from" folder see "Folder Type
 *      Constants" for descriptions of possible values. An item dropped
 *      on the folder specified in this parameter will be routed to the
 *      folder specified in the routeToFolder parameter.
 *    
 *    routeToFolder:
 *      The folder type of the "to" folder see "Folder Type Constants"
 *      for descriptions of possible values.
 *    
 *    flags:
 *      Reserved for future use; pass 0.
 *    
 *    replaceFlag:
 *      Pass a Boolean value indicating whether you wish to replace a
 *      folder routing that already exists. If true , it replaces the
 *      folder to which the item is being routed. If false , it leaves
 *      the folder to which the item is being routed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
AddFolderRouting(
  OSType         fileType,
  FolderType     routeFromFolder,
  FolderType     routeToFolder,
  RoutingFlags   flags,
  Boolean        replaceFlag)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  RemoveFolderRouting()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Folder Manager routing is deprecated on Mac OS X.  Do not rely on
 *    this feature in your application, because support for it will be
 *    removed in a future version of the OS.
 *  
 *  Summary:
 *    Deletes a folder routing structure from the global routing list.
 *  
 *  Discussion:
 *    Both the file type and the folder type specified must match those
 *    of an existing folder routing structure in the global routing
 *    list for the RemoveFolderRouting function to succeed.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    fileType:
 *      Pass the file type value contained in the folder routing
 *      structure to be removed.
 *    
 *    routeFromFolder:
 *      Pass the folder type of the "from" folder see "Folder Type
 *      Constants" for descriptions of possible values.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
RemoveFolderRouting(
  OSType       fileType,
  FolderType   routeFromFolder)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  FindFolderRouting()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Folder Manager routing is deprecated on Mac OS X.  Do not rely on
 *    this feature in your application, because support for it will be
 *    removed in a future version of the OS.
 *  
 *  Summary:
 *    Finds the destination folder from a matching folder routing
 *    structure for the specified file.
 *  
 *  Discussion:
 *    Both the file type and the folder type specified must match those
 *    of a folder routing structure in the global routing list for the
 *    FindFolderRouting function to succeed.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    fileType:
 *      Pass the file type specified in the appropriate folder routing
 *      structure for the file for which you wish to find a destination
 *      folder.
 *    
 *    routeFromFolder:
 *      Pass the folder type of the "from" folder for which you wish to
 *      find a "to" folder see "Folder Type Constants" for descriptions
 *      of possible values. An item dropped on the folder specified in
 *      this parameter will be routed to the folder specified in the
 *      routeToFolder parameter.
 *    
 *    routeToFolder:
 *      A pointer to a value of type FolderType. On return, the value
 *      is set to the folder type of the destination folder.
 *    
 *    flags:
 *      Reserved; pass 0.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
FindFolderRouting(
  OSType          fileType,
  FolderType      routeFromFolder,
  FolderType *    routeToFolder,
  RoutingFlags *  flags)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  GetFolderRoutings()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Folder Manager routing is deprecated on Mac OS X.  Do not rely on
 *    this feature in your application, because support for it will be
 *    removed in a future version of the OS.
 *  
 *  Summary:
 *    Obtains folder routing information from the global routing list.
 *  
 *  Discussion:
 *    The folder routing information in the global routing list
 *    determines how the Finder routes files.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    requestedRoutingCount:
 *      An unsigned 32-bit value. Pass the number of folder routing
 *      structures that can fit in the buffer pointed to by the
 *      theRoutings parameter.
 *    
 *    totalRoutingCount:
 *      A pointer to an unsigned 32-bit value. On return, the value is
 *      set to the number of folder routing structures in the global
 *      list. If this value is less than or equal to
 *      requestedRoutingCount , all folder routing structures were
 *      returned to the caller.
 *    
 *    routingSize:
 *      Pass the size (in bytes) of the FolderRouting structure.
 *    
 *    theRoutings:
 *      Pass a pointer to an array of FolderRouting structures. On
 *      return the structure(s) contain the requested routing
 *      information. You may pass null if you do not wish this
 *      information.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
GetFolderRoutings(
  UInt32           requestedRoutingCount,
  UInt32 *         totalRoutingCount,
  Size             routingSize,
  FolderRouting *  theRoutings)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  InvalidateFolderDescriptorCache()
 *  
 *  Summary:
 *    Invalidates any prior FindFolder results for the specified folder.
 *  
 *  Discussion:
 *    The InvalidateFolderDescriptorCache function searches to see if
 *    there is currently a cache of results from FindFolder calls on
 *    the specified folder. If so, it invalidates the cache from the
 *    previous calls to the FindFolder function in order to force the
 *    Folder Manager to reexamine the disk when FindFolder is called
 *    again on the specified directory ID or volume reference number.
 *    
 *    
 *    You should not normally need to call
 *    InvalidateFolderDescriptorCache.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    vRefNum:
 *      Pass the volume reference number (or the constant kOnSystemDisk
 *      for the startup disk) of the volume containing the folder for
 *      which you wish the descriptor cache to be invalidated. Pass 0
 *      to completely invalidate all folder cache information.
 *    
 *    dirID:
 *      Pass the directory ID number for the folder for which you wish
 *      the descriptor cache to be invalidated. Pass 0 to invalidate
 *      the cache for all folders on the specified disk.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
InvalidateFolderDescriptorCache(
  short   vRefNum,
  long    dirID)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IdentifyFolder()
 *  
 *  Summary:
 *    Obtains the folder type for the specified folder.
 *  
 *  Discussion:
 *    The folder type is identified for the folder specified by the
 *    vRefNum and dirID parameters, if such a folder exists. Note that
 *    IdentifyFolder may take several seconds to complete. Note also
 *    that if there are multiple folder descriptors that map to an
 *    individual folder, IdentifyFolder returns the folder type of only
 *    the first matching descriptor that it finds.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    vRefNum:
 *      Pass the volume reference number (or the constant kOnSystemDisk
 *      for the startup disk) of the volume containing the folder whose
 *      type you wish to identify.
 *    
 *    dirID:
 *      Pass the directory ID number for the folder whose type you wish
 *      to identify.
 *    
 *    foldType:
 *      Pass a pointer to a value of type FolderType. On return, the
 *      value is set to the folder type of the folder with the
 *      specified vRefNum and dirID parameters; see "Folder Type
 *      Constants" for descriptions of possible values.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
IdentifyFolder(
  short         vRefNum,
  long          dirID,
  FolderType *  foldType)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;







/*
 *  FSpDetermineIfSpecIsEnclosedByFolder()
 *  
 *  Summary:
 *    Determine whether the given FSSpec is enclosed inside the given
 *    special folder type for the given domain.
 *  
 *  Discussion:
 *    This is a fairly fast call which can determine whether a given
 *    FSSpec on disk is 'inside' the given special folder type for the
 *    given domain.  This call will be more efficient than the
 *    equivalent client code which walked up the file list, checking
 *    each parent with IdentifyFolder() to see if it matches. One use
 *    for this call is to determine if a given file or folder is inside
 *    the trash on a volume, with something like
 *    
 *    err = FSpDetermineIfRefIsEnclosedByFolder( kOnAppropriateDisk,
 *    kTrashFolderType, & spec, & result );
 *    if ( err == noErr && result ) {
 *    //  FSSpec is inside trash on the volume.<br> }
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Parameters:
 *    
 *    domainOrVRefNum:
 *      The domain or vRefNum to check.  You can also pass
 *      kOnAppropriateDisk to check whatever vRefNum is appropriate for
 *      the given FSRef, or the value 0 to check all vRefNums and
 *      domains.
 *    
 *    folderType:
 *      The folder type to check
 *    
 *    inSpec:
 *      The FSSpec to look for.
 *    
 *    outResult:
 *      If non-NULL, this will be filled in with true if the given
 *      FSRef is enclosed inside the special folder type for the given
 *      domain, or false otherwise.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
FSpDetermineIfSpecIsEnclosedByFolder(
  short           domainOrVRefNum,
  OSType          folderType,
  const FSSpec *  inSpec,
  Boolean *       outResult)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  FSDetermineIfRefIsEnclosedByFolder()
 *  
 *  Summary:
 *    Determine whether the given FSRef is enclosed inside the given
 *    special folder type for the given domain.
 *  
 *  Discussion:
 *    This is a fairly fast call which can determine whether a given
 *    FSRef on disk is 'inside' the given special folder type for the
 *    given domain.  This call will be more efficient than the
 *    equivalent client code which walked up the file list, checking
 *    each parent with IdentifyFolder() to see if it matches. One use
 *    for this call is to determine if a given file or folder is inside
 *    the trash on a volume, with something like
 *    
 *    err = FSDetermineIfRefIsEnclosedByFolder( kOnAppropriateDisk,
 *    kTrashFolderType, & ref, & result );
 *    if ( err == noErr && result ) {
 *    //  FSRef is inside trash on the volume.<br> }
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Parameters:
 *    
 *    domainOrVRefNum:
 *      The domain or vRefNum to check.  You can also pass
 *      kOnAppropriateDisk to check whatever vRefNum is appropriate for
 *      the given FSRef, or the value 0 to check all vRefNums and
 *      domains.
 *    
 *    folderType:
 *      The folder type to check
 *    
 *    inRef:
 *      The FSRef to look for.
 *    
 *    outResult:
 *      If non-NULL, this will be filled in with true if the given
 *      FSRef is enclosed inside the special folder type for the given
 *      domain, or false otherwise.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
FSDetermineIfRefIsEnclosedByFolder(
  short          domainOrVRefNum,
  OSType         folderType,
  const FSRef *  inRef,
  Boolean *      outResult)                                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  DetermineIfPathIsEnclosedByFolder()
 *  
 *  Summary:
 *    Determine whether the given FSRef is enclosed inside the given
 *    special folder type for the given domain.
 *  
 *  Discussion:
 *    This is a fairly fast call which can determine whether a given
 *    path on disk is 'inside' the given special folder type for the
 *    given domain.  This call will be more efficient than the
 *    equivalent client code which walked up the file list, checking
 *    each parent with IdentifyFolder() to see if it matches. One use
 *    for this call is to determine if a given file or folder is inside
 *    the trash on a volume, with something like
 *    
 *    err = DetermineIfPathIsEnclosedByFolder( kOnAppropriateDisk,
 *    kTrashFolderType, path, false, & result );
 *    if ( err == noErr && result ) {
 *    //  FSRef is inside trash on the volume.<br> }
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Parameters:
 *    
 *    domainOrVRefNum:
 *      The domain or vRefNum to check.  You can also pass
 *      kOnAppropriateDisk to check whatever vRefNum is appropriate for
 *      the given FSRef, or the value 0 to check all vRefNums and
 *      domains.
 *    
 *    folderType:
 *      The folder type to check
 *    
 *    utf8Path:
 *      A UTF-8 encoded path name for the file.
 *    
 *    pathIsRealPath:
 *      Pass true if utf8Path is guaranteed to be a real pathname, with
 *      no symlinks or relative pathname items. Pass false if the
 *      utf8Path may contain relative pathnames, or symlinks, or
 *      aliases, etc.
 *    
 *    outResult:
 *      If non-NULL, this will be filled in with true if the given
 *      FSRef is enclosed inside the special folder type for the given
 *      domain, or false otherwise.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
DetermineIfPathIsEnclosedByFolder(
  short          domainOrVRefNum,
  OSType         folderType,
  const UInt8 *  utf8Path,
  Boolean        pathIsRealPath,
  Boolean *      outResult)                                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  FolderManagerRegisterNotificationProc()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated on Mac OS X.
 *  
 *  Summary:
 *    Register a function to be called at certain times
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    notificationProc:
 *    
 *    refCon:
 *    
 *    options:
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FolderManagerRegisterNotificationProc(
  FolderManagerNotificationUPP   notificationProc,
  void *                         refCon,
  UInt32                         options)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3;


/*
 *  FolderManagerUnregisterNotificationProc()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated on Mac OS X.
 *  
 *  Summary:
 *    Unregister a function to be called at certain times
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    notificationProc:
 *    
 *    refCon:
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FolderManagerUnregisterNotificationProc(
  FolderManagerNotificationUPP   notificationProc,
  void *                         refCon)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3;


/*
 *  FolderManagerRegisterCallNotificationProcs()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    This function is deprecated on Mac OS X.
 *  
 *  Summary:
 *    Call the registered Folder Manager notification procs.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    message:
 *    
 *    arg:
 *    
 *    options:
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.3
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSStatus 
FolderManagerRegisterCallNotificationProcs(
  OSType   message,
  void *   arg,
  UInt32   options)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_3;




/*******************************/
/* MultiUser (At Ease) globals */
/*******************************/
/*
   This structure has been through some evolution since the early days of At Ease 1.0.  The structure
   has been expanded (and developers should assume that it will continue this way into the future).  Older
   fields have been obsoleted as the features have changed in newer versions of the code.
*/

/* Some fields in here are really only valid for the network version of Macintosh Manager*/

struct MultiUserGestalt {
                                              /*    Version 1 fields.*/
  short               giVersion;              /* structure version: 0 = invalid, 6 = OS 9*/
  short               giReserved0;            /* [OBSOLETE with v3] giIsActive: if true then At Ease is currently running*/
  short               giReserved1;            /* [OBSOLETE] if true then auto create alias*/
  short               giReserved2;            /* [OBSOLETE with v6]  if true then request floppy on new saves*/
  short               giReserved3;            /* [OBSOLETE] if true then hypercard stacks are shown on Applications panel*/
  FSSpec              giReserved4;            /* [OBSOLETE with v6] location of At Ease Items folder*/

                                              /*    Version 2 fields.*/
  short               giDocsVRefNum;          /* vrefnum of user's documents location (only valid if not on floppy)*/
  long                giDocsDirID;            /* directory id of user's documents folder (only valid if not on floppy)*/
  short               giForceSaves;           /* true if user is forced to save to their documents folder*/
  short               giForceOpens;           /* true if user is forced to open from their documents folder*/
  Str31               giSetupName;            /* name of current setup*/
  Str31               giUserName;             /* name of current user*/
  Str31               giFrontAppName;         /* name of the frontmost application*/
  short               giReserved5;            /* [OBSOLETE with v6] true if user has Go To Finder menu item*/
  short               giIsOn;                 /* true if Multiple Users/Macintosh Manager is on right now*/

                                              /*    Version 3 fields.*/
                                              /*  There were no additional fields for version 3.x*/

                                              /*    Version 4 fields.*/
  short               giUserLoggedInType;     /* 0 = normal user, 1 = workgroup admin, 2 = global admin*/
  char                giUserEncryptPwd[16];   /* encrypted user password (our digest form)*/
  short               giUserEnvironment;      /* 0 = panels, 1 = normal Finder, 2 = limited/restricted Finder*/
  long                giReserved6;            /* [OBSOLETE]*/
  long                giReserved7;            /* [OBSOLETE]*/
  Boolean             giDisableScrnShots;     /* true if screen shots are not allowed*/

                                              /*    Version 5 fields.*/
  Boolean             giSupportsAsyncFSCalls; /* Finder uses this to tell if our patches support async trap patches*/
  short               giPrefsVRefNum;         /* vrefnum of preferences*/
  long                giPrefsDirID;           /* dirID of the At Ease Items folder on preferences volume*/
  unsigned long       giUserLogInTime;        /* time in seconds we've been logged in (0 or 1 mean not logged in)*/
  Boolean             giUsingPrintQuotas;     /* true if logged in user is using printer quotas*/
  Boolean             giUsingDiskQuotas;      /* true if logged in user has disk quotas active*/

                                              /* Version 6 fields - As of Mac OS 9's "Multiple Users 1.0"*/
  Boolean             giInSystemAccess;       /* true if system is in System Access (i.e., owner logged in)*/
  Boolean             giUserFolderEnabled;    /* true if FindFolder is redirecting folders (uses giUserName for user)*/
  short               giReserved8;
  long                giReserved9;
  Boolean             giInLoginScreen;        /* true if no user has logged in (including owner)*/


                                              /* May have more fields added in future, so never check for sizeof(GestaltRec)*/

};
typedef struct MultiUserGestalt         MultiUserGestalt;
typedef MultiUserGestalt *              MultiUserGestaltPtr;
typedef MultiUserGestaltPtr *           MultiUserGestaltHandle;





#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint reset
#endif

#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __FOLDERS__ */

