// Copyright © Apple Inc. All rights reserved.

#import <GameKit/GKPlayer.h>
#import <GameKit/GKReleaseState.h>
#import <TargetConditionals.h>

#if !TARGET_OS_TV
#import <Contacts/Contacts.h>
#endif

typedef NS_ENUM(NSInteger, GKLeaderboardTimeScope) {
    GKLeaderboardTimeScopeToday = 0,
    GKLeaderboardTimeScopeWeek,
    GKLeaderboardTimeScopeAllTime
} API_AVAILABLE(ios(4.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0));

typedef NS_ENUM(NSInteger, GKLeaderboardPlayerScope) {
    GKLeaderboardPlayerScopeGlobal = 0,
    GKLeaderboardPlayerScopeFriendsOnly
} API_AVAILABLE(ios(4.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0));

typedef NS_ENUM(NSInteger, GKLeaderboardType)
{
    GKLeaderboardTypeClassic,
    GKLeaderboardTypeRecurring,
} API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), visionos(1.0), watchos(7.0));

@class GKScore;
@class UIImage;
@class GKLeaderboardEntry;

NS_ASSUME_NONNULL_BEGIN

/// GKLeaderboard represents a single instance of a leaderboard for the current game.
/// Leaderboards can be of the following types:
///      1. Classic - Traditional, non-expiring leaderboards
///      2. Recurring - Periodic timed leaderboards that follow a recurrence rule defined in App Store Connect.

API_AVAILABLE(ios(4.1), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0))
@interface GKLeaderboard : NSObject

/// Localized title
@property(readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *title;

/// set when leaderboards have been designated a game group; set when loadLeaderboardsWithCompletionHandler has been called for leaderboards that support game groups
@property(nonatomic, readonly, nullable, strong) NSString *groupIdentifier API_AVAILABLE(ios(6.0), macos(10.9), tvos(9.0), visionos(1.0), watchos(3.0));

/// Leaderboard ID defined in App Store Connect that this instance is associated with
@property (strong, readonly, nonatomic) NSString *baseLeaderboardID API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));

/// Type of leaderboard
@property (readonly, nonatomic) GKLeaderboardType type API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));

/// Date and time this instance started accepting score submissions (only applicable to recurring leaderboards)
@property (strong, readonly, nonatomic, nullable) NSDate *startDate API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));

/// Date and time the next instance will start accepting score submissions (only applicable to recurring leaderboards)
@property (strong, readonly, nonatomic, nullable) NSDate *nextStartDate API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));

/// Duration from startDate during which this leaderboard instance accepts score submissions (only applicable to recurring leaderboards)
@property (readonly, nonatomic) NSTimeInterval duration API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));

/// The description of this Leaderboard as configured by the developer in App Store Connect.
@property (readonly, nonatomic, copy) NSString *leaderboardDescription API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), visionos(26.0), watchos(26.0));

/// The release state of the leaderboard in App Store Connect.
@property(nonatomic, assign, readonly) GKReleaseState releaseState API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), visionos(26.0), watchos(26.0));

/// The identifier of the game activity associated with this leaderboard, as configured by the developer in App Store Connect.
@property (readonly, nonatomic, copy) NSString *activityIdentifier API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), visionos(26.0), watchos(26.0));

/// The properties when associating this leaderboard with a game activity, as configured by the developer in App Store Connect.
@property (readonly, nonatomic, strong) NSDictionary<NSString *, NSString *> *activityProperties API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), visionos(26.0), watchos(26.0));

/// A Boolean value that indicates whether the current leaderboard isn't visible in Game Center views.
///
/// You can still submit scores to a hidden leaderboard.
@property (readonly, nonatomic) BOOL isHidden API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), visionos(26.0), watchos(26.0));

/// Loads classic and recurring leaderboards associated with the supplied App Store Connect leaderboard IDs.
/// If leaderboardIDs is nil, this loads all classic and recurring leaderboards for this game.
+ (void)loadLeaderboardsWithIDs:(NSArray<NSString *> * _Nullable)leaderboardIDs
              completionHandler:(void(^)(NSArray<GKLeaderboard *> * _Nullable leaderboards, NSError * _Nullable error))completionHandler NS_SWIFT_NAME(loadLeaderboards(IDs:completionHandler:)) API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));

/// Loads the occurrence preceding this occurrence for a recurring leaderboard in which the local player submitted a score. If no previous occurrence is found that the player submitted a score to, then the most recent previous occurrence is returned.
- (void)loadPreviousOccurrenceWithCompletionHandler:(void(^)(GKLeaderboard * _Nullable_result leaderboard, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));

