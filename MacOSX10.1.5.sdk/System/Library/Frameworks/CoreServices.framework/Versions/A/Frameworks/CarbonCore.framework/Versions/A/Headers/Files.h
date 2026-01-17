/*
     File:       CarbonCore/Files.h
 
     Contains:   File Manager (MFS, HFS, and HFS+) Interfaces.
 
     Version:    CarbonCore-317~6
 
     Copyright:  © 1985-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __FILES__
#define __FILES__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif

#ifndef __OSUTILS__
#include <CarbonCore/OSUtils.h>
#endif

#ifndef __TEXTCOMMON__
#include <CarbonCore/TextCommon.h>
#endif

#ifndef __UTCUTILS__
#include <CarbonCore/UTCUtils.h>
#endif


/* Finder constants were moved to Finder.Å */
#ifndef __FINDER__
#include <CarbonCore/Finder.h>
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

/* HFSUniStr255 is the Unicode equivalent of Str255 */
struct HFSUniStr255 {
  UInt16              length;                 /* number of unicode characters */
  UniChar             unicode[255];           /* unicode characters */
};
typedef struct HFSUniStr255             HFSUniStr255;
typedef const HFSUniStr255 *            ConstHFSUniStr255Param;
enum {
  fsCurPerm                     = 0x00, /* open access permissions in ioPermssn */
  fsRdPerm                      = 0x01,
  fsWrPerm                      = 0x02,
  fsRdWrPerm                    = 0x03,
  fsRdWrShPerm                  = 0x04,
  fsRdDenyPerm                  = 0x10, /* for use with OpenDeny and OpenRFDeny */
  fsWrDenyPerm                  = 0x20  /* for use with OpenDeny and OpenRFDeny */
};

enum {
  fsRtParID                     = 1,
  fsRtDirID                     = 2
};

enum {
  fsAtMark                      = 0,    /* positioning modes in ioPosMode */
  fsFromStart                   = 1,
  fsFromLEOF                    = 2,
  fsFromMark                    = 3
};

enum {
                                        /* ioPosMode flags */
  pleaseCacheBit                = 4,    /* please cache this request */
  pleaseCacheMask               = 0x0010,
  noCacheBit                    = 5,    /* please don't cache this request */
  noCacheMask                   = 0x0020,
  rdVerifyBit                   = 6,    /* read verify mode */
  rdVerifyMask                  = 0x0040,
  rdVerify                      = 64,   /* old name of rdVerifyMask */
  forceReadBit                  = 6,
  forceReadMask                 = 0x0040,
  newLineBit                    = 7,    /* newline mode */
  newLineMask                   = 0x0080,
  newLineCharMask               = 0xFF00 /* newline character */
};


enum {
                                        /* CatSearch Search bitmask Constants */
  fsSBPartialName               = 1,
  fsSBFullName                  = 2,
  fsSBFlAttrib                  = 4,
  fsSBFlFndrInfo                = 8,
  fsSBFlLgLen                   = 32,
  fsSBFlPyLen                   = 64,
  fsSBFlRLgLen                  = 128,
  fsSBFlRPyLen                  = 256,
  fsSBFlCrDat                   = 512,
  fsSBFlMdDat                   = 1024,
  fsSBFlBkDat                   = 2048,
  fsSBFlXFndrInfo               = 4096,
  fsSBFlParID                   = 8192,
  fsSBNegate                    = 16384,
  fsSBDrUsrWds                  = 8,
  fsSBDrNmFls                   = 16,
  fsSBDrCrDat                   = 512,
  fsSBDrMdDat                   = 1024,
  fsSBDrBkDat                   = 2048,
  fsSBDrFndrInfo                = 4096,
  fsSBDrParID                   = 8192
};

enum {
                                        /* CatSearch Search bit value Constants */
  fsSBPartialNameBit            = 0,    /*ioFileName points to a substring*/
  fsSBFullNameBit               = 1,    /*ioFileName points to a match string*/
  fsSBFlAttribBit               = 2,    /*search includes file attributes*/
  fsSBFlFndrInfoBit             = 3,    /*search includes finder info*/
  fsSBFlLgLenBit                = 5,    /*search includes data logical length*/
  fsSBFlPyLenBit                = 6,    /*search includes data physical length*/
  fsSBFlRLgLenBit               = 7,    /*search includes resource logical length*/
  fsSBFlRPyLenBit               = 8,    /*search includes resource physical length*/
  fsSBFlCrDatBit                = 9,    /*search includes create date*/
  fsSBFlMdDatBit                = 10,   /*search includes modification date*/
  fsSBFlBkDatBit                = 11,   /*search includes backup date*/
  fsSBFlXFndrInfoBit            = 12,   /*search includes extended finder info*/
  fsSBFlParIDBit                = 13,   /*search includes file's parent ID*/
  fsSBNegateBit                 = 14,   /*return all non-matches*/
  fsSBDrUsrWdsBit               = 3,    /*search includes directory finder info*/
  fsSBDrNmFlsBit                = 4,    /*search includes directory valence*/
  fsSBDrCrDatBit                = 9,    /*directory-named version of fsSBFlCrDatBit*/
  fsSBDrMdDatBit                = 10,   /*directory-named version of fsSBFlMdDatBit*/
  fsSBDrBkDatBit                = 11,   /*directory-named version of fsSBFlBkDatBit*/
  fsSBDrFndrInfoBit             = 12,   /*directory-named version of fsSBFlXFndrInfoBit*/
  fsSBDrParIDBit                = 13    /*directory-named version of fsSBFlParIDBit*/
};

enum {
                                        /* vMAttrib (GetVolParms) bit position constants */
  bLimitFCBs                    = 31,
  bLocalWList                   = 30,
  bNoMiniFndr                   = 29,
  bNoVNEdit                     = 28,
  bNoLclSync                    = 27,
  bTrshOffLine                  = 26,
  bNoSwitchTo                   = 25,
  bNoDeskItems                  = 20,
  bNoBootBlks                   = 19,
  bAccessCntl                   = 18,
  bNoSysDir                     = 17,
  bHasExtFSVol                  = 16,
  bHasOpenDeny                  = 15,
  bHasCopyFile                  = 14,
  bHasMoveRename                = 13,
  bHasDesktopMgr                = 12,
  bHasShortName                 = 11,
  bHasFolderLock                = 10,
  bHasPersonalAccessPrivileges  = 9,
  bHasUserGroupList             = 8,
  bHasCatSearch                 = 7,
  bHasFileIDs                   = 6,
  bHasBTreeMgr                  = 5,
  bHasBlankAccessPrivileges     = 4,
  bSupportsAsyncRequests        = 3,    /* asynchronous requests to this volume are handled correctly at any time*/
  bSupportsTrashVolumeCache     = 2
};

enum {
                                        /* vMAttrib (GetVolParms) bit position constants */
  bHasDirectIO                  = 1
};

enum {
                                        /* vMExtendedAttributes (GetVolParms) bit position constants */
  bIsEjectable                  = 0,    /* volume is in an ejectable disk drive */
  bSupportsHFSPlusAPIs          = 1,    /* volume supports HFS Plus APIs directly (not through compatibility layer) */
  bSupportsFSCatalogSearch      = 2,    /* volume supports FSCatalogSearch */
  bSupportsFSExchangeObjects    = 3,    /* volume supports FSExchangeObjects */
  bSupports2TBFiles             = 4,    /* volume supports supports 2 terabyte files */
  bSupportsLongNames            = 5,    /* volume supports file/directory/volume names longer than 31 characters */
  bSupportsMultiScriptNames     = 6,    /* volume supports file/directory/volume names with characters from multiple script systems */
  bSupportsNamedForks           = 7,    /* volume supports forks beyond the data and resource forks */
  bSupportsSubtreeIterators     = 8,    /* volume supports recursive iterators not at the volume root */
  bL2PCanMapFileBlocks          = 9     /* volume supports Lg2Phys SPI correctly */
};

enum {
                                        /* vMExtendedAttributes (GetVolParms) bit position constants */
  bParentModDateChanges         = 10,   /* Changing a file or folder causes its parent's mod date to change */
  bAncestorModDateChanges       = 11    /* Changing a file or folder causes all ancestor mod dates to change */
};

enum {
                                        /* vMExtendedAttributes (GetVolParms) bit position constants */
  bSupportsSymbolicLinks        = 13,   /* volume supports the creation and use of symbolic links (Mac OS X only) */
  bIsAutoMounted                = 14,   /* volume was mounted automatically (Mac OS X only) */
  bAllowCDiDataHandler          = 17    /* allow QuickTime's CDi data handler to examine this volume */
};

enum {
                                        /* Desktop Database, ffsGetIconMessage and fsmGetFSIconMessage icon type and size Constants */
  kLargeIcon                    = 1,
  kLarge4BitIcon                = 2,
  kLarge8BitIcon                = 3,
  kSmallIcon                    = 4,
  kSmall4BitIcon                = 5,
  kSmall8BitIcon                = 6,
  kicnsIconFamily               = 239   /* Note: The 'icns' icon family record is variable sized. */
};

enum {
  kLargeIconSize                = 256,
  kLarge4BitIconSize            = 512,
  kLarge8BitIconSize            = 1024,
  kSmallIconSize                = 64,
  kSmall4BitIconSize            = 128,
  kSmall8BitIconSize            = 256
};

enum {
                                        /* Large Volume Constants */
  kWidePosOffsetBit             = 8,
  kUseWidePositioning           = (1 << kWidePosOffsetBit),
  kMaximumBlocksIn4GB           = 0x007FFFFF
};

enum {
                                        /* Foreign Privilege Model Identifiers */
  fsUnixPriv                    = 1
};

enum {
                                        /* Authentication Constants */
  kNoUserAuthentication         = 1,
  kPassword                     = 2,
  kEncryptPassword              = 3,
  kTwoWayEncryptPassword        = 6
};


/* mapping codes (ioObjType) for MapName & MapID */
enum {
  kOwnerID2Name                 = 1,
  kGroupID2Name                 = 2,
  kOwnerName2ID                 = 3,
  kGroupName2ID                 = 4,    /* types of oj object to be returned (ioObjType) for _GetUGEntry */
  kReturnNextUser               = 1,
  kReturnNextGroup              = 2,
  kReturnNextUG                 = 3
};

/* vcbFlags bits */
enum {
  kVCBFlagsIdleFlushBit         = 3,    /* Set if volume should be flushed at idle time */
  kVCBFlagsIdleFlushMask        = 0x0008,
  kVCBFlagsHFSPlusAPIsBit       = 4,    /* Set if volume implements HFS Plus APIs itself (not via emulation) */
  kVCBFlagsHFSPlusAPIsMask      = 0x0010,
  kVCBFlagsHardwareGoneBit      = 5,    /* Set if disk driver returned a hardwareGoneErr to Read or Write */
  kVCBFlagsHardwareGoneMask     = 0x0020,
  kVCBFlagsVolumeDirtyBit       = 15,   /* Set if volume information has changed since the last FlushVol */
  kVCBFlagsVolumeDirtyMask      = 0x8000
};

/* ioVAtrb bits returned by PBHGetVInfo and PBXGetVolInfo */
enum {
  kioVAtrbDefaultVolumeBit      = 5,    /* Set if the volume is the default volume */
  kioVAtrbDefaultVolumeMask     = 0x0020,
  kioVAtrbFilesOpenBit          = 6,    /* Set if there are open files or iterators */
  kioVAtrbFilesOpenMask         = 0x0040,
  kioVAtrbHardwareLockedBit     = 7,    /* Set if volume is locked by a hardware setting */
  kioVAtrbHardwareLockedMask    = 0x0080,
  kioVAtrbSoftwareLockedBit     = 15,   /* Set if volume is locked by software */
  kioVAtrbSoftwareLockedMask    = 0x8000
};

/* ioFlAttrib bits returned by PBGetCatInfo */
enum {
                                        /* file and directory attributes in ioFlAttrib */
  kioFlAttribLockedBit          = 0,    /* Set if file or directory is locked */
  kioFlAttribLockedMask         = 0x01,
  kioFlAttribResOpenBit         = 2,    /* Set if resource fork is open */
  kioFlAttribResOpenMask        = 0x04,
  kioFlAttribDataOpenBit        = 3,    /* Set if data fork is open */
  kioFlAttribDataOpenMask       = 0x08,
  kioFlAttribDirBit             = 4,    /* Set if this is a directory */
  kioFlAttribDirMask            = 0x10,
  ioDirFlg                      = 4,    /* Set if this is a directory (old name) */
  ioDirMask                     = 0x10,
  kioFlAttribCopyProtBit        = 6,    /* Set if AppleShare server "copy-protects" the file */
  kioFlAttribCopyProtMask       = 0x40,
  kioFlAttribFileOpenBit        = 7,    /* Set if file (either fork) is open */
  kioFlAttribFileOpenMask       = 0x80, /* ioFlAttrib for directories only */
  kioFlAttribInSharedBit        = 2,    /* Set if the directory is within a shared area of the directory hierarchy */
  kioFlAttribInSharedMask       = 0x04,
  kioFlAttribMountedBit         = 3,    /* Set if the directory is a share point that is mounted by some user */
  kioFlAttribMountedMask        = 0x08,
  kioFlAttribSharePointBit      = 5,    /* Set if the directory is a share point */
  kioFlAttribSharePointMask     = 0x20
};

/* ioFCBFlags bits returned by PBGetFCBInfo */
enum {
  kioFCBWriteBit                = 8,    /* Data can be written to this file */
  kioFCBWriteMask               = 0x0100,
  kioFCBResourceBit             = 9,    /* This file is a resource fork */
  kioFCBResourceMask            = 0x0200,
  kioFCBWriteLockedBit          = 10,   /* File has a locked byte range */
  kioFCBWriteLockedMask         = 0x0400,
  kioFCBLargeFileBit            = 11,   /* File may grow beyond 2GB; cache uses file blocks, not bytes */
  kioFCBLargeFileMask           = 0x0800,
  kioFCBSharedWriteBit          = 12,   /* File is open for shared write access */
  kioFCBSharedWriteMask         = 0x1000,
  kioFCBFileLockedBit           = 13,   /* File is locked (write-protected) */
  kioFCBFileLockedMask          = 0x2000,
  kioFCBOwnClumpBit             = 14,   /* File has clump size specified in FCB */
  kioFCBOwnClumpMask            = 0x4000,
  kioFCBModifiedBit             = 15,   /* File has changed since it was last flushed */
  kioFCBModifiedMask            = 0x8000
};

/* ioACUser bits returned by PBGetCatInfo */
/* Note: you must clear ioACUser before calling PBGetCatInfo because some file systems do not use this field */
enum {
  kioACUserNoSeeFolderBit       = 0,    /* Set if user does not have See Folder privileges */
  kioACUserNoSeeFolderMask      = 0x01,
  kioACUserNoSeeFilesBit        = 1,    /* Set if user does not have See Files privileges */
  kioACUserNoSeeFilesMask       = 0x02,
  kioACUserNoMakeChangesBit     = 2,    /* Set if user does not have Make Changes privileges */
  kioACUserNoMakeChangesMask    = 0x04,
  kioACUserNotOwnerBit          = 7,    /* Set if user is not owner of the directory */
  kioACUserNotOwnerMask         = 0x80
};

/* Folder and File values of access privileges in ioACAccess */
enum {
  kioACAccessOwnerBit           = 31,   /* User is owner of directory */
  kioACAccessOwnerMask          = (long)0x80000000,
  kioACAccessBlankAccessBit     = 28,   /* Directory has blank access privileges */
  kioACAccessBlankAccessMask    = 0x10000000,
  kioACAccessUserWriteBit       = 26,   /* User has write privileges */
  kioACAccessUserWriteMask      = 0x04000000,
  kioACAccessUserReadBit        = 25,   /* User has read privileges */
  kioACAccessUserReadMask       = 0x02000000,
  kioACAccessUserSearchBit      = 24,   /* User has search privileges */
  kioACAccessUserSearchMask     = 0x01000000,
  kioACAccessEveryoneWriteBit   = 18,   /* Everyone has write privileges */
  kioACAccessEveryoneWriteMask  = 0x00040000,
  kioACAccessEveryoneReadBit    = 17,   /* Everyone has read privileges */
  kioACAccessEveryoneReadMask   = 0x00020000,
  kioACAccessEveryoneSearchBit  = 16,   /* Everyone has search privileges */
  kioACAccessEveryoneSearchMask = 0x00010000,
  kioACAccessGroupWriteBit      = 10,   /* Group has write privileges */
  kioACAccessGroupWriteMask     = 0x00000400,
  kioACAccessGroupReadBit       = 9,    /* Group has read privileges */
  kioACAccessGroupReadMask      = 0x00000200,
  kioACAccessGroupSearchBit     = 8,    /* Group has search privileges */
  kioACAccessGroupSearchMask    = 0x00000100,
  kioACAccessOwnerWriteBit      = 2,    /* Owner has write privileges */
  kioACAccessOwnerWriteMask     = 0x00000004,
  kioACAccessOwnerReadBit       = 1,    /* Owner has read privileges */
  kioACAccessOwnerReadMask      = 0x00000002,
  kioACAccessOwnerSearchBit     = 0,    /* Owner has search privileges */
  kioACAccessOwnerSearchMask    = 0x00000001,
  kfullPrivileges               = 0x00070007, /* all privileges for everybody and owner*/
  kownerPrivileges              = 0x00000007 /* all privileges for owner only*/
};

