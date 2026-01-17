//
//  Copyright © 2016 Apple, Inc. All rights reserved.
//

#import <Photos/PHLivePhoto.h>
#import <CoreImage/CIImage.h>
#import <CoreMedia/CMTime.h>

NS_ASSUME_NONNULL_BEGIN

@protocol PHLivePhotoFrame;
@class PHContentEditingInput;
@class PHContentEditingOutput;

/// A block callback for processing frames of a live photo, including the still image
typedef CIImage * _Nullable (^PHLivePhotoFrameProcessingBlock)(id <PHLivePhotoFrame> _Nonnull frame, NSError * _Nullable * _Nonnull error);

typedef NSString * const PHLivePhotoEditingOption NS_STRING_ENUM;

NS_CLASS_AVAILABLE(10_12, 10_0) @interface PHLivePhotoEditingContext : NSObject

/// Initializer from the specified live photo input
/// Return nil if the specified input is not for a live photo
- (nullable instancetype)initWithLivePhotoEditingInput:(PHContentEditingInput *)livePhotoInput NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

// ------------------------------------------------------------------------
// Read-only properties
// ------------------------------------------------------------------------

/// The original full-size image from the input live photo
@property (readonly) CIImage *fullSizeImage;

/// The duration of the live photo
@property (readonly) CMTime duration;

/// The time of the still image within the live photo
@property (readonly) CMTime photoTime;

// The orientation of the live photo
@property (readonly) CGImagePropertyOrientation orientation;

// ------------------------------------------------------------------------
// Editable properties
// ------------------------------------------------------------------------

/// A block that can be set to process each frame of the live photo
/// Note that the context uses a copy of the processor block during processing
@property (nullable, copy) PHLivePhotoFrameProcessingBlock frameProcessor;

/// Specify the volume gain of the live photo
/// Must be between 0.0 and 1.0
/// Default to 1.0
@property float audioVolume;

// ------------------------------------------------------------------------
// Processing
// ------------------------------------------------------------------------

/// Asynchronously generate a new live photo suitable for playback in a PHLivePhotoView of the specified target size
/// The options dictionary can contain additional options, see below
- (void)prepareLivePhotoForPlaybackWithTargetSize:(CGSize)targetSize options:(nullable NSDictionary<PHLivePhotoEditingOption, id> *)options completionHandler:(void(^)(PHLivePhoto * _Nullable livePhoto, NSError * _Nullable error))handler;

/// Asynchronously process and save the edited live photo to the specified content editing output
/// Options dictionary should be nil, reserved for future expansion
- (void)saveLivePhotoToOutput:(PHContentEditingOutput *)output options:(nullable NSDictionary<PHLivePhotoEditingOption, id> *)options completionHandler:(void(^)(BOOL success, NSError * _Nullable error))handler;

/// Cancel the current asynchronous operation
/// This is implicitly called whenever prepare or save is called
/// A canceled operation will call its completion handler with an appropriate error code of PHLivePhotoEditingErrorCodeAborted
- (void)cancel;

@end

/// Type of frames in a Live Photo
typedef NS_ENUM(NSInteger, PHLivePhotoFrameType)
{
    /// Indicate the still image
    PHLivePhotoFrameTypePhoto,
    
    /// Indicate a video frame
    PHLivePhotoFrameTypeVideo,
} NS_ENUM_AVAILABLE(10_12, 10_0);

/// Protocol that describes a single frame of a live photo
NS_CLASS_AVAILABLE(10_12, 10_0) @protocol PHLivePhotoFrame <NSObject>

/// Input image for the frame
@property (readonly) CIImage *image;

/// The time of the frame relative to the beginning of the live photo
@property (readonly) CMTime time;

/// The type of frame (photo or video)
@property (nonatomic, readonly) PHLivePhotoFrameType type;

/// The scale of the frame relative to the full-size image
@property (readonly) CGFloat renderScale;

@end

// ------------------------------------------------------------------------
// Options that can be set during processing
// ------------------------------------------------------------------------

/// Indicates whether processing should happen at playback time
/// If set to NO (the default) the live photo will always be rendered before playback
/// If set to YES, the editing context might still choose to render first for performance reasons
/// This option is ignored by the saveLivePhotoToOutput method
extern PHLivePhotoEditingOption PHLivePhotoShouldRenderAtPlaybackTime NS_AVAILABLE(10_12, 10_0);

// ------------------------------------------------------------------------
// Errors
// ------------------------------------------------------------------------

/// The error domain for all Live Photo Editing errors
extern NSString * const PHLivePhotoEditingErrorDomain NS_AVAILABLE(10_12, 10_0);

/// Error code for Live Photo Editing errors
typedef NS_ENUM(NSInteger, PHLivePhotoEditingErrorCode)
{
    PHLivePhotoEditingErrorCodeUnknown,
    PHLivePhotoEditingErrorCodeAborted,
} NS_AVAILABLE(10_12, 10_0);

NS_ASSUME_NONNULL_END
