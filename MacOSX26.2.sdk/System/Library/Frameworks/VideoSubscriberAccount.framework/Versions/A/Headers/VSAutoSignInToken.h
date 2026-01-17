//
//  VSAutoSignInToken.h
//  VideoSubscriberAccountFramework
//
//  Created by Felipe (fcy) Cypriano on 3/11/25.
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>


#import <VideoSubscriberAccount/VSAutoSignInAuthorization.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(26.0), tvos(26.0), macos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos, macCatalyst)
NS_REFINED_FOR_SWIFT
@interface VSAutoSignInToken : NSObject <NSSecureCoding>

@property (nonatomic, readonly) VSAutoSignInAuthorization authorization;
@property (nonatomic, readonly, nullable) NSString *value;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

