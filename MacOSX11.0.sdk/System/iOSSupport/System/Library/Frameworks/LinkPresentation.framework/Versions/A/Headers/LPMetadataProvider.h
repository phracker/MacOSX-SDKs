//
//  LinkPresentation
//  Copyright © 2015-2019 Apple Inc. All rights reserved.
//

#import <LinkPresentation/LPFoundation.h>

#import <LinkPresentation/LPLinkMetadata.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An LPMetadataProvider object retrieves metadata for a given URL.

 An instance of LPMetadataProvider can only be asked to retrieve metadata once;
 a new instance should be created for each request.

 A client must have the com.apple.security.network.client entitlement
 in order to be able to use LPMetadataProvider for remote URLs.

 @see `LPLinkMetadata`
 */
LP_EXTERN API_AVAILABLE(macos(10.15), ios(13.0)) API_UNAVAILABLE(watchos, tvos)
@interface LPMetadataProvider : NSObject

/**
 Fetch metadata for the given URL.

 The completion handler will be called on a non-main queue.

 File URLs returned in the resultant LPLinkMetadata will be deleted
 when the completion handler returns.

 An exception will be thrown if this is called more than once
 on a particular LPMetadataProvider instance.
 */
- (void)startFetchingMetadataForURL:(NSURL *)URL completionHandler:(void(^)(LPLinkMetadata *_Nullable metadata, NSError *_Nullable error))completionHandler;

/**
 Cancel a metadata request.

 If the request had not already completed, the completion handler will be invoked
 with the error code `LPErrorMetadataFetchCancelled`.
 */
- (void)cancel;

/**
 A boolean value indicating whether LPMetadataProvider should download secondary
 resources specified by the metadata, like the icon, image, or video. If
 shouldFetchSubresources is set to `NO`, the returned LPLinkMetadata object will
 consist only of metadata retrieved from the main resource.
 
 The default value is `YES`.
 */
@property (nonatomic) BOOL shouldFetchSubresources;

/**
 The time interval after which the request will automatically fail if it has not
 already completed.

 If the timeout is reached, no metadata is returned; the completion handler will
 be invoked with the error code `LPErrorMetadataFetchTimedOut`.

 The default timeout is 30 seconds.
*/
@property (nonatomic) NSTimeInterval timeout;

@end

NS_ASSUME_NONNULL_END