/* values of user IDs and group IDs */
enum {
  knoUser                       = 0,
  kadministratorUser            = 1
};

enum {
  knoGroup                      = 0
};


struct GetVolParmsInfoBuffer {
  short               vMVersion;              /*version number*/
  long                vMAttrib;               /*bit vector of attributes (see vMAttrib constants)*/
  Handle              vMLocalHand;            /*handle to private data*/
  long                vMServerAdr;            /*AppleTalk server address or zero*/
                                              /*       vMVersion 1 GetVolParmsInfoBuffer ends here */
  long                vMVolumeGrade;          /*approx. speed rating or zero if unrated*/
  short               vMForeignPrivID;        /*foreign privilege model supported or zero if none*/
                                              /*       vMVersion 2 GetVolParmsInfoBuffer ends here */
  long                vMExtendedAttributes;   /*extended attribute bits (see vMExtendedAttributes constants)*/
                                              /*       vMVersion 3 GetVolParmsInfoBuffer ends here */
  void *              vMDeviceID;             /* device id name for interoperability with IOKit */
                                              /*       vMVersion 4 GetVolParmsInfoBuffer ends here */
};
typedef struct GetVolParmsInfoBuffer    GetVolParmsInfoBuffer;
typedef union ParamBlockRec             ParamBlockRec;

typedef ParamBlockRec *                 ParmBlkPtr;
typedef CALLBACK_API( void , IOCompletionProcPtr )(ParmBlkPtr paramBlock);
typedef STACK_UPP_TYPE(IOCompletionProcPtr)                     IOCompletionUPP;
struct IOParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  short               ioRefNum;               /*refNum for I/O operation*/
  SInt8               ioVersNum;              /*version number*/
  SInt8               ioPermssn;              /*Open: permissions (byte)*/
  Ptr                 ioMisc;                 /*Rename: new name (GetEOF,SetEOF: logical end of file) (Open: optional ptr to buffer) (SetFileType: new type)*/
  Ptr                 ioBuffer;               /*data buffer Ptr*/
  long                ioReqCount;             /*requested byte count; also = ioNewDirID*/
  long                ioActCount;             /*actual byte count completed*/
  short               ioPosMode;              /*initial file positioning*/
  long                ioPosOffset;            /*file position offset*/
};
typedef struct IOParam                  IOParam;
typedef IOParam *                       IOParamPtr;
struct FileParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  short               ioFRefNum;              /*reference number*/
  SInt8               ioFVersNum;             /*version number*/
  SInt8               filler1;
  short               ioFDirIndex;            /*GetFInfo directory index*/
  SInt8               ioFlAttrib;             /*GetFInfo: in-use bit=7, lock bit=0*/
  SInt8               ioFlVersNum;            /*file version number*/
  FInfo               ioFlFndrInfo;           /*user info*/
  unsigned long       ioFlNum;                /*GetFInfo: file number; TF- ioDirID*/
  unsigned short      ioFlStBlk;              /*start file block (0 if none)*/
  long                ioFlLgLen;              /*logical length (EOF)*/
  long                ioFlPyLen;              /*physical length*/
  unsigned short      ioFlRStBlk;             /*start block rsrc fork*/
  long                ioFlRLgLen;             /*file logical length rsrc fork*/
  long                ioFlRPyLen;             /*file physical length rsrc fork*/
  unsigned long       ioFlCrDat;              /*file creation date& time (32 bits in secs)*/
  unsigned long       ioFlMdDat;              /*last modified date and time*/
};
typedef struct FileParam                FileParam;
typedef FileParam *                     FileParamPtr;
struct VolumeParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  long                filler2;
  short               ioVolIndex;             /*volume index number*/
  unsigned long       ioVCrDate;              /*creation date and time*/
  unsigned long       ioVLsBkUp;              /*last backup date and time*/
  unsigned short      ioVAtrb;                /*volume attrib*/
  unsigned short      ioVNmFls;               /*number of files in directory*/
  unsigned short      ioVDirSt;               /*start block of file directory*/
  short               ioVBlLn;                /*GetVolInfo: length of dir in blocks*/
  unsigned short      ioVNmAlBlks;            /*for compatibilty ioVNmAlBlks * ioVAlBlkSiz <= 2 GB*/
  unsigned long       ioVAlBlkSiz;            /*for compatibilty ioVAlBlkSiz is <= $0000FE00 (65,024)*/
  unsigned long       ioVClpSiz;              /*GetVolInfo: bytes to allocate at a time*/
  unsigned short      ioAlBlSt;               /*starting disk(512-byte) block in block map*/
  unsigned long       ioVNxtFNum;             /*GetVolInfo: next free file number*/
  unsigned short      ioVFrBlk;               /*GetVolInfo: # free alloc blks for this vol*/
};
typedef struct VolumeParam              VolumeParam;
typedef VolumeParam *                   VolumeParamPtr;
struct CntrlParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  short               ioCRefNum;              /*refNum for I/O operation*/
  short               csCode;                 /*word for control status code*/
  short               csParam[11];            /*operation-defined parameters*/
};
typedef struct CntrlParam               CntrlParam;
typedef CntrlParam *                    CntrlParamPtr;
struct SlotDevParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  short               ioSRefNum;
  SInt8               ioSVersNum;
  SInt8               ioSPermssn;
  Ptr                 ioSMix;
  short               ioSFlags;
  SInt8               ioSlot;
  SInt8               ioID;
};
typedef struct SlotDevParam             SlotDevParam;
typedef SlotDevParam *                  SlotDevParamPtr;
struct MultiDevParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  short               ioMRefNum;
  SInt8               ioMVersNum;
  SInt8               ioMPermssn;
  Ptr                 ioMMix;
  short               ioMFlags;
  Ptr                 ioSEBlkPtr;
};
typedef struct MultiDevParam            MultiDevParam;
typedef MultiDevParam *                 MultiDevParamPtr;
union ParamBlockRec {
  IOParam             ioParam;
  FileParam           fileParam;
  VolumeParam         volumeParam;
  CntrlParam          cntrlParam;
  SlotDevParam        slotDevParam;
  MultiDevParam       multiDevParam;
};

struct HFileInfo {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  short               ioFRefNum;
  SInt8               ioFVersNum;
  SInt8               filler1;
  short               ioFDirIndex;
  SInt8               ioFlAttrib;
  SInt8               ioACUser;
  FInfo               ioFlFndrInfo;
  long                ioDirID;
  unsigned short      ioFlStBlk;
  long                ioFlLgLen;
  long                ioFlPyLen;
  unsigned short      ioFlRStBlk;
  long                ioFlRLgLen;
  long                ioFlRPyLen;
  unsigned long       ioFlCrDat;
  unsigned long       ioFlMdDat;
  unsigned long       ioFlBkDat;
  FXInfo              ioFlXFndrInfo;
  long                ioFlParID;
  long                ioFlClpSiz;
};
typedef struct HFileInfo                HFileInfo;
struct DirInfo {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  short               ioFRefNum;
  SInt8               ioFVersNum;
  SInt8               filler1;
  short               ioFDirIndex;
  SInt8               ioFlAttrib;
  SInt8               ioACUser;
  DInfo               ioDrUsrWds;
  long                ioDrDirID;
  unsigned short      ioDrNmFls;
  short               filler3[9];
  unsigned long       ioDrCrDat;
  unsigned long       ioDrMdDat;
  unsigned long       ioDrBkDat;
  DXInfo              ioDrFndrInfo;
  long                ioDrParID;
};
typedef struct DirInfo                  DirInfo;
union CInfoPBRec {
  HFileInfo           hFileInfo;
  DirInfo             dirInfo;
};
typedef union CInfoPBRec                CInfoPBRec;
typedef CInfoPBRec *                    CInfoPBPtr;
struct XCInfoPBRec {
  QElemPtr            qLink;
  short               qType;
  short               ioTrap;
  Ptr                 ioCmdAddr;
  ProcPtr             ioCompletion;           /* --> A pointer to a completion routine */
  volatile OSErr      ioResult;               /* --> The result code of the function */
  StringPtr           ioNamePtr;              /* --> Pointer to pathname to object */
  short               ioVRefNum;              /* --> A volume specification */
  long                filler1;
  StringPtr           ioShortNamePtr;         /* <-> A pointer to the short name string buffer - required! */
  short               filler2;
  short               ioPDType;               /* <-- The ProDOS file type */
  long                ioPDAuxType;            /* <-- The ProDOS aux type */
  long                filler3[2];
  long                ioDirID;                /* --> A directory ID */
};
typedef struct XCInfoPBRec              XCInfoPBRec;
typedef XCInfoPBRec *                   XCInfoPBPtr;
/* Catalog position record */
struct CatPositionRec {
  long                initialize;
  short               priv[6];
};
typedef struct CatPositionRec           CatPositionRec;
struct FSSpec {
  short               vRefNum;
  long                parID;
  StrFileName         name;                   /* a Str63 on MacOS*/
};
typedef struct FSSpec                   FSSpec;
typedef FSSpec *                        FSSpecPtr;
typedef FSSpecPtr *                     FSSpecHandle;
/* pointer to array of FSSpecs */
typedef FSSpecPtr                       FSSpecArrayPtr;
/* 
    The only difference between "const FSSpec*" and "ConstFSSpecPtr" is 
    that as a parameter, ConstFSSpecPtr is allowed to be NULL 
*/
typedef const FSSpec *                  ConstFSSpecPtr;
/* 
    The following are structures to be filled out with the _PBGetVolMountInfo call
    and passed back into the _PBVolumeMount call for external file system mounts. 
*/
/* the "signature" of the file system */
typedef OSType                          VolumeType;
enum {
                                        /* the signature for AppleShare */
  AppleShareMediaType           = 'afpm'
};

/*
    VolMount stuff was once in FSM.Å
*/
struct VolMountInfoHeader {
  short               length;                 /* length of location data (including self) */
  VolumeType          media;                  /* type of media.  Variable length data follows */
};
typedef struct VolMountInfoHeader       VolMountInfoHeader;
typedef VolMountInfoHeader *            VolMountInfoPtr;
/* The new volume mount info record.  The old one is included for compatibility. 
    the new record allows access by foriegn filesystems writers to the flags 
    portion of the record. This portion is now public.  
*/
struct VolumeMountInfoHeader {
  short               length;                 /* length of location data (including self) */
  VolumeType          media;                  /* type of media (must be registered with Apple) */
  short               flags;                  /* volume mount flags. Variable length data follows */
};
typedef struct VolumeMountInfoHeader    VolumeMountInfoHeader;
typedef VolumeMountInfoHeader *         VolumeMountInfoHeaderPtr;
/* volume mount flags */
enum {
  volMountNoLoginMsgFlagBit     = 0,    /* Input to VolumeMount: If set, the file system */
  volMountNoLoginMsgFlagMask    = 0x0001, /*  should suppresss any log-in message/greeting dialog */
  volMountExtendedFlagsBit      = 7,    /* Input to VolumeMount: If set, the mount info is a */
  volMountExtendedFlagsMask     = 0x0080, /*  AFPXVolMountInfo record for 3.7 AppleShare Client */
  volMountInteractBit           = 15,   /* Input to VolumeMount: If set, it's OK for the file system */
  volMountInteractMask          = 0x8000, /*  to perform user interaction to mount the volume */
  volMountChangedBit            = 14,   /* Output from VoumeMount: If set, the volume was mounted, but */
  volMountChangedMask           = 0x4000, /*  the volume mounting information record needs to be updated. */
  volMountFSReservedMask        = 0x00FF, /* bits 0-7 are defined by each file system for its own use */
  volMountSysReservedMask       = 0xFF00 /* bits 8-15 are reserved for Apple system use */
};



struct AFPVolMountInfo {
  short               length;                 /* length of location data (including self) */
  VolumeType          media;                  /* type of media */
  short               flags;                  /* bits for no messages, no reconnect */
  SInt8               nbpInterval;            /* NBP Interval parameter (IM2, p.322) */
  SInt8               nbpCount;               /* NBP Interval parameter (IM2, p.322) */
  short               uamType;                /* User Authentication Method */
  short               zoneNameOffset;         /* short positive offset from start of struct to Zone Name */
  short               serverNameOffset;       /* offset to pascal Server Name string */
  short               volNameOffset;          /* offset to pascal Volume Name string */
  short               userNameOffset;         /* offset to pascal User Name string */
  short               userPasswordOffset;     /* offset to pascal User Password string */
  short               volPasswordOffset;      /* offset to pascal Volume Password string */
  char                AFPData[144];           /* variable length data may follow */
};
typedef struct AFPVolMountInfo          AFPVolMountInfo;
typedef AFPVolMountInfo *               AFPVolMountInfoPtr;


/* AFPXVolMountInfo is the new AFP volume mount info record, requires the 3.7 AppleShare Client */
struct AFPXVolMountInfo {
  short               length;                 /* length of location data (including self) */
  VolumeType          media;                  /* type of media */
  short               flags;                  /* bits for no messages, no reconnect */
  SInt8               nbpInterval;            /* NBP Interval parameter (IM2, p.322) */
  SInt8               nbpCount;               /* NBP Interval parameter (IM2, p.322) */
  short               uamType;                /* User Authentication Method type */
  short               zoneNameOffset;         /* short positive offset from start of struct to Zone Name */
  short               serverNameOffset;       /* offset to pascal Server Name string */
  short               volNameOffset;          /* offset to pascal Volume Name string */
  short               userNameOffset;         /* offset to pascal User Name string */
  short               userPasswordOffset;     /* offset to pascal User Password string */
  short               volPasswordOffset;      /* offset to pascal Volume Password string */
  short               extendedFlags;          /* extended flags word */
  short               uamNameOffset;          /* offset to a pascal UAM name string */
  short               alternateAddressOffset; /* offset to Alternate Addresses in tagged format */
  char                AFPData[176];           /* variable length data may follow */
};
typedef struct AFPXVolMountInfo         AFPXVolMountInfo;
typedef AFPXVolMountInfo *              AFPXVolMountInfoPtr;
enum {
  kAFPExtendedFlagsAlternateAddressMask = 1 /*  bit in AFPXVolMountInfo.extendedFlags that means alternateAddressOffset is used*/
};


enum {
                                        /* constants for use in AFPTagData.fType field*/
  kAFPTagTypeIP                 = 0x01, /* 4 byte IP address (MSB first)            */
  kAFPTagTypeIPPort             = 0x02, /* 4 byte IP address, 2 byte port (MSB first)     */
  kAFPTagTypeDDP                = 0x03, /* Net,Node,Socket Sent by the server, currently unused by the client */
  kAFPTagTypeDNS                = 0x04  /* DNS name in  address:port format   (total length variable up to 254 chars of dns name)          */
};


enum {
                                        /* constants for use in AFPTagData.fLength field*/
  kAFPTagLengthIP               = 0x06,
  kAFPTagLengthIPPort           = 0x08,
  kAFPTagLengthDDP              = 0x06
};

