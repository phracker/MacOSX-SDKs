//
//  NSFileProviderDomain.h
//  FileProvider
//
//  Copyright © 2017 Apple Inc. All rights reserved.
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
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
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
- (instancetype)initWithIdentifier:(NSFileProviderDomainIdentifier)identifier displayName:(NSString *)displayName pathRelativeToDocumentStorage:(NSString *)pathRelativeToDocumentStorage;

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
@property (readonly, copy) NSString *pathRelativeToDocumentStorage;


/* If set, the domain is present, but disconnected from its extension.
 In this state, the user continues to be able to browse the domain's contents,
 but the extension doesn't receive updates on modifications to the files, nor is
 it consulted to update folder's contents.

 The disconnected state can be modified on an existing domain by recreating a domain
 with the same identifier, then passing it to addDomain.
 */
@property (readwrite, getter=isDisconnected) BOOL disconnected API_UNAVAILABLE(watchos, tvos) API_UNAVAILABLE(ios, macos);

@end

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos) API_UNAVAILABLE(watchos, tvos)
@interface NSFileProviderExtension (NSFileProviderDomain)
@property(nonatomic, readonly, nullable) NSFileProviderDomain *domain;
@end

NS_ASSUME_NONNULL_END

