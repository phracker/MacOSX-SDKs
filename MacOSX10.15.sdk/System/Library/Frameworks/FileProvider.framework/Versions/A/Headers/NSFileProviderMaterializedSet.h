//
//  NSFileProviderMaterializedSet.h
//  FileProvider
//
//  Copyright (c) 2018 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderExtension.h>
#import <FileProvider/NSFileProviderManager.h>

@interface NSFileProviderExtension (MaterializedSet)

/**
 Called by the system if the set of materialized items changes.

 Materialized items are items that have synced to disk and are not
 dataless.  They may contain a mix of dataless and materialized files and
 directories, but in any case, all their children are represented on disk.
 Traversals of dataless directories by applications trigger an enumeration
 against the file provider extension; traversals of materialized directories
 do not.  It is the responsability of the file provider extension to notify
 the system on remote changes of these files: there is no alternative cache
 invalidation mechanism.

 If the extension doesn't keep track of the materialized set, it will have to
 notify the system of all remote changes.  In that case the working set is the
 entire dataset.  The system may drop items whose parent isn't materialized, to
 avoid unnecessary disk usage.  This saves some I/O, but isn't optimal.  The
 filtering by parentItemIdentifier is better done in the extension;  ideally,
 it would even be done server-side.  A hybrid model is possible, where some
 filtering is done server-side, and some finer filtering is done client-side.

 The file provider extension should therefore keep a list of the identifiers of
 the materialized directories.  This method is called when a new directory is
 materialized or when a materialized directory is rendered dataless.

 To enumerate the set of materialized containers,
 - Call -enumeratorForMaterializedItems on the instance of
   NSFileProviderManager corresponding to your domain;
 - Implement the NSFileProviderEnumerationObserver and
   NSFileProviderChangeObserver on an object;
 - Pass that object to the enumerator;
 - Use the identifiers of items or changes you receive to note the
   materialization status in your database.

 When an item is created, modified or deleted remotely, the file provider
 extension should check whether its parentItemIdentifier is in the materialized
 set.  If it is, the extension needs to inform the system so the system may
 create, modify or delete the file or directory (initially dataless) on disk.
 In the case when an item is reparented, the test should be that either the new
 or the old parentItemIdentifier is in the materialized set.  No need to pretend
 that the iten was deleted if the new parentItemIdentifier is no longer in the
 materialized set: the system will know what to do with an unknown parent
 identifier.

 To notify the system of this created, modified or deleted item,
 - Call -signalEnumeratorForContainerItemIdentifier: on the working set, i.e the
   container identified by NSFileProviderWorkingSetContainerItemIdentifier;
 - Include this item in the next enumeration of the working set.
 */
- (void)materializedItemsDidChangeWithCompletionHandler:(void (^)(void))completionHandler API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

@end

@interface NSFileProviderManager (MaterializedSet)

/**
 Returns an enumerator for the set of materialized containers.

 This enumerator is unlike other enumerators because the roles of the system
 and the extension are reversed:
 - The system enumerates the working set after the extension calls
   'signalEnumeratorForContainerItemIdentifier';
 - The extension enumerates the materialized set after the system calls
   'materializedContainersDidChangeWithCompletionHandler'.
 */
- (id<NSFileProviderEnumerator>)enumeratorForMaterializedItems API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

@end