struct AFPTagData {
  UInt8               fLength;                /* length of this data tag including the fLength field */
  UInt8               fType;
  UInt8               fData[1];               /* variable length data */
};
typedef struct AFPTagData               AFPTagData;
struct AFPAlternateAddress {
                                              /* ¥¥¥ÊNOTE: fVersion was missing in 3.2 Universal Interfaces*/
  UInt8               fVersion;               /* version of the structure (currently 0x00)*/
  UInt8               fAddressCount;
  UInt8               fAddressList[1];        /* actually variable length packed set of AFPTagData */
};
typedef struct AFPAlternateAddress      AFPAlternateAddress;
struct DTPBRec {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  short               ioDTRefNum;             /* desktop refnum */
  short               ioIndex;
  long                ioTagInfo;
  Ptr                 ioDTBuffer;
  long                ioDTReqCount;
  long                ioDTActCount;
  SInt8               ioFiller1;
  UInt8               ioIconType;
  short               ioFiller2;
  long                ioDirID;
  OSType              ioFileCreator;
  OSType              ioFileType;
  long                ioFiller3;
  long                ioDTLgLen;
  long                ioDTPyLen;
  short               ioFiller4[14];
  long                ioAPPLParID;
};
typedef struct DTPBRec                  DTPBRec;
typedef DTPBRec *                       DTPBPtr;

struct HIOParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  short               ioRefNum;
  SInt8               ioVersNum;
  SInt8               ioPermssn;
  Ptr                 ioMisc;
  Ptr                 ioBuffer;
  long                ioReqCount;
  long                ioActCount;
  short               ioPosMode;
  long                ioPosOffset;
};
typedef struct HIOParam                 HIOParam;
typedef HIOParam *                      HIOParamPtr;
struct HFileParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  short               ioFRefNum;
  SInt8               ioFVersNum;
  SInt8               filler1;
  short               ioFDirIndex;
  SInt8               ioFlAttrib;
  SInt8               ioFlVersNum;
  FInfo               ioFlFndrInfo;
  long                ioDirID;
  unsigned short      ioFlStBlk;
  long                ioFlLgLen;
  long                ioFlPyLen;
  unsigned short      ioFlRStBlk;
  long                ioFlRLgLen;
  long                ioFlRPyLen;
  unsigned long       ioFlCrDat;
  unsigned long       ioFlMdDat;
};
typedef struct HFileParam               HFileParam;
typedef HFileParam *                    HFileParamPtr;
struct HVolumeParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  long                filler2;
  short               ioVolIndex;
  unsigned long       ioVCrDate;
  unsigned long       ioVLsMod;
  short               ioVAtrb;
  unsigned short      ioVNmFls;
  unsigned short      ioVBitMap;
  unsigned short      ioAllocPtr;
  unsigned short      ioVNmAlBlks;
  unsigned long       ioVAlBlkSiz;
  unsigned long       ioVClpSiz;
  unsigned short      ioAlBlSt;
  unsigned long       ioVNxtCNID;
  unsigned short      ioVFrBlk;
  unsigned short      ioVSigWord;
  short               ioVDrvInfo;
  short               ioVDRefNum;
  short               ioVFSID;
  unsigned long       ioVBkUp;
  short               ioVSeqNum;
  unsigned long       ioVWrCnt;
  unsigned long       ioVFilCnt;
  unsigned long       ioVDirCnt;
  long                ioVFndrInfo[8];
};
typedef struct HVolumeParam             HVolumeParam;
typedef HVolumeParam *                  HVolumeParamPtr;
struct XIOParam {
  QElemPtr            qLink;
  short               qType;
  short               ioTrap;
  Ptr                 ioCmdAddr;
  IOCompletionUPP     ioCompletion;
  volatile OSErr      ioResult;
  StringPtr           ioNamePtr;
  short               ioVRefNum;
  short               ioRefNum;
  SInt8               ioVersNum;
  SInt8               ioPermssn;
  Ptr                 ioMisc;
  Ptr                 ioBuffer;
  long                ioReqCount;
  long                ioActCount;
  short               ioPosMode;              /* must have kUseWidePositioning bit set */
  wide                ioWPosOffset;           /* wide positioning offset */
};
typedef struct XIOParam                 XIOParam;
typedef XIOParam *                      XIOParamPtr;
struct XVolumeParam {
  QElemPtr            qLink;
  short               qType;
  short               ioTrap;
  Ptr                 ioCmdAddr;
  IOCompletionUPP     ioCompletion;
  volatile OSErr      ioResult;
  StringPtr           ioNamePtr;
  short               ioVRefNum;
  unsigned long       ioXVersion;             /* this XVolumeParam version (0) */
  short               ioVolIndex;
  unsigned long       ioVCrDate;
  unsigned long       ioVLsMod;
  short               ioVAtrb;
  unsigned short      ioVNmFls;
  unsigned short      ioVBitMap;
  unsigned short      ioAllocPtr;
  unsigned short      ioVNmAlBlks;
  unsigned long       ioVAlBlkSiz;
  unsigned long       ioVClpSiz;
  unsigned short      ioAlBlSt;
  unsigned long       ioVNxtCNID;
  unsigned short      ioVFrBlk;
  unsigned short      ioVSigWord;
  short               ioVDrvInfo;
  short               ioVDRefNum;
  short               ioVFSID;
  unsigned long       ioVBkUp;
  short               ioVSeqNum;
  unsigned long       ioVWrCnt;
  unsigned long       ioVFilCnt;
  unsigned long       ioVDirCnt;
  long                ioVFndrInfo[8];
  UInt64              ioVTotalBytes;          /* total number of bytes on volume */
  UInt64              ioVFreeBytes;           /* number of free bytes on volume */
};
typedef struct XVolumeParam             XVolumeParam;
typedef XVolumeParam *                  XVolumeParamPtr;
struct AccessParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  short               filler3;
  short               ioDenyModes;            /*access rights data*/
  short               filler4;
  SInt8               filler5;
  SInt8               ioACUser;               /*access rights for directory only*/
  long                filler6;
  long                ioACOwnerID;            /*owner ID*/
  long                ioACGroupID;            /*group ID*/
  long                ioACAccess;             /*access rights*/
  long                ioDirID;
};
typedef struct AccessParam              AccessParam;
typedef AccessParam *                   AccessParamPtr;
struct ObjParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  short               filler7;
  short               ioObjType;              /*function code*/
  StringPtr           ioObjNamePtr;           /*ptr to returned creator/group name*/
  long                ioObjID;                /*creator/group ID*/
};
typedef struct ObjParam                 ObjParam;
typedef ObjParam *                      ObjParamPtr;
struct CopyParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  short               ioDstVRefNum;           /*destination vol identifier*/
  short               filler8;
  StringPtr           ioNewName;              /*ptr to destination pathname*/
  StringPtr           ioCopyName;             /*ptr to optional name*/
  long                ioNewDirID;             /*destination directory ID*/
  long                filler14;
  long                filler15;
  long                ioDirID;
};
typedef struct CopyParam                CopyParam;
typedef CopyParam *                     CopyParamPtr;
struct WDParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  short               ioWDCreated;
  short               ioWDIndex;
  long                ioWDProcID;
  short               ioWDVRefNum;
  short               filler10;
  long                filler11;
  long                filler12;
  long                filler13;
  long                ioWDDirID;
};
typedef struct WDParam                  WDParam;
typedef WDParam *                       WDParamPtr;
struct FIDParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  long                filler14;
  StringPtr           ioDestNamePtr;          /* dest file name */
  long                filler15;
  long                ioDestDirID;            /* dest file's directory id */
  long                filler16;
  long                filler17;
  long                ioSrcDirID;             /* source file's directory id */
  short               filler18;
  long                ioFileID;               /* file ID */
};
typedef struct FIDParam                 FIDParam;
typedef FIDParam *                      FIDParamPtr;
struct ForeignPrivParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  long                ioFiller21;
  long                ioFiller22;
  Ptr                 ioForeignPrivBuffer;
  long                ioForeignPrivActCount;
  long                ioForeignPrivReqCount;
  long                ioFiller23;
  long                ioForeignPrivDirID;
  long                ioForeignPrivInfo1;
  long                ioForeignPrivInfo2;
  long                ioForeignPrivInfo3;
  long                ioForeignPrivInfo4;
};
typedef struct ForeignPrivParam         ForeignPrivParam;
typedef ForeignPrivParam *              ForeignPrivParamPtr;
struct CSParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/
  FSSpecPtr           ioMatchPtr;             /* match array */
  long                ioReqMatchCount;        /* maximum allowable matches */
  long                ioActMatchCount;        /* actual match count */
  long                ioSearchBits;           /* search criteria selector */
  CInfoPBPtr          ioSearchInfo1;          /* search values and range lower bounds */
  CInfoPBPtr          ioSearchInfo2;          /* search values and range upper bounds */
  long                ioSearchTime;           /* length of time to run search */
  CatPositionRec      ioCatPosition;          /* current position in the catalog */
  Ptr                 ioOptBuffer;            /* optional performance enhancement buffer */
  long                ioOptBufSize;           /* size of buffer pointed to by ioOptBuffer */
};
typedef struct CSParam                  CSParam;
typedef CSParam *                       CSParamPtr;
union HParamBlockRec {
  HIOParam            ioParam;
  HFileParam          fileParam;
  HVolumeParam        volumeParam;
  AccessParam         accessParam;
  ObjParam            objParam;
  CopyParam           copyParam;
  WDParam             wdParam;
  FIDParam            fidParam;
  CSParam             csParam;
  ForeignPrivParam    foreignPrivParam;
};
typedef union HParamBlockRec            HParamBlockRec;


typedef HParamBlockRec *                HParmBlkPtr;

struct CMovePBRec {
  QElemPtr            qLink;
  short               qType;
  short               ioTrap;
  Ptr                 ioCmdAddr;
  IOCompletionUPP     ioCompletion;
  volatile OSErr      ioResult;
  StringPtr           ioNamePtr;
  short               ioVRefNum;
  long                filler1;
  StringPtr           ioNewName;
  long                filler2;
  long                ioNewDirID;
  long                filler3[2];
  long                ioDirID;
};
typedef struct CMovePBRec               CMovePBRec;
typedef CMovePBRec *                    CMovePBPtr;
struct WDPBRec {
  QElemPtr            qLink;
  short               qType;
  short               ioTrap;
  Ptr                 ioCmdAddr;
  IOCompletionUPP     ioCompletion;
  volatile OSErr      ioResult;
  StringPtr           ioNamePtr;
  short               ioVRefNum;
  short               filler1;
  short               ioWDIndex;
  long                ioWDProcID;
  short               ioWDVRefNum;
  short               filler2[7];
  long                ioWDDirID;
};
typedef struct WDPBRec                  WDPBRec;
typedef WDPBRec *                       WDPBPtr;
struct FCBPBRec {
  QElemPtr            qLink;
  short               qType;
  short               ioTrap;
  Ptr                 ioCmdAddr;
  IOCompletionUPP     ioCompletion;
  volatile OSErr      ioResult;
  StringPtr           ioNamePtr;
  short               ioVRefNum;
  short               ioRefNum;
  short               filler;
  short               ioFCBIndx;
  short               filler1;
  long                ioFCBFlNm;
  short               ioFCBFlags;
  unsigned short      ioFCBStBlk;
  long                ioFCBEOF;
  long                ioFCBPLen;
  long                ioFCBCrPs;
  short               ioFCBVRefNum;
  long                ioFCBClpSiz;
  long                ioFCBParID;
};
typedef struct FCBPBRec                 FCBPBRec;
typedef FCBPBRec *                      FCBPBPtr;
struct VCB {
  QElemPtr            qLink;
  short               qType;
  short               vcbFlags;
  unsigned short      vcbSigWord;
  unsigned long       vcbCrDate;
  unsigned long       vcbLsMod;
  short               vcbAtrb;
  unsigned short      vcbNmFls;
  short               vcbVBMSt;
  short               vcbAllocPtr;
  unsigned short      vcbNmAlBlks;
  long                vcbAlBlkSiz;
  long                vcbClpSiz;
  short               vcbAlBlSt;
  long                vcbNxtCNID;
  unsigned short      vcbFreeBks;
  Str27               vcbVN;
  short               vcbDrvNum;
  short               vcbDRefNum;
  short               vcbFSID;
  short               vcbVRefNum;
  Ptr                 vcbMAdr;
  Ptr                 vcbBufAdr;
  short               vcbMLen;
  short               vcbDirIndex;
  short               vcbDirBlk;
  unsigned long       vcbVolBkUp;
  unsigned short      vcbVSeqNum;
  long                vcbWrCnt;
  long                vcbXTClpSiz;
  long                vcbCTClpSiz;
  unsigned short      vcbNmRtDirs;
  long                vcbFilCnt;
  long                vcbDirCnt;
  long                vcbFndrInfo[8];
  unsigned short      vcbVCSize;
  unsigned short      vcbVBMCSiz;
  unsigned short      vcbCtlCSiz;
  unsigned short      vcbXTAlBlks;
  unsigned short      vcbCTAlBlks;
  short               vcbXTRef;
  short               vcbCTRef;
  Ptr                 vcbCtlBuf;
  long                vcbDirIDM;
  short               vcbOffsM;
};
typedef struct VCB                      VCB;
typedef VCB *                           VCBPtr;
struct DrvQEl {
  QElemPtr            qLink;
  short               qType;
  short               dQDrive;
  short               dQRefNum;
  short               dQFSID;
  unsigned short      dQDrvSz;
  unsigned short      dQDrvSz2;
};
typedef struct DrvQEl                   DrvQEl;
typedef DrvQEl *                        DrvQElPtr;
/*
 *  NewIOCompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern IOCompletionUPP
NewIOCompletionUPP(IOCompletionProcPtr userRoutine);

/*
 *  DisposeIOCompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeIOCompletionUPP(IOCompletionUPP userUPP);

/*
 *  InvokeIOCompletionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeIOCompletionUPP(
  ParmBlkPtr       paramBlock,
  IOCompletionUPP  userUPP);


/*
   PBOpenSync(), PBOpenAsync(), PBOpenImmed() were moved to Devices.h
   PBCloseSync(), PBCloseAsync(), PBCloseImmed() were moved to Devices.h
   PBReadSync(), PBReadAsync(), PBReadImmed() were moved to Devices.h
   PBWriteSync(), PBWriteAsync(), PBWriteImmed() were moved to Devices.h
*/


/*
 *  PBGetVInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBGetVInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBXGetVolInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern OSErr  PBXGetVolInfoSync(XVolumeParamPtr paramBlock);


/*
 *  PBXGetVolInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern OSErr  PBXGetVolInfoAsync(XVolumeParamPtr paramBlock);


/*
 *  PBGetVolSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBGetVolAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBSetVolSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBSetVolAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBFlushVolSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBFlushVolSync(ParmBlkPtr paramBlock);


/*
 *  PBFlushVolAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBFlushVolAsync(ParmBlkPtr paramBlock);


/*
 *  PBHTrashVolumeCachesSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */


/*
 *  PBCreateSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBCreateAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBDeleteSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBDeleteAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBOpenDFSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBOpenDFAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBOpenRFSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBOpenRFAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBRenameSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBRenameAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBGetFInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBGetFInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBSetFInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBSetFInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBSetFLockSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBSetFLockAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBRstFLockSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBRstFLockAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBSetFVersSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBSetFVersAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBAllocateSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBAllocateSync(ParmBlkPtr paramBlock);


/*
 *  PBAllocateAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBAllocateAsync(ParmBlkPtr paramBlock);


/*
 *  PBGetEOFSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBGetEOFSync(ParmBlkPtr paramBlock);


/*
 *  PBGetEOFAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBGetEOFAsync(ParmBlkPtr paramBlock);


/*
 *  PBSetEOFSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBSetEOFSync(ParmBlkPtr paramBlock);


/*
 *  PBSetEOFAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBSetEOFAsync(ParmBlkPtr paramBlock);


/*
 *  PBGetFPosSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBGetFPosSync(ParmBlkPtr paramBlock);


/*
 *  PBGetFPosAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBGetFPosAsync(ParmBlkPtr paramBlock);


/*
 *  PBSetFPosSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBSetFPosSync(ParmBlkPtr paramBlock);


/*
 *  PBSetFPosAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBSetFPosAsync(ParmBlkPtr paramBlock);


/*
 *  PBFlushFileSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBFlushFileSync(ParmBlkPtr paramBlock);


/*
 *  PBFlushFileAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBFlushFileAsync(ParmBlkPtr paramBlock);


/*
 *  PBMountVol()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBUnmountVol()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBUnmountVol(ParmBlkPtr paramBlock);


/*
 *  PBUnmountVolImmed()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */


/*
 *  PBEject()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBOffLine()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBCatSearchSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBCatSearchSync(CSParamPtr paramBlock);


/*
 *  PBCatSearchAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBCatSearchAsync(CSParamPtr paramBlock);


/*
 *  SetVol()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  UnmountVol()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
UnmountVol(
  ConstStr63Param   volName,       /* can be NULL */
  short             vRefNum);


