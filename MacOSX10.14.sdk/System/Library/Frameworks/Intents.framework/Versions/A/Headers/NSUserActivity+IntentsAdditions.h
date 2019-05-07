//
//  NSUserActivity+IntentsAdditions.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INInteraction;

NS_ASSUME_NONNULL_BEGIN

@interface NSUserActivity (IntentsAdditions)

@property (readonly, nullable, NS_NONATOMIC_IOSONLY) INInteraction *interaction API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.2));

// A human-understandable string that can be used to suggest a voice shortcut phrase to the user
@property (readwrite, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *suggestedInvocationPhrase API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx, tvos);

@end

NS_ASSUME_NONNULL_END
