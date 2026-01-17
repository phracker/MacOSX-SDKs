/*
     File:       CarbonCore/Folders.h
 
     Contains:   Folder Manager Interfaces.
 
     Version:    CarbonCore-317~6
 
     Copyright:  © 1995-2001 by Apple Computer, Inc., all rights reserved.
 
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
  kLastDomainConstant           = kUserDomain
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
  kTemporaryFolderType          = 'temp' /* temporary files go here (deleted periodically, but don't rely on it.) */
};

/*
 *  FindFolder()
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
  long *    foundDirID);


/*
 *  FindFolderExtended()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FindFolderExtended(
  short     vol,
  OSType    foldType,
  Boolean   createFolder,
  UInt32    flags,
  void *    data,
  short *   vRefNum,
  long *    dirID);


/*
 *  ReleaseFolder()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
ReleaseFolder(
  short    vRefNum,
  OSType   folderType);



/*
 *  FSFindFolder()
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
  FSRef *   foundRef);



/*
 *  FSFindFolderExtended()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
FSFindFolderExtended(
  short     vol,
  OSType    foldType,
  Boolean   createFolder,
  UInt32    flags,
  void *    data,
  FSRef *   foundRef);


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
  kTextEncodingsFolderType      = 'Ätex', /* encoding tables */
  kStationeryFolderType         = 'odst', /* stationery */
  kOpenDocFolderType            = 'odod', /* OpenDoc root */
  kOpenDocShellPlugInsFolderType = 'odsp', /* OpenDoc Shell Plug-Ins in OpenDoc folder */
  kEditorsFolderType            = 'oded', /* OpenDoc editors in MacOS Folder */
  kOpenDocEditorsFolderType     = 'Äodf', /* OpenDoc subfolder of Editors folder */
  kOpenDocLibrariesFolderType   = 'odlb', /* OpenDoc libraries folder */
  kGenEditorsFolderType         = 'Äedi', /* CKH general editors folder at root level of Sys folder */
  kHelpFolderType               = 'Ählp', /* CKH help folder currently at root of system folder */
  kInternetPlugInFolderType     = 'Änet', /* CKH internet plug ins for browsers and stuff */
  kModemScriptsFolderType       = 'Ämod', /* CKH modem scripts, get 'em OUT of the Extensions folder */
  kPrinterDescriptionFolderType = 'ppdf', /* CKH new folder at root of System folder for printer descs. */
  kPrinterDriverFolderType      = 'Äprd', /* CKH new folder at root of System folder for printer drivers */
  kScriptingAdditionsFolderType = 'Äscr', /* CKH at root of system folder */
  kSharedLibrariesFolderType    = 'Älib', /* CKH for general shared libs. */
  kVoicesFolderType             = 'fvoc', /* CKH macintalk can live here */
  kControlStripModulesFolderType = 'sdev', /* CKH for control strip modules */
  kAssistantsFolderType         = 'astÄ', /* SJF for Assistants (MacOS Setup Assistant, etc) */
  kUtilitiesFolderType          = 'utiÄ', /* SJF for Utilities folder */
  kAppleExtrasFolderType        = 'aexÄ', /* SJF for Apple Extras folder */
  kContextualMenuItemsFolderType = 'cmnu', /* SJF for Contextual Menu items */
  kMacOSReadMesFolderType       = 'morÄ', /* SJF for MacOS ReadMes folder */
  kALMModulesFolderType         = 'walk', /* EAS for Location Manager Module files except type 'thng' (within kExtensionFolderType) */
  kALMPreferencesFolderType     = 'trip', /* EAS for Location Manager Preferences (within kPreferencesFolderType; contains kALMLocationsFolderType) */
  kALMLocationsFolderType       = 'fall', /* EAS for Location Manager Locations (within kALMPreferencesFolderType) */
  kColorSyncProfilesFolderType  = 'prof', /* for ColorSyncª Profiles */
  kThemesFolderType             = 'thme', /* for Theme data files */
  kFavoritesFolderType          = 'favs', /* Favorties folder for Navigation Services */
  kInternetFolderType           = 'intÄ', /* Internet folder (root level of startup volume) */
  kAppearanceFolderType         = 'appr', /* Appearance folder (root of system folder) */
  kSoundSetsFolderType          = 'snds', /* Sound Sets folder (in Appearance folder) */
  kDesktopPicturesFolderType    = 'dtpÄ', /* Desktop Pictures folder (in Appearance folder) */
  kInternetSearchSitesFolderType = 'issf', /* Internet Search Sites folder */
  kFindSupportFolderType        = 'fnds', /* Find support folder */
  kFindByContentFolderType      = 'fbcf', /* Find by content folder */
  kInstallerLogsFolderType      = 'ilgf', /* Installer Logs folder */
  kScriptsFolderType            = 'scrÄ', /* Scripts folder */
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
  kFrameworksFolderType         = 'fram', /* Contains MacOS X Framework folders     */
  kPrivateFrameworksFolderType  = 'pfrm', /* Contains MacOS X Private Framework folders     */
  kClassicDesktopFolderType     = 'sdsk', /* MacOS 9 compatible desktop folder - same as */
                                        /* kSystemDesktopFolderType but with a more appropriate*/
                                        /* name for Mac OS X code.*/
  kDeveloperFolderType          = 'devf', /* Contains MacOS X Developer Resources*/
  kSystemSoundsFolderType       = 'ssnd', /* Contains Mac OS X System Sound Files*/
  kComponentsFolderType         = 'cmpd', /* Contains Mac OS X components*/
  kQuickTimeComponentsFolderType = 'wcmp', /* Contains QuickTime components for Mac OS X*/
  kCoreServicesFolderType       = 'csrv', /* Refers to the "CoreServices" folder on Mac OS X*/
  kPictureDocumentsFolderType   = 'pdoc', /* Refers to the "Pictures" folder in a users home directory*/
  kMovieDocumentsFolderType     = 'mdoc', /* Refers to the "Movies" folder in a users home directory*/
  kMusicDocumentsFolderType     = 'µdoc', /* Refers to the "Music" folder in a users home directory*/
  kInternetSitesFolderType      = 'site', /* Refers to the "Sites" folder in a users home directory*/
  kPublicFolderType             = 'pubb', /* Refers to the "Public" folder in a users home directory*/
  kAudioSupportFolderType       = 'adio', /* Refers to the Audio support folder for Mac OS X*/
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
  kMIDIDriversFolderType        = 'midi' /* Refers to the MIDI Drivers folder on Mac OS X*/
};