/*
 *  Eject()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  FlushVol()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FlushVol(
  ConstStr63Param   volName,       /* can be NULL */
  short             vRefNum);


/*
 *  HSetVol()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
HSetVol(
  ConstStr63Param   volName,       /* can be NULL */
  short             vRefNum,
  long              dirID);


/* AddDrive() was moved to Devices.h*/

/*
 *  FSOpen()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  OpenDF()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  FSClose()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FSClose(short refNum);


/*
 *  FSRead()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FSRead(
  short   refNum,
  long *  count,
  void *  buffPtr);


/*
 *  FSWrite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FSWrite(
  short         refNum,
  long *        count,
  const void *  buffPtr);


/*
 *  GetVInfo()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  GetFInfo()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  GetVol()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  Create()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  FSDelete()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  OpenRF()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  Rename()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SetFInfo()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  SetFLock()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  RstFLock()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  Allocate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
Allocate(
  short   refNum,
  long *  count);


/*
 *  GetEOF()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetEOF(
  short   refNum,
  long *  logEOF);


/*
 *  SetEOF()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetEOF(
  short   refNum,
  long    logEOF);


/*
 *  GetFPos()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetFPos(
  short   refNum,
  long *  filePos);


/*
 *  SetFPos()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
SetFPos(
  short   refNum,
  short   posMode,
  long    posOff);


/*
 *  GetVRefNum()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetVRefNum(
  short    fileRefNum,
  short *  vRefNum);


/*
 *  fsopen()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  getvinfo()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  getfinfo()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  getvol()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  setvol()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  unmountvol()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  eject()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  flushvol()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  create()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  fsdelete()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  openrf()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  fsrename()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  setfinfo()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  setflock()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  rstflock()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBOpenWDSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBOpenWDAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBCloseWDSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBCloseWDAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBHSetVolSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHSetVolSync(WDPBPtr paramBlock);


/*
 *  PBHSetVolAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHSetVolAsync(WDPBPtr paramBlock);


/*
 *  PBHGetVolSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHGetVolSync(WDPBPtr paramBlock);


/*
 *  PBHGetVolAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHGetVolAsync(WDPBPtr paramBlock);


/*
 *  PBCatMoveSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBCatMoveSync(CMovePBPtr paramBlock);


/*
 *  PBCatMoveAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBCatMoveAsync(CMovePBPtr paramBlock);


/*
 *  PBDirCreateSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDirCreateSync(HParmBlkPtr paramBlock);


/*
 *  PBDirCreateAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDirCreateAsync(HParmBlkPtr paramBlock);


/*
 *  PBGetWDInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBGetWDInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBGetFCBInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBGetFCBInfoSync(FCBPBPtr paramBlock);


/*
 *  PBGetFCBInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBGetFCBInfoAsync(FCBPBPtr paramBlock);


/*
 *  PBGetCatInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBGetCatInfoSync(CInfoPBPtr paramBlock);


/*
 *  PBGetCatInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBGetCatInfoAsync(CInfoPBPtr paramBlock);


/*
 *  PBSetCatInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBSetCatInfoSync(CInfoPBPtr paramBlock);


/*
 *  PBSetCatInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBSetCatInfoAsync(CInfoPBPtr paramBlock);


/*
 *  PBAllocContigSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBAllocContigSync(ParmBlkPtr paramBlock);


/*
 *  PBAllocContigAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBAllocContigAsync(ParmBlkPtr paramBlock);


/*
 *  PBLockRangeSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBLockRangeSync(ParmBlkPtr paramBlock);


/*
 *  PBLockRangeAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBLockRangeAsync(ParmBlkPtr paramBlock);


/*
 *  PBUnlockRangeSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBUnlockRangeSync(ParmBlkPtr paramBlock);


/*
 *  PBUnlockRangeAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBUnlockRangeAsync(ParmBlkPtr paramBlock);


/*
 *  PBSetVInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBSetVInfoSync(HParmBlkPtr paramBlock);


/*
 *  PBSetVInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBSetVInfoAsync(HParmBlkPtr paramBlock);


/*
 *  PBHGetVInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHGetVInfoSync(HParmBlkPtr paramBlock);


/*
 *  PBHGetVInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHGetVInfoAsync(HParmBlkPtr paramBlock);


/*
 *  PBHOpenSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHOpenSync(HParmBlkPtr paramBlock);


/*
 *  PBHOpenAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHOpenAsync(HParmBlkPtr paramBlock);


/*
 *  PBHOpenRFSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHOpenRFSync(HParmBlkPtr paramBlock);


/*
 *  PBHOpenRFAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHOpenRFAsync(HParmBlkPtr paramBlock);


/*
 *  PBHOpenDFSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHOpenDFSync(HParmBlkPtr paramBlock);


/*
 *  PBHOpenDFAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHOpenDFAsync(HParmBlkPtr paramBlock);


/*
 *  PBHCreateSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHCreateSync(HParmBlkPtr paramBlock);


/*
 *  PBHCreateAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHCreateAsync(HParmBlkPtr paramBlock);


/*
 *  PBHDeleteSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHDeleteSync(HParmBlkPtr paramBlock);


/*
 *  PBHDeleteAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHDeleteAsync(HParmBlkPtr paramBlock);


/*
 *  PBHRenameSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHRenameSync(HParmBlkPtr paramBlock);


/*
 *  PBHRenameAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHRenameAsync(HParmBlkPtr paramBlock);


/*
 *  PBHRstFLockSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHRstFLockSync(HParmBlkPtr paramBlock);


/*
 *  PBHRstFLockAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHRstFLockAsync(HParmBlkPtr paramBlock);


/*
 *  PBHSetFLockSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHSetFLockSync(HParmBlkPtr paramBlock);


/*
 *  PBHSetFLockAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHSetFLockAsync(HParmBlkPtr paramBlock);


/*
 *  PBHGetFInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHGetFInfoSync(HParmBlkPtr paramBlock);


/*
 *  PBHGetFInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHGetFInfoAsync(HParmBlkPtr paramBlock);


/*
 *  PBHSetFInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHSetFInfoSync(HParmBlkPtr paramBlock);


/*
 *  PBHSetFInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHSetFInfoAsync(HParmBlkPtr paramBlock);


/*
 *  PBMakeFSSpecSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBMakeFSSpecSync(HParmBlkPtr paramBlock);


/*
 *  PBMakeFSSpecAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBMakeFSSpecAsync(HParmBlkPtr paramBlock);


/*
 *  FInitQueue()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  PBDirectIOOpenDFSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  PBDirectIOOpenRFSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  PBDirectIOCloseSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  PBDirectIOReadSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  PBDirectIOReadAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  PBDirectIOWriteSync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  PBDirectIOWriteAsync()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  GetFSQHdr()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  GetVCBQHdr()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/* GetDrvQHdr was moved to Devices.h*/

/*
 *  HGetVol()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
HGetVol(
  StringPtr   volName,
  short *     vRefNum,
  long *      dirID);


/*
 *  HOpen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
HOpen(
  short              vRefNum,
  long               dirID,
  ConstStr255Param   fileName,
  SInt8              permission,
  short *            refNum);


/*
 *  HOpenDF()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
HOpenDF(
  short              vRefNum,
  long               dirID,
  ConstStr255Param   fileName,
  SInt8              permission,
  short *            refNum);


/*
 *  HOpenRF()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
HOpenRF(
  short              vRefNum,
  long               dirID,
  ConstStr255Param   fileName,
  SInt8              permission,
  short *            refNum);


/*
 *  AllocContig()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
AllocContig(
  short   refNum,
  long *  count);


/*
 *  HCreate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
HCreate(
  short              vRefNum,
  long               dirID,
  ConstStr255Param   fileName,
  OSType             creator,
  OSType             fileType);


/*
 *  DirCreate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
DirCreate(
  short              vRefNum,
  long               parentDirID,
  ConstStr255Param   directoryName,
  long *             createdDirID);


/*
 *  HDelete()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
HDelete(
  short              vRefNum,
  long               dirID,
  ConstStr255Param   fileName);


/*
 *  HGetFInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
HGetFInfo(
  short              vRefNum,
  long               dirID,
  ConstStr255Param   fileName,
  FInfo *            fndrInfo);


/*
 *  HSetFInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
HSetFInfo(
  short              vRefNum,
  long               dirID,
  ConstStr255Param   fileName,
  const FInfo *      fndrInfo);


/*
 *  HSetFLock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
HSetFLock(
  short              vRefNum,
  long               dirID,
  ConstStr255Param   fileName);


/*
 *  HRstFLock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
HRstFLock(
  short              vRefNum,
  long               dirID,
  ConstStr255Param   fileName);


/*
 *  HRename()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
HRename(
  short              vRefNum,
  long               dirID,
  ConstStr255Param   oldName,
  ConstStr255Param   newName);


/*
 *  CatMove()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
CatMove(
  short              vRefNum,
  long               dirID,
  ConstStr255Param   oldName,
  long               newDirID,
  ConstStr255Param   newName);


/*
 *  OpenWD()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  CloseWD()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*
 *  GetWDInfo()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */


