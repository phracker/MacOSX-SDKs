//
//  NSFileProviderDomain.h
//  FileProvider
//
//  Copyright © 2017-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FileProvider/NSFileProviderExtension.h>


NS_ASSUME_NONNULL_BEGIN

FILEPROVIDER_API_AVAILABILITY_V2_V3
typedef NSString *NSFileProviderDomainIdentifier NS_EXTENSIBLE_STRING_ENUM;

/**
 File provider domain version.

 This object can be used by the `NSFileProviderReplicatedExtension` to describe the
 current version of the domain. This object is immutable and can safely be used as
 a key in a dictionary.
 */
FILEPROVIDER_API_AVAILABILITY_V3_1
@interface NSFileProviderDomainVersion : NSObject <NSSecureCoding>

/** Build a version that is strictly greater than the receiver.
 */
- (NSFileProviderDomainVersion *)next;

/** Compare two domain versions.

 This returns the NSComparisonResult of the comparison of the receiver and the
 other version:
  - NSOrderedAscending if the receiver predates the otherVersion
  - NSOrderedDescending if the otherVersion predates the receiver
  - NSOrderedSame if both versions are equal

 In Swift, NSFileProviderDomainVersion is comparable.
 */
- (NSComparisonResult)compare:(NSFileProviderDomainVersion *)otherVersion NS_REFINED_FOR_SWIFT;

@end

/** Testing modes.
 */
FILEPROVIDER_API_AVAILABILITY_V3_1
typedef NS_OPTIONS(NSUInteger, NSFileProviderDomainTestingModes) {
    /** Enable the domain without any user action required.
     */
    NSFileProviderDomainTestingModeAlwaysEnabled = 1 << 0,

    /** Enable interactive mode.

     Disable the automatic scheduling from the system and allow external tools to
     control the execution of operations.

     When manual scheduling is enabled, an external tool should use
     -[NSFileProviderManager listAvailableTestingOperationsWithError:] and
     -[NSFileProviderManager runTestingOperations:error:] to control the system.

     If that mode is enabled, some crash recovery guarantees are lost. For instance,
     the system may lose any event that hasn't been ingested. The system does not
     support removing this mode from a domain on which it has been enabled.
     */
    NSFileProviderDomainTestingModeInteractive = 1 << 1
} NS_SWIFT_NAME(NSFileProviderDomain.TestingModes);

/**
 File provider domain.

 A file provider domain can be used to represent accounts or different locations
 exposed within a given file provider.

 Domains can be registered to the system using
 @c -[NSFileProviderMananger addDomain:completionHandler:]

 By default, a file provider extension does not have any domain.

 On the extension side, a separate instance of NSFileProviderExtension will be
 created for each @c NSFileProviderDomain registered.  In that case, the
 @c NSFileProviderExtension.domain properties will indicate which domain the
 NSFileProviderExtension belongs to (or nil if none).

 All the files on disk belonging to the same domain must be grouped inside a
 common directory. That directory path is indicated by the
 @p pathRelativeToDocumentStorage property.
 */
FILEPROVIDER_API_AVAILABILITY_V2_V3
@interface NSFileProviderDomain : NSObject

/**
 Initialize a new NSFileProviderDomain

 The file provider extension implementation can pick any @c identifier as it sees
 fit to identify the group of items. The identifier must not contain any characters from this set: [/:]

 @param displayName a user visible string representing the group of items the
 file provider extension is using.

 @param pathRelativeToDocumentStorage a path relative to
 @c NSFileProviderExtension.documentStorageURL.
 */
- (instancetype)initWithIdentifier:(NSFileProviderDomainIdentifier)identifier displayName:(NSString *)displayName pathRelativeToDocumentStorage:(NSString *)pathRelativeToDocumentStorage FILEPROVIDER_API_AVAILABILITY_V2;