/// Class method to submit a single score to multiple leaderboards
///   score - earned by the player
///   context - developer supplied metadata associated with the player's score
///   player - the player for whom this score is being submitted
///   leaderboardIDs - one or more leaderboard IDs defined in App Store Connect
+ (void)submitScore:(NSInteger)score
            context:(NSUInteger)context
             player:(GKPlayer *)player
     leaderboardIDs:(NSArray<NSString *> *)leaderboardIDs
  completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));

/// Instance method to submit a single score to the leaderboard associated with this instance
///   score - earned by the player
///   context - developer supplied metadata associated with the player's score
///   player - the player for whom this score is being submitted
- (void)submitScore:(NSInteger)score
            context:(NSUInteger)context
             player:(GKPlayer *)player
  completionHandler:(void(^)(NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));


/// Loads leaderboard entries based on the supplied parameters.
///   playerScope - Friends or Global
///   timeScope - Today, Week, All Time (Only applicable to classic leaderboards)
///   range - Range of ranked entries to return (minimum start index 1, maximum length 100)
/// Upon completion, will return:
///   localPlayerEntry - entry for the local player
///   entries - requested entries matching supplied parameters
///   totalPlayerCount - total player count matching specified scope
- (void)loadEntriesForPlayerScope:(GKLeaderboardPlayerScope)playerScope
                        timeScope:(GKLeaderboardTimeScope)timeScope
                            range:(NSRange)range
                completionHandler:(void(^)(GKLeaderboardEntry * _Nullable_result localPlayerEntry, NSArray<GKLeaderboardEntry *> * _Nullable entries, NSInteger totalPlayerCount, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));

/// Loads leaderboard entries for specific players based on the supplied parameters.
///   players - Array of players to load entries for
///   timeScope - Today, Week, All Time (Only applicable to classic leaderboards)
/// Upon completion, will return:
///   localPlayerEntry - entry for the local player
///   entries - requested entries matching supplied parameters
- (void)loadEntriesForPlayers:(NSArray<GKPlayer *> *)players
                    timeScope:(GKLeaderboardTimeScope)timeScope
            completionHandler:(void(^)(GKLeaderboardEntry * _Nullable_result localPlayerEntry, NSArray<GKLeaderboardEntry *> * _Nullable entries, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0), macos(11.0), tvos(14.0), watchos(7.0));

@end

@interface GKLeaderboard (Deprecated)

@property(copy, nullable, NS_NONATOMIC_IOSONLY) NSString *category API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKLeaderboard/loadEntries(for:timeScope:range:completionHandler:)`` method instead.", ios(4.1,7.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos);

- (nullable instancetype)initWithPlayerIDs:(nullable NSArray<NSString *> *)playerIDs API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKLeaderboard/loadEntries(for:timeScope:completionHandler:)`` method instead.", ios(4.1,8.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos);

+ (void)loadCategoriesWithCompletionHandler:(void(^__nullable)(NSArray<NSString *> * __nullable categories, NSArray<NSString *> * __nullable titles, NSError * __nullable error))completionHandler API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKLeaderboard/loadLeaderboards(completionHandler:)`` method instead.", ios(4.1,6.0), macos(10.8,10.9)) API_UNAVAILABLE(tvos);

+ (void)setDefaultLeaderboard:(nullable NSString *)leaderboardIdentifier withCompletionHandler:(void(^__nullable)(NSError * __nullable error))completionHandler API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKLocalPlayer/setDefaultLeaderboardIdentifier(_:completionHandler:)`` method instead.", ios(5.0,7.0), macos(10.8,10.10)) API_UNAVAILABLE(tvos);

@property(assign, NS_NONATOMIC_IOSONLY) GKLeaderboardTimeScope timeScope API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboard/loadEntries(for:timeScope:range:completionHandler:)`` instead.", ios(4.0, 14.0), tvos(9.0, 14.0), macos(10.8, 11.0), watchos(3.0, 7.0));

/// Filter on friends. Does not apply to leaderboard initialized with players.
@property(assign, NS_NONATOMIC_IOSONLY) GKLeaderboardPlayerScope playerScope API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboard/loadEntries(for:timeScope:range:completionHandler:)`` instead.", ios(4.0, 14.0), tvos(9.0, 14.0), macos(10.8, 11.0), watchos(3.0, 7.0));