/*  shared environment  */
/*
 *  PBHGetVolParmsSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHGetVolParmsSync(HParmBlkPtr paramBlock);


/*
 *  PBHGetVolParmsAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHGetVolParmsAsync(HParmBlkPtr paramBlock);


/*
 *  PBHGetLogInInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHGetLogInInfoSync(HParmBlkPtr paramBlock);


/*
 *  PBHGetLogInInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHGetLogInInfoAsync(HParmBlkPtr paramBlock);


/*
 *  PBHGetDirAccessSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHGetDirAccessSync(HParmBlkPtr paramBlock);


/*
 *  PBHGetDirAccessAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHGetDirAccessAsync(HParmBlkPtr paramBlock);


/*
 *  PBHSetDirAccessSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHSetDirAccessSync(HParmBlkPtr paramBlock);


/*
 *  PBHSetDirAccessAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHSetDirAccessAsync(HParmBlkPtr paramBlock);


/*
 *  PBHMapIDSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHMapIDSync(HParmBlkPtr paramBlock);


/*
 *  PBHMapIDAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHMapIDAsync(HParmBlkPtr paramBlock);


/*
 *  PBHMapNameSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHMapNameSync(HParmBlkPtr paramBlock);


/*
 *  PBHMapNameAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHMapNameAsync(HParmBlkPtr paramBlock);


/*
 *  PBHCopyFileSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHCopyFileSync(HParmBlkPtr paramBlock);


/*
 *  PBHCopyFileAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHCopyFileAsync(HParmBlkPtr paramBlock);


/*
 *  PBHMoveRenameSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHMoveRenameSync(HParmBlkPtr paramBlock);


/*
 *  PBHMoveRenameAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHMoveRenameAsync(HParmBlkPtr paramBlock);


/*
 *  PBHOpenDenySync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHOpenDenySync(HParmBlkPtr paramBlock);


/*
 *  PBHOpenDenyAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHOpenDenyAsync(HParmBlkPtr paramBlock);


/*
 *  PBHOpenRFDenySync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHOpenRFDenySync(HParmBlkPtr paramBlock);


/*
 *  PBHOpenRFDenyAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBHOpenRFDenyAsync(HParmBlkPtr paramBlock);


/*
 *  PBGetXCatInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern OSErr  PBGetXCatInfoSync(XCInfoPBPtr paramBlock);


/*
 *  PBGetXCatInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern OSErr  PBGetXCatInfoAsync(XCInfoPBPtr paramBlock);


/*
 *  PBExchangeFilesSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBExchangeFilesSync(HParmBlkPtr paramBlock);


/*
 *  PBExchangeFilesAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBExchangeFilesAsync(HParmBlkPtr paramBlock);


/*
 *  PBCreateFileIDRefSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBCreateFileIDRefSync(HParmBlkPtr paramBlock);


/*
 *  PBCreateFileIDRefAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBCreateFileIDRefAsync(HParmBlkPtr paramBlock);


/*
 *  PBResolveFileIDRefSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBResolveFileIDRefSync(HParmBlkPtr paramBlock);


/*
 *  PBResolveFileIDRefAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBResolveFileIDRefAsync(HParmBlkPtr paramBlock);


/*
 *  PBDeleteFileIDRefSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDeleteFileIDRefSync(HParmBlkPtr paramBlock);


/*
 *  PBDeleteFileIDRefAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDeleteFileIDRefAsync(HParmBlkPtr paramBlock);


/*
 *  PBGetForeignPrivsSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBGetForeignPrivsSync(HParmBlkPtr paramBlock);


/*
 *  PBGetForeignPrivsAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBGetForeignPrivsAsync(HParmBlkPtr paramBlock);


/*
 *  PBSetForeignPrivsSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBSetForeignPrivsSync(HParmBlkPtr paramBlock);


/*
 *  PBSetForeignPrivsAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBSetForeignPrivsAsync(HParmBlkPtr paramBlock);


/*  Desktop Manager  */
/*
 *  PBDTGetPath()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTGetPath(DTPBPtr paramBlock);


/*
 *  PBDTCloseDown()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTCloseDown(DTPBPtr paramBlock);


/*
 *  PBDTAddIconSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTAddIconSync(DTPBPtr paramBlock);


/*
 *  PBDTAddIconAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTAddIconAsync(DTPBPtr paramBlock);


/*
 *  PBDTGetIconSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTGetIconSync(DTPBPtr paramBlock);


/*
 *  PBDTGetIconAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTGetIconAsync(DTPBPtr paramBlock);


/*
 *  PBDTGetIconInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTGetIconInfoSync(DTPBPtr paramBlock);


/*
 *  PBDTGetIconInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTGetIconInfoAsync(DTPBPtr paramBlock);


/*
 *  PBDTAddAPPLSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTAddAPPLSync(DTPBPtr paramBlock);


/*
 *  PBDTAddAPPLAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTAddAPPLAsync(DTPBPtr paramBlock);


/*
 *  PBDTRemoveAPPLSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTRemoveAPPLSync(DTPBPtr paramBlock);


/*
 *  PBDTRemoveAPPLAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTRemoveAPPLAsync(DTPBPtr paramBlock);


/*
 *  PBDTGetAPPLSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTGetAPPLSync(DTPBPtr paramBlock);


/*
 *  PBDTGetAPPLAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTGetAPPLAsync(DTPBPtr paramBlock);


/*
 *  PBDTSetCommentSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTSetCommentSync(DTPBPtr paramBlock);


/*
 *  PBDTSetCommentAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTSetCommentAsync(DTPBPtr paramBlock);


/*
 *  PBDTRemoveCommentSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTRemoveCommentSync(DTPBPtr paramBlock);


/*
 *  PBDTRemoveCommentAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTRemoveCommentAsync(DTPBPtr paramBlock);


/*
 *  PBDTGetCommentSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTGetCommentSync(DTPBPtr paramBlock);


/*
 *  PBDTGetCommentAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTGetCommentAsync(DTPBPtr paramBlock);


/*
 *  PBDTFlushSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTFlushSync(DTPBPtr paramBlock);


/*
 *  PBDTFlushAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTFlushAsync(DTPBPtr paramBlock);


/*
 *  PBDTResetSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTResetSync(DTPBPtr paramBlock);


/*
 *  PBDTResetAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTResetAsync(DTPBPtr paramBlock);


/*
 *  PBDTGetInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTGetInfoSync(DTPBPtr paramBlock);


/*
 *  PBDTGetInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTGetInfoAsync(DTPBPtr paramBlock);


/*
 *  PBDTOpenInform()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTOpenInform(DTPBPtr paramBlock);


/*
 *  PBDTDeleteSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTDeleteSync(DTPBPtr paramBlock);


/*
 *  PBDTDeleteAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBDTDeleteAsync(DTPBPtr paramBlock);


/*  VolumeMount traps  */
/*
 *  PBGetVolMountInfoSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBGetVolMountInfoSize(ParmBlkPtr paramBlock);


/*
 *  PBGetVolMountInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBGetVolMountInfo(ParmBlkPtr paramBlock);


/*
 *  PBVolumeMount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBVolumeMount(ParmBlkPtr paramBlock);


/*  FSp traps  */
/*
 *  FSMakeFSSpec()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FSMakeFSSpec(
  short              vRefNum,
  long               dirID,
  ConstStr255Param   fileName,
  FSSpec *           spec);


/*
 *  FSpOpenDF()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FSpOpenDF(
  const FSSpec *  spec,
  SInt8           permission,
  short *         refNum);


/*
 *  FSpOpenRF()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FSpOpenRF(
  const FSSpec *  spec,
  SInt8           permission,
  short *         refNum);


/*
 *  FSpCreate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FSpCreate(
  const FSSpec *  spec,
  OSType          creator,
  OSType          fileType,
  ScriptCode      scriptTag);


/*
 *  FSpDirCreate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FSpDirCreate(
  const FSSpec *  spec,
  ScriptCode      scriptTag,
  long *          createdDirID);


/*
 *  FSpDelete()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FSpDelete(const FSSpec * spec);


/*
 *  FSpGetFInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FSpGetFInfo(
  const FSSpec *  spec,
  FInfo *         fndrInfo);


/*
 *  FSpSetFInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FSpSetFInfo(
  const FSSpec *  spec,
  const FInfo *   fndrInfo);


/*
 *  FSpSetFLock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FSpSetFLock(const FSSpec * spec);


/*
 *  FSpRstFLock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FSpRstFLock(const FSSpec * spec);


/*
 *  FSpRename()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FSpRename(
  const FSSpec *     spec,
  ConstStr255Param   newName);


/*
 *  FSpCatMove()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FSpCatMove(
  const FSSpec *  source,
  const FSSpec *  dest);


/*
 *  FSpExchangeFiles()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FSpExchangeFiles(
  const FSSpec *  source,
  const FSSpec *  dest);



/*
 *  PBShareSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBShareSync(HParmBlkPtr paramBlock);


/*
 *  PBShareAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBShareAsync(HParmBlkPtr paramBlock);


/*
 *  PBUnshareSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBUnshareSync(HParmBlkPtr paramBlock);


/*
 *  PBUnshareAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBUnshareAsync(HParmBlkPtr paramBlock);


/*
 *  PBGetUGEntrySync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBGetUGEntrySync(HParmBlkPtr paramBlock);


/*
 *  PBGetUGEntryAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr  PBGetUGEntryAsync(HParmBlkPtr paramBlock);






/*
    The PBxxx() routines are obsolete.  
    
    Use the PBxxxSync() or PBxxxAsync() version instead.
*/
#define PBGetVInfo(pb, async) ((async) ? PBGetVInfoAsync(pb) : PBGetVInfoSync(pb))
#define PBXGetVolInfo(pb, async) ((async) ? PBXGetVolInfoAsync(pb) : PBXGetVolInfoSync(pb))
#define PBGetVol(pb, async) ((async) ? PBGetVolAsync(pb) : PBGetVolSync(pb))
#define PBSetVol(pb, async) ((async) ? PBSetVolAsync(pb) : PBSetVolSync(pb))
#define PBFlushVol(pb, async) ((async) ? PBFlushVolAsync(pb) : PBFlushVolSync(pb))
#define PBCreate(pb, async) ((async) ? PBCreateAsync(pb) : PBCreateSync(pb))
#define PBDelete(pb, async) ((async) ? PBDeleteAsync(pb) : PBDeleteSync(pb))
#define PBOpenDF(pb, async) ((async) ? PBOpenDFAsync(pb) : PBOpenDFSync(pb))
#define PBOpenRF(pb, async) ((async) ? PBOpenRFAsync(pb) : PBOpenRFSync(pb))
#define PBRename(pb, async) ((async) ? PBRenameAsync(pb) : PBRenameSync(pb))
#define PBGetFInfo(pb, async) ((async) ? PBGetFInfoAsync(pb) : PBGetFInfoSync(pb))
#define PBSetFInfo(pb, async) ((async) ? PBSetFInfoAsync(pb) : PBSetFInfoSync(pb))
#define PBSetFLock(pb, async) ((async) ? PBSetFLockAsync(pb) : PBSetFLockSync(pb))
#define PBRstFLock(pb, async) ((async) ? PBRstFLockAsync(pb) : PBRstFLockSync(pb))
#define PBSetFVers(pb, async) ((async) ? PBSetFVersAsync(pb) : PBSetFVersSync(pb))
#define PBAllocate(pb, async) ((async) ? PBAllocateAsync(pb) : PBAllocateSync(pb))
#define PBGetEOF(pb, async) ((async) ? PBGetEOFAsync(pb) : PBGetEOFSync(pb))
#define PBSetEOF(pb, async) ((async) ? PBSetEOFAsync(pb) : PBSetEOFSync(pb))
#define PBGetFPos(pb, async) ((async) ? PBGetFPosAsync(pb) : PBGetFPosSync(pb))
#define PBSetFPos(pb, async) ((async) ? PBSetFPosAsync(pb) : PBSetFPosSync(pb))
#define PBFlushFile(pb, async) ((async) ? PBFlushFileAsync(pb) : PBFlushFileSync(pb))
#define PBCatSearch(pb, async) ((async) ? PBCatSearchAsync(pb) : PBCatSearchSync(pb))
#define PBOpenWD(pb, async) ((async) ? PBOpenWDAsync(pb) : PBOpenWDSync(pb))
#define PBCloseWD(pb, async) ((async) ? PBCloseWDAsync(pb) : PBCloseWDSync(pb))
#define PBHSetVol(pb, async) ((async) ? PBHSetVolAsync(pb) : PBHSetVolSync(pb))
#define PBHGetVol(pb, async) ((async) ? PBHGetVolAsync(pb) : PBHGetVolSync(pb))
#define PBCatMove(pb, async) ((async) ? PBCatMoveAsync(pb) : PBCatMoveSync(pb))
#define PBDirCreate(pb, async) ((async) ? PBDirCreateAsync(pb) : PBDirCreateSync(pb))
#define PBGetWDInfo(pb, async) ((async) ? PBGetWDInfoAsync(pb) : PBGetWDInfoSync(pb))
#define PBGetFCBInfo(pb, async) ((async) ? PBGetFCBInfoAsync(pb) : PBGetFCBInfoSync(pb))
#define PBGetCatInfo(pb, async) ((async) ? PBGetCatInfoAsync(pb) : PBGetCatInfoSync(pb))
#define PBSetCatInfo(pb, async) ((async) ? PBSetCatInfoAsync(pb) : PBSetCatInfoSync(pb))
#define PBAllocContig(pb, async) ((async) ? PBAllocContigAsync(pb) : PBAllocContigSync(pb))
#define PBLockRange(pb, async) ((async) ? PBLockRangeAsync(pb) : PBLockRangeSync(pb))
#define PBUnlockRange(pb, async) ((async) ? PBUnlockRangeAsync(pb) : PBUnlockRangeSync(pb))
#define PBSetVInfo(pb, async) ((async) ? PBSetVInfoAsync(pb) : PBSetVInfoSync(pb))
#define PBHGetVInfo(pb, async) ((async) ? PBHGetVInfoAsync(pb) : PBHGetVInfoSync(pb))
#define PBHOpen(pb, async) ((async) ? PBHOpenAsync(pb) : PBHOpenSync(pb))
#define PBHOpenRF(pb, async) ((async) ? PBHOpenRFAsync(pb) : PBHOpenRFSync(pb))
#define PBHOpenDF(pb, async) ((async) ? PBHOpenDFAsync(pb) : PBHOpenDFSync(pb))
#define PBHCreate(pb, async) ((async) ? PBHCreateAsync(pb) : PBHCreateSync(pb))
#define PBHDelete(pb, async) ((async) ? PBHDeleteAsync(pb) : PBHDeleteSync(pb))
#define PBHRename(pb, async) ((async) ? PBHRenameAsync(pb) : PBHRenameSync(pb))
#define PBHRstFLock(pb, async) ((async) ? PBHRstFLockAsync(pb) : PBHRstFLockSync(pb))
#define PBHSetFLock(pb, async) ((async) ? PBHSetFLockAsync(pb) : PBHSetFLockSync(pb))
#define PBHGetFInfo(pb, async) ((async) ? PBHGetFInfoAsync(pb) : PBHGetFInfoSync(pb))
#define PBHSetFInfo(pb, async) ((async) ? PBHSetFInfoAsync(pb) : PBHSetFInfoSync(pb))
#define PBMakeFSSpec(pb, async) ((async) ? PBMakeFSSpecAsync(pb) : PBMakeFSSpecSync(pb))
#define PBHGetVolParms(pb, async) ((async) ? PBHGetVolParmsAsync(pb) : PBHGetVolParmsSync(pb))
#define PBHGetLogInInfo(pb, async) ((async) ? PBHGetLogInInfoAsync(pb) : PBHGetLogInInfoSync(pb))
#define PBHGetDirAccess(pb, async) ((async) ? PBHGetDirAccessAsync(pb) : PBHGetDirAccessSync(pb))
#define PBHSetDirAccess(pb, async) ((async) ? PBHSetDirAccessAsync(pb) : PBHSetDirAccessSync(pb))
#define PBHMapID(pb, async) ((async) ? PBHMapIDAsync(pb) : PBHMapIDSync(pb))
#define PBHMapName(pb, async) ((async) ? PBHMapNameAsync(pb) : PBHMapNameSync(pb))
#define PBHCopyFile(pb, async) ((async) ? PBHCopyFileAsync(pb) : PBHCopyFileSync(pb))
#define PBHMoveRename(pb, async) ((async) ? PBHMoveRenameAsync(pb) : PBHMoveRenameSync(pb))
#define PBHOpenDeny(pb, async) ((async) ? PBHOpenDenyAsync(pb) : PBHOpenDenySync(pb))
#define PBHOpenRFDeny(pb, async) ((async) ? PBHOpenRFDenyAsync(pb) : PBHOpenRFDenySync(pb))
#define PBExchangeFiles(pb, async) ((async) ? PBExchangeFilesAsync(pb) : PBExchangeFilesSync(pb))
#define PBCreateFileIDRef(pb, async) ((async) ? PBCreateFileIDRefAsync(pb) : PBCreateFileIDRefSync(pb))
#define PBResolveFileIDRef(pb, async) ((async) ? PBResolveFileIDRefAsync(pb) : PBResolveFileIDRefSync(pb))
#define PBDeleteFileIDRef(pb, async) ((async) ? PBDeleteFileIDRefAsync(pb) : PBDeleteFileIDRefSync(pb))
#define PBGetForeignPrivs(pb, async) ((async) ? PBGetForeignPrivsAsync(pb) : PBGetForeignPrivsSync(pb))
#define PBSetForeignPrivs(pb, async) ((async) ? PBSetForeignPrivsAsync(pb) : PBSetForeignPrivsSync(pb))
#define PBDTAddIcon(pb, async) ((async) ? PBDTAddIconAsync(pb) : PBDTAddIconSync(pb))
#define PBDTGetIcon(pb, async) ((async) ? PBDTGetIconAsync(pb) : PBDTGetIconSync(pb))
#define PBDTGetIconInfo(pb, async) ((async) ? PBDTGetIconInfoAsync(pb) : PBDTGetIconInfoSync(pb))
#define PBDTAddAPPL(pb, async) ((async) ? PBDTAddAPPLAsync(pb) : PBDTAddAPPLSync(pb))
#define PBDTRemoveAPPL(pb, async) ((async) ? PBDTRemoveAPPLAsync(pb) : PBDTRemoveAPPLSync(pb))
#define PBDTGetAPPL(pb, async) ((async) ? PBDTGetAPPLAsync(pb) : PBDTGetAPPLSync(pb))
#define PBDTSetComment(pb, async) ((async) ? PBDTSetCommentAsync(pb) : PBDTSetCommentSync(pb))
#define PBDTRemoveComment(pb, async) ((async) ? PBDTRemoveCommentAsync(pb) : PBDTRemoveCommentSync(pb))
#define PBDTGetComment(pb, async) ((async) ? PBDTGetCommentAsync(pb) : PBDTGetCommentSync(pb))
#define PBDTFlush(pb, async) ((async) ? PBDTFlushAsync(pb) : PBDTFlushSync(pb))
#define PBDTReset(pb, async) ((async) ? PBDTResetAsync(pb) : PBDTResetSync(pb))
#define PBDTGetInfo(pb, async) ((async) ? PBDTGetInfoAsync(pb) : PBDTGetInfoSync(pb))
#define PBDTDelete(pb, async) ((async) ? PBDTDeleteAsync(pb) : PBDTDeleteSync(pb))

typedef SInt16                          FSVolumeRefNum;
enum {
  kFSInvalidVolumeRefNum        = 0
};

struct FSRef {
  UInt8               hidden[80];             /* private to File Manager; ¥¥ need symbolic constant */
};
typedef struct FSRef                    FSRef;
typedef FSRef *                         FSRefPtr;

/*
 *  FSPermissionInfo
 *  
 *  Discussion:
 *    This structure is used when kFSCatInfoPermissions is passed to
 *    the HFSPlus API. On return from GetCatalogInfo and
 *    GetCatalogInfoBulk, the userID, groupID, and mode fields are
 *    returned.  When passed to SetCatalogInfo, only the mode field is
 *    set.  See chmod(2) for details about the mode field. This is
 *    supported on Mac OS X only.
 */
struct FSPermissionInfo {
  UInt32              userID;
  UInt32              groupID;
  UInt8               reserved1;
  UInt8               userAccess;
  UInt16              mode;
  UInt32              reserved2;
};
typedef struct FSPermissionInfo         FSPermissionInfo;
/*  CatalogInfoBitmap describes which fields of the CatalogInfo you wish to get or set.*/

typedef UInt32                          FSCatalogInfoBitmap;
enum {
  kFSCatInfoNone                = 0x00000000,
  kFSCatInfoTextEncoding        = 0x00000001,
  kFSCatInfoNodeFlags           = 0x00000002, /* Locked (bit 0) and directory (bit 4) only */
  kFSCatInfoVolume              = 0x00000004,
  kFSCatInfoParentDirID         = 0x00000008,
  kFSCatInfoNodeID              = 0x00000010,
  kFSCatInfoCreateDate          = 0x00000020,
  kFSCatInfoContentMod          = 0x00000040,
  kFSCatInfoAttrMod             = 0x00000080,
  kFSCatInfoAccessDate          = 0x00000100,
  kFSCatInfoBackupDate          = 0x00000200,
  kFSCatInfoPermissions         = 0x00000400, /* Should this be finer granularity? */
  kFSCatInfoFinderInfo          = 0x00000800,
  kFSCatInfoFinderXInfo         = 0x00001000,
  kFSCatInfoValence             = 0x00002000, /* Folders only, zero for files */
  kFSCatInfoDataSizes           = 0x00004000, /* Data fork logical and physical size */
  kFSCatInfoRsrcSizes           = 0x00008000, /* Resource fork logical and physical size */
  kFSCatInfoSharingFlags        = 0x00010000, /* sharingFlags: kioFlAttribMountedBit, kioFlAttribSharePointBit */
  kFSCatInfoUserPrivs           = 0x00020000, /* userPrivileges */
  kFSCatInfoUserAccess          = 0x00080000, /* (OS X only) */
  kFSCatInfoAllDates            = 0x000003E0,
  kFSCatInfoGettableInfo        = 0x0003FFFF,
  kFSCatInfoSettableInfo        = 0x00001FE3, /* flags, dates, permissions, Finder info, text encoding */
  kFSCatInfoReserved            = (long)0xFFFC0000 /* bits that are currently reserved */
};

/*  Constants for nodeFlags field of FSCatalogInfo */
enum {
  kFSNodeLockedBit              = 0,    /* Set if file or directory is locked */
  kFSNodeLockedMask             = 0x0001,
  kFSNodeResOpenBit             = 2,    /* Set if the resource fork is open */
  kFSNodeResOpenMask            = 0x0004,
  kFSNodeDataOpenBit            = 3,    /* Set if the data fork is open */
  kFSNodeDataOpenMask           = 0x0008,
  kFSNodeIsDirectoryBit         = 4,    /* Set if the object is a directory */
  kFSNodeIsDirectoryMask        = 0x0010,
  kFSNodeCopyProtectBit         = 6,
  kFSNodeCopyProtectMask        = 0x0040,
  kFSNodeForkOpenBit            = 7,    /* Set if the file or directory has any open fork */
  kFSNodeForkOpenMask           = 0x0080
};

