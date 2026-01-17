//------------------------------------------------------------------------------------------------------------------------------
//
//  ICCameraFile.h
//  ImageCaptureCore
//
//  Copyright (c) 2008-2019 Apple Inc., all rights reserved.
//
//  Best viewed with the following settings: Tab width 4, Indent width 2, Wrap lines, Indent wrapped lines by 3, Page guide 128.
//
//------------------------------------------------------------------------------------------------------------------------------

#pragma once

#import <ImageCaptureCore/ICCameraItem.h>

CF_ASSUME_NONNULL_BEGIN

//----------------------------------------------------------------------------------------------------------------- ICCameraFile
/*!
 @class ICCameraFile
 @abstract This class represents a file on an ICCameraDevice object.
 */
IC_AVAILABLE(macos(10.4), ios(13.0))
@interface ICCameraFile : ICCameraItem {
}

/*!
 @property width
 @abstract Width of an image or movie frame.
 */
@property (nonatomic, readonly) NSInteger width IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property height
 @abstract Height of an image or movie frame.
 */
@property (nonatomic, readonly) NSInteger height IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property originalFilename
 @abstract Original filename on disk
 */
@property (nonatomic, readonly, nullable) NSString* originalFilename IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property createdFilename
 @abstract Created filename
 */
@property (nonatomic, readonly, nullable) NSString* createdFilename IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property fileSize
 @abstract ￼Size of file in bytes.
 */
@property (nonatomic, readonly) off_t fileSize IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property orientation
 @abstract ￼Desired orientation of image to use when it is downloaded.
 @discussion This property is set to ICEXIFOrientation1 initially. If the format of this file supports EXIF orientation tag, then this property will be updated to match the value of that tag, when the thumbnail or metadata for this file is received.
 */
@property (nonatomic, readwrite) ICEXIFOrientationType orientation IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property duration
 @abstract ￼Duration of audio/video file in seconds.
 */
@property (nonatomic, readonly) double duration IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property highFramerate
 @abstract True if file is a slo-mo or high framerate video file, nil otherwise.
 */
@property (nonatomic, readonly) BOOL highFramerate IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property timeLapse
 @abstract True if file is a time-lapse video file, nil otherwise.
 */
@property (nonatomic, readonly) BOOL timeLapse IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property firstPicked
 @abstract True if file is a firstPicked nil otherwise.
 */
@property (nonatomic, readonly) BOOL firstPicked IC_AVAILABLE(macos(10.13), ios(13.0));

/*!
 @property originatingAssetID
 @abstract originatingAssetID of file if present, nil if not a HEIF or HVEC.
 */
@property (nonatomic, readonly, nullable) NSString* originatingAssetID IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property groupUUID
 @abstract groupUUID of file if present, nil if file has no groupUUID.
 */
@property (nonatomic, readonly, nullable) NSString* groupUUID IC_AVAILABLE(macos(10.13), ios(13.0));

/*!
 @property gpsString
 @abstract GPS String in standard format.
 */
@property (nonatomic, readonly, nullable) NSString* gpsString IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property relatedUUID
 @abstract Internal related UUID for dbg/aae/etc.
 */
@property (nonatomic, readonly, nullable) NSString* relatedUUID IC_AVAILABLE(macos(10.11), ios(13.0));

/*!
 @property burstUUID
 @abstract burstUUID of file if present, nil if not in a burst.
 */
@property (nonatomic, readonly, nullable) NSString* burstUUID IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property burstFavorite
 @abstract True if burst favorite, ignored if not in a burst or not a burst favorite.
 */
@property (nonatomic, readonly) BOOL burstFavorite IC_AVAILABLE(macos(10.10), ios(13.0));

/*!
 @property burstPicked
 @abstract True if burst user picked, ignored if not in a burst or not a burst user picked.
 */
@property (nonatomic, readonly) BOOL burstPicked IC_AVAILABLE(macos(10.10), ios(13.0));

/*!
 @property sidecarFiles
 @abstract This property is NULL if there are no sidecar files associated with this file. Otherwise it is an array of
 ICCameraFile instances of sidecar files associated with this file. An example of a sidecar file is a file with the same base
 name as this file and having an extension XMP.
 */
@property (nonatomic, readonly, nullable) NSArray<ICCameraItem*>* sidecarFiles IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property pairedRawImage
 @abstract A single item subset of the sidecarFiles array, which contains the logical RAW compliment of a JPG or other
 format image.
 */
@property (nonatomic, readonly, nullable) ICCameraFile* pairedRawImage IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property fileCreationDate
 @abstract Properties will either represent the actual file creation
 date, or nil.
 */
