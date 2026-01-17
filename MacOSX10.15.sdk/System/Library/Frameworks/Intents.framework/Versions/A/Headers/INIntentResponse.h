//
//  INIntentResponse.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macosx)
@interface INIntentResponse : NSObject <NSCopying, NSSecureCoding>

// This user activity will be used to launch the containing application when host application finds appropriate or when users request so.
// The containing application should implement the continuity app delegate method(s) to consume this user activity.
@property (copy, readwrite, nullable, nonatomic) NSUserActivity *userActivity;

@end

NS_ASSUME_NONNULL_END