/*  Constants for sharingFlags field of FSCatalogInfo */
enum {
  kFSNodeInSharedBit            = 2,    /* Set if a directory is within a share point */
  kFSNodeInSharedMask           = 0x0004,
  kFSNodeIsMountedBit           = 3,    /* Set if a directory is a share point currently mounted by some user */
  kFSNodeIsMountedMask          = 0x0008,
  kFSNodeIsSharePointBit        = 5,    /* Set if a directory is a share point (exported volume) */
  kFSNodeIsSharePointMask       = 0x0020
};


struct FSCatalogInfo {
  UInt16              nodeFlags;              /* node flags */
  FSVolumeRefNum      volume;                 /* object's volume ref */
  UInt32              parentDirID;            /* parent directory's ID */
  UInt32              nodeID;                 /* file/directory ID */
  UInt8               sharingFlags;           /* kioFlAttribMountedBit and kioFlAttribSharePointBit */
  UInt8               userPrivileges;         /* user's effective AFP privileges (same as ioACUser) */
  UInt8               reserved1;
  UInt8               reserved2;
  UTCDateTime         createDate;             /* date and time of creation */
  UTCDateTime         contentModDate;         /* date and time of last fork modification */
  UTCDateTime         attributeModDate;       /* date and time of last attribute modification */
  UTCDateTime         accessDate;             /* date and time of last access (for Mac OS X) */
  UTCDateTime         backupDate;             /* date and time of last backup */

  UInt32              permissions[4];         /* permissions (for Mac OS X) */

  UInt8               finderInfo[16];         /* Finder information part 1 */
  UInt8               extFinderInfo[16];      /* Finder information part 2 */

  UInt64              dataLogicalSize;        /* files only */
  UInt64              dataPhysicalSize;       /* files only */
  UInt64              rsrcLogicalSize;        /* files only */
  UInt64              rsrcPhysicalSize;       /* files only */

  UInt32              valence;                /* folders only */
  TextEncoding        textEncodingHint;
};
typedef struct FSCatalogInfo            FSCatalogInfo;
typedef FSCatalogInfo *                 FSCatalogInfoPtr;
struct FSRefParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  ConstStringPtr      ioNamePtr;              /*ptr to Vol:FileName string*/
  short               ioVRefNum;              /*volume refnum (DrvNum for Eject and MountVol)*/

  SInt16              reserved1;              /* was ioRefNum */
  UInt8               reserved2;              /* was ioVersNum */
  UInt8               reserved3;              /* was ioPermssn */

  const FSRef *       ref;                    /* Input ref; the target of the call */
  FSCatalogInfoBitmap  whichInfo;
  FSCatalogInfo *     catInfo;
  UniCharCount        nameLength;             /* input name length for create/rename */
  const UniChar *     name;                   /* input name for create/rename */
  long                ioDirID;
  FSSpec *            spec;
  FSRef *             parentRef;              /* ref of directory to move another ref to */
  FSRef *             newRef;                 /* Output ref */
  TextEncoding        textEncodingHint;       /* for Rename, MakeFSRefUnicode */
  HFSUniStr255 *      outName;                /* Output name for GetCatalogInfo */
};
typedef struct FSRefParam               FSRefParam;
typedef FSRefParam *                    FSRefParamPtr;
typedef struct OpaqueFSIterator*        FSIterator;
enum {
  kFSIterateFlat                = 0,    /* Immediate children of container only */
  kFSIterateSubtree             = 1,    /* Entire subtree rooted at container */
  kFSIterateDelete              = 2,
  kFSIterateReserved            = (long)0xFFFFFFFC
};

typedef OptionBits                      FSIteratorFlags;
enum {
                                        /* CatalogSearch constants */
  fsSBNodeID                    = 0x00008000, /* search by range of nodeID */
  fsSBAttributeModDate          = 0x00010000, /* search by range of attributeModDate */
  fsSBAccessDate                = 0x00020000, /* search by range of accessDate */
  fsSBPermissions               = 0x00040000, /* search by value/mask of permissions */
  fsSBNodeIDBit                 = 15,
  fsSBAttributeModDateBit       = 16,
  fsSBAccessDateBit             = 17,
  fsSBPermissionsBit            = 18
};

struct FSSearchParams {
  Duration            searchTime;             /* a Time Manager duration */
  OptionBits          searchBits;             /* which fields to search on */
  UniCharCount        searchNameLength;
  const UniChar *     searchName;
  FSCatalogInfo *     searchInfo1;            /* values and lower bounds */
  FSCatalogInfo *     searchInfo2;            /* masks and upper bounds */
};
typedef struct FSSearchParams           FSSearchParams;
typedef FSSearchParams *                FSSearchParamsPtr;
struct FSCatalogBulkParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  Boolean             containerChanged;       /* true if container changed since last iteration */
  UInt8               reserved;               /* make following fields 4-byte aligned */

  FSIteratorFlags     iteratorFlags;
  FSIterator          iterator;
  const FSRef *       container;              /* directory/volume to iterate */
  ItemCount           maximumItems;
  ItemCount           actualItems;
  FSCatalogInfoBitmap  whichInfo;
  FSCatalogInfo *     catalogInfo;            /* returns an array */
  FSRef *             refs;                   /* returns an array */
  FSSpec *            specs;                  /* returns an array */
  HFSUniStr255 *      names;                  /* returns an array */
  const FSSearchParams * searchParams;
};
typedef struct FSCatalogBulkParam       FSCatalogBulkParam;
typedef FSCatalogBulkParam *            FSCatalogBulkParamPtr;
typedef UInt16                          FSAllocationFlags;
enum {
  kFSAllocDefaultFlags          = 0x0000, /* as much as possible, not contiguous */
  kFSAllocAllOrNothingMask      = 0x0001, /* allocate all of the space, or nothing */
  kFSAllocContiguousMask        = 0x0002, /* new space must be one contiguous piece */
  kFSAllocNoRoundUpMask         = 0x0004, /* don't round up allocation to clump size */
  kFSAllocReservedMask          = 0xFFF8 /* these bits are reserved and must not be set */
};

struct FSForkIOParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  void *              reserved1;              /* was ioNamePtr */
  SInt16              reserved2;              /* was ioVRefNum */
  SInt16              forkRefNum;             /* same as ioRefNum */
  UInt8               reserved3;              /* was ioVersNum */
  SInt8               permissions;            /* desired access to the fork */
  const FSRef *       ref;                    /* which object to open */


  Ptr                 buffer;                 /*data buffer Ptr*/
  UInt32              requestCount;           /*requested byte count*/
  UInt32              actualCount;            /*actual byte count completed*/
  UInt16              positionMode;           /*initial file positioning*/
  SInt64              positionOffset;         /*file position offset*/

  FSAllocationFlags   allocationFlags;
  UInt64              allocationAmount;

  UniCharCount        forkNameLength;         /* input; length of fork name */
  const UniChar *     forkName;               /* input; name of fork */

  CatPositionRec      forkIterator;
  HFSUniStr255 *      outForkName;            /* output; name of fork */
};
typedef struct FSForkIOParam            FSForkIOParam;
typedef FSForkIOParam *                 FSForkIOParamPtr;
struct FSForkInfo {
  SInt8               flags;                  /* copy of FCB flags */
  SInt8               permissions;
  FSVolumeRefNum      volume;
  UInt32              reserved2;
  UInt32              nodeID;                 /* file or directory ID */
  UInt32              forkID;                 /* fork ID */
  UInt64              currentPosition;
  UInt64              logicalEOF;
  UInt64              physicalEOF;
  UInt64              process;                /* should be ProcessSerialNumber */
};
typedef struct FSForkInfo               FSForkInfo;
typedef FSForkInfo *                    FSForkInfoPtr;
struct FSForkCBInfoParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  SInt16              desiredRefNum;          /* 0 to iterate, non-0 for specific refnum */
  SInt16              volumeRefNum;           /* volume to match, or 0 for all volumes */
  SInt16              iterator;               /* 0 to start iteration */
  SInt16              actualRefNum;           /* actual refnum found */

  FSRef *             ref;
  FSForkInfo *        forkInfo;
  HFSUniStr255 *      forkName;
};
typedef struct FSForkCBInfoParam        FSForkCBInfoParam;
typedef FSForkCBInfoParam *             FSForkCBInfoParamPtr;
typedef UInt32                          FSVolumeInfoBitmap;
enum {
  kFSVolInfoNone                = 0x0000,
  kFSVolInfoCreateDate          = 0x0001,
  kFSVolInfoModDate             = 0x0002,
  kFSVolInfoBackupDate          = 0x0004,
  kFSVolInfoCheckedDate         = 0x0008,
  kFSVolInfoFileCount           = 0x0010,
  kFSVolInfoDirCount            = 0x0020,
  kFSVolInfoSizes               = 0x0040, /* totalBytes and freeBytes */
  kFSVolInfoBlocks              = 0x0080, /* blockSize, totalBlocks, freeBlocks */
  kFSVolInfoNextAlloc           = 0x0100,
  kFSVolInfoRsrcClump           = 0x0200,
  kFSVolInfoDataClump           = 0x0400,
  kFSVolInfoNextID              = 0x0800,
  kFSVolInfoFinderInfo          = 0x1000,
  kFSVolInfoFlags               = 0x2000,
  kFSVolInfoFSInfo              = 0x4000, /* filesystemID, signature */
  kFSVolInfoDriveInfo           = 0x8000, /* driveNumber, driverRefNum */
  kFSVolInfoGettableInfo        = 0xFFFF, /* This seems like it is here just for completeness */
  kFSVolInfoSettableInfo        = 0x3004 /* backup date, Finder info, flags */
};

/* FSVolumeInfo.flags bits.  These are the same as for ioVAtrb, but with nicer names. */
enum {
  kFSVolFlagDefaultVolumeBit    = 5,    /* Set if the volume is the default volume */
  kFSVolFlagDefaultVolumeMask   = 0x0020,
  kFSVolFlagFilesOpenBit        = 6,    /* Set if there are open files or iterators */
  kFSVolFlagFilesOpenMask       = 0x0040,
  kFSVolFlagHardwareLockedBit   = 7,    /* Set if volume is locked by a hardware setting */
  kFSVolFlagHardwareLockedMask  = 0x0080,
  kFSVolFlagSoftwareLockedBit   = 15,   /* Set if volume is locked by software */
  kFSVolFlagSoftwareLockedMask  = 0x8000
};


struct FSVolumeInfo {
                                              /* Dates -- zero means "never" or "unknown" */
  UTCDateTime         createDate;
  UTCDateTime         modifyDate;
  UTCDateTime         backupDate;
  UTCDateTime         checkedDate;

                                              /* File/Folder counts -- return zero if unknown */
  UInt32              fileCount;              /* total files on volume */
  UInt32              folderCount;            /* total folders on volume */
                                              /* Note: no root directory counts */

  UInt64              totalBytes;             /* total number of bytes on volume */
  UInt64              freeBytes;              /* number of free bytes on volume */

                                              /* HFS and HFS Plus specific.  Set fields to zero if not appropriate */
  UInt32              blockSize;              /* size (in bytes) of allocation blocks */
  UInt32              totalBlocks;            /* number of allocation blocks in volume */
  UInt32              freeBlocks;             /* number of unused allocation blocks */
  UInt32              nextAllocation;         /* start of next allocation search */
  UInt32              rsrcClumpSize;          /* default resource fork clump size */
  UInt32              dataClumpSize;          /* default data fork clump size */
  UInt32              nextCatalogID;          /* next unused catalog node ID ¥¥¥ OYG ¥¥¥ need to make HFSVolumes.h work Should be HFSCatalogNodeID*/
  UInt8               finderInfo[32];         /* information used by Finder */

                                              /* Identifying information */
  UInt16              flags;                  /* ioVAtrb */
  UInt16              filesystemID;           /* ioVFSID */
  UInt16              signature;              /* ioVSigWord, unique within an FSID */
  UInt16              driveNumber;            /* ioVDrvInfo */
  short               driverRefNum;           /* ioVDRefNum */
};
typedef struct FSVolumeInfo             FSVolumeInfo;
typedef FSVolumeInfo *                  FSVolumeInfoPtr;
struct FSVolumeInfoParam {
  QElemPtr            qLink;                  /*queue link in header*/
  short               qType;                  /*type byte for safety check*/
  short               ioTrap;                 /*FS: the Trap*/
  Ptr                 ioCmdAddr;              /*FS: address to dispatch to*/
  IOCompletionUPP     ioCompletion;           /*completion routine addr (0 for synch calls)*/
  volatile OSErr      ioResult;               /*result code*/
  StringPtr           ioNamePtr;              /* unused */
  FSVolumeRefNum      ioVRefNum;              /* volume refnum */

  UInt32              volumeIndex;            /* index, or 0 to use ioVRefNum */
  FSVolumeInfoBitmap  whichInfo;              /* which volumeInfo fields to get/set */
  FSVolumeInfo *      volumeInfo;             /* information about the volume */
  HFSUniStr255 *      volumeName;             /* output; pointer to volume name */
  FSRef *             ref;                    /* volume's FSRef */
};
typedef struct FSVolumeInfoParam        FSVolumeInfoParam;
typedef FSVolumeInfoParam *             FSVolumeInfoParamPtr;
/*
    MakeFSRef
    Create an FSRef for an existing object specified by a combination
    of volume refnum, parent directory, and pathname.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  ioNamePtr       A pointer to a pathname
    ->  ioVRefNum       A volume specification
    ->  ioDirID         A directory ID
    <-  newRef          A pointer to an FSRef
*/
/*
 *  FSpMakeFSRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSpMakeFSRef(
  const FSSpec *  source,
  FSRef *         newRef);


/*
 *  PBMakeFSRefSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBMakeFSRefSync(FSRefParam * paramBlock);


/*
 *  PBMakeFSRefAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBMakeFSRefAsync(FSRefParam * paramBlock);



/*
    MakeFSRefUnicode
    Create an FSRef for an existing object specified by 
    Parent FSRef and Unicode name.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  ref             A pointer to the parent directory FSRef
    ->  name            A pointer to Unicde name
    ->  nameLength      The length of the Unicode Name
    ->  textEncodingHint A suggested text encoding to use for the name
    <-  newRef          A pointer to an FSRef
*/
/*
 *  FSMakeFSRefUnicode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSMakeFSRefUnicode(
  const FSRef *    parentRef,
  UniCharCount     nameLength,
  const UniChar *  name,
  TextEncoding     textEncodingHint,
  FSRef *          newRef);


/*
 *  PBMakeFSRefUnicodeSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBMakeFSRefUnicodeSync(FSRefParam * paramBlock);


/*
 *  PBMakeFSRefUnicodeAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBMakeFSRefUnicodeAsync(FSRefParam * paramBlock);



/*
    CompareFSRefs
    Test whether two FSRefs refer to the same file or directory.
    If they do, noErr is returned.  Otherwise, an appropriate error
    (such as errFSRefsDifferent) is returned.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  ref             A pointer to the first FSRef
    ->  parentRef       A pointer to the second FSRef
*/
/*
 *  FSCompareFSRefs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSCompareFSRefs(
  const FSRef *  ref1,
  const FSRef *  ref2);


/*
 *  PBCompareFSRefsSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBCompareFSRefsSync(FSRefParam * paramBlock);


/*
 *  PBCompareFSRefsAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBCompareFSRefsAsync(FSRefParam * paramBlock);



/*
    CreateFileUnicode
    Creates a new file.  The input filename is in Unicode.
    You can optionally set catalog info for the file.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  ref             The directory where the file is to be created
    ->  whichInfo       Which catalog info fields to set
    ->  catInfo         The values for catalog info fields to set; may be NULL
    ->  nameLength      Number of Unicode characters in the file's name
    ->  name            A pointer to the Unicode name
    <-  spec            A pointer to the FSSpec for the new directory; may be NULL
    <-  newRef          A pointer to the FSRef for the new file; may be NULL
*/
/*
 *  FSCreateFileUnicode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSCreateFileUnicode(
  const FSRef *          parentRef,
  UniCharCount           nameLength,
  const UniChar *        name,
  FSCatalogInfoBitmap    whichInfo,
  const FSCatalogInfo *  catalogInfo,       /* can be NULL */
  FSRef *                newRef,            /* can be NULL */
  FSSpec *               newSpec);          /* can be NULL */


