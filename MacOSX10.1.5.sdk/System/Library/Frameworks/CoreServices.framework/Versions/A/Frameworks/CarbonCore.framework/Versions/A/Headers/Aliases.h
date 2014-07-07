/*
     File:       CarbonCore/Aliases.h
 
     Contains:   Alias Manager Interfaces.
 
     Version:    CarbonCore-317~6
 
     Copyright:  © 1989-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __ALIASES__
#define __ALIASES__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
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
  rAliasType                    = 'alis' /* Aliases are stored as resources of this type */
};

enum {
                                        /* define alias resolution action rules mask */
  kARMMountVol                  = 0x00000001, /* mount the volume automatically */
  kARMNoUI                      = 0x00000002, /* no user interface allowed during resolution */
  kARMMultVols                  = 0x00000008, /* search on multiple volumes */
  kARMSearch                    = 0x00000100, /* search quickly */
  kARMSearchMore                = 0x00000200, /* search further */
  kARMSearchRelFirst            = 0x00000400 /* search target on a relative path first */
};

enum {
                                        /* define alias record information types */
  asiZoneName                   = -3,   /* get zone name */
  asiServerName                 = -2,   /* get server name */
  asiVolumeName                 = -1,   /* get volume name */
  asiAliasName                  = 0,    /* get aliased file/folder/volume name */
  asiParentName                 = 1     /* get parent folder name */
};

/* ResolveAliasFileWithMountFlags options */
enum {
  kResolveAliasFileNoUI         = 0x00000001 /* no user interaction during resolution */
};

/* define the alias record that will be the blackbox for the caller */
struct AliasRecord {
  OSType              userType;               /* appl stored type like creator type */
  unsigned short      aliasSize;              /* alias record size in bytes, for appl usage */
};
typedef struct AliasRecord              AliasRecord;
typedef AliasRecord *                   AliasPtr;
typedef AliasPtr *                      AliasHandle;
/* alias record information type */
typedef short                           AliasInfoType;
/*
 *  NewAlias()
 *  
 *  Summary:
 *    create a new alias between fromFile and target, returns alias
 *    record handle
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
NewAlias(
  const FSSpec *  fromFile,       /* can be NULL */
  const FSSpec *  target,
  AliasHandle *   alias);


/*
 *  NewAliasMinimal()
 *  
 *  Summary:
 *    create a minimal new alias for a target and return alias record
 *    handle
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
NewAliasMinimal(
  const FSSpec *  target,
  AliasHandle *   alias);


/*
 *  NewAliasMinimalFromFullPath()
 *  
 *  Summary:
 *    create a minimal new alias from a target fullpath (optional zone
 *    and server name) and return alias record handle
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
NewAliasMinimalFromFullPath(
  short             fullPathLength,
  const void *      fullPath,
  ConstStr32Param   zoneName,
  ConstStr31Param   serverName,
  AliasHandle *     alias);


/*
 *  ResolveAlias()
 *  
 *  Summary:
 *    given an alias handle and fromFile, resolve the alias, update the
 *    alias record and return aliased filename and wasChanged flag.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
ResolveAlias(
  const FSSpec *  fromFile,         /* can be NULL */
  AliasHandle     alias,
  FSSpec *        target,
  Boolean *       wasChanged);


/*
 *  GetAliasInfo()
 *  
 *  Summary:
 *    given an alias handle and an index specifying requested alias
 *    information type, return the information from alias record as a
 *    string.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
GetAliasInfo(
  AliasHandle     alias,
  AliasInfoType   index,
  Str63           theString);



/*
 *  IsAliasFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern OSErr 
IsAliasFile(
  const FSSpec *  fileFSSpec,
  Boolean *       aliasFileFlag,
  Boolean *       folderFlag);


/*
 *  ResolveAliasWithMountFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 8.5 and later
 */
extern OSErr 
ResolveAliasWithMountFlags(
  const FSSpec *  fromFile,         /* can be NULL */
  AliasHandle     alias,
  FSSpec *        target,
  Boolean *       wasChanged,
  unsigned long   mountFlags);


/*
 *  ResolveAliasFile()
 *  
 *  Summary:
 *    Given a file spec, return target file spec if input file spec is
 *    an alias. It resolves the entire alias chain or one step of the
 *    chain.  It returns info about whether the target is a folder or
 *    file; and whether the input file spec was an alias or not.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
ResolveAliasFile(
  FSSpec *   theSpec,
  Boolean    resolveAliasChains,
  Boolean *  targetIsFolder,
  Boolean *  wasAliased);



/*
 *  ResolveAliasFileWithMountFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
ResolveAliasFileWithMountFlags(
  FSSpec *        theSpec,
  Boolean         resolveAliasChains,
  Boolean *       targetIsFolder,
  Boolean *       wasAliased,
  unsigned long   mountFlags);


/*
 *  FollowFinderAlias()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
FollowFinderAlias(
  const FSSpec *  fromFile,         /* can be NULL */
  AliasHandle     alias,
  Boolean         logon,
  FSSpec *        target,
  Boolean *       wasChanged);