/// leaderboardID. If nil, fetch the aggregate leaderboard.
@property(copy, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboard/loadEntries(for:timeScope:range:completionHandler:)`` instead.", ios(7.0, 14.0), tvos(9.0, 14.0), macos(10.10, 11.0), watchos(3.0, 7.0));

/// Leaderboards start at index 1 and the length should be less than 100. Does not apply to leaderboards initialized with players.  Exception will be thrown if developer tries to set an invalid range.
@property(assign, NS_NONATOMIC_IOSONLY) NSRange range API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboard/loadEntries(for:timeScope:range:completionHandler:)`` instead.", ios(4.0, 14.0), tvos(9.0, 14.0), macos(10.8, 11.0), watchos(3.0, 7.0));

/// Scores are not valid until loadScores: has completed.
@property(readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSArray<GKScore *> *scores API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboard/loadEntries(for:timeScope:range:completionHandler:)`` instead.", ios(4.0, 14.0), tvos(9.0, 14.0), macos(10.8, 11.0), watchos(3.0, 7.0));

/// The maxRange which represents the size of the leaderboard is not valid until loadScores: has completed.
@property(readonly, assign, NS_NONATOMIC_IOSONLY) NSUInteger maxRange API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboard/loadEntries(for:timeScope:range:completionHandler:)`` instead.", ios(4.0, 14.0), tvos(9.0, 14.0), macos(10.8, 11.0), watchos(3.0, 7.0));

/// The local player's score
@property(readonly, strong, nullable, NS_NONATOMIC_IOSONLY) GKScore *localPlayerScore API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboard/loadEntries(for:timeScope:range:completionHandler:)`` instead.", ios(4.0, 14.0), tvos(9.0, 14.0), macos(10.8, 11.0), watchos(3.0, 7.0));

/// This property is true if the leaderboard is currently loading
@property(readonly, getter=isLoading) BOOL loading API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboard/loadEntries(for:timeScope:range:completionHandler:)`` instead.", ios(4.1, 14.0), tvos(9.0, 14.0), macos(10.8, 11.0), watchos(3.0, 7.0));

/// Default is the range 1-10 with Global/AllTime scopes.
/// If you want to change the scopes or range, set the properites before loading the scores.
- (instancetype)init API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKLeaderboard/loadLeaderboards(IDs:completionHandler:)`` method instead.", ios(4.0, 14.0), tvos(9.0, 14.0), macos(10.8, 11.0), watchos(3.0, 7.0));

/// Specify an array of GKPlayers. For example, the players who are in a match together
/// Defaults to AllTime score, if you want to change the timeScope, set the property before loading the scores. Range and playerScope are not applicable. players may not be nil.
- (instancetype)initWithPlayers:(NSArray<GKPlayer *> *)players API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKLeaderboard/loadEntries(for:timeScope:completionHandler:)`` method instead.", ios(8.0, 14.0), tvos(9.0, 14.0), macos(10.10, 11.0), watchos(3.0, 7.0));

/// Load the scores for this leader board asynchronously. Error will be nil on success.
/// Possible reasons for error:
/// 1. Communications problem
/// 2. Unauthenticated player
- (void)loadScoresWithCompletionHandler:(void(^__nullable)(NSArray<GKScore *> * __nullable scores, NSError * __nullable error))completionHandler API_DEPRECATED_WITH_REPLACEMENT("Use ``GKLeaderboard/loadEntries(for:timeScope:range:completionHandler:)`` instead.", ios(4.0, 14.0), tvos(9.0, 14.0), macos(10.8, 11.0), watchos(3.0, 7.0)) NS_SWIFT_DISABLE_ASYNC;

/// Loads the array of GKLeaderboard for your app
/// Possible reasons for error:
/// 1. Communications problem
/// 2. Unauthenticated player
/// 3. Leaderboard not present
+ (void)loadLeaderboardsWithCompletionHandler:(void(^__nullable)(NSArray<GKLeaderboard *> * __nullable leaderboards, NSError * __nullable error))completionHandler  API_DEPRECATED_WITH_REPLACEMENT("Use the ``GKLeaderboard/loadLeaderboards(IDs:completionHandler:)`` method instead.", ios(6.0, 14.0), tvos(9.0, 14.0), macos(10.8, 11.0), watchos(3.0, 7.0));

@end
NS_ASSUME_NONNULL_END

#if !TARGET_OS_WATCH

@interface GKLeaderboard (UI)
 
#if TARGET_OS_IPHONE
/// Asynchronously load the image. Error will be nil on success.
- (void)loadImageWithCompletionHandler:(void(^__nullable)(UIImage * __nullable image, NSError * __nullable error))completionHandler API_AVAILABLE(ios(7.0), macos(10.8), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);
#else
/// Asynchronously load the image. Error will be nil on success.
- (void)loadImageWithCompletionHandler:(void(^__nullable)(NSImage * __nullable image, NSError * __nullable error))completionHandler API_AVAILABLE(ios(7.0), macos(10.8), visionos(1.0)) API_UNAVAILABLE(tvos, watchos);
#endif

@end

#endif