/**
 Initialize a new NSFileProviderDomain

 The file provider extension implementation can pick any @c identifier as it sees
 fit to identify the group of items. The identifier must not contain any characters from this set: [/:]

 @param displayName a user visible string representing the group of items the
 file provider extension is using.
 */
- (instancetype)initWithIdentifier:(NSFileProviderDomainIdentifier)identifier displayName:(NSString *)displayName FILEPROVIDER_API_AVAILABILITY_V3;

/**
 The identifier - as provided by the file provider extension.
 */
@property (readonly, copy) NSFileProviderDomainIdentifier identifier;

/**
 The display name shown by the system to represent this domain.
 */
@property (readonly, copy) NSString *displayName;

/**
 The path relative to the document storage of the file provider extension.
 Files belonging to this domains should be stored under this path.
 */
@property (readonly, copy) NSString *pathRelativeToDocumentStorage FILEPROVIDER_API_AVAILABILITY_V2;


/** If set, the domain is present, but disconnected from its extension.
 In this state, the user continues to be able to browse the domain's contents,
 but the extension doesn't receive updates on modifications to the files, nor is
 it consulted to update folder's contents.

 The disconnected state can be modified on an existing domain via the disconnectWithReason method
 on NSFileProviderManager.
 */
@property (readonly, getter=isDisconnected) BOOL disconnected FILEPROVIDER_API_AVAILABILITY_V3;

/** If user has disabled this domain from Files.app on iOS or System Preferences on macOS, this will bet set
 to NO.
*/
@property (readonly) BOOL userEnabled FILEPROVIDER_API_AVAILABILITY_V3;

/** If this domain is not user visible.

 Typically, this can be used for dry-run migration. The files are still on disk though.
*/
@property (readwrite, assign, getter=isHidden) BOOL hidden FILEPROVIDER_API_AVAILABILITY_V3;

/** Testing modes.

 Testing modes are exposed as a means for the provider to have more control over the system in
 a testing environment. Enabling a testing mode alters the behavior of the system and enables
 some APIs for that mode.

 A process must have the com.apple.developer.fileprovider.testing-mode entitlement in order to
 configure a domain with non-empty testing modes.
 */
@property (readwrite, assign) NSFileProviderDomainTestingModes testingModes FILEPROVIDER_API_AVAILABILITY_V3_1;

/**
 Identity of the backing store of the domain on the system.

 This property only applies for extensions that implement NSFileProviderReplicatedExtension.

 This provides an identifier that uniquely identifies the backing store used by the system for
 the domain. When this identifier has changed, the system has dropped its backing store and is
 building a new one.

 The system may decide to rebuild its backing store if it got corrupted. The backing store can also
 be rebuilt as a response to the provider calling `-[NSFileProviderManager reimportItemsBelowItemWithIdentifier:completionHandler:]`.
 It is guaranteed that calling reimport on the root item will cause the backing store to be rebuilt,
 but the system can also decide to do so when reimport is called on other items.

 When rebuilding the backing store, the system will invalidate any extension instance associated
 to that domain. As a consequence, the identity of the backing store associated with that domain
 is guaranteed to be stable for the lifetime of the NSFileProviderReplicatedExtension instance.
 */
@property (nonatomic, readonly, nullable) NSData *backingStoreIdentity FILEPROVIDER_API_AVAILABILITY_V4_0;

@end

FILEPROVIDER_API_AVAILABILITY_V2
@interface NSFileProviderExtension (NSFileProviderDomain)
@property(nonatomic, readonly, nullable) NSFileProviderDomain *domain;
@end

/** Posted when any domain changed.

Interested client should then call `+[NSFileProviderManager getDomainsWithCompletionHandler:]` and see
 what changed.

 Note, this notification starts to be posted only after `+[NSFileProviderManager getDomainsWithCompletionHandler:]` is
 called.
 */
FOUNDATION_EXPORT NSNotificationName const NSFileProviderDomainDidChange
FILEPROVIDER_API_AVAILABILITY_V3;

NS_ASSUME_NONNULL_END

