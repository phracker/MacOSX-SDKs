/*
     File:       LSSharedFileList.h
 
     Contains:   Services to load and share file lists.
 
     Copyright:  Copyright 2003-2009 by Apple Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/
#ifndef __LSSHAREDFILELIST__
#define __LSSHAREDFILELIST__

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifndef __CARBONCORE__
#include <CarbonCore/CarbonCore.h>
#endif

#ifndef __ICONSCORE__
#include <LaunchServices/IconsCore.h>
#endif


#ifndef __AUTHORIZATION__
#include <Security/Authorization.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* The shared file list API is for sharing and storing list of references to file system objects.
   The shared file list is a persistent list of objects, where each item has assigned display name, icon, and url
   as well as other optional properties.

   Each list can also have various properties attached.
*/
typedef struct OpaqueLSSharedFileListRef*  LSSharedFileListRef;
typedef struct OpaqueLSSharedFileListItemRef*  LSSharedFileListItemRef;

/* list types */

/*
 *  kLSSharedFileListFavoriteVolumes
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kLSSharedFileListFavoriteVolumes                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  kLSSharedFileListFavoriteItems
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kLSSharedFileListFavoriteItems                    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  kLSSharedFileListRecentApplicationItems
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kLSSharedFileListRecentApplicationItems           AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  kLSSharedFileListRecentDocumentItems
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kLSSharedFileListRecentDocumentItems              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  kLSSharedFileListRecentServerItems
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kLSSharedFileListRecentServerItems                AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  kLSSharedFileListSessionLoginItems
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kLSSharedFileListSessionLoginItems                AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  kLSSharedFileListGlobalLoginItems
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kLSSharedFileListGlobalLoginItems                 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/* LSSharedFileList property keys */


/*
 *  kLSSharedFileListRecentItemsMaxAmount
 *  
 *  Discussion:
 *    maximum amount of items in the list.  Associated property is
 *    CFNumber
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kLSSharedFileListRecentItemsMaxAmount             AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*
 *  kLSSharedFileListVolumesComputerVisible
 *  
 *  Discussion:
 *    is Computer item visible in favorite volumes list. Associated
 *    property is CFBoolean.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kLSSharedFileListVolumesComputerVisible           AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*
 *  kLSSharedFileListVolumesIDiskVisible
 *  
 *  Discussion:
 *    is iDisk item visible in favorite volumes list. Associated
 *    property is CFBoolean.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kLSSharedFileListVolumesIDiskVisible              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*
 *  kLSSharedFileListVolumesNetworkVisible
 *  
 *  Discussion:
 *    is Network item visible in favorite volumes list. Associated
 *    property is CFBoolean.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kLSSharedFileListVolumesNetworkVisible            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* item default positions */


/*
 *  kLSSharedFileListItemBeforeFirst
 *  
 *  Discussion:
 *    A virtual item reference for inserting new item at beginning of
 *    the list.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern LSSharedFileListItemRef kLSSharedFileListItemBeforeFirst      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*
 *  kLSSharedFileListItemLast
 *  
 *  Discussion:
 *    A virtual item reference for inserting new item at end of the
 *    list.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern LSSharedFileListItemRef kLSSharedFileListItemLast             AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/* LSSharedFileListItem property keys */


/*
 *  kLSSharedFileListItemHidden
 *  
 *  Discussion:
 *    Is item hidden in UI? Associated property is CFBoolean.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kLSSharedFileListItemHidden                       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kLSSharedFileListLoginItemHidden
 *  
 *  Discussion:
 *    Should UI hide login item's window? Associated property is
 *    CFBoolean.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.6 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kLSSharedFileListLoginItemHidden                  AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* LSSharedFileListItemResolve flags */
enum {
  kLSSharedFileListNoUserInteraction = 1 << 0, /* no user interaction during resolution */
  kLSSharedFileListDoNotMountVolumes = 1 << 1 /* do not mount volumes during resolution */
};


/*
 *  LSSharedFileListChangedProcPtr
 *  
 *  Discussion:
 *    callback to use with LSSharedFileListAddObserver and
 *    LSSharedFileListRemoveObserver.
 */
typedef CALLBACK_API_C( void , LSSharedFileListChangedProcPtr )(LSSharedFileListRef inList, void *context);

