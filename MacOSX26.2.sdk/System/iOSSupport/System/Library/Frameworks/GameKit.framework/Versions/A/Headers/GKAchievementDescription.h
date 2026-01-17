// Copyright © Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>
#import <GameKit/GKReleaseState.h>
#import <TargetConditionals.h>

NS_ASSUME_NONNULL_BEGIN
/// GKAchievementDescription is a full description of the achievement as defined before app submission in App Store Connect.
API_AVAILABLE(ios(4.1), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0))
@interface GKAchievementDescription : NSObject <NSCoding, NSSecureCoding>

/// Asynchronously load all achievement descriptions
+ (void)loadAchievementDescriptionsWithCompletionHandler:(void(^ __nullable)(NSArray<GKAchievementDescription *> * __nullable descriptions,NSError * __nullable error))completionHandler;

@property(copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;
/// The group identifier for the achievement, if one exists.
@property(nonatomic, retain, nullable, readonly) NSString *groupIdentifier API_AVAILABLE(ios(6.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0));
/// The title of the achievement.
@property(copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *title;
/// The description for an unachieved achievement.
@property(copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *achievedDescription;
/// The description for an achieved achievement.
@property(copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *unachievedDescription;
/// Maximum points available for completing this achievement.
@property(assign, readonly, NS_NONATOMIC_IOSONLY) NSInteger maximumPoints;
/// Whether or not the achievement should be listed or displayed if not yet unhidden by the game.
@property(getter = isHidden, assign, readonly, NS_NONATOMIC_IOSONLY) BOOL hidden;
/// Whether or not the achievement will be reported by the game when the user earns it again. This allows the achievement to be used for challenges when the recipient has previously earned it.
@property(nonatomic, getter = isReplayable, assign, readonly) BOOL replayable  API_AVAILABLE(ios(6.0), macos(10.8), tvos(9.0), visionos(1.0), watchos(3.0));
/// If present, the rarity of the achievement expressed as a percentage of players that earned it. Null if not enough data is available to compute it.
@property(copy, readonly, nullable) NSNumber *rarityPercent API_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0)) NS_REFINED_FOR_SWIFT;
/// The release state of the achievement in App Store Connect.
@property(nonatomic, assign, readonly) GKReleaseState releaseState API_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4), visionos(2.4));

/// The identifier of the game activity associated with this achievement, as configured by the developer in App Store Connect.
@property (readonly, nonatomic, copy) NSString *activityIdentifier API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), visionos(26.0), watchos(26.0));

/// The properties when associating this achievement with a game activity, as configured by the developer in App Store Connect.
@property (readonly, nonatomic, strong) NSDictionary<NSString *, NSString *> *activityProperties API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), visionos(26.0), watchos(26.0));
@end
NS_ASSUME_NONNULL_END


#if TARGET_OS_IPHONE
@class UIImage;
#else
@class NSImage;
#endif

@interface GKAchievementDescription (UI)

#if TARGET_OS_IPHONE

// Image for completed achievement. Not valid until loadImage: has completed. Deprecated -- use loadImageWithCompletionHandler: instead.
@property(nonatomic, retain, readonly, nullable) UIImage *image API_DEPRECATED_WITH_REPLACEMENT("Use ``GKAchievementDescription/loadImage(completionHandler:)`` instead.", ios(4.1,7.0), macos(10.8,10.10), tvos(9.0,17.2)) API_UNAVAILABLE(watchos);

// Asynchronously load the image. Error will be nil on success.
- (void)loadImageWithCompletionHandler:(void(^ __nullable)(UIImage * __nullable image, NSError * __nullable error))completionHandler API_UNAVAILABLE(watchos);
#else

// Image for completed achievement. Not valid until loadImage: has completed. Deprecated -- use loadImageWithCompletionHandler: instead.
@property(atomic, retain, readonly, nullable) NSImage *image API_DEPRECATED_WITH_REPLACEMENT("Use ``GKAchievementDescription/loadImage(completionHandler:)`` instead.", macos(10.8,14.2));

// Asynchronously load the image. Error will be nil on success.
- (void)loadImageWithCompletionHandler:(void(^ __nullable)(NSImage * __nullable image, NSError * __nullable error))completionHandler;
#endif

#if TARGET_OS_IPHONE

// The default image for any incomplete achievement
+ (nonnull UIImage *)incompleteAchievementImage API_UNAVAILABLE(watchos);

// A placeholder image to be used for any completed achievement until the description image has loaded.
+ (nonnull UIImage *)placeholderCompletedAchievementImage API_UNAVAILABLE(watchos);

#else

// The default image for any incomplete achievement
+ (nonnull NSImage *)incompleteAchievementImage;

// A placeholder image to be used for any completed achievement until the description image has loaded.
+ (nonnull NSImage *)placeholderCompletedAchievementImage;

#endif

@end