enum {
  kLocalesFolderType            = 'Äloc', /* PKE for Locales folder */
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
  kAppleshareAutomountServerAliasesFolderType = 'srvÄ', /* Appleshare puts volumes to automount inside this folder. */
  kPreMacOS91ApplicationsFolderType = 'Œpps', /* The "Applications" folder, pre Mac OS 9.1 */
  kPreMacOS91InstallerLogsFolderType = '”lgf', /* The "Installer Logs" folder, pre Mac OS 9.1 */
  kPreMacOS91AssistantsFolderType = 'ŒstÄ', /* The "Assistants" folder, pre Mac OS 9.1 */
  kPreMacOS91UtilitiesFolderType = 'ŸtiÄ', /* The "Utilities" folder, pre Mac OS 9.1 */
  kPreMacOS91AppleExtrasFolderType = 'ŒexÄ', /* The "Apple Extras" folder, pre Mac OS 9.1 */
  kPreMacOS91MacOSReadMesFolderType = 'µorÄ', /* The "Mac OS ReadMes" folder, pre Mac OS 9.1 */
  kPreMacOS91InternetFolderType = '”ntÄ', /* The "Internet" folder, pre Mac OS 9.1 */
  kPreMacOS91AutomountedServersFolderType = '§rvÄ', /* The "Servers" folder, pre Mac OS 9.1 */
  kPreMacOS91StationeryFolderType = '¿dst' /* The "Stationery" folder, pre Mac OS 9.1 */
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
  kFolderInLocalOrRemoteUserFolder = kFolderInUserFolder | kFolderInRemoteUserFolderIfAvailable
};

typedef UInt32                          FolderDescFlags;
/* FolderClass values */
enum {
  kRelativeFolder               = 'relf',
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
NewFolderManagerNotificationUPP(FolderManagerNotificationProcPtr userRoutine);

/*
 *  DisposeFolderManagerNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeFolderManagerNotificationUPP(FolderManagerNotificationUPP userUPP);

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
  FolderManagerNotificationUPP  userUPP);

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

/***************************/
/* Folder Manager routines */
/***************************/
/* Folder Manager administration routines */
/*
 *  AddFolderDescriptor()
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
  Boolean                 replaceFlag);


/*
 *  GetFolderDescriptor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
GetFolderDescriptor(
  FolderType    foldType,
  Size          descSize,
  FolderDesc *  foldDesc);


/*
 *  GetFolderTypes()
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
  FolderType *  theTypes);


/*
 *  RemoveFolderDescriptor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
RemoveFolderDescriptor(FolderType foldType);


/* legacy routines */
/*
 *  GetFolderName()
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
  StrFileName   name);


/* routing routines */
/*
 *  AddFolderRouting()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
AddFolderRouting(
  OSType         fileType,
  FolderType     routeFromFolder,
  FolderType     routeToFolder,
  RoutingFlags   flags,
  Boolean        replaceFlag);


/*
 *  RemoveFolderRouting()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
RemoveFolderRouting(
  OSType       fileType,
  FolderType   routeFromFolder);


/*
 *  FindFolderRouting()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
FindFolderRouting(
  OSType          fileType,
  FolderType      routeFromFolder,
  FolderType *    routeToFolder,
  RoutingFlags *  flags);


/*
 *  GetFolderRoutings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
GetFolderRoutings(
  UInt32           requestedRoutingCount,
  UInt32 *         totalRoutingCount,
  Size             routingSize,
  FolderRouting *  theRoutings);


/*
 *  InvalidateFolderDescriptorCache()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
InvalidateFolderDescriptorCache(
  short   vRefNum,
  long    dirID);


/*
 *  IdentifyFolder()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FoldersLib 1.0 and later
 */
extern OSErr 
IdentifyFolder(
  short         vRefNum,
  long          dirID,
  FolderType *  foldType);



/*
 *  FolderManagerRegisterNotificationProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FolderManagerRegisterNotificationProc(
  FolderManagerNotificationUPP   notificationProc,
  void *                         refCon,
  UInt32                         options);


/*
 *  FolderManagerUnregisterNotificationProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FolderManagerUnregisterNotificationProc(
  FolderManagerNotificationUPP   notificationProc,
  void *                         refCon);


/*
 *  FolderManagerRegisterCallNotificationProcs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSStatus 
FolderManagerRegisterCallNotificationProcs(
  OSType   message,
  void *   arg,
  UInt32   options);


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

#endif /* __FOLDERS__ */