@property (nonatomic, readonly, nullable) NSDate* fileCreationDate IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property fileModificationDate
 @abstract Properties will either represent the actual file modification
 date, or nil.
 */
@property (nonatomic, readonly, nullable) NSDate* fileModificationDate IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property exifCreationDate
 @abstract Properties will either represent the exif creation
 date, or nil.
 */
@property (nonatomic, readonly, nullable) NSDate* exifCreationDate IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property exifModificationDate
 @abstract Properties will either represent the exif modification
 date, or nil.
 */
@property (nonatomic, readonly, nullable) NSDate* exifModificationDate IC_AVAILABLE(macos(10.4), ios(13.0));

/*!
 @property fingerprint
 @abstract A fingerprint generated from the camera file data
 date, or nil.
 */
@property (nonatomic, readonly, nullable) NSString* fingerprint;

/*!
 @property fingerprintForFileAtURL
 @abstract Generates a fingerprint given a URL
 date, or nil.
 */
+ (NSString* _Nullable)fingerprintForFileAtURL:(NSURL*)url;

#pragma mark - Block API

/*!
   @method requestThumbnailDataWithOptions:completion
   @abstract ￼Perform a thumbnail request and execute the block callback in place of the delegate.
   @param options Options dictionary

   - 'kCGImageSourceThumbnailMaxPixelSize' - Request a width different from the embedded EXIF thumbnail

   @param completion Completion block called with an NSData* object representing the JPG, and an NSError* for status.
   @note The completion block will execute on an any available queue, often this will not be the main queue.
 */
- (void)requestThumbnailDataWithOptions:(NSDictionary<ICCameraItemThumbnailOption, id>* _Nullable)options
                             completion:(void (^)(NSData* _Nullable, NSError* _Nullable))completion IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
   @method requestMetadataDictionaryWithOptions:completion
   @abstract ￼Perform a metadata request and execute the block callback in place of the delegate.
   @param options Options dictionary
   @param completion Completion block called with an NSDictionary* object containing the metadata, and an NSError* for status.
   @note The completion block will execute on an any available queue, often this will not be the main queue.
 */
- (void)requestMetadataDictionaryWithOptions:(NSDictionary<ICCameraItemMetadataOption, id>* _Nullable)options
                                  completion:(void (^)(NSDictionary* _Nullable, NSError* _Nullable))completion IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
   @method requestDownloadWithOptions:progressDelegate:completion
   @abstract ￼Perform a download request and execute the block callback in place of the delegate.
   @param options Dictionary Keys:

   - `ICDownloadsDirectoryURL`
   - `ICSaveAsFilename`
   - `ICOverwriteExistingFile`
   - `ICDeleteAfterDownload`
   - `ICAdjustCreationDate`

   @param completion Completion block to executed after request has returned,
   @note The completion block will execute on an any available queue, often this will not be the main queue.
 */
- (NSProgress* _Nullable)requestDownloadWithOptions:(NSDictionary<ICDownloadOption, id>* _Nullable)options
                                         completion:(void (^)(NSString* _Nullable filename, NSError* _Nullable error))completion
    IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
   @method requestReadDataAtOffset:length:completion
   @abstract This method asynchronously reads data of a specified length from a specified offset.
   @param offset The offset into the file to start reading from
   @param length The length of data to be read.
   @param completion Completion block called with an NSData* object representing the data, and an NSError* for status.
   @note The completion block will execute on an any available queue, often this will not be the main queue.
 */
- (void)requestReadDataAtOffset:(off_t)offset length:(off_t)length
                     completion:(void (^)(NSData* _Nullable, NSError* _Nullable)) completion IC_AVAILABLE(macos(10.15), ios(13.0));

/*!
   @method requestSecurityScopedURLWithCompletion
   @abstract ￼Requests a security scoped NSURL* for a media file on a mass storage volume. The returned NSURL* requires the use of
 startAccessingSecurityScopedResource, and stopAccessingSecurityScopedResource for access.
   @param completion Completion block called with an NSURL*, and an NSError* for status.
   @note The completion block will execute on an any available queue, often this will not be the main queue.
 */
- (void)requestSecurityScopedURLWithCompletion:(void (^)(NSURL* _Nullable, NSError* _Nullable))completion IC_AVAILABLE(macos(14.0), ios(17.0));

/*!
   @method requestFingerprintWithCompletion
   @abstract ￼Requests a fingerprint be generated for camera file.
   @param completion Completion block called with an NSString*, and an NSError* for status.
   @note The completion block will execute on an any available queue, often this will not be the main queue.
 */
- (void)requestFingerprintWithCompletion:(void (^)(NSString* _Nullable, NSError* _Nullable))completion IC_AVAILABLE(macos(15.0), ios(18.0));

@end

CF_ASSUME_NONNULL_END
