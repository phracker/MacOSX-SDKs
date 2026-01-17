//
//  CNAssetInfo.h
//  Cinematic
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
/// Information associated with an AVAsset for a cinematic video.
@interface CNAssetInfo : NSObject

/// Check if asset is cinematic asynchronously.
+ (void)checkIfCinematic:(AVAsset *)asset completionHandler:(void (^)(BOOL result))completionHandler;

/// Load cinematic asset information asynchronously.
+ (void)loadFromAsset:(AVAsset *)asset
        completionHandler:(void (^)(CNAssetInfo * _Nullable cinematicAssetInfo,
                                    NSError * _Nullable error))completionHandler;

@property (strong, readonly) AVAsset *asset;

@property (strong, readonly) NSArray<AVAssetTrack *> *allCinematicTracks;

@property (strong, readonly) AVAssetTrack *cinematicVideoTrack;
@property (strong, readonly) AVAssetTrack *cinematicDisparityTrack;
@property (strong, readonly) AVAssetTrack *cinematicMetadataTrack;

/// Time range over which all cinematic tracks are valid.
@property (readonly) CMTimeRange timeRange;

/// Natural size at which cinematic video would be rendered
@property (readonly) CGSize naturalSize;

/// Natural size at which cinematic video would be displayed.
/// Same as naturalSize with preferredTransform applied.
@property (readonly) CGSize preferredSize;

/// The preferred transform of the rendered image for display purposes.
/// Always the identity transform or a multiple of a 90º rotation with no scaling.
@property (readonly) CGAffineTransform preferredTransform;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// Use of these properties where appropriate is preferred to help maintain future compatibility
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface CNAssetInfo (AbstractTracks)

/// Track to be used for frame timing
@property (strong, readonly) AVAssetTrack *frameTimingTrack;

/// Tracks required to construct AVAssetReaderVideoCompositionOutput.
@property (strong, readonly) NSArray<AVAssetTrack *> *videoCompositionTracks;

/// Source video track IDs required to implement AVVideoCompositionInstruction protocol
@property (strong, readonly) NSArray<NSNumber *> *videoCompositionTrackIDs;

/// Source metadata track IDs required to implement AVVideoCompositionInstruction protocol
@property (strong, readonly) NSArray<NSNumber *> *sampleDataTrackIDs;

@end

NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
/// Information about composition tracks added to an AVComposition for a cinematic asset.
@interface CNCompositionInfo : CNAssetInfo

/// Inserts a timeRange of a cinematic source asset into the corresponding tracks of a composition
/// - Parameters:
///  - timeRange: time range of the cinematic asset to be inserted
///  - assetInfo: identifies the tracks of the cinematic asset to be inserted
///  - atTime: the time at which the inserted tracks are to be presented by the composition; `kCMTimeInvalid` may be used to append at the end.
///  - error: AVError if it fails, as with `-[AVMutableCompositionTrack insertTimeRange:ofTrack:atTime:error:]`
/// - Returns: whether the insertion was successful
- (BOOL)insertTimeRange:(CMTimeRange)timeRange ofCinematicAssetInfo:(CNAssetInfo *)assetInfo atTime:(CMTime)startTime error:(NSError * _Nullable * _Nullable)outError;

@end


API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface AVMutableComposition (CNComposition)

/// Adds a group of empty tracks associated with a cinematic asset to a mutable composition.
/// - Returns: Information about the composition tracks added to the mutable composition.
/// Be sure to call insertTimeRange on the result to specify at least one time range of cinematic asset you'd like in the composition.
- (CNCompositionInfo *)addTracksForCinematicAssetInfo:(CNAssetInfo *)assetInfo preferredStartingTrackID:(CMPersistentTrackID)preferredStartingTrackID NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
