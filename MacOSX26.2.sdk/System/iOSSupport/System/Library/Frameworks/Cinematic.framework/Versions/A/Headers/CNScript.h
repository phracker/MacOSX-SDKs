//
//  CNScript.h
//  Cinematic
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cinematic/Cinematic.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class CNScriptChanges;
@class CNScriptFrame;

NS_REFINED_FOR_SWIFT NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
/// Database of focus decisions with methods to change them.
/// Knows what has been detected in each frame and which detection is being focused on.
/// All operations are executed in a thread-safe manner, but that also means that a long-running update can stall a lookup.
/// Best practice is to lookup what you need up front (outside your critical code) and pass the immutable results to where it's needed.
/// That way, you're not blocked when you access the information, say inside the rendering portion of your code.
///
@interface CNScript : NSObject

#pragma mark - load

/// Load cinematic script asynchronously from a cinematic asset.
/// - Parameters:
///   - asset: the cinematic asset to be loaded.
///   - changes: optional changes since asset was recorded. Can be obtained from a previous editing session. If `nil`, the asset is loaded as originally recorded.
///   - progress: optional progress object to track progress or cancel loading. Represents just the loading of this asset. Create with desired total unit count or use zero to have the unit count filled in automatically.  If `nil`, no progress is reported.
///   - completionHandler: called with the loaded cinematic script when done, or with with an error if it fails. If progress is canceled before it completes, the completion handler is called with an error.
///
+ (void)loadFromAsset:(AVAsset *)asset
              changes:(nullable CNScriptChanges *)changes
             progress:(nullable NSProgress *)progress
    completionHandler:(void (^)(CNScript * _Nullable script,
                                NSError * _Nullable error))completionHandler;

/// Reload the cinematic script with optional changes applied, removing any previous changes made.
/// This can be more efficient than loading the asset from scratch.
/// - Parameters:
///   - changes: optional changes since asset was recorded. Can be obtained from a previous editing session. If `nil`, the asset is reloaded as originally recorded.
- (void)reloadWithChanges:(nullable CNScriptChanges *)changes;

#pragma mark - changes

/// Changes made since cinematic asset was recorded. Can be used to checkpoint and later restore changes made so far.
- (CNScriptChanges *)changes;

/// Changes trimmed and time range shifted to start at zero — for use with a similarly trimmed cinematic asset.
- (CNScriptChanges *)changesTrimmedByTimeRange:(CMTimeRange)timeRange;

#pragma mark - frames

/// The time range of the cinematic asset. All frames, decisions, and detections are within this time range.
@property (readonly) CMTimeRange timeRange;

/// The closest frame to the given time within the given tolerance. Returns `nil` if there are none.
- (nullable CNScriptFrame *)frameAtTime:(CMTime)time tolerance:(CMTime)tolerance;

/// All frames within the given time range.
- (NSArray<CNScriptFrame *> *)framesInTimeRange:(CMTimeRange)timeRange;

#pragma mark - effective decisions

/// The closest decision to the given time within the given tolerance. Returns `nil` if there are none.
- (nullable CNDecision *)decisionAtTime:(CMTime)time tolerance:(CMTime)tolerance;

/// All decisions within the given time range.
- (NSArray<CNDecision *> *)decisionsInTimeRange:(CMTimeRange)timeRange;

/// The decision that occurs after the given time. Pass the time of an existing decision to find the next one.
- (nullable CNDecision *)decisionAfterTime:(CMTime)time;

/// The decision that occurs before the given time. Pass the time of an existing decisions to find the previous one.
- (nullable CNDecision *)decisionBeforeTime:(CMTime)time;

#pragma mark - transitions

/// The primary decision that is in effect at the specified time, unless if it's outside the time range of the cinematic script.
/// Also represents the decision that is being transitioned away from if the given time is during a focus transition.
- (nullable CNDecision *)primaryDecisionAtTime:(CMTime)time;

/// The secondary decision that is being transitioned towards if the given time is during a focus transition.
- (nullable CNDecision *)secondaryDecisionAtTime:(CMTime)time;

/// The time range during which the focus transition away from the given decision occurs.
- (CMTimeRange)timeRangeOfTransitionAfterDecision:(CNDecision *)decision;

/// The time range during which the focus transition towards the given decision occurs.
- (CMTimeRange)timeRangeOfTransitionBeforeDecision:(CNDecision *)decision;

#pragma mark - decision layers

/// All user decisions in the given time range. Includes user decisions made during recording or added to the script.
- (NSArray<CNDecision *> *)userDecisionsInTimeRange:(CMTimeRange)timeRange;

/// All base decisions made automatically during recording in the given time range. These apply if no user decision overrides them.
- (NSArray<CNDecision *> *)baseDecisionsInTimeRange:(CMTimeRange)timeRange;