/*
 *  PBCreateFileUnicodeSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBCreateFileUnicodeSync(FSRefParam * paramBlock);


/*
 *  PBCreateFileUnicodeAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBCreateFileUnicodeAsync(FSRefParam * paramBlock);



/*
    CreateDirectoryUnicode
    Creates a new directory.  The input directory name is in Unicode.
    You can optionally set catalog info for the directory.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  ref             The parent directory where the directory is to be created
    ->  whichInfo       Which catalog info fields to set
    ->  catInfo         The values for catalog info fields to set; may be NULL
    ->  nameLength      Number of Unicode characters in the directory's name
    ->  name            A pointer to the Unicode name
    <-  ioDirID         The DirID of the new directory
    <-  spec            A pointer to the FSSpec for the new directory; may be NULL
    <-  newRef          A pointer to the FSRef for the new directory; may be NULL
*/
/*
 *  FSCreateDirectoryUnicode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSCreateDirectoryUnicode(
  const FSRef *          parentRef,
  UniCharCount           nameLength,
  const UniChar *        name,
  FSCatalogInfoBitmap    whichInfo,
  const FSCatalogInfo *  catalogInfo,       /* can be NULL */
  FSRef *                newRef,            /* can be NULL */
  FSSpec *               newSpec,           /* can be NULL */
  UInt32 *               newDirID);         /* can be NULL */


/*
 *  PBCreateDirectoryUnicodeSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBCreateDirectoryUnicodeSync(FSRefParam * paramBlock);


/*
 *  PBCreateDirectoryUnicodeAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBCreateDirectoryUnicodeAsync(FSRefParam * paramBlock);



/*
    DeleteObject
    Deletes an existing file or directory.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  ref             The file or directory to be deleted
*/
/*
 *  FSDeleteObject()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSDeleteObject(const FSRef * ref);


/*
 *  PBDeleteObjectSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBDeleteObjectSync(FSRefParam * paramBlock);


/*
 *  PBDeleteObjectAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBDeleteObjectAsync(FSRefParam * paramBlock);



/*
    MoveObject
    Move an existing file or directory into a different directory.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  ref             The file or directory to be moved
    ->  parentRef       The file or directory will be moved into this directory
    <-  newRef          A new FSRef for the file or directory in its new location;
                        optional, may be NULL
    NOTE: Moving an object may change its FSRef.  If you want to continue to
    refer to the object, you should pass a non-NULL pointer in newRef and use
    that returned FSRef to access the object after the move.  The FSRef passed
    in "ref" may or may not be usable to access the object after it is moved.
    "newRef" may point to the same storage as "parentRef" or "ref".
*/
/*
 *  FSMoveObject()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSMoveObject(
  const FSRef *  ref,
  const FSRef *  destDirectory,
  FSRef *        newRef);             /* can be NULL */


/*
 *  PBMoveObjectSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBMoveObjectSync(FSRefParam * paramBlock);


/*
 *  PBMoveObjectAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBMoveObjectAsync(FSRefParam * paramBlock);



/*
    ExchangeObjects
    swap the contents of two files.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  ref             The first file 
    ->  parentRef       The second file 
*/
/*
 *  FSExchangeObjects()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSExchangeObjects(
  const FSRef *  ref,
  const FSRef *  destRef);


/*
 *  PBExchangeObjectsSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBExchangeObjectsSync(FSRefParam * paramBlock);


/*
 *  PBExchangeObjectsAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBExchangeObjectsAsync(FSRefParam * paramBlock);



/*
    RenameUnicode
    Change the name of an existing file or directory.  The new name is in
    Unicode.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  ref             The file or directory to be moved
    ->  nameLength      Number of Unicode characters in the new name
    ->  name            A pointer to the new Unicode name
    ->  textEncodingHint A suggested text encoding to use for the name
    <-  newRef          A new FSRef for the file or directory; may be NULL
    NOTE: Renaming an object may change its FSRef.  If you want to continue to
    refer to the object, you should pass a non-NULL pointer in newRef and use
    that returned FSRef to access the object after the rename.  The FSRef passed
    in "ref" may or may not be usable to access the object after it is renamed.
    "newRef" may point to the same storage as "ref".
*/
/*
 *  FSRenameUnicode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSRenameUnicode(
  const FSRef *    ref,
  UniCharCount     nameLength,
  const UniChar *  name,
  TextEncoding     textEncodingHint,
  FSRef *          newRef);                /* can be NULL */


/*
 *  PBRenameUnicodeSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBRenameUnicodeSync(FSRefParam * paramBlock);


/*
 *  PBRenameUnicodeAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBRenameUnicodeAsync(FSRefParam * paramBlock);



/*
    GetCatalogInfo
    Returns various information about a given file or directory.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  ref             The file or directory whose information is to be returned
    ->  whichInfo       Which catalog info fields to get
    <-  catInfo         The returned values of catalog info fields; may be NULL
    <-  spec            A pointer to the FSSpec for the object; may be NULL
    <-  parentRef       A pointer to the FSRef for the object's parent directory; may be NULL
    <-  outName         The Unicode name is returned here.  This pointer may be NULL.
    Note: All of the outputs are optional; if you don't want that particular output, just
    set its pointer to NULL.  This is the call to use to map from an FSRef to an FSSpec.
*/
/*
 *  FSGetCatalogInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSGetCatalogInfo(
  const FSRef *         ref,
  FSCatalogInfoBitmap   whichInfo,
  FSCatalogInfo *       catalogInfo,       /* can be NULL */
  HFSUniStr255 *        outName,           /* can be NULL */
  FSSpec *              fsSpec,            /* can be NULL */
  FSRef *               parentRef);        /* can be NULL */


/*
 *  PBGetCatalogInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBGetCatalogInfoSync(FSRefParam * paramBlock);


/*
 *  PBGetCatalogInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBGetCatalogInfoAsync(FSRefParam * paramBlock);



/*
    SetCatalogInfo
    Set catalog information about a given file or directory.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  ref             The file or directory whose information is to be changed
    ->  whichInfo       Which catalog info fields to set
    ->  catInfo         The new values of catalog info fields
    Note: Only some of the catalog info fields may be set.  The settable fields
    are given by the constant kFSCatInfoSettableInfo; no other bits may be set in
    whichInfo.
*/
/*
 *  FSSetCatalogInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSSetCatalogInfo(
  const FSRef *          ref,
  FSCatalogInfoBitmap    whichInfo,
  const FSCatalogInfo *  catalogInfo);


/*
 *  PBSetCatalogInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBSetCatalogInfoSync(FSRefParam * paramBlock);


/*
 *  PBSetCatalogInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBSetCatalogInfoAsync(FSRefParam * paramBlock);



/*
    OpenIterator
    Creates an FSIterator to iterate over a directory or subtree.  The
    iterator can then be passed to GetCatalogInfoBulk or CatalogSearch.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    <-  iterator        The returned FSIterator
    ->  iteratorFlags   Controls whether the iterator iterates over subtrees
                        or just the immediate children of the container.
    ->  container       An FSRef for the directory to iterate (or root of
                        the subtree to iterate).
*/
/*
 *  FSOpenIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSOpenIterator(
  const FSRef *     container,
  FSIteratorFlags   iteratorFlags,
  FSIterator *      iterator);


/*
 *  PBOpenIteratorSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBOpenIteratorSync(FSCatalogBulkParam * paramBlock);


/*
 *  PBOpenIteratorAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBOpenIteratorAsync(FSCatalogBulkParam * paramBlock);



/*
    CloseIterator
    Invalidates and disposes an FSIterator.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  iterator        The returned FSIterator
*/
/*
 *  FSCloseIterator()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSCloseIterator(FSIterator iterator);


/*
 *  PBCloseIteratorSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBCloseIteratorSync(FSCatalogBulkParam * paramBlock);


/*
 *  PBCloseIteratorAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBCloseIteratorAsync(FSCatalogBulkParam * paramBlock);



/*
    GetCatalogInfoBulk
    Iterates over catalog objects and returns information about them.
    For now, iterator must have been created with kFSIterateFlat option.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  iterator        The iterator
    ->  maximumItems    The maximum number of items to return
    <-  actualItems     The actual number of items returned
    <-  containerChanged Set to true if the container's contents changed
    ->  whichInfo       The catalog information fields to return for each item
    <-  catalogInfo     An array of catalog information; one for each returned item
    <-  refs            An array of FSRefs; one for each returned item
    <-  specs           An array of FSSpecs; one for each returned item
    <-  names           An array of filenames; one for each returned item
    Note: The catalogInfo, refs, specs, names, and containerChanged are all optional outputs;
    if you don't want that particular output, set its pointer to NULL.
*/
/*
 *  FSGetCatalogInfoBulk()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSGetCatalogInfoBulk(
  FSIterator            iterator,
  ItemCount             maximumObjects,
  ItemCount *           actualObjects,
  Boolean *             containerChanged,       /* can be NULL */
  FSCatalogInfoBitmap   whichInfo,
  FSCatalogInfo *       catalogInfos,           /* can be NULL */
  FSRef *               refs,                   /* can be NULL */
  FSSpec *              specs,                  /* can be NULL */
  HFSUniStr255 *        names);                 /* can be NULL */


/*
 *  PBGetCatalogInfoBulkSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBGetCatalogInfoBulkSync(FSCatalogBulkParam * paramBlock);


/*
 *  PBGetCatalogInfoBulkAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBGetCatalogInfoBulkAsync(FSCatalogBulkParam * paramBlock);


/*
    CatalogSearch
    Iterates over catalog objects, searching for objects that match given
    search criteria.  Returns various information about matching objects.
    For now, iterator must have been created with kFSIterateSubtree option
    and the container must have been the root directory of a volume.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  iterator        The iterator
    ->  maximumItems    The maximum number of items to return
    <-  actualItems     The actual number of items returned
    <-  containerChanged Set to true if the container's contents changed
    ->  whichInfo       The catalog information fields to return for each item
    <-  catalogInfo     An array of catalog information; one for each returned item
    <-  refs            An array of FSRefs; one for each returned item
    <-  specs           An array of FSSpecs; one for each returned item
    <-  names           An array of filenames; one for each returned item
    ->  searchParams    The criteria that controls the matching, including timeout, a bitmap
                        controlling the fields to compare, and the (Unicode) name to compare.
    Note: The catalogInfo, refs, specs, and names are all optional outputs; if you don't want
    that particular output, set its pointer to NULL.
*/
/*
 *  FSCatalogSearch()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSCatalogSearch(
  FSIterator              iterator,
  const FSSearchParams *  searchCriteria,
  ItemCount               maximumObjects,
  ItemCount *             actualObjects,
  Boolean *               containerChanged,       /* can be NULL */
  FSCatalogInfoBitmap     whichInfo,
  FSCatalogInfo *         catalogInfos,           /* can be NULL */
  FSRef *                 refs,                   /* can be NULL */
  FSSpec *                specs,                  /* can be NULL */
  HFSUniStr255 *          names);                 /* can be NULL */


/*
 *  PBCatalogSearchSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBCatalogSearchSync(FSCatalogBulkParam * paramBlock);


/*
 *  PBCatalogSearchAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBCatalogSearchAsync(FSCatalogBulkParam * paramBlock);



/*
    CreateFork
    Create a named fork for a file or directory.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  ref             The file or directory
    ->  forkNameLength  The length of the fork name (in Unicode characters)
    ->  forkName        The name of the fork to open (in Unicode)
*/
/*
 *  FSCreateFork()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSCreateFork(
  const FSRef *    ref,
  UniCharCount     forkNameLength,
  const UniChar *  forkName);            /* can be NULL */


/*
 *  PBCreateForkSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBCreateForkSync(FSForkIOParam * paramBlock);


/*
 *  PBCreateForkAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBCreateForkAsync(FSForkIOParam * paramBlock);



/*
    DeleteFork
    Delete a named fork of a file or directory.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  ref             The file or directory
    ->  forkNameLength  The length of the fork name (in Unicode characters)
    ->  forkName        The name of the fork to open (in Unicode)
*/
/*
 *  FSDeleteFork()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSDeleteFork(
  const FSRef *    ref,
  UniCharCount     forkNameLength,
  const UniChar *  forkName);            /* can be NULL */


/*
 *  PBDeleteForkSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBDeleteForkSync(FSForkIOParam * paramBlock);


/*
 *  PBDeleteForkAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBDeleteForkAsync(FSForkIOParam * paramBlock);



/*
    IterateForks
    Return the names and sizes of the forks of a file or directory.
    One fork is returned per call.
    ->  ioCompletion    A pointer to a completion routine.
    <-  ioResult        The result code of the function.
    ->  ref             The file or directory containing the forks.
    <-  positionOffset  The length of the fork, in bytes.
    <-  allocationAmount The space allocated to the fork (physical length).
    <-  outForkName     The name of the fork in Unicode.
    <>  forkIterator    Maintains state between calls for a given FSRef.
                        Before the first call, set the initialize field to zero.
*/
/*
 *  FSIterateForks()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSIterateForks(
  const FSRef *     ref,
  CatPositionRec *  forkIterator,
  HFSUniStr255 *    forkName,               /* can be NULL */
  SInt64 *          forkSize,               /* can be NULL */
  UInt64 *          forkPhysicalSize);      /* can be NULL */


/*
 *  PBIterateForksSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBIterateForksSync(FSForkIOParam * paramBlock);


/*
 *  PBIterateForksAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBIterateForksAsync(FSForkIOParam * paramBlock);



/*
    OpenFork
    Open a fork for reading and/or writing.  Allows the opened fork
    to grow beyond 2GB in size.  All volumes should support data and
    resource forks.  Other named forks may be supported by some
    volumes.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  ref             The file or directory containing the fork to open
    ->  forkNameLength  The length of the fork name (in Unicode characters)
    ->  forkName        The name of the fork to open (in Unicode)
    ->  permissions     The access (read and/or write) you want
    <-  forkRefNum      The reference number for accessing the open fork
*/
/*
 *  FSOpenFork()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSOpenFork(
  const FSRef *    ref,
  UniCharCount     forkNameLength,
  const UniChar *  forkName,             /* can be NULL */
  SInt8            permissions,
  SInt16 *         forkRefNum);


/*
 *  PBOpenForkSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBOpenForkSync(FSForkIOParam * paramBlock);


/*
 *  PBOpenForkAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBOpenForkAsync(FSForkIOParam * paramBlock);



/*
    ReadFork
    Read data from a fork opened via OpenFork.  The first byte to read is
    indicated by a combination of positionMode and positionOffset.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  forkRefNum      The reference number of the fork to read from
    <-  buffer          Pointer to buffer where data will be returned
    ->  requestCount    The number of bytes to read
    <-  actualCount     The number of bytes actually read
    ->  positionMode    The base location for start of read
    ->  positionOffset  The offset from base location for start of read
*/
/*
 *  FSReadFork()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSReadFork(
  SInt16       forkRefNum,
  UInt16       positionMode,
  SInt64       positionOffset,
  ByteCount    requestCount,
  void *       buffer,
  ByteCount *  actualCount);         /* can be NULL */


/*
 *  PBReadForkSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBReadForkSync(FSForkIOParam * paramBlock);


/*
 *  PBReadForkAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBReadForkAsync(FSForkIOParam * paramBlock);



/*
    WriteFork
    Write data to a fork opened via OpenFork.  The first byte to write is
    indicated by a combination of positionMode and positionOffset.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  forkRefNum      The reference number of the fork to write to
    ->  buffer          Pointer to data to write
    ->  requestCount    The number of bytes to write
    <-  actualCount     The number of bytes actually written
    ->  positionMode    The base location for start of write
    ->  positionOffset  The offset from base location for start of write
*/
/*
 *  FSWriteFork()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSWriteFork(
  SInt16        forkRefNum,
  UInt16        positionMode,
  SInt64        positionOffset,
  ByteCount     requestCount,
  const void *  buffer,
  ByteCount *   actualCount);         /* can be NULL */


