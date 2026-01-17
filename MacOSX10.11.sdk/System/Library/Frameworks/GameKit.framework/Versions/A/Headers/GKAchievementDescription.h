//
//  GKAchievementDescription.h
//  Game Center
//
//  Copyright 2010-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GameKit/GKDefines.h>


NS_ASSUME_NONNULL_BEGIN
// GKAchievementDescription is a full description of the achievement as defined before app submission in iTunes Connect.
NS_CLASS_AVAILABLE(10_8, 4_1)
@interface GKAchievementDescription : NSObject <NSCoding, NSSecureCoding>

// Asynchronously load all achievement descriptions
+ (void)loadAchievementDescriptionsWithCompletionHandler:(void(^ __nullable)(NSArray<GKAchievementDescription *> * __nullable descriptions,NSError * __nullable error))completionHandler;

@property(copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *identifier;
@property(nonatomic, retain, nullable, readonly) NSString *groupIdentifier NS_AVAILABLE(10_8, 6_0);       // The group identifier for the achievement, if one exists.
@property(copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *title;                 // The title of the achievement.
@property(copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *achievedDescription;   // The description for an unachieved achievement.
@property(copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSString *unachievedDescription; // The description for an achieved achievement.
@property(assign, readonly, NS_NONATOMIC_IOSONLY) NSInteger maximumPoints;         // Maximum points available for completing this achievement.
@property(getter = isHidden, assign, readonly, NS_NONATOMIC_IOSONLY) BOOL hidden;  // Whether or not the achievement should be listed or displayed if not yet unhidden by the game.
@property(nonatomic, getter = isReplayable, assign, readonly) BOOL replayable  NS_AVAILABLE(10_8, 6_0);  // Whether or not the achievement will be reported by the game when the user earns it again. This allows the achievement to be used for challenges when the recipient has previously earned it.
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
@property(nonatomic, retain, readonly, nullable) UIImage *image NS_DEPRECATED(10_8, 10_10, 4_1, 7_0, "Use loadImageWithCompletionHandler: instead");

// Asynchronously load the image. Error will be nil on success.
- (void)loadImageWithCompletionHandler:(void(^ __nullable)(UIImage * __nullable image, NSError * __nullable error))completionHandler;
#else

// Image for completed achievement. Not valid until loadImage: has completed. Deprecated -- use loadImageWithCompletionHandler: instead.
@property(atomic, retain, readonly, nullable) NSImage *image __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_8, __MAC_NA, __IPHONE_4_1, __IPHONE_7_0);

// Asynchronously load the image. Error will be nil on success.
- (void)loadImageWithCompletionHandler:(void(^ __nullable)(NSImage * __nullable image, NSError * __nullable error))completionHandler;
#endif

#if TARGET_OS_IPHONE

// The default image for any incomplete achievement
+ (nonnull UIImage *)incompleteAchievementImage;

// A placeholder image to be used for any completed achievement until the description image has loaded.
+ (nonnull UIImage *)placeholderCompletedAchievementImage;

#else

// The default image for any incomplete achievement
+ (nonnull NSImage *)incompleteAchievementImage;

// A placeholder image to be used for any completed achievement until the description image has loaded.
+ (nonnull NSImage *)placeholderCompletedAchievementImage;

#endif

@end


