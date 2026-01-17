// Copyright © Apple Inc. All rights reserved.

#import <TargetConditionals.h>

#if !TARGET_OS_WATCH

#import <Foundation/Foundation.h>
#import <GameKit/GKGameActivityPlayStyle.h>
#import <GameKit/GKReleaseState.h>
#import <TargetConditionals.h>

#if TARGET_OS_IPHONE
@class UIImage;
#else
@class NSImage;
#endif

@class GKAchievementDescription;
@class GKLeaderboard;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_SENDABLE @interface GKGameActivityDefinition : NSObject

/// The developer defined identifier for a given game activity.
@property (nonatomic, readonly, copy) NSString *identifier;

/// The group identifier for the activity, if one exists.
@property (nonatomic, readonly, copy, nullable) NSString *groupIdentifier;

/// A short title for the game activity.
@property (nonatomic, readonly, copy) NSString *title;

/// A more detailed description of the game activity.
@property (nonatomic, readonly, copy, nullable) NSString *details;

/// Default properties defined by the developer for this type of game activity.
@property (nonatomic, readonly, copy) NSDictionary<NSString *, NSString *> *defaultProperties;

/// A fallback URL that can be used to construct a game-specific URL for players to share or join, if the joining device does not support the default URL.
@property (nonatomic, readonly, strong, nullable) NSURL *fallbackURL;

/// Whether the activity can be joined by others via a party code.
/// - SeeAlso: ``-[GKGameActivityListener player:wantsToPlayGameActivity:completionHandler:]`` where you can receive and handle game activities that players want to play in a party with friends.
@property (nonatomic, readonly, assign) BOOL supportsPartyCode;

/// The maximum number of participants that can join the activity. Returns nil when no maximum is set (unlimited players) or when player range is undefined. When not nil, the value is always greater than or equal to `minPlayers`.
@property (nonatomic, readonly, strong, nullable) NSNumber *maxPlayers NS_REFINED_FOR_SWIFT;

/// The minimum number of participants that can join the activity.
@property (nonatomic, readonly, strong, nullable) NSNumber *minPlayers NS_REFINED_FOR_SWIFT;

/// True if the activity supports an unlimited number of players. False if maxPlayers is set to a defined limit or if no player range is provided.
@property (nonatomic, readonly, assign) BOOL supportsUnlimitedPlayers;

/// The play style of the game activity.
@property (nonatomic, readonly, assign) GKGameActivityPlayStyle playStyle;

/// The release state of the game activity definition in App Store Connect.
@property (nonatomic, readonly) GKReleaseState releaseState;

- (instancetype)init NS_UNAVAILABLE;

/// Loads all associated achievements that have defined deep links to this game activity definition.
- (void)loadAchievementDescriptionsWithCompletionHandler:(void(^)(NSArray<GKAchievementDescription *> * _Nullable achievementDescriptions,
                                                                  NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(getter:achievementDescriptions());

/// Loads all associated leaderboards that have defined deep links to this game activity definition.
- (void)loadLeaderboardsWithCompletionHandler:(void(^)(NSArray<GKLeaderboard *> * _Nullable leaderboards,
                                                       NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(getter:leaderboards());

#if TARGET_OS_IPHONE
/// Asynchronously load the image. Error will be nil on success.
- (void)loadImageWithCompletionHandler:(void(^)(UIImage * _Nullable_result image, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(getter:image());
#else
/// Asynchronously load the image. Error will be nil on success.
- (void)loadImageWithCompletionHandler:(void(^)(NSImage * _Nullable_result image, NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(getter:image());
#endif

@end

API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
NS_SWIFT_SENDABLE @interface GKGameActivityDefinition (State)

/// Loads all the game activity definitions for the current game.
+ (void)loadGameActivityDefinitionsWithCompletionHandler:(void(^)(NSArray<GKGameActivityDefinition *> * _Nullable activityDefinitions,
                                                                  NSError * _Nullable error))completionHandler NS_SWIFT_ASYNC_NAME(getter:all());

/// Loads game activity definitions with the supplied App Store Connect identifiers.
+ (void)loadGameActivityDefinitionsWithIDs:(NSArray<NSString *> * _Nullable)activityDefinitionIDs
                         completionHandler:(void(^)(NSArray<GKGameActivityDefinition *> * _Nullable activityDefinitions,
                                                    NSError * _Nullable error))completionHandler NS_SWIFT_NAME(loadGameActivityDefinitions(IDs:completionHandler:));
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#endif // #if !TARGET_OS_WATCH
