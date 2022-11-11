//
//  INShortcut.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Intents/INIntent.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract A shortcut is an action that can be suggested by the system or added to Siri.
 */
API_AVAILABLE(ios(12.0), macos(11.0), watchos(5.0)) API_UNAVAILABLE(tvos)
@interface INShortcut : NSObject <NSSecureCoding, NSCopying>

/*!
 @abstract The intent that will be performed when this shortcut is invoked.
 @discussion Is @c nil if the shortcut was created with a @c NSUserActivity.
 */
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INIntent *intent;

/*!
 @abstract The user activity that will be performed when this shortcut is invoked.
 @discussion Is @c nil if the shortcut was created with an @c INIntent.
 */
@property (readonly, strong, nullable, NS_NONATOMIC_IOSONLY) NSUserActivity *userActivity;

/*!
 @note Must be initilaized with either an intent or user activity, using those initializers.
 */
+ (instancetype)new NS_UNAVAILABLE;

/*!
 @note Must be initilaized with either an intent or user activity, using those initializers.
 */
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Creates a shortcut with the given intent.
 @param intent Unless user configurable, must have a title and have valid shortcut types.
 @return Will return @c nil (and log an error) if the intent isn't valid.
 */
- (nullable instancetype)initWithIntent:(INIntent *)intent;

/*!
 @abstract Creates a shortcut with the given user activity.
 */
- (instancetype)initWithUserActivity:(NSUserActivity *)userActivity;

@end

NS_ASSUME_NONNULL_END