#pragma mark - detection tracks

/// A detection track representing all detections with the given detectionID over the entire cinematic script.
- (nullable CNDetectionTrack *)detectionTrackForID:(CNDetectionID)detectionID;

/// A detection track representing all detections that would be chosen by a given decision.
- (nullable CNDetectionTrack *)detectionTrackForDecision:(CNDecision *)decision;

#pragma mark - fNumber

/// The f/number to apply to the entire movie, initially set to that of the recorded movie.
///
/// Pass this to the rendering session in the rendering frame attributes to match the selected aperture.
/// Change this property when the user selects a different aperture for the edited movie.
/// Changes to this property are reflected in the script changes for later restoration.
///
@property float fNumber;

#pragma mark - add/remove decisions

/// Add a new user decision. Replaces an existing user decision if the times are identical.
///
/// Adding a decision can fail if the decision focuses on an detection or group that does not exist or if its time is not within the time range of the cinematic script.
///
/// - Returns: whether adding was successful
///
- (BOOL)addUserDecision:(CNDecision *)decision;

/// Remove an existing user decision.
///
/// User decisions added to the script or those made at recording time (by tapping during recording) can be removed.
/// Decisions that are not user decisions cannot be removed.
///
/// - Returns: whether removal was successful
///
- (BOOL)removeUserDecision:(CNDecision *)decision;

/// Remove all user decisions and revert to base decisions only.
///
- (void)removeAllUserDecisions;

#pragma mark - add/remove detection tracks

/// Add user created detection track.
///
/// - Returns: the detectionID assigned to the added track, which can be used for later lookup or decision creation.
///
- (CNDetectionID)addDetectionTrack:(CNDetectionTrack *)detectionTrack;

/// Remove user created detection track.
///
/// Tracks created at recording time cannot be removed.
///
/// - Returns: whether removal was successful
///
- (BOOL)removeDetectionTrack:(CNDetectionTrack *)detectionTrack;

/// All detection tracks that have been added since recording.
///
@property (readonly, strong) NSArray<CNDetectionTrack *> *addedDetectionTracks;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
/// Represents a snapshot of changes made to the cinematic script since recording.
/// Can be used as a snapshot to quickly revert to previously saved edits via `-[CNScript reloadWithChanges:]`
///
@interface CNScriptChanges : NSObject

/// Create from previously saved data representation
- (nullable instancetype)initWithDataRepresentation:(NSData *)dataRepresentation;

/// Get persistent data representation of these changes for later restoration.
///
/// The changes can only be used with the original cinematic asset from which the CNScript was created.
///
@property (readonly) NSData *dataRepresentation;

/// The f/number to apply to the entire movie.
@property (readonly) float fNumber;

/// All active user decisions, including those made at recording time, unless they have been removed.
@property (readonly) NSArray<CNDecision *> *userDecisions;

/// All detection tracks that have been added. Does not include those created at recording time.
@property (readonly) NSArray<CNDetectionTrack *> *addedDetectionTracks;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_REFINED_FOR_SWIFT NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
/// Represents focus & detection information at a particular time.
///
/// Indicates where to focus (disparity) and what to focus on (detection) at a particular time in the movie.
/// It also provides access to all known detections that can be focused on at that time.
/// Utility methods support looking up a detection by detectionID or detectionGroupID.
///
/// Frames are obtained from the cinematic script using `frame(at:tolerance:)` or `frames(in:)`.
///
@interface CNScriptFrame : NSObject <NSCopying>

/// The presentation time associated with the remaining properties.
@property (readonly) CMTime time;

/// The disparity value representing the focus plane at which the script is focused in this frame.
///
/// A larger disparity results in the focus plane being closer to the camera. The scale and offset of disparity is not defined.
///
/// Pass this to the rendering session when rendering the corresponding frame of the movie to focus at the recommended depth.
///
@property (readonly) float focusDisparity;

/// The detection on which the script is focused in this frame.
///
/// The focusDisparity of the focusDetection can be different from that of the frame such as when a rack focus is in progress.
///
@property (readonly, strong) CNDetection *focusDetection;

/// All detected objects in this frame.
@property (readonly, strong) NSArray<CNDetection *> *allDetections;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface CNScriptFrame (CNExtensions)

/// The detection in this frame with the given detection ID, if any.
- (nullable CNDetection *)detectionForID:(CNDetectionID)detectionID;

/// The best detection to focus on in this frame among those with the given detectionGroupID.
/// For example, a face is preferred to the corresponding torso, even though both have the same detectionGroupID.
- (nullable CNDetection *)bestDetectionForGroupID:(CNDetectionGroupID)detectionGroupID;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