/*
 *  PBWriteForkSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBWriteForkSync(FSForkIOParam * paramBlock);


/*
 *  PBWriteForkAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBWriteForkAsync(FSForkIOParam * paramBlock);



/*
    GetForkPosition
    Get the current (default) position of a fork that was
    opened via OpenFork.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  forkRefNum      The reference number of the fork
    <-  positionOffset  The current position of the fork
*/
/*
 *  FSGetForkPosition()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSGetForkPosition(
  SInt16    forkRefNum,
  SInt64 *  position);


/*
 *  PBGetForkPositionSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBGetForkPositionSync(FSForkIOParam * paramBlock);


/*
 *  PBGetForkPositionAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBGetForkPositionAsync(FSForkIOParam * paramBlock);



/*
    SetForkPosition
    Set the current (default) position of a fork that was
    opened via OpenFork.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  forkRefNum      The reference number of the fork
    ->  positionMode    The base location for the new position
    ->  positionOffset  The offset of the new position from the base
*/
/*
 *  FSSetForkPosition()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSSetForkPosition(
  SInt16   forkRefNum,
  UInt16   positionMode,
  SInt64   positionOffset);


/*
 *  PBSetForkPositionSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBSetForkPositionSync(FSForkIOParam * paramBlock);


/*
 *  PBSetForkPositionAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBSetForkPositionAsync(FSForkIOParam * paramBlock);



/*
    GetForkSize
    Get the current logical size (end-of-file) of an open fork.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  forkRefNum      The reference number of the fork
    <-  positionOffset  The logical size of the fork, in bytes
*/
/*
 *  FSGetForkSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSGetForkSize(
  SInt16    forkRefNum,
  SInt64 *  forkSize);


/*
 *  PBGetForkSizeSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBGetForkSizeSync(FSForkIOParam * paramBlock);


/*
 *  PBGetForkSizeAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBGetForkSizeAsync(FSForkIOParam * paramBlock);



/*
    SetForkSize
    Set the logical size (end-of-file) of an open fork.  This
    may cause space to be allocated or deallocated.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  forkRefNum      The reference number of the fork
    ->  positionMode    The base location for the new size
    ->  positionOffset  The offset of the new size from the base
*/
/*
 *  FSSetForkSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSSetForkSize(
  SInt16   forkRefNum,
  UInt16   positionMode,
  SInt64   positionOffset);


/*
 *  PBSetForkSizeSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBSetForkSizeSync(FSForkIOParam * paramBlock);


/*
 *  PBSetForkSizeAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBSetForkSizeAsync(FSForkIOParam * paramBlock);



/*
    AllocateFork
    Allocate space to an open fork.  Typically, the space to be
    allocated is beyond the current size of the fork, to reserve
    space so the file will be able to grow later.  Some volume
    formats are unable to allocate space beyond the logical size
    of the fork.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  forkRefNum      The reference number of the fork
    ->  positionMode    The base location for start of allocation
    ->  positionOffset  The offset of the start of allocation
    ->  allocationFlags Zero or more of the following flags:
        kFSAllocContiguousMask
                Any newly allocated space must be one contiguous piece.
        kFSAllocAllOrNothingMask
                All of the request space must be available, or the call
                will fail.  (If not set, the call may succeed even though
                some of the requested space wasn't allocated.)
        kFSAllocNoRoundUpMask
                Do not allocate additional space.  (If not set, a volume
                may allocate additional space in order to reduce fragmentation.)
    <>  allocationAmount    The number of bytes to allocate
                            On output, the number of bytes actually added
*/
/*
 *  FSAllocateFork()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSAllocateFork(
  SInt16              forkRefNum,
  FSAllocationFlags   flags,
  UInt16              positionMode,
  SInt64              positionOffset,
  UInt64              requestCount,
  UInt64 *            actualCount);         /* can be NULL */


/*
 *  PBAllocateForkSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBAllocateForkSync(FSForkIOParam * paramBlock);


/*
 *  PBAllocateForkAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBAllocateForkAsync(FSForkIOParam * paramBlock);



/*
    FlushFork
    Flush a fork.  Any data written to this fork refnum is flushed to the device.
    The volume's control structures are also flushed to the device.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  forkRefNum      The reference number of the fork to flush
*/
/*
 *  FSFlushFork()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSFlushFork(SInt16 forkRefNum);


/*
 *  PBFlushForkSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBFlushForkSync(FSForkIOParam * paramBlock);


/*
 *  PBFlushForkAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBFlushForkAsync(FSForkIOParam * paramBlock);



/*
    CloseFork
    Flush and close a fork.  Any data written to this fork refnum is flushed
    to the device.  The volume's control structures are also flushed to the device.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  forkRefNum      The reference number of the fork to close
*/
/*
 *  FSCloseFork()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSCloseFork(SInt16 forkRefNum);


/*
 *  PBCloseForkSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBCloseForkSync(FSForkIOParam * paramBlock);


/*
 *  PBCloseForkAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBCloseForkAsync(FSForkIOParam * paramBlock);



/*
    GetForkCBInfo
    Return information about an open fork.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    <>  desiredRefNum   If non-zero on input, then get information for this refnum;
                        unchanged on output.  If zero on input, iterate over all open
                        forks (possibly limited to a single volume); on output, contains
                        the fork's refnum.
    ->  volumeRefNum    Used when desiredRefNum is zero on input.  Set to 0 to iterate over all
                        volumes, or set to a FSVolumeRefNum to limit iteration to that volume.
    <>  iterator        Used when desiredRefNum is zero on input.  Set to 0 before iterating.
                        Pass the iterator returned by the previous call to continue iterating.
    <-  actualRefNum    The refnum of the open fork.
    <-  ref             The FSRef for the file or directory that contains the fork.
    <-  forkInfo        Various information about the open fork.
    <-  outForkName     The name of the fork
    Note: the foundRefNum, ref, forkInfo, and fork name outputs are all optional; if you don't want
    a particular output, then set its pointer to NULL.  If forkName is NULL, then forkNameLength
    will be undefined.
    Note: Returning the forkInfo generally does not require a disk access.  Returning the
    ref or forkName may cause disk access for some volume formats.
*/
/*
 *  FSGetForkCBInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSGetForkCBInfo(
  SInt16           desiredRefNum,
  FSVolumeRefNum   volume,
  SInt16 *         iterator,            /* can be NULL */
  SInt16 *         actualRefNum,        /* can be NULL */
  FSForkInfo *     forkInfo,            /* can be NULL */
  FSRef *          ref,                 /* can be NULL */
  HFSUniStr255 *   outForkName);        /* can be NULL */


/*
 *  PBGetForkCBInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBGetForkCBInfoSync(FSForkCBInfoParam * paramBlock);


/*
 *  PBGetForkCBInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBGetForkCBInfoAsync(FSForkCBInfoParam * paramBlock);



/*
    GetVolumeInfo
    Returns various information about a given volume, or indexing over all volumes.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    <>  ioVRefNum       On input, the volume reference number or drive number whose
                        information is to be returned (if volumeIndex is 0); same
                        as "volume" input to FSGetVolumeInfo.
                        On output, the actual volume reference number; same as
                        "actualVolume" output of FSGetVolumeInfo.
    ->  volumeIndex     The index of the desired volume, or 0 to use ioVRefNum
    ->  whichInfo       Which volInfo info fields to get
    <-  volumeInfo      The returned values of Volume info fields; may be NULL
    <-  name            The Unicode name is returned here.  This pointer may be NULL.
    Note: All of the outputs are optional; if you don't want that particular output, just
    set its pointer to NULL.
*/
/*
 *  FSGetVolumeInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSGetVolumeInfo(
  FSVolumeRefNum       volume,
  ItemCount            volumeIndex,
  FSVolumeRefNum *     actualVolume,        /* can be NULL */
  FSVolumeInfoBitmap   whichInfo,
  FSVolumeInfo *       info,                /* can be NULL */
  HFSUniStr255 *       volumeName,          /* can be NULL */
  FSRef *              rootDirectory);      /* can be NULL */


/*
 *  PBGetVolumeInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBGetVolumeInfoSync(FSVolumeInfoParam * paramBlock);


/*
 *  PBGetVolumeInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBGetVolumeInfoAsync(FSVolumeInfoParam * paramBlock);



/*
    SetVolumeInfo
    Set information about a given volume.
    ->  ioCompletion    A pointer to a completion routine
    <-  ioResult        The result code of the function
    ->  ioVRefNum       The volume whose information is to be changed
    ->  whichInfo       Which catalog info fields to set
    ->  volumeInfo      The new values of volume info fields
    Note: Only some of the volume info fields may be set.  The settable fields
    are given by the constant kFSVolInfoSettableInfo; no other bits may be set in
    whichInfo.
*/
/*
 *  FSSetVolumeInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSSetVolumeInfo(
  FSVolumeRefNum        volume,
  FSVolumeInfoBitmap    whichInfo,
  const FSVolumeInfo *  info);


/*
 *  PBSetVolumeInfoSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
PBSetVolumeInfoSync(FSVolumeInfoParam * paramBlock);


/*
 *  PBSetVolumeInfoAsync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern void 
PBSetVolumeInfoAsync(FSVolumeInfoParam * paramBlock);


/*
    FSGetDataForkName
    Returns the constant for the name of the data fork (the empty string)
*/
/*
 *  FSGetDataForkName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSGetDataForkName(HFSUniStr255 * dataForkName);


/*
    FSGetResourceForkName
    Returns the constant for the name of the resource fork
    (currently "RESOURCE_FORK").
*/
/*
 *  FSGetResourceForkName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.0 and later
 */
extern OSErr 
FSGetResourceForkName(HFSUniStr255 * resourceForkName);


/*
 *  FSRefMakePath()
 *  
 *  Summary:
 *    converts an FSRef to a POSIX path
 *  
 *  Parameters:
 *    
 *    ref:
 *      the file/dir to get the POSIX path for
 *    
 *    path:
 *      a pointer to a buffer which FSRefMakePath will fill with a UTF8
 *      encoded C string representing the path the the specified FSRef
 *    
 *    maxPathSize:
 *      the maximum size path length in bytes that path can hold
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FSRefMakePath(
  const FSRef *  ref,
  UInt8 *        path,
  UInt32         maxPathSize);


/*
 *  FSPathMakeRef()
 *  
 *  Summary:
 *    converts a POSIX path to an FSRef
 *  
 *  Parameters:
 *    
 *    path:
 *      a pointer to a UTF8 encoded C String that is a POSIX path
 *    
 *    ref:
 *      a pointer to an FSRef to fill in
 *    
 *    isDirectory:
 *      an optional pointer to a Boolean that will be filled in with
 *      whether the specified path is a directory (vs. a file)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FSPathMakeRef(
  const UInt8 *  path,
  FSRef *        ref,
  Boolean *      isDirectory);      /* can be NULL */




/*
 *  FNMessage
 *  
 *  Discussion:
 *    Messages broadcast about a directory.  If system clients (such as
 *    the Finder) are interested in changes to a directory, they will
 *    receive notifications when application code broadcasts change
 *    messages about that directory.
 */

  /*
   */
typedef UInt32 FNMessage;
enum {
  kFNDirectoryModifiedMessage   = 1
};

/*
 *  FNNotify()
 *  
 *  Summary:
 *    Broadcasts notification of changes to the specified directory.
 *  
 *  Parameters:
 *    
 *    ref:
 *      The directory for which to broadcast the notification
 *    
 *    message:
 *      An indication of what happened to the target directory
 *    
 *    flags:
 *      Options about delivery of the notification (specify kNilOptions
 *      for default behaviour)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FNNotify(
  const FSRef *  ref,
  FNMessage      message,
  OptionBits     flags);


/*
 *  FNNotifyByPath()
 *  
 *  Summary:
 *    Broadcasts notification of changes to the specified directory.
 *  
 *  Parameters:
 *    
 *    path:
 *      Path to the directory for which to broadcast the notification
 *    
 *    message:
 *      An indication of what happened to the target directory
 *    
 *    flags:
 *      Options about delivery of the notification (specify kNilOptions
 *      for default behaviour)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FNNotifyByPath(
  const UInt8 *  path,
  FNMessage      message,
  OptionBits     flags);


/*
 *  FNNotifyAll()
 *  
 *  Discussion:
 *    Broadcasts notification of changes to the filesystem (should only
 *    be used by installers or programs which make lots of changes and
 *    only send one broadcast).
 *  
 *  Parameters:
 *    
 *    message:
 *      An indication of what happened
 *    
 *    flags:
 *      Options about delivery of the notification (specify kNilOptions
 *      for default behaviour)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FNNotifyAll(
  FNMessage    message,
  OptionBits   flags);




/*
 *  FNSubscriptionRef
 *  
 *  Discussion:
 *    A token associated with a notification subscription.  The
 *    subscriber gets one back when they subscribe to notifications for
 *    a particular directory, and they supply it when the unsubscribe. 
 *    It is also delivered along with the notifications for that
 *    subscription.
 */
typedef struct OpaqueFNSubscriptionRef*  FNSubscriptionRef;

/*
 *  Discussion:
 *    Options that can be specified at subscription time.
 */

  /*
   * Specify this option if you do not want to receive notifications on
   * this subscription when FNNotifyAll is called; by default any
   * subscription is also implicitly a subscription to wildcard
   * notifications
   */
enum {
  kFNNoImplicitAllSubscription  = (1 << 0)
};


/*
 *  FNSubscriptionProcPtr
 *  
 *  Discussion:
 *    Callback delivered for directory notifications.
 *  
 *  Parameters:
 *    
 *    message:
 *      An indication of what happened
 *    
 *    flags:
 *      Options about delivery of the notification (typically
 *      kNilOptions)
 *    
 *    refcon:
 *      User reference supplied with subscription
 *    
 *    subscription:
 *      Subscription corresponding to this notification
 */
typedef CALLBACK_API_C( void , FNSubscriptionProcPtr )(FNMessage message, OptionBits flags, void *refcon, FNSubscriptionRef subscription);
typedef STACK_UPP_TYPE(FNSubscriptionProcPtr)                   FNSubscriptionUPP;
/*
 *  NewFNSubscriptionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib on Mac OS X
 *    Non-Carbon CFM:   available as macro/inline
 */
extern FNSubscriptionUPP
NewFNSubscriptionUPP(FNSubscriptionProcPtr userRoutine);

/*
 *  DisposeFNSubscriptionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib on Mac OS X
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeFNSubscriptionUPP(FNSubscriptionUPP userUPP);

/*
 *  InvokeFNSubscriptionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib on Mac OS X
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeFNSubscriptionUPP(
  FNMessage          message,
  OptionBits         flags,
  void *             refcon,
  FNSubscriptionRef  subscription,
  FNSubscriptionUPP  userUPP);

/*
 *  FNSubscribe()
 *  
 *  Summary:
 *    Subscribe to change notifications for the specified directory.
 *  
 *  Parameters:
 *    
 *    directoryRef:
 *      Directory for which the caller wants notifications
 *    
 *    callback:
 *      Function to call back when a notification arrives
 *    
 *    refcon:
 *      User state carried with the subscription
 *    
 *    flags:
 *      Options for future use (specify kNilOptions, or one of the
 *      FNSubscriptionOptions)
 *    
 *    subscription:
 *      Subscription token for subsequent query or unsubscription
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FNSubscribe(
  const FSRef *        directoryRef,
  FNSubscriptionUPP    callback,
  void *               refcon,
  OptionBits           flags,
  FNSubscriptionRef *  subscription);


/*
 *  FNSubscribeByPath()
 *  
 *  Summary:
 *    Subscribe to change notifications for the specified directory.
 *  
 *  Parameters:
 *    
 *    directoryPath:
 *      Directory for which the caller wants notifications
 *    
 *    callback:
 *      Function to call back when a notification arrives
 *    
 *    refcon:
 *      User state carried with the subscription
 *    
 *    flags:
 *      Options for future use (specify kNilOptions, or one of the
 *      FNSubscriptionOptions)
 *    
 *    subscription:
 *      Subscription token for subsequent query or unsubscription
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FNSubscribeByPath(
  const UInt8 *        directoryPath,
  FNSubscriptionUPP    callback,
  void *               refcon,
  OptionBits           flags,
  FNSubscriptionRef *  subscription);


/*
 *  FNUnsubscribe()
 *  
 *  Summary:
 *    Release a subscription which is no longer needed.
 *  
 *  Parameters:
 *    
 *    subscription:
 *      Subscription previously returned from FNSubscribe or
 *      FNSubscribeForPath
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FNUnsubscribe(FNSubscriptionRef subscription);


/*
 *  FNGetDirectoryForSubscription()
 *  
 *  Summary:
 *    Fetch the directory for which this subscription was originally
 *    entered. There is no path variant because paths are fragile, and
 *    the path may have changed.  If the caller does not care about
 *    this subtlety, she can call FSRefMakePath to get a path from the
 *    returned ref.
 *  
 *  Parameters:
 *    
 *    subscription:
 *      Subscription previously returned from FNSubscribe or
 *      FNSubscribeForPath
 *    
 *    ref:
 *      Directory for which this subscription was created
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FNGetDirectoryForSubscription(
  FNSubscriptionRef   subscription,
  FSRef *             ref);



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

#endif /* __FILES__ */

