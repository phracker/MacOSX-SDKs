/*
     File:       CarbonCore/NameRegistry.h
 
     Contains:   NameRegistry Interfaces
 
     Version:    CarbonCore-682.26~1
 
     Copyright:  © 1993-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __NAMEREGISTRY__
#define __NAMEREGISTRY__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#pragma options align=power

/*******************************************************************************
 * 
 * Foundation Types
 *
 */
/* Value of a property */
typedef void *                          RegPropertyValue;
/* Length of property value */
typedef UInt32                          RegPropertyValueSize;
/*******************************************************************************
 * 
 * RegEntryID   :   The Global x-Namespace Entry Identifier
 *
 */
typedef struct OpaqueDeviceNodePtr*     DeviceNodePtr;
struct RegEntryID {
  unsigned short      es_ver;
  unsigned short      es_gen;
  DeviceNodePtr       es_devid;
  unsigned long       es_spare1;
  unsigned long       es_spare2;
};
typedef struct RegEntryID               RegEntryID;
typedef RegEntryID *                    RegEntryIDPtr;
/*    
    For Copland, RegEntryID was renamed RegEntryRef.  Add typedef in case
    any source code switched to use the new name.
*/
typedef RegEntryID                      RegEntryRef;
/*******************************************************************************
 *
 * Root Entry Name Definitions  (Applies to all Names in the RootNameSpace)
 *
 *  ¥ Names are a colon-separated list of name components.  Name components
 *    may not themselves contain colons.  
 *  ¥ Names are presented as null-terminated ASCII character strings.
 *  ¥ Names follow similar parsing rules to Apple file system absolute
 *    and relative paths.  However the '::' parent directory syntax is
 *    not currently supported.
 */
/* Max length of Entry Name */
enum {
  kRegCStrMaxEntryNameLength    = 47
};

/* Entry Names are single byte ASCII */
typedef char                            RegCStrEntryName;
typedef char *                          RegCStrEntryNamePtr;
/* length of RegCStrEntryNameBuf =  kRegCStrMaxEntryNameLength+1*/
typedef char                            RegCStrEntryNameBuf[48];
typedef char                            RegCStrPathName;
typedef UInt32                          RegPathNameSize;
enum {
  kRegPathNameSeparator         = ':',  /* 0x3A */
  kRegEntryNameTerminator       = 0x00, /* '\0' */
  kRegPathNameTerminator        = 0x00  /* '\0' */
};

/*******************************************************************************
 *
 * Property Name and ID Definitions
 *  (Applies to all Properties Regardless of NameSpace)
 */
enum {
  kRegMaximumPropertyNameLength = 31,   /* Max length of Property Name */
  kRegPropertyNameTerminator    = 0x00  /* '\0' */
};

typedef char                            RegPropertyNameBuf[32];
typedef char                            RegPropertyName;
typedef char *                          RegPropertyNamePtr;
enum {
  kRegMaxPropertyNameLength     = kRegMaximumPropertyNameLength
};

/*******************************************************************************
 *
 * Iteration Operations
 *
 *  These specify direction when traversing the name relationships
 */
typedef UInt32                          RegIterationOp;
typedef RegIterationOp                  RegEntryIterationOp;
enum {
                                        /* Absolute locations*/
  kRegIterRoot                  = 0x00000002, /* "Upward" Relationships */
  kRegIterParents               = 0x00000003, /* include all  parent(s) of entry */
                                        /* "Downward" Relationships*/
  kRegIterChildren              = 0x00000004, /* include all children */
  kRegIterSubTrees              = 0x00000005, /* include all sub trees of entry */
  kRegIterDescendants           = 0x00000005, /* include all descendants of entry */
                                        /* "Horizontal" Relationships */
  kRegIterSibling               = 0x00000006, /* include all siblings */
                                        /* Keep doing the same thing*/
  kRegIterContinue              = 0x00000001
};

/*******************************************************************************
 *
 * Name Entry and Property Modifiers
 *
 *
 *
 * Modifiers describe special characteristics of names
 * and properties.  Modifiers might be supported for
 * some names and not others.
 * 
 * Device Drivers should not rely on functionality
 * specified as a modifier.
 */
