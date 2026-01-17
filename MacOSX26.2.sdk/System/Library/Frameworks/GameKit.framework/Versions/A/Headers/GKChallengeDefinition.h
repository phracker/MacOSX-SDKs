// Copyright © Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <TargetConditionals.h>

#import <GameKit/GKLeaderboard.h>
#import <GameKit/GKReleaseState.h>

#if TARGET_OS_IPHONE
@class UIImage;
#else
@class NSImage;
#endif

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), visionos(26.0), watchos(26.0))
NS_SWIFT_SENDABLE @interface GKChallengeDefinition: NSObject

/// The developer defined identifier for a given challenge definition.
@property (nonatomic, readonly, copy) NSString *identifier;

/// The group identifier for the challenge definition, if one exists.
@property (nonatomic, readonly, copy, nullable) NSString *groupIdentifier;

/// A short title for the challenge definition.
@property (nonatomic, readonly, copy) NSString *title;

/// A more detailed description of the challenge definition.
@property (nonatomic, readonly, copy, nullable) NSString *details;

/// The duration options for the challenge, like `1 day` or `1 week`.
///  - Note: If set, the amount of weeks is stored in the `weekOfYear` field.
/// - Important: The actual duration of the challenge may be dynamically adjusted
///              in order to accommodate different factors like players' timezones.
@property (nonatomic, readonly, copy) NSArray<NSDateComponents *> *durationOptions;

/// Indicates if a challenge can be attempted more than once.
@property (nonatomic, readonly) BOOL isRepeatable;

/// Scores submitted to this leaderboard will also be submitted as scores in this challenge.
@property (nonatomic, readonly, strong, nullable) GKLeaderboard *leaderboard;

/// The release state of the challenge definition in App Store Connect.
@property (nonatomic, readonly) GKReleaseState releaseState;

#if TARGET_OS_IPHONE
/// Loads the image set on the challenge definition, which may be `nil` if none was set.
- (void)loadImageWithCompletionHandler:(void(^)(UIImage * _Nullable_result image, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(getter:image()) API_UNAVAILABLE(watchos);
#else
/// Loads the image set on the challenge definition, which may be `nil` if none was set.
- (void)loadImageWithCompletionHandler:(void(^)(NSImage * _Nullable_result image, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(getter:image());
#endif

@end

API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), visionos(26.0), watchos(26.0))
NS_SWIFT_SENDABLE @interface GKChallengeDefinition (State)

/// Loads all the challenge definitions for the current game, returns an empty array if none exist.
/// - Important: Archived challenge definitions are excluded.
+ (void)loadChallengeDefinitionsWithCompletionHandler:(void(^)(NSArray<GKChallengeDefinition *> * _Nullable challengeDefinitions,
                                                               NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(getter:all());

/// Indicates if this definition has active challenges associated with it.
- (void)hasActiveChallengesWithCompletionHandler:(void(^)(BOOL hasActiveChallenges,
                                                          NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(getter:hasActiveChallenges());

@end

NS_HEADER_AUDIT_END(nullability, sendability)
