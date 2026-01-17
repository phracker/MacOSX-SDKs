//
//  NSUserActivity+IntentsAdditions.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Intents/INIntent.h>

@class INInteraction;

NS_ASSUME_NONNULL_BEGIN

@interface NSUserActivity (IntentsAdditions)

@property (readonly, nullable, NS_NONATOMIC_IOSONLY) INInteraction *interaction API_AVAILABLE(ios(10.0), macos(12.0), watchos(3.2), tvos(14.0));

// A human-understandable string that can be used to suggest a voice shortcut phrase to the user
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *suggestedInvocationPhrase API_AVAILABLE(ios(12.0), macos(12.0), watchos(5.0)) API_UNAVAILABLE(tvos);

// Defines additional contexts in which this user activity is relevant to be suggested to the user.
@property (readwrite, assign, NS_NONATOMIC_IOSONLY) INShortcutAvailabilityOptions shortcutAvailability API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos, tvos);

@end

NS_ASSUME_NONNULL_END