/*
 *  LSSharedFileListGetTypeID()
 *  
 *  Discussion:
 *    This routine will return the CFTypeID for the LSSharedFileListRef
 *    type.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Result:
 *    CFTypeID for the LSSharedFileListRef type.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
LSSharedFileListGetTypeID(void)                               AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListItemGetTypeID()
 *  
 *  Discussion:
 *    This routine will return the CFTypeID for the
 *    LSSharedFileListItemRef type.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Result:
 *    CFTypeID for the LSSharedFileListItemRef type.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeID 
LSSharedFileListItemGetTypeID(void)                           AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListCreate()
 *  
 *  Summary:
 *    Create shared file list reference.
 *  
 *  Discussion:
 *    Creates shared file list reference to be used for changing list
 *    and reading its various properties.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    inAllocator:
 *      CFAllocatorRef used to allocate the LSSharedFileListRef object.
 *      As usual, NULL means default allocator.
 *    
 *    inListType:
 *      A constant indicating list type to create (for example
 *      kLSSharedFileListSessionLoginItems).
 *    
 *    listOptions:
 *      Additional parameters for the list type (as applicable). NULL
 *      means no options.
 *  
 *  Result:
 *    A reference to created shared file list object or NULL if
 *    creation failed. Has to be released with CFRelease when list
 *    object is not needed anymore.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern LSSharedFileListRef 
LSSharedFileListCreate(
  CFAllocatorRef   inAllocator,
  CFStringRef      inListType,
  CFTypeRef        listOptions)                               AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListSetAuthorization()
 *  
 *  Summary:
 *    Set authorization reference for the shared list.
 *  
 *  Discussion:
 *    Sets authorization reference for the shared list. Before
 *    attempting to perform a privileged operation on the shared list
 *    caller must authorize appropriate rights. For example, modifying
 *    kLSSharedFileListGlobalLoginItems list requires
 *    "system.global-login-items." right authorized.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    inList:
 *      Shared list reference.
 *    
 *    inAuthorization:
 *      Authorization reference.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSSharedFileListSetAuthorization(
  LSSharedFileListRef   inList,
  AuthorizationRef      inAuthorization)                      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListAddObserver()
 *  
 *  Summary:
 *    Add observer of shared list changes.
 *  
 *  Discussion:
 *    Adds observer of shared list changes. The provided function will
 *    be called when the list has changed (or any item property has
 *    changed).
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    inList:
 *      Shared list reference.
 *    
 *    inRunloop:
 *      Runloop to run on.
 *    
 *    inRunloopMode:
 *      Mode for runloop.
 *    
 *    callback:
 *      Function to call when list has changed.
 *    
 *    context:
 *      Context pointer defined by client.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
LSSharedFileListAddObserver(
  LSSharedFileListRef              inList,
  CFRunLoopRef                     inRunloop,
  CFStringRef                      inRunloopMode,
  LSSharedFileListChangedProcPtr   callback,
  void *                           context)                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListRemoveObserver()
 *  
 *  Summary:
 *    Remove observer of shared list changes.
 *  
 *  Discussion:
 *    Removes observer of shared list changes.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    inList:
 *      Shared list reference.
 *    
 *    inRunloop:
 *      Runloop to run on.
 *    
 *    inRunloopMode:
 *      Mode for runloop.
 *    
 *    callback:
 *      Function to call when list has changed.
 *    
 *    context:
 *      Context pointer defined by client.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
LSSharedFileListRemoveObserver(
  LSSharedFileListRef              inList,
  CFRunLoopRef                     inRunloop,
  CFStringRef                      inRunloopMode,
  LSSharedFileListChangedProcPtr   callback,
  void *                           context)                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListGetSeedValue()
 *  
 *  Summary:
 *    Return current seed value.
 *  
 *  Discussion:
 *    Returns seed value of the shared list.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    inList:
 *      Shared list reference.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern UInt32 
LSSharedFileListGetSeedValue(LSSharedFileListRef inList)      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListCopyProperty()
 *  
 *  Summary:
 *    Return property by its name.
 *  
 *  Discussion:
 *    Returns lists named property as CFTypeRef object.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    inList:
 *      Shared list reference.
 *    
 *    inPropertyName:
 *      Name of the property to return.
 *  
 *  Result:
 *    CFTypeRef containing requested property. NULL means list has no
 *    property with this name. Has to be released with CFRelease when
 *    property object is not needed anymore.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeRef 
LSSharedFileListCopyProperty(
  LSSharedFileListRef   inList,
  CFStringRef           inPropertyName)                       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListSetProperty()
 *  
 *  Summary:
 *    Set property by its name.
 *  
 *  Discussion:
 *    Set lists named property as CFTypeRef object.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    inList:
 *      Shared list reference.
 *    
 *    inPropertyName:
 *      Name of the property to return.
 *    
 *    inPropertyData:
 *      Property data to set. Pass NULL to remove existing property.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSSharedFileListSetProperty(
  LSSharedFileListRef   inList,
  CFStringRef           inPropertyName,
  CFTypeRef             inPropertyData)                       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListCopySnapshot()
 *  
 *  Summary:
 *    Create snapshot array.
 *  
 *  Discussion:
 *    Creates snapshot array, which is list of all items at the moment
 *    LSSharedFileListCopySnapshot was called.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    inList:
 *      Shared list reference.
 *    
 *    outSnapshotSeed:
 *      Returned seed value at which snapshot was taken.
 *  
 *  Result:
 *    Immutable CFArray of LSSharedFileListItemRef values. Has to be
 *    released with CFRelease when snapshot array is not needed anymore.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFArrayRef 
LSSharedFileListCopySnapshot(
  LSSharedFileListRef   inList,
  UInt32 *              outSnapshotSeed)                      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListInsertItemURL()
 *  
 *  Summary:
 *    Insert item into shared list.
 *  
 *  Discussion:
 *    Inserts item into shared list at specified location. If the item
 *    already exists in the list it will be moved and its icon, display
 *    name and properties will be updated.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    inList:
 *      Shared list reference.
 *    
 *    insertAfterThisItem:
 *      Item after which new item has to be inserted. To insert at the
 *      beginning of the list use kLSSharedFileListItemBeforeFirst or
 *      to insert at the end of the list use kLSSharedFileListItemLast.
 *    
 *    inDisplayName:
 *      Display name of the new item. Can be NULL.
 *    
 *    inIconRef:
 *      Icon of the new item. Can be NULL.
 *    
 *    inURL:
 *      URL of the new item.
 *    
 *    inPropertiesToSet:
 *      CFDictionary of properties to set. Keys are property names and
 *      values are property values. The property values are retained
 *      and copied by the API. Can be NULL.
 *    
 *    inPropertiesToClear:
 *      CFArray of property names to clear if item already exists. Can
 *      be NULL.
 *  
 *  Result:
 *    Reference to new item. Has to be released with CFRelease when the
 *    item is not needed anymore.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern LSSharedFileListItemRef 
LSSharedFileListInsertItemURL(
  LSSharedFileListRef       inList,
  LSSharedFileListItemRef   insertAfterThisItem,
  CFStringRef               inDisplayName,
  IconRef                   inIconRef,
  CFURLRef                  inURL,
  CFDictionaryRef           inPropertiesToSet,
  CFArrayRef                inPropertiesToClear)              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListInsertItemFSRef()
 *  
 *  Summary:
 *    Insert item into shared list.
 *  
 *  Discussion:
 *    Inserts item into shared list at specified location. If the item
 *    already exists in the list it will be moved and its icon, display
 *    name and properties will be updated.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    inList:
 *      Shared list reference.
 *    
 *    insertAfterThisItem:
 *      Item after which new item has to be inserted. To insert at the
 *      beginning of the list use kLSSharedFileListItemBeforeFirst or
 *      to insert at the end of the list use kLSSharedFileListItemLast.
 *    
 *    inDisplayName:
 *      Display name of the new item. Can be NULL.
 *    
 *    inIconRef:
 *      Icon of the new item. Can be NULL.
 *    
 *    inFSRef:
 *      FSRef of the new item.
 *    
 *    inPropertiesToSet:
 *      CFDictionary of properties to set. Keys are property names and
 *      values are property values. The property values are retained
 *      and copied by the API. Can be NULL.
 *    
 *    inPropertiesToClear:
 *      CFArray of property names to clear if item already exists. Can
 *      be NULL.
 *  
 *  Result:
 *    Reference to new item. Has to be released with CFRelease when the
 *    item is not needed anymore.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern LSSharedFileListItemRef 
LSSharedFileListInsertItemFSRef(
  LSSharedFileListRef       inList,
  LSSharedFileListItemRef   insertAfterThisItem,
  CFStringRef               inDisplayName,
  IconRef                   inIconRef,
  const FSRef *             inFSRef,
  CFDictionaryRef           inPropertiesToSet,
  CFArrayRef                inPropertiesToClear)              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListItemMove()
 *  
 *  Summary:
 *    Move item.
 *  
 *  Discussion:
 *    Moves item at specified location.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    inList:
 *      Shared list reference.
 *    
 *    inItem:
 *      Item to move.
 *    
 *    inMoveAfterItem:
 *      New icon of the new item. Use kLSSharedFileListItemBeforeFirst
 *      and kLSSharedFileListItemLast to move at the beginning or the
 *      end of the shared list.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSSharedFileListItemMove(
  LSSharedFileListRef       inList,
  LSSharedFileListItemRef   inItem,
  LSSharedFileListItemRef   inMoveAfterItem)                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListItemRemove()
 *  
 *  Summary:
 *    Remove item from shared list.
 *  
 *  Discussion:
 *    Removes item from shared list.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    inList:
 *      Shared list reference.
 *    
 *    inItem:
 *      Item to remove.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSSharedFileListItemRemove(
  LSSharedFileListRef       inList,
  LSSharedFileListItemRef   inItem)                           AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListRemoveAllItems()
 *  
 *  Summary:
 *    Remove all items from shared list.
 *  
 *  Discussion:
 *    Removes all items from shared list.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    inList:
 *      Shared list to clear.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSSharedFileListRemoveAllItems(LSSharedFileListRef inList)    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListItemGetID()
 *  
 *  Summary:
 *    Obtain unique item id.
 *  
 *  Discussion:
 *    Returns unique item id.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern UInt32 
LSSharedFileListItemGetID(LSSharedFileListItemRef inItem)     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListItemCopyIconRef()
 *  
 *  Summary:
 *    Obtain item's icon.
 *  
 *  Discussion:
 *    Returns icon ref for the item.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Result:
 *    IconRef to the item. Caller is responsible to releasing it by
 *    calling ReleaseIconRef().
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern IconRef 
LSSharedFileListItemCopyIconRef(LSSharedFileListItemRef inItem) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListItemCopyDisplayName()
 *  
 *  Summary:
 *    Obtain item's display name.
 *  
 *  Discussion:
 *    Returns display name of the item. Caller is responsible to
 *    releasing it by calling CFRelease().
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
LSSharedFileListItemCopyDisplayName(LSSharedFileListItemRef inItem) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListItemResolve()
 *  
 *  Summary:
 *    Resolve LSSharedFileListItemRef's item and return its FSRef.
 *  
 *  Discussion:
 *    Resolves LSSharedFileListItemRef's item and returns its FSRef.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    inItem:
 *      Item to resolve.
 *    
 *    inFlags:
 *      Resolution flags. Pass zero for default resolution flags.
 *    
 *    outURL:
 *      CFURL of original item. Can be NULL. Returned valus has to be
 *      released with CFRelease().
 *    
 *    outRef:
 *      FSRef of original item. Can be NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSSharedFileListItemResolve(
  LSSharedFileListItemRef   inItem,
  UInt32                    inFlags,
  CFURLRef *                outURL,
  FSRef *                   outRef)                           AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListItemCopyProperty()
 *  
 *  Summary:
 *    Obtain item's property by its name.
 *  
 *  Discussion:
 *    Returns persistent item's property as CF object. Caller is
 *    responsible to releasing it by calling CFRelease().
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFTypeRef 
LSSharedFileListItemCopyProperty(
  LSSharedFileListItemRef   inItem,
  CFStringRef               inPropertyName)                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  LSSharedFileListItemSetProperty()
 *  
 *  Summary:
 *    Set item property by its name.
 *  
 *  Discussion:
 *    Sets persistent item property by its name.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSSharedFileListItemSetProperty(
  LSSharedFileListItemRef   inItem,
  CFStringRef               inPropertyName,
  CFTypeRef                 inPropertyData)                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;



#ifdef __cplusplus
}
#endif

#endif /* __LSSHAREDFILELIST__ */