typedef UInt32                          RegModifiers;
typedef RegModifiers                    RegEntryModifiers;
typedef RegModifiers                    RegPropertyModifiers;
enum {
  kRegNoModifiers               = 0x00000000, /* no entry modifiers in place */
  kRegUniversalModifierMask     = 0x0000FFFF, /* mods to all entries */
  kRegNameSpaceModifierMask     = 0x00FF0000, /* mods to all entries within namespace */
  kRegModifierMask              = (long)0xFF000000 /* mods to just this entry */
};

/* Universal Property Modifiers */
enum {
  kRegPropertyValueIsSavedToNVRAM = 0x00000020, /* property is non-volatile (saved in NVRAM) */
  kRegPropertyValueIsSavedToDisk = 0x00000040 /* property is non-volatile (saved on disk) */
};

/* NameRegistry version, Gestalt/PEF-style -- MUST BE KEPT IN SYNC WITH MAKEFILE !! */
enum {
  LatestNR_PEFVersion           = 0x01030000 /* latest NameRegistryLib version (Gestalt/PEF-style) */
};

/* ///////////////////////
//
// The Registry API
//
/////////////////////// */
/* NameRegistry dispatch indexes */
enum {
  kSelectRegistryEntryIDInit    = 0,
  kSelectRegistryEntryIDCompare = 1,
  kSelectRegistryEntryIDCopy    = 2,
  kSelectRegistryEntryIDDispose = 3,
  kSelectRegistryCStrEntryCreate = 4,
  kSelectRegistryEntryDelete    = 5,
  kSelectRegistryEntryCopy      = 6,
  kSelectRegistryEntryIterateCreate = 7,
  kSelectRegistryEntryIterateDispose = 8,
  kSelectRegistryEntryIterateSet = 9,
  kSelectRegistryEntryIterate   = 10,
  kSelectRegistryEntrySearch    = 11,
  kSelectRegistryCStrEntryLookup = 12,
  kSelectRegistryEntryToPathSize = 13,
  kSelectRegistryCStrEntryToPath = 14,
  kSelectRegistryCStrEntryToName = 15,
  kSelectRegistryPropertyCreate = 16,
  kSelectRegistryPropertyDelete = 17,
  kSelectRegistryPropertyRename = 18,
  kSelectRegistryPropertyIterateCreate = 19,
  kSelectRegistryPropertyIterateDispose = 20,
  kSelectRegistryPropertyIterate = 21,
  kSelectRegistryPropertyGetSize = 22,
  kSelectRegistryPropertyGet    = 23,
  kSelectRegistryPropertySet    = 24,
  kSelectRegistryEntryGetMod    = 25,
  kSelectRegistryEntrySetMod    = 26,
  kSelectRegistryPropertyGetMod = 27,
  kSelectRegistryPropertySetMod = 28,
  kSelectRegistryEntryMod       = 29,
  kSelectRegistryEntryPropertyMod = 30, /* if you add more selectors here, remember to change 'kSelectRegistryHighestSelector' below*/
  kSelectRegistryHighestSelector = kSelectRegistryEntryPropertyMod
};


/* ///////////////////////
//
// Entry Management
//
/////////////////////// */

/*-------------------------------
 * EntryID handling
 */
/*
 * Initialize an EntryID to a known invalid state
 *   note: invalid != uninitialized
 */
/*
 *  RegistryEntryIDInit()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 * Compare EntryID's for equality or if invalid
 *
 * If a NULL value is given for either id1 or id2, the other id 
 * is compared with an invalid ID.  If both are NULL, the id's 
 * are consided equal (result = true). 
 */
/*
 *  RegistryEntryIDCompare()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 * Copy an EntryID
 */
/*
 *  RegistryEntryIDCopy()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 * Free an ID so it can be reused.
 */
/*
 *  RegistryEntryIDDispose()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*-------------------------------
 * Adding and removing entries
 *
 * If (parentEntry) is NULL, the name is assumed
 * to be a rooted path. It is rooted to an anonymous, unnamed root.
 */
