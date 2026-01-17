//
//  NSFileProviderRequest.h
//  FileProvider
//
//  Copyright © 2018-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FileProvider/NSFileProviderDefines.h>
#import <FileProvider/NSFileProviderManager.h>

NS_ASSUME_NONNULL_BEGIN

FILEPROVIDER_API_AVAILABILITY_V3_IOS
@interface NSFileProviderRequest : NSObject
/**
 The request was made by the sync system, e.g. to update a file to its latest version after a remote update was pushed.

 This is only valid for NSFileProviderRequest objects passed to these methods:
 - [NSFileProviderEnumerating enumeratorForContainerItemIdentifier:]
 - [NSFileProviderReplicatedExtension fetchContentsForItemWithIdentifier:]

 For sync up methods (createItem/modifyItem/deleteItem), the system does not know which actor made the
 modifications to the file, so it cannot supply this information.
 */
@property (nonatomic, readonly) BOOL isSystemRequest;

/**
 The request was made by Finder or one of its helpers.

 This is only valid for NSFileProviderRequest objects passed to these methods:
 - [NSFileProviderEnumerating enumeratorForContainerItemIdentifier:]
 - [NSFileProviderReplicatedExtension fetchContentsForItemWithIdentifier:]

 For sync up methods (createItem/modifyItem/deleteItem), the system does not know which actor made the
 modifications to the file, so it cannot supply this information.
 */
@property (nonatomic, readonly) BOOL isFileViewerRequest;

/**
 The URL of the requesting executable. This will always be nil unless both an MDM profile key is set, and the
 provider's application is installed by an MDM profile.
*/
@property (nonatomic, readonly, copy, nullable) NSURL *requestingExecutable API_UNAVAILABLE(ios);

/**
 The version of the domain when the event that triggered the request was observed.

 If the extension doesn't implement the NSFileProviderDomainState protocol, this will be nil.
 */
@property (nonatomic, readonly, nullable) NSFileProviderDomainVersion *domainVersion FILEPROVIDER_API_AVAILABILITY_V3_1_IOS;

@end

NS_ASSUME_NONNULL_END