/* 
   Low Level Routines 
*/
/*
 *  UpdateAlias()
 *  
 *  Summary:
 *    given a fromFile-target pair and an alias handle, update the
 *    alias record pointed to by alias handle to represent target as
 *    the new alias.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
UpdateAlias(
  const FSSpec *  fromFile,         /* can be NULL */
  const FSSpec *  target,
  AliasHandle     alias,
  Boolean *       wasChanged);



typedef CALLBACK_API( Boolean , AliasFilterProcPtr )(CInfoPBPtr cpbPtr, Boolean *quitFlag, Ptr myDataPtr);
typedef STACK_UPP_TYPE(AliasFilterProcPtr)                      AliasFilterUPP;
/*
 *  NewAliasFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern AliasFilterUPP
NewAliasFilterUPP(AliasFilterProcPtr userRoutine);

/*
 *  DisposeAliasFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeAliasFilterUPP(AliasFilterUPP userUPP);

/*
 *  InvokeAliasFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeAliasFilterUPP(
  CInfoPBPtr      cpbPtr,
  Boolean *       quitFlag,
  Ptr             myDataPtr,
  AliasFilterUPP  userUPP);

/*
 *  MatchAlias()
 *  
 *  Summary:
 *    Given an alias handle and fromFile, match the alias and return
 *    aliased filename(s) and needsUpdate flag
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
 */
extern OSErr 
MatchAlias(
  const FSSpec *   fromFile,          /* can be NULL */
  unsigned long    rulesMask,
  AliasHandle      alias,
  short *          aliasCount,
  FSSpecArrayPtr   aliasList,
  Boolean *        needsUpdate,
  AliasFilterUPP   aliasFilter,
  void *           yourDataPtr);




/*
 *  ResolveAliasFileWithMountFlagsNoUI()
 *  
 *  Summary:
 *    variation on ResolveAliasFile that does not prompt user with a
 *    dialog
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ResolveAliasFileWithMountFlagsNoUI(
  FSSpec *        theSpec,
  Boolean         resolveAliasChains,
  Boolean *       targetIsFolder,
  Boolean *       wasAliased,
  unsigned long   mountFlags);


/*
 *  MatchAliasNoUI()
 *  
 *  Summary:
 *    variation on MatchAlias that does not prompt user with a dialog
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
MatchAliasNoUI(
  const FSSpec *   fromFile,          /* can be NULL */
  unsigned long    rulesMask,
  AliasHandle      alias,
  short *          aliasCount,
  FSSpecArrayPtr   aliasList,
  Boolean *        needsUpdate,
  AliasFilterUPP   aliasFilter,
  void *           yourDataPtr);


/*
 *  FSNewAlias()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
FSNewAlias(
  const FSRef *  fromFile,       /* can be NULL */
  const FSRef *  target,
  AliasHandle *  inAlias);


/*
 *  FSNewAliasMinimal()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
FSNewAliasMinimal(
  const FSRef *  target,
  AliasHandle *  inAlias);


/*
 *  FSIsAliasFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
FSIsAliasFile(
  const FSRef *  fileRef,
  Boolean *      aliasFileFlag,
  Boolean *      folderFlag);



/*
 *  FSResolveAliasWithMountFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
FSResolveAliasWithMountFlags(
  const FSRef *   fromFile,         /* can be NULL */
  AliasHandle     inAlias,
  FSRef *         target,
  Boolean *       wasChanged,
  unsigned long   mountFlags);



/*
 *  FSResolveAlias()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
FSResolveAlias(
  const FSRef *  fromFile,         /* can be NULL */
  AliasHandle    alias,
  FSRef *        target,
  Boolean *      wasChanged);



/*
 *  FSResolveAliasFileWithMountFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
FSResolveAliasFileWithMountFlags(
  FSRef *         theRef,
  Boolean         resolveAliasChains,
  Boolean *       targetIsFolder,
  Boolean *       wasAliased,
  unsigned long   mountFlags);



/*
 *  FSResolveAliasFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
FSResolveAliasFile(
  FSRef *    theRef,
  Boolean    resolveAliasChains,
  Boolean *  targetIsFolder,
  Boolean *  wasAliased);



/*
 *  FSFollowFinderAlias()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
FSFollowFinderAlias(
  FSRef *       fromFile,         /* can be NULL */
  AliasHandle   alias,
  Boolean       logon,
  FSRef *       target,
  Boolean *     wasChanged);


/*
 *  FSUpdateAlias()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in InterfaceLib 9.1 and later
 */
extern OSErr 
FSUpdateAlias(
  const FSRef *  fromFile,         /* can be NULL */
  const FSRef *  target,
  AliasHandle    alias,
  Boolean *      wasChanged);





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

#endif /* __ALIASES__ */