/*
 *  RegistryCStrEntryCreate()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 *  RegistryEntryDelete()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 *  RegistryEntryCopy()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*---------------------------
 * Traversing the namespace
 *
 * To support arbitrary namespace implementations in the future,
 * I have hidden the form that the place pointer takes.  The previous
 * interface exposed the place pointer by specifying it as a
 * RegEntryID.
 *
 * I have also removed any notion of returning the entries
 * in a particular order, because an implementation might
 * return the names in semi-random order.  Many name service
 * implementations will store the names in a hashed lookup
 * table.
 *
 * Writing code to traverse some set of names consists of
 * a call to begin the iteration, the iteration loop, and
 * a call to end the iteration.  The begin call initializes
 * the iteration cookie data structure.  The call to end the 
 * iteration should be called even in the case of error so 
 * that allocated data structures can be freed.
 *
 *  Create(...)
 *  do {
 *      Iterate(...);
 *  } while (!done);
 *  Dispose(...);
 *
 * This is the basic code structure for callers of the iteration
 * interface.
 */
typedef struct OpaqueRegEntryIter*      RegEntryIter;
/* 
 * create/dispose the iterator structure
 *   defaults to root with relationship = kRegIterDescendants
 */
/*
 *  RegistryEntryIterateCreate()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 *  RegistryEntryIterateDispose()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/* 
 * set Entry Iterator to specified entry
 */
/*
 *  RegistryEntryIterateSet()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 * Return each value of the iteration
 *
 * return entries related to the current entry
 * with the specified relationship
 */
/*
 *  RegistryEntryIterate()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 * return entries with the specified property
 *
 * A NULL RegPropertyValue pointer will return an
 * entry with the property containing any value.
 */
/*
 *  RegistryEntrySearch()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*--------------------------------
 * Find a name in the namespace
 *
 * This is the fast lookup mechanism.
 * NOTE:  A reverse lookup mechanism
 *    has not been provided because
 *        some name services may not
 *        provide a fast, general reverse
 *        lookup.
 */
/*
 *  RegistryCStrEntryLookup()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*---------------------------------------------
 * Convert an entry to a rooted name string
 *
 * A utility routine to turn an Entry ID
 * back into a name string.
 */
/*
 *  RegistryEntryToPathSize()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 *  RegistryCStrEntryToPath()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 * Parse a path name.
 *
 * Retrieve the last component of the path, and
 * return a spec for the parent.
 */
/*
 *  RegistryCStrEntryToName()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/* //////////////////////////////////////////////////////
//
// Property Management
//
////////////////////////////////////////////////////// */
/*-------------------------------
 * Adding and removing properties
 */
/*
 *  RegistryPropertyCreate()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 *  RegistryPropertyDelete()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 *  RegistryPropertyRename()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*---------------------------
 * Traversing the Properties of a name
 *
 */
typedef struct OpaqueRegPropertyIter*   RegPropertyIter;
/*
 *  RegistryPropertyIterateCreate()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 *  RegistryPropertyIterateDispose()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 *  RegistryPropertyIterate()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 * Get the value of the specified property for the specified entry.
 *
 */
/*
 *  RegistryPropertyGetSize()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 * (*propertySize) is the maximum size of the value returned in the buffer
 * pointed to by (propertyValue).  Upon return, (*propertySize) is the size of the
 * value returned.
 */
/*
 *  RegistryPropertyGet()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 *  RegistryPropertySet()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/* //////////////////////////////////////////////////////
//
// Modifier Management
//
////////////////////////////////////////////////////// */
/*
 * Modifiers describe special characteristics of names
 * and properties.  Modifiers might be supported for
 * some names and not others.
 * 
 * Device Drivers should not rely on functionality
 * specified as a modifier.  These interfaces
 * are for use in writing Experts.
 */
/*
 * Get and Set operators for entry modifiers
 */
/*
 *  RegistryEntryGetMod()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 *  RegistryEntrySetMod()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 * Get and Set operators for property modifiers
 */
/*
 *  RegistryPropertyGetMod()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 *  RegistryPropertySetMod()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 * Iterator operator for entry modifier search
 */
/*
 *  RegistryEntryMod()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */


/*
 * Iterator operator for entries with matching 
 * property modifiers
 */
/*
 *  RegistryEntryPropertyMod()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   in NameRegistryLib 1.0 and later
 */




#pragma options align=reset


#endif /* __NAMEREGISTRY__ */

