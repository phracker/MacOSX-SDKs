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

@end

NS_ASSUME_NONNULL_END
