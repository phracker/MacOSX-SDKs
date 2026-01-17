//
//  NSFileProviderDomain.h
//  FileProvider
//
//  Copyright © 2017-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FileProvider/NSFileProviderExtension.h>


NS_ASSUME_NONNULL_BEGIN

typedef NSString *NSFileProviderDomainIdentifier NS_EXTENSIBLE_STRING_ENUM;

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
 fit to identify the group of items.

 @param displayName a user visible string representing the group of items the
 file provider extension is using.

 @param pathRelativeToDocumentStorage a path relative to
 @c NSFileProviderExtension.documentStorageURL.
 */
- (instancetype)initWithIdentifier:(NSFileProviderDomainIdentifier)identifier displayName:(NSString *)displayName pathRelativeToDocumentStorage:(NSString *)pathRelativeToDocumentStorage FILEPROVIDER_API_AVAILABILITY_V2;

/**
 Initialize a new NSFileProviderDomain

 The file provider extension implementation can pick any @c identifier as it sees
 fit to identify the group of items.

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

