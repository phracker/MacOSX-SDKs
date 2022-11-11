//
//  QLThumbnailGenerator.h
//  Quick Look Thumbnailing
//
//  Copyright (c) 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuickLookThumbnailing/QLThumbnailGenerationRequest.h>
#import <QuickLookThumbnailing/QLThumbnailErrors.h>
#import <QuickLookThumbnailing/QLThumbnailRepresentation.h>
#import <QuickLookThumbnailing/QLThumbnailingBase.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(10.15)) API_UNAVAILABLE(watchos,tvos)
QLT_EXPORT @interface QLThumbnailGenerator : NSObject

@property (class, readonly) QLThumbnailGenerator *sharedGenerator NS_SWIFT_NAME(shared);

/**
 @param completionHandler
 Always called when the thumbnail generation is over.
 The thumbnail passed to this handler is the most representative version of the thumbnail that was successfully generated (if any).
 If set, the error contains information about the issue that occurred while trying to generate the thumbnail.
 QLThumbnail error codes can be found in <QuickLookThumbnailing/QLThumbnailErrors.h>.
 */
- (void)generateBestRepresentationForRequest:(QLThumbnailGenerationRequest *)request
                           completionHandler:(void (^)(QLThumbnailRepresentation * _Nullable thumbnail, NSError * _Nullable error))completionHandler NS_SWIFT_NAME(generateBestRepresentation(for:completion:));

/**
 @param updateHandler
 Called for the successive requested representations of a thumbnail.
 If a representation was not successfully generated, this may be called with a nil representation.
 If a requested more representative version was successfully generated before a less representative one, this handler will be called only for the more representative version, skipping the less representative one.
 This handler is guaranteed to be called at least once, for the requested most representative version, whether a representation could be successfully generated or not.
 If set, the error contains information about the issue that occurred while trying to generate the representation of the given type.
 QLThumbnail error codes can be found in <QuickLookThumbnailing/QLThumbnailErrors.h>.
 */
- (void)generateRepresentationsForRequest:(QLThumbnailGenerationRequest *)request
                            updateHandler:(void (^ _Nullable)(QLThumbnailRepresentation * _Nullable thumbnail, QLThumbnailRepresentationType type, NSError * _Nullable error))updateHandler
                            NS_SWIFT_NAME(generateRepresentations(for:update:));

/**
 Cancels the given QLThumbnailGenerationRequest.
 @param request The request that should be cancelled.
 */
- (void)cancelRequest:(QLThumbnailGenerationRequest *)request;

/**
 Saves a thumbnail for the request on disk at fileURL.
 The file saved at fileURL has to be deleted when it is not used anymore.
 This is primarily intended for file provider extensions which need to upload thumbnails and have a small memory limit.

 @param contentType An image content type to save the thumbnail as, supported by CGImageDestination, such as kUTTypePNG or kUTTypeJPEG
 @param completionHandler
 Always called when the thumbnail generation is over. Will contain an error if the thumbnail could not be successfully saved to disk at fileURL.
 */
- (void)saveBestRepresentationForRequest:(QLThumbnailGenerationRequest *)request
                             toFileAtURL:(NSURL*)fileURL
                         withContentType:(NSString*)contentType
                       completionHandler:(void (^)(NSError * _Nullable error))completionHandler NS_SWIFT_NAME(saveBestRepresentation(for:to:contentType:completion:));

@end

NS_ASSUME_NONNULL_END
